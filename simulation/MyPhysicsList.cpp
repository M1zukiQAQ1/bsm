
#include "G4VUserPhysicsList.hh"
#include <G4ParticleTable.hh>
#include <G4PhysicsListHelper.hh>

// Particle Definations
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4GenericIon.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4Positron.hh"

// Decay & Stopping
#include "G4RadioactiveDecay.hh"
#include <G4Decay.hh>

#include "MyPhysicsList.hh"

void MyPhysicsList::ConstructParticle() {
  G4MuonMinus::Definition();
  G4Electron::Definition();
  G4Positron::Definition();
  G4NeutrinoMu::Definition();
  G4Gamma::Definition();
}

void MyPhysicsList::ConstructProcess() {
  AddTransportation();

  auto *ph = G4PhysicsListHelper::GetPhysicsListHelper();

  // Rodiaactive nuclear Decay
  auto *radioactiveDecay = new G4RadioactiveDecay();
  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());

  // Ordinary muon Decay
  auto *decay = new G4Decay();
  ph->RegisterProcess(decay, G4MuonMinus::Definition());
}
