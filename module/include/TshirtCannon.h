// Copyright (c) FIRST and other WPILib contributors.
// Open Source Software; you can modify and/or share it under the terms of
// the WPILib BSD license file in the root directory of this project.

#pragma once

#include <frc/Joystick.h>
#include <frc/AnalogInput.h>
#include <frc/motorcontrol/Spark.h>
#include <frc/Solenoid.h>
#include <frc/Timer.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <iostream>

class TshirtCannon {
 public:
  TshirtCannon(frc::Joystick * driverStick);
  void init();
  void periodic();

  int maxPSI;
  float PSI;
  float var_input;
  bool reached_max_pressure = false;
  bool pressed_button_pressure = true;
  bool valve_start = false;
  float v_shutoffTimer_float;

//  units::time::second_t v_shutoffDelay;
  float v_shutoffDelay;
  bool v_shutoffTimerFlag;

  int count;

  frc::Joystick * joystick;
  frc::AnalogInput * analog_input = new frc::AnalogInput(1);

  frc::Solenoid * valve = new frc::Solenoid(frc::PneumaticsModuleType::CTREPCM, 1);

  frc::Spark* compressor = new frc::Spark(1);

  frc::Timer* v_shutoffTimer = new frc::Timer();


};
