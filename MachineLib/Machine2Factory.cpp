/**
 * @file Machine2Factory.cpp
 * @author dalla
 */

#include "pch.h"
#include "Machine2Factory.h"
#include "Machine.h"
#include "Body.h"
#include "Goal.h"
#include "Hamster.h"
#include "Pulley.h"
#include "Conveyor.h"
#include "HamsterAndConveyorFactory.h"

/// The images directory in resources
const std::wstring ImagesDirectory = L"/images";

/**
 * Constructor
 * @param resourcesDir Directory containing the machine resources
 */
Machine2Factory::Machine2Factory(std::wstring resourcesDir) : mResourcesDir(resourcesDir)
{

}

/**
 * Create a machine
 * @return Pointer to newly created machine
 */
std::shared_ptr<Machine> Machine2Factory::Create()
{
    auto machine = std::make_shared<Machine>(2);

    auto hamster = std::make_shared<Hamster>(mResourcesDir + ImagesDirectory);
    //mHamster = hamster;
    hamster->SetPosition(wxPoint2DDouble(-50,120));
    hamster->GetCagePolygon()->SetInitialPosition(-50,120);
    hamster->SetInitiallyRunning(true);
    hamster->SetSpeed(1.0);
    machine->AddComponent(hamster);
    auto hamsterShaft = hamster->GetShaftPosition();

//    auto pulley1 = std::make_shared<Pulley>(10);
//    pulley1->SetImage(mResourcesDir + ImagesDirectory + L"/pulley3.png");
//    pulley1->SetPosition1(hamsterShaft);
//    machine->AddComponent(pulley1);



    auto pulley2 = std::make_shared<Pulley>(10);
    pulley2->SetImage(mResourcesDir + ImagesDirectory + L"/pulley3.png");
    pulley2->SetPosition1(hamsterShaft);
    machine->AddComponent(pulley2);

    hamster->GetSource()->AddSink(pulley2);

//    pulley1->Drive(pulley2);
//    pulley1->GetSource()->AddSink(pulley2);
    //pulley1->SetSerpentine();
    //pulley1->SetPositiveToPositive();

    auto pulley3 = std::make_shared<Pulley>(35);
    pulley3->SetImage(mResourcesDir + ImagesDirectory + L"/pulley2.png");
    pulley3->SetPosition1(wxPoint2DDouble(50,275));
    machine->AddComponent(pulley3);

    pulley2->GetSource()->AddSink(pulley3);

    pulley2->Drive(pulley3);
    pulley2->SetSerpentine();
    pulley2->SetPositiveToPositive();

    auto pulley4 = std::make_shared<Pulley>(15);
    pulley4->SetImage(mResourcesDir + ImagesDirectory + L"/pulley1.png");
    pulley4->SetPosition1(wxPoint2DDouble(100,200));
    machine->AddComponent(pulley4);

    pulley3->GetSource()->AddSink(pulley4);

    pulley3->Drive(pulley4);
    pulley3->SetSerpentine();
    pulley3->SetPositiveToNegative();

    auto pulley5 = std::make_shared<Pulley>(15);
    pulley5->SetImage(mResourcesDir + ImagesDirectory + L"/pulley1.png");
    pulley5->SetPosition1(wxPoint2DDouble(150,275));
    machine->AddComponent(pulley5);

    pulley4->GetSource()->AddSink(pulley5);

    pulley4->Drive(pulley5);
    pulley4->SetSerpentine();
    pulley4->SetNegativeToPositive();

    auto pulley6 = std::make_shared<Pulley>(25);
    pulley6->SetImage(mResourcesDir + ImagesDirectory + L"/pulley2.png");
    pulley6->SetPosition1(wxPoint2DDouble(200,150));
    machine->AddComponent(pulley6);

    //pulley5->GetSource()->AddSink(pulley6);

    pulley5->Drive(pulley6);
    pulley5->SetSerpentine();
    pulley5->SetPositiveToPositive();

    pulley6->Drive(pulley2);
    pulley6->SetSerpentine();
    pulley6->SetPositiveToPositive();



    return machine;
}
