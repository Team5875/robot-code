#pragma config(Sensor, S4,     leftSensor,     sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Sensor, S1,     rightSensor,    sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

typedef enum Sides { // an enumerator to allow for line following on 2 different sides in a way that looks nice
	Right = 0,
	Left = 1
};

Sides side; // global variable to handle the side of the line to follow
tSensors port; // the port of the light sensor to follow with
int mid; // mid value for light sensors
int speed; // speed to follow at
float kP; // kp scales error value (smoothness of line follow)
bool doLF; // flag that tells the robot to line follow

task SLF() // line follow task. allows to line follow while doing other things
{
	while(true) 
	{
		while(dolf)
		{
			int error = (getColorReflected(port) - mid)*kP; // calculates an error value and multiplies it by kP to scale it
			setMotorSpeed(leftMotor, speed - error); // subracts this scaled correction from the desired speed of the left motor
			setMotorSpeed(rightMotor, speed + error); // adds this scaled correction from the desired speed of the right motor
		}
	}
}

void SmoothLF(Sides s, tSensors p, int m, int spd, float k) // line follow function. starts the SLF task
{
	side = s; // set all of the line follow variables
	port = p;
	mid = m;
	speed = spd;
	kP = k;
	if (side == Left)
	{
		// left side of line case
		kP = kP*-1; // reverses the kp(scaling) value
	}
	doLF = true; // raise the line follow flag
}

task main()
{
	doLF = false; // make sure the line follow flag is lowered
	startTask(SLF); // start the SLF task
	
	SmoothLF(Right, rightSensor, 30, 30, 0.35);
	sleep(10000);
	
	doLF = false; // stop line following
	stopTask(SLF); // end the task (always do this at the end of the code)
}