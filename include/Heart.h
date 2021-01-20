#ifndef __HEART_H__
#define __HEART_H__

#include "State.h"

class Heart
{
private:
    sf::RectangleShape shape;
    sf::Texture heartTexture;
    
    sf::Text text;
    sf::Font font;

    void initializeShape(sf::Vector2f v, sf::Vector2f s);
    void initializeText();
public:
    static int numberOfHearts;
public:
    Heart(); // constructor
    Heart(sf::Vector2f v, sf::Vector2f s);

    void operator ++();
    void operator--();
    ~Heart();

    static bool doIHaveRemainingHearts();
    void render(sf::RenderTarget* target);
    void update();

};

#endif // __HEART_H__