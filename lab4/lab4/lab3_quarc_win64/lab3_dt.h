/*
 * lab3_dt.h
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

#include "ext_types.h"

/* data type size table */
static uint_T rtDataTypeSizes[] = {
  sizeof(real_T),
  sizeof(real32_T),
  sizeof(int8_T),
  sizeof(uint8_T),
  sizeof(int16_T),
  sizeof(uint16_T),
  sizeof(int32_T),
  sizeof(uint32_T),
  sizeof(boolean_T),
  sizeof(fcn_call_T),
  sizeof(int_T),
  sizeof(pointer_T),
  sizeof(action_T),
  2*sizeof(uint32_T),
  sizeof(t_card)
};

/* data type name table */
static const char_T * rtDataTypeNames[] = {
  "real_T",
  "real32_T",
  "int8_T",
  "uint8_T",
  "int16_T",
  "uint16_T",
  "int32_T",
  "uint32_T",
  "boolean_T",
  "fcn_call_T",
  "int_T",
  "pointer_T",
  "action_T",
  "timer_uint32_pair_T",
  "t_card"
};

/* data type transitions for block I/O structure */
static DataTypeTransition rtBTransitions[] = {
  { (char_T *)(&lab3_B.Clock), 0, 0, 6 }
  ,

  { (char_T *)(&lab3_DW.HILInitialize_AIMinimums[0]), 0, 0, 12 },

  { (char_T *)(&lab3_DW.HILInitialize_Card), 14, 0, 1 },

  { (char_T *)(&lab3_DW.ToWorkspace2_PWORK.LoggedData), 11, 0, 5 },

  { (char_T *)(&lab3_DW.HILInitialize_ClockModes), 6, 0, 7 }
};

/* data type transition table for block I/O structure */
static DataTypeTransitionTable rtBTransTable = {
  5U,
  rtBTransitions
};

/* data type transitions for Parameters structure */
static DataTypeTransition rtPTransitions[] = {
  { (char_T *)(&lab3_P.HILInitialize_OOStart), 0, 0, 21 },

  { (char_T *)(&lab3_P.HILInitialize_CKChannels), 6, 0, 4 },

  { (char_T *)(&lab3_P.HILInitialize_AIChannels[0]), 7, 0, 10 },

  { (char_T *)(&lab3_P.HILInitialize_Active), 8, 0, 37 }
};

/* data type transition table for Parameters structure */
static DataTypeTransitionTable rtPTransTable = {
  4U,
  rtPTransitions
};

/* [EOF] lab3_dt.h */
