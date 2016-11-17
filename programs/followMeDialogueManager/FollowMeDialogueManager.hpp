// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __FM_DIALOGUE_MANAGER_HPP__
#define __FM_DIALOGUE_MANAGER_HPP__

#include <yarp/os/all.h>
#include <stdlib.h>

#include "StateMachine.hpp"

namespace teo
{

/**
 * @ingroup followMeDialogueManager
 *
 * @brief Dialogue Manager 1.
 */
class FollowMeDialogueManager : public yarp::os::RFModule {
  private:
    StateMachine stateMachine;
    yarp::os::BufferedPort<yarp::os::Bottle> inSrPort;
    yarp::os::RpcClient outTtsPort;
    yarp::os::RpcClient outSrecPort; // SpeechRecognition port
    yarp::os::RpcClient testPort; // -- BORRAR
    yarp::os::Port outCmdPort;    

    bool interruptModule();
    double getPeriod();
    bool updateModule();

  public:
    bool configure(yarp::os::ResourceFinder &rf);
};

}  // namespace teo

#endif  // __FM_DIALOGUE_MANAGER_HPP__
