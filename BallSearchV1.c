#pragma config(Sensor, in1,    sharpRight,     sensorAnalog)
#pragma config(Sensor, in2,    sharpShort,     sensorAnalog)
#pragma config(Sensor, in4,    sharpTop,       sensorAnalog)
#pragma config(Sensor, in5,    sharpLeft,      sensorAnalog)
#pragma config(Sensor, in7,    backLeftanal,   sensorAnalog)
#pragma config(Sensor, in8,    line_a,         sensorAnalog)
#pragma config(Sensor, dgtl1,  backLeft,       sensorNone)
#pragma config(Sensor, dgtl2,  frontLeft,      sensorDigitalIn)
#pragma config(Sensor, dgtl3,  frontRight,     sensorDigitalIn)
#pragma config(Sensor, dgtl4,  backRight,      sensorDigitalIn)
#pragma config(Sensor, dgtl7,  compassN,       sensorDigitalIn)
#pragma config(Sensor, dgtl8,  compassE,       sensorDigitalIn)
#pragma config(Sensor, dgtl9,  compassS,       sensorDigitalIn)
#pragma config(Sensor, dgtl10, compassW,       sensorDigitalIn)
#pragma config(Sensor, dgtl11, limit_power,    sensorDigitalIn)
#pragma config(Motor,  port2,           rightWheel,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftWheel,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("DebugStream")

//TO DO LATER REDUCE THE GLOBAL VARIABLES
int _sensorDetect;
int distanceR = 0, distanceL = 0, distanceTL = 0;
int shortDistance = 0;
int detectsLine = 0;
int sawBall = 0;
int ball_detected_code = 0;
int avgRglobal;
int avgLglobal, avgTLglobal;
int check_if_exit = 0;

int numPivots = 0;

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
 North-West 10001 = 9

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

int check_south(int val){
for(int i = 0; i < 3; i++){
  if(south[i] == val) return 1;}
  return 0;}

int check_north(int val){
for(int i = 0; i < 3; i++){
  if(north[i] == val) return 1;}
  return 0;}

int get_distanceL()
{
	int numberOfReadingsToAverage = 50;
		int totalL = 0;
		int avgL = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

	    distanceL = 29.988 * pow(SensorValue[sharpLeft], -1.173) * 1000 * 5 / 2;
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
	int numberOfReadingsToAverage = 50;
		int totalR = 0;
		int avgR = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

	   distanceR = 29.988 * pow(SensorValue[sharpRight], -1.173) * 1000 * 5 / 2;
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
	int numberOfReadingsToAverage = 50;
		int totalTL = 0;
		int avgTL = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

	    distanceTL = 29.988 * pow(SensorValue[sharpTop], -1.173) * 1000 * 5 / 2;
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

/*void move_forward(int milliSecond)
{
	clearTimer(T1);

    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = -120;
        motor[leftWheel] = 110;
    }
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
}*/
void move_forward(int milliSecond)
{
	clearTimer(T1);

    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = -50;
        motor[leftWheel] = 40;
    }
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
}

void move_back(int milliSecond)
{
	clearTimer(T1);

    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = 92;
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

void move_fcw(int milliSecond)
{
	clearTimer(T1);

    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = -50;
        motor[leftWheel] = 127;
    }
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
}

void move_bccw(int milliSecond)
{
	clearTimer(T1);

    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = 127;
        motor[leftWheel] = -50;
    }
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
}

int sensorDetect()
{
		int returnVal=1000;
    avgRglobal = get_distanceR();
    avgLglobal = get_distanceL();
    avgTLglobal = get_distanceTL();
    //changing this to avgR instead
    if ((avgRglobal < 70) && (avgRglobal > 69))
    {
        returnVal=returnVal+1;
    }
    if((avgLglobal < 70) && (avgLglobal > 69)){
   			returnVal=returnVal+100;
  	}
  	if((avgTLglobal < 70) && (avgTLglobal > 69)){
  		returnVal=returnVal+10;
  	}
    return returnVal;
}

bool clockwise_circular_search_right(int milliSecond)
{
	clearTimer(T2);

  while(time1(T2)< milliSecond){
  	_sensorDetect = sensorDetect();
  	if (_sensorDetect!=1000){
  		writeDebugStreamLine("miss lee is the root of all our problems (SOMETHING IS DETECTING)");
  	}
  	bool _tempReturn;
  	//rotates right for 100ms
	  move_right(60);
	  //and pause to scan
	  if (_sensorDetect==1000)
	  	{
	  		//return false;
	  		//break and return true if sees something
	  	}
	  else if(_sensorDetect==1001){
	  //detected with right sensor
	  writeDebugStreamLine("RIGHT DETECTED");
	  /*_tempReturn = clockwise_circular_search_right(2000);
	  if(_tempReturn==true){
	  	return true;
	  	}*/
	  move_right(50);
	  move_forward(500);
	  return true;
	  //detect with right routine ends here
	} else if(_sensorDetect==1100){
		//detected with left
		writeDebugStreamLine("LEFT DETECTED");
		move_left(200);
		move_forward(500);
		return true;
		//detect with left ends here
	}
	// else if (_sensorDetect>=1100){
	// 	//if top detects, no matter what else, don't move towards it

	// }
	else if (_sensorDetect == 1011){
		//if both L and R - check if it is deposition area (if compass is E or NE or N)
		//if (read_compass() ==
	}
	else if (_sensorDetect==1010){
	//only top sensor detects?

	//detect with top handled
	} else if(_sensorDetect==1101){
	//left and right detect

	//detect with l and r both done
} else if(_sensorDetect==1110){
	//detected with left bottom and top - robot detected

	//detect robot handled
} else if(_sensorDetect==1011){
	//detected with right bottom and left top??

	//lb and rt detect handle ends here
} else if(_sensorDetect==1111){
	//detect with all sensors

	//detect with all sensors ends here
} else if(_sensorDetect==1010){
	//detect with only top sensor

	//detect with only top sensor ended
}


    //else return false at end of sweep time
}
return false;
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
                move_right(100);
                value = read_compass();
            }
        }
        else
        {
            //turn left
            while (value != 8)
            {
                move_left(100);
                value = read_compass();
            }
        }
    }
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
                move_right(100);
                value = read_compass();
            }
        }
        else
        {
            //turn left
            while (value != 2)
            {
                move_left(100);
                value = read_compass();
            }
        }
    }
}


void detectBall()
{

//	move_forward(1000);
	while (true){
		sawBall=0;
		while (sawBall==0){
			bool ballDetected = clockwise_circular_search_right(50000);
			writeDebugStreamLine("EXITED OUT OF THE clockwise_circular_search_right");
			if (ballDetected){
				sawBall = 1;
				move_right(500);
				move_forward(1000);
				break;
			}
			else {
				//testing figure eight pattern
				if ((numPivots == 0)){
					//rotate right 45
					move_right(50);
				}
				else if (numPivots%4 == 0){
					//if multiple of 4 and not 0
					//rotate right 90
					move_right(50);
				}
				else{
					//rotate left 90
					move_left(50);
				}

			}
			//move foward and start scan
			move_forward(2000);
			numPivots++;
			//loop back to top and start scan
			//delay(10000);
		}
	}
		/*
		if (ballDetected){
			move_forward(100);
			move_back(100);
			move_forward(100);
			move_back(100);
			move_forward(100);
			move_back(100);
			break;
		}
	}


	/*
    for (int i = 0; i <= 5; i++)
    {
        move_forward(2); //move forward
        bool ballDetected = clockwise_circular_search();
        if (ballDetected)
        {
            sawBall = 3;
            break;
        }
        //if(ball_detected_handler(ball_detect())){collect_ball();break;};
    }
    */
}

/*task line_detection(){
	while(true){
    if (SensorValue[frontLeft]==0 && SensorValue[backLeft] ==0){
        hogCPU();
        //writeDebugStreamLine("LEFT LINE DETECTED");
        move_right(1000);
        releaseCPU();
    }
    if (SensorValue[frontRight]==0 && SensorValue[backRight] ==0){
        hogCPU();
        //writeDebugStreamLine("RIGHT LINE DETECTED");
        move_left(1000);
        releaseCPU();
    }
    else if (SensorValue[frontLeft]==0 || SensorValue[frontRight] == 0){
        hogCPU();
        //writeDebugStreamLine("FRONT LINE DETECTED");
    	move_back(1000);
    	releaseCPU();}
    else if (SensorValue[backLeft]==0 || SensorValue[backRight]==0){
        hogCPU();
        //writeDebugStreamLine("BACK LINE DETECTED");
    	move_forward(1000);
    	releaseCPU();}
	}
}*/


task line_detection(){
	int moveTime = 750;
	while(true){
    if (SensorValue[frontLeft]==0){
        hogCPU();
        move_bccw(moveTime);
        releaseCPU();
        //writeDebugStreamLine("FRONT LEFT LINE DETECTED");
    }
    if (SensorValue[frontRight]==0){
        hogCPU();
        move_bccw(moveTime);
        releaseCPU();
				//writeDebugStreamLine("FRONT RIGHT LINE DETECTED");
        }
    if (SensorValue[backLeftanal]<=1000){
        hogCPU();
        move_fcw(moveTime);
        releaseCPU();
        //writeDebugStreamLine("BACK LEFT LINE DETECTED %d",SensorValue[backLeftanal]);
        }
    if (SensorValue[backRight]==0){
        hogCPU();
        move_fcw(moveTime);
        releaseCPU();
 				//writeDebugStreamLine("BACK RIGHT LINE DETECTED");
        }
  }
}


void diamond_path(){
    move_right(400);
    move_forward(2000);
    move_right(2500);
    move_left(400);
    move_forward(2000);
    move_right(2500);
    move_left(600);
    move_forward(2000);
    move_right(2500);
    move_left(400);
    move_forward(2000);
}

task main()
{
    clearDebugStream();
    writeDebugStreamLine("STARTING ROBOT");
    //move_bccw(1000);
    startTask(line_detection);
    diamond_path();
    //clockwise_circular_search_right(2500);
    //detectBall();
}

/*
void move_backward(int time){
    int timeSteps = 0;
	while(True){
	timeSteps++;
    motor[rightWheel] = -50;
    motor[leftWheel] = 50;
    delay(100);
    if(timeSteps>time*10){
    	break;
    }
  }
}

void stop_motion(int time){
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
    delay(time*1000);
}


void move_left(){
    int timeSteps = 0;
	while(True){
	timeSteps++;
    motor[rightWheel] = 50;
    motor[leftWheel] = 50;
    delay(100);
    if(timeSteps>time*10){
    	break;
    }
  }
}

int * get_distance(){
    distanceL = 29.988 * pow(SensorValue[sharpLeft],-1.173) *1000 * 5/2;
    distanceR = 29.988 * pow(SensorValue[sharpRight],-1.173) *1000 * 5/2;
	distanceT = 29.988 * pow(SensorValue[sharpTop],-1.173) *1000 * 5/2;

    shortDistance = 12.08 * pow(SensorValue[sharpShort], -1.058)*1000 * 5/4;

    int distVals[4];
    distVals[0] = distanceL;
    distVals[1] = distanceR;
    distVals[2] = distanceT;
    distVals[3] = shortDistance;

//    printf("got distance");
    return distVals;
 }

void initial_strategy(bool lr){
    move_forward(5);
    if (lr){
    move_left(2);
    } else if (!(lr)){
        move_right(2);
    }
    move_forward(3);
}

int ball_detect(){//todo
    //int returned is code for whether ball is detected, and if so, on left, right, or using short dist sensor
    sensors = get_distance();
    //todo
}

int collect_ball(int ball_detected_code){//todo
}

void deposit_ball(){//todo

}

bool ball_detected_handler(int ball_detected_state){//todo
    //returns true if ball is detected
}

void eight_pattern_search(int scale){
    for (int i==0;i<1;i++){
        move_left(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_right(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_right(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_right(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_right(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_left(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_left(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_left(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_left(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
        move_forward(scale);
        if(ball_detected_handler(ball_detect())){collect_ball();break;};
    }
}
*/
