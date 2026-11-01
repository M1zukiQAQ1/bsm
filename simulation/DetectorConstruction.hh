
#pragma once

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"

const G4double width = 5 * cm;
const G4double height = 5 * cm;
const G4double thickness = 5 * mm;

class DetectorConstruction : public G4VUserDetectorConstruction {
public:
  G4VPhysicalVolume *Construct() override;
};
