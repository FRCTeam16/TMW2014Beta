/*
 * ResetCams.h
 *
 *  Created on: Dec 11, 2014
 *      Author: Programmer
 */
#include "jankyTask.h"
#include "WPILib.h"
#include "Robot.h"
#ifndef RESETCAMS_H_
#define RESETCAMS_H_

class ResetCams : private JankyTask
{
private:
	float 	stage1Setpoint;

public:
	ResetCams();
	virtual ~ResetCams();
    virtual void Run();
};

#endif /* RESETCAMS_H_ */
