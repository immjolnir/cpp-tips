#pragma once

#include <iostream>

class GasolineSource {
  public:
    void FuelUp() = 0;
};

class GasStation : public GasolineSource {
  public:
    void FuelUp() { std::cout << "Pumping gas at gas station" << std::endl; }
};

// Car is dependent on GasStation being defined in order to fuel up.
class Car {
    GasStation gasolineService;

  public:
    Car() {}

    void getGasoline() {
        std::cout << "Car needs more gasoline!" << std::endl;
        gasolineService.FuelUp();
    }
};
