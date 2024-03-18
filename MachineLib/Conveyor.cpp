/**
 * @file Conveyor.cpp
 * @author dalla
 */
#include "pch.h"
#include "Conveyor.h"
#include <b2_contact.h>

/// The offset from the bottom center of the conveyor
/// to the center of the drive shaft.  48
const auto ConveyorShaftOffset = wxPoint2DDouble(48, 4);

/// The size of the conveyor in cm
const auto ConveyorSize = wxSize(125, 14);

/// The conveyor image to use
const std::wstring ConveyorImageName = L"/conveyor.png";

/**
 * Constructor
 * @param imagesDir image directory
 */
Conveyor::Conveyor(std::wstring imagesDir)
{
    mConveyor.SetImage(imagesDir + ConveyorImageName);
    mConveyor.BottomCenteredRectangle(ConveyorSize);

}

/**
 * Draw the Conveyor
 * @param graphics Graphics device to render onto
 */
void Conveyor::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mConveyor.Draw(graphics);
}

/**
 * Update the Conveyor
 * @param elapsed time since last update
 */
void Conveyor::Update(double elapsed)
{
    Component::Update(elapsed);
}

/**
 * Get position of the shaft
 * @return position of shaft
 */
wxPoint2DDouble Conveyor::GetShaftPosition()
{
    return mPosition + ConveyorShaftOffset;
}

/**
 * Handle before the solution of a contact with the
 * Conveyor object.
 * @param contact Contact object
 * @param oldManifold Manifold object
 */
void Conveyor::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetTangentSpeed(mSpeed);
}



/**
 * Install physics on the pulley
 * @param world containing the pulley
 * @param contactListener the pulley uses for interactions
 */
void Conveyor::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)
{
    mConveyor.InstallPhysics(world);
}

/**
 * Rotate (linearly) the Conveyor
 * @param rotation angle
 * @param speed of rotation (angular velocity)
 */
void Conveyor::Rotate(double rotation, double speed)
{
    auto contact = mConveyor.GetBody()->GetContactList();
    while(contact != nullptr)
    {
        if(contact->contact->IsTouching())
        {
            contact->other->SetLinearVelocity(b2Vec2(-speed, 0));
        }

        contact = contact->next;
    }
}

