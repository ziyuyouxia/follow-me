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
     virtual bool configure(yarp::os::ResourceFinder &rf);
private:
     /** RFModule interruptModule. */
     virtual bool interruptModule();
     /** RFModule getPeriod. */
     virtual double getPeriod();
     /** RFModule updateModule. */
     virtual bool updateModule();

     /** Left Arm Device */
     yarp::dev::PolyDriver leftArmDevice;
     /** Left Arm Position Interface */
     yarp::dev::IPositionControl *leftArmPos;

     /** Right Arm Device */
     yarp::dev::PolyDriver rightArmDevice;
     /** Right Arm Position Interface */
     yarp::dev::IPositionControl *rightArmPos;

     /** Phase of arm swing movement */
     bool phase;

     /** Input port from speech recognition */
     yarp::os::Port inSrPort;
     /** Treats data received from input port from speech recognition */
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
