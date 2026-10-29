#pragma once

#include "G4VUserActionInitialization.hh"
#include "PrimaryGeneratorAction.hh"

class ActionInitialization : public G4VUserActionInitialization {
public:
    void Build() const override {
        SetUserAction(new PrimaryGeneratorAction());
    }
};