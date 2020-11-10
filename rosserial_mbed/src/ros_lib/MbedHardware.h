/*
 * MbedHardware
 *
 *  Created on: Aug 17, 2011
 *      Author: nucho
 */

#ifndef ROS_MBED_HARDWARE_H_
#define ROS_MBED_HARDWARE_H_

#include "mbed.h"

class MbedHardware {
  public:
    MbedHardware(PinName tx, PinName rx, int baud = 57600) : 
        iostream(tx, rx, baud)
    {
      ;
      baud_ = baud;
      t.start();
    }

    MbedHardware()
      : iostream(USBTX, USBRX) {
        baud_ = 57600;
        t.start();
    }

    void setBaud(int baud){
      this->baud_= baud;
      iostream.set_baud(baud_);
    }

    int getBaud(){return baud_;}

    void init(){
        iostream.set_baud(baud_);
    }

    int read(){
        if (iostream.readable()) {
            char c;
            iostream.read(&c, 1);
            return c;
        } else {
            return -1;
        }
    };
    
    void write(uint8_t* data, int length) {
        // for (int i=0; i<length; i++)
        iostream.write(data, length);
    }

    unsigned long time(){return chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();}

protected:
    BufferedSerial iostream;
    int baud_;
    Timer t;
};


#endif /* ROS_MBED_HARDWARE_H_ */
