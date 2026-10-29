
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4String.hh"
#include "G4Isotope.hh"

#include "DetectorConstruction.hh"

G4VPhysicalVolume *DetectorConstruction::Construct()
{
    auto *nist = G4NistManager::Instance();

    // Building Material for Global Environment: Vacuum
    auto *vacuum = nist->FindOrBuildMaterial("G4_Galactic");

    // Building Material for Target 10B
    auto *b10 = new G4Isotope("B10", 5, 10, 10.0129 * (gram / mole));
    auto *enrichedBoron = new G4Element("EnrichedBoron10", "B", 1);
    enrichedBoron->AddIsotope(b10, 100 * perCent);
    auto *targetMaterial = new G4Material("Boron10Target", 2.2 * g / cm3, 1, kStateSolid);
    targetMaterial->AddElement(enrichedBoron, 1.0);

    auto *worldSolid = new G4Box(
        "WorldSolid",
        20 * cm,
        20 * cm,
        20 * cm);

    auto *targetSolid = new G4Box(
        "TargetSolid",
        width / 2,
        height / 2,
        thickness / 2);

    auto *worldLogical = new G4LogicalVolume(
        worldSolid,
        vacuum,
        "WorldLogical");

    auto *targetLogical = new G4LogicalVolume(
        targetSolid,
        targetMaterial,
        "TargetLogical");

    // Place the world. Its mother volume is nullptr.
    auto *worldPhysical = new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        worldLogical,
        "World",
        nullptr, // No mother: this is the world
        false,
        0,
        true);

    // Place the target inside the world.
    new G4PVPlacement(
        nullptr,
        G4ThreeVector(0, 0, 0),
        targetLogical,
        "Target",
        worldLogical, // Target's mother is the world
        false,
        0,
        true);

    return worldPhysical;
}
