/**
 * @file Body.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_BODY_H
#define CANADIANEXPERIENCE_MACHINELIB_BODY_H
#include "Component.h"
#include "IRotationSink.h"

/**
 * A class describing a body of the machine
 *
 */
class Body : public Component, public IRotationSink
{
private:

    /// polygon describing this component
    cse335::PhysicsPolygon mPolygon;

    /// x, y coordinated
    wxPoint2DDouble mPosition;

    /// top left of floor
    wxPoint mOrigin = wxPoint(0,0);

    /// The underlying image we are drawing
    std::unique_ptr<wxImage> mImage;

    /// The graphics bitmap we will use
    wxGraphicsBitmap mBitmap;

    /// IRotation sink
    IRotationSink* mComponent = nullptr;

public:

    Body();
    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon* GetPolygon() {return &mPolygon;}

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void SetImage(std::wstring filename);

    /**
     * Set starting point for the body
     * @param x coord. to set body
     * @param y coord. to set body
     */
    void SetInitialPosition(double x, double y) {mPosition.m_x = x; mPosition.m_y = y;}

    /**
     * Get position of the body
     * @return position to set body
     */
    wxPoint2DDouble GetPosition() {return mPosition;}

    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;

    void Rotate(double rotation, double speed) override;
};

#endif //CANADIANEXPERIENCE_MACHINELIB_BODY_H
