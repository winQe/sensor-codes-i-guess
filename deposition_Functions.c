#pragma config(Sensor, dgtl6,  encoder1,       sensorQuadEncoder)
#pragma config(Motor,  port3,           collector,     tmotorVex393_HBridge, openLoop)
#pragma config(Motor,  port1,          depositor,     tmotorVex393_HBridge, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

//int encoderValue= 0;

void deposit(){

		clearTimer (T1);
		while (time1(T1)< 1000){
			motor[collector] = -127;
		}
		motor[collector] = 0;
		clearTimer(T2);
		while(time1(T2)<2000){

			motor[depositor] = -20;
	}
	clearTimer(T2);
			while(time1(T2)<2000){
			motor[depositor] = 20;
	}
	motor[depositor] = 0;
}

void collection_on(){
	motor[collector] = 100;}

task main()
{

clearTimer(T2);
while(time1(T2)<5000){
	collection_on();}
	motor[collector]=0;
	deposit();

//SensorValue[encoder]=0;


}
