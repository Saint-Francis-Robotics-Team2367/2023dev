#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/shuffleboard/Shuffleboard.h>
#include <frc/shuffleboard/ShuffleboardTab.h>
#include <iostream>

class Shuffleboard {

    public:
        // const wpi::StringMap<std::shared_ptr<nt::Value>>& properties {
        //     std::make_pair("min", nt::Value::MakeDouble(0)),
        //     std::make_pair("max", nt::Value::MakeDouble(2))
        // };

        //tuning constants, can put some stuff in same graph and can put it all in a layout
        nt::NetworkTableEntry p = frc::Shuffleboard::GetTab("PID Tuning").Add("P", 1)
            .WithWidget(frc::BuiltInWidgets::kNumberSlider)
           // .WithProperties(properties);
            .GetEntry();
        nt::NetworkTableEntry i = frc::Shuffleboard::GetTab("PID Tuning").Add("I", 0)
            .WithWidget(frc::BuiltInWidgets::kNumberSlider)
           // .WithProperties(properties);
            .GetEntry();
        nt::NetworkTableEntry d = frc::Shuffleboard::GetTab("PID Tuning").Add("D", 0)
            .WithWidget(frc::BuiltInWidgets::kNumberSlider)
            .GetEntry();
         nt::NetworkTableEntry iZone = frc::Shuffleboard::GetTab("PID Tuning").Add("iZone", 0)
            .WithWidget(frc::BuiltInWidgets::kNumberSlider)
            .GetEntry();
        nt::NetworkTableEntry voltage = frc::Shuffleboard::GetTab("PID Tuning").Add("Voltage", 0)
            .WithWidget(frc::BuiltInWidgets::kGraph)
            .GetEntry(); //can send an array here with setpoint in the graph too, double graphs!!!!
        nt::NetworkTableEntry encoder = frc::Shuffleboard::GetTab("PID Tuning").Add("Encoder", 0)
            .WithWidget(frc::BuiltInWidgets::kGraph)
            .GetEntry();
};