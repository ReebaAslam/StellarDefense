#include "Explosion.hpp"
Explosion::Explosion(LTexture* image, float x, float y,int explosion_frames)//, int xsheet, int ysheet, int widthsheet, int heightsheet) //, int explosion_frames)
{
	this->explosion_frames = explosion_frames;
	EX_spriteClips = new SDL_Rect[explosion_frames];
	spriteSheetTexture = image;
	if (explosion_frames == 64)
	{
		for (int i = 0; i < 64; i++)
		{
			EX_spriteClips[i].x = 125*i;//192 * i; //40*i
			EX_spriteClips[i].y = 0;//25; //131 //0
			EX_spriteClips[i].w = 125; //192; //40
			EX_spriteClips[i].h = 125;//190; //41

		}
		//for (int i = 32; i < 64; i++)
		//{
		//	EX_spriteClips[i].x = 192 * i; //40*i
		//	EX_spriteClips[i].y = 215; //131 //190
		//	EX_spriteClips[i].w = 192; //40
		//	EX_spriteClips[i].h = 190; //41

		//}
		widthSheet = EX_spriteClips[0].w;
		heightSheet = EX_spriteClips[0].h;
	}
	else if (explosion_frames == 20)
	{
		for (int i = 0; i < 20; i++)
		{
			EX_spriteClips[i].x = 50 * i; //40*i
			EX_spriteClips[i].y = 0; //131 //190
			EX_spriteClips[i].w = 50; //40
			EX_spriteClips[i].h = 50; //41

		}
		widthSheet = EX_spriteClips[0].w;
		heightSheet = EX_spriteClips[0].h;
	}
	position.x = x; //uses point attribute of the gameobject
	position.y = y;
	frame = 0;

}
Explosion::~Explosion()
{
	printf("Explosion Destructed\n");
	spriteSheetTexture = NULL;
}
bool Explosion::EndExplosion()
{
	return (this->frame == explosion_frames);
}
void Explosion::Render(long int& frame, SDL_Renderer* gRenderer, SDL_RendererFlip flip)
{
	++this->frame;
	spriteSheetTexture->RenderTexture(position.x - widthSheet / 2, position.y - heightSheet / 2, gRenderer,&EX_spriteClips[frame % explosion_frames], flip,0.0, NULL);
}