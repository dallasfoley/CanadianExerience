/**
 * @file Machine.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINE_H

class Component;
class ContactListener;
class b2World;

/**
 * Instantiation of MachineSystem
 *
 */
class Machine
{
private:

    /// Components that make up the machine
    std::vector<std::shared_ptr<Component>> mComponents;

    /// Machine number (1 or 2)
    int mMachineNumber;

    /// The box2d world
    std::shared_ptr<b2World> mWorld;

    /// The installed contact filter
    std::shared_ptr<ContactListener> mContactListener;

    /// Resource directory
    std::wstring mResourcesDir;

/// running time of machine in seconds
    double mMachineTime;

    /// frame rate
    double mFrameRate;

    /// current frame
    int mFrame;


public:
    explicit Machine(int machineNumber);
    void AddComponent(std::shared_ptr<Component> component);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Update(double elapsed);
    void Reset();



};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINE_H
