/*#############################################################################
## Requires freeglut3-dev to be installed with your package manager          ##
## To build an executable: `g++ test-gl.cpp -w -lGL -lGLU -lglut -o test`    ##
##                                                                           ##
## Testing building OpenGL projects with source code from lazyfoo -          ##
## https://lazyfoo.net/tutorials/OpenGL/                                     ##
##############################################################################
## test-gl.cpp
*/

#include <lib-opengl-test.hpp>

#include <GL/freeglut.h>

#include <cstdio>

//Screen constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;

//Color modes
const int COLOR_MODE_CYAN = 0;
const int COLOR_MODE_MULTI = 1;

int main( int argc, char* args[] )
{
  //Initialize FreeGLUT
  glutInit( &argc, args );

  //Create OpenGL 2.1 context
  glutInitContextVersion( 2, 1 );

  //Create Double Buffered Window
  glutInitDisplayMode( GLUT_DOUBLE );
  glutInitWindowSize( SCREEN_WIDTH, SCREEN_HEIGHT );
  glutCreateWindow( "OpenGL" );

  //Do post window/context creation initialization
  if( !initGL() )
  {
    printf( "Unable to initialize graphics library!\n" );
    return 1;
  }

  //Set keyboard handler
  glutKeyboardFunc( handleKeys );

  //Set rendering function
  glutDisplayFunc( render );

  //Set main loop
  glutTimerFunc( 1000 / SCREEN_FPS, runMainLoop, 0 );

  //Start GLUT main loop
  glutMainLoop();

  return 0;
}

