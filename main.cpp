//
//  main.cpp
//  SDL_tutorial
//
//  Edited by Swayam Bansal on 5/31/23.
//

#include <iostream>
#include <SDL2/SDL.h>
#include <stdio.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Starts up SDL and creates a window
bool init();

// Loads the media
bool loadMedia();

// Frees media and shutdown SDL
void close();

//The window we'll be rendering to
SDL_Window* window = NULL;

//The surface contained by the window
SDL_Surface* screenSurface = NULL;

//The image we will load and show on the screen
SDL_Surface* HelloWorld = NULL;

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
    
    // Loading the image on the gui
    const char *image_path = "/Applications/PROJECTS_C++/SDL_tutorial/Images/Hello_world_image.bmp";
    HelloWorld = SDL_LoadBMP(image_path);
    
    if( HelloWorld == NULL){
        printf( "\nUnable to load image %s! SDL Error: %s\n", image_path , SDL_GetError() );
        success = false;
    }
    
    
    return success;
}

void close(){
    //Deallocate surface
    SDL_FreeSurface( HelloWorld );
    HelloWorld = NULL;
    
    //Destroy window
    SDL_DestroyWindow( window );
    window = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
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
                           }

                           //Apply the image
                           SDL_BlitSurface( HelloWorld, NULL, screenSurface, NULL );
                       
                           //Update the surface
                           SDL_UpdateWindowSurface( window );
                   }
            }
        }
    
   // free up the resources and quit SDL
    close();
    
    return 0;
}

