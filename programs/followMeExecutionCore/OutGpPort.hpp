// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __OUT_GP_PORT_HPP__
#define __OUT_GP_PORT_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <stdlib.h>

#define VOCAB_FOLLOW_ME VOCAB4('f','o','l','l')
#define VOCAB_STOP_FOLLOWING VOCAB4('s','f','o','l')


using namespace yarp::os;

namespace teo
{

/**
 * @ingroup followMeExecutionCore
 *
 * @brief Input port of computer vision data.
 *
 */
class OutGpPort : public BufferedPort<Bottle> {
public:
    void getPosition(bool value);
    void getHeadPos(double *vectPos);


protected:
        bool position;

        /** Callback on incoming Bottle. **/
        virtual void onRead(Bottle& b);

        yarp::dev::IPositionControl *iPositionControl;

        //-- Robot device
        yarp::dev::IEncoders *iEncoders;

};

}


#endif // __OUT_GP_PORT_HPP__


