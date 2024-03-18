/**
 * @file IRotationSink.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#define CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
#include <memory>
class Component;

/**
 * An interface for Components that can be rotated by a source
 *
 */
class IRotationSink
{
private:

public:
    /**
    * Rotate this object
    * @param rotation angle to set
    * @param speed to set the rotation
    */
    virtual void Rotate(double rotation, double speed) {}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_IROTATIONSINK_H
