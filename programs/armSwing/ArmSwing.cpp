// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "ArmSwing.hpp"

namespace teo
{

/************************************************************************/

bool ArmSwing::configure(yarp::os::ResourceFinder &rf)
{
    yarp::os::Property leftArmOptions;
    leftArmOptions.put("device","remote_controlboard");
    leftArmOptions.put("remote","/teo/leftArm");
    leftArmOptions.put("local","/local");
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
    rightArmOptions.put("local","/local");
    leftArmDevice.open(rightArmOptions);
    if(!leftArmDevice.isValid()) {
      printf("/teo/leftArm device not available.\n");
      leftArmDevice.close();
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

bool ArmSwing::interruptModule()
{
    leftArmDevice.close();
    return true;
}

/************************************************************************/

double ArmSwing::getPeriod()
{
    return 5.0; // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/

bool ArmSwing::updateModule()
{
    printf("Entered updateModule...\n");
    if(phase)
    {
        leftArmPos->positionMove(0, 10);
        rightArmPos->positionMove(0, 10);
    }
    else
    {
        leftArmPos->positionMove(0, -10);
        rightArmPos->positionMove(0, -10);
    }

    return true;
}

/************************************************************************/

}  // namespace teo

