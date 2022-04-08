#pragma config(Sensor, in1,    sharpShort,     sensorAnalog)
#pragma config(Sensor, in5,    sharpRight,     sensorAnalog)
#pragma config(Sensor, in2,    sharpLeft,      sensorAnalog)
#pragma config(Sensor, in8,    sharpTop,       sensorAnalog)
#pragma config(Sensor, dgtl1,  backLeft,       sensorDigitalIn)
#pragma config(Sensor, dgtl2,  backRight,      sensorDigitalIn)
#pragma config(Sensor, dgtl3,  frontRight,     sensorDigitalIn)
#pragma config(Sensor, dgtl4,  encoder,        sensorQuadEncoder)
#pragma config(Sensor, dgtl7,  compassN,       sensorDigitalIn)
#pragma config(Sensor, dgtl8,  compassE,       sensorDigitalIn)
#pragma config(Sensor, dgtl9,  compassS,       sensorDigitalIn)
#pragma config(Sensor, dgtl10, compassW,       sensorDigitalIn)
#pragma config(Sensor, dgtl11, frontLeft,      sensorDigitalIn)
#pragma config(Sensor, dgtl12, ballLimit,      sensorDigitalIn)
#pragma config(Motor,  port1,           depositor,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port2,           rightWheel,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           collectionMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor,  port8,           leftWheel,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")

int depositionOn = 0;

int startRight = 0;
int no_of_balls_collected  = 0;
int _sensorDetect;


void orientNorth();
void orientSouth();
void orientEast();
void deposit();
// Compass mapping
/*
N E S W
1 --> direction that the compass is pointing at (yes I flipped it)

North 1000 = 8
North-East 1100 = 12
East 0100 = 4
South-East 0110 = 6
South 0010 =  2
South-West 0011 = 3
West 0001 = 1
North-West 1001 = 9

North >=8
East >=4
South >=2
West >=1
*/
int north[3] = {8,12,9};
int east[3] = {4,12,6};
int south[3] = {2,3,6};
int west[3] = {1,3,9};

// Convert digital compass reading into discrete integer value N E S W
int read_compass(){
	return !SensorValue[compassN] * 8 + !SensorValue[compassE] * 4 + !SensorValue[compassS] * 2 + !SensorValue[compassW] * 1;}

int get_distanceL()
{
	int numberOfReadingsToAverage = 20;
	int totalL = 0;
	int avgL = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

		int distanceL = 29.988 * pow(SensorValue[sharpLeft], -1.173) * 1000 * 5 / 2;
		if (distanceL<10){
			distanceL = 10;
		}
		if (distanceL>80){
			distanceL = 80;
		}
		totalL = totalL + distanceL;
	}

	avgL = totalL/numberOfReadingsToAverage;
	return avgL;
}

int get_distanceR()
{
	int numberOfReadingsToAverage = 20;
	int totalR = 0;
	int avgR = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

		int distanceR = 29.988 * pow(SensorValue[sharpRight], -1.173) * 1000 * 5 / 2;
		if (distanceR<10){
			distanceR = 10;
		}
		if (distanceR>80){
			distanceR = 80;
		}
		totalR = totalR + distanceR;
	}

	avgR = totalR/numberOfReadingsToAverage;
	return avgR;
}

int get_distanceTL()
{
	int numberOfReadingsToAverage = 20;
	int totalTL = 0;
	int avgTL = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

		int distanceTL = 29.988 * pow(SensorValue[sharpTop], -1.173) * 1000 * 5 / 2;
		if (distanceTL<10){
			distanceTL = 10;
		}
		if (distanceTL>80){
			distanceTL = 80;
		}
		totalTL = totalTL + distanceTL;
	}

	avgTL = totalTL/numberOfReadingsToAverage;
	return avgTL;
}

int get_distanceB()
{
	int numberOfReadingsToAverage = 20;
	int totalB = 0;
	int avgB = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){
		int distanceB = 12.08 * pow(SensorValue[sharpShort], -1.058)*1000 * 5/4;
		if (distanceB<4){
			distanceB = 4;}

		if (distanceB>30){
			distanceB = 30;
		}
		totalB = totalB + distanceB;
	}

	avgB = totalB/numberOfReadingsToAverage;
	return avgB;
}

void move_right(int milliSecond)
{
	clearTimer(T1);
	while (time1(T1)<milliSecond)
	{
		motor[rightWheel] = 50;
		motor[leftWheel] = 50;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}


/** move only (without collection) **/

void move_forward(int milliSecond)
{
	clearTimer(T1);

	while (time1(T1)<milliSecond)
	{
		motor[rightWheel] = -120;
		motor[leftWheel] = 110;
		motor[collectionMotor] = 127;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}


void move_back(int milliSecond)
{
	clearTimer(T1);

	while (time1(T1)<milliSecond)
	{
		motor[rightWheel] = 120;
		motor[leftWheel] = -110;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}


void move_left(int milliSecond)
{
	clearTimer(T1);
	while (time1(T1)<milliSecond)
	{
		motor[rightWheel] = -70;
		motor[leftWheel] = -70;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

void stopMC(){
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

void collection_on(){
motor[collectionMotor] = 127;}

void collection_off(){
	motor[collectionMotor] =0;}

//***********

// 1 L TL R
int sensorDetect()
{
	int range = 40;
	int returnVal=1000;
	int avgR = get_distanceR();
	int avgL = get_distanceL();
	int avgTL = get_distanceTL();
	//changing this to avgR instead
	if ((avgR <range ) && (avgR > 10))
	{
		returnVal=returnVal+1;
	}
	if((avgL < range) && (avgL > 10)){
		returnVal=returnVal+100;
	}
	if((avgTL < range) && (avgTL > 10)){
		returnVal=returnVal+10;
	}
	return returnVal;
}

bool topDetect(){
	int topval = get_distanceTL();
	if((topval < 40) && (topval > 10)) return true;
	return false;}

void robot_detected(){
}

bool clockwise_circular_search_right(int milliSecond)
{
	clearTimer(T2);
	while(time1(T2)< milliSecond){
		_sensorDetect = sensorDetect();
		//1 Left Top Right
		if(_sensorDetect==1001){
			move_right(5);
			_sensorDetect = sensorDetect();
			//if (((_sensorDetect-(_sensorDetect%10))/10)%10 == 0){ //Top doesn't detect
			if (topDetect() == false){
				//move_right(5);
				//collection_on();
				clearTimer(T4);
				while (time1(T4) < 2000){
					if (SensorValue[ballLimit] == 0) return true;
					move_forward(50);}
				continue;
			}
			else continue;//top has detected
			//detect with right routine ends here
			}
		else if(_sensorDetect==1100){
			//detected with left
			move_left(200);
			//if (((_sensorDetect-(_sensorDetect%10))/10)%10 == 0){
			if(topDetect()== false){
				//collection_on();
				move_forward(2000);
				return true;}
			else continue; //top has detected
			//detect with left ends here
		}
			else if(_sensorDetect==1101){
			//left and right detect
				switch(read_compass()){
					case 2:
					case 3:
					case 6:
						move_back(750);
						orientNorth();
						break;
					default:
						move_left(200);
				if(topDetect()== false){
					//collection_on();
					move_forward(2000);
					return true;}
					 //top has detected
						break;
				}
			}
			//detect with l and r both done
		move_right(15);
		}
	int exit_search = 0;
	while(true){
		switch(sensorDetect()){
			case 1110:
			case 1011:
			case 1111:
				move_right(10);
				break;
			default:
				exit_search = 1;
				break;
		}
		if (exit_search==1) break;
	}
	return false;
}

bool clockwise_circular_search_left(int milliSecond)
{
	clearTimer(T2);
	while(time1(T2)< milliSecond){
		_sensorDetect = sensorDetect();
		//1 Left Top Right
		if(_sensorDetect==1001){
			move_right(5);
			_sensorDetect = sensorDetect();
			//if (((_sensorDetect-(_sensorDetect%10))/10)%10 == 0){ //Top doesn't detect
			if (topDetect() == false){
				//move_right(5);
				collection_on();
				clearTimer(T4);
				while (time1(T4) < 2000){
					if (SensorValue[ballLimit] == 0) return true;
					move_forward(50);}
				continue;
			}
			else deposit();//top has detected
			//detect with right routine ends here
			}
		else if(_sensorDetect==1100){
			//detected with left
			move_left(200);
			//if (((_sensorDetect-(_sensorDetect%10))/10)%10 == 0){
			if(topDetect()== false){
				collection_on();
				move_forward(2000);
				return true;}
			else deposit(); //top has detected
			//detect with left ends here
		}
			else if(_sensorDetect==1101){
			//left and right detect
				switch(read_compass()){
					case 2:
					case 3:
					case 6:
						move_back(750);
						orientNorth();
						break;
					default:
						move_left(200);
				if(topDetect()== false){
					collection_on();
					move_forward(2000);
					return true;}
				else deposit(); //top has detected
						break;
				}
			}
			//detect with l and r both done
		move_left(15);
		}
	int exit_search = 0;
	while(true){
		switch(sensorDetect()){
			case 1110:
			case 1011:
			case 1111:
				move_right(10);
				break;
			default:
				exit_search = 1;
				break;
		}
		if (exit_search==1) break;
	}
	return false;
}

void orientSouth()
{
	int value = read_compass();
	if (value != 2)
	{
		if ((value == 12) || (value == 4) || (value == 6) || (value == 8))
		{
			//turn right
			while (value != 2)
			{
				move_right(10);
				value = read_compass();
			}
		}
		else
		{
			//turn left
			while (value != 2)
			{
				move_left(10);
				value = read_compass();
			}
		}
	}
}

void orientSouthNewFn()
{
	int value = read_compass();
	if (value != 2){
			while (value != 2)
			{
				move_right(10);
				value = read_compass();
			}
		}
 move_left(200);
}

void orientNorth()
{
	int value = read_compass();
	if (value != 8)
	{
		if ((value == 12) || (value == 4) || (value == 6) || (value == 2))
		{
			//turn right
			while (value != 8)
			{
				move_right(10);
				value = read_compass();
			}
		}
		else
		{
			//turn left
			while (value != 8)
			{
				move_left(10);
				value = read_compass();
			}
		}
	}
}

void orientEast()
{
	int value = read_compass();
	if (value != 4)
	{
		if ((value == 12) || (value == 8) || (value == 1) || (value == 9))
		{
			//turn right
			while (value != 4)
			{
				move_right(10);
				value = read_compass();
			}
		}
		else
		{
			//turn left
			while (value != 4)
			{
				move_left(10);
				value = read_compass();
			}
		}
	}
}

void deposit(){
	int collector_count = 0;
	while (collector_count<100){
		motor[collectionMotor] = 127;
		collector_count +=1;
	}
	motor[collectionMotor] = 0;
	while(SensorValue[encoder]<90){
		motor[depositor] = -50;
	}
	motor[depositor] = 0;
	delay(2000);
	while(SensorValue[encoder]>30){
	motor[depositor] = 25;
	}
	motor[depositor] = 0;
}


task line_detection(){
	int moveTime = 750;
	while(true){
		clearTimer(T3);
		int front_count = 0;
		int back_count = 0;
		while(time1(T3)<10000){
			if (front_count>=3){
				hogCPU();
				move_back(750);
				move_right(1200);
				releaseCPU();
			}
			if (back_count>=3){
				hogCPU();
				move_forward(750);
				move_right(1200);
				releaseCPU();
			}
			if (SensorValue[frontLeft]==0 && depositionOn==0){
				hogCPU();
				move_back(moveTime);
				move_right(200);
				front_count +=1;
				releaseCPU();
			}
			if (SensorValue[frontRight]==0 && depositionOn==0){
				hogCPU();
				move_back(moveTime);
				move_left(200);
				front_count +=1;
				releaseCPU();
			}
			if (SensorValue[backLeft]==0 && depositionOn==0){
				hogCPU();
				move_forward(moveTime);
				move_right(200);
				back_count +=1;
				releaseCPU();
			}
			if (SensorValue[backRight]==0 && depositionOn==0){
				hogCPU();
				move_forward(moveTime);
				move_left(200);
				back_count+=1;
				releaseCPU();
			}
	}
	}
}

void first_ball_path(){
	move_forward(3000);//tune this to 2/3

	if(startRight == 1){
			while(true){
				//if right limit switch pressed
				clockwise_circular_search_left(500); //tune this to do a >90 degree turn and search
				orientNorth();
				move_forward (500);
			}
	}else{
			while(true){
					//if left limit switch pressed
					clockwise_circular_search_right(500);//tune this to do a >90 degree turn and search
					orientNorth();
					move_forward (500);
			}
	}
}

void diamond_path(){
/*	switch(no_of_balls_collected){
		case 5:
		first_ball_path();
		break;
		default:*/

			//move_right(100);
			move_forward(2000);
			clockwise_circular_search_right(2500);
			move_left(100);
			move_forward(2000);
			clockwise_circular_search_right(2500);
			move_left(300);
			move_forward(2000);
			clockwise_circular_search_right(2500);
			move_left(100);
			move_forward(2000);

}

void test_path(){
	//collection_on();
	//move_forward(5000);
	clockwise_circular_search_right(12500);
	//move_right_with_collection(2000);
	//delivery();
}


task ball_deposition(){
	while(true){
		while(depositionOn==0){
			if (SensorValue[ballLimit] == 0){
				depositionOn=1;
				int collector_count =0;
				while (collector_count<100){
				collector_count++;
				motor[collectionMotor] = 127;}
	}
		collection_off();
			continue;
		}
		hogCPU();
		//first orient the robot to face South
		orientSouth();
		//then move back till short sensor gives a particular value
		//disable line detection
		while (true)
		{
			int back_dist = get_distanceB();
			if ((SensorValue[backLeft] == 0 || SensorValue[backRight] == 0)&&(back_dist<=10))
			{
			orientSouth();
			move_back(10);
			stopMC();
			deposit();
				break;
			}
			if (SensorValue[backLeft] == 0 && back_dist>10){
				move_forward(500);
				orientSouth();
			}
			if (SensorValue[backRight] == 0 && back_dist>10){
				move_forward(500);
				orientSouth();
			}
			move_back(10);
		}

		depositionOn = 0;
		no_of_balls_collected++;
    //release ball depending on servo or motor
		releaseCPU();
		collection_on();
		move_forward(2000);
	}
}

task main()
{
while(true){
	//startTask(line_detection);
//	//move_forward(20000);
//collection_on();
startTask(ball_deposition);
	move_forward(3000);
	clockwise_circular_search_right(5000);
	move_left(100);
	move_forward(2000);
	clockwise_circular_search_right(2500);
	move_left(300);
	move_forward(2000);
	clockwise_circular_search_right(2500);
	move_left(100);
	move_forward(2000);}
//	//test_path();
//	//clockwise_circular_search_right(2500);
//}
}
