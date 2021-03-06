// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __FM_EXECUTION_CORE_HPP__
#define __FM_EXECUTION_CORE_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <stdlib.h>

#include "InCvPort.hpp"
#include "InDialoguePortProcessor.hpp"

#define VOCAB_FOLLOW_ME VOCAB4('f','o','l','l')
#define VOCAB_STOP_FOLLOWING VOCAB4('s','f','o','l')

using namespace yarp::os;

namespace teo
{

/**
 * @ingroup follow-me_programs
 *
 * @brief Head Execution Core.
 *
 */
class FollowMeHeadExecution : public RFModule {
    public:
        bool configure(ResourceFinder &rf);


    protected:
        //-- Rpc port, server to knowing encoder position (reply position port), etc...
        RpcServer inDialoguePort;
        InDialoguePortProcessor inDialoguePortProcessor; // old (InSrPort)
        InCvPort inCvPort;

        /** Head Device */
        yarp::dev::PolyDriver headDevice;
        /** Head ControlMode2 Interface */
        yarp::dev::IControlMode2 *headIControlMode2;
        /** Head PositionControl2 Interface */
        yarp::dev::IPositionControl2 *headIPositionControl2;

        yarp::dev::IEncoders *iEncoders;

        bool interruptModule();
        double getPeriod();
        bool updateModule();



};

}  // namespace teo

#endif  // __FM_EXECUTION_CORE_HPP__
