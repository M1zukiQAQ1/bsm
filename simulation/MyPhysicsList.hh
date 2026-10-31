
#pragma once

#include <G4Decay.hh>
#include <G4MuonMinus.hh>
#include <G4ParticleTable.hh>
#include <G4PhysicsListHelper.hh>
#include <G4VUserPhysicsList.hh>

class MyPhysicsList : public G4VUserPhysicsList {
public:
  MyPhysicsList();
  ~MyPhysicsList() override = default;

  void ConstructParticle() override;

  void ConstructProcess() override;
};
