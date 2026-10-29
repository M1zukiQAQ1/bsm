#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "FTFP_BERT.hh"

int main(int argc, char** argv) {
    auto* session = new G4UIExecutive(argc, argv, "qt");
    auto* runManager = G4RunManagerFactory::CreateRunManager();

    runManager->SetUserInitialization(new DetectorConstruction());
    runManager->SetUserInitialization(new FTFP_BERT());
    runManager->SetUserInitialization(new ActionInitialization());

    // Register the available visualization systems.
    auto* visManager = new G4VisExecutive();
    visManager->Initialize();

    // Build geometry and initialize physics.
    runManager->Initialize();

    // Open the viewer and configure what it displays.
    auto* ui = G4UImanager::GetUIpointer();
    ui->ApplyCommand("/control/execute ../vis.mac");

    // Keep the interactive window open.
    session->SessionStart();

    delete session;
    delete visManager;
    delete runManager;
    return 0;
}