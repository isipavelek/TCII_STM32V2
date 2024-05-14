
/*
===============================================================================
 Name        : filter.h
 Author      : Israel Pavelek, Cesar Fuoco
 Version     : 1.2
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#ifndef INC_FILTER_H_
#define INC_FILTER_H_

#include <stdint.h>
#include "arm_math.h"

#define float_filter

#ifdef float_filter
#define arm_fir_init arm_fir_init_f32
#define arm_biquad_cascade_df1_init arm_biquad_cascade_df1_init_f32
#define filter_bicuad_cascade arm_biquad_cascade_df1_f32
#define arm_fir arm_fir_f32
#else
#define arm_fir_init arm_fir_init_q31
#define arm_biquad_cascade_df1_init arm_biquad_cascade_df1_init_q31
#define filter_bicuad_cascade arm_biquad_cascade_df1_q31
#define arm_fir arm_fir_q31
#endif


#define FIR_TAP_NUM 101
#define IIR_TAP_NUM 15

#define SAMPLES_PER_BLOCK 1024

extern int32_t fir_taps[];
extern int32_t iir_taps[];
extern float32_t float_fir_taps[];
extern float32_t float_iir_taps[];


typedef enum{
	NO_PROCESAR,
	PROCESAR_A,
	PROCESAR_B,

}procesar_type_t;



#endif /* INC_FILTER_H_ */
