// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#include "Robot.h"

// // All Module Includes
//#include "DriveBaseModule.h"

//DriveBaseModule drive;
//moved instantiation to h file

void Robot::RobotInit()
{
  elev->Init();
  //compRobotDrive.periodicInit();

  //need drive inits
  //drive.driveThread.detach(); 
 
}

void Robot::RobotPeriodic()
{
  //elev->Periodic('t', ctr->GetLeftTriggerAxis(), ctr->GetRightTriggerAxis());
}
void Robot::AutonomousInit()
{
  //drive.state = 'a';
}
void Robot::AutonomousPeriodic()
{
  // testLeftMotor->Set(0.2);
  // testRightMotor->Set(0.2);
}


void Robot::TeleopInit()
{
  //drive.state = 't'; //add codes in while loops to break if state change
}

void Robot::TeleopPeriodic()
{
  elev->TeleopPeriodic(ctr->GetLeftTriggerAxis(), ctr->GetRightTriggerAxis());
}

void Robot::DisabledInit() {
  elev->m_elev1->Set(0);
  //drive.stopAuto = true;
}
void Robot::DisabledPeriodic() {
}

void Robot::TestInit()
{
  //drive.state = 'd';
}

void Robot::TestPeriodic()
{
}

#ifndef RUNNING_FRC_TESTS
int main()
{
  return frc::StartRobot<Robot>();
}
#endif
