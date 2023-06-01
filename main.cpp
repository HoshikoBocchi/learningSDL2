//
//  main.cpp
//  SDL_tutorial
//
//  Edited by Swayam Bansal on 6/1/23.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1080;
const int SCREEN_HEIGHT = 720;

//The constraints for key events
enum KeyPressSurfaces{
    DEFAULT,    // DEFAULT = 0
    UP,         // UP = 1
    DOWN,       // DOWN = 2
    RIGHT,      // RIGHT = 3
    LEFT,       // LEFT = 4
    TOTAL       // TOTAL = 5
};

// Starts up SDL and creates a window
bool init();

// Loads the media
bool loadMedia();

// Frees media and shutdown SDL
void close();

//Loads individual image
SDL_Surface* loadSurface( std::string path );

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//The images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[ TOTAL ];

//Current displayed image
SDL_Surface* gCurrentSurface = NULL;

bool init(){
    // intizaliting the return var
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = false;
    }
    
    else
        {
            //Create window
            window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
            if( window == NULL )
            {
                printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
                success = false;
            }
            
            else{
                //Get window surface
                screenSurface = SDL_GetWindowSurface( window );
            }
        }
    
    return success;
}

bool loadMedia(){
    // Loading success flag
    bool success = true;
    
    // loading the default picture on the screen
    gKeyPressSurfaces[ DEFAULT ] = loadSurface("/Applications/PROJECTS_C++/SDL_tutorial/Images/miku_wave_hi.bmp");
    
    if(gKeyPressSurfaces[DEFAULT] == NULL){
        printf("\nUnable to load image! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    
    // loading the picture on the screen for UP key pressed
    gKeyPressSurfaces[ UP ] = loadSurface("/Applications/PROJECTS_C++/SDL_tutorial/Images/miku_jump.bmp");
    
    if(gKeyPressSurfaces[UP] == NULL){
        printf("\nUnable to load image! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    
    // loading the picture on the screen for DOWN key pressed
    gKeyPressSurfaces[ DOWN ] = loadSurface("/Applications/PROJECTS_C++/SDL_tutorial/Images/miku_sit.bmp");
    
    if(gKeyPressSurfaces[DOWN] == NULL){
        printf("\nUnable to load image! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    
    // loading the picture on the screen for LEFT key pressed
    gKeyPressSurfaces[ LEFT ] = loadSurface("/Applications/PROJECTS_C++/SDL_tutorial/Images/miku_left.bmp");
    
    if(gKeyPressSurfaces[LEFT] == NULL){
        printf("\nUnable to load image! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    
    // loading the picture on the screen for UP key pressed
    gKeyPressSurfaces[ RIGHT ] = loadSurface("/Applications/PROJECTS_C++/SDL_tutorial/Images/miku_right.bmp");
    
    if(gKeyPressSurfaces[RIGHT] == NULL){
        printf("\nUnable to load image! SDL Error %s\n", SDL_GetError());
        success = false;
    }
    
    return success;
}

void close(){
    //Deallocating surfaces
    for(int i = 0; i < TOTAL; i++){
        SDL_FreeSurface( gKeyPressSurfaces[i] );
        gKeyPressSurfaces[ i ] = NULL;
    }
    
    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
}

SDL_Surface* loadSurface( std::string path ){
    
    //load the image of the given specific path
    SDL_Surface *loadSurface = SDL_LoadBMP( path.c_str() );
    if( loadSurface == NULL ){
        printf("\nUnable to load the image %s!, SDL Error : %s\n", path.c_str() , SDL_GetError() );
    }
    
    return loadSurface;
}


int main( int argc, char* args[] )
{
    //Initialize SDL
    if( !init() )
    {
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    }
    
    else
        {
            //Load media
            if( !loadMedia() )
            {
                printf( "\nFailed to load media!\n" );
            }
            
            else
                   {
                       //Main loop flag
                       bool quit = false;

                       //Event handler
                       SDL_Event e;
                       
                       //set the current surface to default
                       gCurrentSurface = gKeyPressSurfaces[ DEFAULT ];

                       //While application is running
                       while( !quit )
                       {
                           //Handle events on queue
                           while( SDL_PollEvent( &e ) != 0 )
                           {
                               //User requests quit
                               if( e.type == SDL_QUIT )
                               {
                                   quit = true;
                               }
                               
                               else if( e.type == SDL_KEYDOWN )
                               {
                                   //Select surfaces based on key press
                                   switch( e.key.keysym.sym )
                                   {
                                       case SDLK_UP:
                                           gCurrentSurface = gKeyPressSurfaces[ UP ];
                                           break;
                                       
                                       case SDLK_DOWN:
                                           gCurrentSurface = gKeyPressSurfaces[ DOWN ];
                                           break;
                                           
                                       case SDLK_RIGHT:
                                           gCurrentSurface = gKeyPressSurfaces[ RIGHT ];
                                           break;
                                           
                                       case SDLK_LEFT:
                                           gCurrentSurface = gKeyPressSurfaces[ LEFT ];
                                           break;
                                       
                                       default:
                                           gCurrentSurface = gKeyPressSurfaces[ DEFAULT ];
                                           break;
                                   }
                               }
                           }

                           //Apply the image
                           SDL_BlitSurface( gCurrentSurface, NULL, screenSurface, NULL );
                       
                           //Update the surface
                           SDL_UpdateWindowSurface( window );
                   }
            }
        }
    
   // free up the resources and quit SDL
    close();
    
    return 0;
}

