#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
#pragma DebbugerWindows (debugstream)
#pragma DebbugerWindows (EV3LCDScreen)

task main()
{
	int ls; // initializes the light sensor variable. It stores the value of the light sensor reading
	float hi[] = {0,-1,-1,-1,-1}; // initializes the High values lower than the lowest possible light sensor reading
	float lo[] = {0,1024,1024,1024,1024}; // initializes the Low values higher than the highest possible light sensor reading
	float mid[] = {0,0,0,0,0}; // fills in the mid array with empty values
	tSensors sensors[]= {S1, S2, S3, S4}; // an array that stores all of the portNumbers in a nice, usable way

	resetMotorEncoder(leftMotor); //resets the drive motor encoders
	resetMotorEncoder(rightMotor);
	setMotorSync(leftMotor, rightMotor, 0, 20); // Starts the drive motors at 20% speed

	while(getMotorEncoder(leftMotor) < 720)//repeats the loop until the motor has elapsed 720 degrees
	{
		for (int portNumber = 1; portNumber <= 4; portNumber++) // loops through every sensor portNumber
		{
			ls = SensorRaw[sensors[portNumber-1]];// if the light sensor reading of the portNumber is greater than the high value...
			if (ls>hi[portNumber])
				hi[portNumber] = ls; // The light sensor reading replaces the current high value
			if (ls<lo[portNumber])// if the light sensor reading of the portNumber is lesser than the low value...
				lo[portNumber] = ls; // The light sensor reading replaces the current low value
		}
	}
	long midhandle,hihandle,lohandle;
	char*Threshold="Mid";
	char*High="Hi";
	char*Low="Lo";
	midhandle=_OpenFile(Threshold,fileFlagWriteOnly|fileFlagCreate|fileFlagTruncate);
	hihandle=_OpenFile(High,fileFlagWriteOnly|fileFlagCreate|fileFlagTruncate);
	lohandle=_OpenFile(Low,fileFlagWriteOnly|fileFlagCreate|fileFlagTruncate);
	for (int portNumber = 1; portNumber <= 4; portNumber++)
	{
		mid[portNumber] = (hi[portNumber] + lo[portNumber])/2;//Averages the High and low values for each portNumber and writes it in the corresponding index in the mid array
		fileWriteFloat(midhandle,mid[portNumber]);
		fileWriteFloat(hihandle,hi[portNumber]);
		fileWriteFloat(lohandle,lo[portNumber]);
	}
	fileClose(midhandle);
	fileClose(hihandle);
	fileClose(lohandle);
}
