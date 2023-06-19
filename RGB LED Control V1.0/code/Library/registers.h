#ifndef REGISTERS_H_
#define REGISTERS_H_

#define GPIO_APB
#ifdef 	GPIO_APB
#define GPIO_OFFEST(x)	((x<4) ? ((0x40004000)+((x)*(0x1000))) : ((0x40024000)+ ((x-4)*(0x1000))))
#elif 	GPIO_AHB
#error "Not supported"
#else
#error "please select GPIO BUS"
#endif

//GPIO registers

#define GPIODATA(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x3FC)))
#define GPIODIR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x400)))
#define GPIOIS(x)			(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x404)))
#define GPIOIBE(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x408)))
#define GPIOIEV(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x40C)))
#define GPIOIM(x)			(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x410)))
#define GPIORIS(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x414)))
#define GPIOMIS(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x418)))
#define GPIOICR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x41C)))
#define GPIOAFSEL(x)	(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x420)))
#define GPIODR2R(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x500)))
#define GPIODR4R(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x504)))
#define GPIODR8R(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x508)))
#define GPIOODR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x50C)))
#define GPIOPUR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x510)))
#define GPIOPDR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x514)))
#define GPIOSLR(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x518)))
#define GPIODEN(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x51C)))
#define GPIOLOCK(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x520)))
#define GPIOCR(x)			(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x524)))
#define GPIOAMSEL(x)	(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x528)))
#define GPIOPCTL(x)		(*((volatile unsigned long *)(GPIO_OFFEST(x)+ 0x52C)))
	
#define RCGC2GPIO     (*((volatile unsigned long *)0x400FE108))

#endif /* REGISTERS_H_ */

