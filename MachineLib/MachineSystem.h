/**
 * @file MachineSystem.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#define CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
#include "IMachineSystem.h"
#include "Machine.h"

class Component;


/**
 * Handles functionality of machine.
 *
 */
class MachineSystem : public IMachineSystem
{
private:

    /// Actual Machine object
    std::shared_ptr<Machine> mMachine;

    /// location of machine
    wxPoint mLocation;

    /// Resource directory
    std::wstring mResourcesDir;

    /// How many pixels there are for each CM
    double mPixelsPerCentimeter = 1.5;

    /// machine's number (1 or 2)
    int mMachineNumber = 1;

    /// running time of machine in seconds
    double mMachineTime = 0;

    /// frame rate
    double mFrameRate = 30.0;

    /// current frame
    int mFrame = 0;

    ///flag number
    int mFlag;

    //wxPoint2DDouble mBannerPosition = wxPoint2DDouble(500,500);

public:

    MachineSystem(std::wstring dir);
    /**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
    void SetLocation(wxPoint location) override {mLocation = location;}

    /**
     * Get the location of hte machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() override {return mLocation;}

    /**
    * Draw the machine at the currently specified location
    * @param graphics Graphics object to render to
    */
    void DrawMachine(std::shared_ptr<wxGraphicsContext> graphics) override;

    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    void SetMachineFrame(int frame) override;

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) override {mFrameRate = rate;}

    /**
    * Set the machine number
    * @param machine An integer number. Each number makes a different machine
    */
    void SetMachineNumber(int machine) override;

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() override {return mMachineNumber;}
    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() override {return mMachineTime;}

    /**
     * Set the flag from the control panel
     * @param flag Flag to set
     */
    void SetFlag(int flag) override {mFlag = flag;}

    //void DrawRollingBanner(std::shared_ptr<wxGraphicsContext> graphics);
};

#endif //CANADIANEXPERIENCE_MACHINELIB_MACHINESYSTEM_H
