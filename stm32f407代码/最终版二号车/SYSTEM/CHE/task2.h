#ifndef task_h__
#define task_h__
#include "sys.h"
#define sp_zw 28
extern u8 t2dir;
extern u8 send_num;
extern u8 leave_flag;

#define HUNG (500)
extern int ttt;
void TASK2_GO(void);
void CAR_xunji_2(void);


#endif //task_h__

