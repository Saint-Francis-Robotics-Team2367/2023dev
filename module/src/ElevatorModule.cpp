#include "ElevatorModule.h"

ElevatorModule::ElevatorModule(int motorID) {
    motorID = m_ID;
}

double ElevatorModule::ctrMove(double Linput, double Rinput) {
    frc::SmartDashboard::PutNumber("l", Linput);
    frc::SmartDashboard::PutNumber("r", Rinput);

    double L = Linput;
    double R = Rinput;
    if (Linput < triggerDeadband) {L = 0;}
    if (Rinput < triggerDeadband) {R = 0;}
    if ((Linput == 0) && (Rinput == 0) && STAY_PID) {
        return -10;
    }
    if (L > R) {return -(L / 4) ;}
    else { return R / 4 ; }
}

double ElevatorModule::getPos() {
    return enc.GetPosition();
}

void ElevatorModule::Init() {
    m_elev1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_elev1->SetInverted(invert);
    enc.SetPositionConversionFactor(conv_factor);
}

void ElevatorModule::Periodic(char state, double Linput, double Rinput) {
    run_counter +=  1;
    frc::SmartDashboard::PutNumber("Position", getPos());

    if (state == 't') {
        double setpt = ctrMove(Linput, Rinput);
        frc::SmartDashboard::PutNumber("setpt", setpt);
        if ((setpt < -1) && STAY_PID) {
            frc::SmartDashboard::PutNumber("PID", 1);
            PID_ctr.SetReference(enc.GetPosition(), rev::ControlType::kPosition);
        } else {
            frc::SmartDashboard::PutNumber("PID", 0);
            m_elev1->Set(setpt);
        }
    } else if (state == 'a') {
        m_elev1->Set(0);
    }

}

