// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "InSrPort.hpp"

namespace teo
{

/************************************************************************/

bool InSrPort::read(ConnectionReader& connection) {
    Bottle in, out;
    bool ok = in.read(connection);
    if (!ok) return false;

    switch ( in.get(0).asVocab() ) { //-- b.get(0).asVocab()
        case VOCAB_FOLLOW_ME:
            printf("follow\n");
            inCvPortPtr->setFollow(true);
            break;
        case VOCAB_STOP_FOLLOWING:
            printf("stopFollowing\n");
            inCvPortPtr->setFollow(false);
            break;
        case VOCAB_WAVE_APPROPRIATE_HAND:
            // implementar movimiento brazo dependiendo de iEncoders
            double encValue;
            if ( ! iEncoders->getEncoder(0, &encValue) )  // 0 es el tilt del cuello (http://robots.uc3m.es/index.php/TEO_Diagrams)
            {
                printf("Error: getEncoder failed\n");
                return false;
            }

            if(encValue > 0)
            {
                printf("USER IS ON LEFT -> MOVE THE LEFT ARM\n");
            }

            if(encValue < 0)
            {
                printf("USER IS ON RIGHT -> MOVE THE RIGHT ARM\n");
            }


        default:
            break;
    }
}

/************************************************************************/

}  // namespace teo
