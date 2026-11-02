
#include "ActionInitialization.hh"
#include "DetectorConstruction.hh"
#include "G4MultiSteppingAction.hh"
#include "MuonMinusSteppingAction.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

void ActionInitialization::Build() const {

  // Initilize Generator
  auto *generator = new PrimaryGeneratorAction();
  SetUserAction(generator);

  // Initialize Anaylsis (Histograms)
  auto *runAction = new RunAction();
  SetUserAction(runAction);

  SetUserAction(new MuonMinusSteppingAction(fDetector->GetTargetLogical(),
                                            fDetector->frontZ,
                                            runAction->getMuonDepthId()));
}

void ActionInitialization::BuildForMaster() const {
  SetUserAction(new RunAction);
}
