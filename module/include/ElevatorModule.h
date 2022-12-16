
#include <vector>
#include <math.h> 

#include <rev/CANSparkMax.h>

#include <frc/SmartDashboard/SmartDashboard.h>
#include <frc/PIDController.h>

#include <thread>
#include <chrono>
#include<mutex>
#include <atomic>


#define triggerDeadband 0.1




class ElevatorModule {
    int run_counter = 0;




    public:
    //Spec Setup
    int m_ID = 10;
    double enc_range = 295; //Encoderwise top to bottom range
    double start_position = 0; //Start position encoderwise
    double enc_range_safety = 5; // Safety range from top/bottom bound for stopping



    //Gravity PID
    bool stay_still; //If first loop after no input
    double curr_reference; //No input ->start position
    bool GRAV_PID = true; //Overarching gravity PID switch
    

    double grav_Kp = 0.5;
    double grav_Ki = 0.0;
    double grav_Kd = 0.5;


    ElevatorModule(int motorID);
    bool invert = false;
    double conv_factor = 2.37;
    rev::CANSparkMax* m_elev1 = new rev::CANSparkMax(m_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::SparkMaxRelativeEncoder enc = m_elev1->GetEncoder();
    rev::SparkMaxPIDController PID_ctr = m_elev1->GetPIDController();


    double boundStop(double input, double position);
    double ctrMove(double Linput, double Rinput);
    void Init();
    void Periodic(char state, double Linput, double Rinput);
    double getPos();

    


};