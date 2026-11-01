
#include "ActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"
#include "RunAction.hh"

void ActionInitialization::Build() const {

  // Initilize Generator
  auto *generator = new PrimaryGeneratorAction();
  SetUserAction(generator);

  // Initialize Anaylsis (Histograms)
  auto *runAction = new RunAction();
  SetUserAction(runAction);
}
