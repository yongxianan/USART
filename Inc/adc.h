/*
 * adc.h
 *
 *  Created on: Dec 4, 2019
 *      Author: User
 */

#ifndef ADC_H_
#define ADC_H_

#include <stdint.h>

typedef	struct	ADCx	ADCx;
struct ADCx{
	volatile	uint32_t	SR;			//0x00
	volatile	uint32_t	CR1;		//0x04
	volatile	uint32_t	CR2;		//0x08
	volatile	uint32_t	SMPR1;		//0x0C
	volatile	uint32_t	SMPR2;		//0x10
	volatile	uint32_t	JOFR1;		//0x14
	volatile	uint32_t	JOFR2;		//0x18
	volatile	uint32_t	JOFR3;		//0x1C
	volatile	uint32_t	JOFR4;		//0x20
	volatile	uint32_t	HTR;		//0x24
	volatile	uint32_t	LTR;		//0x28
	volatile	uint32_t	SQR1;		//0x2C
	volatile	uint32_t	SQR2;		//0x30
	volatile	uint32_t	SQR3;		//0x34
	volatile	uint32_t	JSQR;	//0x38
	volatile	uint32_t	JDR1;	//0x3C
	volatile	uint32_t	JDR2;	//0x40
	volatile	uint32_t	JDR3;	//0x44
	volatile	uint32_t	JDR4;	//0x48
	volatile	uint32_t	DR;	//0x4C
};



typedef	struct	commonADC	commonADC;
struct commonADC{
	volatile	uint32_t	CSR;			//0x00
	volatile	uint32_t	CCR;		//0x04
	volatile	uint32_t	CDR;		//0x08
};

typedef enum{
	_3_CYCLES,
	_15_CYCLES,
	_28_CYCLES,
	_56_CYCLES,
	_84_CYCLES,
	_112_CYCLES,
	_144_CYCLES,
	_480_CYCLES,
}SamplingTime;

typedef enum{
	channel_5,
	channel_13,
}CHState;

#define	ADC1	((ADCx *)(0x40012000))
#define	ADC2	((ADCx *)(0x40012100))
#define	ADC3	((ADCx *)(0x40012200))
#define CommonADC	((commonADC *)(0x40012300))


/*
 * ADC_SR_
 */
#define ADC_SR_OVR			(1<<5)
#define ADC_SR_STRT			(1<<4)
#define ADC_SR_JSTRT		(1<<3)
#define ADC_SR_JEOC			(1<<2)
#define ADC_SR_EOC			(1<<1)
#define ADC_SR_AWD			(1<<0)


/*
 * ADC_CR1_
 */
#define ADC_CR1_OVRIE		(1<<26)

#define ADC_CR1_RES_12		(0<<24)
#define ADC_CR1_RES_10		(1<<24)
#define ADC_CR1_RES_8		(2<<24)
#define ADC_CR1_RES_6		(3<<24)

#define ADC_CR1_AWDEN		(1<<23)
#define ADC_CR1_JAWDEN		(1<<22)

#define ADC_CR1_DISCNUM_CH1		(0<<13)
#define ADC_CR1_DISCNUM_CH2		(1<<13)
#define ADC_CR1_DISCNUM_CH3		(2<<13)
#define ADC_CR1_DISCNUM_CH4		(3<<13)
#define ADC_CR1_DISCNUM_CH5		(4<<13)
#define ADC_CR1_DISCNUM_CH6		(5<<13)
#define ADC_CR1_DISCNUM_CH7		(6<<13)
#define ADC_CR1_DISCNUM_CH8		(7<<13)

#define ADC_CR1_JDISCEN		(1<<12)
#define ADC_CR1_DISCEN		(1<<11)
#define ADC_CR1_JAUTO		(1<<10)
#define ADC_CR1_AWDSGL		(1<<9)
#define ADC_CR1_SCAN		(1<<8)
#define ADC_CR1_JEOCIE		(1<<7)
#define ADC_CR1_AWDIE		(1<<6)
#define ADC_CR1_EOCIE		(1<<5)

#define ADC_CR1_AWDCH_CH0		(0<<0)
#define ADC_CR1_AWDCH_CH1		(1<<0)
#define ADC_CR1_AWDCH_CH2		(2<<0)
#define ADC_CR1_AWDCH_CH3		(3<<0)
#define ADC_CR1_AWDCH_CH4		(4<<0)
#define ADC_CR1_AWDCH_CH5		(5<<0)
#define ADC_CR1_AWDCH_CH6		(6<<0)
#define ADC_CR1_AWDCH_CH7		(7<<0)
#define ADC_CR1_AWDCH_CH8		(8<<0)
#define ADC_CR1_AWDCH_CH9		(9<<0)
#define ADC_CR1_AWDCH_CH10		(10<<0)
#define ADC_CR1_AWDCH_CH11		(11<<0)
#define ADC_CR1_AWDCH_CH12		(12<<0)
#define ADC_CR1_AWDCH_CH13		(13<<0)
#define ADC_CR1_AWDCH_CH14		(14<<0)
#define ADC_CR1_AWDCH_CH15		(15<<0)
#define ADC_CR1_AWDCH_CH16		(16<<0)
#define ADC_CR1_AWDCH_CH17		(17<<0)
#define ADC_CR1_AWDCH_CH18		(18<<0)

/*
 * ADC_CR2_
 */
#define ADC_CR2_SWSTART				(1ULL<<(32+30))

#define ADC_CR2_EXTEN_DISABLE		(1ULL<<(32+28))
#define ADC_CR2_EXTEN_RISING_EDGE	(1ULL<<(32+28))
#define ADC_CR2_EXTEN_FALLING_EDGE	(1ULL<<(32+28))
#define ADC_CR2_EXTEN_BOTH_EDGE		(1ULL<<(32+28))

#define ADC_CR2_EXTSEL_TIMER1_CC1	(0ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER1_CC2	(1ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER1_CC3	(2ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER2_CC2	(3ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER2_CC3	(4ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER2_CC4	(5ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER2_TRGO	(6ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER3_CC1	(7ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER3_TRGO	(8ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER4_CC4	(9ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER5_CC1	(10ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER5_CC2	(11ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER5_CC3	(12ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER8_CC1	(13ULL<<(32+24))
#define ADC_CR2_EXTSEL_TIMER8_TRGO	(14ULL<<(32+24))
#define ADC_CR2_EXTSEL_EXTI_11		(15ULL<<(32+24))

#define ADC_CR2_JSWSTART			(1ULL<<(32+22))

#define ADC_CR2_JEXTEN_DISABLE		(1ULL<<(32+20))
#define ADC_CR2_JEXTEN_RISING_EDGE	(1ULL<<(32+20))
#define ADC_CR2_JEXTEN_FALLING_EDGE	(1ULL<<(32+20))
#define ADC_CR2_JEXTEN_BOTH_EDGE	(1ULL<<(32+20))

#define ADC_CR2_EXTSEL_TIMER1_CC4	(0ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER1_TRGO	(1ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER2_CC1	(2ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER2_TRGO	(3ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER3_CC2	(4ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER3_CC4	(5ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER4_CC1	(6ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER4_CC2	(7ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER4_CC3	(8ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER4_TRGO	(9ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER5_CC4	(10ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER5_TRGO	(11ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER8_CC2	(12ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER8_CC3	(13ULL<<(32+16))
#define ADC_CR2_EXTSEL_TIMER8_CC4	(14ULL<<(32+16))
#define ADC_CR2_EXTSEL_EXTI_15		(15ULL<<(32+16))

#define ADC_CR2_LEFT_ALIGN			(1ULL<<(32+11))
#define ADC_CR2_EOCS				(1ULL<<(32+10))
#define ADC_CR2_DDS					(1ULL<<(32+9))
#define ADC_CR2_DMA					(1ULL<<(32+8))
#define ADC_CR2_CONT				(1ULL<<(32+1))
#define ADC_CR2_ADON				(1ULL<<(32+0))

/*
 * ADC_CCR_
 */
#define ADC_CCR_TSVREFE				(1<<23)

#endif /* ADC_H_ */
