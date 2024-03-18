/**
 * @file RotationSource.cpp
 * @author dalla
 */
#include "pch.h"
#include "RotationSource.h"
#include "IRotationSink.h"


RotationSource::RotationSource()
{

}
/**
 * Constructor
 * @param component associated with this source
 * @param imagesDir image directory
 */
RotationSource::RotationSource(Component *component, std::wstring imagesDir)
{

}

/**
 * Rotate all sinks associated with this source
 * @param rotation angle
 * @param speed of rotation
 */
void RotationSource::SetRotation(double rotation, double speed)
{
    for (auto sink: mSinks)
    {
        sink->Rotate(rotation, speed);
    }

}

/**
 * Add a sink association to this source
 * @param sink associated with this source
 */
void RotationSource::AddSink(std::shared_ptr<IRotationSink> sink)
{
    mSinks.push_back(sink);
}

