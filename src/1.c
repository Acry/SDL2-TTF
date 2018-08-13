#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#include <stdlib.h>
#include <stdio.h>

#define SCREEN_WIDTH    750
#define SCREEN_HEIGHT   (SCREEN_WIDTH/16*7)

int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

SDL_Window   *Window            = NULL;
SDL_Renderer *Renderer          = NULL;

TTF_Font     *Font              = NULL;

SDL_Surface  *temp_Surface      = NULL;

SDL_Texture  *gradient_texture  = NULL;
SDL_Rect gradient_texture_dst;

SDL_Texture  *heal_Texture 	= NULL;
SDL_Texture  *heal2_Texture 	= NULL;

SDL_Texture  *line1_texture 	= NULL;
SDL_Rect line1_texture_dst;
SDL_Texture  *line2_texture 	= NULL;
SDL_Rect line2_texture_dst;
SDL_Texture  *line3_texture 	= NULL;
SDL_Rect line3_texture_dst;
SDL_Texture  *number_texture 	= NULL;
SDL_Rect number_texture_dst;

if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        SDL_Quit();
        return EXIT_SUCCESS;
}

Window = SDL_CreateWindow("Fun with BLENDMODE", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
Renderer =  SDL_CreateRenderer( Window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC| SDL_RENDERER_TARGETTEXTURE);

//BEGIN ICON
SDL_Surface *icon;
icon = SDL_LoadBMP("assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(Window, icon);
SDL_FreeSurface(icon);
//END ICON
if(TTF_Init() == -1) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Failed to initialize SDL2_ttf!", Window);
	SDL_DestroyWindow(Window);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
	
}

Font = TTF_OpenFont("assets/fonts/cafeteria-black.ttf", 60);

if(Font == NULL) {
	SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "SDL", "Failed to load font!", Window);
	SDL_DestroyWindow(Window);
	TTF_CloseFont(Font);
	TTF_Quit();
	SDL_Quit();
	return EXIT_SUCCESS;
}
//BEGIN GRADIENT
temp_Surface = IMG_Load("assets/gfx/gradient.png");
SDL_Rect gradient_src;
gradient_src.x=0;
gradient_src.y=0;
gradient_src.h=68;
gradient_src.w=374;

gradient_texture = SDL_CreateTextureFromSurface(Renderer, temp_Surface);
SDL_QueryTexture(gradient_texture, NULL, NULL, &gradient_texture_dst.w, &gradient_texture_dst.h);
gradient_texture_dst.x=50;
gradient_texture_dst.y=250;
//END 	GRADIENT

int counter = 0;

SDL_Color color;
color.r = 255;
color.g = 255;
color.b = 255;

Uint32 fmt;
fmt=SDL_GetWindowPixelFormat(Window);

temp_Surface = TTF_RenderText_Blended(Font, "Rainbow Heal Beam", color);
heal_Texture = SDL_CreateTextureFromSurface(Renderer,temp_Surface);
int w, h;
SDL_QueryTexture(heal_Texture, NULL, NULL, &w, &h);
heal2_Texture=SDL_CreateTexture(Renderer, fmt, SDL_TEXTUREACCESS_TARGET, w, h);
SDL_Rect pos;
pos.x = 50;
pos.y = 200;
pos.w = w;
pos.h = h;

// LINE1
color.r = 255;
color.g = 0;
color.b = 0;
temp_Surface = TTF_RenderText_Blended(Font, "Drawing Text!", color);
line1_texture=SDL_CreateTextureFromSurface(Renderer,temp_Surface);
SDL_QueryTexture(line1_texture, NULL, NULL, &w, &h);
line1_texture_dst.w=w;
line1_texture_dst.h=h;
line1_texture_dst.x=50;
line1_texture_dst.y=50;

// LINE2
color.r = 0;
color.g = 255;
color.b = 0;
temp_Surface = TTF_RenderText_Blended(Font, "In any color I want!", color);
line2_texture=SDL_CreateTextureFromSurface(Renderer,temp_Surface);
SDL_QueryTexture(line2_texture, NULL, NULL, &w, &h);
line2_texture_dst.w=w;
line2_texture_dst.h=h;
line2_texture_dst.x=50;
line2_texture_dst.y=100;

// LINE3
color.r = 0;
color.g = 0;
color.b = 255;
temp_Surface = TTF_RenderText_Blended(Font, "Counting to 1000 really fast: ", color);
line3_texture=SDL_CreateTextureFromSurface(Renderer,temp_Surface);
SDL_QueryTexture(line3_texture, NULL, NULL, &w, &h);
line3_texture_dst.w=w;
line3_texture_dst.h=h;
line3_texture_dst.x=50;
line3_texture_dst.y=150;

// NUMBER
char buffer[4];
sprintf(buffer, "%d", counter);
temp_Surface = TTF_RenderText_Blended(Font, buffer, color);
number_texture=SDL_CreateTextureFromSurface(Renderer,temp_Surface);
SDL_QueryTexture(number_texture, NULL, NULL, &w, &h);
number_texture_dst.w=w;
number_texture_dst.h=h;
number_texture_dst.x=50+line3_texture_dst.w;
number_texture_dst.y=150;

SDL_Event event;
SDL_bool running = SDL_TRUE;

while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT)
			running = SDL_FALSE;
	}
	SDL_RenderClear(Renderer);

	SDL_RenderCopy(Renderer, line1_texture, NULL, &line1_texture_dst);
	SDL_RenderCopy(Renderer, line2_texture, NULL, &line2_texture_dst);

	SDL_SetRenderTarget(Renderer, heal2_Texture);
	SDL_RenderCopy(Renderer, heal_Texture, NULL, NULL);
	SDL_SetTextureBlendMode(gradient_texture,SDL_BLENDMODE_MOD);
	SDL_RenderCopy(Renderer, gradient_texture, &gradient_src, NULL);
	SDL_SetRenderTarget(Renderer, NULL);

	SDL_RenderCopy(Renderer, heal2_Texture, NULL, &pos);
	SDL_RenderCopy(Renderer, line3_texture, NULL, &line3_texture_dst);
	sprintf(buffer, "%d", counter);
	temp_Surface = TTF_RenderText_Blended(Font, buffer, color);
	number_texture=SDL_CreateTextureFromSurface(Renderer,temp_Surface);
	SDL_RenderCopy(Renderer, number_texture, NULL, &number_texture_dst);
	SDL_QueryTexture(number_texture, NULL, NULL, &w, &h);
	number_texture_dst.w=w;
	number_texture_dst.h=h;

	counter++;
	if(counter > 999)
		counter = 0;

	gradient_src.x++;
	if (gradient_src.x > 374)
		gradient_src.x=0;

	SDL_RenderPresent(Renderer);

}

SDL_FreeSurface(temp_Surface);

SDL_DestroyTexture(gradient_texture);
SDL_DestroyTexture(heal_Texture);
SDL_DestroyTexture(heal2_Texture);
SDL_DestroyTexture(line1_texture);
SDL_DestroyTexture(line2_texture);
SDL_DestroyTexture(line3_texture);
SDL_DestroyTexture(number_texture);

SDL_DestroyRenderer(Renderer);
SDL_DestroyWindow(Window);
TTF_CloseFont(Font);

TTF_Quit();
SDL_Quit();

return EXIT_SUCCESS;

}


