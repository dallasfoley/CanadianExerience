/**
 * @file Component.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#define CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
#include "PhysicsPolygon.h"
#include "ContactListener.h"
class Machine;
class b2World;

/**
 * A class describing the basic parts of a machine
 *
 */
class Component
{
private:

    /// Machine associated with this component
    Machine* mMachine;

public:
    Component();
    /**
     * Draw the component
     * @param graphics Graphics context to draw on
     */
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) {}
    /**
     * Update Component
     * @param elapsed time since last update
     */
    virtual void Update(double elapsed) {}
    /**
     * Install physics on the component
     * @param world containing the component
     * @param contactListener the component uses for interactions
     */
    virtual void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) {}

    /**
     * Set the machine this Component is associated with
     * @param machine to associate with
     */
    void SetMachine(Machine* machine) {mMachine = machine;}

    /**
     * Rotate the Component
     * @param rotation angle
     * @param speed of rotation (angular velocity)
     */
    virtual void Rotate(double rotation, double speed) {}


};

#endif //CANADIANEXPERIENCE_MACHINELIB_COMPONENT_H
