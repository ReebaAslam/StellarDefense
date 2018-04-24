#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "LTexture.h"
#include <string>
#include <sstream>
#include "word.h"
#include "Button.h"
#include "splashScreen.h"
#include "menuScreen.h"
#include "excerptScreen.h"
#include "gameScreen.h"
#include "pauseScreen.h"
#include "InventoryScreen.h"
#include "quitScreen.h"
#include "GameObject.hpp"
#include "SpaceShip.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"
#include "Beam.hpp"
#include <math.h>
#include <vector>
#include "HealthBar.hpp"
#include "Ammunition.hpp"
#include "Explosion.hpp"
#include "Planet.h"
#include "BlackHole.h"
#include "Asteroid.h"
#include "Star.h"
#include "GameManager.h"


//Pre defined screen width and height
const int SCREEN_WIDTH = GlobalFunctions::GetSCREEN_WIDTH();
const int SCREEN_HEIGHT = GlobalFunctions::GetSCREEN_HEIGHT();

Mix_Music* music = NULL;
Mix_Chunk* objectExplosionSound = NULL;
Mix_Chunk* spaceShipExplosionSound = NULL;
Mix_Chunk* buttonHover = NULL;
Mix_Chunk* fire = NULL;
Mix_Chunk* beamSound=NULL;
Mix_Chunk* enemyFire = NULL;
Mix_Chunk* screenTransition = NULL;
Mix_Chunk* canonSound = NULL;


bool init();
bool loadMedia();
void close();

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
GameManager game;

///Textures for different images that rendered on the screen
LTexture gFontTexture;
LTexture gExcerpt;
LTexture gSplashTexture;
LTexture gMainMenuTexture;
LTexture gGameTexture;
LTexture gResourceInfoTexture;
LTexture gPauseTexture;
LTexture gInventoryTexture;
LTexture gQuitTexture;

LTexture gSpriteSheetTexture1;
LTexture gSpriteSheetTexture2;
LTexture gSpriteSheetTexture3;

LTexture hero;
LTexture enemies;
LTexture blue_fire;
LTexture red_fire;
LTexture explosion;
LTexture asteroid_ex;
LTexture sun_ex;
LTexture beam;

LTexture planet;
LTexture star;
LTexture asteriod1;
LTexture asteriod2;
LTexture blackhole;

vector<GameObject*> Objects;
vector<GameObject*> bullets;
vector<Explosion*> explosions;

bool init();
bool loadMedia();
void close();
void CleanVectors();
void PopulateVectors();
void EmptyObjects();

GameObject* object = NULL;

int main( int argc, char* args[] )
{
    ///flags to check which screen is running
    bool splashRunning=true;
    bool menuRunning=true;
    bool excerptRunning=false;
    bool gameRunning=false;
    bool pauseRunning=false;
    bool inventoryRunning=false;
    bool quitRunning=false;

    bool NoMoney=false;
    bool NoHealth=false;

    bool renderAll = false;
    bool newGame=true;
    bool longDelay=false;

    bool mouseClicked=false; ///flag indicating mouse click
    bool renderEarth = false;
    bool Delay=false;       ///flag indicating whether there needs to be a Delay in screen transitioning
    bool QuitToPause=false; ///flag indicating transition from Quit to Pause Screens and vice versa

    int ButtonIndex=-1;     ///index of button in selection, negative value shows none
    int posX,posY;
    int ButtonCount;        ///No of Buttons on the screen
    Button* buttons=NULL;   ///will hold button(s) on the screen

    ///Alpha Modulation component
    Uint8 a = 255;
    Uint8 b = 0;

    int x,y;

    //The background scrolling offset
    int scrollingOffset = 0;

	///Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		///Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{

			bool quit = false;                      ///Main loop flag
			long int frame = 0;
			long int frame1=0;
			SDL_Event e;                            ///Event handler

            int StartCount=0;
			///initialize random seed:
            srand (time(NULL));
			Point direction;
			bool change_weapon = false;
			bool iamalive = true;
			GameObject* earth = new Planet(&planet, 600, 100, 0, 0, 163, 172, 0);
			GameObject* plane = new SpaceShip(&hero, (float)SCREEN_WIDTH / 2, (float)SCREEN_HEIGHT / 2+ 100, 0, 0, 99, 87, 0);
			int scrollingOffset = 0;
			Explosion* explode = NULL;
            HealthBar BeamBar;
			int beamlevel;
			SDL_Rect rect = { 1050,40,200,10 };
			BeamBar.setRect(&rect);
			BeamBar.setHealth(198);
			float angle = 0;
            ///creating all screen objects


            splashScreen splash(&gSplashTexture, SCREEN_WIDTH, SCREEN_HEIGHT);

            menuScreen mainMenu(&gMainMenuTexture,&gFontTexture,SCREEN_WIDTH,SCREEN_HEIGHT);

            excerptScreen Excerpt(&gExcerpt,SCREEN_WIDTH,SCREEN_HEIGHT);

            gameScreen GameScreen(&gGameTexture,&gFontTexture,&gResourceInfoTexture,SCREEN_WIDTH, SCREEN_HEIGHT);

            pauseScreen PauseScreen(&gPauseTexture,&gFontTexture,SCREEN_WIDTH,SCREEN_HEIGHT);

            InventoryScreen Iscreen(&gSpriteSheetTexture1,&gSpriteSheetTexture2,&gSpriteSheetTexture3,&gFontTexture, &gInventoryTexture, (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT);

            quitScreen QuitScreen(&gQuitTexture,&gFontTexture,SCREEN_WIDTH,SCREEN_HEIGHT);

            int resourceCount[3]={0,0,0};
            int resourceCost[3]={100,150,50};



            //PopulateVectors();

			if( Mix_PlayingMusic() == 0 )
            {
                //Play the music
                Mix_PlayMusic( music, -1 );
            }
            //If music is being played
            else
            {
                //If the music is paused
                if( Mix_PausedMusic() == 1 )
                {
                    //Resume the music
                    Mix_ResumeMusic();
                }
                //If the music is playing
                else
                {
                    //Pause the music
                    Mix_PauseMusic();
                }
            }

			while( !quit )                          ///While application is running
			{
				while( SDL_PollEvent( &e ) != 0 )   ///Handle events on queue
				{

                    if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					SDL_GetMouseState(&x,&y);           ///gets position of pointer on the screen
					if (menuRunning)                    ///event handling for menu screen
                    {
                        for(int i=0;i<2;i++)
                        {
                            GameScreen.ChangeButtonState(Normal,i);     ///when transitioning to game screen, all buttons would be normal
                        }

                        buttons=mainMenu.getButtons();
                        ButtonCount=mainMenu.getButtonCount();
                        if(e.type==SDL_KEYDOWN)             ///key events handling
                        {
                            const Uint8 *KeyState=SDL_GetKeyboardState(NULL);
                            if(KeyState[SDL_SCANCODE_TAB])                      ///checks if TAB Key is pressed and increases ButtonIndex
                            {
                                if(ButtonIndex==ButtonCount-1 || ButtonIndex<0) ///keeps the ButtonIndex in range
                                    ButtonIndex=0;
                                else
                                    ButtonIndex++;
                                for(int i=0; i<ButtonCount; i++)
                                {
                                    if(i==ButtonIndex)
                                        mainMenu.ChangeButtonState(Hover,i);    ///Button State of selected button changes to Hover
                                    else
                                        mainMenu.ChangeButtonState(Normal,i);   ///Button State of non-selected buttons remains Normal
                                }
                            }
                            else if(KeyState[SDL_SCANCODE_RETURN])      ///presses the button when ENTER is pressed
                            {
                                mainMenu.ChangeButtonState(Clicked,ButtonIndex);    ///Button State of pressed button changes to Clicked

                                ///Checks the Text of Clicked Button to function the Game accordingly
                                StartCount++;
                                if(buttons[ButtonIndex].getText()=="NEW GAME" && newGame)
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    excerptRunning=true;
                                    newGame=false; ///make this false so that populate vectors is not called in every frame.
                                    plane->setHealth(198);
                                    BeamBar.setHealth(198);
                                    renderEarth=false;
                                    change_weapon=false;
                                    plane->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                                    plane->SetAlive(true);
                                    plane->SetCash(0);
                                    resourceCount[0]=resourceCount[1]=resourceCount[2]=0;
                                    iamalive=true;
                                    if(StartCount>1)
                                        EmptyObjects();
                                    PopulateVectors();
                                    renderAll = true;
                                }
                                else if (buttons[ButtonIndex].getText()=="CONTINUE")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    game.Load(&star,&asteriod1,&asteriod2, &blackhole,&enemies,&hero, &planet);
                                    menuRunning=false;
                                    newGame=false;
                                    gameRunning=true;
                                    renderAll = true;
                                    //load game code here
                                }
                                else if (buttons[ButtonIndex].getText()=="  EXIT  ")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    quit=true;     ///Exits the Game
                                }
                                ButtonIndex=-1;   ///Buttons trigger screen transitions so no Button should be selected on the new screen
                            }
                        }
                        ///mouse events handling
                        if (e.type==SDL_MOUSEBUTTONDOWN && !splashRunning)
                        {
                            if(e.button.button==SDL_BUTTON_LEFT)
                                mouseClicked=true;
                        }
                        else if(e.type==SDL_MOUSEBUTTONUP && mouseClicked)
                        {
                            for(int i=0; i<ButtonCount; i++)    ///loop going through each button index
                            {
                                ///x and y positions of the button with index i on the screen
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                ///checks if the pointer position lie inside the border of the button
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=-1;
                                    mainMenu.ChangeButtonState(Clicked,i);
                                    StartCount++;
                                    if(buttons[i].getText()=="NEW GAME" && newGame)
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        excerptRunning=true;
                                        newGame=false;
                                        renderEarth=false;
                                        plane->setHealth(198);
                                        BeamBar.setHealth(198);
                                        change_weapon=false;
                                        plane->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                                        plane->SetAlive(true);
                                        iamalive=true;
                                        plane->SetCash(0);
                                        resourceCount[0]=resourceCount[1]=resourceCount[2]=0;
                                        if(StartCount>1)
                                            EmptyObjects();
                                        PopulateVectors();
                                        renderAll = true;
                                        break;
                                    }
                                    else if (buttons[i].getText()=="CONTINUE")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        //load game code here
                                        game.Load(&star,&asteriod1,&asteriod2, &blackhole,&enemies,&hero, &planet);
                                        menuRunning=false;
                                        gameRunning=true;
                                        newGame=false;
                                        renderAll = true;
                                        break;

                                    }
                                    else if (buttons[i].getText()=="  EXIT  ")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        quit=true;
                                    }
                                }
                            }
                        }
                        else if(e.type==SDL_MOUSEMOTION)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    mainMenu.ChangeButtonState(Hover,i);
                                    ButtonIndex=i;  ///ButtonIndex changes to the Button, pointer is hovering over
                                }
                                else
                                {
                                    mainMenu.ChangeButtonState(Normal,i);
                                }
                            }
                        }
                    }
                    else if(gameRunning && !pauseRunning && !inventoryRunning && !quitRunning)   ///events handling for when only Game Screen Running
                    {
                        for(int i=0;i<3;i++)
                        {
                            PauseScreen.ChangeButtonState(Normal,i);    ///when transitioning to Pause screen, all buttons would be normal
                        }
                        ///Back Button on Inventory should be normal because only Back button is used for transition between inventory and game screen
                        Iscreen.ChangeButtonState(Normal,3);
                        ButtonCount=GameScreen.getButtonCount();
                        buttons=GameScreen.getButtons();
                        if(e.type==SDL_KEYDOWN)
                        {
                            const Uint8 *KeyState=SDL_GetKeyboardState(NULL);
                            if(KeyState[SDL_SCANCODE_TAB])
                            {
                                if(ButtonIndex==ButtonCount-1 || ButtonIndex<0)
                                    ButtonIndex=0;
                                else
                                    ButtonIndex++;
                                for(int i=0; i<ButtonCount; i++)
                                {
                                    if(i==ButtonIndex)
                                        GameScreen.ChangeButtonState(Hover,i);
                                    else
                                        GameScreen.ChangeButtonState(Normal,i);
                                }
                            }

                            else if(KeyState[SDL_SCANCODE_RETURN])
                            {
                                GameScreen.ChangeButtonState(Clicked,ButtonIndex);
                                if(buttons[ButtonIndex].getText()=="PAUSE")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    pauseRunning=true;
                                }
                                else if (buttons[ButtonIndex].getText()=="INVENTORY")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    inventoryRunning=true;
                                }
                                ButtonIndex=-1;
                            }


						if (KeyState[SDL_SCANCODE_D])
							plane->Move(RIGHT);
						if (KeyState[SDL_SCANCODE_A])
							plane->Move(LEFT);
						if (KeyState[SDL_SCANCODE_W])
							plane->Move(UP);
						if (KeyState[SDL_SCANCODE_S])
							plane->Move(DOWN);
						if (KeyState[SDL_SCANCODE_2])
							change_weapon = true;
						if (KeyState[SDL_SCANCODE_1])
							change_weapon = false;
                        }
                        if (e.type==SDL_MOUSEBUTTONDOWN)
                        {
                            if(e.button.button==SDL_BUTTON_LEFT)
                                mouseClicked=true;
                            if (plane->CheckAlive())
                            {
                                if (change_weapon)
                                {
                                    beamlevel = BeamBar.getHealth();
                                    BeamBar.setHealth(beamlevel - 33);
                                    if (beamlevel > 0)
                                    {
                                        Mix_PlayChannel(-1, canonSound, 0);
                                        Mix_PlayChannel(-1, beamSound, 0);
                                        bullets.push_back(plane->Fire(&beam, "beam"));
                                    }
                                    else if(beamlevel<=0)
                                    {
                                        change_weapon=false;
                                    }
                                }
                                else
                                {
                                    Mix_PlayChannel(-1, fire, 0);
                                    bullets.push_back(plane->Fire(&blue_fire, "bullet"));
                                }
                            }
                        }
                        else if(e.type==SDL_MOUSEBUTTONUP && mouseClicked)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=-1;
                                    GameScreen.ChangeButtonState(Clicked,i);
                                    if(buttons[i].getText()=="PAUSE")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        pauseRunning=true;
                                        break;
                                    }
                                    else if(buttons[i].getText()=="INVENTORY")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        inventoryRunning=true;
                                        break;
                                    }
                                }
                            }
                        }
                        else if(e.type==SDL_MOUSEMOTION)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=i;
                                    GameScreen.ChangeButtonState(Hover,i);
                                }
                                else
                                {
                                    GameScreen.ChangeButtonState(Normal,i);
                                }
                            }
                        }
                    }
                    else if(pauseRunning)       ///events handling for pause menu
                    {
                        for(int i=0;i<3;i++)
                        {
                            QuitScreen.ChangeButtonState(Normal,i);    ///when transitioning to Quit screen, all buttons would be normal
                        }
                        buttons=PauseScreen.getButtons();
                        ButtonCount=PauseScreen.getButtonCount();
                        if(e.type==SDL_KEYDOWN)
                        {
                            const Uint8 *KeyState=SDL_GetKeyboardState(NULL);
                            if(KeyState[SDL_SCANCODE_TAB])
                            {
                                if(ButtonIndex==ButtonCount-1 || ButtonIndex<0)
                                    ButtonIndex=0;
                                else
                                    ButtonIndex++;
                                for(int i=0; i<ButtonCount; i++)
                                {
                                    if(i==ButtonIndex)
                                        PauseScreen.ChangeButtonState(Hover,i);
                                    else
                                        PauseScreen.ChangeButtonState(Normal,i);
                                }
                            }

                            else if(KeyState[SDL_SCANCODE_RETURN])
                            {
                                Delay=true;             ///All transitions from pause screen would have a delay
                                PauseScreen.ChangeButtonState(Clicked,ButtonIndex);
                                GameScreen.ChangeButtonState(Normal,0);     ///when transitioning to Game screen, Pause button would be normal

                                if(buttons[ButtonIndex].getText()==" RESUME ")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    //pauseRunning=false;
                                    GameScreen.ChangeButtonState(Normal,0);     ///when transitioning to Game screen, Pause button would be normal
                                }
                                else if (buttons[ButtonIndex].getText()=="RESTART")
                                {
                                    StartCount++;
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    newGame=true;
                                    renderEarth=false;
                                    plane->setHealth(198);
                                    BeamBar.setHealth(198);
                                    change_weapon=false;
                                    plane->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                                    plane->SetAlive(true);
                                    plane->SetCash(0);
                                    resourceCount[0]=resourceCount[1]=resourceCount[2]=0;
                                    iamalive=true;
                                    if(StartCount>1)
                                        EmptyObjects();
                                    PopulateVectors();
                                    renderAll = true;
                                    break;
                                    //restart the game here
                                }
                                else if (buttons[ButtonIndex].getText()=="  QUIT  ")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    quitRunning=true;
                                    break;
                                    //pauseRunning=false;
                                }
                                ButtonIndex=-1;
                            }
                        }
                        if (e.type==SDL_MOUSEBUTTONDOWN)
                        {
                            if(e.button.button==SDL_BUTTON_LEFT)
                                mouseClicked=true;
                        }
                        else if(e.type==SDL_MOUSEBUTTONUP && mouseClicked)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    Delay=true;
                                    ButtonIndex=-1;
                                    GameScreen.ChangeButtonState(Normal,0);
                                    PauseScreen.ChangeButtonState(Clicked,i);
                                    if(buttons[i].getText()==" RESUME ")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        //pauseRunning=false;
                                        break;
                                    }
                                    else if (buttons[i].getText()=="RESTART")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        newGame=true;
                                        StartCount++;
                                        plane->setHealth(198);
                                        BeamBar.setHealth(198);
                                        change_weapon=false;
                                        renderEarth=false;
                                        plane->setPosition(SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                                        plane->SetCash(0);
                                        resourceCount[0]=resourceCount[1]=resourceCount[2]=0;
                                        plane->SetAlive(true);
                                        iamalive=true;
                                        if(StartCount>1)
                                            EmptyObjects();
                                        PopulateVectors();
                                        renderAll = true;
                                        break;
                                        //restart the game here
                                    }

                                    else if(buttons[i].getText()=="  QUIT  ")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        quitRunning=true;
                                        //pauseRunning=false;
                                        break;
                                    }
                                }
                            }
                        }
                        else if(e.type==SDL_MOUSEMOTION)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=i;
                                    PauseScreen.ChangeButtonState(Hover,i);
                                }
                                else
                                {
                                    PauseScreen.ChangeButtonState(Normal,i);
                                }
                            }
                        }
                    }
                    else if(inventoryRunning)   ///events handling for Inventory Screen
                    {
                        Button* buttons=Iscreen.getButtons();
                        ButtonCount=Iscreen.getButtonCount();
                        if(e.type==SDL_KEYDOWN)
                        {
                            const Uint8 *KeyState=SDL_GetKeyboardState(NULL);
                            if(KeyState[SDL_SCANCODE_TAB])
                            {
                                if(ButtonIndex==ButtonCount-1 || ButtonIndex<0)
                                    ButtonIndex=0;
                                else
                                    ButtonIndex++;
                                for(int i=0; i<ButtonCount; i++)
                                {
                                    if(i==ButtonIndex)
                                        Iscreen.ChangeButtonState(Hover,i);
                                    else
                                        Iscreen.ChangeButtonState(Normal,i);
                                }
                            }

                            else if(KeyState[SDL_SCANCODE_RETURN])
                            {
                                Iscreen.ChangeButtonState(Clicked,ButtonIndex);
                                if(buttons[ButtonIndex].getText()=="  BACK  ")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    Delay=true;
                                    //inventoryRunning=false;
                                    GameScreen.ChangeButtonState(Normal,1);     ///when transitioning to Game screen, Inventory button would be normal
                                }
                                else if (buttons[ButtonIndex].getText()=="BUY")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);

                                    int cash=plane->GetCash();
                                    if (cash>=resourceCost[ButtonIndex])
                                    {
                                        int newcash = cash - resourceCost[ButtonIndex];
                                        plane->SetCash(newcash);
                                        resourceCount[ButtonIndex]++;
                                    }
                                    else
                                    {
                                        NoMoney=true;
                                    }


                                    //check balance and then deduct money if the resource is affordable
                                }
                                ButtonIndex=-1;
                            }
                        }
                        if (e.type==SDL_MOUSEBUTTONDOWN)
                        {
                            if(e.button.button==SDL_BUTTON_LEFT)
                                mouseClicked=true;
                        }
                        else if(e.type==SDL_MOUSEBUTTONUP && mouseClicked)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=-1;
                                    Iscreen.ChangeButtonState(Clicked,i);
                                    if(buttons[i].getText()=="  BACK  ")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        Delay=true;
                                        //inventoryRunning=false;
                                        GameScreen.ChangeButtonState(Normal,1);
                                        break;
                                    }
                                    else if(buttons[i].getText()=="BUY")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);

                                        int cash=plane->GetCash();
                                        if (cash>=resourceCost[i])
                                        {
                                            int newcash = cash - resourceCost[i];
                                            plane->SetCash(newcash);
                                            resourceCount[i]++;
                                        }
                                        else
                                        {
                                            NoMoney=true;
                                        }


                                        //check balance and then deduct money if the resource is affordable
                                        break;
                                    }

                                }
                            }
                        }
                        else if(e.type==SDL_MOUSEMOTION)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=i;
                                    Iscreen.ChangeButtonState(Hover,i);
                                }
                                else
                                {
                                    Iscreen.ChangeButtonState(Normal,i);
                                }
                            }
                        }
                    }
                    else if(quitRunning)    ///events handling for quit screen
                    {
                        buttons=QuitScreen.getButtons();
                        ButtonCount=QuitScreen.getButtonCount();
                        if(e.type==SDL_KEYDOWN)
                        {
                            const Uint8 *KeyState=SDL_GetKeyboardState(NULL);
                            if(KeyState[SDL_SCANCODE_TAB])
                            {
                                if(ButtonIndex==ButtonCount-1 || ButtonIndex<0)
                                    ButtonIndex=0;
                                else
                                    ButtonIndex++;
                                for(int i=0; i<ButtonCount; i++)
                                {
                                    if(i==ButtonIndex)
                                        QuitScreen.ChangeButtonState(Hover,i);
                                    else
                                        QuitScreen.ChangeButtonState(Normal,i);
                                }
                            }

                            else if(KeyState[SDL_SCANCODE_RETURN])
                            {
                                Delay=true;
                                QuitScreen.ChangeButtonState(Clicked,ButtonIndex);
                                if(buttons[ButtonIndex].getText()==" YES ")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    game.Save(Objects, earth, plane,&BeamBar);
                                    //save game code here
                                    //quitRunning=false;
                                    gameRunning=false;
                                    menuRunning=true;
                                    mainMenu.ChangeButtonState(Normal,1);       ///NewGame button on Main Menu would be normal on transition
                                    mainMenu.ChangeButtonState(Normal,0);       ///Continue button Main Menu would be normal on transition
                                    renderAll = false;
                                    newGame = true;
                                }
                                else if (buttons[ButtonIndex].getText()=="  NO  ")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    //quitRunning=false;
                                    gameRunning=false;
                                    menuRunning=true;
                                    newGame = true;
                                    mainMenu.ChangeButtonState(Normal,1);
                                    mainMenu.ChangeButtonState(Normal,0);
                                    renderAll = false;
                                }
                                else if (buttons[ButtonIndex].getText()=="CANCEL")
                                {
                                    Mix_PlayChannel(-1, buttonHover, 0);
                                    //quitRunning=false;
                                    pauseRunning=true;
                                    QuitToPause=true;
                                    PauseScreen.ChangeButtonState(Normal,2);    ///Quit Button on Pause Screen would be normal on transition
                                }
                                ButtonIndex=-1;
                            }
                        }
                        if (e.type==SDL_MOUSEBUTTONDOWN)
                        {
                            if(e.button.button==SDL_BUTTON_LEFT)
                                mouseClicked=true;
                        }
                        else if(e.type==SDL_MOUSEBUTTONUP && mouseClicked)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    Delay=true;
                                    ButtonIndex=-1;
                                    QuitScreen.ChangeButtonState(Clicked,i);
                                    if(buttons[i].getText()==" YES ")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        game.Save(Objects, earth, plane,&BeamBar);
                                        //save game code here
                                        //quitRunning=false;
                                        gameRunning=false;
                                        menuRunning=true;
                                        renderAll = false;
                                        newGame = true;
                                        mainMenu.ChangeButtonState(Normal,1);
                                        break;
                                    }
                                    else if (buttons[i].getText()=="  NO  ")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        //quitRunning=false;
                                        gameRunning=false;
                                        menuRunning=true;
                                        renderAll = false;
                                        newGame = true;
                                        mainMenu.ChangeButtonState(Normal,1);
                                        break;
                                    }

                                    else if(buttons[i].getText()=="CANCEL")
                                    {
                                        Mix_PlayChannel(-1, buttonHover, 0);
                                        //quitRunning=false;
                                        pauseRunning=true;
                                        QuitToPause=true;
                                        PauseScreen.ChangeButtonState(Normal,2);
                                        break;
                                    }
                                }
                            }
                        }
                        else if(e.type==SDL_MOUSEMOTION)
                        {
                            for(int i=0; i<ButtonCount; i++)
                            {
                                posX=buttons[i].getPosition().x;
                                posY=buttons[i].getPosition().y;
                                if((x<=posX+buttons[i].getWidth()/2 && x>=posX-buttons[i].getWidth()/2)&&(y<=posY+buttons[i].getHeight()/2 && y>=posY-buttons[i].getHeight()/2))
                                {
                                    ButtonIndex=i;
                                    QuitScreen.ChangeButtonState(Hover,i);
                                }
                                else
                                {
                                    QuitScreen.ChangeButtonState(Normal,i);
                                }
                            }
                        }
                    }

				}
				///Scroll background
                --scrollingOffset;
                if( scrollingOffset < -gGameTexture.GetWidth() )
                {
                    scrollingOffset = 0;
                }

				///Cap if below 0
                if( a - 32 < 0 )
                {
                    a = 0;
                }
                ///Decrement otherwise
                else
                {
                    a -= 2;
                    if(excerptRunning &&gameRunning)
                        a-=5;
                }
                ///Cap if above 255
                if( b-255 > 0 )
                {
                    b=255;
                }
                ///Increment otherwise
                else
                {
                    b+=2;
                    if(excerptRunning &&gameRunning)
                        b+=5;
                }


				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );    ///Clear screen
				SDL_RenderClear( gRenderer );


                if(splashRunning)       ///checks if Splash screen is running
                {
                    gSplashTexture.setAlpha(a);     ///Splash Screen fades out with a decreasing
                    splash.Render(gRenderer);       ///Rendering Splash Screen
                    if(a==0)
                    {
                        Mix_PlayChannel(-1, screenTransition, 0);
                        splashRunning=false;    ///indicates the end of splash screen run
                        a=255;
                        b=0;
                    }
                }
                if(menuRunning && !splashRunning && !Delay)     ///checks if Main Menu Screen is running
                {
                    gMainMenuTexture.setAlpha(a);
                    if(a<=200)
                        gFontTexture.setAlpha(a);
                    else
                        gFontTexture.setAlpha(200);
                    mainMenu.Render(gRenderer);
                    if(!excerptRunning)         ///checks if transition to Excerpt is not called
                    {
                        a=255;      ///maintains the alpha values
                        b=0;
                    }

                }
                if(excerptRunning && menuRunning)       ///transition between game and menu screen involves an excerpt, checks if the excerpt has to be rendered
                {
                    gExcerpt.setAlpha(b);
                    Excerpt.Render(gRenderer);

                    if(a==0)    ///checks if the screen has completely faded
                    {
                        Mix_PlayChannel(-1, screenTransition, 0);
                        SDL_Delay(3000);        ///keeps the excerpt on screen for 3 seconds
                        gameRunning=true;       ///indicates the start of game screen run
                        menuRunning=false;
                        a=255;
                        b=0;
                    }
                }
                if(gameRunning && excerptRunning)       ///transition between Game screen and Excerpt
                {
                    scrollingOffset=0;      ///game screen would stay in original position during transition
                    gExcerpt.setAlpha(a);
                    Excerpt.Render(gRenderer);
                    gGameTexture.setAlpha(b);
                    gFontTexture.setAlpha(b);
                    GameScreen.Render(gRenderer);
                    if(a==0)
                        excerptRunning=false;

                }
                if(gameRunning && !excerptRunning)      ///checks if only game screen is running
                {
                    ///keeps the alpha value maximum if no other screen is being rendered over game screen
                    if(!pauseRunning && !inventoryRunning && !quitRunning && !Delay)
                    {
                        gFontTexture.setAlpha(255);
                        gGameTexture.setAlpha(255);
                        hero.setAlpha(255);
                        enemies.setAlpha(255);
                        red_fire.setAlpha(255);
                        explosion.setAlpha(255);
                        asteroid_ex.setAlpha(255);
                        sun_ex.setAlpha(255);
                        beam.setAlpha(255);
                        planet.setAlpha(255);
                        star.setAlpha(255);
                        asteriod1.setAlpha(255);
                        asteriod2.setAlpha(255);
                        blackhole.setAlpha(255);

                    }
                    ///decreases it otherwise
                    else
                    {
                        scrollingOffset++;      ///keeps the Game screen still if other screens are being rendered
                        gGameTexture.setAlpha(100);
                        hero.setAlpha(100);
                        enemies.setAlpha(100);
                        red_fire.setAlpha(100);
                        explosion.setAlpha(100);
                        asteroid_ex.setAlpha(100);
                        sun_ex.setAlpha(100);
                        beam.setAlpha(100);
                        planet.setAlpha(100);
                        star.setAlpha(100);
                        asteriod1.setAlpha(100);
                        asteriod2.setAlpha(100);
                        blackhole.setAlpha(100);
                        plane->GetHealthBar().SetAlpha(100);
                        BeamBar.SetAlpha(100);
                        earth->GetHealthBar().SetAlpha(100);
                        for (auto i:Objects)
                        {
                            if (i->GetName() == "enemy")
                            {
                                i->GetHealthBar().SetAlpha(100);
                            }
                        }
                    }
                    GameScreen.Render(gRenderer,scrollingOffset);
                    GameScreen.Render(gRenderer,scrollingOffset+SCREEN_WIDTH);

                    ostringstream convert;
                    convert<<plane->GetCash();
                    string Result=convert.str();
                    Word Money(Result,&gFontTexture,100,50);
                    Money.Render(gRenderer);

                    ostringstream convert2;
                    convert2<<resourceCount[0];
                    Result=convert2.str();
                    Word Chemical(Result,&gFontTexture,445,625);
                    Chemical.Render(gRenderer);


                    ostringstream convert3;
                    convert3<<resourceCount[1];
                    Result=convert3.str();
                    Word Water(Result,&gFontTexture,600,625);
                    Water.Render(gRenderer);

                    ostringstream convert4;
                    convert4<<resourceCount[2];
                    Result=convert4.str();
                    Word Plant(Result,&gFontTexture,755,625);
                    Plant.Render(gRenderer);

                    if (!pauseRunning && !inventoryRunning && !quitRunning && !Delay && renderAll)
                    {
                        if (plane->GetCash() >= 300)
                        {
                            renderEarth = true;
                        }
                        if(renderEarth)
                            earth->Render(frame, gRenderer, SDL_FLIP_NONE, angle);

                        int s_size = 0;
                        for (auto i : Objects)
                        {
                            if (i->GetName() == "enemy")
                            {
                                ++s_size;
                                i->SetSpeedxy(2.0, 2.0);
                                i->SetAngle(plane->GetCenter().x, plane->GetCenter().y);
                                i->Render(frame, gRenderer, SDL_FLIP_VERTICAL, i->GetAngle());
                                i->Move(plane->GetCenter().x, plane->GetCenter().y);
                                if (frame % 50 == 0 && plane->CheckAlive())
                                {
                                    int ran = rand() % 2;
                                    if (ran ==1 )
                                    {
                                        Mix_PlayChannel(-1, enemyFire, 0);
                                        bullets.push_back(i->Fire(&red_fire, "bullet"));
                                    }
                                }
                                for (auto j : Objects)
                                {
                                    if (j->GetName() == "enemy")
                                    {
                                        if (i->CheckCollision(j))
                                        {
                                            i->Repel(j);
                                            break;
                                        }
                                    }
                                }
                            }
                            else
                            {
                                i->Render(frame, gRenderer, SDL_FLIP_VERTICAL, angle);
                                //SDL_RenderDrawRect(gRenderer, &i->GetCurrentObjectPosition());
                                i->Move();
                            }
                        }
                        for (auto bull : bullets)
                        {
                            if (bull->GetName() == "enemy bullet") //enemy bullet
                            {
                                bull->SetSpeedxy(-10, 10);
                                if (plane->CheckCollision(bull))
                                {
                                    plane->Attacked(bull->getHarmValue());
                                    bull->SetAlive(false);
                                }
                            }
                            else
                            {
                                bull->SetSpeedxy(10, -10); //my bullet speed
                            }
                            //SDL_RenderDrawRect(gRenderer, &bull->GetCurrentObjectPosition());
                            bull->Render(frame, gRenderer, SDL_FLIP_NONE, 0);
                            bull->Move();
                            bull->BoundaryCollision();
                            for (auto i : Objects)
                            { //bullet collison with enemy and asteroids.
                                if (bull->CheckCollision(i) && bull->GetName() != "enemy bullet") //so that enemy does not kill itself
                                {
                                    if (i->GetName() == "enemy")
                                    {
                                        i->Attacked(bull->getHarmValue()+9);
                                        bull->SetAlive(false);
                                    }
                                    if (i->GetName() == "asteroid")
                                    {
                                        explode = new Explosion(&asteroid_ex, i->GetCenter().x, i->GetCenter().y, 20);
                                        explosions.push_back(explode);
                                        i->SetAlive(false);
                                        bull->SetAlive(false);
                                    }
                                }
                                //if plane collides with asteroid
                                if (i->GetName() == "asteroid")
                                {
                                    if (plane->CheckCollision(i))
                                    {
                                        explode = new Explosion(&asteroid_ex, i->GetCenter().x, i->GetCenter().y, 20);
                                        explosions.push_back(explode);
                                        i->SetAlive(false);
                                        plane->Attacked(1);
                                    }
                                    i->BoundaryCollision();
                                }
                                if (i->GetName() == "blackhole")
                                {
                                    if (plane->CheckCollision(i))
                                        plane->setFriction(0.001f); //gives a feel of being attracted towards blackhole.
                                    else
                                        plane->setFriction(0.97f);
                                }
                                if (i->GetName() == "star")
                                {
                                    if (plane->CheckCollision(i) && iamalive)
                                    {
                                        explode = new Explosion(&explosion, plane->GetCenter().x, plane->GetCenter().y, 64);
                                        explosions.push_back(explode);
                                        plane->SetAlive(false);
                                        iamalive = false;
                                        Word GameOver("Game Over",&gFontTexture,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                                        GameOver.Render(gRenderer);
                                        newGame=true;
                                        menuRunning=true;
                                        gameRunning=false;
                                        longDelay=true;
                                        break;
                                    }
                                }
                            }
                        }
                        for (auto i = explosions.begin(); i != explosions.end();)
                        {
                            Explosion *e = *i;
                            if (e->EndExplosion())
                            {
                                //Play the music
                                Mix_PlayChannel( -1, objectExplosionSound, 0 );

                                i = explosions.erase(i);
                                delete e;
                            }
                            else
                            {
                                e->Render(frame, gRenderer, SDL_FLIP_NONE);
                                i++;
                            }
                        }
                        for (auto i = Objects.begin(); i != Objects.end();)
                        {
                            GameObject *e = *i;
                            if (e->CheckAlive() == false)
                            {
                                if (e->GetName() == "enemy")
                                {
                                    int cash = plane->GetCash();
                                    plane->SetCash(cash+20);
                                    Mix_PlayChannel(-1, spaceShipExplosionSound, 0);
                                    explode = new Explosion(&explosion, e->GetCenter().x, e->GetCenter().y, 64);
                                    explosions.push_back(explode);
                                    int ranh = (rand() % SCREEN_HEIGHT)+100;
                                    int ran =rand()%2; //making enemies again.
                                    if (ran)
                                        object = new Enemy(&enemies, 1400, ranh, 0, 0, 120, 120, 0.0);
                                    else
                                        object = new Enemy(&enemies, -100, ranh, 0, 0, 120, 120, 0);
                                    Objects.push_back(object);
                                }
                                if(e->GetName() == "asteroid")
                                {
                                    int ranh = rand() % SCREEN_HEIGHT;
                                    int ranw = (rand() % SCREEN_WIDTH) + SCREEN_WIDTH ;
                                    int ran = rand() % 2;
                                    if (ran)
                                        object = new Asteroid(&asteriod1, ranw, ranh, 0, 0, 57, 60, 0);
                                    else
                                        object = new Asteroid(&asteriod2,ranw, ranh, 0, 0, 49, 60, 0);
                                    object->SetSpeedxy(-2,0);
                                    Objects.push_back(object);
                                }
                                i = Objects.erase(i);
                                delete e;
                            }
                            else i++;
                        }
                        for (auto i = bullets.begin(); i != bullets.end();)
                        {
                            GameObject *e = *i;
                            if (e->CheckAlive() == false)
                            {
                                i = bullets.erase(i);
                                delete e;
                            }
                            else i++;
                        }
                        if (!plane->CheckAlive() && iamalive)
                        {
                            Mix_PlayChannel(-1, spaceShipExplosionSound, 0);
                            explode = new Explosion(&explosion, plane->GetCenter().x, plane->GetCenter().y, 64);
                            explosions.push_back(explode);
                            iamalive = false;
                            NoHealth=true;
                            //break;
                            //quit = true;
                        }
                        else if (iamalive)
                        {
                            plane->SetAngle(x,y);
                            plane->Render(frame, gRenderer, SDL_FLIP_HORIZONTAL, plane->GetAngle());
                            BeamBar.Render("blue", gRenderer);
                            ///SDL_RenderDrawRect(gRenderer, &plane->GetCurrentObjectPosition());
                            ///SDL_RenderDrawLine(gRenderer, plane->GetCenter().x, plane->GetCenter().y, x, y);
                        }
                        if (plane->CheckCollision(earth) && renderEarth)
                        {
                            if (resourceCount[0] > 0 && resourceCount[1] > 0 && resourceCount[2] >0)
                            {
                                Word YouWon("You Win!",&gFontTexture,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                                menuRunning=true;
                                gameRunning=false;
                                longDelay=true;
                                YouWon.Render(gRenderer);
                                newGame=true;
                                plane->setchem(0);
                                plane->setwater(0);
                                plane->setplant(0);
                            }
                            else
                            {
                                Word ResourceMessage("You should have at least one resource each!",&gFontTexture,1270/2,700/2);
                                ResourceMessage.Render(gRenderer);
                                longDelay = true;
                            }
                        }
                        plane->Move();
                        ++frame;
                        if (frame % 65 == 0)
                            frame = 0;
                        ++angle;
                        if (angle == 360)
                            angle = 0;
                    }
                }
                if (pauseRunning || inventoryRunning || quitRunning || Delay)
                {
                    for (auto i : Objects)
                    {
                        if (i->GetName() == "enemy")
                            i->Render(frame, gRenderer, SDL_FLIP_VERTICAL, i->GetAngle());
                        else
                            i->Render(frame,gRenderer,SDL_FLIP_NONE,angle);
                    }
                    for (auto i : bullets)
                    {
                        i->Render(frame,gRenderer,SDL_FLIP_NONE,0);
                    }
                    plane->Render(frame,gRenderer,SDL_FLIP_NONE,plane->GetAngle());
                    if (renderEarth)
                        earth->Render(frame,gRenderer,SDL_FLIP_NONE,0);
                    BeamBar.Render("blue",gRenderer);
                }
                if (quitRunning && !pauseRunning)   ///checks if only Quit screen is running
                {
                    gQuitTexture.setAlpha(150);
                    QuitScreen.Render(gRenderer);
                    ///Stops the Quit Screen from running if there is a Delay due to button press so that quit screen is not rendered in the next iteration
                    if (Delay)
                        quitRunning=false;

                }

                if (pauseRunning)
                {
                    ///Renders Pause Screen when either no transition between Quit and Pause Screen or when transition from Pause to Quit
                    if(!QuitToPause)
                    {
                        gPauseTexture.setAlpha(150);
                        PauseScreen.Render(gRenderer);
                        if(Delay)
                            pauseRunning=false;
                    }
                    ///Stops the Quit Screen from running in the next iteration otherwise
                    else
                    {
                        QuitToPause=false;
                        quitRunning=false;
                    }
                }
                else if(inventoryRunning)       ///checks if inventory screen is running
                {
                    gInventoryTexture.setAlpha(150);
                    Iscreen.Render(gRenderer,0,frame1);
                    if(Delay)
                        Delay=inventoryRunning=false;   ///inventory screen is already running with a delay due to frames
                    if(NoMoney)
                    {
                        Word BuyMessage("Spend after you have earned!",&gFontTexture,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                        BuyMessage.Render(gRenderer);
                        NoMoney=false;
                        longDelay=true;
                    }

                }
                if(NoHealth && gameRunning)
                {
                    Word GameOver("Game Over",&gFontTexture,SCREEN_WIDTH/2,SCREEN_HEIGHT/2);
                    GameOver.Render(gRenderer);
                    newGame=true;
                    menuRunning=true;
                    gameRunning=false;
                    longDelay=true;
                    NoHealth=false;
                }




                SDL_RenderPresent( gRenderer );   ///Update screen
                if(Delay)
                {
                    SDL_Delay(100);     ///Delay of 100 milliseconds
                    Delay=false;        ///Ending Delay for the next iteration
                }

                if(inventoryRunning)
                {
                    ++frame1;           ///increases frames
                    SDL_Delay(100);     ///Delay of 100 milliseconds for smooth animation
                }
                if(longDelay)
                {
                    SDL_Delay(1000);
                    longDelay=false;
                }

			}
		}
	}

	///Free resources and close SDL
	close();

	return 0;
}

bool init()
{
	///Initialization flag
	bool success = true;

	///Initialize SDL
	if( SDL_Init( SDL_INIT_EVERYTHING ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		///Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		///Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}

		else
		{
			///Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
			else
			{
				///Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0, 0, 0, 0 );

				///Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}
	if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        success = false;
    }

	return success;
}

bool loadMedia()
{
	///Loading success flag
	bool success = true;

	///Load sprite sheet texture
	if( !gFontTexture.LoadFromFile( "Images/XiroidFinal2.png", gRenderer) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gFontTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !gExcerpt.LoadFromFile( "Images/Excerpt.png", gRenderer) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gExcerpt.setBlendMode( SDL_BLENDMODE_BLEND );
    }
	if( !gSplashTexture.LoadFromFile( "Images/splashComplete.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
    else
    {
        ///Set standard alpha blending
        gSplashTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
	if( !gMainMenuTexture.LoadFromFile( "Images/mainMenuBG.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gMainMenuTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !gGameTexture.LoadFromFile( "Images/space.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gGameTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !gResourceInfoTexture.LoadFromFile( "Images/ResourceInfo.png" , gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
    if( !gPauseTexture.LoadFromFile( "Images/PauseScreen2.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gPauseTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !gInventoryTexture.LoadFromFile( "Images/InventoryScreen.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gInventoryTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !gQuitTexture.LoadFromFile( "Images/QuitScreen.png", gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
	else
    {
        ///Set standard alpha blending
        gQuitTexture.setBlendMode( SDL_BLENDMODE_BLEND );
    }
    if( !gSpriteSheetTexture1.LoadFromFile( "Images/Chemical.png" , gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
    if( !gSpriteSheetTexture2.LoadFromFile( "Images/Water.png" , gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}
    if( !gSpriteSheetTexture3.LoadFromFile( "Images/Plant4.png" , gRenderer  ) )
	{
		printf( "Failed to load sprite sheet texture!\n" );
		success = false;
	}


		if (!blackhole.LoadFromFile("Images/blackhole.png", gRenderer, false, 255, 255, 255))
	{
		printf("Failed to load blackhole texture!\n");
		success = false;
	}
	if (!asteriod1.LoadFromFile("Images/asteroidSprites.png", gRenderer, true, 255, 255, 255))
	{
		printf("Failed to load asteroid1 texture!\n");
		success = false;
	}
	if (!asteriod2.LoadFromFile("Images/asteroidSprites2.png", gRenderer, true, 255, 255, 255))
	{
		printf("Failed to load asteriod2 texture!\n");
		success = false;
	}
	if (!planet.LoadFromFile("Images/earthSprites.png", gRenderer, false, 255, 255, 255))
	{
		printf("Failed to load asteriod2 texture!\n");
		success = false;
	}
	//if (!gBackground.LoadFromFile("Images/earthSpritesDamaged.png", gRenderer, true, 0, 0, 0))
	//{
	//	printf("Failed to load sick planet texture!\n");
	//	success = false;
	//}
	if (!star.LoadFromFile("Images/bigsun.png",gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load star texture!\n");
		success = false;
	}
	if (!hero.LoadFromFile("Images/mainhero.png", gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load ships texture!\n");
		success = false;
	}
	if (!blue_fire.LoadFromFile("Images/fire_blue2.png", gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load blue fire texture!\n");
		success = false;
	}
	if (!red_fire.LoadFromFile("Images/fire_red.png", gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load blue fire texture!\n");
		success = false;
	}
	if (!beam.LoadFromFile("Images/beams.png", gRenderer, true, 0, 0, 0))
	{
		printf("Failed to load beam texture!\n");
		success = false;
	}
	if (!enemies.LoadFromFile("Images/newenemy.png", gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load enemy texture!\n");
		success = false;
	}
	if (!explosion.LoadFromFile("Images/type_Bs.png", gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load explosion texture!\n");
		success = false;
	}
	if (!asteroid_ex.LoadFromFile("Images/type_A.png", gRenderer, false, 0, 0, 0))
	{
		printf("Failed to load asteroid explosion texture!\n");
		success = false;
	}

   music = Mix_LoadMUS("Sounds/Space 03.wav");
    //If there was a problem loading the music
    if( music == NULL )
    {
        success= false;
    }
    objectExplosionSound = Mix_LoadWAV("Sounds/Explosion 02.wav");
    if(objectExplosionSound==NULL)
    {
        success=false;
    }
    buttonHover = Mix_LoadWAV("Sounds/Button click.wav");
    if(buttonHover==NULL)
    {
        success=false;
    }
    fire = Mix_LoadWAV("Sounds/Fire 02.wav");
    if(fire==NULL)
    {
        success=false;
    }
    beamSound = Mix_LoadWAV("Sounds/Beam.wav");
    if(beamSound==NULL)
    {
        success=false;
    }
    enemyFire = Mix_LoadWAV("Sounds/Fire.wav");
    if(enemyFire==NULL)
    {
        success=false;
    }
    spaceShipExplosionSound = Mix_LoadWAV("Sounds/Enemy Explosion 01.wav");
    if(spaceShipExplosionSound==NULL)
    {
        success=false;
    }
    screenTransition = Mix_LoadWAV("Sounds/Screen Transition 03.wav");
    if(screenTransition==NULL)
    {
        success=false;
    }
    canonSound = Mix_LoadWAV("Sounds/Canon.wav");
    if(canonSound==NULL)
    {
        success=false;
    }*/

	return success;
}
void PopulateVectors()
{
    int ranh, ranw;
    object = new BlackHole(&blackhole, 1150, 160, 0, 0, 175, 175, 0); //blackhole
    Objects.push_back(object);
    for (int i = 0; i < 6; i++) //enemies
    {
        ranh = (rand() % SCREEN_HEIGHT)+100;
        if (i<3)
            object = new Enemy(&enemies, 1400, ranh, 0, 0, 120, 120, 0.0);
        else
            object = new Enemy(&enemies, -100, ranh, 0, 0, 120, 120, 0);
        Objects.push_back(object);
    }
    object = new Star(&star, 325, 100, 1460, 20, 230, 210, 0); //sun
    Objects.push_back(object);
    for (int i = 0; i < 10; i++) //asteriods
    {
        ranh = rand() % SCREEN_HEIGHT;
        ranw = (rand() % SCREEN_WIDTH) + SCREEN_WIDTH ;
        int ran = rand() % 2;
        if (ran)
            object = new Asteroid(&asteriod1, ranw, ranh, 0, 0, 57, 60, 0);
        else
            object = new Asteroid(&asteriod2,ranw, ranh, 0, 0, 49, 60, 0);
        object->SetSpeedxy(-2,0);
        Objects.push_back(object);
    }

}
void EmptyObjects()
{
    for (auto i = Objects.begin(); i != Objects.end();)
    {
        GameObject *e = *i;
        delete e;
        i++;
    }
    Objects.erase(Objects.begin(),Objects.end());
}
void CleanVectors()
{
	int ssize = Objects.size();
	for (int i = 0; i < ssize; i++)
	{
		delete Objects[i];
	}
	ssize = bullets.size();
	for (int i = 0; i < ssize; i++)
	{
		delete bullets[i];
	}
	ssize = explosions.size();
	for (int i = 0; i < ssize; i++)
	{
		delete explosions[i];
	}
}

void close()
{
	///Free loaded images

    CleanVectors();
	hero.Free();
	enemies.Free();
	blue_fire.Free();
	red_fire.Free();
	explosion.Free();
	beam.Free();
	asteroid_ex.Free();
	sun_ex.Free();
	planet.Free();
	//LTexture sickplanet;
	star.Free();
	asteriod1.Free();
	asteriod2.Free();
	blackhole.Free();
	Mix_FreeMusic(music);
	Mix_FreeChunk(objectExplosionSound);
	Mix_FreeChunk(spaceShipExplosionSound);
	Mix_FreeChunk(spaceShipExplosionSound);
	Mix_FreeChunk(buttonHover);
	Mix_FreeChunk(fire);
	Mix_FreeChunk(beamSound);
	Mix_FreeChunk(enemyFire);
	Mix_FreeChunk(screenTransition);
	Mix_FreeChunk(canonSound);

	gFontTexture.Free();
	gExcerpt.Free();
    gSplashTexture.Free();
    gMainMenuTexture.Free();
    gGameTexture.Free();
    gResourceInfoTexture.Free();
    gInventoryTexture.Free();
    gPauseTexture.Free();
    gQuitTexture.Free();

    gSpriteSheetTexture1.Free();
	gSpriteSheetTexture2.Free();
	gSpriteSheetTexture3.Free();

	///Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	///Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
