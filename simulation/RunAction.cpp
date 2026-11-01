
#include "RunAction.hh"
#include "G4AnalysisManager.hh"

RunAction::RunAction() {
  auto *analysisManager = G4AnalysisManager::Instance();
}
