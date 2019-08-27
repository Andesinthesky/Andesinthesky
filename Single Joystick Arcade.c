#pragma config(Motor, motor6,	leftMotor, tmotorVexIQ, openLoop, reversed, encoder)
#pragma config (Motor, motor1,	rightMotor, tmotorVexIQ, openLoop, encoder)
#pragma config(Motor, motor10, armMotor, tmotorVexIQ, openLoop, encoder)
task main()
{
	int iPower, iTurn, iTurnPrevious=0;
	int iLowerThreshold=30, iUpperThreshold=95;

	repeat (forever)
	{
		iPower=getJoystickValue(ChA);
		iTurn=getJoystickValue(ChB);

		if ( abs(iPower) > iUpperThreshold )
		{
			iPower=100*sgn(iPower);
		}
		else if ( abs(iPower) < iLowerThreshold )
		{
			iPower=0;
		}
		else
		{
			iPower=iPower;
		}

		if ( abs(iTurn) > iUpperThreshold )
		{
			iTurnPrevious=iTurn;
			iTurn=100*sgn(iTurn);
		}
		else if ( abs(iTurn) < iLowerThreshold )
		{
			iTurnPrevious=iTurn;
			iTurn=0;
		}
		else if ( abs(iTurn) < abs(iTurnPrevious) )
		{
			iTurnPrevious=iTurn;
			iTurn=0;
		}
		else
		{
			iTurnPrevious=iTurn;
			iTurn=iTurn/3;
		}

		setMotorSpeed(leftMotor, (iPower+iTurn)/2);
		setMotorSpeed(rightMotor, (iPower-iTurn)/2);

		if (getJoystickValue(BtnRUp)== 1)
		{
			setMotorSpeed(armMotor, -100);
		}
		else if (getJoystickValue(BtnRDown)==1)
		{
			setMotorSpeed(armMotor, 100);
		}
		else
		{
			setMotorSpeed(armMotor, 0);
		}

		wait10Msec(2);
	}
}
