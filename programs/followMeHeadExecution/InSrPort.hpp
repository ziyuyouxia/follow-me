// -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*-

#ifndef __IN_SR_PORT_HPP__
#define __IN_SR_PORT_HPP__

#include <yarp/os/all.h>
#include <yarp/dev/all.h>
#include <stdlib.h>

#include "InCvPort.hpp"

#define VOCAB_FOLLOW_ME VOCAB4('f','o','l','l')
#define VOCAB_WAVE_APPROPRIATE_HAND VOCAB4('w','a','p','h')


using namespace yarp::os;

namespace teo
{

/**
 * @ingroup followMeExecutionCore
 *
 * @brief Input port of speech recognition data.
 *
 */

class inSrPort : public PortReader { // -- InSrPort
     virtual bool read(ConnectionReader& connection) {
          Bottle in, out;
          bool ok = in.read(connection);
          if (!ok) return false;
          ...      // process data "in", prepare "out"
          ConnectionWriter *returnToSender = connection.getWriter();
          if (returnToSender!=NULL) {
         out.write(*returnToSender);
          }
          return true;
     }
};
DataProcessor processor;
...
p.setReader(processor);  // no need to call p.read() on port any more.

/*
class InSrPort : public BufferedPort<Bottle> {
    public:
        void setInCvPortPtr(InCvPort *inCvPortPtr) {
            this->inCvPortPtr = inCvPortPtr;
        }

        void setIEncoders(yarp::dev::IEncoders *iEncoders) {
            this->iEncoders = iEncoders;
        }

        bool configure();
*/

//    protected:
        /** Callback on incoming Bottle. **/
//        virtual void onRead(Bottle& b);

        //-- Cv Port
//        InCvPort* inCvPortPtr;

        //-- Robot device
//        yarp::dev::IEncoders *iEncoders;
//};


}  // namespace teo

#endif  // __IN_SR_PORT_HPP__
