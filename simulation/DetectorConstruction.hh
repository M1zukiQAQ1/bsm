
#pragma once

#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4String.hh"
#include "G4Isotope.hh"

const G4double width = 20 * mm;
const G4double height = 20 * mm;
const G4double thickness = 5.0 * mm;

class DetectorConstruction: public G4VUserDetectorConstruction {
public:
    G4VPhysicalVolume* Construct() override;
};
