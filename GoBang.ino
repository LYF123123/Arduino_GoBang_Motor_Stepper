/*
������ ��������
 Name:		GoBang.ino
 Created:	2018/9/10 23:34:14
 Author:	admin
*/
//����ʾ��ͼ

// 00 01 02 03 04 05 06
// 07 08 09 10 11 12 13
// 14 15 16 17 18 19 20
// 21 22 23 24 25 26 27
// 28 29 30 31 32 33 34
// 35 36 37 38 39 40 41
// 42 43 44 45 46 47 48
#include "Machine_Player.h"
bool MODE = false;//ģʽ���л���Ĭ��������
Draw_graph my_draw_graph;
Machine_Player mpl(length_x, length_y);


uint8_t buffer_map[300];//һ�λ�õ����ֵ�buffer

int hand = 1;//ͨ���Ⱥ��ֵķ�ʽ��ȷ���ڰ���
//�������̵ı�����ʼ������Ҫ��
unsigned char keymap[M_SIZE][M_SIZE];
int key;
//ʤ��δ�����ڶ��ģ�0��
//����ʤ����1��
//����ʧ�ܣ�2��
//���֣�3��
int over = 0;
//����ʹ�õı���x��y
char l_x;
char l_y;
int local_x;
int local_y;
Little_Stepper_Motor rua(Step_Motor_Z_1, Step_Motor_Z_2, Step_Motor_Z_3, Step_Motor_Z_4);
// the setup function runs once when you press reset or power the board
void setup() {
	Serial.begin(115200);
	if (MODE == false)
	{
		mpl.mode_pin();
		mpl.clear_desk();
		mpl.keyboard_refresh();
		mpl.reset_Lasted_y();
		mpl.reset_Lasted_x();
		mpl.reset();
		digitalWrite(Vacuum, LOW);
	}
	if (MODE == true)
	{
		my_draw_graph.pin_mode();
		my_draw_graph.reset();

	}
	Serial.println("Reset Finished!");
}

// the loop function runs over and over again until power down or reset
void loop() {
	//if ((digitalRead(Button_Chess) == LOW) && (digitalRead(Button_Write_And_Draw) == HIGH))
	//{
	//	MODE = true;
	//}
	//if ((digitalRead(Button_Chess) == HIGH) && (digitalRead(Button_Write_And_Draw) == LOW))
	//{
	//	MODE = false;
	//}

	//if (MODE == true)
	//{
	//	bool ruaaaaa = false;
	//	for (int i = 0; i < 300; i++) { buffer_map[i] = 0; }
	//	int count = 0;
	//	while (Serial.available() > 0)
	//	{
	//		ruaaaaa = true;
	//		//
	//		Serial.readBytes(buffer_map, 300);
	//	}
	//	if (ruaaaaa == true)
	//	{
	//		for (int i = 12; i < 300; i++)
	//		{
	//			if (buffer_map[i] != 0)
	//			{
	//				Serial.print(buffer_map[i]);
	//				Serial.print(" ");
	//			}
	//		}
	//		Serial.println();
	//		for (int i = 12; i < 300; i++)
	//		{
	//			if (buffer_map[i] != 0)
	//			{
	//				Serial.print(buffer_map[i],HEX);
	//				Serial.print(" ");
	//			}
	//		}
	//		Serial.println("=====");
	//		Write_and_Draw WD(Length_of_X_Paper, Length_of_Y_Paper, Rate_of_Word);
	//		WD.Write();
	//		Serial.println("Write Finished!");
	//		WD.reset_Paper();
	//	}
	//	
	//}

	//rua.Stepper_Motor_Move();
	////digitalWrite(Vacuum, HIGH);
	//delay(4000);
	//rua.Stepper_Motor_Move();
	//while (true);

	if (MODE == false)
	{
		int xx, yy, checkhand;
		xx = 11;
		yy = 11;
		checkhand = 1;
		delay(500);
		Serial.println();
		Serial.println(-1);//��ע��
		Serial.println(0);
		Serial.println(0);
		Serial.println(1);//��ע��
		while (over == 0)//ʤ��δ�֣����ڶ���
		{
			key = mpl.desk_scan();

			if (xx != mpl.get_Latest_x() || yy != mpl.get_Latest_y()||checkhand!=hand) {
				//=========================
				/*l_x = 'Q';
				l_y = 'Q';
				Serial.println("Please Enter X and Y");
				while ((l_x == 'Q') || (l_y == 'Q'))
				{
					while (Serial.available() > 0)
					{
						l_x = Serial.read();
					}
					if (l_y == 'Q')
					{
						l_y = l_x;
						l_x = 'Q';
					}
				}
				local_x = l_x - '0';
				local_y = l_y - '0';
				Serial.print("The local X and Y:  "); Serial.print(local_x); Serial.print("  ");
				Serial.println(local_y);
				keymap[local_x][local_y] = 2;
				mpl.reset_Lasted_x(local_x);
				mpl.reset_Lasted_y(local_y);
				
				for (int i = 0; i < length_x; i++)
				{
					for (int j = 0; j < length_y; j++)
					{
						Serial.print(keymap[j][i]);
						Serial.print("  ");
					}
					Serial.println();
				}*/
				//=========================
				Serial.println("********************");
				Serial.println(key);//��ע��
				Serial.println(mpl.get_Latest_x());
				Serial.println(mpl.get_Latest_y());
				Serial.println(hand);//��ע��
				xx = mpl.get_Latest_x();
				yy = mpl.get_Latest_y();
				checkhand = hand;
				delay(500);
				key = 2;
			}
			if (key == 2)//�����������������
			{
				key = 0;
				Serial.println("Check win or lose");
				over = mpl.win();
				if (over != 0) { break; }
				Serial.println("check finished");
				//ִ��put_cheese
				Serial.println("Putting cheese");
				mpl.put_cheese();
				//==============
				for (int i = 0; i < length_x; i++)
				{
					for (int j = 0; j < length_y; j++)
					{
						Serial.print(keymap[j][i]);
						Serial.print("  ");
					}
					Serial.println();
				}
				//==============
				Serial.println("Putting finished!");
				Serial.println("Check win or lose");
				over = mpl.win();
				Serial.println("check finished");
				Serial.println("********************");
				Serial.println();
				Serial.println();
				hand = hand + 2;
			}
		}
		Serial.print("over:  "); Serial.println(over);
		while (true);
		//if (over == 1)//����ʤ��
		//{
			
		//	over = 0;//������Ϸ״̬
		//	Serial.println("������");
		//	mpl.reset();//���¿�ʼ��Ϸ
		//}
		//if (over == 2)//����ʧ��
		//{
		//	over = 0;//������Ϸ״̬
		//	Serial.println("��Ӯ��");
		//	mpl.reset();//���¿�ʼ��Ϸ
		//}
		//if (over == 3)//����
		//{
		//	over = 0;//������Ϸ״̬
		//	Serial.println("����");
		//	mpl.reset();//���¿�ʼ��Ϸ
		//}
	}

	if (MODE == true)
	{
		my_draw_graph.draw_trangle();
	}
}
