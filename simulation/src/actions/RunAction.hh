
#pragma once

#include <G4Types.hh>
#include <G4UserRunAction.hh>

class RunAction : public G4UserRunAction {
public:
  RunAction();
  ~RunAction() override = default;

  void BeginOfRunAction(const G4Run *) override;
  void EndOfRunAction(const G4Run *) override;

  G4int getMuonDepthId();
  G4int getElectronSpectrumId();

private:
  G4int muonDepthId;
  G4int electronSpectrumId;
};
