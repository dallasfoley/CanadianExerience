/**
 * @file Body.cpp
 * @author dalla
 */
#include "pch.h"
#include "Body.h"

/**
 * Default Constructor
 *
 */
Body::Body() //: mSink(this)
{

}

/**
 * Set image for the body
 * @param filename image to set
 */
void Body::SetImage(std::wstring filename)
{
    mPolygon.SetImage(filename);
}

/**
 * Draw the body
 * @param graphics Graphics context to draw on
 */
void Body::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.Draw(graphics);
}

/**
 * Install physics on the body
 * @param world containing the body
 * @param contactListener the body uses for interactions
 */
void Body::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)
{
    mPolygon.InstallPhysics(world);
}

/**
 * Rotate the Body
 * @param rotation angle
 * @param speed of rotation (angular velocity)
 */
void Body::Rotate(double rotation, double speed)
{
    mPolygon.SetAngularVelocity(speed);
}
