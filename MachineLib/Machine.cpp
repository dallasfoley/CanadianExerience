/**
 * @file Machine.cpp
 * @author dalla
 */

#include "pch.h"
#include "Machine.h"
#include "Component.h"
#include "ContactListener.h"
#include <b2_world.h>
#include "PhysicsPolygon.h"
using namespace std;

/// Gravity in meters per second per second
const float Gravity = -9.8f;

/// Number of velocity update iterations per step
const int VelocityIterations = 6;

/// Number of position update iterations per step
const int PositionIterations = 2;

/**
 * Constructor
 * @param machineNumber to set machine
 */
Machine::Machine(int machineNumber)
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));

    mMachineNumber = machineNumber;
}

/**
 * Add a Component to the machine
 * @param component to add
 */
void Machine::AddComponent(std::shared_ptr<Component> component)
{
    mComponents.push_back(component);
    component->SetMachine(this);
}

/**
 * Draw the machine
 * @param graphics Graphics device to render onto
 */
void Machine::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    for (auto component: mComponents)
    {
        component->Draw(graphics);
    }
}

/**
 * Update the machine
 * @param elapsed time since last update
 */
void Machine::Update(double elapsed)
{
    // Call Update on all of our components so they can advance in time
    for (auto component: mComponents)
    {
        component->Update(elapsed);
    }

    // Advance the physics system one frame in time
    mWorld->Step(elapsed, VelocityIterations, PositionIterations);
}

/**
 * Reset the machine
 */
void Machine::Reset()
{
    mWorld = std::make_shared<b2World>(b2Vec2(0.0f, Gravity));
    // Create and install the contact filter
    mContactListener = std::make_shared<ContactListener>();

    mWorld->SetContactListener(mContactListener.get());
    for (auto component: mComponents)
    {
       component->InstallPhysics(mWorld, mContactListener);
    }

}
