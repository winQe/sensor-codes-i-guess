//detect balls robotc

#pragma config(Sensor, in1, sharpRight, sensorAnalog)
#pragma config(Sensor, in2, sharpShort, sensorAnalog)
#pragma config(Sensor, in4, sharpTop, sensorAnalog)
#pragma config(Sensor, in5, sharpLeft, sensorAnalog)
#pragma config(Sensor, in7, reflective, sensorAnalog)
#pragma config(Sensor, in8, line_a, sensorAnalog)
#pragma config(Sensor, dgtl1, line_d, sensorDigitalIn)
#pragma config(Sensor, dgtl11, limit_power, sensorDigitalIn)
#pragma config(Motor, port2, rightWheel, tmotorVex393_MC29, openLoop, reversed)
#pragma config(Motor, port3, leftWheel, tmotorVex393_MC29, openLoop, reversed)
//*!!Code automatically generated by 'ROBOTC' configuration wizard							 !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard								!!//

#pragma DebuggerWindows("Globals")
#pragma DebuggerWindows("systemParameters")
#pragma DebuggerWindows("Sensors")
#pragma DebuggerWindows("DebugStream")
int distanceR = 0, distanceL = 0, distanceT = 0;
int * currDists[3];

void right_step_move(int time){
    int timeSteps = 0;
	while(true){
	timeSteps++;
    motor[rightWheel] = -50;
    motor[leftWheel] = -50;
    currDists = get_distance();
    for (int count3=0;count3<3;count3++){
        if (currDists[count3]<80 && currDists[count3]>10){
            move_forward(5);
        }
    }
    if(timeSteps>time*200){
    	break;
    }
  }
}

void move_forward(int milliSecond)
{
	clearTimer(T1);

    while (time1(T1)<milliSecond)
    {
        motor[rightWheel] = -92;
        motor[leftWheel] = 110;
    }
}

int *get_distance()
{
    distanceL = 29.988 * pow(SensorValue[sharpLeft], -1.173) * 1000 * 5 / 2;
    distanceR = 29.988 * pow(SensorValue[sharpRight], -1.173) * 1000 * 5 / 2;
    distanceT = 29.988 * pow(SensorValue[sharpTop], -1.173) * 1000 * 5 / 2;

    //shortDistance = 12.08 * pow(SensorValue[sharpShort], -1.058) * 1000 * 5 / 4;

    int distVals[3];
    distVals[0] = distanceL;
    distVals[1] = distanceR;
    distVals[2] = distanceT;
    //distVals[2] = shortDistance;

    return distVals;
}

task main(){
    right_step_move(10);
}
