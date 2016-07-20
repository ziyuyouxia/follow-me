// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FollowMeArmSwing.hpp"

namespace teo
{

/************************************************************************/

bool FollowMeArmSwing::configure(yarp::os::ResourceFinder &rf)
{
    std::string robot = rf.check("robot",yarp::os::Value(DEFAULT_ROBOT),"name of /robot to be used").asString();

    printf("--------------------------------------------------------------\n");
    if (rf.check("help"))
    {
        printf("FollowMeArmSwing options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        printf("\t--robot: %s [%s]\n",robot.c_str(),DEFAULT_ROBOT);
        ::exit(0);
    }

    std::string followMeArmSwingStr("/followMeArmSwing");

    yarp::os::Property leftArmOptions;
    leftArmOptions.put("device","remote_controlboard");
    leftArmOptions.put("remote",robot+"/leftArm");
    leftArmOptions.put("local",followMeArmSwingStr+robot+"/leftArm");
    leftArmDevice.open(leftArmOptions);
    if(!leftArmDevice.isValid()) {
      printf("robot leftArm device not available.\n");
      leftArmDevice.close();
      yarp::os::Network::fini();
      return false;
    }

    if ( ! leftArmDevice.view(leftArmPos) ) {
        printf("[warning] Problems acquiring leftArmPos interface\n");
        return false;
    } else printf("[success] Acquired leftArmPos interface\n");
    leftArmPos->setPositionMode();

    yarp::os::Property rightArmOptions;
    rightArmOptions.put("device","remote_controlboard");
    rightArmOptions.put("remote",robot+"/rightArm");
    rightArmOptions.put("local",followMeArmSwingStr+robot+"/rightArm");
    rightArmDevice.open(rightArmOptions);
    if(!rightArmDevice.isValid()) {
      printf("robot rightArm device not available.\n");
      rightArmDevice.close();
      yarp::os::Network::fini();
      return false;
    }

    if ( ! rightArmDevice.view(rightArmPos) ) {
        printf("[warning] Problems acquiring rightArmPos interface\n");
        return false;
    } else printf("[success] Acquired rightArmPos interface\n");
    rightArmPos->setPositionMode();

    phase = false;

    inSrPort.open("/followMeArmSwing/dialogueManager/command:i");
    inSrPort.setReader(*this);  //-- Callback reader: avoid need to call inSrPort.read().

    return true;
}

/************************************************************************/

bool FollowMeArmSwing::interruptModule()
{
    inSrPort.interrupt();
    leftArmDevice.close();
    return true;
}

/************************************************************************/

double FollowMeArmSwing::getPeriod()
{
    return 4.0; // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/

bool FollowMeArmSwing::updateModule()
{
    printf("Entered updateModule...\n");
    if(phase)
    {
        leftArmPos->positionMove(0, 20);
        rightArmPos->positionMove(0, 20);
        phase = false;
    }
    else
    {
        leftArmPos->positionMove(0, -20);
        rightArmPos->positionMove(0, -20);
        phase = true;
    }

    return true;
}

/************************************************************************/

}  // namespace teo

