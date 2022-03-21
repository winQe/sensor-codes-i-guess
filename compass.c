#pragma config(Sensor, in1, sharpRight, sensorAnalog)
#pragma config(Sensor, in2, sharpShort, sensorAnalog)
#pragma config(Sensor, in4, sharpTop, sensorAnalog)
#pragma config(Sensor, in5, sharpLeft, sensorAnalog)
#pragma config(Sensor, in7, reflective, sensorAnalog)
#pragma config(Sensor, in8, line_a, sensorAnalog)
#pragma config(Sensor, dgtl1, line_d, sensorDigitalIn)
#pragma config(Sensor, dgtl7, compassN, sensorDigitalIn)
#pragma config(Sensor, dgtl8, compassE, sensorDigitalIn)
#pragma config(Sensor, dgtl9, compassS, sensorDigitalIn)
#pragma config(Sensor, dgtl10, compassW, sensorDigitalIn)
#pragma config(Sensor, dgtl11, limit_power, sensorDigitalIn)
#pragma config(Motor, port2, rightWheel, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port3, leftWheel, tmotorVex393_MC29, openLoop, reversed)
#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("DebugStream")
int distanceR = 0, distanceL = 0, distanceT = 0;
int shortDistance = 0;
// int detectsLine = 0;
int sawBall = 0;
int ball_detected_code = 0;
int done = 0;

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
int north[3] = {8, 12, 9};
int east[3] = {4, 12, 6};
int south[3] = {2, 3, 6};
int west[3] = {1, 3, 9};


int read_compass()
{
    return !SensorValue[compassN] * 8 + !SensorValue[compassE] * 4 + !SensorValue[compassS] * 2 + !SensorValue[compassW] * 1;
}

int check_south(int val)
{
    for (int i = 0; i < 3; i++)
    {
        if (south[i] == val)
            return 1;
    }
    return 0;
}

int check_north(int val)
{
    for (int i = 0; i < 3; i++)
    {
        if (north[i] == val)
            return 1;
    }
    return 0;
}

/*void detectsLine(line &boundary){
    boundary.detected = SensorValue[line_d];
    if (check_south(read_compass())) {boundary.direction=1;}
  	else if (check_north(read_compass())) {boundary.direction=2;}
    else boundary.direction=0;
}*/

// Function to detect line and which line it is
/* Doesn't detect line return 0
    Detects south line return 1
    Detects north line return 2
    Detect East line return 3
    Detects West line return 4 */
int detectsLine()
{
    if (SensorValue[line_d] == 1)
    {
        if (check_south(read_compass()))
            return 1;
        else if (check_north(read_compass()))
            return 2;
        else if (read_compass() == 4)
            return 3;
        else if (read_compass() == 1)
            return 4;
    }
    return 0;
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

void move_right(int milliSecond)
{
	clearTimer(T1);
    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = -50;
        motor[leftWheel] = -50;
    }
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
}

void move_left(int milliSecond)
{
	clearTimer(T1);
    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = 30;
        motor[leftWheel] = 30;
    }
    motor[rightWheel] = 0;
    motor[leftWheel] = 0;
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

task main()
{
    clearDebugStream();
    orientRobot();
}
