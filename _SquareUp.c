#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color)
#pragma config(Sensor, S4,     rightSensor,    sensorEV3_Color)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

void SquareUp(int mid1, int mid2, float kP, int acceptance, int speed, int crsAdjsmtReps) // function to square up on a line. consists of coarse and fine adjustments
{
	setMotorBrakeMode(leftMotor, motorBrake);  // enable brakes
	setMotorBrakeMode(rightMotor, motorBrake); // on all motors

	for (byte i = 0; i < crsAdjsmtReps; i++) // do as many coarse adjustments as needed
	{
		bool Exit1 = false; // exit flags
		bool Exit2 = false; // both must be true to exit
		setMotorSpeed(leftMotor, speed);  // enable both motors
		setMotorSpeed(rightMotor, speed); // to get to the line

		while(!(Exit1 && Exit2)) // while at least 1 exit flag is false
		{
			if (getColorReflected(rightSensor) < mid1) // check if right sensor is at the black line
			{
				setMotorSpeed(rightMotor, 0); // stop the right motor
				Exit1 = true; // enable exit flag 1
			}
			if (getColorReflected(leftSensor) < mid2) // check is left sensor is st the black line
			{
				setMotorSpeed(leftMotor, 0); // stop left motor
				Exit2 = true; // enable exit flag 2
			}
		}
		if (i < crsAdjsmtReps-1) // check if this is not the last loop
		{
			setMotorSyncEncoder(leftMotor,rightMotor, 0, 360, -30); // move backwards to try coarce adjustment again
		}
	}

	bool fnAdjsmt = true; // flag that shows if robot is aligned
	while (fnAdjsmt) // loop while robot is not aligned
	{
		setMotorSpeed(leftMotor,(getColorReflected(leftSensor) - mid1)*kP);   // enable both motors 
		setMotorSpeed(rightMotor,(getColorReflected(rightSensor) - mid2)*kP);

		int ls1 = getColorReflected(leftSensor); // get values from both light sensors
		int ls2 = getColorReflected(rightSensor);

		if ((ls1 > mid1 - acceptance) && (ls1 < mid1 + acceptance) && (ls2 > mid2 - acceptance) && (ls2 < mid2 + acceptance)) // check is either light sensor is close enough to the line
			fnAdjsmt = false; // robot is now aligned
	}
}

task main()
{
	SquareUp(30, 30, 0.3, 5, 30, 1);
}
