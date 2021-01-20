# Nonogram Game
### Author: Ana-Maria Comorașu

#### Course Tasks:

1. Graphical interface
- used SFML library

2. Run-time type information
``` C++
// Game.cpp
if (dynamic_cast<MenuState*>(this->states.top()) && this->states.top()->getGameOver() != NOT_FINISHED)
    {
        if (this->states.top()->getGameOver() == WON)
            this->states.push(GameOverState::getInstance(this->window, &this->states, "win"));
        if (this->states.top()->getGameOver() == LOST)
            this->states.push(GameOverState::getInstance(this->window, &this->states, "loss"));
    }
```
3. Abstract classes
``` C++
// State.h
// pure virtual functions
    virtual void update() = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
```
4. Operator overloading
``` C++
// Heart.cpp
void Heart::operator++()
{
    Heart::numberOfHearts = Heart::numberOfHearts + 1;
}

void Heart::operator--()
{
    Heart::numberOfHearts = Heart::numberOfHearts - 10;
}
```
5. Heap Memory Allocation
```C++
// MenuState.cpp
void MenuState::initializeButtons()
{
    this->buttons["NEW_GAME"] = new Button(230, 460, 100, 100,
                                           "res/playbutton.png", "res/playbuttonhover.png", "res/playbuttonhover.png");
    this->buttons["EXIT_GAME"] = new Button(470, 460, 100, 100,
                                            "res/quitbutton.png", "res/quitbuttonjover.png", "res/quitbuttonjover.png");
}
```

6. Exceptions
```C++
// Exception.h
class Exception : public std::exception
{
private:
    std::string errorType;

public:
    Exception(std::string error) : errorType(error)
    {
    }

    ~Exception() throw() {}
    virtual const char *what() throw()
    {
        return this->errorType.c_str();
    }
};
```

```C++
// Button.cpp
void Button::initializeTexture(std::string defaultSource, std::string hoverSource, std::string activeSource)
{
    try
    {
        if (!this->defaultTexture.loadFromFile(defaultSource))
            throw Exception("Error: failed to load texture from file");
        if (!this->hoverTexture.loadFromFile(hoverSource))
            throw Exception("Error: failed to load texture from file");
        if (!this->activeTexture.loadFromFile(activeSource))
            throw Exception("Error: failed to load texture from file");
    }
    catch (Exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    this->shape.setTexture(&this->defaultTexture);
}
```

7. Standard Template Library
```C++
#include <stack>
#include <map>
#include <vector>
#include <string>
```

8. Lambda expressions
```C++
// Tablepixel.cpp
bool TablePixel::isCorrectlyClicked()
{
    auto lambda = [](pixelStates pixelState, pixelStates puzzleState) {
        return pixelState == puzzleState;
    };
    return lambda(this->pixelState, this->puzzleState);
}
```

9. Templates
```C++
template <typename T>
bool operator!=(std::map<T, std::map<T, pixelStates>> &firstMap, std::map<T, std::map<T, pixelStates>> &secondMap)
{
    for (auto &i : firstMap)
    {
        for (auto &j : i.second)
        {
            if (auto it = secondMap.find(j.first); it == secondMap.end())
            {
                return true;
            }
            else
            {
                if (secondMap[i.first][j.first] == EMPTY and j.second == MARKED)
                {
                    return true;
                }
                if (secondMap[i.first][j.first] == MARKED and j.second == EMPTY)
                {
                    return true;
                }
            }
        }
    }
    return false;
}
```

10. Smart pointers
```C++
// Nonogramstate.h
std::unique_ptr<Heart> h;
```

```C++
// Nonogramstate.cpp
void NonogramState::initializeHearts()
{
   h = std::make_unique<Heart>(sf::Vector2f(50 + 60 * 1, 50), sf::Vector2f(50, 50));
}
```

11. Design Patterns
* Singleton 
```C++
class GameOverState
    : public State
{
private:
    // singleton : private constructor
    static GameOverState *instance;
    sf::Text text;

    sf::Clock clock;

    void initializeText(std::string message);
    GameOverState(sf::RenderWindow *window, std::stack<State *> *states, std::string message);

public:
    static GameOverState *getInstance(sf::RenderWindow *window,
                                      std::stack<State *> *states,
                                      std::string message);

    ~GameOverState();

    GameOverState(const GameOverState &) = delete;  // delete the copy constructor
    void operator=(GameOverState const &) = delete; // delete the assignment operator

    void updateKeyInput();
    // overriding functions
    void render(sf::RenderTarget *target = nullptr) override;
    void update() override;
};
```

* State
```C++
class State
{
protected:
    sf::RenderWindow *window;
    bool quit;
    std::stack<State *> *states;
    //std::shared_ptr<std::stack<State*>> states;
    sf::Font font;

    // mouse positions
    sf::Vector2f mousePositionView;

    // initializer functions
    void initializeFonts();
    static gameFinality gameOver;

public:
    State(sf::RenderWindow *window, std::stack<State *> *states);
    virtual ~State();

    const bool &getQuit() const;
    gameFinality getGameOver() const;
    virtual void updateMousePositions();

    // pure virtual functions
    virtual void update() = 0;
    virtual void render(sf::RenderTarget *target = nullptr) = 0;
    void endState();
};
```

12. Features of C++17/20
* Init statement for if/switch
```C++
if (auto it = secondMap.find(j.first); it == secondMap.end())
            {
                return true;
            }
```