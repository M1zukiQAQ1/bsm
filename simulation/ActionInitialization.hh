#pragma once

#include "DetectorConstruction.hh"
#include "G4VUserActionInitialization.hh"

class ActionInitialization : public G4VUserActionInitialization {
public:
  explicit ActionInitialization(const DetectorConstruction *detector)
      : fDetector(detector) {}

  void Build() const override;
  void BuildForMaster() const override;

private:
  const DetectorConstruction *fDetector;
};
