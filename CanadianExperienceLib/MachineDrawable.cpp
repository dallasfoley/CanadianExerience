/**
 * @file MachineDrawable.cpp
 * @author dalla
 */
#include "pch.h"
#include <gdiplus.h>
#include <GdiplusGraphics.h>
#include "MachineDrawable.h"
#include "Picture.h"

/**
 * Constructor
 * @param resourcesDir the resource directory
 */
MachineDrawable::MachineDrawable(std::wstring resourcesDir): mResourceDir(resourcesDir)
{
    MachineSystemFactory factory(resourcesDir);
    std::shared_ptr<IMachineSystem> machine = factory.CreateMachineSystem();
    mSystem = machine;

}


//void MachineDrawable::Draw(Gdiplus::Graphics *graphics)
//{
//    double scale = 0.0025f;
//
//    graphics->PushState();
//    graphics.Translate(mPlacedPosition.x, mPlacedPosition.y);
//    graphics->Scale(scale, scale);
//    mSystem->SetLocation(wxPoint(300, 300));
//    mSystem->DrawMachine(graphics);
//    graphics->PopState();
//}

/**
 * Draw this MachineDrawable
 * @param graphics The Graphics object we are drawing on
 */
void MachineDrawable::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    double scale = 0.75f;
    SetMachineFrame(GetAngleChannel()->GetTimeline()->GetCurrentFrame());
    graphics->PushState();
    graphics->Translate(mPlacedPosition.x, mPlacedPosition.y);
    //graphics->Scale(scale, scale);
    mSystem->SetLocation(wxPoint(0, 0));
    mSystem->DrawMachine(graphics);
    graphics->PopState();
}


/**
 * Handle when the drawable is clicked
 * @param parent New parent pointer
 */
void MachineDrawable::IsClicked(wxFrame* parent)
{
    MachineDialog dlg(parent, mSystem);
    if (dlg.ShowModal() == wxID_OK)
    {
        // A machine has been selected
    }
}

/**
 * Test if drawable it hitting anything
 * @param pos position to test
 * @return if drawable is hitting anything
 */
bool MachineDrawable::HitTest(wxPoint pos)
{
    double wid = 0; double hit = 0;
    if (GetMachineNumber() == 1)
    {
        wid = 500;
        hit = 500;
    }
    else if (GetMachineNumber() == 2)
    {
        wid = 400;
        hit = 400;
    }


    // Make x and y relative to the top-left corner of the bitmap image

    double testX = pos.x - GetPlacedPosition().x + wid / 2;
    double testY = pos.y - GetPlacedPosition().y + hit / 2;

    // if we are out of the image, return false
    if (testX < 0 || testY < 0 || testX > wid || testY > hit)
        {return false;}

    return true;
}


