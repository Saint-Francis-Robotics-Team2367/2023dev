
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
#define STAY_PID 1



class ElevatorModule {
    int run_counter = 0;

    public:
    int m_ID;
    ElevatorModule(int motorID);
    bool invert = false;
    double conv_factor = 2.37;
    rev::CANSparkMax* m_elev1 = new rev::CANSparkMax(m_ID, rev::CANSparkMax::MotorType::kBrushless);
    rev::SparkMaxRelativeEncoder enc = m_elev1->GetEncoder();
    rev::SparkMaxPIDController PID_ctr = m_elev1->GetPIDController();



    double ctrMove(double Linput, double Rinput);
    void Init();
    void Periodic(char state, double Linput, double Rinput);
    double getPos();

    


};