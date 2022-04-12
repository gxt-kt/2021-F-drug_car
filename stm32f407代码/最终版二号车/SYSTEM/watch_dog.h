#ifndef watch_dog_h__
#define watch_dog_h__			    
#include "sys.h" 

void IWDG_Init(u8 prer,u16 rlr);
void IWDG_Feed(void);

#endif //watch_dog_h__
















