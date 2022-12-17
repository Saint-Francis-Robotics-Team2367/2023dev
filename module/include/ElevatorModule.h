#include <rev/CANSparkMax.h>
#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PIDController.h>

#define triggerDeadband 0.1
#define PI 3.1415926

class ElevatorModule {
    int run_counter = 0;

    public:
    //Conversion Factors:
    double pitch_diameter = 1.273;
    double pitch_circum = pitch_diameter * PI;
    double conversion_factor = pitch_circum / (30); //Ratio 30:1

    //Mech/Electronics Setup
    int m_ID = 10;
    double enc_range = 17; //Encoderwise top to bottom range
    double start_position = 0; //Start position encoderwise
    double enc_range_safety = 0.2; // Safety range from top/bottom bound for stopping
    bool invert = false;

    //Gravity PID
    double PID_range = 0.4;
    bool bound = true; //Start Elevator at bottom position
    bool stay_still; //If first loop after no input
    double curr_reference; //No input ->start position
    bool GRAV_PID = true; //Overarching gravity PID switch
    
    //Gravity PID Constants
    double grav_Kp = 0.5;
    double grav_Ki = 0.0;
    double grav_Kd = 0.5;

    ElevatorModule(int motorID);
    rev::CANSparkMax* m_elev1 = new rev::CANSparkMax(m_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::SparkMaxRelativeEncoder enc = m_elev1->GetEncoder();
    rev::SparkMaxPIDController PID_ctr = m_elev1->GetPIDController();

    double boundStop(double input, double position);
    double ctrMove(double Linput, double Rinput);
    void Init();
    void TeleopPeriodic(double Linput, double Rinput);
    void AutoPeriodic(double inp_setpt);
    double getPos();

    


};