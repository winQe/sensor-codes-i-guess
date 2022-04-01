#pragma config(Sensor, in1,		 sharpRight,		 sensorAnalog)
#pragma config(Sensor, in2,		 sharpShort,		 sensorAnalog)
#pragma config(Sensor, in4,		 sharpTop,			 sensorAnalog)
#pragma config(Sensor, in5,		 sharpLeft,			 sensorAnalog)
#pragma config(Sensor, in7,		 reflective,		 sensorAnalog)
#pragma config(Sensor, in8,    line_a,         sensorAnalog)
#pragma config(Sensor, dgtl1,  line_d,         sensorDigitalIn)
#pragma config(Sensor, dgtl11, limit_power,		 sensorDigitalIn)
#pragma config(Motor,	 port2,	 rightWheel,		 tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,	 port3,	 leftWheel,		 tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("DebugStream")
int distanceR = 0, distanceL = 0, distanceT = 0;
int shortDistance = 0;
int detectsLine = 0;
int sawBall = 0;
int robot_start;
int robot_end;
int count;
int ball_detected_code = 0;
char state[50];

/*bool line_detected(){
    bool line_detection = SensorValue[line_d];
    return (line_detection);
}*/
void move_backward(int time){
	int timeSteps = 0;
	while(True){
	timeSteps++;
    motor[rightWheel] = -92;
    motor[leftWheel] = 110;
    delay(50);
    if(timeSteps>time*20){
    	break;
    }
  }
}
void move_forward(int time){
	int timeSteps = 0;
	while(True){
	timeSteps++;
    motor[rightWheel] = 92;
    motor[leftWheel] = -110;
    if (!SensorValue[line_d]){
    	move_backward(2);
      break;
    }
    delay(50);
    if(timeSteps>time*20){
    	break;
    }
  }
}

void move_right(int time){
    int timeSteps = 0;
	while(True){
	timeSteps++;
    motor[rightWheel] = -50;
    motor[leftWheel] = -50;
    delay(100);
    if(timeSteps>time*10){
    	break;
    }
  }
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
void clockwise_circular_search(){//int scale, int tuneToCircle){
    for(int i=0;i<=1;i++){
        move_right(5);
        //if(ball_detected_handler(ball_detect())){collect_ball();break;};
    }
}

 task main(){
    clearDebugStream();
    //move_forward(60);
    clockwise_circular_search();
    //move_backward(5);
    //move_right(2);
    //move_left(2);
    //stop_motion(5);
 }