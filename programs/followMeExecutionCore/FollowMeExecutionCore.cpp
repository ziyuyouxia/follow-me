// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FollowMeExecutionCore.hpp"

namespace teo
{

/************************************************************************/

bool FollowMeExecutionCore::configure(ResourceFinder &rf) {

    //ConstString fileName(DEFAULT_FILE_NAME);
    
    printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("FollowMeExecutionCore options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        //printf("\t--file (default: \"%s\")\n",fileName.c_str());
    }
    //if (rf.check("file")) fileName = rf.find("file").asString();
    //printf("FollowMeExecutionCore using file: %s\n",fileName.c_str());

    printf("--------------------------------------------------------------\n");
    if(rf.check("help")) {
        ::exit(1);
    }

    //
    Property headOptions;
    headOptions.put("device","remote_controlboard");
    headOptions.put("local","/followMeExecutionCore/head");
    headOptions.put("remote","/teo/head");
    headDevice.open(headOptions);
    if( ! headDevice.isValid() ) {
        printf("head remote_controlboard instantiation not worked.\n");
        return false;
    }
    if( ! headDevice.view(iPositionControl) ) {
        printf("view(iPositionControl) not worked.\n");
        return false;
    }
    inCvPort.setIPositionControl(iPositionControl);

    //-----------------OPEN LOCAL PORTS------------//
    inSrPort.setInCvPortPtr(&inCvPort);
    inCvPort.useCallback();
    inSrPort.useCallback();
    inSrPort.open("/followMeExecutionCore/dialogueManager/command:i");
    inCvPort.open("/followMeExecutionCore/cv/state:i");

    return true;
}

/************************************************************************/
double FollowMeExecutionCore::getPeriod() {
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/
bool FollowMeExecutionCore::updateModule() {
    //printf("StateMachine in state [%d]. FollowMeExecutionCore alive...\n", stateMachine.getMachineState());
    return true;
}

/************************************************************************/

bool FollowMeExecutionCore::interruptModule() {
    printf("FollowMeExecutionCore closing...\n");
    inCvPort.disableCallback();
    inSrPort.disableCallback();
    inCvPort.interrupt();
    inSrPort.interrupt();
    inCvPort.close();
    inSrPort.close();
    return true;
}

/************************************************************************/

}  // namespace teo
