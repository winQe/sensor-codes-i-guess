#pragma config(Sensor, in1,    sharpRight,     sensorAnalog)
#pragma config(Sensor, in2,    sharpShort,     sensorAnalog)
#pragma config(Sensor, in4,    sharpTop,       sensorAnalog)
#pragma config(Sensor, in5,    sharpLeft,      sensorAnalog)
#pragma config(Sensor, in7,    reflective,     sensorAnalog)
#pragma config(Sensor, in8,    line_a,         sensorAnalog)
#pragma config(Sensor, dgtl1,  line_d,         sensorDigitalIn)
#pragma config(Sensor, dgtl7,  compassN,       sensorDigitalIn)
#pragma config(Sensor, dgtl8,  compassE,       sensorDigitalIn)
#pragma config(Sensor, dgtl9,  compassS,       sensorDigitalIn)
#pragma config(Sensor, dgtl10, compassW,       sensorDigitalIn)
#pragma config(Sensor, dgtl11, limit_power,    sensorDigitalIn)
#pragma config(Motor,  port2,           rightWheel,    tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor,  port3,           leftWheel,     tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard							 !!//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("DebugStream")
int distanceR = 0, distanceL = 0, distanceT = 0;
int shortDistance = 0;
// int detectsLine = 0;
int sawBall = 0;
int ball_detected_code = 0;

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
 int west[3] = {1,6,9};

/* Struct to store if boundary line is detected and its direction
detected
1 = line detected
0 = no boundary detected
direction
0 = any other direction
1 = south line (aka the end of the arena)
2 = north line (during deposition)
*/

typedef struct{
int detected;
int direction;
} line;

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

void detectsLine(line &boundary){
    boundary.detected = SensorValue[line_d];
    if (check_south(read_compass())) {boundary.direction=1;}
  	else if (check_north(read_compass())) {boundary.direction=2;}
    else boundary.direction=0;
}

void move_backward(int time)
{
    int timeSteps = 0;
    while (true)
    {
        timeSteps++;
        motor[rightWheel] = -92;
        motor[leftWheel] = 110;
        delay(50);
        if (timeSteps > time * 20)
        {
            break;
        }
    }
}
void move_forward(int time)
{
    int timeSteps = 0;
    while (true)
    {
        timeSteps++;
        motor[rightWheel] = 92;
        motor[leftWheel] = -110;
        if (!SensorValue[line_d])
        {
            move_backward(2);
            break;
        }
        delay(50);
        if (timeSteps > time * 20)
        {
            break;
        }
    }
}

void move_right(int time)
{
    int timeSteps = 0;
    while (true)
    {
        timeSteps++;
        motor[rightWheel] = -50;
        motor[leftWheel] = -50;
        delay(100);
        if (timeSteps > time * 10)
        {
            break;
        }
    }
}

//Orient to any direction (refer to compass mapping), turns right until correct direction
void orient(int direction)
{
	while (true){
	move_right(1);
		if (read_compass() == direction) {
			  motor[rightWheel] = 0;
        motor[leftWheel] = 0;
			break;}
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
void clockwise_circular_search()
{ //int scale, int tuneToCircle){
    for (int i = 0; i <= 1; i++)
    {
        move_right(5);
        //if(ball_detected_handler(ball_detect())){collect_ball();break;};
    }
}

task main()
{
    clearDebugStream();
    //move_right(10);
    //move_forward(60);
    //clockwise_circular_search();
    //move_backward(5);
    //move_right(2);
    //move_left(2);
    //stop_motion(5);
}
