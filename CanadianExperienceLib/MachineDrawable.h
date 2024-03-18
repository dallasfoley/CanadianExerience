/**
 * @file MachineDrawable.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#define CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
#include "Drawable.h"
#include "Timeline.h"
#include <machine-api.h>
class IMachineSystem;
class Picture;


/**
 * A drawable class that displays an machine
 */
class MachineDrawable : public Drawable
{
private:
    /// Machine system
    std::shared_ptr<IMachineSystem> mSystem;
    ///Machine's location
    wxPoint2DDouble mPosition;
    /// Resource directory
    std::wstring mResourceDir;
    /// picture this drawable is a part of
    std::shared_ptr<Picture> mPicture = nullptr;


public:

    MachineDrawable(std::wstring resourcesDir);

    void Draw(std::shared_ptr<wxGraphicsContext> graphics);

    /**
    * Set the picture for the root of the machine
    * @param picture The picture to assocoitate the machine
    */
    void SetPicture(std::shared_ptr<Picture> picture) {mPicture = picture;}
    /**
    * Set the position for the root of the machine
    * @param location The x,y location to place the machine
    */
    void SetLocation(wxPoint location) {mSystem->SetLocation(location);}

    /**
     * Get the location of hte machine
     * @return Location x,y in pixels as a point
     */
    wxPoint GetLocation() {return mSystem->GetLocation();}



    /**
    * Set the current machine animation frame
    * @param frame Frame number
    */
    void SetMachineFrame(int frame) {mSystem->SetMachineFrame(frame);}

    /**
     * Set the expected frame rate in frames per second
     * @param rate Frame rate in frames per second
     */
    void SetFrameRate(double rate) {mSystem->SetFrameRate(rate);}

    /**
    * Set the machine number
    * @param machine An integer number. Each number makes a different machine
    */
    void SetMachineNumber(int machine) {mSystem->SetMachineNumber(machine);}

    /**
     * Get the current machine number
     * @return Machine number integer
     */
    int GetMachineNumber() {return mSystem->GetMachineNumber();}

    /**
     * Get the current machine time.
     * @return Machine time in seconds
     */
    double GetMachineTime() {return mSystem->GetMachineNumber();}


    bool HitTest(wxPoint pos) override;



    void IsClicked(wxFrame* parent) override;

};

#endif //CANADIANEXPERIENCE_CANADIANEXPERIENCELIB_MACHINEDRAWABLE_H
