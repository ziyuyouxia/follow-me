// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FmArmSwing.hpp"

namespace teo
{

/************************************************************************/

bool FmArmSwing::configure(yarp::os::ResourceFinder &rf)
{
    yarp::os::Property leftArmOptions;
    leftArmOptions.put("device","remote_controlboard");
    leftArmOptions.put("remote","/teo/leftArm");
    leftArmOptions.put("local","/fmArmSwing/teo/leftArm");
    leftArmDevice.open(leftArmOptions);
    if(!leftArmDevice.isValid()) {
      printf("/teo/leftArm device not available.\n");
      leftArmDevice.close();
      yarp::os::Network::fini();
      return 1;
    }

    if ( ! leftArmDevice.view(leftArmPos) ) {
        printf("[warning] Problems acquiring leftArmPos interface\n");
        return false;
    } else printf("[success] Acquired leftArmPos interface\n");
    leftArmPos->setPositionMode();

    yarp::os::Property rightArmOptions;
    rightArmOptions.put("device","remote_controlboard");
    rightArmOptions.put("remote","/teo/rightArm");
    rightArmOptions.put("local","/fmArmSwing/teo/rightArm");
    rightArmDevice.open(rightArmOptions);
    if(!rightArmDevice.isValid()) {
      printf("/teo/rightArm device not available.\n");
      rightArmDevice.close();
      yarp::os::Network::fini();
      return 1;
    }

    if ( ! rightArmDevice.view(rightArmPos) ) {
        printf("[warning] Problems acquiring rightArmPos interface\n");
        return false;
    } else printf("[success] Acquired rightArmPos interface\n");
    rightArmPos->setPositionMode();

    phase = false;

    return true;
}

/************************************************************************/

bool FmArmSwing::interruptModule()
{
    leftArmDevice.close();
    return true;
}

/************************************************************************/

double FmArmSwing::getPeriod()
{
    return 5.0; // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/

bool FmArmSwing::updateModule()
{
    printf("Entered updateModule...\n");
    if(phase)
    {
        leftArmPos->positionMove(0, 20);
        rightArmPos->positionMove(1, -20);  // open
        phase = false;
    }
    else
    {
        leftArmPos->positionMove(0, -20);
        rightArmPos->positionMove(1, 0);  // neutral (close)
        phase = true;
    }

    return true;
}

/************************************************************************/

}  // namespace teo

