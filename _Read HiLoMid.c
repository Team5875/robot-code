#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
#pragma DebbugerWindows (debugstream)
#pragma DebbugerWindows (EV3LCDScreen)

task main()
{
	float mid[] = {0,0,0,0,0};//Initializes Hi, Lo & Mid as empty
	float hi[] = {0,0,0,0,0};
	float lo[] = {0,0,0,0,0};
	long midhandle,hihandle,lohandle;//Initializes file handles
	char*Threshold="Mid";//Initializes Files
	char*High="Hi";
	char*Low="Lo";
	midhandle=_OpenFile(Threshold,fileFlagReadOnly);//Gets filehandles for reading
	hihandle=_OpenFile(High,fileFlagReadOnly);
	lohandle=_OpenFile(Low,fileFlagReadOnly);
	if(midhandle==-1|hihandle==-1|lohandle==-1)//Checks if files don't exist
	{
		displayCenteredTextLine(5,"Calibrate may not have been run yet");//Tells user to re-Calibrate
		displayCenteredTextLine(5,"Please run Calibrate and check again");
	}
	for (int portNumber = 1; portNumber <= 4; portNumber++)//Reads float data from file
	{
		fileReadFloat(midhandle,&mid[portNumber]);//Inputs float data into mid, hi and lo
		fileReadFloat(hihandle,&hi[portNumber]);
		fileReadFloat(lohandle,&lo[portNumber]);
	}
	fileClose(midhandle);//Saves files
	fileClose(hihandle);
	fileClose(lohandle);

	for (int portNumber = 1; portNumber <= 4; portNumber++)//Displays Hi, Lo & Mid
	{
		writeDebugStreamLine("Port %i Mid=%3.2f",portNumber,mid[portNumber]);
		writeDebugStreamLine("Port %i High=%3.2f",portNumber,hi[portNumber]);
		writeDebugStreamLine("Port %i Low=%3.2f",portNumber,lo[portNumber]);
	}
}
