/**
 * @file RotationSource.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
#define CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
class IRotationSink;
#include "Component.h"


/**
 * A class describing a Rotation source used to rotate components
 *
 */
class RotationSource
{
private:
    /// rotation angle
    double mRotation = 0;
    /// rotation speed
    double mSpeed;
    /// Sinks connected to this source
    std::vector<std::shared_ptr<IRotationSink>> mSinks;

public:
    /// Default constructor
    RotationSource();
    /// Copy constructor (disabled)
    RotationSource(const RotationSource &) = delete;
    /// Assignment operator (disabled)
    void operator=(const RotationSource &) = delete;

    RotationSource(Component* component, std::wstring imagesDir);

    void AddSink(std::shared_ptr<IRotationSink> component);
    void SetRotation(double rotation, double speed);


};

#endif //CANADIANEXPERIENCE_MACHINELIB_ROTATIONSOURCE_H
