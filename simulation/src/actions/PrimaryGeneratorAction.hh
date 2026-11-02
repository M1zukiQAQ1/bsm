
#include "G4MuonMinus.hh"
#include "G4ParticleGun.hh"
#include "G4VUserPrimaryGeneratorAction.hh"

const G4ThreeVector gunLocation(0, 0, -5);

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
  PrimaryGeneratorAction();

  ~PrimaryGeneratorAction();

  void GeneratePrimaries(G4Event *event) override;

private:
  G4ParticleGun *gun = new G4ParticleGun(G4MuonMinus::Definition());
};
