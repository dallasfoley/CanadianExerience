/**
 * @file MachineSystem.cpp
 * @author dalla
 */

#include "pch.h"
#include "MachineSystem.h"
#include "Machine1Factory.h"
#include "Machine2Factory.h"
using namespace std;

/**
 * Constructor, sets resource directory and machine number
 * @param dir resource directory
 */
MachineSystem::MachineSystem(std::wstring dir)
{
    mResourcesDir = dir;
    SetMachineNumber(1);
}


void MachineSystem::DrawMachine(std::shared_ptr<wxGraphicsContext> graphics)
{
    graphics->PushState();
    graphics->Translate(mLocation.x, mLocation.y);
    graphics->Scale(mPixelsPerCentimeter, -mPixelsPerCentimeter);

    // Draw your machine assuming an origin of 0,0
    mMachine->Draw(graphics);

    //DrawRollingBanner(graphics);

    graphics->PopState();
}


void MachineSystem::SetMachineNumber(int machine)
{
    mMachineNumber = machine;
    if (mMachineNumber == 1)
    {
        Machine1Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->Reset();
    }
    else
    {
        Machine2Factory factory(mResourcesDir);
        mMachine = factory.Create();
        mMachine->Reset();
    }
}


void MachineSystem::SetMachineFrame(int frame)
{
    if(frame < mFrame)
    {
        mFrame = 0;
        mMachine->Reset();
    }

    for( ; mFrame < frame;  mFrame++)
    {
        mMachine->Update(1.0 / mFrameRate);
    }
    mMachineTime = frame / mFrameRate;
}


///**
// * Draw a rolling banner
// * @param graphics Graphics device to render onto
// */
//void MachineSystem::DrawRollingBanner(std::shared_ptr<wxGraphicsContext> graphics)
//{
//    // Load banner image
//    wxImage bannerImage(mResourcesDir + "/images/banner.png", wxBITMAP_TYPE_PNG);
//    wxBitmap bannerBitmap(bannerImage);
//
//    // Set initial position of the banner
//    //float bannerX = mBannerPosition.m_x; // Assume mBannerPosition is a member variable
//
//    // Set the speed at which the banner will roll
//    float speed = 5.0;
//
//    // Move the banner
//    bannerX += speed;
//
//    // If the banner goes off the screen, reset its position
//    if (bannerX > 1000)
//    {
//        bannerX = -bannerBitmap.GetWidth();
//    }
//
//    // Draw the banner on the screen
//    graphics->DrawBitmap(bannerBitmap, bannerX, mBannerPosition.m_y,bannerBitmap.GetWidth(),bannerBitmap.GetHeight());
//}