#include "IntakeModule.h"

void IntakeModule::intake(frc::Joystick* driverStick, frc::Joystick* operatorStick) {
  double basePos = 0.0;
  double outPos = 2.5; // change to position of the motor at full extension

  if (driverStick->GetRawButtonPressed(1))
  {
    if (intakeActive)
    {
      intakeAction->Set(-1.0);
      intakeRoller->StopMotor();
    }
    else
    {
      intakeAction->Set(1.0);
      intakeRoller->Set(1.0);
    }
    intakeActive = !intakeActive;
  }

  if ((intakeActive && iActEncoder.GetPosition() >=  outPos) || (!intakeActive && iActEncoder.GetPosition() <= basePos))
    intakeAction->StopMotor();

  if (operatorStick->GetRawButtonPressed(1))
  {
    if (intakeActive)
      intakeRoller->Set(-1.0);
  }
}

void IntakeModule::periodicInit() {
  this->msInterval = IntakeModuleRunInterval;
}

void IntakeModule::periodicRoutine() {
  // Use mode of robot to determine control source
  // Autonomous -> AutonomousPipe
  // Monitor input from BrownoutPipe
  // Command manipulators from operatorStick state

  // if (stateRef->IsAutonomous()) {
  //   if (!this->pressed && driverStick->GetRawButtonPressed(1)) {
  //     PIDTurn(90, 5, 1, 1);
  //     this->pressed = true;
  //     frc::SmartDashboard::PutBoolean("Pressed", this->pressed);

  //   }
  // }
	// Add rest of manipulator code...
  Message* m = pipes[0]->popQueue();
  if (m->str == "disable")
  {
    intakeAction->Set(-1.0);
    intakeRoller->StopMotor();
  }
  if (m->str == "activate")
  {
    intakeAction->Set(1.0);
    intakeRoller->Set(1.0);
  }

  if ((intakeActive && iActEncoder.GetPosition() >=  outPos) || (!intakeActive && iActEncoder.GetPosition() <= basePos))
    intakeAction->StopMotor();

  if (m->str == "outtake")
  {
    if (intakeActive)
      intakeRoller->Set(-1.0);
  }

  if (m->str == "shooting") {
    if (m->val)
      for (int i = 0;i < 3; i++) {
        indexMotors[i].Set(1.0);
      }
    else
      or (int i = 0;i < 3; i++) {
        indexMotors[i].Set(0.0);
      }
  }
}

std::vector<uint8_t> IntakeModule::getConstructorArgs() { return std::vector<uint8_t> {DriveBaseModuleID}; }