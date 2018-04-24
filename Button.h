#pragma once
#include "LTexture.h"
#include "Point.h"
#include "word.h"

enum State{Normal, Hover, Clicked};                                 ///Enumerating three states of buttons

class Button
{
    int width;                                                      ///width of each of the three parts of the button
    int ButtonWidth;                                                ///final width of the Button
    int height;                                                     ///height of the Button
    std::string text;                                              ///Text on the button
    Word word;                                                     ///object of word class to be rendered over the button
    enum AnimationFrames{Colors=3};
    SDL_Rect spriteClips[Colors];                                   ///sprite clips for each state of the button
    LTexture* spriteSheetTexture;                                  ///Texture of image consisting of Buttons
    Point position;                                                ///Position of the Button
    int state;                                                     ///current state of the Button

public:
    Button();
    Button(LTexture*,std::string, float, float);
    Button(const Button&);
    void Render(SDL_Renderer*);
    ~Button();
    ///functions to access private attributes
    Point getPosition();
    int getWidth();
    int getHeight();
    std::string getText();
    void changeState(State);                                    ///changes the current state of the button
    Word getWord();
};
