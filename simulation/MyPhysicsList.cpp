
#include <G4VUserPhysicsList.hh>
#include <G4ParticleTable.hh>
#include <G4MuonMinus.hh>
#include <G4Electron.hh>
#include <G4PhysicsListHelper.hh>
#include <G4Decay.hh>
#include "FTFP_BERT.hh"

#include "MyPhysicsList.hh"

void MyPhysicsList::ConstructParticle()
{
    G4MuonMinus::Definition();
    G4Electron::Definition();
}

void MyPhysicsList::ConstructProcess()
{
    AddTransportation();

    auto *ph = G4PhysicsListHelper::GetPhysicsListHelper();
    ph->RegisterProcess(
        new G4Decay,
        G4MuonMinus::Definition());
}
