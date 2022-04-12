#ifndef onefly_contorl_h__
#define onefly_contorl_h__
#include "sys.h"


extern u8 onefly_setup;
extern struct PID_wz onefly_pid;
void  onefly_pid_init(void);
s16 onefly_control(s16 pid_now,s16 pid_anti);

#endif //onefly_contorl_h__

