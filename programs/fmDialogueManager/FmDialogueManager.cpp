// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FmDialogueManager.hpp"

namespace teo
{

/************************************************************************/

bool FmDialogueManager::configure(yarp::os::ResourceFinder &rf) {

    //ConstString fileName(DEFAULT_FILE_NAME);
    
    printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("FmDialogueManager options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        //printf("\t--file (default: \"%s\")\n",fileName.c_str());
    }
    //if (rf.check("file")) fileName = rf.find("file").asString();
    //printf("FmDialogueManager using file: %s\n",fileName.c_str());

    printf("--------------------------------------------------------------\n");
    if(rf.check("help")) {
        ::exit(1);
    }

    //-----------------OPEN LOCAL PORTS------------//
    outCmdPort.open("/followMeDialogueManager/command:o");
    outTtsPort.open("/followMeDialogueManager/iSpeak:o");
    inSrPort.open("/followMeDialogueManager/speechRecognition:i");
    stateMachine.setOutCmdPort(&outCmdPort);
    stateMachine.setOutTtsPort(&outTtsPort);
    stateMachine.setInSrPort(&inSrPort);
    while(1){
        if(outTtsPort.getOutputCount() > 0) break;
        printf("Waiting for \"/followMeDialogueManager/tts:o\" to be connected to something...\n");
        yarp::os::Time::delay(0.5);
    }    
    stateMachine.start();
    return true;
}

/************************************************************************/
double FmDialogueManager::getPeriod() {
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/
bool FmDialogueManager::updateModule() {
    printf("StateMachine in state [%d]. FmDialogueManager alive...\n", stateMachine.getMachineState());
    return true;
}

/************************************************************************/

bool FmDialogueManager::interruptModule() {
    printf("FmDialogueManager closing...\n");
    inSrPort.interrupt();
    outTtsPort.interrupt();
    stateMachine.stop();
    inSrPort.close();
    outTtsPort.close();
    return true;
}

/************************************************************************/

}  // namespace teo
