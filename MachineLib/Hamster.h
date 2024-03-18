/**
 * @file Hamster.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#define CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
#include "Component.h"
#include "RotationSource.h"



/**
 * A class describing a Hamster Component
 *
 */
class Hamster : public Component, public b2ContactListener
{
private:
    /// Hamster Cage
    cse335::PhysicsPolygon mCage;
    /// Hamster wheel
    cse335::Polygon mWheel;
    /// Hamster 1 (sleeping)
    cse335::Polygon mHamster1;
    /// Hamster 2
    cse335::Polygon mHamster2;
    /// Hamster 3
    cse335::Polygon mHamster3;
    /// Hamster 4
    cse335::Polygon mHamster4;
    /// Image directory
    std::wstring mImagesDir;
    /// Hamster's position
    wxPoint2DDouble mPosition;
    /// Hamster's speed
    double mSpeed = 0;
    /// Rotation angle
    double mRotation = 0;
    /// Is the hamster running to start?
    bool mInitiallyRunning = false;
    /// Is the hamster running?
    bool mRunning = false;
    /// Rotation source
    RotationSource mSource;
    /// Hamster image number
    int mHamsterImageNumber = 0;
    /// Is the Hamster image number increasing
    bool mIncreasing = true;
    /// Amount of rotations
    int mRotationNumber = 0;




public:
    Hamster(const std::wstring& imagesDir);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;

    /**
     * Set starting point for the Hamster
     * @param position to set Hamster
     */
    void SetPosition(wxPoint2DDouble position) {mPosition = position;}

    /**
     * Get position of the Hamster
     * @return position to set Hamster
     */
    wxPoint2DDouble GetPosition() {return mPosition;}
    /**
     * Set the initial running condition
     * @param running condition to set
     */
     void SetInitiallyRunning(bool running) {mInitiallyRunning = mRunning = running;}
    /**
    * Set speed for the Hamster
    * @param speed to set Hamster
    */
    void SetSpeed(double speed) {mSpeed = speed;}

    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;

    void BeginContact(b2Contact *contact) override;

    /**
     * Get a pointer to the polygon this body uses
     * @return Pointer to the polygon object
     */
    cse335::PhysicsPolygon* GetCagePolygon() {return &mCage;}

    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }


    wxPoint2DDouble GetShaftPosition();

};

#endif //CANADIANEXPERIENCE_MACHINELIB_HAMSTER_H
