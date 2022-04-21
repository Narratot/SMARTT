TYPE
  LOGLEVEL : (CRITICAL, WARNING, INFO, DEBUG) := INFO;
END_TYPE

FUNCTION_BLOCK LOGGER
  VAR_INPUT
    TRIG : BOOL;
    MSG : STRING;
    LEVEL : LOGLEVEL := INFO;
  END_VAR
  VAR
    TRIG0 : BOOL;
  END_VAR

  IF TRIG AND NOT TRIG0 THEN
  {{
   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  }}
  END_IF;
  TRIG0:=TRIG;
END_FUNCTION_BLOCK



FUNCTION_BLOCK python_eval
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_poll
  VAR_INPUT
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    STATE : DWORD;
    BUFFER : STRING;
    PREBUFFER : STRING;
    TRIGM1 : BOOL;
    TRIGGED : BOOL;
  END_VAR

  {extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);}
END_FUNCTION_BLOCK

FUNCTION_BLOCK python_gear
  VAR_INPUT
    N : UINT;
    TRIG : BOOL;
    CODE : STRING;
  END_VAR
  VAR_OUTPUT
    ACK : BOOL;
    RESULT : STRING;
  END_VAR
  VAR
    py_eval : python_eval;
    COUNTER : UINT;
    ADD10_OUT : UINT;
    EQ13_OUT : BOOL;
    SEL15_OUT : UINT;
    AND7_OUT : BOOL;
  END_VAR

  ADD10_OUT := ADD(COUNTER, 1);
  EQ13_OUT := EQ(N, ADD10_OUT);
  SEL15_OUT := SEL(EQ13_OUT, ADD10_OUT, 0);
  COUNTER := SEL15_OUT;
  AND7_OUT := AND(EQ13_OUT, TRIG);
  py_eval(TRIG := AND7_OUT, CODE := CODE);
  ACK := py_eval.ACK;
  RESULT := py_eval.RESULT;
END_FUNCTION_BLOCK


PROGRAM SD_P
  VAR
    TIME_IN : REAL;
    TIME_OUT : REAL;
    SG1_Press : REAL;
    SG2_Press : REAL;
    SD_Valve : REAL;
    SD_OnOff : REAL := 0.0;
    MANIPIO_CONTROL : REAL := 0.0;
    KPI : REAL := 0.00005;
    Ti : REAL := 20.0;
    SET_POINT : REAL := 7692000.0;
    INIT : REAL := 0.0;
  END_VAR
  VAR
    INTEGRAL0 : INTEGRAL;
    EQ24_OUT : BOOL;
    ADD34_OUT : REAL;
    DIV33_OUT : REAL;
    LIMIT36_OUT : REAL;
    SUB27_OUT : REAL;
    MUL7_OUT : REAL;
    EQ30_OUT : BOOL;
    EQ21_OUT : BOOL;
    DIV9_OUT : REAL;
    MUL12_OUT : REAL;
    SEL6_OUT : REAL;
    ADD14_OUT : REAL;
    LIMIT18_OUT : REAL;
    SEL23_OUT : REAL;
  END_VAR

  TIME_OUT := TIME_IN;
  EQ24_OUT := EQ(MANIPIO_CONTROL, 1.0);
  ADD34_OUT := ADD(SG1_Press, SG2_Press);
  DIV33_OUT := DIV(ADD34_OUT, 2.0);
  LIMIT36_OUT := LIMIT(0.0, DIV33_OUT, 999999999.0);
  SUB27_OUT := SUB(LIMIT36_OUT, SET_POINT);
  MUL7_OUT := MUL(SUB27_OUT, KPI);
  EQ30_OUT := EQ(TIME_IN, 0.0);
  EQ21_OUT := EQ(LIMIT18_OUT, ADD14_OUT);
  DIV9_OUT := DIV(1.0, Ti);
  MUL12_OUT := MUL(MUL7_OUT, DIV9_OUT);
  SEL6_OUT := SEL(EQ21_OUT, 0.0, MUL12_OUT);
  INTEGRAL0(RUN := 1, R1 := EQ30_OUT, XIN := SEL6_OUT, X0 := INIT, CYCLE := T#100ms);
  ADD14_OUT := ADD(MUL7_OUT, INTEGRAL0.XOUT);
  LIMIT18_OUT := LIMIT(0.0, ADD14_OUT, 120.0);
  SEL23_OUT := SEL(EQ24_OUT, LIMIT18_OUT, SD_Valve);
  SD_Valve := SEL23_OUT;
END_PROGRAM


CONFIGURATION Config0

  RESOURCE Res0 ON PLC
    TASK task0(INTERVAL := T#100ms,PRIORITY := 0);
    PROGRAM instance0 WITH task0 : SD_P;
  END_RESOURCE
END_CONFIGURATION