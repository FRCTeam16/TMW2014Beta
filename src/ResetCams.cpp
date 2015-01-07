/*
 * ResetCams.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: Programmer
 */

#include <ResetCams.h>

ResetCams::ResetCams() {
	stage1Setpoint = .5;

}

ResetCams::~ResetCams() {
	// TODO Auto-generated destructor stub
}

void ResetCams::Run() {
/*	if(Robot::shooter->GetCorrectedCamPos() < 4.8 && !Robot::shooter->GetResetCamComplete()) {
		if(Robot::shooter->GetCorrectedCamPos() > stage1Setpoint) {
			Robot::shooter->SetResetCamComplete(false);
			Robot::shooter->RunCams(1, false);
		}
		else {
			Robot::shooter->RunCams(.7, false);
			Robot::shooter->SetResetCamComplete(false);
		}
	}
	else {
		Robot::shooter->RunCams(0, false);
		Robot::shooter->SetResetCamComplete(true);
		Robot::shooter->SetFireFlag(false);
		Robot::shooter->SetFireDelayFlag(false);
	}

*/
}

