
#pragma once

#include "G4UserSteppingAction.hh"
#include <G4LogicalVolume.hh>
#include <G4Step.hh>
#include <G4Types.hh>

// Fills the kinetic-energy spectrum of mu- decay-in-orbit (DIO) electrons
// for primary mu- that stop inside the target.
//
// A mu- at rest in matter is handled entirely by G4MuonMinusCapture
// ("muMinusCaptureAtRest", a hadronic at-rest process); G4Decay never acts
// on it. That single process emits both the DIO electron and Auger electrons
// from the muonic-atom cascade, so electrons are selected by their creator
// *model* rather than by their creator process.
class ElectronSpectrumSteppingAction : public G4UserSteppingAction {
public:
  ElectronSpectrumSteppingAction(const G4LogicalVolume *target,
                                 const G4int electronSpectrumId)
      : fTarget(target), fElectronSpectrumId(electronSpectrumId) {}

  void UserSteppingAction(const G4Step *step) override;

private:
  const G4LogicalVolume *fTarget;
  G4int fElectronSpectrumId;

  // Looked up from G4PhysicsModelCatalog on the first at-rest step
  G4bool fDioModelLookedUp = false;
  G4int fDioModelId = -1;
};
