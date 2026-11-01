
#pragma once

#include "G4VDiscreteProcess.hh"

class BSMProcess : public G4VDiscreteProcess {
public:
  BSMProcess();

  G4bool IsApplicable(const G4ParticleDefinition &) override;

  void PreparePhysicsTable(const G4ParticleDefinition &) override;

  void BuildPhysicsTable(const G4ParticleDefinition &) override;

  G4VParticleChange *PostStepDoIt(const G4Track &track,
                                  const G4Step &step) override;

protected:
  G4double GetMeanFreePath(const G4Track &track, G4double previousStepSize,
                           G4ForceCondition *condition) override;
};
