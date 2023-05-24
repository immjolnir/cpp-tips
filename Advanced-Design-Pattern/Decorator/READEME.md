# [Decorator pattern](https://en.wikipedia.org/wiki/Decorator_pattern)
装饰模式(decorator)：装饰模式以对客户端透明的方式扩展对象的功能，是继承关系的一个替代方案，提供比继承更多的灵活性。

Decorator is a structural pattern that allows adding new behaviors to objects dynamically by placing them inside special wrapper objects, called decorators.

Using decorators you can wrap objects countless number of times since both target objects and decorators follow the same interface. The resulting object will get a stacking behavior of all wrappers.

> Attach additional responsibilities to an object dynamically. Decorators provide a flexible alternative to subclassing for extending functionality.

In object-oriented programming, the decorator pattern is a design pattern that allows behavior to be added to an individual object, dynamically, without affecting the behavior of other objects from the same class.[1] The decorator pattern is often useful for adhering to the Single Responsibility Principle, as it allows functionality to be divided between classes with unique areas of concern[2] as well as to the Open-Closed Principle, by allowing the functionality of a class to be extended without being modified.[3] Decorator use can be more efficient than subclassing, because an object's behavior can be augmented without defining an entirely new object.

## Overview
The decorator[4] design pattern is one of the twenty-three well-known design patterns; these describe how to solve recurring design problems and design flexible and reusable object-oriented software—that is, objects which are easier to implement, change, test, and reuse.

### What problems can it solve?
* Responsibilities should be added to (and removed from) an object dynamically at run-time.[5]

* A flexible alternative to subclassing for extending functionality should be provided.
When using subclassing, different subclasses extend a class in different ways. But an extension is bound to the class at compile-time and can't be changed at run-time.

### What solution does it describe?
Define Decorator objects that
* implement the interface of the extended (decorated) object (Component) transparently by forwarding all requests to it

* perform additional functionality before/after forwarding a request.
This allows working with different Decorator objects to extend the functionality of an object dynamically at run-time.


* https://en.wikipedia.org/wiki/Design_Patterns
> Decorator dynamically adds/overrides behaviour in an existing method of an object.


## [What's the difference between decorator and inheritance?](https://www.linkedin.com/advice/0/how-do-you-balance-performance-flexibility)

* How do they differ?

The main difference between decorator pattern and inheritance is that decorator pattern does not create a new class or a new type of object, but rather modifies an existing object by wrapping it with another object. Inheritance, on the other hand, creates a new class and a new type of object that is derived from another class. Another difference is that decorator pattern can be applied to any object that conforms to a given interface, while inheritance requires a fixed class hierarchy.

* When to use inheritance?

Inheritance is suitable when you have a clear and stable relationship between classes that share common attributes and behaviors. For example, you can use inheritance to model a hierarchy of animals, where each subclass inherits the properties and methods of the animal class, and also defines its own specific features. Inheritance is also useful when you want to enable polymorphism, which allows you to treat different subclasses of the same superclass in a uniform way.

* When to use decorator pattern?

Decorator pattern is suitable when you want to add new functionality to an existing object without changing its class or affecting other objects of the same class. For example, you can use decorator pattern to add logging, caching, encryption, or validation features to an object without modifying its original behavior. Decorator pattern is also useful when you want to compose different behaviors at runtime based on the context or user preferences.

* How to balance performance and flexibility?

Both decorator pattern and inheritance have their advantages and disadvantages in terms of performance and flexibility. Decorator pattern offers more flexibility and adaptability, as you can modify the behavior of an object without changing its class or creating a new subclass. However, decorator pattern can also introduce more complexity and overhead, as you have to create and manage multiple wrapper objects that may affect the readability and maintainability of the code. Inheritance offers more performance and simplicity, as you can reuse and extend the code of the superclass without creating additional objects. However, inheritance can also introduce more rigidity and coupling, as you have to follow a fixed class hierarchy that may limit the variability and extensibility of the system.

