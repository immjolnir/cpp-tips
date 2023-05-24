#pragma once

#include <iostream>

class GasolineSource {
  public:
    void FuelUp() = 0;
};

class FuelCan : public GasolineSource {
  public:
    void FuelUp() { std::cout << "Pumping gas from fuel can" << std::endl; }
};

// Car is dependent on FuelCan being defined in order to fuel up.
class Car {
    FuelCan gasolineService;

  public:
    Car() {}

    void getGasoline() {
        std::cout << "Car needs more gasoline!" << std::endl;
        gasolineService.FuelUp();
    }
};
