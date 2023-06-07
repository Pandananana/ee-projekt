/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: pidTF2Code.c
 *
 * Code generated for Simulink model 'pidTF2Code'.
 *
 * Model version                  : 1.4
 * Simulink Coder version         : 9.9 (R2023a) 19-Nov-2022
 * C/C++ source code generated on : Thu Jun  8 00:46:47 2023
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Atmel->AVR
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "pidTF2Code.h"

/* Block states (default storage) */
DW_pidTF2Code_T pidTF2Code_DW;

/* External inputs (root inport signals with default storage) */
ExtU_pidTF2Code_T pidTF2Code_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_pidTF2Code_T pidTF2Code_Y;

/* Real-time model */
static RT_MODEL_pidTF2Code_T pidTF2Code_M_;
RT_MODEL_pidTF2Code_T *const pidTF2Code_M = &pidTF2Code_M_;

/* Model step function */
void pidTF2Code_step(void)
{
  /* DiscreteZeroPole: '<Root>/Discrete Zero-Pole' incorporates:
   *  Inport: '<Root>/indput'
   *  Outport: '<Root>/output'
   */
  {
    pidTF2Code_Y.output = (pidTF2Code_P.DiscreteZeroPole_C[0])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[0]
      + (pidTF2Code_P.DiscreteZeroPole_C[1])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[1]
      + (pidTF2Code_P.DiscreteZeroPole_C[2])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[2];
    pidTF2Code_Y.output += pidTF2Code_P.DiscreteZeroPole_D*pidTF2Code_U.indput;
  }

  /* Update for DiscreteZeroPole: '<Root>/Discrete Zero-Pole' incorporates:
   *  Inport: '<Root>/indput'
   *  Outport: '<Root>/output'
   */
  {
    real_T xnew[3];
    xnew[0] = (pidTF2Code_P.DiscreteZeroPole_A[0])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[0];
    xnew[0] += (pidTF2Code_P.DiscreteZeroPole_B[0])*pidTF2Code_U.indput;
    xnew[1] = (pidTF2Code_P.DiscreteZeroPole_A[1])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[0]
      + (pidTF2Code_P.DiscreteZeroPole_A[2])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[1]
      + (pidTF2Code_P.DiscreteZeroPole_A[3])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[2];
    xnew[1] += (pidTF2Code_P.DiscreteZeroPole_B[1])*pidTF2Code_U.indput;
    xnew[2] = (pidTF2Code_P.DiscreteZeroPole_A[4])*
      pidTF2Code_DW.DiscreteZeroPole_DSTATE[1];
    (void) memcpy(&pidTF2Code_DW.DiscreteZeroPole_DSTATE[0], xnew,
                  sizeof(real_T)*3);
  }
}

/* Model initialize function */
void pidTF2Code_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void pidTF2Code_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
