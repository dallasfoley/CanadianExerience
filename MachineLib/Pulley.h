/**
 * @file Pulley.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#define CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
#include "Component.h"
#include "RotationSource.h"
#include "IRotationSink.h"

/**
 * A class describing a Pulley Component
 *
 */
class Pulley : public Component, public IRotationSink
{
private:
    /// Wheel radius
    double mRadius;
    /// Pulley polygon
    cse335::Polygon mWheel1;
    /// Wheel1's position
    wxPoint2DDouble mPosition1;
    /// Wheel2's position
    wxPoint2DDouble mPosition2 = wxPoint2DDouble(0,0);
    /// Pulley's speed
    double mSpeed = 0;
    /// Rotation angle
    double mRotation = 0;
    /// Rotation source
    RotationSource mSource;
    /// Is the Pulley running?
    bool mRunning = false;
    /// Pulley to drive
    std::shared_ptr<Pulley> mDrive;
    /// Pulleys to drive
    std::vector<std::shared_ptr<Pulley>> mDrives;
    /// Is this pulley part of a serpentine system of pulleys?
    bool mSerpentine = false;
    /// Rotation direction of the pulley and Drive positive?
    bool mPositiveToPositive = false;
    /// Rotation direction of the pulley and Drive negative?
    bool mNegativeToNegative = false;
    /// Rotation direction of the pulley positive and Drive negative?
    bool mPositiveToNegative = false;
    /// Rotation direction of the pulley negative and Drive positive?
    bool mNegativeToPositive = false;

public:
    /// Constructor
    Pulley(double radius);
    void SetImage(const std::wstring& filename);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsed) override;
    /**
     * Set starting point for the Pulley
     * @param position to set Pulley
     */
    void SetPosition1(wxPoint2DDouble position) {mPosition1 = position;}
    /**
     * Get position of the Pulley
     * @return position to set Pulley
     */
    wxPoint2DDouble GetPosition() {return mPosition1;}
    /**
     * Get radius of the Pulley
     * @return radius of the Pulley
     */
    double GetRadius() {return mRadius;}
    /**
     * Get a pointer to the source object
     * @return Pointer to RotationSource object
     */
    RotationSource *GetSource() { return &mSource; }

    /**
     * Set rotation angle for the Pulley
     * @param rotation angle to set Pulley
     */
    void SetRotation(double rotation) {mRotation = rotation;}

    void Rotate(double rotation, double speed) override;

    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;

    void Drive(const std::shared_ptr<Pulley>& pulley);

    /**
     * Set the Pulley to a Serpentine Pulley
     */
    void SetSerpentine() {mSerpentine = true;}

    /**
     * Set the Pulley rotations (this pulley and its drive) to positive to positive
     */
    void SetPositiveToPositive() {mPositiveToPositive = true;}
    /**
     * Set the Pulley rotations (this pulley and its drive) to negative to positive
     */
    void SetNegativeToPositive() {mNegativeToPositive = true;}
    /**
     * Set the Pulley rotations (this pulley and its drive) to positive to negative
     */
    void SetPositiveToNegative() {mPositiveToNegative = true;}
    /**
     * Set the Pulley rotations (this pulley and its drive) to negative to negative
     */
    void SetNegativeToNegative() {mNegativeToNegative = true;}



};

#endif //CANADIANEXPERIENCE_MACHINELIB_PULLEY_H
