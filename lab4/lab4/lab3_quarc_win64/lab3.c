/*
 * lab3.c
 *
 * Code generation for model "lab3".
 *
 * Model version              : 1.26
 * Simulink Coder version : 8.5 (R2013b) 08-Aug-2013
 * C source code generated on : Wed Oct 04 17:20:44 2017
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: 32-bit Generic
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */
#include "lab3.h"
#include "lab3_private.h"
#include "lab3_dt.h"

/* Block signals (auto storage) */
B_lab3_T lab3_B;

/* Continuous states */
X_lab3_T lab3_X;

/* Block states (auto storage) */
DW_lab3_T lab3_DW;

/* Real-time model */
RT_MODEL_lab3_T lab3_M_;
RT_MODEL_lab3_T *const lab3_M = &lab3_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  lab3_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  lab3_step();
  lab3_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  lab3_step();
  lab3_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void lab3_step(void)
{
  /* local block i/o variables */
  real_T rtb_TransferFcn;
  real_T rtb_HILReadEncoder_o2;
  if (rtmIsMajorTimeStep(lab3_M)) {
    /* set solver stop time */
    if (!(lab3_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&lab3_M->solverInfo, ((lab3_M->Timing.clockTickH0 +
        1) * lab3_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&lab3_M->solverInfo, ((lab3_M->Timing.clockTick0 + 1)
        * lab3_M->Timing.stepSize0 + lab3_M->Timing.clockTickH0 *
        lab3_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(lab3_M)) {
    lab3_M->Timing.t[0] = rtsiGetT(&lab3_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(lab3_M)) {
  }

  /* Clock: '<Root>/Clock' */
  lab3_B.Clock = lab3_M->Timing.t[0];
  if (rtmIsMajorTimeStep(lab3_M)) {
    /* S-Function (hil_read_encoder_block): '<Root>/HIL Read Encoder' */

    /* S-Function Block: lab3/HIL Read Encoder (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(lab3_DW.HILInitialize_Card,
        lab3_P.HILReadEncoder_Channels, 2, &lab3_DW.HILReadEncoder_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
      } else {
        lab3_B.HILReadEncoder_o1 = lab3_DW.HILReadEncoder_Buffer[0];
        rtb_HILReadEncoder_o2 = lab3_DW.HILReadEncoder_Buffer[1];
      }
    }

    /* Gain: '<Root>/Gain1' */
    lab3_B.Gain1 = lab3_P.Gain1_Gain * lab3_B.HILReadEncoder_o1;
  }

  /* Clock: '<Root>/Clock1' */
  rtb_TransferFcn = lab3_M->Timing.t[0];

  /* Fcn: '<Root>/Fcn' */
  lab3_B.Fcn = sin(3.0 * rtb_TransferFcn) * 0.15 * exp(-0.3 * rtb_TransferFcn);

  /* Sum: '<Root>/Sum' */
  lab3_B.Sum = lab3_B.Fcn - lab3_B.Gain1;

  /* TransferFcn: '<Root>/Transfer Fcn' */
  rtb_TransferFcn = 0.0;
  rtb_TransferFcn += lab3_P.TransferFcn_C * lab3_X.TransferFcn_CSTATE;
  rtb_TransferFcn += lab3_P.TransferFcn_D * lab3_B.Sum;

  /* Saturate: '<Root>/Saturation' */
  if (rtb_TransferFcn >= lab3_P.Saturation_UpperSat) {
    lab3_B.Saturation = lab3_P.Saturation_UpperSat;
  } else if (rtb_TransferFcn <= lab3_P.Saturation_LowerSat) {
    lab3_B.Saturation = lab3_P.Saturation_LowerSat;
  } else {
    lab3_B.Saturation = rtb_TransferFcn;
  }

  /* End of Saturate: '<Root>/Saturation' */
  if (rtmIsMajorTimeStep(lab3_M)) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: lab3/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(lab3_DW.HILInitialize_Card,
        &lab3_P.HILWriteAnalog_Channels, 1, &lab3_B.Saturation);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
      }
    }
  }

  if (rtmIsMajorTimeStep(lab3_M)) {
    /* External mode */
    rtExtModeUploadCheckTrigger(2);

    {                                  /* Sample time: [0.0s, 0.0s] */
      rtExtModeUpload(0, lab3_M->Timing.t[0]);
    }

    if (rtmIsMajorTimeStep(lab3_M)) {  /* Sample time: [0.002s, 0.0s] */
      rtExtModeUpload(1, (((lab3_M->Timing.clockTick1+lab3_M->Timing.clockTickH1*
                            4294967296.0)) * 0.002));
    }
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep(lab3_M)) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal(lab3_M)!=-1) &&
          !((rtmGetTFinal(lab3_M)-(((lab3_M->Timing.clockTick1+
               lab3_M->Timing.clockTickH1* 4294967296.0)) * 0.002)) >
            (((lab3_M->Timing.clockTick1+lab3_M->Timing.clockTickH1*
               4294967296.0)) * 0.002) * (DBL_EPSILON))) {
        rtmSetErrorStatus(lab3_M, "Simulation finished");
      }

      if (rtmGetStopRequested(lab3_M)) {
        rtmSetErrorStatus(lab3_M, "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&lab3_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++lab3_M->Timing.clockTick0)) {
      ++lab3_M->Timing.clockTickH0;
    }

    lab3_M->Timing.t[0] = rtsiGetSolverStopTime(&lab3_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.002s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.002, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      lab3_M->Timing.clockTick1++;
      if (!lab3_M->Timing.clockTick1) {
        lab3_M->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void lab3_derivatives(void)
{
  XDot_lab3_T *_rtXdot;
  _rtXdot = ((XDot_lab3_T *) lab3_M->ModelData.derivs);

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = 0.0;
  _rtXdot->TransferFcn_CSTATE += lab3_P.TransferFcn_A *
    lab3_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += lab3_B.Sum;
}

/* Model initialize function */
void lab3_initialize(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)lab3_M, 0,
                sizeof(RT_MODEL_lab3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&lab3_M->solverInfo, &lab3_M->Timing.simTimeStep);
    rtsiSetTPtr(&lab3_M->solverInfo, &rtmGetTPtr(lab3_M));
    rtsiSetStepSizePtr(&lab3_M->solverInfo, &lab3_M->Timing.stepSize0);
    rtsiSetdXPtr(&lab3_M->solverInfo, &lab3_M->ModelData.derivs);
    rtsiSetContStatesPtr(&lab3_M->solverInfo, (real_T **)
                         &lab3_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&lab3_M->solverInfo, &lab3_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&lab3_M->solverInfo, (&rtmGetErrorStatus(lab3_M)));
    rtsiSetRTModelPtr(&lab3_M->solverInfo, lab3_M);
  }

  rtsiSetSimTimeStep(&lab3_M->solverInfo, MAJOR_TIME_STEP);
  lab3_M->ModelData.intgData.y = lab3_M->ModelData.odeY;
  lab3_M->ModelData.intgData.f[0] = lab3_M->ModelData.odeF[0];
  lab3_M->ModelData.intgData.f[1] = lab3_M->ModelData.odeF[1];
  lab3_M->ModelData.intgData.f[2] = lab3_M->ModelData.odeF[2];
  lab3_M->ModelData.contStates = ((X_lab3_T *) &lab3_X);
  rtsiSetSolverData(&lab3_M->solverInfo, (void *)&lab3_M->ModelData.intgData);
  rtsiSetSolverName(&lab3_M->solverInfo,"ode3");
  rtmSetTPtr(lab3_M, &lab3_M->Timing.tArray[0]);
  rtmSetTFinal(lab3_M, 18.0);
  lab3_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  lab3_M->Sizes.checksums[0] = (3605075674U);
  lab3_M->Sizes.checksums[1] = (1916688379U);
  lab3_M->Sizes.checksums[2] = (3904675101U);
  lab3_M->Sizes.checksums[3] = (97831241U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    lab3_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(lab3_M->extModeInfo,
      &lab3_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(lab3_M->extModeInfo, lab3_M->Sizes.checksums);
    rteiSetTPtr(lab3_M->extModeInfo, rtmGetTPtr(lab3_M));
  }

  /* block I/O */
  (void) memset(((void *) &lab3_B), 0,
                sizeof(B_lab3_T));

  /* states (continuous) */
  {
    (void) memset((void *)&lab3_X, 0,
                  sizeof(X_lab3_T));
  }

  /* states (dwork) */
  (void) memset((void *)&lab3_DW, 0,
                sizeof(DW_lab3_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    lab3_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 15;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.B = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.P = &rtPTransTable;
  }

  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: lab3/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &lab3_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(lab3_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(lab3_DW.HILInitialize_Card,
      "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(lab3_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(lab3_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(lab3_M, _rt_error_message);
      return;
    }

    if ((lab3_P.HILInitialize_AIPStart && !is_switching) ||
        (lab3_P.HILInitialize_AIPEnter && is_switching)) {
      lab3_DW.HILInitialize_AIMinimums[0] = lab3_P.HILInitialize_AILow;
      lab3_DW.HILInitialize_AIMinimums[1] = lab3_P.HILInitialize_AILow;
      lab3_DW.HILInitialize_AIMaximums[0] = lab3_P.HILInitialize_AIHigh;
      lab3_DW.HILInitialize_AIMaximums[1] = lab3_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(lab3_DW.HILInitialize_Card,
        lab3_P.HILInitialize_AIChannels, 2U,
        &lab3_DW.HILInitialize_AIMinimums[0], &lab3_DW.HILInitialize_AIMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
        return;
      }
    }

    if ((lab3_P.HILInitialize_AOPStart && !is_switching) ||
        (lab3_P.HILInitialize_AOPEnter && is_switching)) {
      lab3_DW.HILInitialize_AOMinimums[0] = lab3_P.HILInitialize_AOLow;
      lab3_DW.HILInitialize_AOMinimums[1] = lab3_P.HILInitialize_AOLow;
      lab3_DW.HILInitialize_AOMaximums[0] = lab3_P.HILInitialize_AOHigh;
      lab3_DW.HILInitialize_AOMaximums[1] = lab3_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(lab3_DW.HILInitialize_Card,
        lab3_P.HILInitialize_AOChannels, 2U,
        &lab3_DW.HILInitialize_AOMinimums[0], &lab3_DW.HILInitialize_AOMaximums
        [0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
        return;
      }
    }

    if ((lab3_P.HILInitialize_AOStart && !is_switching) ||
        (lab3_P.HILInitialize_AOEnter && is_switching)) {
      lab3_DW.HILInitialize_AOVoltages[0] = lab3_P.HILInitialize_AOInitial;
      lab3_DW.HILInitialize_AOVoltages[1] = lab3_P.HILInitialize_AOInitial;
      result = hil_write_analog(lab3_DW.HILInitialize_Card,
        lab3_P.HILInitialize_AOChannels, 2U, &lab3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
        return;
      }
    }

    if (lab3_P.HILInitialize_AOReset) {
      lab3_DW.HILInitialize_AOVoltages[0] = lab3_P.HILInitialize_AOWatchdog;
      lab3_DW.HILInitialize_AOVoltages[1] = lab3_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (lab3_DW.HILInitialize_Card, lab3_P.HILInitialize_AOChannels, 2U,
         &lab3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
        return;
      }
    }

    if ((lab3_P.HILInitialize_EIPStart && !is_switching) ||
        (lab3_P.HILInitialize_EIPEnter && is_switching)) {
      lab3_DW.HILInitialize_QuadratureModes[0] =
        lab3_P.HILInitialize_EIQuadrature;
      lab3_DW.HILInitialize_QuadratureModes[1] =
        lab3_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode(lab3_DW.HILInitialize_Card,
        lab3_P.HILInitialize_EIChannels, 2U, (t_encoder_quadrature_mode *)
        &lab3_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
        return;
      }
    }

    if ((lab3_P.HILInitialize_EIStart && !is_switching) ||
        (lab3_P.HILInitialize_EIEnter && is_switching)) {
      lab3_DW.HILInitialize_InitialEICounts[0] = lab3_P.HILInitialize_EIInitial;
      lab3_DW.HILInitialize_InitialEICounts[1] = lab3_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(lab3_DW.HILInitialize_Card,
        lab3_P.HILInitialize_EIChannels, 2U,
        &lab3_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
        return;
      }
    }
  }

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  lab3_X.TransferFcn_CSTATE = 0.0;
}

/* Model terminate function */
void lab3_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: lab3/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(lab3_DW.HILInitialize_Card);
    hil_monitor_stop_all(lab3_DW.HILInitialize_Card);
    is_switching = false;
    if ((lab3_P.HILInitialize_AOTerminate && !is_switching) ||
        (lab3_P.HILInitialize_AOExit && is_switching)) {
      lab3_DW.HILInitialize_AOVoltages[0] = lab3_P.HILInitialize_AOFinal;
      lab3_DW.HILInitialize_AOVoltages[1] = lab3_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(lab3_DW.HILInitialize_Card,
        lab3_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &lab3_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(lab3_M, _rt_error_message);
      }
    }

    hil_task_delete_all(lab3_DW.HILInitialize_Card);
    hil_monitor_delete_all(lab3_DW.HILInitialize_Card);
    hil_close(lab3_DW.HILInitialize_Card);
    lab3_DW.HILInitialize_Card = NULL;
  }
}
