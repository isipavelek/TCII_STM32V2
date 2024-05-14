/*
===============================================================================
 Name        : ADCMSIS.c
 Author      : Israel Pavelek, Cesar Fuoco
 Version     : 2.0
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "filter.h"

#include <stdio.h>
#include <stdbool.h>
#include "arm_math.h"
#include "adc.h"
#include "dac_port.h"
#include "hw_init.h"

typedef enum{
	TALKTHROUGH,
	FIR,
	IIR,
}filter_type_t;

filter_type_t filter = TALKTHROUGH; //Función que ejecuta

extern procesar_type_t procesar;

//Estructuras
arm_fir_instance_f32 SFIR;
arm_biquad_casd_df1_inst_f32 SIIR;

//Variables de estado
float32_t fir_state[FIR_TAP_NUM+SAMPLES_PER_BLOCK-1];
float32_t iir_state[IIR_TAP_NUM+SAMPLES_PER_BLOCK-1];

//Ping Pong Buffers
float32_t InputA[SAMPLES_PER_BLOCK];
float32_t InputB[SAMPLES_PER_BLOCK];
float32_t OutputA[SAMPLES_PER_BLOCK];
float32_t OutputB[SAMPLES_PER_BLOCK];


int main(void){
	uint32_t index;
	float32_t max;
	Hard_Init();
	ADC_Init();
	DAC_Init();

	//Conversion float to q31
#ifndef float_filter
	arm_float_to_q31(float_fir_taps, fir_taps,FIR_TAP_NUM);
#endif

	arm_max_f32(float_iir_taps,IIR_TAP_NUM,&max,&index);

	if(max>=1)arm_scale_f32(float_iir_taps, ((float32_t)1/((1<<(uint32_t)max))),float_iir_taps,IIR_TAP_NUM );
	//arm_float_to_q31(float_iir_taps, iir_taps, IIR_TAP_NUM);

	//Inicializa los filtros
	//arm_fir_init_q31(&SFIR,FIR_TAP_NUM,fir_taps,fir_state,SAMPLES_PER_BLOCK);

	arm_fir_init(&SFIR,FIR_TAP_NUM,float_fir_taps,fir_state,SAMPLES_PER_BLOCK);
	arm_biquad_cascade_df1_init(&SIIR,IIR_TAP_NUM/5,float_iir_taps,iir_state);


	while(true){
		if(procesar){
			switch (filter){
				case TALKTHROUGH:
						for(uint16_t i=0;i<SAMPLES_PER_BLOCK;i++){
							if(procesar==PROCESAR_A)OutputA[i]=InputA[i];
							else OutputB[i]=InputB[i];
						}
						break;

				case IIR:
						if(procesar==PROCESAR_A){
							filter_bicuad_cascade(&SIIR, InputA, OutputA, SAMPLES_PER_BLOCK);
						}else {
							filter_bicuad_cascade(&SIIR, InputB, OutputB, SAMPLES_PER_BLOCK);
						}
						break;

				case FIR:
						if(procesar==PROCESAR_A){
							arm_fir(&SFIR,InputA, OutputA, SAMPLES_PER_BLOCK);
						}else {
							arm_fir(&SFIR,InputB, OutputB , SAMPLES_PER_BLOCK);
						}
						break;
			}
			procesar=NO_PROCESAR;
		}
	}
}

