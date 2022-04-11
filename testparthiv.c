#pragma config(Sensor, in1, sharpShort, sensorAnalog)
#pragma config(Sensor, in5, sharpRight, sensorAnalog)
#pragma config(Sensor, in2, sharpLeft, sensorAnalog)
#pragma config(Sensor, in8, sharpTop, sensorAnalog)
#pragma config(Sensor, dgtl1, backLeft, sensorDigitalIn)
#pragma config(Sensor, dgtl2, backRight, sensorDigitalIn)
#pragma config(Sensor, dgtl3, frontRight, sensorDigitalIn)
#pragma config(Sensor, dgtl4, encoder, sensorQuadEncoder)
#pragma config(Sensor, dgtl7, compassN, sensorDigitalIn)
#pragma config(Sensor, dgtl8, compassE, sensorDigitalIn)
#pragma config(Sensor, dgtl9, compassS, sensorDigitalIn)
#pragma config(Sensor, dgtl10, compassW, sensorDigitalIn)
#pragma config(Sensor, dgtl11, frontLeft, sensorDigitalIn)
#pragma config(Sensor, dgtl12, ballLimit, sensorDigitalIn)
#pragma config(Motor, port1, depositor, tmotorVex393_HBridge, openLoop)
#pragma config(Motor, port2, rightWheel, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port3, collectionMotor, tmotorVex393_MC29, openLoop)
#pragma config(Motor, port8, leftWheel, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")

#define FIRST_MOVE_FORWARD_DURATION 4000
#define RANGE 50

int depositionOn = 0;

int startRight = 0;
int _sensorDetect;

float volt = 0;
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
int north[3] = {8, 12, 9};
int east[3] = {4, 12, 6};
int south[3] = {2, 3, 6};
int west[3] = {1, 3, 9};

// Convert digital compass reading into discrete integer value N E S W
int read_compass()
{
	return !SensorValue[compassN] * 8 + !SensorValue[compassE] * 4 + !SensorValue[compassS] * 2 + !SensorValue[compassW] * 1;
}

int get_distanceL()
{
	int numberOfReadingsToAverage = 20;
	int totalL = 0;
	int avgL = 0;
	for (int i = 0; i < numberOfReadingsToAverage; i++)
	{

		int distanceL = 29.988 * pow(SensorValue[sharpLeft], -1.173) * 1000 * 5 / 2;
		if (distanceL < 10)
		{
			distanceL = 10;
		}
		if (distanceL > 80)
		{
			distanceL = 80;
		}
		totalL = totalL + distanceL;
	}

	avgL = totalL / numberOfReadingsToAverage;
	return avgL;
}

int get_distanceR()
{
	int numberOfReadingsToAverage = 20;
	int totalR = 0;
	int avgR = 0;
	for (int i = 0; i < numberOfReadingsToAverage; i++)
	{

		int distanceR = 29.988 * pow(SensorValue[sharpRight], -1.173) * 1000 * 5 / 2;
		if (distanceR < 10)
		{
			distanceR = 10;
		}
		if (distanceR > 80)
		{
			distanceR = 80;
		}
		totalR = totalR + distanceR;
	}

	avgR = totalR / numberOfReadingsToAverage;
	return avgR;
}

int get_distanceTL()
{
	int numberOfReadingsToAverage = 20;
	int totalTL = 0;
	int avgTL = 0;
	for (int i = 0; i < numberOfReadingsToAverage; i++)
	{

		int distanceTL = 29.988 * pow(SensorValue[sharpTop], -1.173) * 1000 * 5 / 2;
		if (distanceTL < 10)
		{
			distanceTL = 10;
		}
		if (distanceTL > 80)
		{
			distanceTL = 80;
		}
		totalTL = totalTL + distanceTL;
	}

	avgTL = totalTL / numberOfReadingsToAverage;
	return avgTL;
}

int get_distanceB()
{
	int numberOfReadingsToAverage = 20;
	int totalB = 0;
	int avgB = 0;
	for (int i = 0; i < numberOfReadingsToAverage; i++)
	{
		int distanceB = 12.08 * pow(SensorValue[sharpShort], -1.058) * 1000 * 5 / 4;
		if (distanceB < 4)
		{
			distanceB = 4;
		}

		if (distanceB > 30)
		{
			distanceB = 30;
		}
		totalB = totalB + distanceB;
	}

	avgB = totalB / numberOfReadingsToAverage;
	return avgB;
}

void move_right(int milliSecond)
{
	clearTimer(T1);
	while (time1(T1) < milliSecond)
	{
		motor[rightWheel] = 50;
		motor[leftWheel] = 50;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

void move_right_search(int milliSecond)
{
	clearTimer(T1);
	while (time1(T1) < milliSecond)
	{
		motor[rightWheel] = 30;
		motor[leftWheel] = 45;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

/** move only (without collection) **/

void move_forward(int milliSecond)
{
	clearTimer(T1);
		motor[collectionMotor] = 127;

	while (time1(T1) < milliSecond)
	{
		motor[rightWheel] = -127;
		motor[leftWheel] = 90;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

void move_back(int milliSecond)
{
	//to be tuned
	clearTimer(T1);
	while (time1(T1) < milliSecond)
	{
		motor[rightWheel] = 100;
		motor[leftWheel] = -100;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

void move_left(int milliSecond)
{
	clearTimer(T1);

	while (time1(T1) < milliSecond)
	{
		motor[rightWheel] = -70;
		motor[leftWheel] = -70;
	}
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}

void stopMC()
{
	motor[rightWheel] = 0;
	motor[leftWheel] = 0;
}



//***********

// 1 L TL R
int sensorDetect()
{
	int returnVal = 1000;
	int avgR = get_distanceR();
	int avgL = get_distanceL();
	int avgTL = get_distanceTL();
	// changing this to avgR instead
	if ((avgR < RANGE) && (avgR > 10))
	{
		returnVal = returnVal + 1;
	}
	if ((avgL < RANGE) && (avgL > 10))
	{
		returnVal = returnVal + 100;
	}
	if ((avgTL < RANGE) && (avgTL > 10))
	{
		returnVal = returnVal + 10;
	}
	return returnVal;
}

bool topDetect()
{
	int topval = get_distanceTL();
	if ((topval < RANGE) && (topval > 10))
		return true;
	return false;
}

bool clockwise_circular_search_right(int milliSecond)
{
	clearTimer(T2);
	while (time1(T2) < milliSecond)
	{
		move_right(100);
		_sensorDetect = sensorDetect();
		// 1 Left Top Right
		if (_sensorDetect == 1001)
		{
			if (sensorDetect() == _sensorDetect)
			{
				move_right(5);
				if (topDetect() == false)
				{
					for (int tempIndex_ = 0; tempIndex_ < 4; tempIndex_++)
					{
						if (SensorValue[ballLimit] == 0)
							return true;
						move_forward(500);
					}
					continue;
				}
				else {
					continue;
				} // top has detected
				// detect with right routine ends here
			}
			else
			{
				continue;
			}
		}
		else if (_sensorDetect == 1100)
		{
			if (sensorDetect() == _sensorDetect){
				// detected with left
				move_left(200);
			if (topDetect() == false)
			{
				for (int tempIndex_ = 0; tempIndex_ < 4; tempIndex_++)
					{
						if (SensorValue[ballLimit] == 0)
							return true;
						move_forward(500);
					}
					continue;
			}
			else
				continue; // top has detected
			// detect with left ends here
			}
			
		}
		else if (_sensorDetect == 1101)
		{
			// left and right detect
			switch (read_compass())
			{
			case 8:
			case 12:
			case 9:
				move_back(750);
				orientSouth();
				break;
			default:
				move_left(200);
				for (int tempIndex_ = 0; tempIndex_ < 4; tempIndex_++)
					{
						if (SensorValue[ballLimit] == 0)
							return true;
						move_forward(500);
					}
					continue;
				
			}
		}
		// detect with l and r both done
	}
// 	int exit_search = 0;
// 	while (true)
// 	{
// 		switch (sensorDetect())
// 		{
// 		case 1110:
// 		case 1011:
// 		case 1111:
// 			move_right(10);
// 			break;
// 		default:
// 			exit_search = 1;
// 			break;
// 		}
// 		if (exit_search == 1)
// 			break;
// 	}
 	return false;
}

void orientSouth()
{
	int value = read_compass();
	if (value != 2)
	{
		if ((value == 12) || (value == 4) || (value == 6) || (value == 8))
		{
			// turn right
			while (value != 2)
			{
				move_right(10);
				value = read_compass();
			}
		}
		else
		{
			// turn left
			while (value != 2)
			{
				move_left(10);
				value = read_compass();
			}
		}
	}
}


void orientNorth()
{
	int value = read_compass();
	if (value != 8)
	{
		if ((value == 12) || (value == 4) || (value == 6) || (value == 2))
		{
			// turn right
			while (value != 8)
			{
				move_right(10);
				value = read_compass();
			}
		}
		else
		{
			// turn left
			while (value != 8)
			{
				move_left(10);
				value = read_compass();
			}
		}
	}
}

void orientNorthEast()
{
    int value = read_compass();
    if (value != 12)
    {
        if ((value == 3) || (value == 1) || (value == 9) || (value == 8))
        {
            // turn right
            while (value != 12)
            {
                move_right(10);
                value = read_compass();
            }
        }
        else
        {
            // turn left
            while (value != 12)
            {
                move_left(10);
                value = read_compass();
            }
        }
    }
}

void orientSouthEast()
{
    int value = read_compass();
    if (value != 6)
    {
        if ((value == 12) || (value == 4) || (value == 9) || (value == 8))
        {
            // turn right
            while (value != 6)
            {
                move_right(10);
                value = read_compass();
            }
        }
        else
        {
            // turn left
            while (value != 6)
            {
                move_left(10);
                value = read_compass();
            }
        }
    }
}

void orientSouthWest()
{
    int value = read_compass();
    if (value != 3)
    {
        if ((value == 12) || (value == 4) || (value == 6) || (value == 2))
        {
            // turn right
            while (value != 3)
            {
                move_right(10);
                value = read_compass();
            }
        }
        else
        {
            // turn left
            while (value != 3)
            {
                move_left(10);
                value = read_compass();
            }
        }
    }
}

void orientNorthWest()
{
    int value = read_compass();
    if (value != 9)
    {
        if ((value == 1) || (value == 3) || (value == 6) || (value == 2))
        {
            // turn right
            while (value != 9)
            {
                move_right(10);
                value = read_compass();
            }
        }
        else
        {
            // turn left
            while (value != 9)
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
            // turn right
            while (value != 4)
            {
                move_right(10);
                value = read_compass();
            }
        }
        else
        {
            // turn left
            while (value != 4)
            {
                move_left(10);
                value = read_compass();
            }
        }
    }
}

void orientWest()
{
    int value = read_compass();
    if (value != 1)
    {
        if ((value == 4) || (value == 6) || (value == 2) || (value == 3))
        {
            // turn right
            while (value != 1)
            {
                move_right(10);
                value = read_compass();
            }
        }
        else
        {
            // turn left
            while (value != 1)
            {
                move_left(10);
                value = read_compass();
            }
        }
    }
}

void turnOneEighty(){
    int current_val = read_compass();

    int val_to_reach;
    
    if(current_val==8){
        val_to_reach = 2;
    }else if(current_val==2){
        val_to_reach = 8;
    }else if(current_val==12){
        val_to_reach = 3;
    }else if(current_val==3){
        val_to_reach = 12;
    }else if(current_val==6){
        val_to_reach = 9;
    }else if(current_val==9){
        val_to_reach = 6;
    }else if(current_val==1){
        val_to_reach = 4;
    }else if(current_val==4){
        val_to_reach = 1;
    }

    if(val_to_reach==8){
        orientNorth();
    }else if (val_to_reach==2){
        orientSouth();
    }else if (val_to_reach==12){
        orientNorthEast();
    }else if (val_to_reach==3){
        orientSouthWest();
    }else if (val_to_reach==6){
        orientSouthEast();
    }else if (val_to_reach==9){
        orientNorthWest();
    }else if (val_to_reach==1){
        orientWest();
    }else if (val_to_reach==4){
        orientEast();
    }
    
}

void deposit()
{
	clearTimer(T1);
	while (SensorValue[encoder] <60 )
	{
		motor[depositor] = 30;
	}
	while (SensorValue[encoder] >-100 )
	{
		motor[depositor] = -30;
	}
	motor[depositor] = 0;
	while(time1(T1)<3000)
	{
		motor[collectionMotor] = 127;
	}
	motor[collectionMotor] = 0;
	while (SensorValue[encoder] <-10 )
	{
		motor[depositor] = 20;
	}
	motor[depositor] = 0;
}

task line_detection()
{
	int moveTime = 750;
	while (true)
	{
		clearTimer(T3);
		int boundary_count = 0;

		while (time1(T3) < 6000)
		{
			if (boundary_count >= 2 && (SensorValue[frontLeft] == 0 || SensorValue[frontRight] == 0 ))
			{
				hogCPU();
				move_back(750);
				turnOneEighty();
				//move_right(1200);// Turn 180 degree
				releaseCPU();
				break;

			}

			if (boundary_count >= 2 && (SensorValue[backLeft] == 0 || SensorValue[backRight] == 0 ))
			{

				hogCPU();
				move_forward(750);
				turnOneEighty();
				//move_right(1200);//Turn 180
				releaseCPU();
				break;
			}

			if (SensorValue[frontLeft] == 0 && depositionOn == 0)
			{
				hogCPU();
				move_back(moveTime);
				move_right(200);
				boundary_count += 1;
				releaseCPU();
			}
			if (SensorValue[frontRight] == 0 && depositionOn == 0)
			{
				hogCPU();
				move_back(moveTime);
				move_left(200);
				boundary_count += 1;
				releaseCPU();
			}
			if (SensorValue[backLeft] == 0 && depositionOn == 0)
			{
				hogCPU();
				move_forward(moveTime);
				move_right(200);
				boundary_count += 1;
				releaseCPU();
			}
			if (SensorValue[backRight] == 0 && depositionOn == 0)
			{
				hogCPU();
				move_forward(moveTime);
				move_left(200);
				boundary_count += 1;
				releaseCPU();
			}
		}
	}
}


task ball_deposition()
{
	while (true)
	{
		while (depositionOn == 0)
		{
			if (SensorValue[ballLimit] == 0)
			{ // Limit switch is pressed
				depositionOn = 1;
			}
		}
		
		motor[collectionMotor] = 0;
		hogCPU();
		// first orient the robot to face South
		orientSouth();
		// then move back till short sensor gives a particular value
		// disable line detection
		while (true)
		{
			int back_dist = get_distanceB();
			int timez = 800;
			if ((SensorValue[backLeft] == 0 || SensorValue[backRight] == 0) && (back_dist <= 10))
			{
				orientSouth();
				move_back(50);
				stopMC();
				SensorValue[encoder] = 0;
				deposit();
				depositionOn = 0;
				move_forward(FIRST_MOVE_FORWARD_DURATION);
				break;
			}
			if (SensorValue[backLeft] == 0 && back_dist > 10)
			{
				move_forward(timez);
				orientSouth();
			}
			if (SensorValue[backRight] == 0 && back_dist > 10)
			{
				move_forward(timez);
				orientSouth();
			}
			if ((SensorValue[frontLeft] == 0 || SensorValue[frontRight] == 0) && back_dist > 10)
			{
				move_back(timez);
				orientSouth();
			}
			move_back(10);
		}		
		releaseCPU();
	}
}

task main()
{
	turnOneEighty();

		//  startTask(line_detection);
		//  startTask(ball_deposition);
		 clockwise_circular_search_right(12000);
		//  move_forward(FIRST_MOVE_FORWARD_DURATION);

	while (false)
	{

		for (int southCount = 0; southCount<2; southCount++){
			orientSouth();
			move_forward(2000);
			clockwise_circular_search_right(4000);

		}

		for (int northCount = 0; northCount<2; northCount++){
			orientNorth();
			move_forward(2000);
			clockwise_circular_search_right(4000);
		}


		
	}
}