/**
 * @file Goal.h
 * @author dalla
 *
 *
 */

#ifndef CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#define CANADIANEXPERIENCE_MACHINELIB_GOAL_H
#include "Component.h"
#include <b2_world_callbacks.h>
class ContactListener;
/**
 * Handles functionality and draws the goal
 *
 */
class Goal : public Component, public b2ContactListener
{
private:
    /// current score
    int mScore;

    /// current position
    wxPoint2DDouble mPosition;

    /// The polygon object for the goal image
    cse335::Polygon mPolygon;

    /// Physics polygon for the backboard/post
    cse335::PhysicsPolygon mPost;

    /// Polygon that we are going to hit to
    /// determine the basket has been scored
    cse335::PhysicsPolygon mGoal;

    /// Resource directory
    std::wstring mResourcesDir;

public:
    Goal(std::wstring dir);
    void BeginContact(b2Contact *contact) override;
    void PreSolve(b2Contact *contact, const b2Manifold *oldManifold) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void InstallPhysics(std::shared_ptr<b2World> world, std::shared_ptr<ContactListener> contactListener) override;

    /**
     * Set starting point for the Goal
     * @param x coord. to set Goal
     * @param y coord. to set Goal
     */
    void SetInitialPosition(double x, double y);

    /**
     * Get position of the body
     * @return position to set body
     */
    wxPoint2DDouble GetPosition() {return mPosition;}

};

#endif //CANADIANEXPERIENCE_MACHINELIB_GOAL_H
