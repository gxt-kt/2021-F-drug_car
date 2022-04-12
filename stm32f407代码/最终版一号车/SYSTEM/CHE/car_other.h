#ifndef car_other__
#define car_other__
#include "sys.h"

extern int SPEED_1;
extern int SPEED_2;
void SPEED_GET(void);

void CAR_TURN_LEFT(void);
void CAR_TURN_RIGHT(void);
void CAR_SPEED_SET(int left,int right);
void CAR_left(void);
void CAR_right(void);
void CAR_back(void);
void CAR_front(void);
int MY_abs(int a);
void CAR_STOP(void);

#endif //car_other__

