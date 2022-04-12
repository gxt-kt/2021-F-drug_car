#ifndef send_data__
#define send_data__
#include "sys.h"

typedef struct{
u8 gxt_chx;
s32 gxt_a;
s32 gxt_b;
s32 gxt_c;
s32 gxt_d;
s32 gxt_e;
s32 gxt_f;
s32 gxt_g;
s32 gxt_h;
s32 gxt_i;
s32 gxt_j;
}f_args;

#define f(...) var_f((f_args){__VA_ARGS__})

//extern u8 gxt_data_to_send[];其他地方也用不到这个数组，不用extern

#define BYTE0(dwTemp) (*((char *)(&dwTemp)))
#define BYTE1(dwTemp) (*((char *)(&dwTemp) + 1))
#define BYTE2(dwTemp) (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp) (*((char *)(&dwTemp) + 3))

void var_f(f_args in);
void gxt_v7_send(u16 v7_id,s32 v7_val);
void gxt_v7_send_check(u8 v7_id,u8 sc,u8 ac);
void gxt_senddata(u8 gxt_chx,s32 gxt_a,s32 gxt_b,s32 gxt_c,s32 gxt_d,s32 gxt_e,s32 gxt_f,s32 gxt_g,s32 gxt_h,s32 gxt_i,s32 gxt_j);
void UART1_Send_Str(u8 *s,u8 cnt_s);
void UART1_Send_Str(u8 *s,u8 cnt_s);
void Send_Quaternion(s16 gxt_a,s16 gxt_b,s16 gxt_c,s16 gxt_d,u8 ronghe);
void Send_LP_QY_TEMP(s16 gxt_a,s16 gxt_b,s16 gxt_c,s32 gxt_d,s16 gxt_e,u8 gxt_f,u8 gxt_g);
void Send_AX_GY(s16 gxt_a,s16 gxt_b,s16 gxt_c,s16 gxt_d,s16 gxt_e,s16 gxt_f,u8 gxt_g);
#endif //send_data__

