#pragma config(Sensor, in1,    sharpShort,     sensorAnalog)
#pragma config(Sensor, in2,    sharpLeft,      sensorAnalog)
#pragma config(Sensor, in5,    sharpRight,     sensorAnalog)
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
#pragma config(Sensor, dgtl12, LimitSwitch,    sensorDigitalIn)
#pragma config(Motor,  port1,           motor1,        tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//!!Code automatically generated by 'ROBOTC' configuration wizard  !!//

 #pragma DebuggerWindows("Globals")
 #pragma DebuggerWindows("systemParameters")
 #pragma DebuggerWindows("Sensors")
//#pragma config(Sensor, in2,    sharpShort,     sensorAnalog

 int distanceRglob = 0, distanceLglob = 0, distanceTglob = 0, distanceBglob = 0;
 int shortDistance = 0;
 int detectsLine = 0;
 int sharpBackDist = 0;

 int analogValSharpLeft = 0;

 int analogValSharpBack = 0;
 float volt = 0;

int get_distanceL()
{
	int numberOfReadingsToAverage = 20;
	int totalL = 0;
	int avgL = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

		int distanceL = (1.0404*(29.988 * pow(SensorValue[sharpLeft], -1.173) * 1000 * 2.5)) + 1.809;
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

		int distanceR = (29.988 * pow(SensorValue[sharpRight], -1.173) * 1000 * 1.59375) + 6.9212;
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

int get_distanceTL()
{
	int numberOfReadingsToAverage = 100;
	int totalTL = 0;
	int avgTL = 0;
	for (int i =0; i< numberOfReadingsToAverage; i++){

		int distanceTL = 29.988 * pow(SensorValue[sharpTop], -1.173) * 1000 * 2.5;
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

task main()
{
	SensorValue[compassN] = 0;
	SensorValue[compassE] = 0;
	SensorValue[compassS] = 0;
	SensorValue[compassW] = 0;
	SensorValue[sharpLeft] = 0;
	SensorValue[sharpTop] = 0;
//SensorValue[line_d] = 0;
	while(1==1){
	volt = nImmediateBatteryLevel;
		/*distanceR = 29.988 * pow(SensorValue[sharpRight],-1.173) *1000 * 5/2;
		if (distanceR > 80) distanceR = 80;
		if (distanceR < 10) distanceR = 10;
		distanceL = 29.988 * pow(SensorValue[sharpLeft],-1.173) *1000 * 5/2;
		if (distanceL > 80) distanceL = 80;
		if (distanceL < 10) distanceL = 10;
		distanceT = 29.988 * pow(SensorValue[sharpTop],-1.173) *1000 * 5/2;
		if (distanceT > 80) distanceT = 80;
		if (distanceT < 10) distanceT = 10;*/
		distanceRglob = get_distanceR();
		distanceLglob = get_distanceL();
		distanceTglob = get_distanceTL();
		distanceBglob = get_distanceB();

		//writeDebugStreamLine("Distance in cm : %i", distance);

		//analogValSharpBack = SensorValue[sharpBack];

		//sharpBackDist = 13 * pow((analogValSharpBack*5/1024),-1);
		//shortDistance = 12.08 * pow(SensorValue[sharpBack], -1.058)*1000 * 5/4;

		analogValSharpLeft = SensorValue[sharpLeft];
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
