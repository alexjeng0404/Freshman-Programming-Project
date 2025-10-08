#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include<iostream>

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 750;

enum figure{
	pic,  //select charcter pic = 0 
	def,  //def = 1
	atk,  //atk = 2 
 	jump, //jump = 3
	def_be_atk, //def be atk = 4
	be_atk, // be atk = 5
	knockdown, //knockdown = 6
	stand_1,  //stand_1 = 7
	stand_2,  //stand_2 = 8
	forward_1,  //forward_1 = 9
	forward_2, //forward_2 = 10 
	backward_1, //backward_1 = 11
	backward_2  //backward_2 = 12
};

SDL_Texture* picture[4][11];
SDL_Texture* menu;
SDL_Texture* choose;
SDL_Texture* strbattle;
SDL_Texture* battle;
SDL_Texture* win[2];
SDL_Texture* intro;
SDL_Texture* icon1;
SDL_Texture* icon2;
SDL_Texture* prop[4];
SDL_Texture* enter; 

//The music that will be played
Mix_Music *background = NULL;


//The sound effects that will be used
Mix_Chunk *mouse_over = NULL;
Mix_Chunk *button = NULL;
Mix_Chunk *atkk = NULL;
Mix_Chunk *atk_def = NULL;
Mix_Chunk *winn = NULL;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads individual image as texture
SDL_Texture* loadTexture( std::string path );

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

SDL_Texture* gTexture = NULL; 

bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				
				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia()
{
	const	char *str[4][11];
	
	str[0][pic]="img/character1.png";
	str[0][def]="img/character1_def.png";
	str[0][atk]="img/character1_atk.png";
	str[0][jump]="img/character1_jump.png";
	str[0][def_be_atk]="img/character1_def_be_atk.png";
	str[0][be_atk]="img/character1_be_atk.png";
	str[0][knockdown]="img/character1_knockdown.png";
	str[0][stand_1]="img/character1_stand_1.png";
	str[0][stand_2]="img/character1_stand_2.png";
	str[0][forward_1]="img/character1_forward_1.png";
	str[0][forward_2]="img/character1_forward_2.png";
	
	str[1][pic]="img/character2.png";
	str[1][def]="img/character2_def.png";
	str[1][atk]="img/character2_atk.png";
	str[1][jump]="img/character2_jump.png";
	str[1][def_be_atk]="img/character2_def_be_atk.png";
	str[1][be_atk]="img/character2_be_atk.png";
	str[1][knockdown]="img/character2_knockdown.png";
	str[1][stand_1]="img/character2_stand_1.png";
	str[1][stand_2]="img/character2_stand_2.png";
	str[1][forward_1]="img/character2_forward_1.png";
	str[1][forward_2]="img/character2_forward_2.png";
	
	str[2][pic]="img/character3.png";
	str[2][def]="img/character3_def.png";
	str[2][atk]="img/character3_atk.png";
	str[2][jump]="img/character3_jump.png";
	str[2][def_be_atk]="img/character3_def_be_atk.png";
	str[2][be_atk]="img/character3_be_atk.png";
	str[2][knockdown]="img/character3_knockdown.png";
	str[2][stand_1]="img/character3_stand_1.png";
	str[2][stand_2]="img/character3_stand_2.png";
	str[2][forward_1]="img/character3_forward_1.png";
	str[2][forward_2]="img/character3_forward_2.png";
	
	
	
	str[3][pic]="img/character4.png";
	str[3][def]="img/character4_def.png";
	str[3][atk]="img/character4_atk.png";
	str[3][jump]="img/character4_jump.png";
	str[3][def_be_atk]="img/character4_def_be_atk.png";
	str[3][be_atk]="img/character4_be_atk.png";
	str[3][knockdown]="img/character4_knockdown.png";
	str[3][stand_1]="img/character4_stand_1.png";
	str[3][stand_2]="img/character4_stand_2.png";
	str[3][forward_1]="img/character4_forward_1.png";
	str[3][forward_2]="img/character4_forward_2.png";
	//Loading success flag
	bool success = true;

	//Load character's texture

	for(int i=0;i<4;i++){
		for(int j=0;j<11;j++){
			picture[i][j] = loadTexture( str[i][j] );
			if( picture[i][j] == NULL )
			{
				printf( "Failed to load texture image!\n" );
				success = false;
			}
		}
	}
		
	//Load background texture
	icon1 = loadTexture("img/icon1.png");
	{
		if( icon1 == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	icon2 = loadTexture("img/icon2.png");
	{
		if( icon2 == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	menu = loadTexture("img/menu.png");
	{
		if( menu == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	intro = loadTexture("img/intro.png");
	{
		if( intro == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	choose = loadTexture("img/choose.png");
	{
		if( choose == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	strbattle = loadTexture("img/strbattle.png");
	{
		if( strbattle == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	battle = loadTexture("img/battle.png");
	{
		if( battle == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	prop[0] = loadTexture("img/sqrt10.png");
	{
		if( prop[0] == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	prop[1] = loadTexture("img/starbuck.png");
	{
		if( prop[1] == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	prop[2] = loadTexture("img/big_note.png");
	{
		if( prop[2] == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	prop[3] = loadTexture("img/withdraw.png");
	{
		if( prop[3] == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	win[0] = loadTexture("img/P1_win.png");
	{
		if( win[0] == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	win[1] = loadTexture("img/P2_win.png");
	{
		if( win[1] == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	enter = loadTexture("img/enter.png");
	{
		if( enter == NULL )
		{
			printf( "Failed to load texture image!\n" );
			success = false;
		}
	}
	//Load music
	background = Mix_LoadMUS( "voi/background.wav" );
	if( background == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	winn = Mix_LoadWAV( "voi/win.wav" );
	if( win == NULL )
	{
		printf( "Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	//Load sound effects
	mouse_over = Mix_LoadWAV( "voi/mouse_over.wav" );
	if( mouse_over == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	button = Mix_LoadWAV( "voi/button.wav" );
	if( button == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	atkk = Mix_LoadWAV( "voi/atk.wav" );
	if( atk == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	atk_def = Mix_LoadWAV( "voi/atk_def.wav" );
	if( atk_def == NULL )
	{
		printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	
	return success;
}

void close()
{
	//Free loaded image
	SDL_DestroyTexture( gTexture );
	gTexture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;
	
	
	//Free the sound effects
	Mix_FreeChunk( winn );
	Mix_FreeChunk( atkk );
	Mix_FreeChunk( atk_def );
	Mix_FreeChunk( button );
	Mix_FreeChunk( mouse_over );
	winn = NULL;
	atkk = NULL;
	atk_def = NULL;
	button = NULL;
	mouse_over = NULL;
	
	//Free the music
	Mix_FreeMusic( background );
	background = NULL;
	

	//Quit SDL subsystems
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture* loadTexture( std::string path )
{
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL )
	{
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
	}
	else
	{
		SDL_SetColorKey( loadedSurface, SDL_TRUE, SDL_MapRGB( loadedSurface->format, 0xFC,0xFC,0xFC ));
		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( gRenderer, loadedSurface );
		if( newTexture == NULL )
		{
			printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	return newTexture;
}


