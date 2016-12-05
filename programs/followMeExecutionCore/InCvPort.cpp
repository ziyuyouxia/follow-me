// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include "InCvPort.hpp"

namespace teo
{

/************************************************************************/

void InCvPort::onRead(Bottle& b) {
    if ( ! follow ) return;
    if (b.size() < 3) return;

    double x = b.get(0).asDouble();
    double y = b.get(1).asDouble();
    double z = b.get(2).asDouble();
    printf("%f %f %f\n",x,y,z);
    if( x > 50 ) iPositionControl->relativeMove(0, 2);
    if( x < -50 ) iPositionControl->relativeMove(0, -2);
    //
    if( y > 50 ) iPositionControl->relativeMove(1, 2);
    if( y < -50 ) iPositionControl->relativeMove(1, -2);

}
//------------------- Obtain current joint position --------------------
void InCvPort::getHeadPos(double *vectPos){
    std::vector<double> currentQ(2);

    if ( ! iEncoders->getEncoders( currentQ.data() ) )
    {
        printf("getEncoders failed, not updating control this iteration.\n");
        return;
    }
    else
        vectPos = currentQ.data(); // -- A pointer to the first element in the array used internally by the vector.
}
/************************************************************************/

void InCvPort::setFollow(bool value)
{
    follow = value;
}

/************************************************************************/

}  // namespace teo

