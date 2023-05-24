# [Dependency injection](https://en.wikipedia.org/wiki/Dependency_injection)

In software engineering, dependency injection is a design pattern in which an object or function receives other objects or functions that it depends on. Dependency injection aims to separate the concerns of constructing objects and using them, leading to loosely coupled programs.

The pattern ensures that an object or function which wants to use a given service should not have to know how to construct those services.  Instead, the receiving 'client' (object or function) is provided with its dependencies by external code (an 'injector'), which it is not aware of.

Dependency injection involves four roles: services, clients, interfaces and injectors.


## [Dependency inversion principle](https://en.wikipedia.org/wiki/Dependency_inversion_principle)
In object-oriented design, the dependency inversion principle is a specific methodology for loosely coupled software modules. When following this principle, the conventional dependency relationships established from high-level, policy-setting modules to low-level, dependency modules are reversed, thus rendering high-level modules independent of the low-level module implementation details. The principle states:[1]

High-level modules should not import anything from low-level modules. Both should depend on abstractions (e.g., interfaces).
Abstractions should not depend on details. Details (concrete implementations) should depend on abstractions.


# Dependency Injection in C++
Dependency Injection (DI) or Inversion of Control(IoC)

Dependency injection is a technique for decoupling the client of a service from the service's implementation [ Wikipedia-a ]. If the client object were to directly create an instance of the service, it would introduce a hard-coded dependency (strong coupling) between the client and the service implementation.

The client object would have to know the exact type of the service, making it impossible to substitute a different implementation of the service at runtime. In dependency injection, we define an interface for the service and the client accesses the service’s methods through the interface. Code external to the client is responsible for creating an instance of the service and injecting it into the client. The injection of the service can be done at construction, or post-construction through setter methods. 


The usefulness of Dependency Injection is in that the implementation of a class is more flexible and independent by decreasing the amount of coupling between a client and another service. The exact decoupling is the removal of a client class’s dependency on the implementation of an interface, instead requiring the implementation to be passed in.

Let’s take a look at a class that requires a dependency and the class defining that dependency.

## exam00.h, exam01.h
Here, the class Car is dependent on the definition for GasStation. Car cannot be defined without GasStation being defined and Car would need to be changed whenever the source of gasoline is changed, like to a can.

## exam02.h
The solution for this issue is Dependency Injection. We can inject the implementation for GasolineSource at runtime and use runtime polymorphism to abstract away the explicit implementation of GasolineSource.

## main.cpp
Here is the output from running main, showing that the appropriate services were called based up the dependencies injected.

# Advanced

Also consider:

* use a pointer to an object (or smart pointer, depending on the case)
* use a template argument for a policy (for an example, see std::default_delete use in smart pointers)
  * Policy-based templates implement dependency injection chosen at compilation time.
* use lambda calcullus with injected functors/predicates.

## exam03-policy-based-template.cpp



Have a look at boost::any (this will allow you to store heterogenous objects in a container, similar to storing objects by object reference in C#).

## [Law of Demter](https://en.wikipedia.org/wiki/Law_of_Demeter)

The Law of Demeter (LoD) or principle of least knowledge is a design guideline for developing software, particularly object-oriented programs. In its general form, the LoD is a specific case of loose coupling.

The following three recommendations serve as a succinct summary:[2]

* Each unit should have only limited knowledge about other units: only units "closely" related to the current unit.
* Each unit should only talk to its friends; don't talk to strangers.
* Only talk to your immediate friends.

### Advantages
The advantage of following the Law of Demeter is that the resulting software tends to be more maintainable and adaptable. Since objects are less dependent on the internal structure of other objects, object implementation can be changed without reworking their callers.

### Disadvantages
Although the LoD increases the adaptiveness of a software system, it may result in having to write many wrapper methods to propagate calls to components; in some cases, this can add noticeable time and space overhead.



## Dependency injection framework
* https://github.com/google/fruit
* https://github.com/boost-ext/di
* https://github.com/stevef51/CPPServiceLocator


## refers
* https://www.codymorterud.com/design/2018/09/07/dependency-injection-cpp.html
* https://stackoverflow.com/questions/29365084/is-dependency-injection-useful-in-c
* https://www.youtube.com/watch?v=l6Y9PqyK1Mc
  * https://github.com/MakersF/makersf.github.io
* https://www.youtube.com/watch?v=BERPCuHJPUg
