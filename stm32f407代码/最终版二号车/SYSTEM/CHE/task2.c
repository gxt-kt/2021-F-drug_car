#include "task2.h"

u8 t2dir=0;
u8 send_num=0;
u8 leave_flag=0;
int ttt=0;
void 	TASK2_GO(void)
{
	static u8 t;
	while(detect_num==0)
	{
		sprintf(sss,"de-%d",detect_num);
		OLED_ShowString(0,3,sss,16);
		RGB_EN(WHITE);
		delay_ms(1000);
	}
	sprintf(sss,"de-%d",detect_num);
		OLED_ShowString(0,3,sss,16);
	RGB_EN(DARK);
	//扫描色块结束
	while(1)
	{
		if(PAin(5)==0) {delay_ms(300);flag_go=1;break;}
		delay_ms(50);
	}
	
	while(1)
	{
		static u8 first=0;
		/*框架开始*/
		if(flag_go==1)
		{
			if(return_sta==1)
			{
				if(board==1&&time_up==0)
				{
					static u8 sta_sta;
					sta_sta=sta_num[--sta_i];
					if(sta_sta==1) {MOTOR_ANTI(sp_zw,0);delay_ms(youzhuan);board=0;ttt=HUNG;}
					else if(sta_sta==3) {MOTOR_ANTI(0,sp_zw);delay_ms(zuozhuan);board=0;ttt=HUNG;}
					else if(sta_sta==2) {;}
				}
				CAR_xunji_2();
			}
			else
			{
			if(first==0){count_go=1;first=1;}
			if(board==1&&time_up==0&&(detect_num==1||detect_num==2))
			{
				if(detect_num==1){MOTOR_ANTI(0,sp_zw);delay_ms(zuozhuan);board=0;ttt=HUNG;sta_num[sta_i++]=1;}
				else if(detect_num==2){MOTOR_ANTI(sp_zw,0);delay_ms(youzhuan);board=0;ttt=HUNG;sta_num[sta_i++]=3;}
			}
			if(board==1&&time_up==0&&(detect_num!=1&&detect_num!=2))
			{
				count_go=0;
				find_MAX(1);
				find_MAX(2);
				if( val1_cnt < 5)find_val1=0;
				if( val2_cnt < 5)find_val2=0;
				if( val3_cnt < 5)find_val3=0;
				if( val4_cnt < 5)find_val4=0;
				for(t=1;t<=8;t++) k210_cnt_l[t]=0;
				for(t=1;t<=8;t++) k210_cnt_r[t]=0;
				sprintf(sss,"val:%d-%d-%d-%d",find_val1,find_val2,find_val3,find_val4);
				OLED_ShowString(0,2,sss,16);
				sprintf(sss,"cnt:%d-%d-%d-%d",val1_cnt,val2_cnt,val3_cnt,val4_cnt);
				OLED_ShowString(0,4,sss,16);
				if(find_val1==detect_num || find_val2==detect_num){t2dir=1;send_num=find_val3;MOTOR_ANTI(0,sp_zw);delay_ms(zuozhuan);ttt=HUNG;sta_num[sta_i++]=1;count_go=1;}
				else if(find_val3==detect_num || find_val4==detect_num){t2dir=2;send_num=find_val1;MOTOR_ANTI(sp_zw,0);delay_ms(youzhuan);ttt=HUNG;sta_num[sta_i++]=3;count_go=1;}
				else {count_go=1;}
				board=0;
			}
			CAR_xunji_2();
			}
		}
		else
		{
			CAR_STOP();
			flag_go=0;
		}
		delay_ms(18);
	}
}

void CAR_xunji_2(void)
{
	static u8 jinru=0;
static int iiii;
		if(openmvdata[0])
		{
				int error = openmvdata[0] - 160;
				vel = error* Kp_qwq;
				if(vel>10) vel = 10;
				if(vel<-10) vel = -10;
				Speed1 = Speed + vel;
				Speed2 = Speed - vel;
				MOTOR_ANTI(Speed1,Speed2);
			//MOTOR_ANTI(0,0);
		}
		else if(openmvdata[0]==0&&black_num>=3)
		{
			if(car_task==3) {delay_ms(400);CAR_STOP();RGB_EN(RED);while(1);};
			if(jinru==1){delay_ms(400);CAR_STOP();RGB_EN(RED);while(1);}
			if(return_sta==1) {
				delay_ms(200);
			//RGB_EN(GREEN);
			CAR_STOP();while(1);
			}
			delay_ms(400);
			RGB_EN(YELLOW);
			CAR_STOP();
			
			while(leave_flag==0)
			{
				
				sprintf(sss,"leav%d",iiii++);
				OLED_ShowString(0,5,sss,16);
				delay_ms(20);
			}
			sprintf(sss,"leav%d",leave_flag);
				OLED_ShowString(0,5,sss,16);
			//RGB_EN(GREEN);

			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			delay_ms(1000);
			MOTOR_ANTI(SD_180,-SD_180);
			delay_ms(ZW_180);
			ttt=40000;
			jinru=1;
//		while(1)
//		{
//			if(PAin(5)==1) {
//				u2_send[3]=2;
//				UART2_Send_Str(u2_send,11);
//				delay_ms(500);break;
//			}
//			delay_ms(50);
//		}
			
//		RGB_EN(DARK);
//		u2_send[3]=2;
//		UART2_Send_Str(u2_send,11);
		
		
//		MOTOR_ANTI(SD_180,-SD_180);
//		delay_ms(ZW_180);
//		CAR_STOP();
//		
//		if(return_sta==0) return_sta=1;
//		else if(return_sta==1) {CAR_STOP();while(1);}
	}
	else
	{
		MOTOR_ANTI(30,30);
	}
}