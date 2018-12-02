#pragma once
#include <EEPROM\EEPROM.h>
#include <Arduino.h>

//��ť
const int Button_Chess = 123;
const int Button_Write_And_Draw = 123;
//���̵Ĵ�С
const int length_x = 10;
const int length_y = 10;
//����Ľӿ�pin   һ��Ҫ�ǵøģ�������������������
//�˴��Ǿ������̵�PIN��һ��Ҫ�ģ���������������
const int rowPins[length_x] = { 24,26,50,31,33,49,52,53,51,41};//input		//0		4
const int colPins[length_y] = { 30,34,37,17,23,27,57,16,25,29};//output
//�˴��ǹ��õĲ������������
//�˴���X��Y��Ĳ������������
const int Step_Motor_X_En = 38;
const int Step_Motor_X_Dir = 55;
const int Step_Motor_X_Step = 54;
const int Step_Motor_X2_En = 62;
const int Step_Motor_X2_Dir = 48;
const int Step_Motor_X2_Step = 46;

const int Step_Motor_Y_En = 56;
const int Step_Motor_Y_Dir = 61;
const int Step_Motor_Y_Step = 60;
//�˴�������Ƴ����Ĳ������������
const int Step_Motor_Z_1 = 63;
const int Step_Motor_Z_2 = 40;
const int Step_Motor_Z_3 = 42;
const int Step_Motor_Z_4 = 65;
const int revolation = 100;
//�˴�������ģ�������
//�˴��������������̵�����
const int Vacuum = 19;

const int percent_x = 4;
const int percent_y = 8;


//�˴��������һ�����ӵĴ�С������Ҫ�������ת����Ȧ
const int Square_Size_X = 8.125*200*percent_x;//32.5
const int Square_Size_Y = 0.8125 * 200 * percent_y;//32.5
//��������ķ�����ʱ���趨
const int delayms_low =  400;
const int delayms_high =  2;
//��λ�㵽���
const long Distance_X =  132.5 * 200 * percent_x;
const long Distance_Y =  5 * 200 * percent_y;//13.25
//�˴�������Ǵ���е���0��0��������Ҫ�ľ���
const long Distance_X_ZERO =  97.5 * 200 * percent_x;//39cm
const long Distance_Y_ZERO =  1.625 * 200 * percent_y;//6.5cm


//X��Y��Z��ĸ�λ��λ��������
const int Limit_Switch_X1 = 18;
const int Limit_Switch_X2 = 14;
const int Limit_Switch_Y = 15;

const int Limit_Switch_Z = 6;

//�˴���д��ģ��Ķ���
const int Rate_of_Word = 1;//���ֵķŴ��ʣ�Ŀǰֻ��������
//���¸������������������������ݺ��޸�
const long Length_of_X_Paper = 666L;//ֽ�ĳ���
const long Length_of_Y_Paper = 666L;//ֽ�Ŀ��
const int Distance_to_Paper_X = 666;//��ֽ��X����
const int Distance_to_Paper_Y = 666;//��ֽ��Y����
const int One_Rate_Distance_X = 2560;	//һ���Ŵ����µ�������ռ��X�ĳ���  2560
const int One_Rate_Distance_Y = 2560;//һ���Ŵ����µ�������ռ��Y�ĳ���  2560

//�˴�Ϊ�������ͷ�ļ�
class Machine_Player
{
private:
	//���������̵Ĵ�С

	unsigned char length;//���̵ĳ��� x
	unsigned char width;//���̵Ŀ�� y
	int latest_x;//�����һ������X������
	int latest_y;//�����һ������Y������

	int latest_AI_x=-1;//��������һ����������
	int latest_AI_y=-1;

	int over;//�Ƿ�������漰�������������¿�ʼ�¼�
	//================
	//���ڸ��������������ǰ��ִ��ʤ���ж�
	//================

	//================
	//���ڸ���������������ִ��ʤ���ж�
	//================
	void Machine_X_Y_Move(int x,int y);
	//�ڶ��ϴ���һ����̬���飻����
	//���鶼�Ǵ��㿪ʼ��
	unsigned short *desk2D;//����ָ��
	void Machine_Write_EEPROM(unsigned char x,unsigned char y);//�������Ӻ󣬺�����д��desk2D
	void Human_Write_EEPROM(unsigned char x,unsigned char y);//�������Ӻ󣬺�����д��desk2D
	void clear_EEPROM();	//���EEPROM����
	unsigned short getKey(
	);//������Ҫ֪������ӵ���ɫ������Ҫ֪�����
	
	bool point_check(int x,int y);//���������ǲ������µ�����
public:
	//����������Ĭ�ϴ�СΪ15*15
	//�˴�Ϊ���������
	Machine_Player(unsigned char l=15,unsigned char w=15,int o=0,int lx=0,int ly=0);
	~Machine_Player();
//******************//
	void set_machine_cheese(unsigned char x,unsigned char y);
	void keyboard_refresh();//��������״̬
	int win();//��Ϸ״̬���жϣ�����ʤ��δ�����ڶ��ģ�0��������ʤ����1��������ʧ�ܣ�2�������֣�3��  ----  �ȴ��㷨
	unsigned short desk_scan();//ɨ������
	void clear_desk();//������̣���ʼ��ʱ��ʹ��
	void put_cheese();//��������   ----  ��ʱû�ж��壬�ȴ��㷨 
	void reset();//��ʼ����λ����
	int get_Latest_x()const;//��õ�ǰ���ӵ�X����
	int get_Latest_y()const;//��õ�ǰ���ӵ�Y����
	void reset_Lasted_x(int x=0);//�������õ�ǰ���ӵ�λ��
	void reset_Lasted_y(int y=0);//�������õ�ǰ���ӵ�λ��
	void mode_pin();
};
class Little_Stepper_Motor
{
private:
	int Steps;
	boolean Direction;// gre
	unsigned long last_time;
	unsigned long currentMillis;
	int steps_left;
	long time;
	//Pin
	 int IN1;
	 int IN2;
	 int IN3;
	 int IN4;
public:
	void Stepper_Motor_Move();
	void stepper(int xw);
	void SetDirection();
	Little_Stepper_Motor(int p1 = Step_Motor_Z_1, int p2 = Step_Motor_Z_2, int p3 = Step_Motor_Z_3, int p4 = Step_Motor_Z_4);
	~Little_Stepper_Motor();
};
class Draw_graph
{
private:
	int latest_x;
	int latest_y;
public:
	Draw_graph();
	~Draw_graph();
	void pin_mode();
	void reset();
	void draw_square();
	void draw_trangle();
	void draw_circle();
};


#ifndef __COBAND_MAIN_H
#define __COBAND_MAIN_H


//***************************************************************
//#define DEBUG           0				//�򿪵�����Ϣ
#define M_SIZE          10              //���̴�СΪ10x10
#define DEPTH            2               //����������ٲ�
#define check(x)    (((x)<0) || ((x)>=M_SIZE))	//���������Ƿ����

//����״̬��ɫ
#define    SPACE            0




/*�Ʒְ�
�������ⶨ��,ֻ�����˲����ĸ������ϵķ�����������������һ��������*/
typedef enum score_e
{
	WIN5 = 1000,          //5��           
	ALIVE4 = 150,         //��4
	ALIVE3 = 15,          //��3
	DIE4 = 15,            //��4
	ALIVE2 =3,           //��2
	DIE3 = 3,             //��3
	DIE2 = 1,              //��2
	ALIVE1 = 1             //��1
}score;

//����
typedef struct chess_s
{
	unsigned char x;
	unsigned char y;
}chess_t;

//���ӵ�����
typedef struct chess_queue_s
{
	chess_t chess[M_SIZE*M_SIZE];
	unsigned char len;
}chess_queue;


/*����ֵ��*/
static int max_alphabeta(signed char depth, chess_t chess,signed int alpha,signed int beta);
/*��С��*/
static int min_alphabeta(signed char depth, chess_t chess,signed int alpha,signed int beta);

/*����Сֵ�㷨*/
void chess_ai_minmax_alphabeta(chess_t *chess, signed char depth);

int is_win(unsigned char x,unsigned char y,unsigned char color);

//�������Ż�:��Ŀ��������Ƚ��й��֣�Ȼ������,��Ϊalpha-beta��֦�����ڿ���˳��.
/*������������(�������ӵĿ�λ)*/
static void generate_point(chess_queue *queue);

/*��б�ߡ���б�ߡ��ᡢ������ת��һά����������*/
static int count_score(unsigned char n[], unsigned char chessColor);

/*�ѵ�ǰ�����������߶��浽һά����,Ȼ����һ�����*/
static signed int evaluate_board(void);

static unsigned int score_table(unsigned int number, unsigned int empty);

/*�Ƿ����ھ�:����֮���Ƿ����Ӵ���(�����Ƕ��ֻ����Լ����Ӷ�����)*/
static int has_neighbors(int x, int y);

//��ʾ���̵Ķ�ά����
//int keymap[M_SIZE][M_SIZE];

#endif





//class Write_and_Draw
//{
//private:
//	//�˴������Ǳʼ��X��Y�����ֽ�Ĵ�С
//	long length_of_X_Paper;
//	long length_of_Y_Paper;
//	int lasted_X_Paper;			
//	int lasted_Y_Paper;	
//	int Rate;//������
//	bool check_out_border_X();//���X�����Ƿ�Խ��
//	bool check_out_border_Y();//���Y�����Ƿ�Խ��
//	 //��һ�������ǳ������ڶ��������� dividend/divisor
//	void Step_Motor_X_Move(int divisor, int dividend = 1);//X�����ƶ�һ�����ӵ�һ������
//	void Step_Motor_Y_Move(int divisor, int dividend = 1);	//Y�����ƶ�һ�����ӵ�һ������
//
//public:
//	Write_and_Draw(long len_x_Paper= Length_of_X_Paper,long len_y_Paper=Length_of_Y_Paper,int Rate= Rate_of_Word);
//	void reset_Paper();//��գ���ʼ��λ��
//	int get_Lasted_x_Paper()const;//��õ�ǰX����
//	int get_Lasted_y_Paper()const;//��õ�ǰY����
//	void set_Lasted_x_Paper(int x=0);//����X����
//	void set_Lasted_y_Paper(int y = 0);//����Y����
//	bool dispose_out_border();//Խ�紦��
//	~Write_and_Draw();
//	void Move_Pen();//д��һ�����ֺ���ƶ��������ƶ�һ����
//	void Write();//��д
//
//
//
//
//    //��д����������
//	//ASCII_ENGLISH
//	//ASCII Between 32 to 126
//	void Write_32(int Rate);	//	' '
//	void Write_33(int Rate);	//	!
//	void Write_34(int Rate);	//	"
//	void Write_35(int Rate);	//	#
//	void Write_36(int Rate);	//	$
//	void Write_37(int Rate);	//	%
//	void Write_38(int Rate);	//	&
//	void Write_39(int Rate);	//  '
//	void Write_40(int Rate);	//	(
//	void Write_41(int Rate);	//	)
//	void Write_42(int Rate);	//	*
//	void Write_43(int Rate);	//	+
//	void Write_44(int Rate);	//	,
//	void Write_45(int Rate);	//	-
//	void Write_46(int Rate);	//	.
//	void Write_47(int Rate);	//	/
//	void Write_48(int Rate);	//	0
//	void Write_49(int Rate);	//	1
//	void Write_50(int Rate);	//	2
//	void Write_51(int Rate);	//	3
//	void Write_52(int Rate);	//	4
//	void Write_53(int Rate);	//	5
//	void Write_54(int Rate);	//	6
//	void Write_55(int Rate);	//	7
//	void Write_56(int Rate);	//	8
//	void Write_57(int Rate);	//	9
//	void Write_58(int Rate);	//	:
//	void Write_59(int Rate);	//	;
//	void Write_60(int Rate);	//	<
//	void Write_61(int Rate);	//	=
//	void Write_62(int Rate);	//	>
//	void Write_63(int Rate);	//	?
//	void Write_64(int Rate);	//	@
//	void Write_65(int Rate);	//	A
//	void Write_66(int Rate);	//	B
//	void Write_67(int Rate);	//	C
//	void Write_68(int Rate);	//	D
//	void Write_69(int Rate);	//	E
//	void Write_70(int Rate);	//	F
//	void Write_71(int Rate);	//	G
//	void Write_72(int Rate);	//	H
//	void Write_73(int Rate);	//	I
//	void Write_74(int Rate);	//	J
//	void Write_75(int Rate);	//	K
//	void Write_76(int Rate);	//	L
//	void Write_77(int Rate);	//	M
//	void Write_78(int Rate);	//	N
//	void Write_79(int Rate);	//	O
//	void Write_80(int Rate);	//	P
//	void Write_81(int Rate);	//	Q
//	void Write_82(int Rate);	//	R
//	void Write_83(int Rate);	//	S
//	void Write_84(int Rate);	//	T
//	void Write_85(int Rate);	//	U
//	void Write_86(int Rate);	//	V
//	void Write_87(int Rate);	//	W
//	void Write_88(int Rate);	//	X
//	void Write_89(int Rate);	//	Y
//	void Write_90(int Rate);	//	Z
//	void Write_91(int Rate);	//	[
//	void Write_92(int Rate);	//	��\��
//	void Write_93(int Rate);	//	]
//	void Write_94(int Rate);	//	^
//	void Write_95(int Rate);	//	_
//	void Write_96(int Rate);	//	`
//	void Write_97(int Rate);	//	a
//	void Write_98(int Rate);	//	b
//	void Write_99(int Rate);	//	c
//	void Write_100(int Rate);	//	d
//	void Write_101(int Rate);	//	e
//	void Write_102(int Rate);	//	f
//	void Write_103(int Rate);	//	g
//	void Write_104(int Rate);	//	h
//	void Write_105(int Rate);	//	i
//	void Write_106(int Rate);	//	j
//	void Write_107(int Rate);	//	k
//	void Write_108(int Rate);	//	l
//	void Write_109(int Rate);	//	m
//	void Write_110(int Rate);	//	n
//	void Write_111(int Rate);	//	o
//	void Write_112(int Rate);	//	p
//	void Write_113(int Rate);	//	q
//	void Write_114(int Rate);	//	r
//	void Write_115(int Rate);	//	s
//	void Write_116(int Rate);	//	t
//	void Write_117(int Rate);	//	u
//	void Write_118(int Rate);	//	v
//	void Write_119(int Rate);	//	w
//	void Write_120(int Rate);	//	x
//	void Write_121(int Rate);	//	y
//	void Write_122(int Rate);	//	z
//	void Write_123(int Rate);	//	{
//	void Write_124(int Rate);	//	|
//	void Write_125(int Rate);	//	}
//	void Write_126(int Rate);	//	~
//
//	//GBK Chinese words
//	//500 Chinese characters commonly used
//};