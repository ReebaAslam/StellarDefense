#include"LTexture.h"


LTexture::LTexture()
{
    this->texture=nullptr;
    this->width=0;
    this->height=0;
}

LTexture::~LTexture()
{
    Free();
}

bool LTexture::LoadFromFile(string path, SDL_Renderer* gRenderer, bool flagColorKey, Uint8 redColorKey, Uint8 greenColorKey, Uint8 blueColorKey)
{
    SDL_Surface* loadedSurface=nullptr;
    SDL_Texture* newTexture=nullptr;

    loadedSurface=IMG_Load(path.c_str());

    if(loadedSurface==nullptr)
    {
        cout<< "Unable to load image from "<< path<< ". SDL_image error"<< IMG_GetError()<<endl;
    }
    else
    {
        //SDL_SetColorKey(loadedSurface, flagColorKey, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
        SDL_SetColorKey(loadedSurface, flagColorKey, SDL_MapRGB(loadedSurface->format, redColorKey, greenColorKey, blueColorKey));
        //SDL_SetColorKey(loadedSurface, flagColorKey, SDL_MapRGB(loadedSurface->format, 255, 255, 255));
        //SDL_SetColorKey(loadedSurface, flagColorKey, SDL_MapRGB(loadedSurface->format, 0, 0, 0));


        newTexture=SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

        if(newTexture!=nullptr)
        {
            this->width=loadedSurface->w;
            this->height=loadedSurface->h;
        }
        else
        {
            cout<< "Unable to create texture from surface from "<<path<< ". SDL_image error"<< IMG_GetError()<<endl;
        }

        SDL_FreeSurface(loadedSurface);
    }
    this->texture=newTexture;
    return this->texture!=nullptr;
}


void LTexture::RenderTexture(int x, int y, SDL_Renderer* gRenderer, SDL_Rect* clip, SDL_RendererFlip flip, double angle, SDL_Point* center)
{
    SDL_Rect rectCoordinates={x, y, this->width, this->height};

    if(clip!=nullptr)
    {
        rectCoordinates.w=clip->w;
        rectCoordinates.h=clip->h;
    }
    SDL_RenderCopyEx(gRenderer, texture, clip, &rectCoordinates, angle, center, flip);
    //SDL_RenderPresent(gRenderer);
}

void LTexture::Free()
{
    if(texture!=nullptr)
    {
        SDL_DestroyTexture(texture);
        texture=nullptr;
        width=0;
        height=0;
    }
}


int LTexture::GetWidth()
{
    return width;
}

int LTexture::GetHeight()
{
    return height;
}

void LTexture::setBlendMode( SDL_BlendMode blending )
{
    //Set blending function
    SDL_SetTextureBlendMode( texture, blending );
}

void LTexture::setAlpha( Uint8 alpha )
{
    //Modulate texture alpha
    SDL_SetTextureAlphaMod( texture, alpha );
}
