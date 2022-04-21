void LOGGER_init__(LOGGER *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->MSG,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->LEVEL,LOGLEVEL__INFO,retain)
  __INIT_VAR(data__->TRIG0,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void LOGGER_body__(LOGGER *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  if ((__GET_VAR(data__->TRIG,) && !(__GET_VAR(data__->TRIG0,)))) {
    #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
    #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)

   LogMessage(GetFbVar(LEVEL),(char*)GetFbVar(MSG, .body),GetFbVar(MSG, .len));
  
    #undef GetFbVar
    #undef SetFbVar
;
  };
  __SET_VAR(data__->,TRIG0,,__GET_VAR(data__->TRIG,));

  goto __end;

__end:
  return;
} // LOGGER_body__() 





void PYTHON_EVAL_init__(PYTHON_EVAL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->BUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->PREBUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->TRIGM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TRIGGED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_EVAL_body__(PYTHON_EVAL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(0, data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // PYTHON_EVAL_body__() 





void PYTHON_POLL_init__(PYTHON_POLL *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->STATE,0,retain)
  __INIT_VAR(data__->BUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->PREBUFFER,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->TRIGM1,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->TRIGGED,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_POLL_body__(PYTHON_POLL *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  #define GetFbVar(var,...) __GET_VAR(data__->var,__VA_ARGS__)
  #define SetFbVar(var,val,...) __SET_VAR(data__->,var,__VA_ARGS__,val)
extern void __PythonEvalFB(int, PYTHON_EVAL*);__PythonEvalFB(1,(PYTHON_EVAL*)(void*)data__);
  #undef GetFbVar
  #undef SetFbVar
;

  goto __end;

__end:
  return;
} // PYTHON_POLL_body__() 





void PYTHON_GEAR_init__(PYTHON_GEAR *data__, BOOL retain) {
  __INIT_VAR(data__->EN,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->ENO,__BOOL_LITERAL(TRUE),retain)
  __INIT_VAR(data__->N,0,retain)
  __INIT_VAR(data__->TRIG,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->CODE,__STRING_LITERAL(0,""),retain)
  __INIT_VAR(data__->ACK,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->RESULT,__STRING_LITERAL(0,""),retain)
  PYTHON_EVAL_init__(&data__->PY_EVAL,retain);
  __INIT_VAR(data__->COUNTER,0,retain)
  __INIT_VAR(data__->ADD10_OUT,0,retain)
  __INIT_VAR(data__->EQ13_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->SEL15_OUT,0,retain)
  __INIT_VAR(data__->AND7_OUT,__BOOL_LITERAL(FALSE),retain)
}

// Code part
void PYTHON_GEAR_body__(PYTHON_GEAR *data__) {
  // Control execution
  if (!__GET_VAR(data__->EN)) {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(FALSE));
    return;
  }
  else {
    __SET_VAR(data__->,ENO,,__BOOL_LITERAL(TRUE));
  }
  // Initialise TEMP variables

  __SET_VAR(data__->,ADD10_OUT,,ADD__UINT__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->COUNTER,),
    (UINT)1));
  __SET_VAR(data__->,EQ13_OUT,,EQ__BOOL__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (UINT)__GET_VAR(data__->N,),
    (UINT)__GET_VAR(data__->ADD10_OUT,)));
  __SET_VAR(data__->,SEL15_OUT,,SEL__UINT__BOOL__UINT__UINT(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->EQ13_OUT,),
    (UINT)__GET_VAR(data__->ADD10_OUT,),
    (UINT)0));
  __SET_VAR(data__->,COUNTER,,__GET_VAR(data__->SEL15_OUT,));
  __SET_VAR(data__->,AND7_OUT,,AND__BOOL__BOOL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (BOOL)__GET_VAR(data__->EQ13_OUT,),
    (BOOL)__GET_VAR(data__->TRIG,)));
  __SET_VAR(data__->PY_EVAL.,TRIG,,__GET_VAR(data__->AND7_OUT,));
  __SET_VAR(data__->PY_EVAL.,CODE,,__GET_VAR(data__->CODE,));
  PYTHON_EVAL_body__(&data__->PY_EVAL);
  __SET_VAR(data__->,ACK,,__GET_VAR(data__->PY_EVAL.ACK,));
  __SET_VAR(data__->,RESULT,,__GET_VAR(data__->PY_EVAL.RESULT,));

  goto __end;

__end:
  return;
} // PYTHON_GEAR_body__() 





void SD_P_init__(SD_P *data__, BOOL retain) {
  __INIT_VAR(data__->TIME_IN,0,retain)
  __INIT_VAR(data__->TIME_OUT,0,retain)
  __INIT_VAR(data__->SG1_PRESS,0,retain)
  __INIT_VAR(data__->SG2_PRESS,0,retain)
  __INIT_VAR(data__->SD_VALVE,0,retain)
  __INIT_VAR(data__->SD_ONOFF,0.0,retain)
  __INIT_VAR(data__->MANIPIO_CONTROL,0.0,retain)
  __INIT_VAR(data__->KPI,0.00005,retain)
  __INIT_VAR(data__->TI,20.0,retain)
  __INIT_VAR(data__->SET_POINT,7692000.0,retain)
  __INIT_VAR(data__->INIT,0.0,retain)
  INTEGRAL_init__(&data__->INTEGRAL0,retain);
  __INIT_VAR(data__->EQ24_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->ADD34_OUT,0,retain)
  __INIT_VAR(data__->DIV33_OUT,0,retain)
  __INIT_VAR(data__->LIMIT36_OUT,0,retain)
  __INIT_VAR(data__->SUB27_OUT,0,retain)
  __INIT_VAR(data__->MUL7_OUT,0,retain)
  __INIT_VAR(data__->EQ30_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->EQ21_OUT,__BOOL_LITERAL(FALSE),retain)
  __INIT_VAR(data__->DIV9_OUT,0,retain)
  __INIT_VAR(data__->MUL12_OUT,0,retain)
  __INIT_VAR(data__->SEL6_OUT,0,retain)
  __INIT_VAR(data__->ADD14_OUT,0,retain)
  __INIT_VAR(data__->LIMIT18_OUT,0,retain)
  __INIT_VAR(data__->SEL23_OUT,0,retain)
}

// Code part
void SD_P_body__(SD_P *data__) {
  // Initialise TEMP variables

  __SET_VAR(data__->,TIME_OUT,,__GET_VAR(data__->TIME_IN,));
  __SET_VAR(data__->,EQ24_OUT,,EQ__BOOL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->MANIPIO_CONTROL,),
    (REAL)1.0));
  __SET_VAR(data__->,ADD34_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->SG1_PRESS,),
    (REAL)__GET_VAR(data__->SG2_PRESS,)));
  __SET_VAR(data__->,DIV33_OUT,,DIV__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->ADD34_OUT,),
    (REAL)2.0));
  __SET_VAR(data__->,LIMIT36_OUT,,LIMIT__REAL__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)0.0,
    (REAL)__GET_VAR(data__->DIV33_OUT,),
    (REAL)999999999.0));
  __SET_VAR(data__->,SUB27_OUT,,SUB__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)__GET_VAR(data__->LIMIT36_OUT,),
    (REAL)__GET_VAR(data__->SET_POINT,)));
  __SET_VAR(data__->,MUL7_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->SUB27_OUT,),
    (REAL)__GET_VAR(data__->KPI,)));
  __SET_VAR(data__->,EQ30_OUT,,EQ__BOOL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->TIME_IN,),
    (REAL)0.0));
  __SET_VAR(data__->,EQ21_OUT,,EQ__BOOL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->LIMIT18_OUT,),
    (REAL)__GET_VAR(data__->ADD14_OUT,)));
  __SET_VAR(data__->,DIV9_OUT,,DIV__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)1.0,
    (REAL)__GET_VAR(data__->TI,)));
  __SET_VAR(data__->,MUL12_OUT,,MUL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->MUL7_OUT,),
    (REAL)__GET_VAR(data__->DIV9_OUT,)));
  __SET_VAR(data__->,SEL6_OUT,,SEL__REAL__BOOL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->EQ21_OUT,),
    (REAL)0.0,
    (REAL)__GET_VAR(data__->MUL12_OUT,)));
  __SET_VAR(data__->INTEGRAL0.,RUN,,1);
  __SET_VAR(data__->INTEGRAL0.,R1,,__GET_VAR(data__->EQ30_OUT,));
  __SET_VAR(data__->INTEGRAL0.,XIN,,__GET_VAR(data__->SEL6_OUT,));
  __SET_VAR(data__->INTEGRAL0.,X0,,__GET_VAR(data__->INIT,));
  __SET_VAR(data__->INTEGRAL0.,CYCLE,,__time_to_timespec(1, 100, 0, 0, 0, 0));
  INTEGRAL_body__(&data__->INTEGRAL0);
  __SET_VAR(data__->,ADD14_OUT,,ADD__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (UINT)2,
    (REAL)__GET_VAR(data__->MUL7_OUT,),
    (REAL)__GET_VAR(data__->INTEGRAL0.XOUT,)));
  __SET_VAR(data__->,LIMIT18_OUT,,LIMIT__REAL__REAL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (REAL)0.0,
    (REAL)__GET_VAR(data__->ADD14_OUT,),
    (REAL)120.0));
  __SET_VAR(data__->,SEL23_OUT,,SEL__REAL__BOOL__REAL__REAL(
    (BOOL)__BOOL_LITERAL(TRUE),
    NULL,
    (BOOL)__GET_VAR(data__->EQ24_OUT,),
    (REAL)__GET_VAR(data__->LIMIT18_OUT,),
    (REAL)__GET_VAR(data__->SD_VALVE,)));
  __SET_VAR(data__->,SD_VALVE,,__GET_VAR(data__->SEL23_OUT,));

  goto __end;

__end:
  return;
} // SD_P_body__() 





