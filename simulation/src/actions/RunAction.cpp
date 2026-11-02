
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"

RunAction::RunAction() {
  auto *analysisManager = G4AnalysisManager::Instance();

  // Create a 1-Dimension Histogram for Muon Stopping Distance inside the Target
  muonDepthId = analysisManager->CreateH1(
      "muon_stopping_distance",
      "Muon Stopping Distance (Displacement);Distance(mm);Entries", 100,
      0.0 * mm, 2 * mm, "mm");
}

int RunAction::getMuonDepthId() { return muonDepthId; }

void RunAction::BeginOfRunAction(const G4Run *) {
  // Open an output file for the histograms filled during this run
  G4AnalysisManager::Instance()->OpenFile("muon_stopping.root");
}

void RunAction::EndOfRunAction(const G4Run *) {
  auto *analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
