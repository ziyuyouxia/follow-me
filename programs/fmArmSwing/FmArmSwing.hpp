// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

namespace teo
{

class FmArmSwing : public yarp::os::RFModule
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
};

}  // namespace teo
