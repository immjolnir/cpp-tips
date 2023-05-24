// see https://en.wikipedia.org/wiki/Decorator_pattern
/*
                VisualComponent
                     ^
                     |
                     |
        .-------------------------------.
        |                               |
        |                               |
.--------------------.           .----------------.
|    TextView        |          |   Decorator    |
|(Concrete Component)|          | - component    |
| + operation()      |          | + operation()  |
'--------------------'          '----------------'
                                        ^
                                        |
                                        |
                                .----------------------.
                                |   BorderDecorator    |
                                | (Concrete Decorator) |
                                | + operation()        |
                                '----------------------'
*/
#include <iostream>
#include <memory>

// defines the interface for objects that can have responsibilities added to them dynamically.
class VisualComponent {  // Component
  public:
    virtual void draw() = 0;
    virtual ~VisualComponent() = default;
};

// defines an object to which additional responsibilities can be attached.
class TextView : public VisualComponent {  // ConcreteComponent
  public:
    virtual void draw() { std::cout << "TextView::draw "; }
};

// maintains a reference to a Component object and defines an interface that conforms to Component's interface.
class Decorator : public VisualComponent {
  public:
    Decorator() : component(nullptr) {}

    Decorator(VisualComponent* component_) : component(component_) {}

    Decorator(const Decorator&) = delete;  // rule of three
    Decorator& operator=(const Decorator&) = delete;

    virtual void draw() { component->draw(); }

  protected:
    VisualComponent* component;
};

// adds responsibilities to the component.
class BorderDecorator : public Decorator {  // ConcreteDecorator
  public:
    BorderDecorator(std::shared_ptr<VisualComponent> component_, int width_) : width(width_) {
        component = component_.get();
    }

    virtual void draw() {
        Decorator::draw();
        drawBorder(width);
    }

  private:
    void drawBorder(int width_) { std::cout << "BorderDecorator::drawBorder width=" << width_ << ' '; }

    int width;
};

class Window {
  public:
    void setContents(std::shared_ptr<VisualComponent> contents_) { contents = contents_.get(); }

    void draw() {
        contents->draw();
        std::cout << '\n';
    }

  private:
    VisualComponent* contents;
};

int main() {
    // The smart pointers prevent memory leaks.
    std::unique_ptr<Window> window = std::make_unique<Window>();

    std::shared_ptr<TextView> textView = std::make_shared<TextView>();
    window->setContents(textView);
    window->draw();

    std::shared_ptr<BorderDecorator> bd1 = std::make_shared<BorderDecorator>(textView, 1);
    window->setContents(bd1);
    window->draw();

    std::shared_ptr<BorderDecorator> bd2 = std::make_shared<BorderDecorator>(textView, 2);
    std::shared_ptr<BorderDecorator> bd3 = std::make_shared<BorderDecorator>(bd2, 1);
    window->setContents(bd3);
    window->draw();
}
