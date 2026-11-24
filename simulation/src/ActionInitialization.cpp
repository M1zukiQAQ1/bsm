
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "ElectronSpectrumSteppingAction.hh"
#include "G4MultiSteppingAction.hh"
#include "MuonMinusSteppingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

#include <memory>

void ActionInitialization::Build() const {

  // Initilize Generator
  auto *generator = new PrimaryGeneratorAction();
  SetUserAction(generator);

  // Initialize Anaylsis (Histograms)
  auto *runAction = new RunAction();
  SetUserAction(runAction);

  // Each stepping action fills one histogram; run them all on every step
  auto *steppingActions = new G4MultiSteppingAction();
  steppingActions->push_back(std::make_unique<MuonMinusSteppingAction>(
      fDetector, runAction->getMuonDepthId()));
  steppingActions->push_back(std::make_unique<ElectronSpectrumSteppingAction>(
      fDetector->GetTargetLogical(), runAction->getElectronSpectrumId()));
  SetUserAction(steppingActions);
}

void ActionInitialization::BuildForMaster() const {
  SetUserAction(new RunAction);
}
