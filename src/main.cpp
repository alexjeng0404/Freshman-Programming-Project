#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include <windows.h>
#include "LButton.h"
#include "player_tool.h"

//Button constants

const int TOTAL_SCENE = 6;
const int TOTAL_BUTTONS = 10;
bool nextstate = false;
static int gamestate = 1;

//Key press surfaces constants

LButton gButtons[TOTAL_BUTTONS];

//determine which picture is going to show
void preset(SDL_Renderer* &gRenderer,bool render,bool render0)
{
	SDL_RenderCopy( gRenderer, menu, NULL, NULL );
	if (render==true)
	{
		SDL_Rect renderQuad1 = { 287, 485, 360, 136};
		SDL_RenderCopyEx( gRenderer, icon1 , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render0==true)
	{
		SDL_Rect renderQuad1 = { 770, 545, 60, 60};
		SDL_RenderCopyEx( gRenderer, icon2 , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
}
void choose1(SDL_Renderer* &gRenderer,bool render1,bool render2,bool render3,bool render4)
{
	SDL_RenderCopy( gRenderer, choose, NULL, NULL );
	if (render1==true)
	{
		SDL_Rect renderQuad1 = { 17, 2, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[0][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render2==true)
	{
		SDL_Rect renderQuad1 = { 21, 190, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[1][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render3==true)
	{
		SDL_Rect renderQuad1 = { 18, 397, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[2][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render4==true)
	{
		SDL_Rect renderQuad1 = { 14, 600, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[3][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
}
void choose2(SDL_Renderer* &gRenderer,bool render5,bool render6,bool render7,bool render8)
{
	SDL_RenderCopy( gRenderer, choose, NULL, NULL );
	if (render5==true)
	{
		SDL_Rect renderQuad1 = { 495, 3, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[0][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render6==true)
	{
		SDL_Rect renderQuad1 = { 495, 193, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[1][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render7==true)
	{
		SDL_Rect renderQuad1 = { 495, 400, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[2][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
	if (render8==true)
	{
		SDL_Rect renderQuad1 = { 490, 600, 150, 150};
		SDL_RenderCopyEx( gRenderer, picture[3][0] , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
	}
}
void startbattle(SDL_Renderer* &gRenderer)
{
	SDL_Rect renderQuad1 = { 350, 220, 300, 300};
	SDL_RenderCopyEx( gRenderer, strbattle , NULL,&renderQuad1,0.0, NULL, SDL_FLIP_NONE);
}
void battlefield(SDL_Renderer* &gRenderer)
{
	SDL_RenderCopy( gRenderer, battle, NULL, NULL );
}
void over1(SDL_Renderer* &gRenderer)
{
	SDL_Rect rect1,rect2;
	rect1 = {(int)SCREEN_WIDTH/3,(int)SCREEN_HEIGHT/3,350,100};
	SDL_RenderCopyEx( gRenderer, win[0], NULL, &rect1 ,0.0, NULL, SDL_FLIP_NONE );
	rect2 = {(int)SCREEN_WIDTH/3,(int)SCREEN_HEIGHT/2,350,100};
	SDL_RenderCopyEx( gRenderer, enter, NULL, &rect2,0.0, NULL, SDL_FLIP_NONE );
}
void over2(SDL_Renderer* &gRenderer)
{
	SDL_Rect rect1,rect2;
	rect1 = {(int)SCREEN_WIDTH/3,(int)SCREEN_HEIGHT/3,350,100};
	SDL_RenderCopyEx( gRenderer, win[1], NULL, &rect1 ,0.0, NULL, SDL_FLIP_NONE );
	rect2 = {(int)SCREEN_WIDTH/3,(int)SCREEN_HEIGHT/2,350,100};
	SDL_RenderCopyEx( gRenderer, enter, NULL, &rect2,0.0, NULL, SDL_FLIP_NONE );	
}
void render_picture(SDL_Renderer* &gRenderer,player &p,int type)
{
	//Set rendering space and render to screen
	int x = p.get_mPosX();
	int y = p.get_mPosY();
	int WIDTH = p.character_WIDTH;
	int HEIGHT = p.character_HEIGHT;
	SDL_Rect renderQuad1 = { x, y, WIDTH, HEIGHT};
	SDL_Rect renderQuad2 = { x-WIDTH-10, y, WIDTH, HEIGHT};
	SDL_Rect renderQuad3 = { x+WIDTH+10, y, WIDTH, HEIGHT};
	if (p.live==true)
		SDL_RenderCopyEx( gRenderer, picture[p.index[0]][p.index[1]], NULL, &renderQuad1 ,0.0, NULL, p.flip );
	if (p.live==false)
	{
		if (type==1)
		{
			SDL_RenderCopyEx( gRenderer, picture[p.index[0]][p.index[1]], NULL, &renderQuad2 ,270, NULL, SDL_FLIP_NONE);
			nextstate = true;
			gamestate = 7; 
		}	
		else if (type==2)
		{
			SDL_RenderCopyEx( gRenderer, picture[p.index[0]][p.index[1]], NULL, &renderQuad3 ,270, NULL, SDL_FLIP_NONE);
			nextstate = true; 
			gamestate = 6;
		}	
	}
}
void render_blood(SDL_Renderer* &gRenderer,player &p,int type)
{
	int ori_blood;
	
	switch(p.index[0])
	{
		case 0:ori_blood = 200; break;
		case 1:ori_blood = 200; break;
		case 2:ori_blood = 170; break;
		case 3:ori_blood = 210; break;
	}
	SDL_Rect  rect1,rect2;
	if (type==1)
	{
		rect1 = {50,10,ori_blood,30};
		if (p.hp>0)
			rect2 = {50,10,p.hp/2,30};
		else
			rect2 = {50,10,0,30};
	}
	if (type==2)
	{
		rect1 = {750,10,ori_blood,30};
		if (p.hp>0)
			rect2 = {750,10,p.hp/2,30};
		else
			rect2 = {750,10,0,30};
	}
	//Render green outlined quad (original 
    SDL_SetRenderDrawColor( gRenderer, 0x00, 0xFF, 0x00, 0xFF );        
    SDL_RenderDrawRect( gRenderer, &rect1 );
    
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x00, 0x00, 0xFF );
    SDL_RenderFillRect( gRenderer, &rect2 );
    
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
}
void guide(SDL_Renderer* &gRenderer)
{
	SDL_RenderCopy( gRenderer, intro, NULL, NULL );
}
void get_prop(player&p,Tool &item,Uint32 time)
{
	
	if (item.data->get_exists() == true)
	{
		if( (item.mPosX - p.mPosX <= p.character_WIDTH + 10 && (p.mPosX  - item.mPosX ) <= item.character_WIDTH + 10 && (p.mPosY-item.mPosY) <= item.character_HEIGHT+10 && (item.mPosY - p.mPosY <= p.character_HEIGHT+10) ))// collision
		{	
			p.starttime = time;
			item.tool_num -= 1;
			switch(item.data->get_index())
			{
				case 1:
					{
						item.sqrt_10(p);
						break;
					}
				case 2:
					{
						item.starbuck(p);
						break;
					}
				case 3:
					{
						item.big_note(p);
						break;
					}
				case 4:
					{
						item.withdraw(p);
						break;
					}
			}	
		}
	}
}

int main( int argc, char* args[] )
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media 
	
		gButtons[0].setPosition(300,500); //start button
		gButtons[1].setPosition(27,12); //player1 character1 icon
		gButtons[2].setPosition(31,203);//player1 character2 icon
		gButtons[3].setPosition(31,410);//player1 character3 icon
		gButtons[4].setPosition(24,610);//pllayer1 character4 icon
		gButtons[5].setPosition(510,16);
		gButtons[6].setPosition(516,203);
		gButtons[7].setPosition(505,410);
		gButtons[8].setPosition(500,610);
		gButtons[9].setPosition(785,560);//guide button
		gButtons[10].setPosition(0,0);//return button
		
		player *p1, *p2;
		Tool *item;
		p1 = new player;
		p2 = new player;
		item = new Tool[2];
		
		if( !loadMedia() )
		{
			
			printf( "Failed to load media!\n" );
		}
		else
		{	
		
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;
			
			
			bool render = false;
			bool render0 = false;
			bool render1 = false;
			bool render2 = false;
			bool render3 = false;
			bool render4 = false;
			bool render5 = false;
			bool render6 = false;
			bool render7 = false;
			bool render8 = false;
			
			//Play the music
			Mix_PlayMusic( background, -1 );
		
			//While application is running
			while( !quit )
			{
				int count = 0;
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					//User presses a key
					switch (gamestate)
					{
						case 0:
							gButtons[10].handleEventBack( &e );
							if (gButtons[10].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN)
							{
								gamestate = 1;
								break;
							}
					}
					switch (gamestate)
					{
						case 1: 
							gButtons[0].handleEventStart( &e );
							gButtons[9].handleEventGuide( &e );
							if (gButtons[0].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OVER_MOTION) 
							{
								Mix_PlayChannel( -1, mouse_over, 0 );
								render = true;
							}
							if (gButtons[0].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) 
							{
								Mix_PlayChannel( -1, button, 0 );
								gamestate = 2;
								render = false;
							}
							if (gButtons[0].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT) 
							{
								render = false;
							}
							if (gButtons[9].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OVER_MOTION) 
							{
								Mix_PlayChannel( -1, mouse_over, 0 );
								render0 = true;
							}
							if (gButtons[9].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) 
							{
								Mix_PlayChannel( -1, button, 0 );
								gamestate = 0;
								render0 = false;
							}
							if (gButtons[9].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT) 
							{
								render0 = false;
							}
							break;
						case 2:	
							for (int i=1;i<=4;i++)
							{
								gButtons[i].handleEventCharacter( &e );
								if (gButtons[i].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OVER_MOTION) 
								{
									Mix_PlayChannel( -1, mouse_over, 0 );
									render = true;
									switch(i)
									{
										case 1:render1 = true;break;
										case 2:render2 = true;break;
										case 3:render3 = true;break;
										case 4:render4 = true;break;
									}
								}
								if (gButtons[i].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) 
								{
									Mix_PlayChannel( -1, button, 0 );
									render = false;
									switch(i)
									{
										case 1:p1->set(0,400,100,100,150,350,11,SDL_FLIP_NONE); render1 = false;break;  //balance
										case 2:p1->set(1,400,135,80,150,350,10,SDL_FLIP_NONE); render2 = false;break;   //attack
										case 3:p1->set(2,340,80,80,150,350,15,SDL_FLIP_NONE); render3 = false;break;   //agile
										case 4:p1->set(3,420,90,140,150,350,5,SDL_FLIP_NONE); render4 = false;break;   //defence
									}
									gamestate = 3;
								}
								if (gButtons[i].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT) 
								{
									switch(i)
									{
										case 1:render1 = false;break;
										case 2:render2 = false;break;
										case 3:render3 = false;break;
										case 4:render4 = false;break;
									}
								}							
							}
							break;
						case 3: 
							for (int i=5;i<=8;i++)
							{
								gButtons[i].handleEventCharacter( &e );
								if (gButtons[i].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OVER_MOTION) 
								{
									Mix_PlayChannel( -1, mouse_over, 0 );
									switch(i)
									{
										case 5:render5 = true;break;
										case 6:render6 = true;break;
										case 7:render7 = true;break;
										case 8:render8 = true;break;
									}
								}
								if (gButtons[i].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_DOWN) 
								{		
									Mix_PlayChannel( -1, button, 0 );							
									switch(i)
									{
										case 5:p2->set(0,400,100,100,750,350,11,SDL_FLIP_HORIZONTAL);render5 = false;break;
										case 6:p2->set(1,400,135,80,750,350,10,SDL_FLIP_HORIZONTAL);render6 = false;break;
										case 7:p2->set(2,340,80,80,750,350,15,SDL_FLIP_HORIZONTAL);render7 = false;break;
										case 8:p2->set(3,420,90,140,750,350,5,SDL_FLIP_HORIZONTAL);render8 = false;break;
									}
									gamestate = 4;
								}
								if (gButtons[i].getmyCurrentSprite() == BUTTON_SPRITE_MOUSE_OUT) 
								{
									
									switch(i)
									{
										case 5:render5 = false;break;
										case 6:render6 = false;break;
										case 7:render7 = false;break;
										case 8:render8 = false;break;
									}
								}
							}
							break;
						case 4: gamestate = 5; Sleep(1000);break;
						case 5: 
							{
								p1->handleEvent( 1,e );
								p2->handleEvent( 2,e );
								p1->collision(*p2);
								p2->collision(*p1);
								p1->be_attacked(*p2);
								p2->be_attacked(*p1);
								get_prop(*p1,item[0],SDL_GetTicks());
								get_prop(*p2,item[0],SDL_GetTicks());
								get_prop(*p1,item[1],SDL_GetTicks());
								get_prop(*p2,item[1],SDL_GetTicks());
								item[0].set_exists( item[0].collision(item[1]) );
								if (item[0].get_exists() == false){
									item[0].set_index(0);	
								} 
								item[1].set_exists(item[1].collision(item[0]));
								if (item[1].get_exists() == false){
									item[1].set_index(0);	
								} 
								break;
							}
						case 6:
							{
								if (e.key.type==SDL_KEYDOWN)
								{
									switch(e.key.keysym.sym)
										case SDLK_RETURN:
											return 0;
								}
							}
						case 7:
							{
								if (e.key.type==SDL_KEYDOWN)
								{
									switch(e.key.keysym.sym)
										case SDLK_RETURN:
											return 0;
								}
							}
					}
				}
				
				
				//Clear screen
				SDL_RenderClear( gRenderer );
				switch(gamestate)
				{
					case 0: guide(gRenderer); break;
					case 1: 
						{
							preset(gRenderer,render,render0);
							break;
						}
					case 2: choose1(gRenderer,render1,render2,render3,render4); break;
					case 3: choose2(gRenderer,render5,render6,render7,render8); break;
					case 4: startbattle(gRenderer); break;
					case 5: 
					{
						battlefield(gRenderer);
						render_picture(gRenderer,*p1,1);
						render_picture(gRenderer,*p2,2);
						render_blood(gRenderer,*p1,1);
						render_blood(gRenderer,*p2,2);
						tool_appear( rand(),SDL_GetTicks(),item[0] );
						tool_appear( rand(),SDL_GetTicks(),item[1] );
						break;
					}  
					case 6: 
						{
							Mix_HaltMusic();
							Mix_PlayChannel( -1, winn, 0 );
							if (nextstate==true)
							{
								delete p1;
								delete p2;
								delete []item;
								nextstate = false;
								break;
							}
							over1(gRenderer);							
							break;
						}				
					case 7:
						{
							Mix_HaltMusic();
							Mix_PlayChannel( -1, winn, 0 );
							if (nextstate==true)
							{
								delete p1;
								delete p2;
								delete []item;
								nextstate = false;
								
								break;
							}
							over2(gRenderer);
							break;
						}						
				}

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}
	//Free resources and close SDL
	close();
	return 0;
}


