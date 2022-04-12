#include "task3.h"



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
					if(sta_sta==1) {MOTOR_ANTI(40,0);delay_ms(youzhuan);board=0;ttt=HUNG;}
					else if(sta_sta==3) {MOTOR_ANTI(0,40);delay_ms(zuozhuan);board=0;ttt=HUNG;}
					else if(sta_sta==2) {;}
				}
				CAR_xunji();
			}
			else
			{
			if(first==0){count_go=1;first=1;}
			if(board==1&&time_up==0&&(detect_num==1||detect_num==2))
			{
				if(detect_num==1){MOTOR_ANTI(0,40);delay_ms(zuozhuan);ttt=HUNG;board=0;sta_num[sta_i++]=1;}
				else if(detect_num==2){MOTOR_ANTI(40,0);delay_ms(youzhuan);ttt=HUNG;board=0;sta_num[sta_i++]=3;}
			}
			if(board==1&&time_up==0&&(detect_num!=1&&detect_num!=2))
			{
				count_go=0;
				find_MAX(1);
				find_MAX(2);
				if( val1_cnt < 3)find_val1=0;
				if( val2_cnt < 3)find_val2=0;
				if( val3_cnt < 3)find_val3=0;
				if( val4_cnt < 3)find_val4=0;
//				find_val1=find_max(1);
//				find_val3=find_max(2);
//				val1_cnt=k210_cnt_l[find_val1];
//				val3_cnt=k210_cnt_l[find_val3];
				for(t=1;t<=8;t++) k210_cnt_l[t]=0;
				for(t=1;t<=8;t++) k210_cnt_r[t]=0;
				sprintf(sss,"val:%d-%d-%d-%d",find_val1,find_val2,find_val3,find_val4);
				OLED_ShowString(0,2,sss,16);
				sprintf(sss,"cnt:%d-%d-%d-%d",val1_cnt,val2_cnt,val3_cnt,val4_cnt);
				OLED_ShowString(0,4,sss,16);
				if(find_val1==detect_num || find_val2==detect_num){MOTOR_ANTI(0,40);delay_ms(zuozhuan);ttt=HUNG;sta_num[sta_i++]=1;count_go=1;}
				else if(find_val3==detect_num || find_val4==detect_num){MOTOR_ANTI(40,0);delay_ms(youzhuan);ttt=HUNG;sta_num[sta_i++]=3;count_go=1;}
				else {count_go=1;}
				board=0;
			}
			
			CAR_xunji();
			}
		}
		else
		{
			CAR_STOP();
			flag_go=0;
		}
		//MOTOR_ANTI(30,30);
		//CAR_SPEED_SET(-100,300);
//		f(1,Speed1,Speed2,car_sta,board,zuo1,you1,USART5_RX_BUF[0],USART6_RX_BUF[0],);
//		f(2,flag_go,board,time_up,openmvdata[0],openmvdata[7],openmvdata[9],board);
		f(1,aaa,openmvdata[0],k210_left[1],k210_left[2],k210_left[3],k210_left[4],k210_left[5],k210_left[6],k210_left[7],k210_left[8]);
		f(2,k210_right[1],k210_right[2],k210_right[3],k210_right[4],k210_right[5],k210_right[6],k210_right[7],k210_right[8]);
		//f(2,K210_zsp_0_you,K210_zsp_1_you,K210_zsp_2_you,K210_zsp_3_you,K210_zsp_4_you,USART6_RX_BUF[0]);
		delay_ms(18);
	}
}