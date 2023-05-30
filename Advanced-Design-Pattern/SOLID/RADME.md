
# Writing Maintainable, Reusable, and Extendable Code

* SRP – Single Responsibility Principle
* OCP – Open/Closed Principle
* LSP – Liskov Substitution Principle
* ISP – Interface Segregation Principle
* DIP – Dependency Inversion Principle

## [Dependency Inversion Principle in C++](https://levelup.gitconnected.com/dependency-inversion-principle-in-c-14ec84408201)

When designing code structure in a high-level language such as C++, it is very important to think about factors such as maintainability and reusability of your code. Software developers are nowadays constantly bombarded with new requirements, platforms and changing library versions. A well-designed software should be able to deal with that. Badly designed (and maintained) software tends toward spaghetti code with dependencies all over the place.

Developers often rely on design patterns and design principles to help them design software. Design patterns are tried and proven recipes for common situations. On the other hand, design principles are guidelines for good system design. While design patterns often apply to a specific language or at least a paradigm (such as object-oriented programming), principles tend to be more general.

> The Dependency Inversion Principle (DIP) is one of the SOLID design principles. It states:
> High-level modules should not depend on low-level modules. Both should depend on abstractions. Abstractions should not depend on details. Details should depend on abstractions.

`High-level` modules generally refer to more abstract and complex operations in your code. These operations require one or more `low-leve`l modules to perform their function. The straightforward way to implement such complex functionality therefore is to make the high-level modules depend on low-level modules.

### Straightforward Implementation
Let’s have a look at an example of a straightforward implementation using two classes in a hypothetical RPG, Player and Door. The desired functionality is to open or close the door once the player interacts with it (depending on its state). The player class may look as follows:
```
class Player
{
public:
    Player() {}
    
    void interactWith(Door *door)
    {
        if (door)
        {
            door->toggleOpen();
        }
    }
};
```

As you can see, it has one relevant method, interactWith. This method calls the toggleOpen method of the Door class. Let us look at the Door class now:
```
class Door
{
public:
    Door() {}
    void toggleOpen() 
    {
        // Open or close the door
        m_open = !m_open;
        if (m_open)
        {
            std::cout << "Door is open" << std::endl;
        }
        else
        {
            std::cout << "Door is closed" << std::endl;
        }
    }
    
private:
    bool m_open = false;
};
```

As you can see, the door in the game toggles between a closed and an open state.

### Issues with the Implementation
At a first glance, everything looks fine. The player is able to interact with doors in the game. However, extensibility should always be on our mind. In our implementation, we reduced code extensibility and reusability due to the dependence of the Player class on the Door class. What if the player wants to interact with other objects in the game? We will need to write a separate method for every new object.

### Implementation Respecting the Dependency Inversion Principle
The key to this problem is to introduce an `InteractiveObject` interface that the Door class can implement. An interface introduces an abstraction that will help us decouple the player and the door. In that way, we will adhere to the principle that both the high-level module and the low-level module should depend only on abstractions:

```
class InteractiveObject
{
public:
    virtual void interact() = 0;
    virtual ~InteractiveObject() = default;
};
```
This interface declares the method interact that allows interaction with the object. We also refactor the Door class slightly to implement this interface:
```
class Door : public InteractiveObject
{
public:
    Door() {}
    void interact() override
    {
        // Open or close the door
        m_open = !m_open;
        if (m_open)
        {
            std::cout << "Door is open" << std::endl;
        }
        else
        {
            std::cout << "Door is closed" << std::endl;
        }
    }
    
private:
    bool m_open = false;
};
```

The Player class will now only need to know the `InteractiveObject` interface and won’t care about the implementation of the object. This adheres to the principle that high-level modules should also depend only on abstractions:
```
class Player
{
public:
    Player() {}
    
    void interactWith(InteractiveObject *obj)
    {
        if (obj)
        {
            obj->interact();
        }
    }
};
```


You can imagine communication of modules through abstractions like driving a car: you only need to know how to turn on the engine, how to steer and how to make the car go faster or slower. You don’t need to know the intricacies of the engine and the transmission.

### Alternative Implementation
To showcase that the dependency inversion principle is not limited to writing interfaces, let us solve the same problem with templates:
```
class Player
{
public:
    Player() {}
    
    template <typename InteractiveObject>
    void interactWith(InteractiveObject *obj)
    {
        if (obj)
        {
            obj->interact();
        }
    }

class Door
{
public:
    Door() {}
    void interact()
    {
        // Open or close the door
        m_open = !m_open;
        if (m_open)
        {
            std::cout << "Door is open" << std::endl;
        }
        else
        {
            std::cout << "Door is closed" << std::endl;
        }
    }
    
private:
    bool m_open = false;
};
```

You see that in this case we don’t need to explicitly declare the `InteractiveObject` interface, but we rather rely on a specific contract that the Door class implements (in this case it needs to implement the interact method. If this contract isn’t implemented, the compiler will throw an error. Since the template method doesn’t use dynamic polymorphism it may run a tiny bit faster. Otherwise, the two implementations are almost identical.

### Conclusion
As you can see, the dependency inversion principle increases maintainability, reusability and extendibility of our code by making high-level modules depend on abstractions instead of detailed low-level implementations.