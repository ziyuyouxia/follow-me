// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <stdio.h>
#include <stdlib.h>

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

using namespace yarp::os;
using namespace yarp::dev;


int main(int argc, char *argv[]) {

    printf("WARNING: requires a running instance of RaveBot (i.e. testRaveBot or cartesianServer)\n");
    Network yarp;
    if (!Network::checkNetwork()) {
        printf("Please start a yarp name server first\n");
        return(-1);
    }
    Property options;
    options.put("device","remote_controlboard");
    options.put("remote","/ravebot");
    options.put("local","/local");
    PolyDriver dd(options);
    if(!dd.isValid()) {
      printf("RaveBot device not available.\n");
	  dd.close();
      Network::fini();
      return 1;
    }

    IPositionControl *pos;
    bool ok = dd.view(pos);
    if (!ok) {
        printf("[warning] Problems acquiring robot interface\n");
        return false;
    } else printf("[success] testAsibot acquired robot interface\n");
    pos->setPositionMode();

    printf("test positionMove(1,-35)\n");
    pos->positionMove(1, -35);

    printf("Delaying 5 seconds...\n");
    Time::delay(5);

    IEncoders *enc;
    ok = dd.view(enc);

    IVelocityControl *vel;
    ok = dd.view(vel);
    vel->setVelocityMode();
    printf("test velocityMove(0,10)\n");
    vel->velocityMove(0,10);

    printf("Delaying 5 seconds...\n");
    Time::delay(5);

    return 0;
}


