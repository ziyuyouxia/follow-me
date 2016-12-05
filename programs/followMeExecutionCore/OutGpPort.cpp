#include "OutGpPort.hpp"

// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

namespace teo
{

/************************************************************************/

void OutGpPort::onRead(Bottle& b) {

}

//------------------- Obtain current joint position --------------------

void OutGpPort::getHeadPos(double *vectPos){
    RpcServer port;
    port.open("/followMeExecutionCore/getPosition/state:o"); // -- output port
    Bottle out;

    std::vector<double> currentQ(2);

    if ( ! iEncoders->getEncoders( currentQ.data() ) )
    {
        printf("getEncoders failed, not updating control this iteration.\n");
        return;
    }
    else
    {
        out.write(currentQ); // -- A pointer to the first element in the array used internally by the vector.
        port.reply(out);     // -- Send reply.
    }
}

/************************************************************************/

void OutGpPort::getPosition(bool value)
{
    position = value;
}

/************************************************************************/
} // -- namespace teo
