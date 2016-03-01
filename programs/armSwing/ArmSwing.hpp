// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

namespace teo
{

class ArmSwing : public yarp::os::RFModule
{
public:
     bool configure(yarp::os::ResourceFinder &rf);
private:
     bool interruptModule();
     double getPeriod();
     bool updateModule();

     yarp::dev::PolyDriver dd;
     yarp::dev::IPositionControl *pos;

};

}  // namespace teo
