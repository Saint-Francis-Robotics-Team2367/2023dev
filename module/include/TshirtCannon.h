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

class TshirtCannon {
 public:
  void init();

  int maxPSI;
  float PSI;
  float var_input;
  bool reached_max_pressure = false;
  bool pressed_button_pressure = true;
  bool valve_start = false;

  float v_shutoffDelay;
  bool v_shutoffTimerFlag;

  bool compressor_start;
  float c_shutoffDelay;
  bool c_shutoffTimerFlag;

  bool compressed_button_pressed;

  int count;

  frc::AnalogInput * analog_input = new frc::AnalogInput(1);

  frc::Solenoid valve{1};

  frc::Spark* compressor = new frc::Spark(1);

  frc::Timer* v_shutoffTimer = new frc::Timer();

  frc::Timer* c_Timer = new frc::Timer();

};
