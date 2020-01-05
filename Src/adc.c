/*
 * adc.c
 *
 *  Created on: Dec 4, 2019
 *      Author: User
 */

#include "adc.h"

void adcConfig(ADCx *ADC, uint64_t CR){
	ADC->CR2 |= (uint32_t)(0xFFFFFFFF & (CR>>32));
	ADC->CR1 |= (uint32_t)(0xFFFFFFFF & CR);
}

void adcSamplingTime(ADCx *ADC,int channel,SamplingTime samplingTime){
	if(channel<=9 && channel>=0){
		ADC->SMPR2 &= ~(7<<(channel*3));
		ADC->SMPR2 |= (samplingTime<<(channel*3));
	}
	else if(channel>9 && channel<=18){
		ADC->SMPR1 &= ~(7<<((channel-9)*3));
		ADC->SMPR1 |= (samplingTime<<((channel-9)*3));
	}
	else{
	}
}

void adcSetChannelSequence(ADCx *ADC,uint32_t *channelList){
	int i=0;
	for(i=0;*(channelList+i) !=-1;i++){
		if(i<=5){
			ADC->SQR3 &= ~(31<<(i*5));
			ADC->SQR3 |= (*(channelList+i)<<(i*5));
		}
		else if(i<=11 && i>=6){
			ADC->SQR2 &= ~(31<<(i*5));
			ADC->SQR2 |= (*(channelList+i)<<(i*5));
		}
		else if(i<=15 && i>=12){
			ADC->SQR1 &= ~(31<<(i*5));
			ADC->SQR1 |= (*(channelList+i)<<(i*5));
		}
	}
	ADC->SQR1 &= ~(15<<20);
	ADC->SQR1 |= ((i-1)<<20);
}

void adcSetChannelInjectSequence(ADCx *ADC,unsigned int *channelList){
	int i=0;
	for(i=0;channelList[i]!=-1;i++){
		ADC->JSQR &= ~(31<<(i*5));
		ADC->JSQR |= (channelList[i]<<(i*5));
	}
	ADC->SQR1 &= ~(3<<20);
	ADC->SQR1 |= ((i-1)<<20);
}
