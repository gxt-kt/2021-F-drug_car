#ifndef led_h__
#define led_h__
#include "sys.h"






#define LED0 PFout(9)	// DS0
#define LED1 PFout(10)	// DS1
#define MY_407_LED PCout(13)

#define digitalToggle(p,i) {p->ODR ^=i;}

#define LED0_TOG digitalToggle(GPIOF,GPIO_Pin_9)
#define LED1_TOG digitalToggle(GPIOF,GPIO_Pin_10)
#define MY_LED_407_TOG digitalToggle(GPIOC,GPIO_Pin_13)

void led_feikong_v1_rgb(void);
void led_f407_kaifaban(void);
void led_my_407(void);
#endif //led_h__

