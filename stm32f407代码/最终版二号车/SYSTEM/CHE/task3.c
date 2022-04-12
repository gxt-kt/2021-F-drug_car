#include "task3.h"
u8 go_flag;
u8 bound;
void 	TASK3_GO(void)
{
	static u8 t;
	while(1)//等待扫描色块//加上openmv有效判断
	{
		count_go=1;
		delay_ms(1000);
		detect_num=find_max(1);
		f(1,detect_num,k210_cnt_l[detect_num]);
		sprintf(sss,"N-%d",detect_num);
		OLED_ShowString(0,0,sss,16);
		sprintf(sss,"omv-%d-b-%d",openmvdata[0],black_num);
		OLED_ShowString(0,5,sss,16);
		
		if(k210_cnt_l[detect_num]>80)
		{
			count_go=0;
		for(t=1;t<=8;t++) k210_cnt_l[t]=0;
			sprintf(sss,"GOGOGO!");
		OLED_ShowString(0,3,sss,16);
			break;
		}
		count_go=0;
		
		for(t=1;t<=8;t++) k210_cnt_l[t]=0;
		;
	}
	//扫描色块结束
	
	while(leave_flag==0)
	{
		RGB_EN(YELLOW);
		delay_ms(5);
	}
	RGB_EN(DARK);
	
	board=0;
	bound=0;
	flag_go=1;
	while(1)//开始巡线
	{
		static u8 dier=0;
			while(dier==0)
			{
				delay_ms(10);
				CAR_xunji_3();
//				sprintf(sss,"1--%d %d",board,bound);
//		OLED_ShowString(0,0,sss,16);
				if(board==1&&time_up==0)
				{MOTOR_ANTI(40,0);delay_ms(youzhuan);ttt=HUNG;board=0;bound++;}
				if(bound>=2) dier=1;
			}
			RGB_EN(BLUE);
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
}
void CAR_xunji_3(void)
{
		if(openmvdata[0])
		{
				int error = openmvdata[0] - 160;
				vel = error* Kp_qwq;
				if(vel>10) vel = 10;
				if(vel<-10) vel = -10;
				Speed1 = Speed + vel;
				Speed2 = Speed - vel;
				MOTOR_ANTI(Speed1,Speed2);
		}
		else if(openmvdata[0]==0&&black_num>=3)
		{
			
//			delay_ms(400);
			CAR_STOP();
			delay_ms(1000);
			MOTOR_ANTI(SD_180,-SD_180);
			delay_ms(ZW_180);//11月14号改这里  //原来是550，11月9号改到了630
			CAR_STOP();
			while(go_flag==0);
			bound=1;
		}
		else
		{
			MOTOR_ANTI(30,30);
		}
	
}