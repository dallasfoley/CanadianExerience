/**
 * @file PictureFactory.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include "MachineDrawable.h"
#include "PictureFactory.h"
#include "Picture.h"
#include "HaroldFactory.h"
#include "SpartyFactory.h"
#include "Actor.h"
#include "ImageDrawable.h"


/// Directory within resources that contains the images.
const std::wstring ImagesDirectory = L"/images";


/**
 * Factory method to create a new picture.
 * @param resourcesDir Directory that contains the resources for this application
 * @return The created picture
 */
std::shared_ptr<Picture> PictureFactory::Create(std::wstring resourcesDir)
{
    auto imagesDir = resourcesDir + ImagesDirectory;

    auto picture = std::make_shared<Picture>();

    // Create the background and add it
    auto background = std::make_shared<Actor>(L"Background");
    background->SetClickable(false);
    background->SetPosition(wxPoint(0, 0));
    auto backgroundI =
            std::make_shared<ImageDrawable>(L"Background", imagesDir + L"/Background.jpg");
    background->AddDrawable(backgroundI);
    background->SetRoot(backgroundI);
    picture->AddActor(background);

    // Create and add Harold
    HaroldFactory haroldFactory;
    auto harold = haroldFactory.Create(imagesDir);

    // This is where Harold will start out.
    harold->SetPosition(wxPoint(300, 600));
    picture->AddActor(harold);

    // Create and add Sparty
    SpartyFactory spartyFactory;
    auto sparty = spartyFactory.Create(imagesDir);

    sparty->SetPosition(wxPoint(550, 620));
    picture->AddActor(sparty);

    auto actor1 = std::make_shared<Actor>(L"Machine1");

    std::shared_ptr<MachineDrawable> machine1 = std::make_shared<MachineDrawable>(resourcesDir);
    machine1->SetMachineNumber(1);
    actor1->SetPosition(wxPoint(0,0));
    machine1->SetPosition(wxPoint(500,500));
    machine1->SetLocation(wxPoint(500,500));
    actor1->AddDrawable(machine1);
    actor1->SetRoot(machine1);
    picture->AddActor(actor1);

    auto actor2 = std::make_shared<Actor>(L"Machine2");

    std::shared_ptr<MachineDrawable> machine2 = std::make_shared<MachineDrawable>(resourcesDir);
    machine2->SetMachineNumber(2);
    actor2->SetPosition(wxPoint(0,0));
    machine2->SetPosition(wxPoint(700,600));
    machine2->SetLocation(wxPoint(700,600));
    actor2->AddDrawable(machine2);
    actor2->SetRoot(machine2);
    picture->AddActor(actor2);

    picture->SetMachineSystem(machine1);
    machine1->SetPicture(picture);

    machine1->SetTimeline(picture->GetTimeline());
    machine2->SetTimeline(picture->GetTimeline());


    return picture;
}

