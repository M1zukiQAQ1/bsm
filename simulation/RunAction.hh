
#pragma once

#include <G4UserRunAction.hh>

class RunAction : public G4UserRunAction {
public:
  RunAction();
  ~RunAction();

  virtual void BeginRunAction(const G4Run *);
  virtual void EndOfRunAction(const G4Run *);
};
