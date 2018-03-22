#ifndef __MODBUS_H__
#define __MODBUS_H__

#define MB_RTU_MODE

#define MB_MAX_INPUT_REG 	9

#define MB_BUAD_RATE DBGU_BAUD_RATE
#define MB_MAX_PACKAGE_INTERVAL	60*100	//120*100ms=120 SEC

#define MB_ASCII_START 			':'
#define MB_ASCII_END0  			'\r'
#define MB_ASCII_END1  			'\n'

#define MB_BROADCAST_ADDR 	0
#define MB_DEV_ADDR 		0X11 //0x10-0x11

#define MB_ADDR  			0X00
#define MB_FN    			0X01
#define MB_DATA  			0X02


#define MB_FRAME_OK   	0xA0
#define MB_ADDR_MATCH 	0xA1
#define MB_LRC_ERR    	0xA2
#define MB_CRC_ERR			0xA3
#define MB_TIMEOUT			0xA4

//exception codes 
#define ILLEGAL_FUNCTION			0x01
#define ILLEGAL_DATA_ADDRESS	0x02
#define ILLEGAL_DATA_VALUE		0x03
#define SLAVE_DEVICE_FAILURE	0x04
#define ACKNOWLDEGE						0x05
#define SLAVE_DEVICE_BUSY			0x06
#define NEGATIVE_ACKNOWLEDGE	0x07
#define MEMORY_RARITY_ERROR		0x08


extern unsigned short reg30000[];
extern unsigned short reg40000[];


/*
#define MB_DEV_STATUS	0
//--------------------------------------
#define MB_RELAY_EN	1
#define MB_RELAY_DIS	2
	#define GL_LED (1<<12)
	#define GL_VACUOMETER (1<<9)
	#define GL_PUMP (1<<8)
	#define GL_BLEED_VALUE (1<<4)
	#define GL_MOTOR (1<<3)
	#define GL_BAFFLE (1<<2)
	#define GL_RHV (1<<1)
	#define GL_LHV (1<<0)
//--------------------------------------

//3-31


//REGISTER MAP
//REGISTER  00001-09999 Coil
//1-32 DO
	//1 		DO0		���Ҹ�ѹǹ��Դ
	//2 		DO1		�����Դ
	//3 		DO2		��Ʒ�����Դ
	//4 		DO3		�����õ�Դ
	//5 		DO4		��Ʒͨ�׼��LED ��Դ
	//38-65 not use
//33-65 RELAY
	//33		relay0	��е�á���ռ�
	//34		relay1	���ӱ�
	//35	 	not use

//REGISTER  30001-39999 Input Register  (R)
//30001	-	��ǹ����״̬
#define MB_HV_ST_L 		0	
	#define HV_PWR 		(1<<0)
	#define HV_SET_OK	(1<<1)
	#define HV_LEVEL1	(1<<2)
	#define HV_CUR_SET_OK	(1<<3)
	#define HV_ENABLE	(1<<7)
	
	#define HV_SET_TO (1<<8)
	#define HV_CUR_OV	(1<<9)
	#define HV_INCTRL	(1<<10)
//30002	-	��ǹ��ѹʵ�ʲ���ֵ��16λ����������λV
#define MB_VOL_FB_L 	1	
//30003	-	��ǹ��ѹʵ�ʲ���ֵ��16λ����������λV
#define MB_CUR_FB_L		2	
//30004	-	��ǹ��ѹ���ƶ˵�ǰ�趨����������ʹ�ã���16λ����������λV
#define MB_VOL_CTL_L	3
//30005	-	��ǹ�������ƶ˵�ǰ�趨����������ʹ�ã���16λ����������λuA
#define MB_CUR_CTL_L	4	

//30006	-	��ǹ����״̬
#define MB_HV_ST_R 		5	
//30007	-	��ǹ��ѹʵ�ʲ���ֵ��16λ����������λV
#define MB_VOL_FB_R 	6
//30008	-	��ǹ����ʵ�ʲ���ֵ��16λ����������λmA
#define MB_CUR_FB_R		7	
//30009	-	��ǹ��ѹ���ƶ˵�ǰ�趨����������ʹ�ã���16λ����������λV
#define MB_VOL_CTL_R	8
//30010	-	��ǹ�������ƶ˵�ǰ�趨����������ʹ�ã���16λ����������λuA
#define MB_CUR_CTL_R	9	
//30011	-	��ǹ��ѹ��ǰ�趨��16λ����������λV
#define MB_VOL_SET_L_ST	10
//30012	-	��ǹ������ǰ�趨��16λ����������λuA
#define MB_CUR_SET_L_ST	11
//30013	-	��ǹ��ѹ��ǰ�趨��16λ����������λV
#define MB_VOL_SET_R_ST	12
//30014	-	��ǹ������ǰ�趨��16λ����������λuA
#define MB_CUR_SET_R_ST	13

//��е��
#define MB_POWERPUMP_ST	16
	#define POWERPUMP_PWR_ON 	(1<<0)
	#define POWERPUMP_PWR_OFF (1<<1)
	
//30017	-	���ӱ�״̬�Ĵ���
#define MB_MPUMP_ST			17
	#define MPUMP_NORMAL	(1<<2)	//�豸��������
	#define MPUMP_HIGH_SP	(1<<3)	//�豸���е�����״̬
	#define MPUMP_RUN		 	(1<<4)	//�豸������
	#define MPUMP_OVERCUR	(1<<5)	//�豸����
	#define MPUMP_OVERHOT	(1<<6)	//�豸��ѹ
	#define MPUMP_TIMEOUT	(1<<7)	//�豸��ʱ

	#define MPUMP_PWR_ON	(1<<8)	//�豸���ϵ�
	#define MPUMP_PWR_OFF	(1<<9)	//�豸���µ�
	#define MPUMP_LOW_SP	(1<<10)	//
	#define MPUMP_STOP		(1<<11)	//
	#define MPUMP_INCTRL	(1<<12)	//�豸���ɿ�
	#define MPUMP_PWR_OFFING (1<<13)
//30018	-	���ӱõ�ǰ����Ƶ�ʣ�16λ����������λHz
#define MB_MPUMP_FREQ		18	
//30019	-	���ӱõ�ǰ������16λ����������λmA
#define MB_MPUMP_CUR		19	
//30020	-	���ӱõ�ǰ��ѹ��16λ����������λV
#define MB_MPUMP_VOL		20

//30025	-	��ռ�״̬
#define MB_VMETER_ST	24
	#define VMETER_PWR_ON 	(1<<0)	//��Դ����״̬��1��ʾ��Դ����
	#define VMETER_PWR_OFF	(1<<1)	//��Դ�ر�״̬��1��ʾ��Դ�ر�
	#define VMETER_WAIT_ON	(1<<2)
	#define VMETER_WAIT_OFF	(1<<3)
//30026	-	���ֵ,��MB_VMTER1һ�����32λ��������(float)((int)(MB_VMETER0<<16) | MB_VMETER1)
#define MB_VMETER0		25	//��MB_VMETER1���32bit��������bit31-16
//30027	-	
#define MB_VMETER1		26	//��MB_VMETER0���32bit��������bit15-0

#define MB_SAMPLE_ST	28	//��Ʒ��Ϣ��״̬
	#define SI_TRANSPARENCY	(1<<0)		//��ƷΪ͸���ģ�
	#define SI_MONITOR_EN	(1<<2)	//��Ʒ���ʹ��,
	#define SI_PWR_OFF_EN	(1<<3)	//�Զ��ػ�ʹ��,	
	#define SI_HOLE0	(1<<4)	//��Ʒ�׾��Ѿ�����hole0
	#define SI_HOLE1	(1<<5)	//��Ʒ�׾��Ѿ�����hole1
	#define SI_HOLE2	(1<<6)	//��Ʒ�׾��Ѿ�����hole2
	#define SI_HOLE3	(1<<7)	//��Ʒ�׾��Ѿ�����hole3
	#define SI_MOTO_PWR_ON (1<<8)	//��Ʒ����ϵ�
	#define SI_MOTO_PWR_OFF (1<<9)	//��Ʒ����ر�	
#define MB_SAMPLE_ANGLE	29	//��Ʒ���ýǶȣ�16λ����������λ0.1��
#define MB_SAMPLE_HOLE	30	//��Ʒ�׾���ѹֵ��16λ����������λmV

#define MB_SAMPLE_LED_ST		31		//��ƷLED״̬
	#define SLED_PWR_ON		(1<<0)		//�豸���ϵ�
	#define SLED_PWR_OFF	(1<<1)		//�豸�Ѷϵ�
	#define SLED1_PWR_ON	(1<<2)		//�豸���ϵ�
	#define SLED1_PWR_OFF	(1<<3)		//�豸�Ѷϵ�

#define MB_BAFFLE_ST				32		//����״̬
	#define BAFFLE_PWR_ON		(1<<0)	//�豸���ϵ�
	#define BAFFLE_PWR_OFF	(1<<1)	//�豸�Ѷϵ�

#define MB_BLEED_VALVE_ST 	33		//����������
	#define BLEED_VALVE_PWR_ON		(1<<0)	//�豸���ϵ�
	#define BLEED_VALVE_PWR_OFF		(1<<1)	//�豸�Ѷϵ�
	#define BLEED_VALVE1_PWR_ON		(1<<2)	//�豸���ϵ�
	#define BLEED_VALVE1_PWR_OFF	(1<<3)	//�豸�Ѷϵ�
	#define BLEED_VALVE2_PWR_ON		(1<<4)	//�豸���ϵ�
	#define BLEED_VALVE2_PWR_OFF	(1<<5)	//�豸�Ѷϵ�
	
	
#define MB_SYS_AUTOCTL_ST	34
	#define SYS_AUTO_ON		(1<<0)
	#define SYS_AUTO_OFF	(1<<1)
	#define SYS_AUTO_EN		(1<<8)
	#define SYS_AUTO_ON_ST 4
	#define SYS_AUTO_OFF_ST 12
	
#define MB_MOTOR_ST		35
	#define MOTOR_FORWARD  (1<<0)
	#define MOTOR_BACKWARD (1<<1)
	#define MOTOR_ENABLE   (1<<7)	
	


//10129-10136
//ADC16λ����ֵ
#define MB_ADC0		56	
#define MB_ADC1		57
#define MB_ADC2		58
#define MB_ADC3		59
#define MB_ADC4		60
#define MB_ADC5		61
#define MB_ADC6		62
#define MB_ADC7		63


//----------------------------------------------------------------------------------------------------------------------------------
//REGISTER  40001-49999 Holding Register (R/W)
#define MB_SYS_AUTOCTL				0
	#define SYS_AUTO_ON		(1<<0)
	#define SYS_AUTO_OFF	(1<<1)
	#define SYS_AUTO_EN		(1<<8)
	
//���Ҹ�ѹǹ�������ò���
#define MB_VOL_MAX			1	//����ѹֵ,16λ����������λV
#define MB_VOL_SCALE		2	//��ѹǹ��ѹ������������λmV/mV
#define MB_VOL_ERR_RATE	3	//��ѹ���������,16λ����������λ1%
#define MB_VOL_STEP			4	//��ѹ����ֵ,16λ����������λV
#define MB_VOL_STEP_INTERVAL	5	//��ѹ�������,16λ����������λmS
#define MB_VOL_STEP_TIMEOUT		6 //��ѹ���������ʱ,16λ����������λmS
#define MB_VOL_LEVEL1		7	//��ѹ��������ֵ�󣬿�ʼ�ӵ������������Զ�����ģʽ��16λ����������λV

#define MB_CURRRENT_MAX			9		//������ֵ,16λ����������λuA
#define MB_CUR_SCALE		10	//��ѹǹ����������������λuA/mV
#define MB_CUR_ERR_RATE	11	//�������������,16λ����������λ1%
#define MB_CUR_STEP			12
#define MB_CUR_STEP_INTERVAL	13
#define MB_CUR_STEP_TIMEOUT		14	
#define MB_CUR_CTL_START			15

#define MB_VOL_SET_L	17	//������ѹ�趨ֵ,16λ����������λV
#define MB_CUR_SET_L	18	//���������趨ֵ,16λ����������λuA
#define MB_VOL_SET_R	19	//������ѹ�趨ֵ,16λ����������λV
#define MB_CUR_SET_R	20	//���������趨ֵ,16λ����������λuA


//��е��
#define MB_POWERPUMP_CTL	24
	#define POWERPUMP_PWR_ON 	(1<<0)
	#define POWERPUMP_PWR_OFF (1<<1)
	
//���ӱ�
#define MB_MPUMP_CTL			25			//���ӱÿ��Ƽ�״̬�Ĵ���
#define MB_MPUMP_FREQ_SET	26 			//���ӱ��趨����Ƶ�ʣ�16λ����������λHz

//��ռ�
#define MB_VMETER_CTL		27
#define MB_VMETER_ERR_RATE	28		//��ռ�������,16λ����������λ1%
#define MB_VMETER_SET0	29
#define MB_VMETER_SET1	30
#define MB_VMETER_SET2	31
#define MB_VMETER_SET3	32


#define MB_SAMPLE_CTL		33	//�趨��Ʒ��Ϣ��״̬
//	#define SI_TRANSPARENCY	(1<<0)		//��ƷΪ͸���ģ�
//	#define SI_MONITOR_EN	(1<<2)	//��Ʒ���ʹ��,
//	#define SI_PWR_OFF_EN	(1<<3)	//�Զ��ػ�ʹ��,
//	#define SI_HOLE0	(1<<4)	//��Ʒ�׾�hole0
//	#define SI_HOLE1	(1<<5)	//��Ʒ�׾�hole1
//	#define SI_HOLE2	(1<<6)	//��Ʒ�׾�hole2
//	#define SI_HOLE3	(1<<7)	//��Ʒ�׾�hole3
//	#define SI_MOTO_PWR_ON (1<<8)	//��Ʒ����ϵ�
//	#define SI_MOTO_PWR_OFF (1<<9)	//��Ʒ����ر�	
#define MB_SAMPLE_ANGLE_SET		34		//��Ʒ���ýǶȣ�16λ����������λ0.1��
#define MB_SAMPLE_HOLE0		35		//����Ʒ�׾��ﵽhole0ʱ�ĵ�ѹֵ
#define MB_SAMPLE_START		36		//����Ʒ��⿪ʼʱ��,xx����֮��ʼ
#define MB_SAMPLE_INTERVAL	37		//����Ʒ�����ʱ��,����

#define MB_SAMPLE_LED		40		//��ƷLED״̬
//	#define SLED_PWR_ON		(1<<0)			//�豸���ϵ�
//	#define SLED_PWR_OFF	(1<<1)			//�豸���ϵ�
	
#define MB_BAFFLE				41		//����״̬
//	#define BAFFLE_PWR_ON		(1<<0)			//�豸���ϵ�
//	#define BAFFLE_PWR_OFF	(1<<1)			//�豸���ϵ�

#define MB_BLEED_VALVE 	42		//����������
//	#define BLEED_VALVE_PWR_ON	(1<<0)			//�豸���ϵ�
//	#define BLEED_VALVE_PWR_OFF	(1<<1)			//�豸���ϵ�
#define VMETER_START_DELAY 43	//��ռƿ��ض�ʱ�� �� ��е�ÿ������ӳ�������ٿ�����ռ�
#define VMETER_STOP_DELAY	 44	//��ռƹرտ��ض�ʱ�� �� �ر���ռƣ��ӳ�������ٹرջ�е��

#define MB_MPUMP_PWR_OFF_FREQ	45	//���ӱõ���ЩƵ��ʱ���Թرջ�е��
#define MB_BAFFLE_INTERVAL	46	//���忪�����,����

#define MB_MOTOR_CTRL		47
	#define MOTOR_FORWARD  (1<<0)
	#define MOTOR_BACKWARD (1<<1)
	#define MOTOR_ENABLE   (1<<7)


#define MB_GSM_CTL 50

#define MB_SMS_CMD      70
  #define MB_SMS_SEND   (1<<0)
  
#define MB_SMS_SERVER	80	//80-89	
#define MB_SMS_SERVER1	81
#define MB_SMS_SERVER2	82
#define MB_SMS_SERVER3	83
#define MB_SMS_SERVER4	84
#define MB_SMS_SERVER5	85
#define MB_SMS_SERVER6	86
#define MB_SMS_SERVER7	87
#define MB_SMS_SERVER8	88
#define MB_SMS_SERVER9	89

#define MB_SMS_PHONE	90	//90-99 
#define MB_SMS_PHONE1	91
#define MB_SMS_PHONE2	92
#define MB_SMS_PHONE3	93
#define MB_SMS_PHONE4	94
#define MB_SMS_PHONE5	95
#define MB_SMS_PHONE6	96
#define MB_SMS_PHONE7	97
#define MB_SMS_PHONE8	98
#define MB_SMS_PHONE9	99

#define MB_SMS_TEXT		256	
#define MB_SMS_TEXT1 	257	
#define MB_SMS_TEXT2 	258	
#define MB_SMS_TEXT3 	259	
#define MB_SMS_TEXT4 	260	
#define MB_SMS_TEXT5 	261	
#define MB_SMS_TEXT6 	262	
#define MB_SMS_TEXT7 	263	
#define MB_SMS_TEXT8 	264	
#define MB_SMS_TEXT9 	265	
#define MB_SMS_TEXT10 	266	
#define MB_SMS_TEXT11 	267	
#define MB_SMS_TEXT12 	268	
#define MB_SMS_TEXT13 	269	
#define MB_SMS_TEXT14 	270	
#define MB_SMS_TEXT15 	271	
#define MB_SMS_TEXT16 	272	
#define MB_SMS_TEXT17 	273	
#define MB_SMS_TEXT18 	274	
#define MB_SMS_TEXT19 	275	
#define MB_SMS_TEXT20 	276	
#define MB_SMS_TEXT21 	277	
#define MB_SMS_TEXT22 	278	
#define MB_SMS_TEXT23 	279	
#define MB_SMS_TEXT24 	280	
#define MB_SMS_TEXT25 	281	
#define MB_SMS_TEXT26 	282	
#define MB_SMS_TEXT27 	283	
#define MB_SMS_TEXT28 	284	
#define MB_SMS_TEXT29 	285	
#define MB_SMS_TEXT30 	286	
#define MB_SMS_TEXT31 	287	
#define MB_SMS_TEXT32 	288	
#define MB_SMS_TEXT33 	289	
#define MB_SMS_TEXT34 	290	
#define MB_SMS_TEXT35 	291	
#define MB_SMS_TEXT36 	292	
#define MB_SMS_TEXT37 	293	
#define MB_SMS_TEXT38 	294	
#define MB_SMS_TEXT39 	295	
#define MB_SMS_TEXT40 	296	
#define MB_SMS_TEXT41 	297	
#define MB_SMS_TEXT42 	298	
#define MB_SMS_TEXT43 	299	
#define MB_SMS_TEXT44 	300	
#define MB_SMS_TEXT45 	301	
#define MB_SMS_TEXT46 	302	
#define MB_SMS_TEXT47 	303	
#define MB_SMS_TEXT48 	304	
#define MB_SMS_TEXT49 	305	
#define MB_SMS_TEXT50 	306	
#define MB_SMS_TEXT51 	307	
#define MB_SMS_TEXT52 	308	
#define MB_SMS_TEXT53 	309	
#define MB_SMS_TEXT54 	310	
#define MB_SMS_TEXT55 	311	
#define MB_SMS_TEXT56 	312	
#define MB_SMS_TEXT57 	313	
#define MB_SMS_TEXT58 	314	
#define MB_SMS_TEXT59 	315	
#define MB_SMS_TEXT60 	316	
#define MB_SMS_TEXT61 	317	
#define MB_SMS_TEXT62 	318	
#define MB_SMS_TEXT63 	319	

//----------------------------------------------------------------------

#define MB_FD110A			0x96
#define MB_BEEP_ON		0x97
#define MB_BEEP_OFF		0x98
#define MB_LED_ON			0x99
#define MB_LED_OFF		0x9A
#define MB_L298_CTL		0x9B

//40129-4136
//DAC�����ѹ�趨��16λ����������λmV
#define MB_DAC0		128
#define MB_DAC1		129
#define MB_DAC2		130
#define MB_DAC3		131
#define MB_DAC4		132
#define MB_DAC5		133
#define MB_DAC6		134
#define MB_DAC7		135


*/


#ifdef MB_RTU_MODE
//volatile extern unsigned int  mb_rtu_frame_flag;
void mb_rtu_timer_enable(void);

#endif

unsigned short mb_CRC16(unsigned char *puchMsg, unsigned short usDataLen);

void modbus_init(void);
short mb_cmd_process(void);

void mb_send_frame(uint8_t *buf,uint8_t len);

char exception_response(char excep);
char read_coil_status(void);
char read_input_status(void);
char read_holding_register(void);
char read_input_register(void);
char fetch_comm_event_count(void);
char force_multiple_coils(void);
char preset_multiple_regs(void);
char report_slave_id(void);

#endif
