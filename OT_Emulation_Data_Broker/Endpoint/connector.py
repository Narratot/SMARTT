from __future__ import annotations

import threading
import logging
import queue
import time
import socket
import sys
import os

import numpy as np
import zmq
import pandas as pd


class Data_Repo(object):
    def __init__(self, SetString):
        Strings = SetString.split(",")
        self.Tags = Strings[::2]
        Mem_Strings = Strings[1::2]
        self.Mem = [int(n) for n in Mem_Strings]
        self.Tag_NoDuplicates = list(set(self.Tags))
        Val = [0.0] * len(self.Tag_NoDuplicates)
        self.Store = dict(zip(self.Tag_NoDuplicates, Val))

    def write(self, Tag, Value):
        self.Store[Tag] = Value

    def read(self, Tag):
        return self.Store[Tag]

    def UDP_TAGS(self):
        return self.Tag_NoDuplicates


def cusum_row(predicted: pd.DataFrame, measured: pd.DataFrame):
    shape = predicted.shape
    result = np.zeros(shape)

    for j in range(shape[1]):
        for i in range(shape[0]):
            result[i, j] = measured.iloc[i, j] - predicted.iloc[i, j]

    return result


class Data(object):
    def __init__(self, sensortags, window_size):
        self.index = ['Time', sensortags]
        self.data = []
        self.window = window_size
        self.prediction = []

    def add_data(self, values):
        self.data.append(values)

    def add_prediction(self, values):
        self.prediction.append(values)

    def compare_prediction(self):
        predictiondf = pd.DataFrame(columns=self.index, data=self.prediction)
        predictiondf.set_index('Time')
        datadf = pd.DataFrame(columns=self.index, data=self.data)
        datadf = datadf.loc(predictiondf.index)

        return cusum_row(predictiondf, datadf)

    def output(self):
        if len(self.data) >= self.window:
            df = pd.DataFrame(columns=self.index, data=self.data[-self.window:])
            df.set_index('Time')
            return df
        else:
            return False


# Initialisation Routine
def initialization():
    context = zmq.Context()
    reciever = context.socket(zmq.REP)
    reciever.bind("tcp://*:6666")

    msgFromServer = reciever.recv()
    msg = str(msgFromServer, 'UTF-8')
    data = msg.split(":")
    reply = bytes(str(data[0]) + " has initialized", 'utf-8')
    reciever.send(reply)
    reciever.close()

    Endian_Key = data[9].split(",")
    Format_Key = data[8].split(",")
    sensor_name_key = data[3].split(",")
    actuator_name_key = data[5].split(",")

    # Parse the sensor and actuator names and memory locations
    if sensor_name_key[0] != "NULL" and len(sensor_name_key) > 1:
        Sensor_Tags = sensor_name_key[::2]
        Sensor_Mem = sensor_name_key[1::2]
    else:
        Sensor_Tags = None
        Sensor_Mem = -1

    data = data[1:len(data) - 1]
    return Sensor_Tags, Sensor_Mem, data


# Logging and Detection
def detection(sensor_data, lock):
    log_data = sensor_data
    tags = log_data.UDP_TAGS()
    msg = str(log_data.read('Time'))
    data = [log_data.read('Time')]
    for i in range(len(Sensor_Tags)):
        msg = msg + ';' + str(log_data.read(Sensor_Tags[i]))
        data.append(log_data.read(Sensor_Tags[i]))

    csv_lgr.debug(msg)


# UDP CLient

def UDP_Client(Data, Lock):
    bufferSize = 128 * 1000
    serverAddressPort = ("255.255.255.255", 8000)
    # Create a UDP socket at client side
    UDPClientSocket = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)
    UDPClientSocket.bind(serverAddressPort)
    UDPClientSocket.settimeout(30)

    # grab tag names from Data class
    with Lock:
        Tags = Data.UDP_TAGS()

    # initalize values
    nTags = len(Tags)
    Values = [0.0] * nTags
    Time_Stamp = 0.0
    First_Time = True

    while not event.is_set():
        # recieve message from UDP
        msgFromServer, address = UDPClientSocket.recvfrom(bufferSize)
        # check if its the first update to pass the server IP to PLC threads
        if First_Time:
            First_Time = False

        # Decode message
        msg = str(msgFromServer, 'UTF-8')
        msg_split = msg.split()

        # See if a stop was requested
        if msg_split[0] == "STOP":
            event.set()
            logging.info("UDP Client was sent stop request from DataBroker.")
            break

        # get and store values from msg
        for i in range(nTags):
            try:
                IDX = msg_split.index(Tags[i])
                Values[i] = float(msg_split[IDX + 1])
                Time_Stamp = float(msg_split[IDX + 2])
            except:
                logging.info("Tag: %s not in UDP message..." % Tags[i])

        # plop data in data repo
        with Lock:
            for i in range(nTags):
                Data.write(Tags[i], Values[i])
                Data.write("Time", Time_Stamp)

        detection(Data, Lock)

    UDPClientSocket.close()
    logging.info("UDP Client received event. Exiting")
    sys.exit(0)


if __name__ == "__main__":

    WINDOW_SIZE = 360

    format = "%(asctime)s: %(message)s"
    logging.basicConfig(format=format, level=logging.INFO,
                        datefmt="%H:%M:%S")

    pipeline = queue.Queue(maxsize=100)
    serverAddress = queue.Queue(maxsize=10)

    # create logger
    csv_lgr = logging.getLogger('CSV Writer')
    csv_lgr.setLevel(logging.DEBUG)  # log all escalated at and above DEBUG
    # add a file handler
    fh = logging.FileHandler('data_csv.csv')
    fh.setLevel(logging.DEBUG)  # ensure all messages are logged to file

    # create a formatter and set the formatter for the handler.
    frmt = logging.Formatter('%(message)s')
    fh.setFormatter(frmt)

    # add the Handler to the logger
    csv_lgr.addHandler(fh)

    event = threading.Event()
    Lock = threading.Lock()

    # Initialize system
    Sensor_Tags, Sensor_Mem, data = initialization()
    tag_str = 'Time'
    for i in range(len(Sensor_Tags)):
        tag_str = tag_str + ';' + Sensor_Tags[i]

    #data = Data(Sensor_Tags, WINDOW_SIZE)

    csv_lgr.debug(tag_str)

    Sensor_Data = Data_Repo(data[2])
    Sensor_Data.write("Time", 0.0)

    # setup UDP thread
    UDP_Thread = threading.Thread(target=UDP_Client, args=(Sensor_Data, Lock))
    UDP_Thread.daemon = True

    # CSV_Thread = threading.Thread(target=detection, args=(Sensor_Data, Lock))
    # CSV_Thread.daemon = True

    try:
        # Start threads and wait for completion
        UDP_Thread.start()
        UDP_Thread.join()

        #    CSV_Thread.start()
        #    CSV_Thread.join()

        time.sleep(2)

    except KeyboardInterrupt:
        print('Interrupted')
        try:
            event.set()
            sys.exit(0)
        except SystemExit:
            event.set()
            os._exit(0)

### --- ZMQ Router Dealer --- ###

# import zmq

# Prepare our context and sockets
# context = zmq.Context()
# frontend = context.socket(zmq.ROUTER)
# backend = context.socket(zmq.DEALER)
# frontend.bind("tcp://*:5559")
# backend.bind("tcp://*:5560")

# Initialize poll set
# poller = zmq.Poller()
# poller.register(frontend, zmq.POLLIN)
# poller.register(backend, zmq.POLLIN)

# Switch messages between sockets
# while True:
#  socks = dict(poller.poll())

#  if socks.get(frontend) == zmq.POLLIN:
#    message = frontend.recv_multipart()
#    backend.send_multipart(message)

#  if socks.get(backend) == zmq.POLLIN:
#    message = backend.recv_multipart()
#    frontend.send_multipart(message)
