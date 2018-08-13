#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdlib.h>

SDL_Renderer *Renderer = NULL;

struct textentry
{
	SDL_Color 	 color;
	SDL_Color 	 out_color;
	TTF_Font        *font;
	char         	*string;
	SDL_Rect 	 srcr;
	SDL_Rect 	 dstr;
	SDL_Texture 	*tex;
};

void get_dbl_text_texture	(struct textentry *, int);

int main(int argc, char *argv[])
{

(void)argc;
(void)argv;

SDL_Init(SDL_INIT_VIDEO);
TTF_Init();
TTF_Font  *font;
font=TTF_OpenFont("assets/fonts/brick.ttf", 300);
SDL_Window   *window = SDL_CreateWindow("Outline and Mirror", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1400, 600, 0);

//BEGIN ICON
SDL_Surface *icon;
icon = SDL_LoadBMP("assets/gfx/SDL2.bmp");
SDL_SetWindowIcon(window, icon);
SDL_FreeSurface(icon);
//END 	ICON

Renderer = SDL_CreateRenderer(window, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

SDL_Color color = { 255, 175, 0, 255 };

//BEGIN TEXT
struct textentry menu_title;
menu_title.color=color;
menu_title.out_color.r=255;
menu_title.out_color.g=0;
menu_title.out_color.b=0;
menu_title.out_color.a=255;
menu_title.font=font;
menu_title.string = "Sahara";
get_dbl_text_texture(&menu_title, 1);
menu_title.dstr.x=40;
menu_title.dstr.y=40;
//END 	TEXT


SDL_RenderCopy(Renderer, menu_title.tex, NULL, &menu_title.dstr);
menu_title.dstr.y+=menu_title.dstr.h-100;
SDL_SetTextureAlphaMod(menu_title.tex,50);
SDL_RenderCopyEx(Renderer, menu_title.tex, NULL,  &menu_title.dstr, 180, 0, 1);
SDL_RenderPresent(Renderer);

SDL_Event event;
SDL_bool  running = SDL_TRUE;

while(running){
	while(SDL_PollEvent(&event)){
		if(event.type == SDL_QUIT)
			running = SDL_FALSE;
	}
	//No Update
}

if (menu_title.tex!=NULL)
	SDL_DestroyTexture(menu_title.tex);

TTF_CloseFont(font);
SDL_DestroyRenderer(Renderer);
SDL_DestroyWindow(window);
TTF_Quit();
SDL_Quit();
return EXIT_SUCCESS;

}

void get_dbl_text_texture(struct textentry *textentry, int os)
{
	if ((os <=0) || (os >= 4))
		os=1;

	SDL_Surface *solid_text_surface = NULL;
	solid_text_surface=TTF_RenderText_Blended(textentry->font, textentry->string , textentry->color);

	SDL_Surface *outline_text_surface = NULL;
	TTF_SetFontOutline(textentry->font,os);
	
	outline_text_surface=TTF_RenderText_Blended(textentry->font, textentry->string , textentry->out_color);

	//blit to solid surface
	SDL_BlitSurface(outline_text_surface, NULL, solid_text_surface, NULL);
	textentry->tex = SDL_CreateTextureFromSurface(Renderer,solid_text_surface );
	
	//free both surfaces since we have a texture now
	SDL_FreeSurface(solid_text_surface);
	SDL_FreeSurface(outline_text_surface);
	SDL_QueryTexture(textentry->tex, NULL, NULL, &textentry->dstr.w, &textentry->dstr.h);
	TTF_SetFontOutline(textentry->font,0);
}

