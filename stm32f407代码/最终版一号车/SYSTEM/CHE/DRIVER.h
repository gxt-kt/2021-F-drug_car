#ifndef DRIVER_H__
#define DRIVER_H__
#include "sys.h"

void CAR_Driver_Init(void);
void RGB_EN(u8 a);
void CAR_KAIGUAN_INIT(void);

#define GREEN_PIN 15
#define RED_PIN 14
#define BLUE_PIN 13

#define GREEN_EN {PBout(GREEN_PIN)=1;}
#define GREEN_DIS {PBout(GREEN_PIN)=0;}
#define RED_EN {PBout(RED_PIN)=1;}
#define RED_DIS {PBout(RED_PIN)=0;}
#define BLUE_EN {PBout(BLUE_PIN)=1;}
#define BLUE_DIS {PBout(BLUE_PIN)=0;}

#define RED 1
#define DARK 2
#define YELLOW 3
#define GREEN 4
#define WHITE 5
#define BLUE 6
#define PURPLE 7
#define CYAN 8

#endif //DRIVER_H__

