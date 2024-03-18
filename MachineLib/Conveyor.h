/**
 * @file Conveyor.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#define CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
#include "Component.h"
#include "IRotationSink.h"

/**
 * A class describing a Conveyor Component
 *
 */
class Conveyor : public Component, public IRotationSink
{
private:
    /// Conveyor polygon
    cse335::PhysicsPolygon mConveyor;
    /// Conveyor's position
    wxPoint2DDouble mPosition;
    /// Conveyor's speed
    double mSpeed = 0;

public:
    Conveyor(std::wstring imagesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;

    void Update(double elapsed) override;

    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;

    void Rotate(double rotation, double speed) override;

    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon* GetPolygon() {return &mConveyor;}

    /**
     * Set position for the Conveyor
     * @param position to set Conveyor
     */
    void SetPosition(wxPoint2DDouble position) {mPosition = position;}
    /**
     * Get position of the Conveyor
     * @return position of Conveyor
     */
    wxPoint2DDouble GetPosition() {return mPosition;}

    wxPoint2DDouble GetShaftPosition();

    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);


};

#endif //CANADIANEXPERIENCE_MACHINELIB_CONVEYOR_H
