
#include "G4Box.hh"
#include "G4Isotope.hh"
#include "G4LogicalVolume.hh"
#include "G4NistManager.hh"
#include "G4PVPlacement.hh"
#include "G4String.hh"
#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"

#include "DetectorConstruction.hh"

G4VPhysicalVolume *DetectorConstruction::Construct() {
  auto *nist = G4NistManager::Instance();

  // Building Material for Global Environment: Vacuum
  auto *vacuum = nist->FindOrBuildMaterial("G4_Galactic");

  // Building Material for Target 106PD

  // TODO: Supply sliced geometry

  auto *pd106 = new G4Isotope("106PD", 46, 106, 105.963 * (gram / mole));
  auto *enrichedPalladium = new G4Element("EnrichedPalladium106", "Pd", 1);
  enrichedPalladium->AddIsotope(pd106, 100 * perCent);
  auto *targetMaterial =
      new G4Material("Palladium106Target", 12.02 * g / cm3, 1, kStateSolid);
  targetMaterial->AddElement(enrichedPalladium, 1.0);

  auto *worldSolid = new G4Box("WorldSolid", 100 * cm, 100 * cm, 100 * cm);

  auto *targetSolid =
      new G4Box("TargetSolid", width / 2, height / 2, thickness / 2);

  auto *worldLogical = new G4LogicalVolume(worldSolid, vacuum, "WorldLogical");

  fTargetLogical =
      new G4LogicalVolume(targetSolid, targetMaterial, "TargetLogical");

  // Place the world. Its mother volume is nullptr.
  auto *worldPhysical =
      new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0), worldLogical, "World",
                        nullptr, // No mother: this is the world
                        false, 0, true);

  // Place the target inside the world.
  new G4PVPlacement(nullptr, G4ThreeVector(0, 0, 0), fTargetLogical, "Target",
                    worldLogical, // Target's mother is the world
                    false, 0, true);

  return worldPhysical;
}
