/*
 * rcc.h
 *
 *  Created on: Oct 17, 2019
 *      Author: User
 */

#ifndef RCC_H_
#define RCC_H_

/*
 * #define	RCC	((RCC_ *)(this is RCC base address))
 */
#define	RCC	((RCC_reg *)(0x40023800))

typedef	struct	RCC_reg	RCC_reg;
struct RCC_reg{
	volatile	uint32_t	CR;			//0x00
	volatile	uint32_t	PLLCFGR;	//0x04
	volatile	uint32_t	CFGR;		//0x08
	volatile	uint32_t	CIR;		//0x0C
	volatile	uint32_t	AHB1RSTR;	//0x10
	volatile	uint32_t	AHB2RSTR;	//0x14
	volatile	uint32_t	AHB3RSTR;	//0x18
	volatile	uint32_t	Reserved1;	//0x1C
	volatile	uint32_t	APB1RSTR;	//0x20
	volatile	uint32_t	APB2RSTR;	//0x24
	volatile	uint32_t	Reserved2;	//0x28
	volatile	uint32_t	Reserved3;	//0x2C
	volatile	uint32_t	AHB1ENR;	//0x30
	volatile	uint32_t	AHB2ENR;	//0x34
	volatile	uint32_t	AHB3ENR;	//0x38
	volatile	uint32_t	Reserved4;	//0x3C
	volatile	uint32_t	APB1ENR;	//0x40
	volatile	uint32_t	APB2ENR;	//0x44
	volatile	uint32_t	Reserved5;	//0x48
	volatile	uint32_t	Reserved6;	//0x4C
	volatile	uint32_t	AHB1LPENR;	//0x50
	volatile	uint32_t	AHB2LPENR;	//0x54
	volatile	uint32_t	AHB3LPENR;	//0x58
	volatile	uint32_t	Reserved7;	//0x5C
	volatile	uint32_t	APB1LPENR;	//0x60
	volatile	uint32_t	APB2LPENR;	//0x64
	volatile	uint32_t	Reserved8;	//0x68
	volatile	uint32_t	Reserved9;	//0x6C
	volatile	uint32_t	BDCR;		//0x70
	volatile	uint32_t	CSR;		//0x74
	volatile	uint32_t	Reserved10;	//0x78
	volatile	uint32_t	Reserved11;	//0x7C
	volatile	uint32_t	SSCGR;		//0x80
	volatile	uint32_t	PLLI2SCFGR;	//0x84
	volatile	uint32_t	PLLSAICFGR;	//0x88
	volatile	uint32_t	DCKCFGR;	//0x8C
};

/*
 * RCC_APB1ENR
 */
#define	RCC_APB1ENR_TIM2EN		(1<<0)
#define	RCC_APB1ENR_TIM3EN		(1<<1)
#define	RCC_APB1ENR_TIM4EN		(1<<2)
#define	RCC_APB1ENR_TIM5EN		(1<<3)
#define	RCC_APB1ENR_TIM6EN		(1<<4)
#define	RCC_APB1ENR_TIM7EN		(1<<5)
#define	RCC_APB1ENR_TIM12EN		(1<<6)
#define	RCC_APB1ENR_TIM13EN		(1<<7)
#define	RCC_APB1ENR_TIM14EN		(1<<8)
#define	RCC_APB1ENR_WWDGEN		(1<<11)
#define	RCC_APB1ENR_SPI2EN		(1<<14)
#define	RCC_APB1ENR_SPI3EN		(1<<15)
#define	RCC_APB1ENR_USART2EN	(1<<17)
#define	RCC_APB1ENR_USART3EN	(1<<18)
#define	RCC_APB1ENR_UART4EN		(1<<19)
#define	RCC_APB1ENR_UART5EN		(1<<20)
#define	RCC_APB1ENR_I2C1EN		(1<<21)
#define	RCC_APB1ENR_I2C2EN		(1<<22)
#define	RCC_APB1ENR_I2C3EN		(1<<23)
#define	RCC_APB1ENR_CAN1EN		(1<<25)
#define	RCC_APB1ENR_CAN2EN		(1<<26)
#define	RCC_APB1ENR_PWREN		(1<<28)
#define	RCC_APB1ENR_DACEN		(1<<29)
#define	RCC_APB1ENR_UART7EN		(1<<30)
#define	RCC_APB1ENR_UART8EN		(1<<31)

/*
 * RCC_APB2ENR
 */
#define	RCC_APB2ENR_TIM1EN		(1<<0)
#define	RCC_APB2ENR_TIM8EN		(1<<1)
#define	RCC_APB2ENR_USART1EN	(1<<4)
#define	RCC_APB2ENR_USART6EN	(1<<5)
#define	RCC_APB2ENR_ADC1EN		(1<<8)
#define	RCC_APB2ENR_ADC2EN		(1<<9)
#define	RCC_APB2ENR_ADC3EN		(1<<10)
#define	RCC_APB2ENR_SDIOEN		(1<<11)
#define	RCC_APB2ENR_SPI1EN		(1<<12)
#define	RCC_APB2ENR_SPI4EN		(1<<13)
#define	RCC_APB2ENR_SYSCFGEN	(1<<14)
#define	RCC_APB2ENR_TIM9EN		(1<<16)
#define	RCC_APB2ENR_TIM10EN		(1<<17)
#define	RCC_APB2ENR_TIM11EN		(1<<18)
#define	RCC_APB2ENR_SPI5EN		(1<<20)
#define	RCC_APB2ENR_SPI6EN		(1<<21)
#define	RCC_APB2ENR_SAI1EN		(1<<22)
#define	RCC_APB2ENR_LTDCEN		(1<<26)

/*
 * RCC_APB1RSTR
 */
#define	RCC_APB1RSTR_TIM2RST		(1<<0)
#define	RCC_APB1RSTR_TIM3RST		(1<<1)
#define	RCC_APB1RSTR_TIM4RST		(1<<2)
#define	RCC_APB1RSTR_TIM5RST		(1<<3)
#define	RCC_APB1RSTR_TIM6RST		(1<<4)
#define	RCC_APB1RSTR_TIM7RST		(1<<5)
#define	RCC_APB1RSTR_TIM12RST		(1<<6)
#define	RCC_APB1RSTR_TIM13RST		(1<<7)
#define	RCC_APB1RSTR_TIM14RST		(1<<8)
#define	RCC_APB1RSTR_WWDGRST		(1<<11)
#define	RCC_APB1RSTR_SPI2RST		(1<<14)
#define	RCC_APB1RSTR_SPI3RST		(1<<15)
#define	RCC_APB1RSTR_UART2RST		(1<<17)
#define	RCC_APB1RSTR_UART3RST		(1<<18)
#define	RCC_APB1RSTR_UART4RST		(1<<19)
#define	RCC_APB1RSTR_UART5RST		(1<<20)
#define	RCC_APB1RSTR_I2C1RST		(1<<21)
#define	RCC_APB1RSTR_I2C2RST		(1<<22)
#define	RCC_APB1RSTR_I2C3RST		(1<<23)
#define	RCC_APB1RSTR_CAN1RST		(1<<25)
#define	RCC_APB1RSTR_CAN2RST		(1<<26)
#define	RCC_APB1RSTR_PWRRST			(1<<28)
#define	RCC_APB1RSTR_DACRST			(1<<29)
#define	RCC_APB1RSTR_UART7RST		(1<<30)
#define	RCC_APB1RSTR_UART8RST		(1<<31)


/*
 * RCC_APB2RSTR
 */
#define	RCC_APB2RSTR_TIM1RST		(1<<0)
#define	RCC_APB2RSTR_TIM8RST		(1<<1)
#define	RCC_APB2RSTR_USART1RST	(1<<4)
#define	RCC_APB2RSTR_USART6RST	(1<<5)
#define	RCC_APB2RSTR_ADCRST			(1<<8)
#define	RCC_APB2RSTR_SDIORST		(1<<11)
#define	RCC_APB2RSTR_SPI1RST		(1<<12)
#define	RCC_APB2RSTR_SP45RST		(1<<13)
#define	RCC_APB2RSTR_SYSCFGRST	(1<<14)
#define	RCC_APB2RSTR_TIM9RST		(1<<16)
#define	RCC_APB2RSTR_TIM10RST		(1<<17)
#define	RCC_APB2RSTR_TIM11RST		(1<<18)
#define	RCC_APB2RSTR_SPI5RST		(1<<20)
#define	RCC_APB2RSTR_SPI6RST		(1<<21)
#define	RCC_APB2RSTR_SAI1RST		(1<<22)
#define	RCC_APB2RSTR_LTDCRST		(1<<26)

/*
 * RCC_AHB1ENR
 */
#define	RCC_AHB1ENR_OTGHSULPIEN		(1<<30)
#define	RCC_AHB1ENR_OTGHSEN			(1<<29)
#define	RCC_AHB1ENR_ETHMACPTPEN		(1<<28)
#define	RCC_AHB1ENR_ETHMACRXEN		(1<<27)
#define	RCC_AHB1ENR_ETHMACTXEN		(1<<26)
#define	RCC_AHB1ENR_ETHMACEN		(1<<25)
#define	RCC_AHB1ENR_DMA2DEN			(1<<23)
#define	RCC_AHB1ENR_DMA2EN			(1<<22)
#define	RCC_AHB1ENR_DMA1EN			(1<<21)
#define	RCC_AHB1ENR_CCMDATARAMEN	(1<<20)
#define	RCC_AHB1ENR_BKPSRAMEN		(1<<18)
#define	RCC_AHB1ENR_CRCEN			(1<<12)
#define	RCC_AHB1ENR_GPIOKEN			(1<<10)
#define	RCC_AHB1ENR_GPIOJEN			(1<<9)
#define	RCC_AHB1ENR_GPIOIEN			(1<<8)
#define	RCC_AHB1ENR_GPIOHEN			(1<<7)
#define	RCC_AHB1ENR_GPIOGEN			(1<<6)
#define	RCC_AHB1ENR_GPIOFEN			(1<<5)
#define	RCC_AHB1ENR_GPIOEEN			(1<<4)
#define	RCC_AHB1ENR_GPIODEN			(1<<3)
#define	RCC_AHB1ENR_GPIOCEN			(1<<2)
#define	RCC_AHB1ENR_GPIOBEN			(1<<1)
#define	RCC_AHB1ENR_GPIOAEN			(1<<0)

/*
 * RCC_AHB1RSTR
 */
#define	RCC_AHB1RSTR_OTGHSRST			(1<<29)
#define	RCC_AHB1RSTR_ETHMACRST			(1<<25)
#define	RCC_AHB1RSTR_DMA2DRST			(1<<23)
#define	RCC_AHB1RSTR_DMA2RST			(1<<22)
#define	RCC_AHB1RSTR_DMA1RST			(1<<21)
#define	RCC_AHB1RSTR_CRCRST				(1<<12)
#define	RCC_AHB1RSTR_GPIOKRST			(1<<10)
#define	RCC_AHB1RSTR_GPIOJRST			(1<<9)
#define	RCC_AHB1RSTR_GPIOIRST			(1<<8)
#define	RCC_AHB1RSTR_GPIOHRST			(1<<7)
#define	RCC_AHB1RSTR_GPIOGRST			(1<<6)
#define	RCC_AHB1RSTR_GPIOFRST			(1<<5)
#define	RCC_AHB1RSTR_GPIOERST			(1<<4)
#define	RCC_AHB1RSTR_GPIODRST			(1<<3)
#define	RCC_AHB1RSTR_GPIOCRST			(1<<2)
#define	RCC_AHB1RSTR_GPIOBRST			(1<<1)
#define	RCC_AHB1RSTR_GPIOARST			(1<<0)


#endif /* RCC_H_ */
