
#include "MuonMinusSteppingAction.hh"
#include "G4MuonMinus.hh"
#include "G4Step.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4AnalysisManager.hh>
#include <G4Positron.hh>
#include <G4SystemOfUnits.hh>
#include <G4TrackStatus.hh>
#include <G4Types.hh>

void MuonMinusSteppingAction::UserSteppingAction(const G4Step *step) {

  // If it's not Muon Minus, return
  if (step->GetTrack()->GetDefinition() != G4MuonMinus::Definition()) {
    return;
  }

  if (step->GetTrack()->GetParentID() != 0) {
    return;
  }

  const auto *pre = step->GetPreStepPoint();
  const auto *post = step->GetPostStepPoint();

  const auto *volume = pre->GetPhysicalVolume();

  // If it's not inside the Target's Volume, we don't care, return
  if (!volume || volume->GetLogicalVolume() != fTarget) {
    return;
  }

  // If it's already stopped, dont record it again
  if (pre->GetKineticEnergy() <= 0.0 || post->GetKineticEnergy() != 0.0) {
    return;
  }

  // Exclude muon fron decay or other processes
  if (step->GetTrack()->GetTrackStatus() == fStopButAlive) {
    return;
  }

  const G4double depth = post->GetPosition().z() - fTargetFrontZ;
  const G4double pathLength = step->GetTrack()->GetTrackLength();

  // Fill in the created histogram
  G4AnalysisManager::Instance()->FillH1(fMuonStoppingId, depth / mm);
}
