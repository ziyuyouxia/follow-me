// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __FM_EXECUTION_CORE_HPP__
#define __FM_EXECUTION_CORE_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <stdlib.h>

#include "InCvPort.hpp"
#include "InSrPort.hpp"

#define VOCAB_FOLLOW_ME VOCAB4('f','o','l','l')
#define VOCAB_STOP_FOLLOWING VOCAB4('s','f','o','l')

using namespace yarp::os;

namespace teo
{

/**
 * @ingroup followMeHeadExecution
 *
 * @brief Execution Core 1.
 *
 */
class FollowMeHeadExecution : public RFModule {
    public:
        bool configure(ResourceFinder &rf);

    protected:
        InSrPort inSrPort;
        InCvPort inCvPort;
        yarp::dev::PolyDriver headDevice;
        yarp::dev::IPositionControl *iPositionControl;
        yarp::dev::IEncoders *iEncoders;

        bool interruptModule();
        double getPeriod();
        bool updateModule();

};

}  // namespace teo

#endif  // __FM_EXECUTION_CORE_HPP__
