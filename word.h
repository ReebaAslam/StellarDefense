#pragma once

#include "LTexture.h"
#include "Character.h"

class Word
{
private:
    Point position;             ///position of word
    std::string word;           ///text of the word
    int wordLen;                ///length of the word
    int width;                  ///width of the word
    int height;                ///height of the word
    LTexture* spriteSheetTexture;
    Character* chars;               ///pointer of character class(used for creating dynamic array of Characters)

public:
    Word();
    Word(std::string, LTexture*, float, float );
    ~Word();
    Word(const Word&);
    void Render(SDL_Renderer*);
    int getLength();
    int getWidth();
    void setPosition(float,float);          ///changes position of the Word
    void changeWord(std::string);           ///changes the text of the Word
};
