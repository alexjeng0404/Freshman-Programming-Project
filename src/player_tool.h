#include "load_picture_sound.h"
#include<cmath>
class player;
class Tool;

class character
{
	
    public:
    	
		//Maximum axis velocity of the dot
		int character_VEL;
				
		//the picture is flipped or not
		SDL_RendererFlip flip;
		
		//Initializes the variables
		character():mVelX(0),mVelY(0),def_or_not(false){
			index = new int [2];
			index[0] = 0;
			index[1] = 8;
		}
		~character(){delete [] index ;}
		//Takes key presses and adjusts the dot's velocity
		void handleEvent( int index , SDL_Event& e );   //different player
				
		virtual int get_mPosX() {return mPosX;}
		virtual int get_mPosY() {return mPosY;}
		int get_mVelX() {return mVelX;}
		int get_mVelY() {return mVelY;} 
		void set_mVelX( int v) { mVelX = v;}
		void set_mVelY( int v) { mVelY = v;} 
		void set_character_v(int v) {	character_VEL = v;}
		
		void set_index2(int a)
		{
			index[1] = a;
		}
		
    protected:
		//The X and Y offsets of the dot
		
		int mPosX, mPosY;
		
		//The velocity of the dot  
		int mVelX, mVelY;
		
		//the index of the picture
		int *index;
		
		//whether the defence button is pressed
		bool def_or_not;
};

class Data{
	private:
		bool exists;
		Uint32 initial_time;
		int *index;
	public:
		Data():exists(false),initial_time(0) {
			index = new int;
			*index = 0;
		}
		void set_exists(bool t){ exists=t;}
		void set_time(Uint32 t){ initial_time = t;}
		void set_index(int i){ *index = i;}
		Uint32 get_time(){return initial_time;}
		bool get_exists(){return exists;	}
		int get_index(){ return *index;}
};



class Tool:public character{
	private:
		Data *data; 
		
		const Uint32 duration;
		const int character_WIDTH;
		const int character_HEIGHT;
	public:
		static int tool_num;
		friend void render_tool(SDL_Renderer* &gRenderer,Tool &item);
		friend void get_prop(player&p,Tool &item,Uint32 time);
		friend void tool_appear( long long int rtime, Uint32 tick_time,Tool &item );
		
		Tool(): character_HEIGHT(80),character_WIDTH(80),duration(5)
		{	
			data = new Data; 
			//index = new int;
			//*index = 0; 
			//initial_time = 0;
			//exists = false;
		}
		~Tool(){delete data;}	
		bool get_exists(){
			return data->get_exists();
		}
		void set_pos(int x,int y){ mPosX = x; mPosY = y;}
		void set_index(int i){ *index = i;}
		void set_exists(bool t){ data->set_exists(t);}
		int get_index(){ return *index;	}
		bool collision(Tool &item);
		void get_num()  {
			std::cout<<tool_num<<std::endl;
		}
		void appear(Uint32);
		void if_vanish(Uint32);
		void sqrt_10( player&p );	
		void starbuck(player&p);
		void big_note(player &p);
		void withdraw(player &p);
};
int Tool::tool_num = 0;

class player: public character{
	public:
		friend void render_blood(SDL_Renderer* &gRenderer,player &p,int type);
		friend void get_prop(player&p,Tool &item,Uint32);
		friend void Tool::sqrt_10(player &p);
		friend void Tool::starbuck(player &p);
		friend void Tool::big_note(player &p);
		friend void Tool::withdraw(player &p);
		friend void render_picture(SDL_Renderer* &gRenderer,player &p,int type);
		const int character_WIDTH;
		const int character_HEIGHT;
		bool live;
		player():live(false),character(),character_WIDTH(50),character_HEIGHT(120),starttime(0){
		}
		~player(){}
		void set(int type,int blood,int attack,int defence,int xpos,int ypos,int speed,SDL_RendererFlip F)
		{
			live = true;
			index[0] = type;
			hp = blood;
			in_hp = blood;
			atk = attack;
			in_atk = attack;
			def = defence;
			in_def = defence;
			mPosX = xpos;
			mPosY = ypos;
			character_VEL = speed;			
			flip = F;
		}
		void collision(player &p);  //move and collide
		void be_attacked(player &p); //checked the player is hit
		int get_VEL(){return character_VEL;}
		void set_atk( int a) { atk = a;}
		void set_def(int a) {def = a;}
		void set_hp( int a){ hp = a;}
		void set_VEL( int a){ character_VEL = a;}
		double get_in_hp(){ return in_hp;}
		int get_in_atk(){ return in_atk;}
		int get_in_def(){ return in_def;}
	private:
		static int player_num;
		double hp;
		int atk, def;
		int in_atk,in_def;
		double in_hp;
		Uint32 starttime;	
		
};
int player::player_num = 0;
void character::handleEvent( int id , SDL_Event& e )
{
    
    if( id == 1)
	{
		//If a key was pressed
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_w: mVelY -= character_VEL; index[1] =10; break;
	            case SDLK_s: mVelY += character_VEL; index[1] =10; break;
	            case SDLK_a: mVelX -= character_VEL; index[1] =10; flip = SDL_FLIP_HORIZONTAL;break;
	            case SDLK_d: mVelX += character_VEL; index[1] =10; flip = SDL_FLIP_NONE;break;
	        	case SDLK_f: index[1] = 2; break;   // press f to attack
	        	case SDLK_g: index[1] = 1; def_or_not = true; break;//press g to defence
	            
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
	            case SDLK_a: mVelX += character_VEL; index[1] =9;break;
	            case SDLK_d: mVelX -= character_VEL; index[1] =9; break;
	            case SDLK_f: index[1] = 8; break;
	        	case SDLK_g: index[1] = 8; def_or_not = false; break;
	        }
	        
	    }
	}
	if( id == 2)
	{
		//If a key was pressed
		if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_UP: mVelY -= character_VEL;   index[1] =10;break;
	            case SDLK_DOWN: mVelY += character_VEL; index[1] =10;break;
	            case SDLK_LEFT: mVelX -= character_VEL; index[1] =10; flip = SDL_FLIP_HORIZONTAL;break;
	            case SDLK_RIGHT: mVelX += character_VEL;index[1] =10; flip = SDL_FLIP_NONE; break;
	            case SDLK_PERIOD: index[1] = 2; break; //press . to attack
	            case SDLK_SLASH: index[1] = 1; def_or_not = true; break;// press / to defence
	        }
	    }
	    //If a key was released
	    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
	    {
	        //Adjust the velocity
	        switch( e.key.keysym.sym )
	        {
	            case SDLK_UP: mVelY += character_VEL;break;
	            case SDLK_DOWN: mVelY -= character_VEL;break;
	            case SDLK_LEFT: mVelX += character_VEL; index[1]=9; break;
	            case SDLK_RIGHT: mVelX -= character_VEL; index[1] =9; break;
	            case SDLK_PERIOD: index[1] = 8; break;
	            case SDLK_SLASH: index[1] = 8; def_or_not = false; break;
	        }
	    }
	}
}

void Tool::appear(Uint32 starttime){
		data->set_time(starttime);
		data->set_exists(true);
}

void Tool::if_vanish(Uint32 endtime){
	if ( endtime - data->get_time()> 5000 ){
			data->set_exists(false);
			tool_num -= 1;
			data->set_time(0);
			data->set_index(0);
	}
}

void Tool::sqrt_10(player & p){
	if( p.live == true){
		double nhp = (p.hp/p.in_hp)* 100.0;
		int new_hp = 10*sqrt(nhp)*p.in_hp/100;
		p.set_hp( new_hp );
		p.set_atk ( 10*sqrt( p.atk));
		p.set_def ( 10*sqrt(p.def ));
	}
	data -> set_index(0);
	data -> set_exists(false) ;
}

void Tool::starbuck (player & p){
	if( p.live == true){
		if( p.hp + 0.2*p.in_hp <= p.in_hp)
			p.set_hp ( p.hp + 0.2*p.in_hp) ; 
		else
			p.set_hp(p.in_hp);
	}
	data -> set_index(0);
	data -> set_exists(false) ;
}

void Tool::big_note(player &p){
	if( p.live == true){
		//p.set_atk( p.atk + 10);
		//p.set_def(p.def + 10) ;
		p.atk+=10;
		p.def+=10;
	}
	data -> set_index(0);
	data -> set_exists(false) ;
}

void Tool::withdraw(player &p){
	p.set_hp(0);
	p.live = false;
	data -> set_index(0);
	data -> set_exists(false) ;
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
			if (p.index[1]==2)
			{
				
				if (def_or_not == true)
				{
					Mix_PlayChannel( -1, atk_def, 0 );
					hp -= 0.2*p.atk*( 1.0 - def/200.0)*0.1;
					index[1] = 4;
				}	
				else
				{
					Mix_PlayChannel( -1, atkk, 0 );
					hp -= p.atk *( 1.0 - def/200.0)*0.1 ;
					index[1] = 5;
				}	
				if (hp<=0)
				{
					live = false;
					index[1] = 6;
				}	
			}
		}
		if (p.flip==SDL_FLIP_NONE&&p.get_mPosX()<get_mPosX())
		{
			if (p.index[1]==2)
			{
				
				if (def_or_not == true)
				{
					Mix_PlayChannel( -1, atk_def, 0 );
					hp -= 0.2*p.atk*( 1.0 - def/200.0)*0.1;
					index[1] = 4;
				}	
				else
				{
					Mix_PlayChannel( -1, atkk, 0 );
					hp -= p.atk*( 1.0 - def/200.0)*0.1 ;
					index[1] = 5;
				}	
				if (hp<=0)
				{
					live = false;
					index[1] = 6;
				}
			}
		}
	}
}



void render_tool(SDL_Renderer* &gRenderer,Tool &item)
{	
	//Set rendering space and render to screen
	int x = item.mPosX;
	int y = item.mPosY;
	int HEIGHT = item.character_HEIGHT;
	int WIDTH = item.character_WIDTH;
	SDL_Rect renderQuad1 = { x, y, WIDTH, HEIGHT};
	SDL_Rect renderQuad2 = { x-WIDTH, y, WIDTH, HEIGHT};
	SDL_Rect renderQuad3 = { x+WIDTH, y, WIDTH, HEIGHT};
	if (item.data->get_exists() ==true)
		SDL_RenderCopyEx( gRenderer, prop[item.data->get_index()-1], NULL, &renderQuad1 ,0.0, NULL, SDL_FLIP_NONE );
}

void tool_appear( long long int rtime, Uint32 tick_time,Tool &item ){
	if( item.data->get_index() == 0)
	{
		switch( (int)floor( rtime % 5) )
		{
			case 1:{
				item.data->set_index(1);
				//item.set_index(5);
				item.appear(tick_time);
				item.set_pos( rtime%(800)+50, rtime%(500) + 100 );
				item.tool_num +=1;
				break;
			}
			case 2:{
				item.data->set_index(2);
				//item.set_index(5);
				item.appear(tick_time);
				item.set_pos( rtime%(800)+50, rtime%(500) + 100);
				item.tool_num +=1;
				break;
			}
			case 3:{
				item.data->set_index(3);
				//item.set_index(5);
				item.appear(tick_time);
				item.set_pos( rtime%(800)+50, rtime%(500) + 100 );
				item.tool_num +=1;
				break;
			}
			case 4:{
				item.data->set_index(4);
				//item.set_index(5);
				item.appear(tick_time);
				item.set_pos( rtime%(800)+50, rtime%(500) + 100);
				item.tool_num +=1;
				break;
			}
		}
	}
	else
	{
		if( item.data->get_exists() == true )
		{
			render_tool(gRenderer,item);
			item.if_vanish(tick_time);
		}
	}	
}



bool Tool::collision(Tool &item)
{
	int item_mPosX = item.get_mPosX();
	int item_mPosY = item.get_mPosY();

	//Move the character left or right
    //If the character went too far to the left or right
    if( ( mPosX < 0 ) || ( mPosX + character_WIDTH > SCREEN_WIDTH ) )
    {
        //Move back
        mPosX += character_WIDTH;
        return true;
    }

    //If the dot went too far up or down
    else if( ( mPosY < character_HEIGHT ) || ( mPosY + character_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= character_HEIGHT;
    	return true;
	}
	
	else if( abs(mPosX-item_mPosX) <= character_WIDTH && abs(mPosY-item_mPosY) <= character_HEIGHT) //if they are going to touch
    {
        //Move back
        return false;
    }
    else return true;
}

