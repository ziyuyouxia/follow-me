// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FollowMeHeadExecution.hpp"

namespace teo
{

/************************************************************************/

bool FollowMeHeadExecution::configure(ResourceFinder &rf) {

    //ConstString fileName(DEFAULT_FILE_NAME);
    
    printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("FollowMeHeadExecution options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        //printf("\t--file (default: \"%s\")\n",fileName.c_str());
    }
    //if (rf.check("file")) fileName = rf.find("file").asString();
    //printf("FollowMeHeadExecution using file: %s\n",fileName.c_str());

    printf("--------------------------------------------------------------\n");
    if(rf.check("help")) {
        ::exit(1);
    }

    //
    Property headOptions;
    headOptions.put("device","remote_controlboard");
    headOptions.put("local","/followMeHeadExecution/head");
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
    if( ! headDevice.view(iEncoders) ) {
        printf("view(iEncoders) not worked.\n");
        return false;
    }
    inCvPort.setIPositionControl(iPositionControl);
    inSrPort.setIEncoders(iEncoders);

    //-----------------OPEN LOCAL PORTS------------//
    inSrPort.setInCvPortPtr(&inCvPort);
    inCvPort.useCallback();
    inSrPort.useCallback();
    inSrPort.open("/followMeHeadExecution/dialogueManager/command:i");
    inCvPort.open("/followMeHeadExecution/cv/state:i");
    replyPosPort.open("/followMeHeadExecution/head/rpc:s"); // -- head

    return true;
}

/************************************************************************/
double FollowMeHeadExecution::getPeriod() {
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/
bool FollowMeHeadExecution::updateModule() {
    //printf("StateMachine in state [%d]. FollowMeHeadExecution alive...\n", stateMachine.getMachineState());
    return true;
}

/************************************************************************/

bool FollowMeHeadExecution::interruptModule() {
    printf("FollowMeHeadExecution closing...\n");
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
