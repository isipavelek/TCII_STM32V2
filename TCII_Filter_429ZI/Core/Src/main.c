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
#include "uart_port.h"
#include "uart.h"

filter_type_t filter = TALKTHROUGH; //Función que ejecuta

extern estado_t estado;

//Estructuras
arm_fir_instance_f32 SFIR;
arm_biquad_casd_df1_inst_f32 SIIR;

//Variables de estado
float32_t fir_state[FIR_TAP_NUM+SAMPLES_PER_BLOCK-1];
float32_t iir_state[IIR_TAP_NUM+SAMPLES_PER_BLOCK-1];

//Ping Pong Buffers
float32_t InputA[SAMPLES_PER_BLOCK]={0};
float32_t InputB[SAMPLES_PER_BLOCK]={0};
float32_t OutputA[SAMPLES_PER_BLOCK]={0};
float32_t OutputB[SAMPLES_PER_BLOCK]={0};
extern UART_HandleTypeDef huart3;

int main(void){

	Hard_Init();
	ADC_Init();
	DAC_Init();

	//Conversion float to q31
#ifndef float_filter
	arm_float_to_q31(float_fir_taps, fir_taps,FIR_TAP_NUM);
#endif

	//arm_max_f32(float_iir_taps,IIR_TAP_NUM,&max,&index);

	//if(max>=1)arm_scale_f32(float_iir_taps, ((float32_t)1/((1<<(uint32_t)max))),float_iir_taps,IIR_TAP_NUM );
	//arm_float_to_q31(float_iir_taps, iir_taps, IIR_TAP_NUM);

	//Inicializa los filtros
	//arm_fir_init_q31(&SFIR,FIR_TAP_NUM,fir_taps,fir_state,SAMPLES_PER_BLOCK);

	arm_fir_init_f32(&SFIR,FIR_TAP_NUM,float_fir_taps,fir_state,SAMPLES_PER_BLOCK);
//	arm_biquad_cascade_df1_init_f32(&SIIR,IIR_TAP_NUM/5,float_iir_taps,iir_state);
	arm_biquad_cascade_df1_init_f32(&SIIR,IIR_TAP_NUM,float_iir_taps,iir_state);

	UART_Menu();
	UART_Receive_IT_init();

	while(true){

		if(estado!=NO_PROCESAR){
			switch (filter){
				case TALKTHROUGH:
						for(uint16_t i=0;i<SAMPLES_PER_BLOCK;i++){
							if(estado==PROCESAR_A)OutputA[i]=InputA[i];
							else OutputB[i]=InputB[i];
						}
						break;

				case IIR:
						if(estado==PROCESAR_A){
							arm_biquad_cascade_df1_f32(&SIIR, InputA, OutputA, SAMPLES_PER_BLOCK);
						}else {
							arm_biquad_cascade_df1_f32(&SIIR, InputB, OutputB, SAMPLES_PER_BLOCK);
						}
						break;

				case FIR:
						if(estado==PROCESAR_A){
							arm_fir_f32(&SFIR,InputA, OutputA, SAMPLES_PER_BLOCK);
						}else {
							arm_fir_f32(&SFIR,InputB, OutputB , SAMPLES_PER_BLOCK);
						}
				default:break;

			}
			estado=NO_PROCESAR;
		}
	}
}



