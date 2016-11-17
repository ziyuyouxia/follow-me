// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FollowMeDialogueManager.hpp"

namespace teo
{

/************************************************************************/

bool FollowMeDialogueManager::configure(yarp::os::ResourceFinder &rf) {

    //ConstString fileName(DEFAULT_FILE_NAME);
    
    printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("FollowMeDialogueManager options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        //printf("\t--file (default: \"%s\")\n",fileName.c_str());
    }
    //if (rf.check("file")) fileName = rf.find("file").asString();
    //printf("FollowMeDialogueManager using file: %s\n",fileName.c_str());

    printf("--------------------------------------------------------------\n");
    if(rf.check("help")) {
        ::exit(1);
    }

    //-----------------OPEN LOCAL PORTS------------//
    outCmdPort.open("/followMeDialogueManager/command:o");
    outTtsPort.open("/followMeDialogueManager/tts/rpc:c");
    inSrPort.open("/followMeDialogueManager/speechRecognition/speech:i"); // -- words (input)
    outSrecPort.open("/followMeDialogueManager/speechRecognition/rpc:c"); // -- setDictionary (client)
    testPort.open("/followMeDialogueManager/miPuertoGuay/testSuperMegaLargo/rpc:c");
    stateMachine.setOutCmdPort(&outCmdPort);
    stateMachine.setOutTtsPort(&outTtsPort);
    stateMachine.setInSrPort(&inSrPort);

    while(1){
        if(outSrecPort.getOutputCount() > 0) break;
        printf("Waiting for \"/followMeDialogueManager/speechRecognition/rpc:c\" to be connected to something...\n");
        yarp::os::Time::delay(0.5);
    }

    while(1){
        if(outTtsPort.getOutputCount() > 0) break;
        printf("Waiting for \"/followMeDialogueManager/tts/rpc:c\" to be connected to something...\n");
        yarp::os::Time::delay(0.5);
    }

    yarp::os::Bottle bOut, bRec;

    // -- Speaking
    bOut.addString("setLanguage");
    bOut.addString("mb-en1");   
    outTtsPort.write(bOut);

    // -- Hearing
    bRec.addString("setDictionary");
    bRec.addString("follow-me");
    bRec.addString("english"); // -- This can be changed in the future (with spanish)
    outSrecPort.write(bRec);

    stateMachine.start();
    return true;
}

/************************************************************************/
double FollowMeDialogueManager::getPeriod() {
    return 2.0;  // Fixed, in seconds, the slow thread that calls updateModule below
}

/************************************************************************/
bool FollowMeDialogueManager::updateModule() {
    printf("StateMachine in state [%d]. FollowMeDialogueManager alive...\n", stateMachine.getMachineState());
    return true;
}

/************************************************************************/

bool FollowMeDialogueManager::interruptModule() {
    printf("FollowMeDialogueManager closing...\n");
    inSrPort.interrupt();
    outTtsPort.interrupt();
    stateMachine.stop();
    inSrPort.close();
    outTtsPort.close();
    return true;
}

/************************************************************************/

}  // namespace teo
