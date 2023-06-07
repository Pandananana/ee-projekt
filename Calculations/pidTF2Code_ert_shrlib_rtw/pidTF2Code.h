/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pidTF2Code.h
 *
 * Code generated for Simulink model 'pidTF2Code'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Jun  8 00:50:13 2023
 *
 * Target selection: ert_shrlib.tlc
 * Embedded hardware selection: Atmel->AVR
 * Emulation hardware selection:
 *    Differs from embedded hardware (MATLAB Host)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_pidTF2Code_h_
#define RTW_HEADER_pidTF2Code_h_
#ifndef pidTF2Code_COMMON_INCLUDES_
#define pidTF2Code_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* pidTF2Code_COMMON_INCLUDES_ */

#include "pidTF2Code_types.h"
#include <string.h>

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  real_T DiscreteZeroPole_DSTATE[3];   /* '<Root>/Discrete Zero-Pole' */
} DW_pidTF2Code_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T indput;                       /* '<Root>/indput' */
} ExtU_pidTF2Code_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T output;                       /* '<Root>/output' */
} ExtY_pidTF2Code_T;

/* Real-time Model Data Structure */
struct tag_RTM_pidTF2Code_T {
  const char_T * volatile errorStatus;
};

/* Block states (default storage) */
extern DW_pidTF2Code_T pidTF2Code_DW;

/* External inputs (root inport signals with default storage) */
extern ExtU_pidTF2Code_T pidTF2Code_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_pidTF2Code_T pidTF2Code_Y;

/* Model entry point functions */
extern void pidTF2Code_initialize(void);
extern void pidTF2Code_step(void);
extern void pidTF2Code_terminate(void);

/* Real-time Model object */
extern RT_MODEL_pidTF2Code_T *const pidTF2Code_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'pidTF2Code'
 */
#endif                                 /* RTW_HEADER_pidTF2Code_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
