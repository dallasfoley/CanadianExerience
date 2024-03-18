/**
 * @file Hamster.cpp
 * @author dalla
 */
#include "pch.h"
#include <sstream>
#include "Polygon.h"
#include "Hamster.h"

using namespace std;

/// The center point for drawing the wheel
/// relative to the bottom center of the cage
const auto WheelCenter = wxPoint2DDouble(-12, 24);

/// The size of the hamster cage in centimeters
const auto HamsterCageSize = wxSize(75, 50);

/// Size of the hamster wheel (diameter) in centimeters
const double HamsterWheelSize = 45;

/// Size of the hamster wheel (square) in centimeters
const double HamsterSize = 45;

/// How fast the hamster runs. This is now many cycles of
/// the 3 images we make per second as images 1, 2, 3, 2, ...
const double HamsterSpeed = 4.0;

/// The offset from the bottom center of the hamster cage
/// to the center of the output shaft.
const auto HamsterShaftOffset = wxPoint2DDouble(25, 40);

/// The image for the hamster cage
const std::wstring HamsterCageImage = L"/hamster-cage.png";

/// The image for the hamster wheel
const std::wstring HamsterWheelImage = L"/hamster-wheel.png";

/// The hamster images. Image 0 is sleeping, 1-3 are
/// the running hamster animation images.
const std::wstring HamsterImages[4] =
    {L"/hamster-sleep.png", L"/hamster-run-1.png",
        L"/hamster-run-2.png", L"/hamster-run-3.png"};

/**
 * Constructor
 * @param imagesDir image directory
 */
Hamster::Hamster(const std::wstring& imagesDir): mSource(this, imagesDir)
{
    mImagesDir = imagesDir;
    mCage.BottomCenteredRectangle(HamsterCageSize);
    mCage.SetImage(imagesDir + HamsterCageImage);
    mWheel.CenteredSquare(HamsterWheelSize);
    mWheel.SetImage(imagesDir + HamsterWheelImage);
    mHamster1.CenteredSquare(HamsterSize);
    mHamster1.SetImage(imagesDir + HamsterImages[0]);
    mHamster2.CenteredSquare(HamsterSize);
    mHamster2.SetImage(imagesDir + HamsterImages[1]);
    mHamster3.CenteredSquare(HamsterSize);
    mHamster3.SetImage(imagesDir + HamsterImages[2]);
    mHamster4.CenteredSquare(HamsterSize);
    mHamster4.SetImage(imagesDir + HamsterImages[3]);
}

/**
 * Draw the Hamster
 * @param graphics Graphics device to render onto
 */
void Hamster::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mCage.Draw(graphics);
    mWheel.DrawPolygon(graphics,mPosition.m_x + WheelCenter.m_x,mPosition.m_y + WheelCenter.m_y,mRotation);
    graphics->PushState();
    graphics->Translate(mPosition.m_x + WheelCenter.m_x, mPosition.m_y + WheelCenter.m_y);
    if(mSpeed < 0)
    {
        graphics->Scale(-1, 1);
    }
    // Draw the running image
    if (mHamsterImageNumber == 0)
        mHamster1.DrawPolygon(graphics,0,0,0);
    if (mHamsterImageNumber == 1)
        mHamster2.DrawPolygon(graphics,0,0,0);
    if (mHamsterImageNumber == 2)
        mHamster3.DrawPolygon(graphics,0,0,0);
    if (mHamsterImageNumber == 3)
        mHamster4.DrawPolygon(graphics,0,0,0);
    graphics->PopState();
}

/**
 * Update the Hamster
 * @param elapsed time since last update
 */
void Hamster::Update(double elapsed)
{
    // This is incomplete...
    if (mRunning)
    {
        if (mHamsterImageNumber == 3)
        {
            mIncreasing = false;
        }
        else if (mHamsterImageNumber == 1)
        {
            mIncreasing = true;
        }
        if (mIncreasing)
            mHamsterImageNumber++;
        else
            mHamsterImageNumber--;
        mRotation += -mSpeed * elapsed;
        mSource.SetRotation(mRotation, -mSpeed);
    }
}

/**
 * Install physics on the goal
 * @param world containing the goal
 * @param contactListener the goal uses for interactions
 */
void Hamster::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)
{
    mCage.InstallPhysics(world);
    contactListener->Add(mCage.GetBody(), this);
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Hamster::BeginContact(b2Contact *contact)
{
    // Turn the hamster on
    mRunning = true;
}

/**
     * Get position of the Hamster
     * @return position to set Hamster
     */
wxPoint2DDouble Hamster::GetShaftPosition()
{
    return {mPosition.m_x + HamsterShaftOffset.m_x, mPosition.m_y + HamsterShaftOffset.m_y};
}

