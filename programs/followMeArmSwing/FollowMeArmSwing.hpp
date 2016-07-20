// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __FM_ARM_SWING_HPP__
#define __FM_ARM_SWING_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#define DEFAULT_ROBOT "/teo"

namespace teo
{

class FollowMeArmSwing : public yarp::os::RFModule, public yarp::os::PortReader
{
public:
     bool configure(yarp::os::ResourceFinder &rf);
private:
     bool interruptModule();
     double getPeriod();
     bool updateModule();

     yarp::dev::PolyDriver leftArmDevice;
     yarp::dev::PolyDriver rightArmDevice;
     yarp::dev::IPositionControl *leftArmPos;
     yarp::dev::IPositionControl *rightArmPos;

     bool phase;

     yarp::os::Port inSrPort;
     virtual bool read(yarp::os::ConnectionReader& connection) {
          yarp::os::Bottle b;
          b.read(connection);
          // process data in b
          printf("Got %s\n", b.toString().c_str());
          return true;
     }
};

}  // namespace teo

#endif  // __FM_ARM_SWING_HPP__
