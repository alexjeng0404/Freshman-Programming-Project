#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "load_picture.h"
class character
{
	friend void get_prop(player&p,Tool &item,Uint32 SDL_GetTicks());
    public:
    	
		//The dimensions of the dot
		const int character_WIDTH;
		const int character_HEIGHT;

		//Maximum axis velocity of the dot
		int character_VEL;  
		
		//the picture is flipped or not
		SDL_RendererFlip flip;
		
		//Initializes the variables
		character():character_WIDTH(50),character_HEIGHT(120),mVelX(0),mVelY(0),index2(8),def_or_not(false){
		}
		
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( int index , SDL_Event& e );   //different player
				
		int get_mPosX() {return mPosX;}
		int get_mPosY() {return mPosY;}
		int get_mVelX() {return mVelX;}
		int get_mVelY() {return mVelY;} 
		
		void set_index2(int a)
		{
			index2 = a;
		}
		
		int get_index1()
		{
			return index1;
		}
		
		int get_index2()
		{
			return index2;
		}
    protected:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
		
		//the index of the picture
		int index1;
		int index2;

		//whether the defence button is pressed
		bool def_or_not;
};

class player: public character{
	friend void render_blood(SDL_Renderer* &gRenderer,player &p,int type);
	public:
		bool live;
		player():live(false){
		}
		set(int type,int blood,int attack,int defence,int xpos,int ypos,int speed,SDL_RendererFlip F)
		{
			live = true;
			index1 = type;
			hp = blood;
			in_hp = blood;
			atk = attack;
			in_atk = attack;
			def = defence;
			in_def = defence;
			mPosX = xpos;
			mPosY = ypos;
			character_VEL = speed;
			in_spd = speed;			
			flip = F;
		}
		void collision(player &p);  //move and collide
		void be_attacked(player &p); //checked the player is hit
		int get_atk() {return atk;}
		int get_def() {return def;}
		int get_hp(){return hp;}
	private:
		double hp;
		int spd, atk, def;
		int in_spd,in_atk,in_def;
		double in_hp;	
};

void character::handleEvent( int index , SDL_Event& e )
{
    
    if( index == 1)
	{
		//If a key was pressed
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_w: mVelY -= character_VEL; break;
	            case SDLK_s: mVelY += character_VEL; break;
	            case SDLK_a: mVelX -= character_VEL; index2 =10; flip = SDL_FLIP_HORIZONTAL; break;
	            case SDLK_d: mVelX += character_VEL; index2 =10; flip = SDL_FLIP_NONE; break;
	        	case SDLK_f: index2 = 2; break;   // press j to attack
	        	case SDLK_g: index2 = 1; def_or_not = true; break;//press k to defence
	            
	        }
	    }
	    //If a key was released
	    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_w: mVelY += character_VEL; break;
	            case SDLK_s: mVelY -= character_VEL; break;
	            case SDLK_a: mVelX += character_VEL; index2 =9; break;
	            case SDLK_d: mVelX -= character_VEL; index2 =9; break;
	            case SDLK_f: index2 = 8; break;
	        	case SDLK_g: index2 = 8; def_or_not = false; break;
	        }
	    }
	}
	if( index == 2)
	{
		//If a key was pressed
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_UP: mVelY -= character_VEL;  break;
	            case SDLK_DOWN: mVelY += character_VEL;  break;
	            case SDLK_LEFT: mVelX -= character_VEL; index2 =10; flip = SDL_FLIP_HORIZONTAL;break;
	            case SDLK_RIGHT: mVelX += character_VEL; index2 =10; flip = SDL_FLIP_NONE; break;
	            case SDLK_PERIOD: index2 = 2; break; //press the keyboard 1 to attack
	            case SDLK_SLASH: index2 = 1; def_or_not = true; break;// press the keyboard 2 to defence
	        }
	    }
	    //If a key was released
	    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_UP: mVelY += character_VEL; break;
	            case SDLK_DOWN: mVelY -= character_VEL; break;
	            case SDLK_LEFT: mVelX += character_VEL; index2 =9; break;
	            case SDLK_RIGHT: mVelX -= character_VEL; index2 =9; break;
	            case SDLK_PERIOD: index2 = 8; break;
	            case SDLK_SLASH: index2 = 8; def_or_not = false; break;
	        }
	    }
	}
}

void player::collision(player &p)
{
	int p_mPosX = p.get_mPosX();
	int p_mPosY = p.get_mPosY();

	//Move the character left or right
    mPosX += mVelX;

    //If the character went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + character_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX -= mVelX;
    }
	
    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    if( ( mPosY < 50 ) || ( mPosY + character_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }
	
	if( abs(mPosX-p_mPosX) <= character_WIDTH-5 && abs(mPosY-p_mPosY) <= character_HEIGHT) //if they are going to touch
    {
        //Move back
        mPosX -= mVelX;
		mPosY -= mVelY;
    }
}

void player::be_attacked(player &p)
{
	int p_mPosX = p.get_mPosX();
	int p_mPosY = p.get_mPosY();
	if( abs(mPosX-p_mPosX) <= character_WIDTH+10 && abs(mPosY-p_mPosY) <= character_HEIGHT ) // be attacked by the other
	{	
		if (p.flip==SDL_FLIP_HORIZONTAL&&p.get_mPosX()>get_mPosX())
		{
			if (p.get_index2()==2)
			{
				
				if (def_or_not == true)
					hp -= 0.2*p.get_atk()*( 1.0 - def/200.0)*0.1;
				else
					hp -= p.get_atk()*( 1.0 - def/200.0)*0.1 ;
				if (hp<=0)
				{
					live = false;
					index2 = 6;
				}	
			}
		}
		if (p.flip==SDL_FLIP_NONE&&p.get_mPosX()<get_mPosX())
		{
			if (p.get_index2()==2)
			{
				
				if (def_or_not == true)
					hp -= 0.2*p.get_atk()*( 1.0 - def/200.0)*0.1;
				else
					hp -= p.get_atk()*( 1.0 - def/200.0)*0.1 ;
				if (hp<=0)
				{
					live = false;
					index2 = 6;
				}	
			}
		}
	}
}


