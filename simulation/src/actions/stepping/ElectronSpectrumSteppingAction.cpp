
#include "ElectronSpectrumSteppingAction.hh"

#include <G4AnalysisManager.hh>
#include <G4Electron.hh>
#include <G4Exception.hh>
#include <G4MuonMinus.hh>
#include <G4PhysicsModelCatalog.hh>
#include <G4Step.hh>
#include <G4Track.hh>
#include <G4VPhysicalVolume.hh>

namespace {
// Model name G4MuonMinusCapture assigns to its G4MuonMinusBoundDecay (DIO)
// secondaries. The other electrons it emits come from
// "model_muMinusCaptureAtRest_EMCascade" (Auger electrons, <~3 MeV).
const G4String kDioModelName = "model_muMinusCaptureAtRest_DIO";
} // namespace

void ElectronSpectrumSteppingAction::UserSteppingAction(const G4Step *step) {
  const auto *track = step->GetTrack();

  // Only primary mu-
  if (track->GetDefinition() != G4MuonMinus::Definition() ||
      track->GetParentID() != 0) {
    return;
  }

  // Only the at-rest step, where the capture / decay products are created
  const auto *pre = step->GetPreStepPoint();
  if (pre->GetKineticEnergy() > 0.0) {
    return;
  }

  // Only muons that stopped inside the target
  const auto *volume = pre->GetPhysicalVolume();
  if (!volume || volume->GetLogicalVolume() != fTarget) {
    return;
  }

  if (!fDioModelLookedUp) {
    fDioModelLookedUp = true;
    fDioModelId = G4PhysicsModelCatalog::GetModelID(kDioModelName);
    if (fDioModelId < 0) {
      G4Exception("ElectronSpectrumSteppingAction::UserSteppingAction",
                  "DIO0001", JustWarning,
                  ("Model '" + kDioModelName +
                   "' not found; electron spectrum will stay empty.")
                      .c_str());
    }
  }
  // Untagged secondaries also carry model ID -1, so never match on it
  if (fDioModelId < 0) {
    return;
  }

  for (const auto *secondary : *step->GetSecondaryInCurrentStep()) {
    if (secondary->GetDefinition() == G4Electron::Definition() &&
        secondary->GetCreatorModelID() == fDioModelId) {
      // Pass the raw G4 value: FillH1 divides by the histogram's unit (MeV)
      G4AnalysisManager::Instance()->FillH1(fElectronSpectrumId,
                                            secondary->GetKineticEnergy());
    }
  }
}
