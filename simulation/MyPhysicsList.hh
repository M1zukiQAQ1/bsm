
#pragma once


#include <G4VUserPhysicsList.hh>
#include <G4ParticleTable.hh>
#include <G4MuonMinus.hh>
#include <G4PhysicsListHelper.hh>
#include <G4Decay.hh>
#include "FTFP_BERT.hh"


class MyPhysicsList : public G4VUserPhysicsList {
public:
    void ConstructParticle() override;

    void ConstructProcess() override;
};