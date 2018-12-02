#include"Machine_Player.h"
extern int keymap[length_x][length_y];
extern int hand;
extern uint8_t buffer_map[300];
Little_Stepper_Motor mystepper(Step_Motor_Z_1, Step_Motor_Z_2, Step_Motor_Z_3, Step_Motor_Z_4);
Little_Stepper_Motor::Little_Stepper_Motor(int p1, int p2, int p3, int p4)
{
	this->IN1 = p1;
	this->IN2 = p2;
	this->IN3 = p3;
	this->IN4 = p4;
	pinMode(IN1, OUTPUT);
	pinMode(IN2, OUTPUT);
	pinMode(IN3, OUTPUT);
	pinMode(IN4, OUTPUT);
	this->Steps = 0;
	this->Direction = true;
	this->steps_left = 1638;//4095 һȦ
}
Little_Stepper_Motor::~Little_Stepper_Motor() {}
void Little_Stepper_Motor::stepper(int xw)
{
	for (int x = 0; x < xw; x++) {
		switch (Steps) {
		case 0:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, HIGH);
			break;
		case 1:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, HIGH);
			break;
		case 2:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, LOW);
			break;
		case 3:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, HIGH);
			digitalWrite(IN3, HIGH);
			digitalWrite(IN4, LOW);
			break;
		case 4:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, HIGH);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			break;
		case 5:
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, HIGH);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			break;
		case 6:
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			break;
		case 7:
			digitalWrite(IN1, HIGH);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, HIGH);
			break;
		default:
			digitalWrite(IN1, LOW);
			digitalWrite(IN2, LOW);
			digitalWrite(IN3, LOW);
			digitalWrite(IN4, LOW);
			break;
		}
		SetDirection();
	}
}
void Little_Stepper_Motor::SetDirection()
{
	if (Direction == 1) {
		Steps++;
	}
	if (Direction == 0) {
		Steps--;
	}
	if (Steps > 7) {
		Steps = 0;
	}
	if (Steps < 0) {
		Steps = 7;
	}
}
void Little_Stepper_Motor::Stepper_Motor_Move()
{
	Serial.println("Stepper Moving!");
	while (steps_left > 0) {
		currentMillis = micros();
		if (currentMillis - last_time >= 1000) {
			stepper(1);
			time = time + micros() - last_time;
			last_time = micros();
			steps_left--;
		}
	}
	//Serial.println(time);
	//Serial.println("Wait...!");
	this->Direction = !this->Direction;
	steps_left = 1638;
	//steps_left = 2047;
}


//�˴�Ϊprivate��Ա����
//EEPROMд���ֵ 0=�հף�1=�������ӣ�2=��������
void Machine_Player::Machine_X_Y_Move(int x, int y)
{//��������x��yΪ��Ҫ��X���ϵ��ƶ���������Ҫ��Y�����ƶ��ĸ���
	int n = 0;
	n = x;
	x = y;
	y = n;
	long x1, x2;//X���ƶ���
	long y1, y2;//Y���ƶ���
	int pos = 0;//Z��ת����
				//�������ת���³�������������
				//digitalWrite(Step_Motor_Z_Dir, LOW);//Z�Ჽ����������˶�
				//for (pos = 0; pos < Step_Motor_Z_Distance; pos++)
				//{
				//	digitalWrite(Step_Motor_Z_Step, HIGH);
				//	delay(delayms);
				//	digitalWrite(Step_Motor_Z_Step, LOW);
				//	delay(delayms);
				//}
	Serial.println("Machine_X_Y_Move");
	digitalWrite(Vacuum, HIGH);//��ձ�����
	delay(4000);
	mystepper.Stepper_Motor_Move();
	mystepper.Stepper_Motor_Move();
	Serial.println("StepMotor_Move_Z over");
	//digitalWrite(Step_Motor_Z_Dir, HIGH);//Z�Ჽ����������˶�
	//for (pos = 0; pos < Step_Motor_Z_Distance; pos++)
	//{
	//	digitalWrite(Step_Motor_Z_Step, HIGH);
	//	delay(delayms);
	//	digitalWrite(Step_Motor_Z_Step, LOW);
	//	delay(delayms);
	//}
	//�˴��Ǵ���е���������
	digitalWrite(Step_Motor_X_Dir, HIGH);//X�Ჽ������򸺷����˶�
	digitalWrite(Step_Motor_X2_Dir, HIGH);
	for (x1 = 0; x1 < (9 - x + 3); x1++)
	{
		for (x2 = 0; x2 < Square_Size_X; x2++)
		{
			digitalWrite(Step_Motor_X_Step, HIGH);
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}
	}
	if (y >= 2)
	{
		digitalWrite(Step_Motor_Y_Dir, LOW);//Y�Ჽ��������������˶�
		for (y1 = 0; y1 < (y - 2); y1++)
		{
			for (y2 = 0; y2 < Square_Size_Y; y2++)
			{
				digitalWrite(Step_Motor_Y_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_Y_Step, LOW);
				delayMicroseconds(delayms_low);
			}
		}
	}
	if (y < 2)
	{
		digitalWrite(Step_Motor_Y_Dir, HIGH);//Y�Ჽ������򸺷����˶�
		for (y1 = 0; y1 < (2 - y); y1++)
		{
			for (y2 = 0; y2 < Square_Size_Y; y2++)
			{
				digitalWrite(Step_Motor_Y_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_Y_Step, LOW);
				delayMicroseconds(delayms_low);
			}
		}
	}
	//�������ת��ʹ������������
	//digitalWrite(Step_Motor_Z_Dir, LOW);//Z�Ჽ����������˶�
	//for (pos = 0; pos < Step_Motor_Z_Distance; pos++)
	//{
	//	digitalWrite(Step_Motor_Z_Step, HIGH);
	//	delay(delayms);
	//	digitalWrite(Step_Motor_Z_Step, LOW);
	//	delay(delayms);
	//}
	mystepper.Stepper_Motor_Move();
	digitalWrite(Vacuum, LOW);//�ر���ձ�
	delay(4000);
	mystepper.Stepper_Motor_Move();
	//digitalWrite(Step_Motor_Z_Dir, HIGH);//Z�Ჽ����������˶�
	//for (pos = 0; pos < Step_Motor_Z_Distance; pos++)
	//{
	//	digitalWrite(Step_Motor_Z_Step, HIGH);
	//	delay(delayms);
	//	digitalWrite(Step_Motor_Z_Step, LOW);
	//	delay(delayms);
	//}
	//�˴��Ǵ����ӵ��������
	digitalWrite(Step_Motor_X_Dir, LOW);//X�Ჽ��������������˶�
	digitalWrite(Step_Motor_X2_Dir, LOW);
	for (x1 = 0; x1 < (9 - x + 3); x1++)
	{
		for (x2 = 0; x2 < Square_Size_X; x2++)
		{
			digitalWrite(Step_Motor_X_Step, HIGH);
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}
	}
	if (y >= 2)
	{
		digitalWrite(Step_Motor_Y_Dir, HIGH);//Y�Ჽ������򸺷����˶�
		for (y1 = 0; y1 < (y - 2); y1++)
		{
			for (y2 = 0; y2 < Square_Size_Y; y2++)
			{
				digitalWrite(Step_Motor_Y_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_Y_Step, LOW);
				delayMicroseconds(delayms_low);
			}
		}
	}
	if (y < 2)
	{
		digitalWrite(Step_Motor_Y_Dir, LOW);//Y�Ჽ��������������˶�
		for (y1 = 0; y1 < (2 - y); y1++)
		{
			for (y2 = 0; y2 < Square_Size_Y; y2++)
			{
				digitalWrite(Step_Motor_Y_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_Y_Step, LOW);
				delayMicroseconds(delayms_low);
			}
		}
	}
}
void Machine_Player::clear_EEPROM()
{
	int i, j;
	int count = 0;
	for (i = 0; i < this->length; ++i)
	{
		for (j = 0; j < this->width; ++j)
		{
			EEPROM.write(count, 0);
			++count;
		}
	}
}
void Machine_Player::Machine_Write_EEPROM(unsigned char x, unsigned char y)
{
	EEPROM.write(x*this->length + y, 1);
	this->desk2D[x*this->length + y] = 1;
	keymap[x][y] = 1;
}
void Machine_Player::Human_Write_EEPROM(unsigned char x, unsigned char y)
{
	EEPROM.write(x*this->length + y, 2);
	this->desk2D[x*this->length + y] = 2;
	keymap[x][y] = 2;
}
unsigned short Machine_Player::getKey()
{
	for (int row = 0; row < length_x; ++row)
	{
		pinMode(rowPins[row], INPUT);
		digitalWrite(rowPins[row], HIGH);
	}
	for (int column = 0; column < length_y; ++column)
	{
		pinMode(colPins[column], OUTPUT);
		digitalWrite(colPins[column], HIGH);
	}
	//��Ե�ɨ��ľ�������
	bool point = false;
	const int keyboard_delay = 20;
	unsigned short key = -1;


	for (int column = 0; column < length_y; ++column)
	{
		digitalWrite(colPins[column], LOW);
		for (int row = 0; row < length_x; ++row)
		{
			if (digitalRead(rowPins[row]) == LOW)
			{
				delay(keyboard_delay);
				if (digitalRead(rowPins[row]) == LOW) {
					//key = keymap[row][column];
					if (this->point_check(row, column))
					{//�жϸ����Ƿ��Ǵ������µ���
						this->latest_x = row;
						this->latest_y = column;
						point = true;
						break;
					}
				}
			}
		}
		if (point == true)
		{
			break;
		}
		digitalWrite(colPins[column], HIGH);
	}
	if ((hand % 2 == 1) && (point == true))
	{
		key = 2;
	}
	if ((hand % 2 == 0) && (point == true))
	{
		key = 1;
	}
	return key;
}
bool Machine_Player::point_check(int x, int y)
{
	if (desk2D[x*this->length + y] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

//�˴�Ϊpublic��Ա����
Machine_Player::Machine_Player(unsigned char l, unsigned char w, int o, int lx, int ly)
{
	this->length = l;
	this->width = w;
	this->over = o;
	this->latest_x = lx;
	this->latest_y = ly;
	desk2D = new unsigned short[this->length*this->width];
	clear_desk();
}
Machine_Player::~Machine_Player()
{
	delete[]desk2D;
}
void Machine_Player::set_machine_cheese(unsigned char x, unsigned char y)
{
	this->desk2D[x*length_x + y] = 1;
	keymap[x][y] = 1;
}
void Machine_Player::keyboard_refresh()
{
	//��̬�ĳ�ʼ������
	int map_x, map_y;
	int count = 0;
	for (map_y = 0; map_y < length_y; ++map_y)
	{
		for (map_x = 0; map_x < length_x; ++map_x)
		{
			keymap[map_x][map_y] = count;
		}
	}

}
int Machine_Player::win()
{  //ʤ��δ�����ڶ��ģ�0��������ʤ����1��������ʧ�ܣ�2�������֣�3��
   //��ÿ�����Ӻ�Ը����ӽ���5�����Ӽ��
	short color = -1;
	color = desk2D[(this->latest_x)*length_x + this->latest_y];
	//б�Խ������"/"	
	int i = 1;
	while (true) {
		int point = 1;
		//Serial.println(i);
		//int position = (this->latest_x)*length_x + this->latest_y;
		int now = (this->latest_x + i)*length_x + this->latest_y - i;
		if (point == 5)
			return color;
		if (now > length_x*length_y || now < 0 || color != desk2D[now])
		{
			if (i < 0)
				break;
			if (i > 0)
				i = -1;
			//now = position;
		}
		if (color == desk2D[now])
		{
			point++;
		}
		i = i + i / abs(i);
		//Serial.println(now); Serial.println(desk2D[now]);
		//Serial.println(i);
		//Serial.print("point:"); Serial.println(point);
		//Serial.println("");
		//delay(1000);
	}

	//б�Խ������"\"
	i = 1;
	while (true) {
		int point = 1;
		//int position = (this->latest_x)*length_x + this->latest_y;
		int now = (this->latest_x - i)*length_x + this->latest_y - i;
		if (point == 5)
			return color;
		if (now > length_x*length_y || now < 0 || color != desk2D[now])
		{
			if (i < 0)
				break;
			if (i > 0)
				i = -1;
			//now = position;
		}
		if (color == desk2D[now])
		{
			point++;
		}
		i = i + i / abs(i);
	}

	//ˮƽ�����"��"
	i = 1;
	while (true) {
		int point = 1;
		//int position = (this->latest_x)*length_x + this->latest_y;
		int now = (this->latest_x + i)*length_x + this->latest_y;
		if (point == 5)
			return color;
		if (now > length_x*length_y || now < 0 || color != desk2D[now])
		{
			if (i < 0)
				break;
			if (i > 0)
				i = -1;
			//now = position;
		}
		if (color == desk2D[now])
		{
			point++;
		}
		i = i + i / abs(i);
	}


	//��ֱ�����"|"
	i = 1;
	while (true) {
		int point = 1;
		//int position = (this->latest_x)*length_x + this->latest_y;
		int now = (this->latest_x)*length_x + this->latest_y + i;
		if (point == 5)
			return color;
		if (now > length_x*length_y || now < 0 || color != desk2D[now])
		{
			if (i < 0)
				break;
			if (i > 0)
				i = -1;
			//now = position;
		}
		if (color == desk2D[now])
		{
			point++;
		}
		i = i + i / abs(i);
	}



	//�Ƿ�����
	int index;
	for (int index = 0; index < length_x*length_y; index++)
	{
		if (desk2D[index] == 0)
			return 0;//���ڶ���
	}
	if (index == length_x*length_y)
		return 3;//����

}
unsigned short Machine_Player::desk_scan()
{
	//ѭ��ɨ��������
	unsigned short key = this->getKey();
	if (key == 1)
	{
		Machine_Write_EEPROM(this->latest_x, this->latest_y);
	}
	if (key == 2)
	{
		Human_Write_EEPROM(this->latest_x, this->latest_y);
	}
	return key;
}

void Machine_Player::clear_desk()
{
	//��Ϸ��������ô˷���
	//��Ҫ����Ϊ�����ά��������
	int i = 0;

	for (i = 0; i < this->length*this->width; ++i)
	{
		desk2D[i] = 0;
	}
}

void Machine_Player::put_cheese()
{
	//�˴�ִ�л������ӣ����������㷨��ʹ��
	//��ʹ���㷨�ó����
	//Machine_X_Y_Move();	�����������꣬�����꣩
	//if (n_x > 10 || n_x < 0 || n_y>10 || n_y < 0) {

	//}

	// "/"
	while (true) {

		int d1, d2, d3, d4, d5, d6, d7, d8;
		//+i+i  +i-i -i+i -i-i +i -i +i -i
		d1 = keymap[latest_x + 1][latest_y + 1];
		d2 = keymap[latest_x + 1][latest_y - 1];
		d3 = keymap[latest_x - 1][latest_y + 1];
		d4 = keymap[latest_x - 1][latest_y - 1];
		d5 = keymap[latest_x + 1][latest_y];
		d6 = keymap[latest_x][latest_y + 1];
		d7 = keymap[latest_x - 1][latest_y];
		d8 = keymap[latest_x][latest_y - 1];
		int i = 0;
		if (d1 == 2) {
			while (keymap[latest_x + 2 - i][latest_y + 2 - i] != 0) {
				i++;
			}
			Serial.println(latest_x + 2);
			Serial.println(latest_y + 2);
			this->set_machine_cheese(latest_x + 2 - i, latest_y + 2 - i);
			Machine_X_Y_Move(latest_x + 2 - i, latest_y + 2 - i);
			break;
		}
		if (d2 == 2) {
			while (keymap[latest_x + 2 - i][latest_y - 2 + i] != 0) {
				i++;
			}
			Serial.println(latest_x + 2);
			Serial.println(latest_y - 2);
			this->set_machine_cheese(latest_x + 2 - i, latest_y - 2 + i);
			Machine_X_Y_Move(latest_x + 2 - i, latest_y - 2 + i);
			break;
		}
		if (d3 == 2) {
			while (keymap[latest_x - 2 + i][latest_y + 2 - i] != 0) {
				i++;
			}
			Serial.println(latest_x - 2);
			Serial.println(latest_y + 2);
			this->set_machine_cheese(latest_x - 2 + i, latest_y + 2 - i);
			Machine_X_Y_Move(latest_x - 2 + i, latest_y + 2 - i);
			break;
		}
		if (d4 == 2) {
			while (keymap[latest_x - 2 + i][latest_y - 2 + i] != 0) {
				i++;
			}
			Serial.println(latest_x - 2);
			Serial.println(latest_y - 2);
			this->set_machine_cheese(latest_x - 2 + i, latest_y - 2 + i);
			Machine_X_Y_Move(latest_x - 2 + i, latest_y - 2 + i);
			break;
		}
		if (d5 == 2) {
			while (keymap[latest_x + 2 - i][latest_y] != 0) {
				i++;
			}
			Serial.println(latest_x + 2);
			Serial.println(latest_y);
			this->set_machine_cheese(latest_x + 2 - i, latest_y);
			Machine_X_Y_Move(latest_x + 2 - i, latest_y);
			break;
		}
		if (d6 == 2) {
			while (keymap[latest_x][latest_y + 2 - i] != 0) {
				i++;
			}
			Serial.println(latest_x);
			Serial.println(latest_y + 2);
			this->set_machine_cheese(latest_x, latest_y + 2 - i);
			Machine_X_Y_Move(latest_x, latest_y + 2 - i);
			break;
		}
		if (d7 == 2) {
			while (keymap[latest_x - 2 + i][latest_y] != 0) {
				i++;
			}
			Serial.println(latest_x - 2);
			Serial.println(latest_y);
			this->set_machine_cheese(latest_x - 2 + i, latest_y);
			Machine_X_Y_Move(latest_x - 2 + i, latest_y);
			break;
		}
		if (d8 == 2) {
			while (keymap[latest_x][latest_y - 2 + i] != 0) {
				i++;
			}
			Serial.println(latest_x);
			Serial.println(latest_y - 2);
			this->set_machine_cheese(latest_x, latest_y - 2 + i);
			Machine_X_Y_Move(latest_x, latest_y - 2 + i);
			break;
		}
		int x = random(1, 3);
		if (x == 1) {
			Serial.println(latest_x);
			Serial.println(latest_y + 1);
			this->set_machine_cheese(latest_x, latest_y + 1);
			Machine_X_Y_Move(latest_x, latest_y + 1);
			break;
		}
		else if (x == 2)
		{
			Serial.println(latest_x + 1);
			Serial.println(latest_y);
			this->set_machine_cheese(latest_x + 1, latest_y);
			Machine_X_Y_Move(latest_x + 1, latest_y);
			break;
		}


	}



	/*if (keymap[maxarr[index].x][maxarr[index].y] == 1 || keymap[maxarr[index].x][maxarr[index].y] == 2)
	{

	}*/
	/*this->set_machine_cheese(maxarr[index].x, maxarr[index].y);
	Machine_X_Y_Move(maxarr[index].x, maxarr[index].y);*/
}


void Machine_Player::reset()
{
	this->mode_pin();
	//��ʼ��״̬
	Serial.println("Reseting!");
	clear_EEPROM();
	Serial.println("EEPROM clear Finished!");
	keyboard_refresh();
	Serial.println("Keboard refresh Finished!");
	clear_desk();
	Serial.println("Desk clear Finished!");
	reset_Lasted_x();
	reset_Lasted_y();
	Serial.println("X and Y Reset Finished!");
	//��еװ�ø�λ����
	digitalWrite(Step_Motor_X_En, LOW);//����X�Ჽ�����
	digitalWrite(Step_Motor_X2_En, LOW);
	digitalWrite(Step_Motor_X_Dir, HIGH);//X�Ჽ���������Ϊ������
	digitalWrite(Step_Motor_X2_Dir, HIGH);

	digitalWrite(Step_Motor_Y_En, LOW);//����Y�Ჽ�����
	digitalWrite(Step_Motor_Y_Dir, HIGH);//Y�Ჽ���������Ϊ������

										 //digitalWrite(Step_Motor_Z_EN, LOW);//����Z�Ჽ�����
										 //digitalWrite(Step_Motor_Z_Dir, HIGH);//Z�Ჽ���������Ϊ������
	digitalWrite(Vacuum, LOW);//�ر���ձ�
							  //�������״̬�³������������λ������,��Ҫ��λ
							  //for (int i = 0; i < Step_Motor_Z_Distance; i++)//Z �Ḵλ
							  //{
							  //	int L_S_Z = digitalRead(Limit_Switch_Z);
							  //	if (L_S_Z == HIGH) { break; }
							  //	digitalWrite(Step_Motor_Z_Step, HIGH);
							  //	delay(delayms);
							  //	digitalWrite(Step_Motor_Z_Step, LOW);
							  //	delay(delayms);
							  //}
	Serial.println("X Axis Reseting!");
	while (true)//X�Ḵλ
	{
		int L_S_X_1 = digitalRead(Limit_Switch_X1);
		int L_S_X_2 = digitalRead(Limit_Switch_X2);
		if ((L_S_X_1 == LOW) && (L_S_X_2 == LOW))
		{
			digitalWrite(Step_Motor_X_Step, HIGH);
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}
		if ((L_S_X_1 == LOW) && (L_S_X_2 == HIGH))
		{
			digitalWrite(Step_Motor_X_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			delayMicroseconds(delayms_low);
		}
		if ((L_S_X_2 == LOW) && (L_S_X_1 == HIGH))
		{
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}


		if ((L_S_X_1 == HIGH) && (L_S_X_2 == HIGH)) { break; }
	}
	Serial.println("X Axis Reset Finished!");
	Serial.println("Y Axis Reseting!");
	while (true)//Y�Ḵλ
	{
		int L_S_Y = digitalRead(Limit_Switch_Y);
		if (L_S_Y == HIGH) { break; }
		digitalWrite(Step_Motor_Y_Step, HIGH);
		delayMicroseconds(delayms_high);
		digitalWrite(Step_Motor_Y_Step, LOW);
		delayMicroseconds(delayms_low);
	}
	Serial.println("Y Axis Reset Finished!");
	//��0��0�����
	//�������ƶ�
	digitalWrite(Step_Motor_X_Dir, LOW);
	digitalWrite(Step_Motor_X2_Dir, LOW);
	digitalWrite(Step_Motor_Y_Dir, LOW);
	Serial.println("from (0,0) to position");
	for (long i = 0; i < Distance_X; i++)
	{
		digitalWrite(Step_Motor_X_Step, HIGH);
		digitalWrite(Step_Motor_X2_Step, HIGH);
		delayMicroseconds(delayms_high);
		digitalWrite(Step_Motor_X_Step, LOW);
		digitalWrite(Step_Motor_X2_Step, LOW);
		delayMicroseconds(delayms_low);
	}
	for (int i = 0; i < Distance_Y; i++)
	{
		digitalWrite(Step_Motor_Y_Step, HIGH);
		delayMicroseconds(delayms_high);
		digitalWrite(Step_Motor_Y_Step, LOW);
		delayMicroseconds(delayms_low);
	}

}

int Machine_Player::get_Latest_x()const
{
	return this->latest_x;
}

int Machine_Player::get_Latest_y()const
{
	return this->latest_y;
}

void Machine_Player::reset_Lasted_x(int x)
{
	this->latest_x = x;
}

void Machine_Player::reset_Lasted_y(int y)
{
	this->latest_y = y;
}

void Machine_Player::mode_pin()
{
	pinMode(Step_Motor_X_En, OUTPUT);
	pinMode(Step_Motor_X_Dir, OUTPUT);
	pinMode(Step_Motor_X_Step, OUTPUT);
	pinMode(Step_Motor_X2_En, OUTPUT);
	pinMode(Step_Motor_X2_Dir, OUTPUT);
	pinMode(Step_Motor_X2_Step, OUTPUT);
	pinMode(Step_Motor_Y_En, OUTPUT);
	pinMode(Step_Motor_Y_Dir, OUTPUT);
	pinMode(Step_Motor_Y_Step, OUTPUT);
	pinMode(Limit_Switch_X1, INPUT_PULLUP);
	pinMode(Limit_Switch_X2, INPUT_PULLUP);
	pinMode(Limit_Switch_Y, INPUT_PULLUP);
	pinMode(Limit_Switch_Z, INPUT_PULLUP);
	pinMode(Vacuum, OUTPUT);
}

//==========
//Draw_graph
//==========
Draw_graph::Draw_graph()
{
	this->latest_x = 0;
	this->latest_y = 0;
}
Draw_graph::~Draw_graph()
{

}
void Draw_graph::pin_mode()
{
	pinMode(Step_Motor_X_En, OUTPUT);
	pinMode(Step_Motor_X_Dir, OUTPUT);
	pinMode(Step_Motor_X_Step, OUTPUT);
	pinMode(Step_Motor_X2_En, OUTPUT);
	pinMode(Step_Motor_X2_Dir, OUTPUT);
	pinMode(Step_Motor_X2_Step, OUTPUT);
	pinMode(Step_Motor_Y_En, OUTPUT);
	pinMode(Step_Motor_Y_Dir, OUTPUT);
	pinMode(Step_Motor_Y_Step, OUTPUT);
	pinMode(Limit_Switch_X1, INPUT_PULLUP);
	pinMode(Limit_Switch_X2, INPUT_PULLUP);
	pinMode(Limit_Switch_Y, INPUT_PULLUP);
	pinMode(Limit_Switch_Z, INPUT_PULLUP);
	pinMode(Vacuum, OUTPUT);
}

void Draw_graph::reset()
{

	this->pin_mode();
	//��ʼ��״̬
	Serial.println("Reseting!");
	//��еװ�ø�λ����
	digitalWrite(Step_Motor_X_En, LOW);//����X�Ჽ�����
	digitalWrite(Step_Motor_X2_En, LOW);
	digitalWrite(Step_Motor_X_Dir, HIGH);//X�Ჽ���������Ϊ������
	digitalWrite(Step_Motor_X2_Dir, HIGH);

	digitalWrite(Step_Motor_Y_En, LOW);//����Y�Ჽ�����
	digitalWrite(Step_Motor_Y_Dir, HIGH);//Y�Ჽ���������Ϊ������
	digitalWrite(Vacuum, LOW);
	Serial.println("X Axis Reseting!");
	while (true)//X�Ḵλ
	{
		int L_S_X_1 = digitalRead(Limit_Switch_X1);
		int L_S_X_2 = digitalRead(Limit_Switch_X2);
		if ((L_S_X_1 == LOW) && (L_S_X_2 == LOW))
		{
			//Serial.println("low + low");
			digitalWrite(Step_Motor_X_Step, HIGH);
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}
		if ((L_S_X_1 == LOW) && (L_S_X_2 == HIGH))
		{
			//Serial.println("low + high");
			digitalWrite(Step_Motor_X_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			delayMicroseconds(delayms_low);
		}
		if ((L_S_X_2 == LOW) && (L_S_X_1 == HIGH))
		{
			//Serial.println("high + low");
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}


		if ((L_S_X_1 == HIGH) && (L_S_X_2 == HIGH)) { break; }
	}
	Serial.println("X Axis Reset Finished!");
	Serial.println("Y Axis Reseting!");
	while (true)//Y�Ḵλ
	{
		int L_S_Y = digitalRead(Limit_Switch_Y);
		if (L_S_Y == HIGH) { break; }
		digitalWrite(Step_Motor_Y_Step, HIGH);
		delayMicroseconds(delayms_high);
		digitalWrite(Step_Motor_Y_Step, LOW);
		delayMicroseconds(delayms_low);
	}
	Serial.println("Y Axis Reset Finished!");
	digitalWrite(Step_Motor_X_Dir, LOW);
	digitalWrite(Step_Motor_X2_Dir, LOW);
	digitalWrite(Step_Motor_Y_Dir, LOW);
	Serial.println("from (0,0) to position");
	for (long i = 0; i < Distance_X; i++)
	{
		digitalWrite(Step_Motor_X_Step, HIGH);
		digitalWrite(Step_Motor_X2_Step, HIGH);
		delayMicroseconds(delayms_high);
		digitalWrite(Step_Motor_X_Step, LOW);
		digitalWrite(Step_Motor_X2_Step, LOW);
		delayMicroseconds(delayms_low);
	}
	for (int i = 0; i < Distance_Y; i++)
	{
		digitalWrite(Step_Motor_Y_Step, HIGH);
		delayMicroseconds(delayms_high);
		digitalWrite(Step_Motor_Y_Step, LOW);
		delayMicroseconds(delayms_low);
	}
	//��position����ͼԭ��
	digitalWrite(Step_Motor_X_Dir, HIGH);//X�Ჽ������򸺷����˶�
	digitalWrite(Step_Motor_X2_Dir, HIGH);
	for (int x1 = 0; x1 < 1; x1++)
	{
		for (int x2 = 0; x2 < Square_Size_X; x2++)
		{
			digitalWrite(Step_Motor_X_Step, HIGH);
			digitalWrite(Step_Motor_X2_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_X_Step, LOW);
			digitalWrite(Step_Motor_X2_Step, LOW);
			delayMicroseconds(delayms_low);
		}
	}
	digitalWrite(Step_Motor_Y_Dir, LOW);//Y�Ჽ��������������˶�
	for (int y1 = 0; y1 < 2; y1++)
	{
		for (int y2 = 0; y2 < Square_Size_Y; y2++)
		{
			digitalWrite(Step_Motor_Y_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_Y_Step, LOW);
			delayMicroseconds(delayms_low);
		}
	}
}

void Draw_graph::draw_trangle()
{
	long x1, x2;//X���ƶ���
	long y1, y2;//Y���ƶ���
	int pos = 0;//Z��ת����
	

	Serial.println("StepMotor_Move_Z low");
	delay(4000);
	mystepper.Stepper_Motor_Move();
	Serial.println("StepMotor_Move_Z low finished");

		digitalWrite(Step_Motor_X_Dir, HIGH);//X�Ჽ������򸺷����˶�
		digitalWrite(Step_Motor_X2_Dir, HIGH);
		digitalWrite(Step_Motor_Y_Dir, LOW);//Y�Ჽ��������������˶�
	//��һ��б��
	for (int i = 0; i < 3; i++)
	{

			for (int z=0;z<Square_Size_Y;z++)
			{
				for (int p = 0; p < 2; p++)
				{
					digitalWrite(Step_Motor_X_Step, HIGH);
					digitalWrite(Step_Motor_X2_Step, HIGH);
					delayMicroseconds(delayms_high);
					digitalWrite(Step_Motor_X_Step, LOW);
					digitalWrite(Step_Motor_X2_Step, LOW);
					delayMicroseconds(delayms_low);
				}

				digitalWrite(Step_Motor_Y_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_Y_Step, LOW);
				delayMicroseconds(delayms_low);

				for (int p = 0; p < 3; p++)
				{
					digitalWrite(Step_Motor_X_Step, HIGH);
					digitalWrite(Step_Motor_X2_Step, HIGH);
					delayMicroseconds(delayms_high);
					digitalWrite(Step_Motor_X_Step, LOW);
					digitalWrite(Step_Motor_X2_Step, LOW);
					delayMicroseconds(delayms_low);
				}
			}

	}
	//ֱ��
	digitalWrite(Step_Motor_X_Dir, HIGH);//X�Ჽ������򸺷����˶�
	digitalWrite(Step_Motor_X2_Dir, HIGH);
	digitalWrite(Step_Motor_Y_Dir, HIGH);//Y�Ჽ������򸺷����˶�

	for (int i = 0; i < 6; i++)
	{
		for (int z = 0; z < Square_Size_Y; z++)
		{
			digitalWrite(Step_Motor_Y_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_Y_Step, LOW);
			delayMicroseconds(delayms_low);
		}
	}
	//�ڶ���б��
	digitalWrite(Step_Motor_X_Dir, LOW);//X�Ჽ��������������˶�
	digitalWrite(Step_Motor_X2_Dir, LOW);
	digitalWrite(Step_Motor_Y_Dir, LOW);//Y�Ჽ��������������˶�
	for (int i = 0; i < 3; i++)
	{

		for (int z = 0; z<Square_Size_Y; z++)
		{
			for (int p = 0; p < 2; p++)
			{
				digitalWrite(Step_Motor_X_Step, HIGH);
				digitalWrite(Step_Motor_X2_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_X_Step, LOW);
				digitalWrite(Step_Motor_X2_Step, LOW);
				delayMicroseconds(delayms_low);
			}

			digitalWrite(Step_Motor_Y_Step, HIGH);
			delayMicroseconds(delayms_high);
			digitalWrite(Step_Motor_Y_Step, LOW);
			delayMicroseconds(delayms_low);

			for (int p = 0; p < 3; p++)
			{
				digitalWrite(Step_Motor_X_Step, HIGH);
				digitalWrite(Step_Motor_X2_Step, HIGH);
				delayMicroseconds(delayms_high);
				digitalWrite(Step_Motor_X_Step, LOW);
				digitalWrite(Step_Motor_X2_Step, LOW);
				delayMicroseconds(delayms_low);
			}
		}

	}

	Serial.println("StepMotor_Move_Z high");
	delay(4000);
	mystepper.Stepper_Motor_Move();
	Serial.println("StepMotor_Move_Z high finished");
}


//================
//�˴���ʼ����Write_and_Draw
//================

//private

//bool Write_and_Draw::check_out_border_X()
//{
//	return this->lasted_X_Paper > (this->length_of_X_Paper / One_Rate_Distance_X);
//}
//
//bool Write_and_Draw::check_out_border_Y()
//{
//	return this->lasted_Y_Paper > (this->length_of_Y_Paper / One_Rate_Distance_Y);
//}
//void Write_and_Draw::Step_Motor_X_Move(int divisor, int dividend)
//{
//	for (int i = 0; i < (One_Rate_Distance_X*dividend*this->Rate) / divisor; i++)
//	{
//		digitalWrite(Step_Motor_X_Step, HIGH);
//		delay(delayms);
//		digitalWrite(Step_Motor_X_Step, LOW);
//		delay(delayms);
//	}
//}
//void  Write_and_Draw::Step_Motor_Y_Move(int divisor, int dividend)
//{
//	for (int i = 0; i < (One_Rate_Distance_Y*dividend*this->Rate) / divisor; i++)
//	{
//		digitalWrite(Step_Motor_Y_Step, HIGH);
//		delay(delayms);
//		digitalWrite(Step_Motor_Y_Step, LOW);
//		delay(delayms);
//	}
//
//}


//public
//Write_and_Draw::Write_and_Draw(long len_x_Paper, long len_y_Paper, int Rate)
//{
//	this->length_of_X_Paper = len_x_Paper;
//	this->length_of_Y_Paper = len_y_Paper;
//	this->lasted_X_Paper = 0;
//	this->lasted_Y_Paper = 0;
//	this->Rate = Rate;
//}
//Write_and_Draw::~Write_and_Draw() {}
//
//void Write_and_Draw::Move_Pen()
//{
//	bool top = this->dispose_out_border();
//	if (top == false)
//	{
//		digitalWrite(Step_Motor_X_Dir, HIGH);
//		for (int i = 0; i < One_Rate_Distance_X*this->Rate; i++)
//		{
//			digitalWrite(Step_Motor_X_Step, HIGH);
//			delay(delayms);
//			digitalWrite(Step_Motor_X_Step, LOW);
//			delay(delayms);
//		}
//		this->length_of_X_Paper += 1;
//	}
//}
//
//bool Write_and_Draw::dispose_out_border()
//{
//	bool top = false;
//	bool x = this->check_out_border_X();
//
//	if (x == true)
//	{
//		digitalWrite(Step_Motor_X_Dir, LOW);
//		for (int i = 0; i < this->length_of_X_Paper;i++)
//		{
//			digitalWrite(Step_Motor_X_Step, HIGH);
//			delay(delayms);
//			digitalWrite(Step_Motor_X_Step, LOW);
//			delay(delayms);
//		}
//		digitalWrite(Step_Motor_Y_Dir,HIGH);
//		for (int i = 0; i < One_Rate_Distance_Y*this->Rate; i++)
//		{
//			digitalWrite(Step_Motor_Y_Step, HIGH);
//			delay(delayms);
//			digitalWrite(Step_Motor_Y_Step, LOW);
//			delay(delayms);
//		}
//
//		this->lasted_X_Paper = 0;
//		this->lasted_Y_Paper += 1;
//		top = true;
//	}
//	bool y = this->check_out_border_Y();
//
//	if (y == true)
//	{
//		digitalWrite(Step_Motor_Y_Dir, HIGH);
//		for (int i = 0; i < this->length_of_Y_Paper; i++)
//		{
//			digitalWrite(Step_Motor_Y_Step, HIGH);
//			delay(delayms);
//			digitalWrite(Step_Motor_Y_Step, LOW);
//			delay(delayms);
//		}
//		this->lasted_Y_Paper = 0;
//		top = true;
//
//	}
//	return top;
//}
//
//int Write_and_Draw::get_Lasted_x_Paper()const
//{
//	return this->lasted_X_Paper;
//}
//
//int Write_and_Draw::get_Lasted_y_Paper()const
//{
//	return this->lasted_Y_Paper;
//}
//
//void Write_and_Draw::set_Lasted_x_Paper(int x)
//{
//	this->lasted_X_Paper = x;
//}
//
//void Write_and_Draw::set_Lasted_y_Paper(int y)
//{
//	this->lasted_Y_Paper = y;
//}
//
//void Write_and_Draw::reset_Paper()
//{
//	//��еװ�ø�λ����
//	digitalWrite(Step_Motor_X_En, LOW);//����X�Ჽ�����
//	digitalWrite(Step_Motor_X_Dir, LOW);//X�Ჽ���������Ϊ������
//
//	digitalWrite(Step_Motor_Y_En, LOW);//����Y�Ჽ�����
//	digitalWrite(Step_Motor_Y_Dir, LOW);//Y�Ჽ���������Ϊ������
//
//	//digitalWrite(Step_Motor_Z_EN, LOW);//����Z�Ჽ�����
//	//digitalWrite(Step_Motor_Z_Dir, HIGH);//Z�Ჽ���������Ϊ������
//	////�������״̬�³������������λ������,��Ҫ��λ
//	//for (int i = 0; i < Step_Motor_Z_Distance; i++)//Z �Ḵλ
//	//{
//	//	int L_S_Z = digitalRead(Limit_Switch_Z);
//	//	if (L_S_Z == HIGH) { break; }
//	//	digitalWrite(Step_Motor_Z_Step, HIGH);
//	//	delay(delayms);
//	//	digitalWrite(Step_Motor_Z_Step, LOW);
//	//	delay(delayms);
//	//}
//	for (long i = 0; i < 99999; i++)//X�Ḵλ
//	{
//		int L_S_X = digitalRead(Limit_Switch_X);
//		if (L_S_X == HIGH) { break; }
//		digitalWrite(Step_Motor_X_Step, HIGH);
//		delay(delayms);
//		digitalWrite(Step_Motor_X_Step, LOW);
//		delay(delayms);
//	}
//	for (long i = 0; i < 99999; i++)//Y�Ḵλ
//	{
//		int L_S_Y = digitalRead(Limit_Switch_Y);
//		if (L_S_Y == HIGH) { break; }
//		digitalWrite(Step_Motor_Y_Step, HIGH);
//		delay(delayms);
//		digitalWrite(Step_Motor_Y_Step, LOW);
//		delay(delayms);
//	}
//
//	digitalWrite(Step_Motor_X_Dir, HIGH);
//	digitalWrite(Step_Motor_Y_Dir, HIGH);
//
//	for (int i = 0; i < Distance_to_Paper_X; i++)
//	{
//		digitalWrite(Step_Motor_X_Step, HIGH);
//		delay(delayms);
//		digitalWrite(Step_Motor_X_Step, LOW);
//		delay(delayms);
//	}
//
//	for (int i = 0; i < Distance_to_Paper_Y; i++)
//	{
//		digitalWrite(Step_Motor_Y_Step, HIGH);
//		delay(delayms);
//		digitalWrite(Step_Motor_Y_Step, LOW);
//		delay(delayms);
//	}
//
//
//}
//
//void Write_and_Draw::Write()
//{
//	//use switch to switch words' code
//	//????????????????
//	for (int i = 12; i < 300; i++)
//	{
//		if ((buffer_map[i] >= 33) && (buffer_map[i] <= 127))
//		{	//English Code
//			switch (buffer_map[i])
//			{
//			case 32:
//				Write_32(this->Rate);
//				Move_Pen();
//				break;
//			case 33:
//				Write_33(this->Rate);
//				Move_Pen();
//				break;
//			case 34:
//				Write_34(this->Rate);
//				Move_Pen();
//				break;
//			case 35:
//				Write_35(this->Rate);
//				Move_Pen();
//				break;
//			case 36:
//				Write_36(this->Rate);
//				Move_Pen();
//				break;
//			case 37:
//				Write_37(this->Rate);
//				Move_Pen();
//				break;
//			case 38:
//				Write_38(this->Rate);
//				Move_Pen();
//				break;
//			case 39:
//				Write_39(this->Rate);
//				Move_Pen();
//				break;
//			case 40:
//				Write_40(this->Rate);
//				Move_Pen();
//				break;
//			case 41:
//				Write_41(this->Rate);
//				Move_Pen();
//				break;
//			case 42:
//				Write_42(this->Rate);
//				Move_Pen();
//				break;
//			case 43:
//				Write_43(this->Rate);
//				Move_Pen();
//				break;
//			case 44:
//				Write_44(this->Rate);
//				Move_Pen();
//				break;
//			case 45:
//				Write_45(this->Rate);
//				Move_Pen();
//				break;
//			case 46:
//				Write_46(this->Rate);
//				Move_Pen();
//				break;
//			case 47:
//				Write_47(this->Rate);
//				Move_Pen();
//				break;
//			case 48:
//				Write_48(this->Rate);
//				Move_Pen();
//				break;
//			case 49:
//				Write_49(this->Rate);
//				Move_Pen();
//				break;
//			case 50:
//				Write_50(this->Rate);
//				Move_Pen();
//				break;
//			case 51:
//				Write_51(this->Rate);
//				Move_Pen();
//				break;
//			case 52:
//				Write_52(this->Rate);
//				Move_Pen();
//				break;
//			case 53:
//				Write_53(this->Rate);
//				Move_Pen();
//				break;
//			case 54:
//				Write_54(this->Rate);
//				Move_Pen();
//				break;
//			case 55:
//				Write_55(this->Rate);
//				Move_Pen();
//				break;
//			case 56:
//				Write_56(this->Rate);
//				Move_Pen();
//				break;
//			case 57:
//				Write_57(this->Rate);
//				Move_Pen();
//				break;
//			case 58:
//				Write_58(this->Rate);
//				Move_Pen();
//				break;
//			case 59:
//				Write_59(this->Rate);
//				Move_Pen();
//				break;
//			case 60:
//				Write_60(this->Rate);
//				Move_Pen();
//				break;
//			case 61:
//				Write_61(this->Rate);
//				Move_Pen();
//				break;
//			case 62:
//				Write_62(this->Rate);
//				Move_Pen();
//				break;
//			case 63:
//				Write_63(this->Rate);
//				Move_Pen();
//				break;
//			case 64:
//				Write_64(this->Rate);
//				Move_Pen();
//				break;
//			case 65:
//				Write_65(this->Rate);
//				Move_Pen();
//				break;
//			case 66:
//				Write_66(this->Rate);
//				Move_Pen();
//				break;
//			case 67:
//				Write_67(this->Rate);
//				Move_Pen();
//				break;
//			case 68:
//				Write_68(this->Rate);
//				Move_Pen();
//				break;
//			case 69:
//				Write_69(this->Rate);
//				Move_Pen();
//				break;
//			case 70:
//				Write_70(this->Rate);
//				Move_Pen();
//				break;
//			case 71:
//				Write_71(this->Rate);
//				Move_Pen();
//				break;
//			case 72:
//				Write_72(this->Rate);
//				Move_Pen();
//				break;
//			case 73:
//				Write_73(this->Rate);
//				Move_Pen();
//				break;
//			case 74:
//				Write_74(this->Rate);
//				Move_Pen();
//				break;
//			case 75:
//				Write_75(this->Rate);
//				Move_Pen();
//				break;
//			case 76:
//				Write_76(this->Rate);
//				Move_Pen();
//				break;
//			case 77:
//				Write_77(this->Rate);
//				Move_Pen();
//				break;
//			case 78:
//				Write_78(this->Rate);
//				Move_Pen();
//				break;
//			case 79:
//				Write_79(this->Rate);
//				Move_Pen();
//				break;
//			case 80:
//				Write_80(this->Rate);
//				Move_Pen();
//				break;
//			case 81:
//				Write_81(this->Rate);
//				Move_Pen();
//				break;
//			case 82:
//				Write_82(this->Rate);
//				Move_Pen();
//				break;
//			case 83:
//				Write_83(this->Rate);
//				Move_Pen();
//				break;
//			case 84:
//				Write_84(this->Rate);
//				Move_Pen();
//				break;
//			case 85:
//				Write_85(this->Rate);
//				Move_Pen();
//				break;
//			case 86:
//				Write_86(this->Rate);
//				Move_Pen();
//				break;
//			case 87:
//				Write_87(this->Rate);
//				Move_Pen();
//				break;
//			case 88:
//				Write_88(this->Rate);
//				Move_Pen();
//				break;
//			case 89:
//				Write_89(this->Rate);
//				Move_Pen();
//				break;
//			case 90:
//				Write_90(this->Rate);
//				Move_Pen();
//				break;
//			case 91:
//				Write_91(this->Rate);
//				Move_Pen();
//				break;
//			case 92:
//				Write_92(this->Rate);
//				Move_Pen();
//				break;
//			case 93:
//				Write_93(this->Rate);
//				Move_Pen();
//				break;
//			case 94:
//				Write_94(this->Rate);
//				Move_Pen();
//				break;
//			case 95:
//				Write_95(this->Rate);
//				Move_Pen();
//				break;
//			case 96:
//				Write_96(this->Rate);
//				Move_Pen();
//				break;
//			case 97:
//				Write_97(this->Rate);
//				Move_Pen();
//				break;
//			case 98:
//				Write_98(this->Rate);
//				Move_Pen();
//				break;
//			case 99:
//				Write_99(this->Rate);
//				Move_Pen();
//				break;
//			case 100:
//				Write_100(this->Rate);
//				Move_Pen();
//				break;
//			case 101:
//				Write_101(this->Rate);
//				Move_Pen();
//				break;
//			case 102:
//				Write_102(this->Rate);
//				Move_Pen();
//				break;
//			case 103:
//				Write_103(this->Rate);
//				Move_Pen();
//				break;
//			case 104:
//				Write_104(this->Rate);
//				Move_Pen();
//				break;
//			case 105:
//				Write_105(this->Rate);
//				Move_Pen();
//				break;
//			case 106:
//				Write_106(this->Rate);
//				Move_Pen();
//				break;
//			case 107:
//				Write_107(this->Rate);
//				Move_Pen();
//				break;
//			case 108:
//				Write_108(this->Rate);
//				Move_Pen();
//				break;
//			case 109:
//				Write_109(this->Rate);
//				Move_Pen();
//				break;
//			case 110:
//				Write_110(this->Rate);
//				Move_Pen();
//				break;
//			case 111:
//				Write_111(this->Rate);
//				break;
//			case 112:
//				Write_112(this->Rate);
//				Move_Pen();
//				break;
//			case 113:
//				Write_113(this->Rate);
//				Move_Pen();
//				break;
//			case 114:
//				Write_114(this->Rate);
//				Move_Pen();
//				break;
//			case 115:
//				Write_115(this->Rate);
//				Move_Pen();
//				break;
//			case 116:
//				Write_116(this->Rate);
//				Move_Pen();
//				break;
//			case 117:
//				Write_117(this->Rate);
//				Move_Pen();
//				break;
//			case 118:
//				Write_118(this->Rate);
//				Move_Pen();
//				break;
//			case 119:
//				Write_119(this->Rate);
//				Move_Pen();
//				break;
//			case 120:
//				Write_120(this->Rate);
//				Move_Pen();
//				break;
//			case 121:
//				Write_121(this->Rate);
//				Move_Pen();
//				break;
//			case 122:
//				Write_122(this->Rate);
//				Move_Pen();
//				break;
//			case 123:
//				Write_123(this->Rate);
//				Move_Pen();
//				break;
//			case 124:
//				Write_124(this->Rate);
//				Move_Pen();
//				break;
//			case 125:
//				Write_125(this->Rate);
//				Move_Pen();
//				break;
//			case 126:
//				Write_126(this->Rate);
//				Move_Pen();
//				break;
//			}
//		}
//		/*if ((buffer_map[i] > 128) && (buffer_map[i + 1] > 0))
//		{
//			uint8_t buffer_map_high = buffer_map[i];
//			uint8_t buffer_map_low = buffer_map[i + 1];
//			Serial.println("Chinese Word!");
//
//		}*/
//	}
//}
//
//
//
////��д�����Ķ���
//void Write_and_Draw::Write_32(int Rate)	//	' '
//{
//	Serial.println(" ");
//	// just blank
//}
//void Write_and_Draw::Write_33(int Rate)	//	!
//{
//	Serial.println("!");
//}
//void Write_and_Draw::Write_34(int Rate)	//	"
//{
//	Serial.println("\"");
//}
//void Write_and_Draw::Write_35(int Rate)	//	#
//{
//	Serial.println("#");
//}
//void Write_and_Draw::Write_36(int Rate)	//	$
//{
//	Serial.println("$");
//}
//void Write_and_Draw::Write_37(int Rate)	//	%
//{
//	Serial.println("%");
//}
//void Write_and_Draw::Write_38(int Rate)	//	&
//{
//	Serial.println("&");
//}
//void Write_and_Draw::Write_39(int Rate)	//  '
//{
//	Serial.println("'");
//}
//void Write_and_Draw::Write_40(int Rate)	//	(
//{
//	Serial.println("(");
//}
//void Write_and_Draw::Write_41(int Rate)	//	)
//{
//	Serial.println(")");
//}
//void Write_and_Draw::Write_42(int Rate)	//	*
//{
//	Serial.println("*");
//}
//void Write_and_Draw::Write_43(int Rate)	//	+
//{
//	Serial.println("+");
//}
//void Write_and_Draw::Write_44(int Rate)	//	,
//{
//	Serial.print(",");
//}
//void Write_and_Draw::Write_45(int Rate)	//	-
//{
//	Serial.println("-");
//}
//void Write_and_Draw::Write_46(int Rate)	//	.
//{
//	Serial.println(".");
//}
//void Write_and_Draw::Write_47(int Rate)	//	/
//{
//	Serial.println("/");
//}
//void Write_and_Draw::Write_48(int Rate)	//	0
//{
//	Serial.println("0");
//}
//void Write_and_Draw::Write_49(int Rate)	//	1
//{
//	Serial.println("1");
//}
//void Write_and_Draw::Write_50(int Rate)	//	2
//{
//	Serial.println("2");
//}
//void Write_and_Draw::Write_51(int Rate)	//	3
//{
//	Serial.println("3");
//}
//void Write_and_Draw::Write_52(int Rate)	//	4
//{
//	Serial.println("4");
//}
//void Write_and_Draw::Write_53(int Rate)	//	5
//{
//	Serial.println("5");
//}
//void Write_and_Draw::Write_54(int Rate)	//	6
//{
//	Serial.println("6");
//}
//void Write_and_Draw::Write_55(int Rate)	//	7
//{
//	Serial.println("7");
//}
//void Write_and_Draw::Write_56(int Rate)	//	8
//{
//	Serial.println("8");
//}
//void Write_and_Draw::Write_57(int Rate)	//	9
//{
//	Serial.println("9");
//}
//void Write_and_Draw::Write_58(int Rate)	//	:
//{
//	Serial.println(":");
//}
//void Write_and_Draw::Write_59(int Rate)	//	;
//{
//	Serial.println(";");
//}
//void Write_and_Draw::Write_60(int Rate)	//	<
//{
//	Serial.println("<");
//}
//void Write_and_Draw::Write_61(int Rate)	//	=
//{
//	Serial.println("=");
//}
//void Write_and_Draw::Write_62(int Rate)	//	>
//{
//	Serial.println(">");
//}
//void Write_and_Draw::Write_63(int Rate)	//	?
//{
//	Serial.println("?");
//}
//void Write_and_Draw::Write_64(int Rate)	//	@
//{
//	Serial.println("@");
//}
//void Write_and_Draw::Write_65(int Rate)	//	A
//{
//	Serial.println("A");
//}
//void Write_and_Draw::Write_66(int Rate)	//	B
//{
//	Serial.println("B");
//}
//void Write_and_Draw::Write_67(int Rate)	//	C
//{
//	Serial.println("C");
//}
//void Write_and_Draw::Write_68(int Rate)	//	D
//{
//	Serial.println("D");
//}
//void Write_and_Draw::Write_69(int Rate)	//	E
//{
//	Serial.println("E");
//}
//void Write_and_Draw::Write_70(int Rate)	//	F
//{
//	Serial.println("F");
//}
//void Write_and_Draw::Write_71(int Rate)	//	G
//{
//	Serial.println("G");
//}
//void Write_and_Draw::Write_72(int Rate)	//	H
//{
//	Serial.println("H");
//}
//void Write_and_Draw::Write_73(int Rate)	//	I
//{
//	Serial.println("I");
//}
//void Write_and_Draw::Write_74(int Rate)	//	J
//{
//	Serial.println("J");
//}
//void Write_and_Draw::Write_75(int Rate)	//	K
//{
//	Serial.println("K");
//}
//void Write_and_Draw::Write_76(int Rate)	//	L
//{
//	Serial.println("L");
//}
//void Write_and_Draw::Write_77(int Rate)	//	M
//{
//	Serial.println("M");
//}
//void Write_and_Draw::Write_78(int Rate)	//	N
//{
//	Serial.println("N");
//}
//void Write_and_Draw::Write_79(int Rate)	//	O
//{
//	Serial.println("O");
//}
//void Write_and_Draw::Write_80(int Rate)	//	P
//{
//	Serial.println("P");
//}
//void Write_and_Draw::Write_81(int Rate)	//	Q
//{
//	Serial.println("Q");
//}
//void Write_and_Draw::Write_82(int Rate)	//	R
//{
//	Serial.println("R");
//}
//void Write_and_Draw::Write_83(int Rate)	//	S
//{
//	Serial.println("S");
//}
//void Write_and_Draw::Write_84(int Rate)	//	T
//{
//	Serial.println("T");
//}
//void Write_and_Draw::Write_85(int Rate)	//	U
//{
//	Serial.println("U");
//}
//void Write_and_Draw::Write_86(int Rate)	//	V
//{
//	Serial.println("V");
//}
//void Write_and_Draw::Write_87(int Rate)	//	W
//{
//	Serial.println("W");
//}
//void Write_and_Draw::Write_88(int Rate)	//	X
//{
//	Serial.println("X");
//}
//void Write_and_Draw::Write_89(int Rate)	//	Y
//{
//	Serial.println("Y");
//}
//void Write_and_Draw::Write_90(int Rate)	//	Z
//{
//	Serial.println("Z");
//}
//void Write_and_Draw::Write_91(int Rate)	//	[
//{
//	Serial.println("[");
//}
//void Write_and_Draw::Write_92(int Rate)	//	��\��
//{
//	Serial.println(" \ ");
//}
//void Write_and_Draw::Write_93(int Rate)	//	]
//{
//	Serial.println("]");
//}
//void Write_and_Draw::Write_94(int Rate)	//	^
//{
//	Serial.println("^");
//}
//void Write_and_Draw::Write_95(int Rate)	//	_
//{
//	Serial.println("_");
//}
//void Write_and_Draw::Write_96(int Rate)	//	`
//{
//	Serial.println("~");
//}
//void Write_and_Draw::Write_97(int Rate)	//	a
//{
//	Serial.println("a");
//}
//void Write_and_Draw::Write_98(int Rate)	//	b
//{
//	Serial.println("b");
//}
//void Write_and_Draw::Write_99(int Rate)	//	c
//{
//	Serial.println("c");
//}
//void Write_and_Draw::Write_100(int Rate)	//	d
//{
//	Serial.println("d");
//}
//void Write_and_Draw::Write_101(int Rate)	//	e
//{
//	Serial.println("e");
//}
//void Write_and_Draw::Write_102(int Rate)	//	f
//{
//	Serial.println("f");
//}
//void Write_and_Draw::Write_103(int Rate)	//	g
//{
//	Serial.println("g");
//}
//void Write_and_Draw::Write_104(int Rate)	//	h
//{
//	Serial.println("h");
//}
//void Write_and_Draw::Write_105(int Rate)	//	i
//{
//	Serial.println("i");
//}
//void Write_and_Draw::Write_106(int Rate)	//	j
//{
//	Serial.println("j");
//}
//void Write_and_Draw::Write_107(int Rate)	//	k
//{
//	Serial.println("k");
//}
//void Write_and_Draw::Write_108(int Rate)	//	l
//{
//	Serial.println("l");
//}
//void Write_and_Draw::Write_109(int Rate)	//	m
//{
//	Serial.println("m");
//}
//void Write_and_Draw::Write_110(int Rate)	//	n
//{
//	Serial.println("n");
//}
//void Write_and_Draw::Write_111(int Rate)	//	o
//{
//	Serial.println("o");
//}
//void Write_and_Draw::Write_112(int Rate)	//	p
//{
//	Serial.println("p");
//}
//void Write_and_Draw::Write_113(int Rate)	//	q
//{
//	Serial.println("q");
//}
//void Write_and_Draw::Write_114(int Rate)	//	r
//{
//	Serial.println("r");
//}
//void Write_and_Draw::Write_115(int Rate)	//	s
//{
//	Serial.println("s");
//}
//void Write_and_Draw::Write_116(int Rate)	//	t
//{
//	Serial.println("t");
//}
//void Write_and_Draw::Write_117(int Rate)	//	u
//{
//	Serial.println("u");
//}
//void Write_and_Draw::Write_118(int Rate)	//	v
//{
//	Serial.println("v");
//}
//void Write_and_Draw::Write_119(int Rate)	//	w
//{
//	Serial.println("w");
//}
//void Write_and_Draw::Write_120(int Rate)	//	x
//{
//	Serial.println("x");
//}
//void Write_and_Draw::Write_121(int Rate)	//	y
//{
//	Serial.println("y");
//}
//void Write_and_Draw::Write_122(int Rate)	//	z
//{
//	Serial.println("z");
//}
//void Write_and_Draw::Write_123(int Rate)	//	{
//{
//	Serial.println("{");
//}
//void Write_and_Draw::Write_124(int Rate)	//	|
//{
//	Serial.println("|");
//}
//void Write_and_Draw::Write_125(int Rate)	//	}
//{
//	Serial.println("}");
//}
//void Write_and_Draw::Write_126(int Rate)	//	~
//{
//	Serial.println("~");
//}