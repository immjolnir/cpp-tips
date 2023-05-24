// not for main
// #pragma once
// See https://en.wikipedia.org/wiki/Dependency_injection

#include <iostream>

class GasolineService {
  public:
    void RON95() { std::cout << "RON95!" << std::endl; }

    void RON97() { std::cout << "RON97!" << std::endl; }
};

// Constructor injection
template <typename Policy>
class Car {
  public:
    Car(Policy* policy) : _policy(policy) {}

    void geGasoline() { _policy->RON97(); }

  private:
    Policy* _policy;
};

// Setter injection
template <typename Policy>
class Truck {
  public:
    void setPolicy(Policy* policy) { _policy = policy; }

    void geGasoline() { _policy->RON95(); }

  private:
    Policy* _policy;
};

int main() {
    GasolineService service;

    Car<GasolineService> car(&service);
    car.geGasoline();

    Truck<GasolineService> truck;
    truck.setPolicy(&service);
    truck.geGasoline();
}
