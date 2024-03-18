/**
 * @file Goal.cpp
 * @author dalla
 */
#include "pch.h"
#include "Goal.h"
#include "PhysicsPolygon.h"
#include "ContactListener.h"
#include <sstream>
#include <b2_contact.h>

using namespace std;

/// Image to draw for the goal
const std::wstring GoalImage = L"/goal.png";

/// Size to draw the entire goal post image
/// This does not go into the physics system at all
const auto GoalSize = wxSize(65, 247);

/// Size to create a rectangle in the physics system only
/// (does not draw) to reflect off of the backboard and post
const auto PostSize = wxSize(10, 250);

/// Size of a target object inside the goal net that
/// we'll consider a score when touched by a ball
const auto TargetSize = wxSize(20, 5);

/// The color of the scoreboard background
const auto ScoreboardBackgroundColor = wxColor(24, 69, 59);

/// Width of the black line around the scoreboard
const int ScoreboarderLineWidth = 3;

/// Scoreboard font size (height) in cm
/// The font color is white
const int ScoreboardFontSize = 20;

/// Rectangle that represents the location relative to the
/// goal position for the scoreboard and its size.
const auto ScoreboardRectangle = wxRect2DDouble(5, 280, 30, 20);

/// Location of the scoreboard text relative to the
/// scoreboard location in cm.
const auto ScoreboardTextLocation = wxPoint2DDouble(9, 299);

/// Position of the goalpost polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble PostPosition = wxPoint2DDouble(22, 0);

/// Position of the basket goal polygon relative to the entire goal
/// This plus the location set by SetPosition is where to draw
/// the goalpost PhysicsPolygon object.
const wxPoint2DDouble GoalPosition = wxPoint2DDouble(-12, 165);

/**
 * Constructor
 * @param dir image directory
 */
Goal::Goal(std::wstring dir)
{
    //contactListener->Add(mGoal.GetBody(), this);
    mScore = 0;
    mResourcesDir = dir;

    mPolygon.BottomCenteredRectangle(GoalSize);
    mPolygon.SetImage(mResourcesDir + GoalImage);

    mPost.BottomCenteredRectangle(PostSize);
    mPost.SetColor(*wxBLUE);

    mGoal.BottomCenteredRectangle(TargetSize);
    mGoal.SetColor(*wxBLUE);
}

/**
 * Draw the Goal
 * @param graphics Graphics device to render onto
 */
void Goal::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    mPolygon.DrawPolygon(graphics,GetPosition().m_x,PostPosition.m_y,0);
    //mPost.Draw(graphics);
    //mGoal.Draw(graphics);
    graphics->SetBrush(wxBrush(wxColour(0, 60, 0)));  // Set brush to green
    wxPen pen(wxColour(0, 0, 0), 1, wxPENSTYLE_SOLID);  // Set pen color and style
    graphics->SetPen(pen);


    // Draw text on the green rectangle
    wxFont font(wxSize(10, 20),
                wxFONTFAMILY_SWISS,
                wxFONTSTYLE_NORMAL,
                wxFONTWEIGHT_BOLD);
    graphics->SetFont(font, wxColour(250, 250, 250));
    ostringstream score;
    if (mScore < 10)
    {
        score << '0' << mScore;
    }
    else
    {
        score << mScore;
    }
    graphics->PushState();
    graphics->Translate(mPosition.m_x + ScoreboardTextLocation.m_x,mPosition.m_y + ScoreboardTextLocation.m_y);
    graphics->Scale(1, -1);
    graphics->DrawRectangle(0,0, ScoreboardRectangle.m_width, ScoreboardRectangle.m_height);
    graphics->DrawText(score.str(), 4, 0);

    graphics->PopState();
}

/**
 * Handle a contact beginning
 * @param contact Contact object
 */
void Goal::BeginContact(b2Contact *contact)
{
    mScore += 2;
}

/**
 * Handle before the solution of a contact with the
 * scoreboard target object. We take this time to
 * turn off the contact, so the ball will pass through.
 * @param contact Contact object
 * @param oldManifold Manifold object
 */
void Goal::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
    contact->SetEnabled(false);
}


/**
 * Install physics on the goal
 * @param world containing the goal
 * @param contactListener the goal uses for interactions
 */
void Goal::InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener)
{
    mPost.InstallPhysics(world);
    mGoal.InstallPhysics(world);
    contactListener->Add(mGoal.GetBody(), this);
    contactListener->Add(mPost.GetBody(), this);
}

void Goal::SetInitialPosition(double x, double y)
{
    mPosition.m_x = x;
    mPosition.m_y = y;
    mGoal.SetInitialPosition(x + PostPosition.m_x,y);
    mPost.SetInitialPosition(x + PostPosition.m_x,y);
}
