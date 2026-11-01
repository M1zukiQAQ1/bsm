
#pragma once

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include <CLHEP/Units/SystemOfUnits.h>
#include <G4LogicalVolume.hh>
#include <G4Types.hh>

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  G4VPhysicalVolume *Construct() override;

  // Full dimensions of target
  inline static constexpr G4double width = 5 * cm;
  inline static constexpr G4double height = 5 * cm;
  inline static constexpr G4double thickness = 5 * mm;

  // Position in Z axis
  inline static constexpr G4double centerZ = 0 * mm;
  inline static constexpr G4double frontZ = centerZ - thickness / 2;

  G4LogicalVolume *GetTargetLogical() const { return fTargetLogical; }

private:
  G4LogicalVolume *fTargetLogical;
};
