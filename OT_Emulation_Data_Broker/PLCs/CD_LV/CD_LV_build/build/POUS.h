#include "beremiz.h"
#ifndef __POUS_H
#define __POUS_H

#include "accessor.h"
#include "iec_std_lib.h"

__DECLARE_ENUMERATED_TYPE(LOGLEVEL,
  LOGLEVEL__CRITICAL,
  LOGLEVEL__WARNING,
  LOGLEVEL__INFO,
  LOGLEVEL__DEBUG
)
// FUNCTION_BLOCK LOGGER
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,MSG)
  __DECLARE_VAR(LOGLEVEL,LEVEL)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(BOOL,TRIG0)

} LOGGER;

void LOGGER_init__(LOGGER *data__, BOOL retain);
// Code part
void LOGGER_body__(LOGGER *data__);
// FUNCTION_BLOCK PYTHON_EVAL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DWORD,STATE)
  __DECLARE_VAR(STRING,BUFFER)
  __DECLARE_VAR(STRING,PREBUFFER)
  __DECLARE_VAR(BOOL,TRIGM1)
  __DECLARE_VAR(BOOL,TRIGGED)

} PYTHON_EVAL;

void PYTHON_EVAL_init__(PYTHON_EVAL *data__, BOOL retain);
// Code part
void PYTHON_EVAL_body__(PYTHON_EVAL *data__);
// FUNCTION_BLOCK PYTHON_POLL
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  __DECLARE_VAR(DWORD,STATE)
  __DECLARE_VAR(STRING,BUFFER)
  __DECLARE_VAR(STRING,PREBUFFER)
  __DECLARE_VAR(BOOL,TRIGM1)
  __DECLARE_VAR(BOOL,TRIGGED)

} PYTHON_POLL;

void PYTHON_POLL_init__(PYTHON_POLL *data__, BOOL retain);
// Code part
void PYTHON_POLL_body__(PYTHON_POLL *data__);
// FUNCTION_BLOCK PYTHON_GEAR
// Data part
typedef struct {
  // FB Interface - IN, OUT, IN_OUT variables
  __DECLARE_VAR(BOOL,EN)
  __DECLARE_VAR(BOOL,ENO)
  __DECLARE_VAR(UINT,N)
  __DECLARE_VAR(BOOL,TRIG)
  __DECLARE_VAR(STRING,CODE)
  __DECLARE_VAR(BOOL,ACK)
  __DECLARE_VAR(STRING,RESULT)

  // FB private variables - TEMP, private and located variables
  PYTHON_EVAL PY_EVAL;
  __DECLARE_VAR(UINT,COUNTER)
  __DECLARE_VAR(UINT,ADD10_OUT)
  __DECLARE_VAR(BOOL,EQ13_OUT)
  __DECLARE_VAR(UINT,SEL15_OUT)
  __DECLARE_VAR(BOOL,AND7_OUT)

} PYTHON_GEAR;

void PYTHON_GEAR_init__(PYTHON_GEAR *data__, BOOL retain);
// Code part
void PYTHON_GEAR_body__(PYTHON_GEAR *data__);
// PROGRAM CD_LV_PLC
// Data part
typedef struct {
  // PROGRAM Interface - IN, OUT, IN_OUT variables

  // PROGRAM private variables - TEMP, private and located variables
  __DECLARE_VAR(REAL,TIME_IN)
  __DECLARE_VAR(REAL,TIME_OUT)
  __DECLARE_VAR(REAL,CD_LEVEL)
  __DECLARE_VAR(REAL,RX_POWER)
  __DECLARE_VAR(REAL,CE_PUMP_SPEED_1)
  __DECLARE_VAR(REAL,CE_PUMP_SPEED_2)
  __DECLARE_VAR(REAL,CE_PUMP_SPEED_3)
  __DECLARE_VAR(REAL,CE_PUMP_ONOFF_1)
  __DECLARE_VAR(REAL,CE_PUMP_ONOFF_2)
  __DECLARE_VAR(REAL,CE_PUMP_ONOFF_3)
  __DECLARE_VAR(REAL,MANIPIO_CONTROL)
  __DECLARE_VAR(REAL,KPI)
  __DECLARE_VAR(REAL,TI)
  __DECLARE_VAR(REAL,SET_POINT)
  __DECLARE_VAR(REAL,INIT)
  INTEGRAL INTEGRAL0;
  __DECLARE_VAR(BOOL,EQ24_OUT)
  __DECLARE_VAR(REAL,SUB27_OUT)
  __DECLARE_VAR(REAL,MUL7_OUT)
  __DECLARE_VAR(BOOL,EQ30_OUT)
  __DECLARE_VAR(BOOL,EQ21_OUT)
  __DECLARE_VAR(REAL,DIV9_OUT)
  __DECLARE_VAR(REAL,MUL12_OUT)
  __DECLARE_VAR(REAL,SEL6_OUT)
  __DECLARE_VAR(REAL,ADD14_OUT)
  __DECLARE_VAR(REAL,LIMIT18_OUT)
  __DECLARE_VAR(REAL,SEL23_OUT)

} CD_LV_PLC;

void CD_LV_PLC_init__(CD_LV_PLC *data__, BOOL retain);
// Code part
void CD_LV_PLC_body__(CD_LV_PLC *data__);
#endif //__POUS_H
