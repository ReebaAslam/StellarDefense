#include "word.h"

using namespace std;

Word::Word()
{
    width=height=0;
    word="\0";
    wordLen=0;
    chars=NULL;
}

Word::Word(string word, LTexture* image, float x, float y)
{
    this->spriteSheetTexture=image;
    width=0;

    wordLen=word.size();
    this->word=word;
    chars= NULL;
    position.x=x;
    position.y=y;
    /*float posX=position.x-16*(wordLen-1);
    int asciiVal;
    for(int i=0; i<wordLen; i++)
    {

        asciiVal=(int)word[i];
        Character temp(spriteSheetTexture,posX+width,y, asciiVal);
        chars[i]=temp;
        width+=32;
        if(i>0)
        {
            chars[i-1].SetPosition(x-width,y+height/2);
            //chars[i].SetPosition(x+width,y+height/2);
        }
    }*/
}

Word::Word(const Word& cpy)
{
    this->position.x=cpy.position.x;
    this->position.y=cpy.position.y;
    this->spriteSheetTexture=cpy.spriteSheetTexture;
    this->word=cpy.word;
    this->wordLen=cpy.wordLen;
    chars= new Character[wordLen];
    for(int i=0;i<wordLen;i++)
    {
        chars[i]=cpy.chars[i];
    }
    this->width=cpy.width;
    this->height=cpy.height;
}

void Word::Render(SDL_Renderer* gRenderer)
{
    chars= new Character[wordLen];
    float posX=position.x-16*(wordLen-1);
    int asciiVal;

    for(int i=0; i<wordLen; i++)
    {

        asciiVal=(int)word[i];
        Character temp(spriteSheetTexture,posX+width,position.y, asciiVal);
        chars[i]=temp;
        width+=32;
        chars[i].Render(gRenderer,false);
    }
    //width=0;
   // float posX=position.x-16*(wordLen-1);
    //for(int i=0; i<wordLen; i++)
   // {
        //chars[i].SetPosition(posX+width,position.y);

        //width+=32;
   // }
}

int Word::getLength()
{
    return wordLen;
}

Word::~Word()
{
    cout<<"Word "<<word<<" is destroyed"<<endl;
    if (chars!=NULL)
        delete[] chars;                                     ///deallocating dynamic array
}

int Word::getWidth()
{
    return width;
}

void Word::setPosition(float x, float y)
{
    position.x=x;
    position.y=y;
}
void Word::changeWord(std::string word)
{
    this->word=word;
    wordLen=word.size();
}
