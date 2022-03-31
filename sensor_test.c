#pragma config(Sensor, in1,    sharpTop,       sensorAnalog)
#pragma config(Sensor, in2,    sharpShort,     sensorAnalog)
#pragma config(Sensor, in3,    sharpRight,     sensorAnalog)
#pragma config(Sensor, in5,    sharpLeft,      sensorAnalog)
#pragma config(Sensor, in8,    line_a,         sensorAnalog)
#pragma config(Sensor, dgtl1,  backLeft,       sensorDigitalIn)
#pragma config(Sensor, dgtl2,  frontLeft,      sensorDigitalIn)
#pragma config(Sensor, dgtl3,  frontRight,     sensorDigitalIn)
#pragma config(Sensor, dgtl4,  backRight,      sensorDigitalIn)
#pragma config(Sensor, dgtl7,  compassN,       sensorDigitalIn)
#pragma config(Sensor, dgtl8,  compassE,       sensorDigitalIn)
#pragma config(Sensor, dgtl9,  compassS,       sensorDigitalIn)
#pragma config(Sensor, dgtl10, compassW,       sensorDigitalIn)
#pragma config(Sensor, dgtl12, limitswitch,    sensorDigitalIn)
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard  !!//

 #pragma DebuggerWindows("Globals")
 #pragma DebuggerWindows("systemParameters")
 #pragma DebuggerWindows("Sensors")


 int distanceR = 0, distanceL = 0, distanceT = 0;
 int shortDistance = 0;
 int detectsLine = 0;

task main()
{
	SensorValue[compassN] = 0;
	SensorValue[compassE] = 0;
	SensorValue[compassS] = 0;
	SensorValue[compassW] = 0;
	SensorValue[sharpLeft] = 0;
	SensorValue[sharpTop] = 0;
	SensorValue[sharpShort] = 0;
	SensorValue[line_a] = 0;
	SensorValue[limitswitch] = 0;
//SensorValue[line_d] = 0;
	while(1==1){

		distanceR = 29.988 * pow(SensorValue[sharpRight],-1.173) *1000 * 5/2;
		distanceL = 29.988 * pow(SensorValue[sharpLeft],-1.173) *1000 * 5/2;
		distanceT = 29.988 * pow(SensorValue[sharpTop],-1.173) *1000 * 5/2;
		//writeDebugStreamLine("Distance in cm : %i", distance);

		shortDistance = 12.08 * pow(SensorValue[sharpShort], -1.058)*1000 * 5/4;
	//	if (SensorValue[frontLeft]==0) writeDebugStreamLine("Front Left Detected");
		//		if (SensorValue[frontRight]==0) writeDebugStreamLine("Front RIGHT Detected");
		//if (SensorValue[backLeft] <=500) writeDebugStreamLine("Back LEFT VALUE DROPPED %d",SensorValue[backLeft]);
		//writeDebugStreamLine("shortDistance in cm : %i", shortDistance);
		//if(SensorValue[reflective]< 160){
			//detectsLine = 1;
		//}else{
		//detectsLine = 0;
	//}

}
}
