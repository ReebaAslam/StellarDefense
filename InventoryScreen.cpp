#include "InventoryScreen.h"


InventoryScreen::InventoryScreen(LTexture* gSpriteSheetTexture1,LTexture* gSpriteSheetTexture2,LTexture* gSpriteSheetTexture3 ,LTexture* gSpriteSheetTexture4, LTexture* gSpriteSheetTexture5,float x , float y )
{
    this->width=700;
    this->height=500;
    this->screenWidth=x;
    this->screenHeight=y;
    this->position.x=screenWidth/2-width/2;
    this->position.y=screenHeight/2-height/2;
    float posX=position.x+50;
    float posY=position.y+60;

    ///the name of resource and its price will be on the same index as the resource
    resources[0] = new Chemical(gSpriteSheetTexture1, 100+posX, 150+posY-10);
    resourceName[0]="Chemical";
    prices[0]="100";
    resources[1] = new Water(gSpriteSheetTexture2, 3*100+posX, 150+posY-10);
    resourceName[1]="Water";
    prices[1]="150";
    resources[2] = new Plant(gSpriteSheetTexture3, 5*100+posX, 150-20+posY-10);
    resourceName[2]="Plant";
    prices[2]="50";

    this->fontSprite=gSpriteSheetTexture4;
    ButtonCount=4;
    buttons=new Button[ButtonCount];
    Button Buy1(fontSprite,"BUY" , 100+posX, 2*(float)150+posY);
    buttons[0] = Buy1;
    Button Buy2(fontSprite,"BUY" , 3*100+posX, 2*(float)150+posY);
    buttons[1] = Buy2;
    Button Buy3(fontSprite,"BUY" , 5*100+posX, 2*(float)150+posY);
    buttons[2] = Buy3;
    Button Back(fontSprite,"  BACK  ",screenWidth/2,position.y+height-70);
    buttons[3]=Back;
    for(int i=0; i<3;i++)
    {
        float X=buttons[i].getPosition().x-buttons[i].getWidth()/2+25;
        float Y=buttons[i].getPosition().y-buttons[i].getHeight()/2-40;
        moneyBag bag(fontSprite,X,Y);
        Bags[i]=bag;
    }
    this->bgImage = gSpriteSheetTexture5;
}

InventoryScreen::~InventoryScreen()
{
    for(int i=0;i<3;i++)
    {
        if (resources[i]!=NULL)
            delete resources[i];
    }
    delete[] buttons;

};
void InventoryScreen::Render(SDL_Renderer* gRenderer,int scrollingoffset,long int frame1)
{
    bgImage->RenderTexture( position.x, position.y,gRenderer, NULL);
    for(int i=0; i<ButtonCount; i++)
    {
        buttons[i].Render(gRenderer);
        if(i<3)
        {
            Bags[i].Render(gRenderer);
            Word price(prices[i],fontSprite,0,0);
            float posX=Bags[i].getPosition().x+Bags[i].getWidth()+price.getWidth()/2+32;
            float posY=Bags[i].getPosition().y;
            price.setPosition(posX,posY);
            Price[i]=price;
            Price[i].Render(gRenderer);
        }
    }
    for(int i=0;i<3;i++)
    {
        resources[i]->Render(frame1,gRenderer, SDL_FLIP_NONE,0);
    }

};

string InventoryScreen::whichResource(int index)
{
    return resourceName[index];
}

string InventoryScreen::whatPrice(int index)
{
    return prices[index];
 /*   if (resourceName[index] == "Plant")
        return 50;
    else if (resourceName[index]== "Chemical")
        return 100;
    else if (resourceName[index]== "Water")
        return 150;*/
}
