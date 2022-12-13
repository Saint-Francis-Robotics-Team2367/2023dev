#include "Macros.h"

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
#define STAY_PID 0



class ElevatorModule {
    int run_counter = 0;

    public:
    ElevatorModule(int motorID);
    bool invert = false;
    double conv_factor = 2.37;
    rev::CANSparkMax* m_elev1;
    rev::SparkMaxRelativeEncoder enc = m_elev1->GetEncoder();
    rev::SparkMaxPIDController PID_ctr = m_elev1->GetPIDController();



    double ctrMove(double Linput, double Rinput);
    void Init();
    void Periodic(char state, double Linput, double Rinput);
    double getPos();

    


};