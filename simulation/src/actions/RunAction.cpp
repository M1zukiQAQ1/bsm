
#include "RunAction.hh"
#include "DetectorConstruction.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include <CLHEP/Units/SystemOfUnits.h>

#include <cmath>

RunAction::RunAction() {
  auto *analysisManager = G4AnalysisManager::Instance();

  // Stopping depth of primary mu- below the target's front face. Span the
  // whole target so a higher beam energy cannot silently overflow.
  constexpr G4double depthBinWidth = 0.02 * mm;
  const auto depthBins = static_cast<G4int>(
      std::lround(DetectorConstruction::thickness / depthBinWidth));
  muonDepthId = analysisManager->CreateH1(
      "muon_stopping_distance", "Muon Stopping Depth in Target", depthBins,
      0.0 * mm, DetectorConstruction::thickness, "mm");
  analysisManager->SetH1XAxisTitle(muonDepthId, "Depth below front face [mm]");
  analysisManager->SetH1YAxisTitle(muonDepthId, "Entries / 0.02 mm");

  // Decay-in-orbit electrons from stopped mu-. Bound-muon motion smears the
  // spectrum past the free Michel edge (52.8 MeV), so keep room for the tail.
  // Axis titles must be set separately: unlike ROOT, the G4 analysis manager
  // does not split "title;x;y" into axis titles.
  electronSpectrumId = analysisManager->CreateH1(
      "electron_spectrum", "Muon Decay-in-Orbit Electron Spectrum", 220,
      0.0 * MeV, 110 * MeV, "MeV");
  analysisManager->SetH1XAxisTitle(electronSpectrumId, "Kinetic Energy [MeV]");
  analysisManager->SetH1YAxisTitle(electronSpectrumId, "Entries / 0.5 MeV");
}

int RunAction::getMuonDepthId() { return muonDepthId; }

int RunAction::getElectronSpectrumId() { return electronSpectrumId; }

void RunAction::BeginOfRunAction(const G4Run *) {
  // Open an output file for the histograms filled during this run
  G4AnalysisManager::Instance()->OpenFile("muon_stopping.root");
}

void RunAction::EndOfRunAction(const G4Run *) {
  auto *analysisManager = G4AnalysisManager::Instance();
  analysisManager->Write();
  analysisManager->CloseFile();
}
