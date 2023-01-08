#include <rev/CANSparkMax.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PIDController.h>

#define triggerDeadband 0.1
#define PI 3.1415926

class ElevatorModule {
    int run_counter = 0;
    double slowCoefficient = 4;
    public:
    //Conversion Factors:
    double pitch_diameter = 1.273;
    double pitch_circum = pitch_diameter * PI;
    double conversion_factor = pitch_circum / (30); //Ratio 30:1

    //Mech/Electronics Setup
   // int m_ID = 10;
    int m_ID = 15;
    
    rev::CANSparkMax* elevatorMotor = new rev::CANSparkMax(m_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::SparkMaxRelativeEncoder enc = elevatorMotor->GetEncoder();
    rev::SparkMaxPIDController elevatorPID = elevatorMotor->GetPIDController();

    double height = 0; //starting the elevator at 0 (no absolute encoder)

    //constants
    double kElevatorMinHeight = 0.0;
    double kElevatorMaxHeight = 11;


    //no feedforward in this case...
    double pDown = 0.8;
    double dDown = 0.0;

    double pUp = 1.0; 
    double dUp = 0.0;

    bool oneRun = false;


    ElevatorModule(int motorID);
    void Init();
    void TeleopPeriodic(double Linput, double Rinput);
    void AutoPeriodic();
    double getPos();
    void resetPos();
    double manualMove(double Linput, double Rinput);
    void setPos(double setpoint);
    double getHeight();


};