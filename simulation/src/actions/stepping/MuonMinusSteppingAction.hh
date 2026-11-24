
#pragma once

#include "DetectorConstruction.hh"
#include "G4UserSteppingAction.hh"
#include <G4Step.hh>
#include <G4Types.hh>

// Records where primary mu- come to rest inside the target, as the depth of
// the stopping point below the target's front face.
class MuonMinusSteppingAction : public G4UserSteppingAction {
public:
  MuonMinusSteppingAction(const DetectorConstruction *detector,
                          const G4int muonStoppingId)
      : fDetector(detector), fMuonStoppingId(muonStoppingId) {}

  void UserSteppingAction(const G4Step *step) override;

private:
  // Hold the detector rather than its target volume: the serial run manager
  // builds user actions before Construct() runs, so the target logical volume
  // only exists once tracking starts.
  const DetectorConstruction *fDetector;
  G4int fMuonStoppingId;
};
