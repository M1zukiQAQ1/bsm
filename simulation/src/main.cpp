#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "FTFP_BERT.hh"
#include "MyPhysicsList.hh"

#include "G4RunManagerFactory.hh"
#include "G4UIExecutive.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"

int main(int argc, char **argv) {
  auto *runManager = G4RunManagerFactory::CreateRunManager();

  auto *detector = new DetectorConstruction();
  runManager->SetUserInitialization(detector);
  runManager->SetUserInitialization(new FTFP_BERT());

  runManager->SetUserInitialization(new ActionInitialization(detector));
  // runManager->SetUserInitialization(new MyPhysicsList());

  // Register the available visualization systems.
  // auto *visManager = new G4VisExecutive();
  // visManager->Initialize();

  // Build geometry and initialize physics.

  // runManager->SetNumberOfThreads(1);
  runManager->SetNumberOfThreads(16);

  runManager->SetVerboseLevel(1);
  runManager->SetPrintProgress(1);

  runManager->Initialize();
  runManager->BeamOn(1000000);
  // Open the viewer and configure what it displays.
  // auto *ui = G4UImanager::GetUIpointer();
  // ui->ApplyCommand("/control/execute ../macros/vis.mac");

  // delete visManager;
  delete runManager;

  return 0;
}
