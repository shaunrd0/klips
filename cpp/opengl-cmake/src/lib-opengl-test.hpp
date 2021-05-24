
#ifndef LIB_OPENGL_TEST_HPP
#define LIB_OPENGL_TEST_HPP

#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>

void runMainLoop( int val );
/*
Pre Condition:
 -Initialized freeGLUT
Post Condition:
 -Calls the main loop functions and sets itself to be called back in 1000 / SCREEN_FPS milliseconds
Side Effects:
 -Sets glutTimerFunc
*/

bool initGL();
void update();
void render();

void handleKeys( unsigned char key, int x, int y );

#endif // LIB_OPENGL_TEST_HPP
