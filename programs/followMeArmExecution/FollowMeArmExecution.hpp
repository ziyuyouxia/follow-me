// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __FOLLOW_ME_ARM_SWING_HPP__
#define __FOLLOW_ME_ARM_SWING_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>

#define DEFAULT_ROBOT "/teo"

#define VOCAB_FOLLOW_ME VOCAB4('f','o','l','l')

#define VOCAB_STATE_SALUTE VOCAB4('s','a','l','u')
#define VOCAB_STATE_ARM_SWINGING VOCAB4('s','w','i','n')
#define VOCAB_STOP_FOLLOWING VOCAB4('s','f','o','l')
#define VOCAB_STATE_SIGNALIZE_RIGHT VOCAB4('s','i','g','r')
#define VOCAB_STATE_SIGNALIZE_LEFT VOCAB4('s','i','g','l')

namespace teo
{

/**
 * @ingroup follow-me_programs
 *
 * @brief Arm Execution Core.
 *
 */
class FollowMeArmExecution : public yarp::os::RFModule, public yarp::os::PortReader, public yarp::os::Thread
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
    /** Left Arm ControlMode2 Interface */
    yarp::dev::IControlMode2 *leftArmIControlMode2;
   /** Left Arm PositionControl2 Interface */
    yarp::dev::IPositionControl2 *leftArmIPositionControl2;

     /** Right Arm Device */
     yarp::dev::PolyDriver rightArmDevice;
     /** Right Arm ControlMode2 Interface */
     yarp::dev::IControlMode2 *rightArmIControlMode2;
     /** Right Arm PositionControl2 Interface */
      yarp::dev::IPositionControl2 *rightArmIPositionControl2;

     /** Phase of arm swing movement */
     bool phase;

     /** Arm Joints Move And Wait */
     bool armJointsMoveAndWait(std::vector<double>& leftArmQ, std::vector<double>& rightArmQ);

     /** State */
     int state;

     /** Input port from dialogue manager */
     yarp::os::RpcServer inDialogPort;

     /** Treats data received from input port from speech recognition */
     virtual bool read(yarp::os::ConnectionReader& connection);

     /** Thread run */
     virtual void run();

};

}  // namespace teo

#endif  // __FOLLOW_ME_ARM_SWING_HPP__
