#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color)
#pragma config(Sensor, S4,     rightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          rightMotor,    tmotorEV3_Large, PIDControl, reversed, encoder)
#pragma config(Motor,  motorC,          leftMotor,     tmotorEV3_Large, PIDControl, reversed, encoder)

bool doLF; // flag to control line follow
float kP; // line follow parameters
float speed;
float mid;
tSensors port;

task SLF() // line follow task. 
{
	while(true) 
	{
		while(doLF) 
		{
			float error = (getColorReflected(leftSensor) - mid) * kP; // calculates an error value and multiplies it by kP to scale it
			setMotorSpeed(leftMotor, speed - error); // subracts this scaled correction from the desired speed of the left motor
			setMotorSpeed(rightMotor, speed + error); // adds this scaled correction from the desired speed of the right motor
		}
	}
}

void initLF() // starts the line follow task (used to make code look nice)
{
	startTask(SLF); // start task
	doLF = false; // initialize the line follow flag
}

void startLF(tSensors p, float s, float m, float k) // start line following using parameters
{
	port = p; // set all line follow parameters
	speed = s;
	mid = m;
	kP = k;
	doLF = true; // raise the line follow flag
}

void stopLF() // stop line following
{
	doLF = false;
}

void quitLF() // stop the line follow task
{
	stopTask(SLF);
}

task main()
{
	initLF();
	
	startLF(leftSensor, 20, 56, 0.2);
	sleep(5000);
	
	stopLF();
	
	quitLF();
}
