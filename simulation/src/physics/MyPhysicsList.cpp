
#include "G4VUserPhysicsList.hh"
#include <G4ParticleTable.hh>
#include <G4PhysicsListHelper.hh>

// Particle Definations
#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4GenericIon.hh"
#include "G4MuonMinus.hh"
#include "G4NeutrinoMu.hh"
#include "G4OpticalPhoton.hh"
#include "G4Positron.hh"

// TODO: Supply RMC, Muon Decay, EM, and other neccessary; Add one by one
// Decay & Stopping
#include "G4MuonMinusCapture.hh"
#include "G4RadioactiveDecay.hh"
#include <G4Decay.hh>

#include "MyPhysicsList.hh"

MyPhysicsList::MyPhysicsList() {
  MyPhysicsList::ph = G4PhysicsListHelper::GetPhysicsListHelper();
}

void MyPhysicsList::ConstructParticle() {

  /*
   Provides Particles:

   G4Alpha::Alpha(), G4AntiProton::AntiProton(), G4Deuteron::Deuteron(),
   G4Electron::Electron(), G4Gamma::Gamma(),
   G4GenericIon::GenericIonDefinition(), G4He3::He3(),
   G4KaonMinus::KaonMinusDefinition(), G4KaonPlus::KaonPlusDefinition(),
   G4MuonMinus::MuonMinus(), G4MuonPlus::MuonPlus(),
   G4PionMinus::PionMinusDefinition(), G4PionPlus::PionPlusDefinition(),
   G4Positron::Positron(), G4Proton::Proton(), and G4Triton::Triton().
  */
  emPhysics.ConstructParticle();

  G4MuonMinus::Definition();
  G4Electron::Definition();
  G4Positron::Definition();
  G4NeutrinoMu::Definition();
  G4Gamma::Definition();
  G4OpticalPhoton::Definition();
}

void MyPhysicsList::ConstructProcess() {

  // Basic Moving
  AddTransportation();

  // Rodiaactive nuclear Decay
  auto *radioactiveDecay = new G4RadioactiveDecay();
  ph->RegisterProcess(radioactiveDecay, G4GenericIon::GenericIon());

  // Ordinary muon Decay
  auto *decay = new G4Decay();
  ph->RegisterProcess(decay, G4MuonMinus::Definition());

  // Muon Capture under Standard Model
  auto *muMinusCapture = new G4MuonMinusCapture();
  ph->RegisterProcess(muMinusCapture, G4MuonMinus::Definition());

  /*
    Provides Processes: G4VEnergyLossProcess::AddEmModel(),
    G4VEmProcess::AddEmModel(), G4VMultipleScattering::AddEmModel(),
    fUseDistanceToBoundary, G4cout, G4endl,
    G4ParticleDefinition::GetParticleName(),
    G4PhysicsListHelper::GetPhysicsListHelper(),
    G4VPhysicsConstructor::GetPhysicsName(), G4LossTableManager::Instance(),
    G4INCL::Math::pi, G4InuclParticleNames::pip, G4InuclParticleNames::pp,
    G4PhysicsListHelper::RegisterProcess(), G4ParticleTableIterator< K, V
    >::reset(), G4VEmModel::SetActivationLowEnergyLimit(),
    G4LossTableManager::SetAtomDeexcitation(),
    G4EmProcessOptions::SetDEDXBinning(), G4VEnergyLossProcess::SetEmModel(),
    G4VEmProcess::SetEmModel(), G4VAtomDeexcitation::SetFluo(),
    G4VEmModel::SetHighEnergyLimit(), G4EmProcessOptions::SetLambdaBinning(),
    G4VEmModel::SetLowEnergyLimit(), G4EmProcessOptions::SetMaxEnergy(),
    G4VEmProcess::SetMaxKinEnergy(), G4EmProcessOptions::SetMinEnergy(),
    G4VEmProcess::SetMinKinEnergy(), G4EmProcessOptions::SetPolarAngleLimit(),
    G4VEnergyLossProcess::SetStepFunction(),
    G4VMultipleScattering::SetStepLimitType(), G4EmProcessOptions::SetVerbose(),
    G4VPhysicsConstructor::theParticleIterator, and G4ParticleTableIterator< K,
    V >::value().
  */

  emPhysics.ConstructProcess();

  ConstructEM();
}

void MyPhysicsList::ConstructEM() { emPhysics.ConstructProcess(); }
