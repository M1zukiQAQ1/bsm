
#include "MuonMinusSteppingAction.hh"
#include "G4MuonMinus.hh"
#include "G4Step.hh"
#include <G4AnalysisManager.hh>
#include <G4TrackStatus.hh>
#include <G4Types.hh>
#include <G4VPhysicalVolume.hh>

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

  // For Muon Stopping Distance
  // If it's not inside the Target's Volume, we don't care, return
  if (!volume || volume->GetLogicalVolume() != fDetector->GetTargetLogical()) {
    return;
  }

  // Only the step on which the muon comes to rest. The at-rest step that
  // follows (capture / decay) starts at zero energy, so it is not recorded
  // again.
  if (pre->GetKineticEnergy() <= 0.0 || post->GetKineticEnergy() != 0.0) {
    return;
  }

  // Keep muons that are stopped
  if (step->GetTrack()->GetTrackStatus() != fStopButAlive) {
    return;
  }

  const G4double depth =
      post->GetPosition().z() - DetectorConstruction::frontZ;

  // Pass the raw G4 value: FillH1 divides by the histogram's unit (mm)
  G4AnalysisManager::Instance()->FillH1(fMuonStoppingId, depth);
}
