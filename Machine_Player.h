#pragma once
#include <EEPROM\EEPROM.h>
#include <Arduino.h>

//按钮
const int Button_Chess = 123;
const int Button_Write_And_Draw = 123;
//棋盘的大小
const int length_x = 10;
const int length_y = 10;
//矩阵的接口pin   一定要记得改！！！！！！！！！！
//此处是矩阵棋盘的PIN，一定要改！！！！！！！！
const int rowPins[length_x] = { 24,26,50,31,33,49,52,53,51,41};//input		//0		4
const int colPins[length_y] = { 30,34,37,17,23,27,57,16,25,29};//output
//此处是共用的步进电机的引脚
//此处是X，Y轴的步进电机的引脚
const int Step_Motor_X_En = 38;
const int Step_Motor_X_Dir = 55;
const int Step_Motor_X_Step = 54;
const int Step_Motor_X2_En = 62;
const int Step_Motor_X2_Dir = 48;
const int Step_Motor_X2_Step = 46;

const int Step_Motor_Y_En = 56;
const int Step_Motor_Y_Dir = 61;
const int Step_Motor_Y_Step = 60;
//此处定义控制齿条的步进电机的引脚
const int Step_Motor_Z_1 = 63;
const int Step_Motor_Z_2 = 40;
const int Step_Motor_Z_3 = 42;
const int Step_Motor_Z_4 = 65;
const int revolation = 100;
//此处是下棋模块的引脚
//此处定义的是真空吸盘的引脚
const int Vacuum = 19;

const int percent_x = 4;
const int percent_y = 8;


//此处定义的是一个格子的大小，即需要步进电机转多少圈
const int Square_Size_X = 8.125*200*percent_x;//32.5
const int Square_Size_Y = 0.8125 * 200 * percent_y;//32.5
//步进电机的防抖动时间设定
const int delayms_low =  400;
const int delayms_high =  2;
//复位点到棋盒
const long Distance_X =  132.5 * 200 * percent_x;
const long Distance_Y =  5 * 200 * percent_y;//13.25
//此处定义的是从棋盒到（0，0）坐标需要的距离
const long Distance_X_ZERO =  97.5 * 200 * percent_x;//39cm
const long Distance_Y_ZERO =  1.625 * 200 * percent_y;//6.5cm


//X和Y和Z轴的复位限位开关引脚
const int Limit_Switch_X1 = 18;
const int Limit_Switch_X2 = 14;
const int Limit_Switch_Y = 15;

const int Limit_Switch_Z = 6;

//此处是写字模块的定义
const int Rate_of_Word = 1;//文字的放大倍率，目前只能整数倍
//以下各个变量的制请量出具体数据后修改
const long Length_of_X_Paper = 666L;//纸的长度
const long Length_of_Y_Paper = 666L;//纸的宽度
const int Distance_to_Paper_X = 666;//到纸的X距离
const int Distance_to_Paper_Y = 666;//到纸的Y距离
const int One_Rate_Distance_X = 2560;	//一倍放大率下的文字所占用X的长宽  2560
const int One_Rate_Distance_Y = 2560;//一倍放大率下的文字所占用Y的长宽  2560

//此处为声明类的头文件
class Machine_Player
{
private:
	//五子棋棋盘的大小

	unsigned char length;//棋盘的长度 x
	unsigned char width;//棋盘的宽度 y
	int latest_x;//人最近一次落子X点坐标
	int latest_y;//人最近一次落子Y点坐标

	int latest_AI_x=-1;//机器最新一次落子坐标
	int latest_AI_y=-1;

	int over;//是否结束，涉及到不重启的重新开始事件
	//================
	//请在覆盖最近落子坐标前，执行胜负判断
	//================

	//================
	//请在覆盖最近落子坐标后，执行胜负判断
	//================
	void Machine_X_Y_Move(int x,int y);
	//在堆上创建一个动态数组；棋盘
	//数组都是从零开始的
	unsigned short *desk2D;//数组指针
	void Machine_Write_EEPROM(unsigned char x,unsigned char y);//机器落子后，函数内写入desk2D
	void Human_Write_EEPROM(unsigned char x,unsigned char y);//人类落子后，函数内写入desk2D
	void clear_EEPROM();	//清空EEPROM区域
	unsigned short getKey(
	);//不光需要知道落得子的颜色，还需要知道落点
	
	bool point_check(int x,int y);//检测这个点是不是最新的落子
public:
	//五子棋棋盘默认大小为15*15
	//此处为构造和析构
	Machine_Player(unsigned char l=15,unsigned char w=15,int o=0,int lx=0,int ly=0);
	~Machine_Player();
//******************//
	void set_machine_cheese(unsigned char x,unsigned char y);
	void keyboard_refresh();//重置棋盘状态
	int win();//游戏状态的判断，包括胜负未分正在对弈（0），机器胜利（1），机器失败（2），死局（3）  ----  等待算法
	unsigned short desk_scan();//扫描棋盘
	void clear_desk();//清空棋盘，初始化时刻使用
	void put_cheese();//机器落子   ----  暂时没有定义，等待算法 
	void reset();//初始化复位机器
	int get_Latest_x()const;//获得当前落子的X坐标
	int get_Latest_y()const;//获得当前落子的Y坐标
	void reset_Lasted_x(int x=0);//重新设置当前落子的位置
	void reset_Lasted_y(int y=0);//重新设置当前落子的位置
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
//#define DEBUG           0				//打开调试信息
#define M_SIZE          10              //棋盘大小为10x10
#define DEPTH            2               //最大搜索多少层
#define check(x)    (((x)<0) || ((x)>=M_SIZE))	//棋子坐标是否溢出

//棋子状态颜色
#define    SPACE            0




/*计分板
分数随意定的,只考虑了不让四个方向上的分数加起来超过更高一级的棋型*/
typedef enum score_e
{
	WIN5 = 1000,          //5连           
	ALIVE4 = 150,         //活4
	ALIVE3 = 15,          //活3
	DIE4 = 15,            //死4
	ALIVE2 =3,           //活2
	DIE3 = 3,             //死3
	DIE2 = 1,              //死2
	ALIVE1 = 1             //活1
}score;

//棋子
typedef struct chess_s
{
	unsigned char x;
	unsigned char y;
}chess_t;

//空子的序列
typedef struct chess_queue_s
{
	chess_t chess[M_SIZE*M_SIZE];
	unsigned char len;
}chess_queue;


/*极大值层*/
static int max_alphabeta(signed char depth, chess_t chess,signed int alpha,signed int beta);
/*极小层*/
static int min_alphabeta(signed char depth, chess_t chess,signed int alpha,signed int beta);

/*极大极小值算法*/
void chess_ai_minmax_alphabeta(chess_t *chess, signed char depth);

int is_win(unsigned char x,unsigned char y,unsigned char color);

//还可以优化:将目标空子们先进行估分，然后排序,因为alpha-beta剪枝依赖于空子顺序.
/*产生空子序列(可以下子的空位)*/
static void generate_point(chess_queue *queue);

/*正斜线、反斜线、横、竖，均转成一维数组来计算*/
static int count_score(unsigned char n[], unsigned char chessColor);

/*把当前局势所有连线都存到一维数组,然后算一遍分数*/
static signed int evaluate_board(void);

static unsigned int score_table(unsigned int number, unsigned int empty);

/*是否有邻居:两步之内是否有子存在(不论是对手还是自己的子都可以)*/
static int has_neighbors(int x, int y);

//表示棋盘的二维数组
//int keymap[M_SIZE][M_SIZE];

#endif





//class Write_and_Draw
//{
//private:
//	//此处两个是笔尖的X和Y坐标和纸的大小
//	long length_of_X_Paper;
//	long length_of_Y_Paper;
//	int lasted_X_Paper;			
//	int lasted_Y_Paper;	
//	int Rate;//缩放率
//	bool check_out_border_X();//检查X坐标是否越界
//	bool check_out_border_Y();//检查Y坐标是否越界
//	 //第一个参数是除数，第二个被除数 dividend/divisor
//	void Step_Motor_X_Move(int divisor, int dividend = 1);//X轴上移动一个格子的一定比例
//	void Step_Motor_Y_Move(int divisor, int dividend = 1);	//Y轴上移动一个格子的一定比例
//
//public:
//	Write_and_Draw(long len_x_Paper= Length_of_X_Paper,long len_y_Paper=Length_of_Y_Paper,int Rate= Rate_of_Word);
//	void reset_Paper();//清空，初始化位置
//	int get_Lasted_x_Paper()const;//获得当前X坐标
//	int get_Lasted_y_Paper()const;//获得当前Y坐标
//	void set_Lasted_x_Paper(int x=0);//设置X坐标
//	void set_Lasted_y_Paper(int y = 0);//设置Y坐标
//	bool dispose_out_border();//越界处理
//	~Write_and_Draw();
//	void Move_Pen();//写完一个文字后的移动，向右移动一“格”
//	void Write();//书写
//
//
//
//
//    //书写函数的声明
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
//	void Write_92(int Rate);	//	“\”
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