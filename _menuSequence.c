//#pragma DebuggerWindows (debugstream)
#pragma config(Sensor, S1,     leftSensor,     sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Sensor, S2,     rightSensor,    sensorEV3_Color, modeEV3Color_Reflected_Raw)
#pragma config(Motor,  motorB,          leftMotor,     tmotorEV3_Large, PIDControl, encoder)
#pragma config(Motor,  motorC,          rightMotor,    tmotorEV3_Large, PIDControl, encoder)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

#define NUM_OF_MENU_ITEMS 5 // this tells the preprocessor to replace NUM_OF_MENU_ITEMS with 5

string menuText [NUM_OF_MENU_ITEMS] = {"program 1","program 2","program 3","program 4","program 5"}; // Create string array for program text


void showMenuItem (byte programNum) { // function to show the current menu item
	eraseDisplay (); // clear the screen
	displayCenteredBigTextLine(5, menuText[programNum]); // display menuText and program number
}

void showMenu (byte programNum) // Display menu item
{
	showMenuItem (programNum); // show the current menu item
	playSoundFile("Click"); // play a clicking sound
	while(getButtonPress(buttonAny)) sleep(1); // wait for the button to be released
}

task main()
{
	bool selected = false; // whether or not the current program is selected
	byte programNum = 0; // number of current program

	showMenuItem(programNum); // Show program
	
	do // screen update loop
	{

		if (getButtonPress(buttonRight)) // if the right button is clicked go up one program
		{
			if (programNum == NUM_OF_MENU_ITEMS - 1) // rollover the program number
				programNum = 0;
			else
				programNum++; // increment programNum

			showMenu(programNum); // show the new menu item
		}
		if (getButtonPress(buttonLeft)) // if the left button is is clicked go down 1 program
		{
			if (programNum == 0) // rollover the program number
				programNum= NUM_OF_MENU_ITEMS - 1;
			else
				programNum--; // decrement programNum
			showMenu(programNum); // show the new mnu item
		}
		if (getButtonPress(buttonEnter)) // if the middle button is clicked, select the program
			selected = true;

	}
	while (!selected); // end of the do-while loop

	displayCenteredBigTextLine(5, "selected"); // show that the program was selected (will be replaced with actually running the mission)
	sleep (2000);
}
