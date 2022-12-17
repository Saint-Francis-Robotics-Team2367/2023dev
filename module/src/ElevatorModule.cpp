#include "ElevatorModule.h"

ElevatorModule::ElevatorModule(int motorID) {
    m_ID = motorID;
}

double ElevatorModule::boundStop(double input, double position) {
    //frc::SmartDashboard::PutNumber("Dist to top", enc_range - position);
    if (position < start_position + enc_range_safety) { // In low bound
        if (input < 0) {
            return 0;
        }
        return input;
    } else if (position > start_position + enc_range - enc_range_safety) { // In hi bound
        if (input > 0) {
            return 0;
        }
        return input;
    }
    return input;
}

double ElevatorModule::ctrMove(double Linput, double Rinput) {
    //frc::SmartDashboard::PutNumber("l", Linput);
    //frc::SmartDashboard::PutNumber("r", Rinput);

    double L = Linput;
    double R = Rinput;
    if (Linput < triggerDeadband) {L = 0;}
    if (Rinput < triggerDeadband) {R = 0;}
    if ((Linput == 0) && (Rinput == 0) && GRAV_PID) {
        return -10;
    }
    return (R - L) / 4;
}

double ElevatorModule::getPos() {
    return enc.GetPosition();
}

void ElevatorModule::Init() {
    enc.SetPosition(start_position);
    PID_ctr.SetP(grav_Kp);
    PID_ctr.SetI(grav_Ki);
    PID_ctr.SetD(grav_Kd);
    PID_ctr.SetOutputRange(-PID_range, PID_range);
    m_elev1->SetIdleMode(rev::CANSparkMax::IdleMode::kBrake);
    m_elev1->SetInverted(invert);
    enc.SetPositionConversionFactor(conversion_factor);
}

void ElevatorModule::TeleopPeriodic(double Linput, double Rinput) {
    run_counter +=  1;
    frc::SmartDashboard::PutBoolean("GRAV_PID", GRAV_PID);
    double pos = getPos();
    frc::SmartDashboard::PutNumber("Position", pos);
    char state = 't';

    if (state == 't') {
        double input = 0;
        if (bound) {
            input = boundStop(ctrMove(Linput, Rinput), getPos());
        } else {
            input = ctrMove(Linput, Rinput);
        }
        
        frc::SmartDashboard::PutNumber("input", input);
        //frc::SmartDashboard::PutBoolean("Staying Still?", this->stay_still);
        //frc::SmartDashboard::PutNumber("StayAtPos:", this->curr_reference);


        if ((input < -1) && this->GRAV_PID) { //No Movement - gravity PID
            frc::SmartDashboard::PutBoolean("GRAV_PID", true); 
            if (this->stay_still) { //If stay_position is already set
                PID_ctr.SetReference(curr_reference, rev::ControlType::kPosition);
            } else {//First iteration > Set curr_reference
                this->stay_still = true;
                this->curr_reference = this->enc.GetPosition();
                PID_ctr.SetReference(this->curr_reference, rev::ControlType::kPosition);

            }
            
        } else { //If there is trigger input
            this->stay_still = false;
            frc::SmartDashboard::PutBoolean("GRAV_PID", false);
            this->m_elev1->Set(input);
        }
    } else if (state == 'a') {
        m_elev1->Set(0);
    }

}

void ElevatorModule::AutoPeriodic(double inp_setpt) {
    double pos = getPos();
    if ((inp_setpt < (start_position + enc_range)) && (inp_setpt > start_position)) {
        PID_ctr.SetReference(inp_setpt, rev::ControlType::kPosition);
        
    }
}