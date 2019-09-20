#pragma DebuggerWindows (debugstream);

task main() //reaction time test
{
	bool playAgain = true;

	while (playAgain == true)
	{
		eraseDisplay();
		for (byte count = 3; count > 0; count--) //Count down
		{
			displayCenteredBigTextLine(5, "%d", count);
			sleep(1000);
		}
		eraseDisplay();

		displayCenteredBigTextLine(5, "Wait, you idiot"); //tell the idiot to wait
		playSound(soundBeepBeep);

		unsigned long timeStop = nPgmTime+ (rand () % 500+1000); //confuse the idiot
		bool cheated = false;

		while (nPgmTime<timeStop&&cheated==false) //wait for go
		{
			if (getButtonPress(7)) // catch the cheater
				cheated = true;

			sleep (10); // give the computer a coffee break you heartless idiot
		}

		eraseDisplay();
		displayCenteredBigTextLine(5, "Go, you idiot"); //allow non-cheating idiot to react
		playImmediateTone (1000, 10);
		unsigned long nowTime = nPgmTime;

		if (cheated == true)
		{
			eraseDisplay();
			setSoundVolume (100);
			playSoundFile("Crying"); //make fun of the cheater
			displayCenteredTextLine (5, "you is idiot cheater"); //remind the cheater that they is idiot
			setLEDColor(ledRedFlash);
			sleep (3000); //insure the idiot cheater combo knows they is idiot cheater discount combo
		}
		else
		{
			while (!getButtonPress(7)) //wait for button to be pressed
			{
				sleep(10); // give the computer a coffee break you heartless idiot
			}

			unsigned long reactTime = nPgmTime - nowTime; //determine reaction time
			eraseDisplay();
			displayCenteredTextLine(5, "reaction time = %d ms", reactTime); //display reaction time

			if (reactTime<500)
				setLEDColor(ledGreenFlash); //flash the light green for zoom zoom fast idiots
			if (reactTime<1000 && reactTime>500)
				setLEDColor(ledOrangeFlash); //flash the light orange for average joe idiots
			if (reactTime>1000)
				setLEDColor(ledRedFlash); //flash the light red for lazy idiots

			sleep (3000); //let the idiot see there score

			eraseDisplay();
			setSoundVolume (100);
			playSoundFile("Magic wand"); //magic wand
			displayCenteredTextLine(5, "congrats, you is idiot"); //insure the idiot knows were they stand

			sleep(3000);
		}
		while (getButtonPress(7));//wait for idiot and/or cheater to release the button
			sleep (10); //give the computer a coffee break you heartless idiot

		displayCenteredTextLine (5, "press to play again"); //ask the idiot to play again

		nowTime = nPgmTime + 5000;
		playAgain=false;
		while (!getButtonPress(7) && nowTime>nPgmTime)
			if (getButtonPress(7))
			playAgain = true; //idiot plays again to be reminded that they is an idiot
		else
			sleep(10); //give the computer a coffee break you heartless idiot

	}


}
