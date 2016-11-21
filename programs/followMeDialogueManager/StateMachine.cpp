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
    ttsSay( presentation1 );
    ttsSay( presentation2 );
    ttsSay( presentation3 );
    while(!isStopping()) {
         if(_machineState==0)
         {
            ttsSay( askName );  //-- , please tell me
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
            if((_inStrState1.find(myNameIs) != yarp::os::ConstString::npos))
            {
                switch (sentence) {
                case 'a':
                    ttsSay( answer1 );
                    sentence = 'b';
                    break;
                case 'b':
                    ttsSay( answer2 );
                    sentence = 'c';
                    break;
                case 'c':
                    ttsSay( answer3 );
                    sentence = 'a';
                    break;
                default:
                    break;
                }
            _machineState=2;
            }
            else
            {
                ttsSay( notUnderstand );
                _machineState=0;
            }
         }
        else if(_machineState==2)
        {
            yarp::os::ConstString inStr = asrListen();
            // Blocking
            _inStrState1 = inStr;
            if( _inStrState1.find(followMe) != yarp::os::ConstString::npos ) _machineState=3;
            else if ( _inStrState1.find(stopFollowing) != yarp::os::ConstString::npos ) _machineState=4;
            else _machineState=2;
        } else if (_machineState==3) {
            ttsSay( okFollow );
            //yarp::os::Time::delay(0.5);
            yarp::os::Bottle cmd;
            cmd.addVocab(VOCAB_FOLLOW_ME);
            outCmdPort->write(cmd);
            _machineState=0;
        } else if (_machineState==4) {
            ttsSay( stopFollow );
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
bool StateMachine::setLanguage(std::string language)
{
    _language = language;
    if("english" == language)
    {
        //-- recognition sentences
        followMe = std::string ("follow me");
        myNameIs = std::string ("my name is");
        stopFollowing = std::string ("stop following");

        return true;
    }
    else if("spanish" == language)
    {
        //-- frases de reconociomiento
        followMe = std::string ("follow me");
        myNameIs = std::string ("my name is");
        stopFollowing = std::string ("stop following");

        return true;
    }
    else
    {
        printf("error! %s????\n",language.c_str());
        return false;
    }
}

/************************************************************************/

bool StateMachine::setSpeakLanguage(std::string language) {

    if("english" == language)
    {
        //-- speak sentences
        presentation1 = std::string("Follow me, demostration started");
        presentation2 = std::string("Hello. My name is TEO. I am, a humanoid robot, of Carlos tercero, university.");
        presentation3 = std::string("Now, I will follow you. Please, tell me");
        askName = std::string("Could you tell me your name");
        answer1 = std::string("Is, a beatifull name. I love it");
        answer2 = std::string("Is, a wonderfull name. My human creator, has the same name");
        answer3 = std::string("My parents, didn't want to baptize me, with that name.");
        notUnderstand = std::string("Sorry, I don't understand");
        okFollow = std::string("Okay, I will follow you");
        stopFollow = std::string("Okay, I will stop following you. See you later");

        return true;
    }
    else if("spanish" == language)
    {
        //-- speak sentences
        presentation1 = std::string("Demostración de detección de caras iniciada");
        presentation2 = std::string("Hola. Me yamo Teo, y soy un grobot humanoide diseñado por ingenieros de la universidad carlos tercero");
        presentation3 = std::string("Por favor, dime qué quieres que haga");
        askName = std::string("Podrías decirme tu nombre");
        answer1 = std::string("Uuooooo ouu, que nombre más bonito. Me encanta");
        answer2 = std::string("Que gran nombre. Mi creador humano se yama igual");
        answer3 = std::string("Mis padres no quisieron bauuutizarme con ese nombre. Malditos.");
        notUnderstand = std::string("Lo siento. No te he entendido");
        okFollow = std::string("Vale. Voy, a comenzar a seguirte");
        stopFollow = std::string("De acuerdo. Voy, a dejar de seguirte. Hasta pronto.");
    }
    else
    {
        printf("error! %s????\n",language.c_str());
        return false;
    }
}

}  // namespace teo
