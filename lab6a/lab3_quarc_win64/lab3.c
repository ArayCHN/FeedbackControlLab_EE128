/*
 * lab3.c
 *
 * Code generation for model "lab3".
 *
 * Model version              : 1.15
 * Simulink Coder version : 8.5 (R2013b) 08-Aug-2013
 * C source code generated on : Wed Nov 01 17:08:08 2017
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

/* Block states (auto storage) */
DW_lab3_T lab3_DW;

/* Real-time model */
RT_MODEL_lab3_T lab3_M_;
RT_MODEL_lab3_T *const lab3_M = &lab3_M_;

/* Model step function */
void lab3_step(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoder_o1;
  real_T rtb_HILReadEncoder_o2;

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
      rtb_HILReadEncoder_o1 = lab3_DW.HILReadEncoder_Buffer[0];
      rtb_HILReadEncoder_o2 = lab3_DW.HILReadEncoder_Buffer[1];
    }
  }

  /* Gain: '<Root>/Gain1' */
  lab3_B.Gain1 = lab3_P.Gain1_Gain * rtb_HILReadEncoder_o1;

  /* Sin: '<Root>/Sine Wave' */
  lab3_B.SineWave = sin(lab3_P.SineWave_Freq * lab3_M->Timing.t[0] +
                        lab3_P.SineWave_Phase) * lab3_P.SineWave_Amp +
    lab3_P.SineWave_Bias;

  /* Derivative: '<Root>/Derivative1' */
  {
    real_T t = lab3_M->Timing.t[0];
    real_T timeStampA = lab3_DW.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = lab3_DW.Derivative1_RWORK.TimeStampB;
    real_T *lastU = &lab3_DW.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      lab3_B.Derivative1 = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &lab3_DW.Derivative1_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &lab3_DW.Derivative1_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      lab3_B.Derivative1 = (lab3_B.Gain1 - *lastU++) / deltaT;
    }
  }

  /* Gain: '<Root>/Gain3' */
  lab3_B.Gain3 = lab3_P.Gain3_Gain * rtb_HILReadEncoder_o2;

  /* Derivative: '<Root>/Derivative' */
  {
    real_T t = lab3_M->Timing.t[0];
    real_T timeStampA = lab3_DW.Derivative_RWORK.TimeStampA;
    real_T timeStampB = lab3_DW.Derivative_RWORK.TimeStampB;
    real_T *lastU = &lab3_DW.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      lab3_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &lab3_DW.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &lab3_DW.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      lab3_B.Derivative = (lab3_B.Gain3 - *lastU++) / deltaT;
    }
  }

  /* Gain: '<Root>/Gain2' incorporates:
   *  Constant: '<Root>/Constant'
   *  Sum: '<Root>/Sum'
   */
  lab3_B.Gain2 = (((lab3_B.SineWave - lab3_B.Gain1) * lab3_P.Gain2_Gain[0] +
                   (lab3_P.Constant_Value[0] - lab3_B.Derivative1) *
                   lab3_P.Gain2_Gain[1]) + (lab3_P.Constant_Value[1] -
    lab3_B.Gain3) * lab3_P.Gain2_Gain[2]) + (lab3_P.Constant_Value[2] -
    lab3_B.Derivative) * lab3_P.Gain2_Gain[3];

  /* Saturate: '<Root>/Saturation' */
  if (lab3_B.Gain2 >= lab3_P.Saturation_UpperSat) {
    lab3_B.Saturation = lab3_P.Saturation_UpperSat;
  } else if (lab3_B.Gain2 <= lab3_P.Saturation_LowerSat) {
    lab3_B.Saturation = lab3_P.Saturation_LowerSat;
  } else {
    lab3_B.Saturation = lab3_B.Gain2;
  }

  /* End of Saturate: '<Root>/Saturation' */

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

  /* SignalConversion: '<Root>/TmpSignal ConversionAtTo Workspace1Inport1' */
  lab3_B.TmpSignalConversionAtToWorkspac[0] = lab3_B.Gain1;
  lab3_B.TmpSignalConversionAtToWorkspac[1] = lab3_B.Derivative1;
  lab3_B.TmpSignalConversionAtToWorkspac[2] = lab3_B.Gain3;
  lab3_B.TmpSignalConversionAtToWorkspac[3] = lab3_B.Derivative;

  /* Clock: '<Root>/Clock' */
  lab3_B.Clock = lab3_M->Timing.t[0];

  /* Update for Derivative: '<Root>/Derivative1' */
  {
    real_T timeStampA = lab3_DW.Derivative1_RWORK.TimeStampA;
    real_T timeStampB = lab3_DW.Derivative1_RWORK.TimeStampB;
    real_T* lastTime = &lab3_DW.Derivative1_RWORK.TimeStampA;
    real_T* lastU = &lab3_DW.Derivative1_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &lab3_DW.Derivative1_RWORK.TimeStampB;
        lastU = &lab3_DW.Derivative1_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &lab3_DW.Derivative1_RWORK.TimeStampB;
        lastU = &lab3_DW.Derivative1_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = lab3_M->Timing.t[0];
    *lastU++ = lab3_B.Gain1;
  }

  /* Update for Derivative: '<Root>/Derivative' */
  {
    real_T timeStampA = lab3_DW.Derivative_RWORK.TimeStampA;
    real_T timeStampB = lab3_DW.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &lab3_DW.Derivative_RWORK.TimeStampA;
    real_T* lastU = &lab3_DW.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &lab3_DW.Derivative_RWORK.TimeStampB;
        lastU = &lab3_DW.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &lab3_DW.Derivative_RWORK.TimeStampB;
        lastU = &lab3_DW.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = lab3_M->Timing.t[0];
    *lastU++ = lab3_B.Gain3;
  }

  /* External mode */
  rtExtModeUploadCheckTrigger(2);

  {                                    /* Sample time: [0.0s, 0.0s] */
    rtExtModeUpload(0, lab3_M->Timing.t[0]);
  }

  {                                    /* Sample time: [0.002s, 0.0s] */
    rtExtModeUpload(1, (((lab3_M->Timing.clockTick1+lab3_M->Timing.clockTickH1*
                          4294967296.0)) * 0.002));
  }

  /* signal main to stop simulation */
  {                                    /* Sample time: [0.0s, 0.0s] */
    if ((rtmGetTFinal(lab3_M)!=-1) &&
        !((rtmGetTFinal(lab3_M)-lab3_M->Timing.t[0]) > lab3_M->Timing.t[0] *
          (DBL_EPSILON))) {
      rtmSetErrorStatus(lab3_M, "Simulation finished");
    }

    if (rtmGetStopRequested(lab3_M)) {
      rtmSetErrorStatus(lab3_M, "Simulation finished");
    }
  }

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

  lab3_M->Timing.t[0] = lab3_M->Timing.clockTick0 * lab3_M->Timing.stepSize0 +
    lab3_M->Timing.clockTickH0 * lab3_M->Timing.stepSize0 * 4294967296.0;

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
}

/* Model initialize function */
void lab3_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)lab3_M, 0,
                sizeof(RT_MODEL_lab3_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&lab3_M->solverInfo, &lab3_M->Timing.simTimeStep);
    rtsiSetTPtr(&lab3_M->solverInfo, &rtmGetTPtr(lab3_M));
    rtsiSetStepSizePtr(&lab3_M->solverInfo, &lab3_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&lab3_M->solverInfo, (&rtmGetErrorStatus(lab3_M)));
    rtsiSetRTModelPtr(&lab3_M->solverInfo, lab3_M);
  }

  rtsiSetSimTimeStep(&lab3_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&lab3_M->solverInfo,"FixedStepDiscrete");
  rtmSetTPtr(lab3_M, &lab3_M->Timing.tArray[0]);
  rtmSetTFinal(lab3_M, 15.0);
  lab3_M->Timing.stepSize0 = 0.002;

  /* External mode info */
  lab3_M->Sizes.checksums[0] = (1072206320U);
  lab3_M->Sizes.checksums[1] = (840342507U);
  lab3_M->Sizes.checksums[2] = (2945066307U);
  lab3_M->Sizes.checksums[3] = (1835344712U);

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

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  lab3_DW.Derivative1_RWORK.TimeStampA = rtInf;
  lab3_DW.Derivative1_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  lab3_DW.Derivative_RWORK.TimeStampA = rtInf;
  lab3_DW.Derivative_RWORK.TimeStampB = rtInf;
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
