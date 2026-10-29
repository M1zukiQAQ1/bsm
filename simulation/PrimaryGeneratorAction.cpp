
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "G4MuonMinus.hh"
#include "G4SystemOfUnits.hh"

#include "PrimaryGeneratorAction.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction()
{
    gun->SetParticleEnergy(10.0 * MeV);
    gun->SetParticleMomentumDirection(G4ThreeVector(0, 0, 1));
    gun->SetParticlePosition(gunLocation);
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete gun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
    gun->GeneratePrimaryVertex(event);
}
