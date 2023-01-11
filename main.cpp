#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include <stdio.h>
#include <time.h>
#include <MMSystem.h>
#include <iostream>
using namespace std;

void display();
void reshape(int,int);
void timer(int);
float angle = 0.0;
float x_position = 0.0;
float y_position = 0.0;
float z_position = 0.0;
int state = 1; //1 y3ny right -1 y3ny left
void init()
{
    glClearColor(0.2,0.3,0.4,1.0); //red green blue alpha
    glEnable(GL_DEPTH_TEST);
}
void texture (void){

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);


}
void keyboard(unsigned char Key, int x, int y)
{
    switch(Key){
    case 'd' : y_position++;
    break;

    case 'a' : y_position--;
    break;


    }
}
void OnMouseClick(int button , int state, int x , int y){
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
    z_position--;
   }

}


int main(int argc,char**argv)
{
   glutInit(&argc,argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
   glutInitWindowPosition(200,0); //position
   glutInitWindowSize(500,500); //size
   glutCreateWindow("16101256");
   //sndPlaySound("F:\\cgraphics\\F:\\cgraphics\\3D Project Computer Graphics\\bestmusic.wav",SND_ASYNC|SND_LOOP);
   //PlaySound(TEXT("bestmusic.wav"),NULL , SND_SYNC);
   glutMouseFunc (OnMouseClick);
   glutKeyboardFunc(keyboard);
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutTimerFunc(0,timer,0);
   init();
   texture(); // Lighting and textures
   glutMainLoop();
}


void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //the flag to clear the frame buffer
    glLoadIdentity(); //to reset any coordinates

    glTranslatef(0.0,y_position,-8.0);
    glRotatef(angle , 1.0 , 0.0 , 0.0 );//angle & x
    glRotatef(angle , 0.0 , 1.0 , 0.0 );//angle & y
    glRotatef(angle , 0.0 , 0.0 , 1.0 );//angle & z

    glBegin(GL_QUADS);

    //front
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    //back
    glColor3f(0.0,1.0,0.0);
    glVertex3f(1.0,1.0,-1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,1.0,-1.0);
    //right
    glColor3f(0.0,0.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);
    glVertex3f(1.0,1.0,-1.0);
    //left
    glColor3f(1.0,1.0,0.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(-1.0,1.0,1.0);
    //top
    glColor3f(0.0,1.0,1.0);
    glVertex3f(-1.0,1.0,-1.0);
    glVertex3f(-1.0,1.0,1.0);
    glVertex3f(1.0,1.0,1.0);
    glVertex3f(1.0,1.0,-1.0);
    //bottom
    glColor3f(1.0,0.0,1.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,1.0);
    glVertex3f(1.0,-1.0,-1.0);

    glEnd();

    glLoadIdentity();
    glTranslatef(3.5, -2.0, x_position);  // Move left and into the screen
    glRotatef(angle , 1.0 , 0.0 , 0.0 );//Rotate on x
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles

    // Front
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f( 0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    // Right
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Back
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    // Left
    glColor3f(1.0,0.0,0.0);       // Red
    glVertex3f( 0.0, 1.0, 0.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0, 1.0);
    glEnd();


    glLoadIdentity();
    glTranslatef(3.5, -2.0, z_position);  // Move left and into the screen
    glRotatef(angle , 1.0 , 0.0 , 0.0 );//Rotate on x
    glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles

    // Front
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f( 0.0, 1.0, 0.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    // Right
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Back
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(0.0, 1.0, 0.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);

    // Left
    glColor3f(1.0,0.0,0.0);       // Red
    glVertex3f( 0.0, 1.0, 0.0);
    glVertex3f(-1.0,-1.0,-1.0);
    glVertex3f(-1.0,-1.0, 1.0);
    glEnd();

    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(-3, -1.0,x_position);
    glRotatef(angle , 0.0 , 1.0 , 0.0 );//Rotate on y
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads

    glColor3f(0.0, 1.0, 0.0);     // Green
    glVertex3f( 1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0,  1.0);
    glVertex3f( 1.0, 1.0,  1.0);

      // Bottom face (y = -1.0f)
    glColor3f(1.0, 0.5, 0.0);     // Orange
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

      // Front face  (z = 1.0f)
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);

      // Back face (z = -1.0f)
    glColor3f(1.0, 1.0, 0.0);     // Yellow
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    // Left face (x = -1.0f)
    glColor3f(0.0, 0.0, 1.0);     // Blue
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);

    // Right face (x = 1.0f)
    glColor3f(1.0, 0.0, 1.0);     // Magenta
    glVertex3f(1.0,  1.0, -1.0);
    glVertex3f(1.0,  1.0,  1.0);
    glVertex3f(1.0, -1.0,  1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();

    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(-3.8, -1.0,-18);
    glRotatef(angle , 0.0 , 1.0 , 0.0 );//Rotate on y
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads

    glColor3f(0.0, 1.0, 0.0);     // Green
    glVertex3f( 1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0,  1.0);
    glVertex3f( 1.0, 1.0,  1.0);

      // Bottom face (y = -1.0f)
    glColor3f(1.0, 0.5, 0.0);     // Orange
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

      // Front face  (z = 1.0f)
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);

      // Back face (z = -1.0f)
    glColor3f(1.0, 1.0, 0.0);     // Yellow
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    // Left face (x = -1.0f)
    glColor3f(0.0, 0.0, 1.0);     // Blue
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);

    // Right face (x = 1.0f)
    glColor3f(1.0, 0.0, 1.0);     // Magenta
    glVertex3f(1.0,  1.0, -1.0);
    glVertex3f(1.0,  1.0,  1.0);
    glVertex3f(1.0, -1.0,  1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();


    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(2.8, -2.0,-16);
    glRotatef(angle , 0.0 , 1.0 , 0.0 );//Rotate on y
    glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads

    glColor3f(0.0, 1.0, 0.0);     // Green
    glVertex3f( 1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0,  1.0);
    glVertex3f( 1.0, 1.0,  1.0);

      // Bottom face (y = -1.0f)
    glColor3f(1.0, 0.5, 0.0);     // Orange
    glVertex3f( 1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0,  1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f( 1.0, -1.0, -1.0);

      // Front face  (z = 1.0f)
    glColor3f(1.0, 0.0, 0.0);     // Red
    glVertex3f(-1.0,  1.0,  1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0,  1.0);

      // Back face (z = -1.0f)
    glColor3f(1.0, 1.0, 0.0);     // Yellow
    glVertex3f( 1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0,  1.0, -1.0);
    glVertex3f( 1.0,  1.0, -1.0);

    // Left face (x = -1.0f)
    glColor3f(0.0, 0.0, 1.0);     // Blue
    glVertex3f( 1.0,  1.0, 1.0);
    glVertex3f(-1.0,  1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f( 1.0, -1.0, 1.0);

    // Right face (x = 1.0f)
    glColor3f(1.0, 0.0, 1.0);     // Magenta
    glVertex3f(1.0,  1.0, -1.0);
    glVertex3f(1.0,  1.0,  1.0);
    glVertex3f(1.0, -1.0,  1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();

    glutSwapBuffers();

}

void reshape(int w,int h)
{
    glViewport(0,0,(GLsizei)w,(GLsizei)h); //view port
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60 , 1 , 2.0 , 50.0);// field of view , expect ratio , Z near , Z far
    glMatrixMode(GL_MODELVIEW);
}
void timer(int)
{
  glutPostRedisplay();
  glutTimerFunc(1000/60,timer,0);

  angle+=1.0;
  if(angle>360.0)
    angle=angle-360.0;

  switch(state)
  {
  case 1 :
    if(x_position<-5)
        x_position+=0.10;
    else
        state = -1;
    break;
  case -1 :
    if(x_position>-15)
        x_position-=0.10;
    else
        state=1;
    break;

  }

}
