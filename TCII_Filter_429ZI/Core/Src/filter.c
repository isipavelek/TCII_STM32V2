/*
 * filter.c
 *
 *  Created on: May 13, 2024
 *      Author: ipave
 */



#include "filter.h"
#include "arm_math.h"
#include <stdint.h>

int32_t fir_taps[FIR_TAP_NUM] = {0};
float32_t float_fir_taps[FIR_TAP_NUM] = {0.221389,0.034399,0.035922,0.036731,0.036731,0.035922,0.034399,0.221389};
int32_t iir_taps[IIR_TAP_NUM] = {0};
float32_t float_iir_taps[IIR_TAP_NUM] = {0};

