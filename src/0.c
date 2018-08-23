//BEGIN HEAD
//BEGIN DESCRIPTION

/* This is a small SDL2 Demo
 */

/* DEFINED PROGRESS GOALS
 * Render Text solid, shaded, blended, utf8-blended
 * and TTF_RenderGlyph_Blended
 * 
 *
 */
//END   DESCRIPTION

//BEGIN INCLUDES
//system headers
#include <math.h>
//local headers
#include "helper.h"
//END   INCLUDES

//BEGIN CPP DEFINITIONS
#define WHITE 	255,255,255,255
#define BLACK 	0,0,0,255
#define RED   	255,0,0,255
#define BLUE   	67,91,112,255
#define WW 	550
#define WH 	(WW/16)*12
//END   CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
int ww=WW;
int wh=WH;

//BEGIN TIMING
//END TIMING

//BEGIN VISIBLES
SDL_Surface    *temp_surface	= NULL;

SDL_Texture    *logo		= NULL;
SDL_Rect 	logo_dst;

TTF_Font       *font		= NULL;

SDL_Texture    *link1		= NULL;
SDL_Rect 	link1_dst;

SDL_Texture    *link1_tp	= NULL;
SDL_Rect 	link1_tp_dst;

SDL_Texture    *link2		= NULL;
SDL_Rect 	link2_dst;

SDL_Texture    *link2_tp	= NULL;
SDL_Rect 	link2_tp_dst;

SDL_Texture    *text1		= NULL;
SDL_Rect 	text1_dst;
//END 	VISIBLES

//END   GLOBALS

//BEGIN FUNCTION PROTOTYPES
void assets_in	(void);
void assets_out	(void);
//END	FUNCTION PROTOTYPES

//END 	HEAD

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

//BEGIN INIT
init();
assets_in();

//BEGIN WINDOW
SDL_SetWindowPosition(Window,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED);
SDL_SetWindowSize(Window,ww,wh);
SDL_SetWindowTitle(Window, "SDL_ttf 2.0");
SDL_ShowWindow(Window);
//END WINDOW
SDL_SetRenderDrawColor(Renderer, WHITE);
SDL_RenderClear(Renderer);

SDL_RenderCopy(Renderer, logo, NULL, &logo_dst);
SDL_RenderCopy(Renderer, link1, NULL, &link1_dst);
SDL_RenderCopy(Renderer, link1_tp, NULL, &link1_tp_dst);
SDL_RenderCopy(Renderer, link2_tp, NULL, &link2_tp_dst);
SDL_RenderCopy(Renderer, link2, NULL, &link2_dst);
SDL_RenderCopy(Renderer, text1, NULL, &text1_dst);
SDL_RenderPresent(Renderer);
SDL_Event event;
int running = 1;
//END   INIT

//BEGIN MAIN LOOP
while(running){
	//BEGIN EVENT LOOP
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running = 0;
		}
		if(event.type == SDL_KEYDOWN ){
			switch(event.key.keysym.sym ){
				case SDLK_ESCAPE:
				case SDLK_q:
					running = 0;
					break;
				default:
					break;
			}
		}
	}
	//END   EVENT LOOP
	//BEGIN RENDERING
	// NO UPDATE
	//END   RENDERING
}
//END   MAIN LOOP

assets_out();
exit_();
return EXIT_SUCCESS;

}
//END   MAIN FUNCTION

//BEGIN FUNCTIONS
void assets_in(void)
{
	//BEGIN LOGO
	temp_surface = IMG_Load("./assets/gfx/logo.png");
	logo = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(logo, NULL, NULL, &logo_dst.w, &logo_dst.h);
	logo_dst.x=ww/2-logo_dst.w/2;
	logo_dst.y=wh-logo_dst.h*1.5;
	//END 	LOGO
	
	//BEGIN Solid
	font=TTF_OpenFont("./assets/fonts/NimbusSanL-Regu.ttf", 36);
	SDL_Color color={BLUE};
	temp_surface=TTF_RenderText_Solid(font,"TTF_RenderText_Solid",color);
	link1 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link1, NULL, NULL, &link1_dst.w, &link1_dst.h);
	link1_dst.x=ww/2-link1_dst.w/2;
	link1_dst.y=4;
	//END 	Solid
	
	//BEGIN Shaded
	SDL_Color bgcolor={199,207,213,255};
	temp_surface=TTF_RenderText_Shaded(font,"TTF_RenderText_Shaded",color, bgcolor);
	link1_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link1_tp, NULL, NULL, &link1_tp_dst.w, &link1_tp_dst.h);
	link1_tp_dst.x=ww/2-link1_tp_dst.w/2;
	link1_tp_dst.y=90;
	//END 	Shaded
	
	//BEGIN Blended
	temp_surface=TTF_RenderText_Blended(font,"TTF_RenderText_Blended",color);
	link2_tp= SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link2_tp, NULL, NULL, &link2_tp_dst.w, &link2_tp_dst.h);
	link2_tp_dst.x= ww/2-link2_tp_dst.w/2;
	link2_tp_dst.y= 170;
	//END 	Blended
	
	//BEGIN TEXT1
	font=TTF_OpenFont("assets/fonts/wts11.ttf", 36);
	temp_surface=TTF_RenderUTF8_Blended(font,"不孝有三",color);
	
	text1 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(text1, NULL, NULL, &text1_dst.w, &text1_dst.h);
	text1_dst.x=ww-text1_dst.w-10;
	text1_dst.y=wh-text1_dst.h-10;
	//END 	TEXT1
	
	//BEGIN Glyph_Blended
	font=TTF_OpenFont("./assets/fonts/fontawesome-webfont.ttf", 100);
	temp_surface=TTF_RenderGlyph_Blended(font, 0xf035 , color);
	link2 = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(link2, NULL, NULL, &link2_dst.w, &link2_dst.h);
	link2_dst.x=10;
	link2_dst.y=wh-link2_dst.h-10;
	//END 	Glyph_Blended
	
	SDL_FreeSurface(temp_surface);

}

void assets_out(void)
{
	SDL_DestroyTexture(logo);
	SDL_DestroyTexture(link1);
	SDL_DestroyTexture(link1_tp);
	SDL_DestroyTexture(link2);
	SDL_DestroyTexture(link2_tp);
	SDL_DestroyTexture(text1);
	TTF_CloseFont(font);
}
//END   FUNCTIONS
