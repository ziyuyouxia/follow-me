// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "StateMachine.hpp"

namespace teo
{

/************************************************************************/

bool StateMachine::threadInit() {
    _machineState = 2;
    sentence = 'a';
    return true;
}

/************************************************************************/

void StateMachine::run() {
    ttsSay( yarp::os::ConstString("Follow me, demostration started") );
    ttsSay( yarp::os::ConstString("Hello. My name is TEO. I am, a humanoid robot, of Carlos tercero, university.") );
    ttsSay( yarp::os::ConstString("Now, I will follow you. Please, tell me") );
    while(!isStopping()) {
         if(_machineState==0)
         {
            ttsSay( yarp::os::ConstString("Could you tell me your name") );  //-- , please tell me
            yarp::os::Bottle cmd;
            cmd.addVocab(VOCAB_STATE_SALUTE);
            outCmdPort->write(cmd);
            _machineState=1;
         }
         else if(_machineState==1)
         {
            yarp::os::ConstString inStr = asrListen();            
            // Blocking
            _inStrState1 = inStr;
            if((_inStrState1.find("my name is") != yarp::os::ConstString::npos))
            {
                switch (sentence) {
                case 'a':
                    ttsSay( yarp::os::ConstString("Is, a beatifull name. I love it") );
                    sentence = 'b';
                    break;
                case 'b':
                    ttsSay( yarp::os::ConstString("Is, a wonderfull name. My human creator, has the same name") );
                    sentence = 'c';
                    break;
                case 'c':
                    ttsSay( yarp::os::ConstString("My parents, didn't want to baptize me, with that name.") );
                    sentence = 'a';
                    break;
                default:
                    break;
                }
            _machineState=2;
            }
            else
            {
                ttsSay( yarp::os::ConstString("Sorry, I don't understand"));
                _machineState=0;
            }
         }
        else if(_machineState==2)
        {
            yarp::os::ConstString inStr = asrListen();
            // Blocking
            _inStrState1 = inStr;
            if( _inStrState1.find("follow me") != yarp::os::ConstString::npos ) _machineState=3;
            else if ( _inStrState1.find("stop following") != yarp::os::ConstString::npos ) _machineState=4;
            else _machineState=2;
        } else if (_machineState==3) {
            ttsSay( yarp::os::ConstString("Okay, I will follow you") );
            //yarp::os::Time::delay(0.5);
            yarp::os::Bottle cmd;
            cmd.addVocab(VOCAB_FOLLOW_ME);
            outCmdPort->write(cmd);
            _machineState=0;
        } else if (_machineState==4) {
            ttsSay( yarp::os::ConstString("Okay, I will stop following you") );
            ttsSay( yarp::os::ConstString("See you later") );
            //yarp::os::Time::delay(0.5);
            yarp::os::Bottle cmd;
            cmd.addVocab(VOCAB_STOP_FOLLOWING);
            outCmdPort->write(cmd);
            _machineState=2;
        } else {
            ttsSay( yarp::os::ConstString("ANOMALY") );
            _machineState=0;
        }
    }
}

/************************************************************************/

void StateMachine::ttsSay(const yarp::os::ConstString& sayConstString) {
    /*yarp::os::Bottle bOutStop, bResStop;
    bOutStop.addString("stop");
    outTtsPort->write(bOutStop,bResStop);

    yarp::os::Time::delay(0.5);*/

    yarp::os::Bottle bOut, bRes;
    bOut.addString("say");
    bOut.addString(sayConstString);
    outTtsPort->write(bOut,bRes);
    printf("[StateMachine] Said: %s [%s]\n", sayConstString.c_str(), bRes.toString().c_str());
    yarp::os::Time::delay(0.5);
    return;
}

/************************************************************************/

yarp::os::ConstString StateMachine::asrListen() {
    yarp::os::Bottle* bIn = inSrPort->read(true);  // shouldWait
    printf("[StateMachine] Listened: %s\n", bIn->toString().c_str());
    return bIn->get(0).asString();
}

/************************************************************************/

int StateMachine::getMachineState() {
    return _machineState;
}

/************************************************************************/

void StateMachine::setInSrPort(yarp::os::BufferedPort<yarp::os::Bottle>* inSrPort) {
    this->inSrPort = inSrPort;
}

/************************************************************************/

void StateMachine::setOutCmdPort(yarp::os::Port* outCmdPort) {
    this->outCmdPort = outCmdPort;
}

/************************************************************************/

void StateMachine::setOutTtsPort(yarp::os::RpcClient* outTtsPort) {
    this->outTtsPort = outTtsPort;
}

/************************************************************************/

}  // namespace teo
