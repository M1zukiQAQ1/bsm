
#pragma once

#include "G4UserSteppingAction.hh"
#include <G4LogicalVolume.hh>
#include <G4Types.hh>

class MuonMinusSteppingAction : public G4UserSteppingAction {
public:
  MuonMinusSteppingAction(const G4LogicalVolume *target, G4double targetFrontZ,
                          const G4int muonStoppingId)
      : fTarget(target), fTargetFrontZ(targetFrontZ),
        fMuonStoppingId(muonStoppingId) {}

  void UserSteppingAction(const G4Step *step) override;

private:
  const G4LogicalVolume *fTarget;
  G4double fTargetFrontZ;
  G4int fMuonStoppingId;
};
