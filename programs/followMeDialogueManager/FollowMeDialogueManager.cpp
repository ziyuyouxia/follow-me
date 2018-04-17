// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "FollowMeDialogueManager.hpp"

namespace teo
{

/************************************************************************/

bool FollowMeDialogueManager::configure(yarp::os::ResourceFinder &rf) {

    //ConstString fileName(DEFAULT_FILE_NAME);
    std::string language = rf.check("language",yarp::os::Value(DEFAULT_LANGUAGE),"language to be used").asString();
    
    printf("--------------------------------------------------------------\n");
    if (rf.check("help")) {
        printf("FollowMeDialogueManager options:\n");
        printf("\t--help (this help)\t--from [file.ini]\t--context [path]\n");
        printf("\t--language (default: \"%s\")\n",language.c_str());
        //printf("\t--file (default: \"%s\")\n",fileName.c_str());
    }
    //if (rf.check("file")) fileName = rf.find("file").asString();
    //printf("FollowMeDialogueManager using file: %s\n",fileName.c_str());

    printf("--------------------------------------------------------------\n");
    if(rf.check("help")) {
        ::exit(1);
    }

    //-----------------OPEN LOCAL PORTS------------//
    outCmdHeadPort.open("/followMeDialogueManager/head/rpc:c");
    outCmdArmPort.open("/followMeDialogueManager/arms/rpc:c");
    outTtsPort.open("/followMeDialogueManager/tts/rpc:c");
    outSrecPort.open("/followMeDialogueManager/speechRecognition/rpc:c"); // -- setDictionary (client)
    inSrPort.open("/followMeDialogueManager/speechRecognition/speech:i"); // -- words (input)

    stateMachine.setOutCmdHeadPort(&outCmdHeadPort);
    stateMachine.setOutCmdArmPort(&outCmdArmPort);
    stateMachine.setOutTtsPort(&outTtsPort);
    stateMachine.setOutSrecPort(&outSrecPort);
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


    // -- Speaking
    /*
    bOut.addString("setLanguage");
    bOut.addString("mb-en1");   
    outTtsPort.write(bOut);

    // -- Hearing
    bRec.addString("setDictionary");
    bRec.addString("follow-me");
    bRec.addString("english"); // -- This can be changed in the future (with spanish)
    outSrecPort.write(bRec);
*/

    //--------------------------

    bOut.addString("setLanguage");
    bRec.addString("setDictionary");
    bRec.addString("follow-me");

    if( language == "english" )
    {
        bOut.addString("mb-en1");
        bRec.addString(language );
    }
    else if ( language == "spanish" )
    {
        bOut.addString("mb-es1");
        bRec.addString(language); // -- cambiar a "language" cuando tengamos reconocimiento en español
    }
    else
    {
        printf("Language not found. Please use '--language english' or '--language spanish'");
        return false;
    }

    outTtsPort.write(bOut);
    outSrecPort.write(bRec);

    // clean yarp bottles
    bRec.clear();
    bOut.clear();

    // set functions
    stateMachine.setLanguage(language);
    stateMachine.setSpeakLanguage(language);


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
    outCmdHeadPort.interrupt();
    outCmdArmPort.interrupt();
    outTtsPort.interrupt();
    outSrecPort.interrupt();
    inSrPort.interrupt();
    stateMachine.stop();
    outCmdHeadPort.close();
    outCmdArmPort.close();
    outTtsPort.close();
    outTtsPort.close();
    inSrPort.close();
    return true;
}

/************************************************************************/

}  // namespace teo
