/**
 * @file Pulley.cpp
 * @author dalla
 */
#include "pch.h"
#include <cmath>

#include "Pulley.h"

using namespace std;

/**
 * Constructor
 * @param radius of wheels
 */
Pulley::Pulley(double radius)
{
    mRadius = radius;
    mWheel1.CenteredSquare(mRadius * 2);
}

/**
     * Set image for the Pulley
     * @param filename to set Pulley image
     */
void Pulley::SetImage(const std::wstring& filename)
{
    mWheel1.SetImage(filename);
}

/**
 * Draw the Pulley
 * @param graphics Graphics device to render onto
 */
void Pulley::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mWheel1.DrawPolygon(graphics, mPosition1.m_x, mPosition1.m_y, mRotation);
    if (mPosition2 != wxPoint2DDouble(0,0))

    {
        wxPoint2DDouble diff = wxPoint2DDouble(mPosition2 - mPosition1);

        double x_square = diff.m_x * diff.m_x;
        double y_square = diff.m_y * diff.m_y;

        double denom = sqrt(x_square + y_square);

        wxPoint2DDouble alpha = mRadius * wxPoint2DDouble(mPosition2 - mPosition1) / denom;
        wxPoint2DDouble beta = wxPoint2DDouble(-alpha.m_y,alpha.m_x);
        wxPen eyebrowPen(*wxBLACK, 2);
        graphics->SetPen(eyebrowPen);
        if (!mSerpentine)
        {
            graphics->StrokeLine(mPosition1.m_x + beta.m_x, mPosition1.m_y + beta.m_y, mPosition2.m_x + beta.m_x, mPosition2.m_y + beta.m_y);
            graphics->StrokeLine(mPosition1.m_x - beta.m_x, mPosition1.m_y - beta.m_y, mPosition2.m_x - beta.m_x, mPosition2.m_y - beta.m_y);
        }
        else
        {
            if (mPositiveToPositive)
            {
                double theta = atan2(diff.m_y, diff.m_x);
                double phi_arg = (mRadius - mDrive->GetRadius())/(denom);
                double phi = asin(phi_arg);
                double pi = 3.14159265359;
                double beta = theta + phi + pi/2;
                graphics->StrokeLine(mPosition1.m_x + mRadius * cos(beta), mPosition1.m_y + mRadius * sin(beta),
                                     mPosition2.m_x + mDrive->GetRadius() * cos(beta), mPosition2.m_y + mDrive->GetRadius() * sin(beta));

            }
            else if(mPositiveToNegative)
            {
                double theta = atan2(diff.m_y, diff.m_x);
                double phi_arg = (mRadius + mDrive->GetRadius())/(denom);
                double phi = asin(phi_arg);
                double pi = 3.14159265359;
                double beta = theta - phi + pi/2;
                graphics->StrokeLine(mPosition1.m_x + mRadius * cos(beta), mPosition1.m_y + mRadius * sin(beta),
                                     mPosition2.m_x - mDrive->GetRadius() * cos(beta), mPosition2.m_y - mDrive->GetRadius() * sin(beta));
            }
            else if (mNegativeToPositive)
            {
                double theta = atan2(diff.m_y, diff.m_x);
                double phi_arg = (mRadius + mDrive->GetRadius())/(denom);
                double phi = asin(phi_arg);
                double pi = 3.14159265359;
                double beta = theta + phi + 3*pi/2;
                graphics->StrokeLine(mPosition1.m_x + mRadius * cos(beta), mPosition1.m_y + mRadius * sin(beta),
                                     mPosition2.m_x - mDrive->GetRadius() * cos(beta), mPosition2.m_y - mDrive->GetRadius() * sin(beta));

            }
            else if (mNegativeToNegative)
            {
                double theta = atan2(diff.m_y, diff.m_x);
                double phi_arg = (mRadius + mDrive->GetRadius())/(denom);
                double phi = asin(phi_arg);
                double pi = 3.14159265359;
                double beta = theta + phi + 3*pi/2;
                graphics->StrokeLine(mPosition1.m_x + mRadius * cos(beta), mPosition1.m_y + mRadius * sin(beta),
                                     mPosition2.m_x + mDrive->GetRadius() * cos(beta), mPosition2.m_y + mDrive->GetRadius() * sin(beta));

            }

        }

    }


}

/**
 * Update the Pulley
 * @param elapsed time since last update
 */
void Pulley::Update(double elapsed)
{
    //mRotation += -mSpeed * elapsed;
}


/**
 * Install physics on the pulley
 * @param world containing the pulley
 * @param contactListener the pulley uses for interactions
 */
void Pulley::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)
{
    //mWheel1.InstallPhysics(world);
}


/**
 * Rotate the Pulley
 * @param rotation angle
 * @param speed of rotation (angular velocity)
 */
void Pulley::Rotate(double rotation, double speed)
{
    mRotation = rotation;
    mSource.SetRotation(rotation, speed);
    mDrive->SetRotation(rotation * (mRadius / mDrive->GetRadius()));
    mDrive->GetSource()->SetRotation(rotation, speed);

}

/**
 * Rotate the connected Pulley
 * @param pulley to drive
 */
void Pulley::Drive(const std::shared_ptr<Pulley>& pulley)
{
    mDrive = pulley;
    mPosition2 = pulley->GetPosition();
}
