//BEGIN INCLUDES
//sys headers
#include <math.h>
#include <stdlib.h>
#include <string.h>

//local headers
#include "helper.h"
//END	INCLUDES

//BEGIN CPP DEFINITIONS
#define DIM_W 1920/2
#define DIM_H 1080/3

#define CENTER_X DIM_W/2
#define CENTER_Y DIM_H/2
//END	CPP DEFINITIONS

//BEGIN DATASTRUCTURES
//END	DATASTRUCTURES

//BEGIN GLOBALS
//END	GLOBALS

//BEGIN FUNCTION PROTOTYPES
//END	FUNCTION PROTOTYPES

/* DEFINED PROGRESS GOALS
 * 
 */

//BEGIN MAIN FUNCTION
int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

init();

TTF_Font *font;
int height, width;
SDL_Color text_color;
char *string = "Sinus Font Scroller";
int size;
char letter[2];

char *font_file;

unsigned int i, dir=1;
double angle = 0;
int xpos, first_x;
int ypos;

font_file = "assets/fonts/brick.ttf";
size = 25;

if((font = TTF_OpenFont(font_file, size)) == NULL) {
	SDL_Log("TTF_OpenFont error: %s", TTF_GetError());
}

text_color.r = 255;
text_color.g = 175;
text_color.b = 0;

TTF_SizeText(font, string, &width, &height);

ypos = DIM_H;
xpos = CENTER_X - width/2;
first_x = xpos;

unsigned int char_count;
char_count=strlen(string);

SDL_Texture *texture[char_count];
SDL_Rect destrect[char_count];
SDL_Surface *temp_surface = NULL;

// Create textentry structs for every letter
for (i=0; i < char_count; i++){
	// convert char to String
	letter[0] = string[i];
	letter[1] = '\0';
	temp_surface=TTF_RenderText_Blended(font, letter , text_color);

	// Creating textures for every letter
	texture[i] = SDL_CreateTextureFromSurface(Renderer, temp_surface);
	SDL_QueryTexture(texture[i], NULL, NULL, &destrect[i].w, &destrect[i].h);	
}
SDL_FreeSurface(temp_surface);

SDL_SetWindowSize(Window, DIM_W, DIM_H);
SDL_SetWindowTitle(Window, "Sinus Scroller");
SDL_ShowWindow(Window);

SDL_SetRenderDrawColor(Renderer, 111, 111, 111, 255);
SDL_Event event;
int running = 1;

while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT){
			running = 0;
		}
	}

SDL_RenderClear(Renderer);
	
for (i=0; i < char_count; i++) {
	if (i==0)
		xpos = first_x;
	destrect[i].x = xpos;
	xpos += destrect[i].w;
	ypos = (CENTER_Y - height/2) + sin(M_PI/180 * (angle + i*15)) * height;
	destrect[i].y = ypos;
	SDL_RenderCopy(Renderer, texture[i], NULL, &destrect[i]);
}
angle += 10;
if (xpos > DIM_W)
	dir = -1;
if (first_x < 0)
	dir = 1;
first_x += dir*3;

SDL_RenderPresent(Renderer);
}

//BEGIN CLEANUP
TTF_CloseFont(font);

for (i=0; i < char_count; i++){
	SDL_DestroyTexture(texture[i]);
}

exit_();
//END	CLEANUP

return EXIT_SUCCESS;

}	
//END	MAIN FUNCTION

//BEGIN FUNCTIONS
//END	FUNCTIONS
