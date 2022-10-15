#include "TshirtCannon.h"

TshirtCannon::TshirtCannon(frc::Joystick * driverStick) {
    joystick = driverStick;
}
void TshirtCannon::init(){
    pressed_button_pressure = false;
    valve_start = false;
  
    valve->Set(false);
    frc::SmartDashboard::PutBoolean("valve", false);

    v_shutoffTimerFlag = false;
    v_shutoffTimer->Reset();

    v_shutoffDelay = -1; // -1 is default behavior, non zero value is delayed shutoff in seconds
    v_shutoffTimer_float = -1;

    count = 0;
}

void TshirtCannon::periodic(){

  analog_input->GetVoltage();
  frc::SmartDashboard::PutNumber("analogInput", analog_input->GetVoltage());

  var_input = frc::SmartDashboard::GetNumber("varInput", 1);
  frc::SmartDashboard::PutNumber("varInput", var_input);

  maxPSI = frc::SmartDashboard::GetNumber("maxPSI", 82);
  frc::SmartDashboard::PutNumber("maxPSI", maxPSI);

  v_shutoffDelay = frc::SmartDashboard::GetNumber("valveDelay", 0.25);
  frc::SmartDashboard::PutNumber("valveDelay", v_shutoffDelay);

  PSI = (analog_input->GetVoltage()) * 100 + 10; // transfer function
  v_shutoffTimer_float = (v_shutoffTimer->Get()).value();
  // to compress
  if (joystick->GetRawButtonPressed(1)) {
    valve->Set(false);
    pressed_button_pressure = true;
    reached_max_pressure = false;
    frc::SmartDashboard::PutBoolean("triggerpress", true);
    frc::SmartDashboard::PutBoolean("valve", false);
  }

  if (joystick->GetRawButtonPressed(3)) {
    valve->Set(false);
    frc::SmartDashboard::PutBoolean("valve", false);
  }

  // debug purposes
  if (reached_max_pressure) {
    std::cout << "reached max pressure" << std::endl;
  }

  if ((joystick->GetRawButtonPressed(2)) && (reached_max_pressure)) {
    valve->Set(true);
    valve_start = true;
    frc::SmartDashboard::PutBoolean("valve", true);
  }

  if (valve_start) {
    v_shutoffTimer->Reset();
    v_shutoffTimer->Start();

    std::cout << "starting timer" << std::endl;
    valve_start = false;
  } else if (v_shutoffTimer_float >= v_shutoffDelay) {
    v_shutoffTimer->Stop();
    valve->Set(false);
    frc::SmartDashboard::PutBoolean("valve", false);
    std::cout << "stopped timer" << std::endl;

  }

  if ((!reached_max_pressure) && (pressed_button_pressure)) {
    if (PSI < maxPSI) {
      compressor->Set(1);
    } else {
      compressor->Set(0);
      reached_max_pressure = true;
      pressed_button_pressure = false; 
      frc::SmartDashboard::PutBoolean("triggerpress", false);
    }
  } 


}
