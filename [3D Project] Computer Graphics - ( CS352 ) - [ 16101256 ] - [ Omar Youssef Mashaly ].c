#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <mmsystem.h>
#include <gl/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
using namespace std;
//#include <irrKlang.h>

#define UP 1
#define Down 2
#define LEFT 3
#define RIGHT 4



// Status Variables
GLint   lvl      = 1;
GLint   points = 0;
GLint   size  = 0;
GLbyte  gameOver = true;
GLbyte  EnableLight = true;



// Snake Variables
GLint   bodyPos[2][100] = {{}};
GLint   _x       = 5;
GLint   _z       = 10;
GLint   _oldX[2] = {};
GLint   _oldZ[2] = {};
GLbyte  direction  = 0;



// Food Variables
GLint   _bx      = 0;
GLint   _bz      = 0;

// Screen variables
GLint   _w       = 800;
GLint   _h       = 550;
GLint   _Giw     = 0;
GLint   _Gih     = 0;
GLint   _Gfw     = 150;
GLint   _Gfh     = 150;

//Variables for the Camera Angle
static GLfloat view_rotx=45.0F ;
static GLfloat view_roty=0.0F ;
static GLfloat view_rotz=0.0F ;

static GLfloat headRotation=90.0F ;
static GLfloat zoom=-300.0f;// This is the camera zoom for the perception of the FOV

//Configure the lightning, this is the texture method
void initLight()
{
    //Add ambient light
    GLfloat ambientColor[] = {0.3f, 0.4f, 0.8f, 1.0f};
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);

    //Add positioned light
    GLfloat lightColor0[] = {0.5f, 0.5f, 0.5f, 1.0f};
    GLfloat lightPos0[] = {4.0f, 0.0f, 8.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColor0);
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

    //Add directed light
    GLfloat lightColor1[] = {0.5f, 0.2f, 0.2f, 1.0f};
    //Coming from the direction (-1, 0.5, 0.5)
    GLfloat lightPos1[] = {-1.0f, 0.5f, 0.5f, 0.0f};
    glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColor1);
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
}
//initialize the first configurations
void Initialize(void)
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f, 0.0f, 0.0f, 1.0f); //Change the background
        if(EnableLight){ //Enable this when the program starts to make it more realistic
        glEnable(GL_COLOR_MATERIAL); //Enable color
        glEnable(GL_LIGHTING); //Enable lighting
        glEnable(GL_LIGHT0); //Enable light #0
        glEnable(GL_LIGHT1); //Enable light #1
        glEnable(GL_NORMALIZE); //Automatically normalize normals
    }
}
//Configure window resize
void resize (int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (double)w / (double)h, 1, 800.0);
}
void Write(char *string){//Write string on the screen
    while(*string)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *string++);
}
//This Function will rotate the object according to the Angles
void ManipulateViewAngle() {
    glRotatef(view_rotx,1.0,0.0,0.0);//Rotate Arround X axis
    glRotatef(view_roty,0.0,1.0,0.0);//Rotate Arround Y axis
    glRotatef(view_rotz,0.0,0.0,1.0);//Rotate Arround Z axis
}
//This Function will reset the snake size and location...
void Reset(){
    _x = 5;
    _z = 2;
    direction = 0;
    lvl = 1;
    points = 0;
    size  = 0;
    gameOver = false;
    view_rotx=45.0F ;
    view_roty=0.0F ;
    view_rotz=0.0F ;
    headRotation=90.0F ;

}

//Display a welcome screen
void WelcomeScreen(){
    char tmp_str[40];

    glColor3f(0, 0, 0);
    glRasterPos2f(0, 50);
    Write("Welcome to EJA Snake Game");


    glColor3f(0, 0, 0);
    glRasterPos2f(0, 40);
    Write("To Start Playing please press Enter Key or Spacebar");

    glColor3f(0, 0, 0);
    glRasterPos2f(0, 30);
    Write("Remember to play it in FULL SCREEN FOR A BETTER EXPERIENCE: Please press f");

    glColor3f(0, 0, 0);
    glRasterPos2f(0, 20);
    Write("To move the snake, use arrow keys!");

    glColor3f(0, 0, 0);
    glRasterPos2f(0, 10);
    Write("To Exit the game press Escape Key");

    glColor3f(0, 0, 0);
    glRasterPos2f(0, -10);
    Write("Tips:-");
    glColor3f(0, 0, 0);
    glRasterPos2f(0, -20);
    Write("Don't eat yourself!");
    glColor3f(0, 0, 0);
    glRasterPos2f(0, -30);
    Write("Press Enter or Spacebar while playing to Restart!");


    glLoadIdentity();                  // Reset the model-view matrix
    glTranslatef(2.5f, -1.0f, -6.0f);  // Move left and into the screen

      glBegin(GL_TRIANGLES);           // Begin drawing the pyramid with 4 triangles
      // Front
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);

      // Right
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(1.0f, -1.0f, 1.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);

      // Back
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(0.0f, 1.0f, 0.0f);
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f(1.0f, -1.0f, -1.0f);
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-1.0f, -1.0f, -1.0f);

      // Left
      glColor3f(1.0f,0.0f,0.0f);       // Red
      glVertex3f( 0.0f, 1.0f, 0.0f);
      glColor3f(0.0f,0.0f,1.0f);       // Blue
      glVertex3f(-1.0f,-1.0f,-1.0f);
      glColor3f(0.0f,1.0f,0.0f);       // Green
      glVertex3f(-1.0f,-1.0f, 1.0f);
      glEnd();

    glLoadIdentity();                  // Reset the model-view matrix
   glTranslatef(-2.5f, -1.0f, -6.0f);
   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1.0f, 0.0f);     // Green
      glVertex3f( 1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f, -1.0f);
      glVertex3f(-1.0f, 1.0f,  1.0f);
      glVertex3f( 1.0f, 1.0f,  1.0f);

      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( 1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f( 1.0f, -1.0f, -1.0f);

      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f(-1.0f,  1.0f,  1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f,  1.0f);

      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( 1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f, -1.0f, -1.0f);
      glVertex3f(-1.0f,  1.0f, -1.0f);
      glVertex3f( 1.0f,  1.0f, -1.0f);

      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f( 1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f,  1.0f, 1.0f);
      glVertex3f(-1.0f, -1.0f, 1.0f);
      glVertex3f( 1.0f, -1.0f, 1.0f);

      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.0f, 1.0f);     // Magenta
      glVertex3f(1.0f,  1.0f, -1.0f);
      glVertex3f(1.0f,  1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f,  1.0f);
      glVertex3f(1.0f, -1.0f, -1.0f);
      glEnd();  // End of drawing color-cube
}

void DrawSnake(){
    int  i;

    //Drawing the head & the plane
    glPushMatrix();
    ManipulateViewAngle();
        //This will draw the plane that the snake will run on.
        glPushMatrix();
        glColor3f(1, 1, 0.1);
        glTranslatef(75.0, -16.0, 75.0);
        glScalef(155,5.0,155);
        glutSolidCube(1);
        glPopMatrix();
    //Here we will draw the Head of the snake
    glColor3f(1,0,0);//Color it red
    glTranslatef(_x,-10.0,_z);//Give it the location according to _x & _z
    glScalef(0.5,0.5,0.5);
    glutSolidSphere(10,20,20);//Draw the head as a sphere a litle bit bigger than the body spheres
    glRotatef(headRotation, 0.0, 1.0, 0.0);
    glColor3f(0.7,0.8,0.2);//The Mouth part as green
    glTranslatef(0,0.0,6.0);
    glScalef(0.8,1.0,1.0);
    glutSolidCone(10,10,20,20);
    glColor3f(0,0,0);// The eyes
    glTranslatef(-4.0,10.0,0.0);
    glScalef(0.3,0.3,0.3);
    glutSolidSphere(10,20,20);
    glTranslatef(26.0,0.0,0.0);
    glutSolidSphere(10,20,20);
    glPopMatrix();

    //Drawing the body
    for(i=0; i<size; i++){//Loop throw the size and draw spheres representing the body
        glPushMatrix();
        ManipulateViewAngle();
        glTranslatef(bodyPos[0][i],-10.0,bodyPos[1][i]);//this will locate the spheres depending on the body position of the last body part
        glColor3f(0.7,0.8,0.2);//Color as the mouth
        glScalef(0.5,0.5,0.5);
        glutSolidSphere(7,20,20);
        glPopMatrix();
    }
}
void DrawFood()
{
    //Draw the Sphere representing the Food for the snake
    glPushMatrix();
    ManipulateViewAngle();
    glTranslatef(_bx,-9.0,_bz);
    glColor3f(0.4, 0.2, 1.0);
    glScalef(0.55,0.55,0.55);
    glutSolidTorus(2,7,20,20);
    glPopMatrix();
}

void GameStatus(){

    char tmp_str[40];

    // Print the status of the game on the screen
    glColor3f(0, 0, 0);
    glRasterPos2f(5, 50);// to position the Writing depending on x and y values

    sprintf(tmp_str, "Level: %d Points: %d", lvl, points);// This is used to write the string pointed to by format to buffer.
    Write(tmp_str);
}
int RandomNumber(int high, int low)
{
    return (rand() % (high-low))+low;
}
void newFood(){
    time_t seconds;// To get the time of the host pc
    time(&seconds);
    srand((unsigned int) seconds);// This is to create a different random number on each program run
    _bx = RandomNumber(_Gfw-_Giw, _Giw+10);
    _bz = RandomNumber(_Gfh-_Gih, _Gih+10);
}
//This Function Will Check for Collision
bool collision(){
    int i;

    for(i=0; i<size; i++){
        if((bodyPos[0][i] == _x && bodyPos[1][i] == _z) ||
        ((bodyPos[0][i] >= _x) && (bodyPos[0][i] <= _x + 5) && (bodyPos[1][i] >= _z) && (bodyPos[1][i] <= _z + 5)) ||
        ((bodyPos[0][i] <= _x) && (bodyPos[0][i] >= _x - 5) && (bodyPos[1][i] <= _z) && (bodyPos[1][i] >= _z - 5)) ||
        ((bodyPos[0][i] <= _x) && (bodyPos[0][i] >= _x - 5) && (bodyPos[1][i] >= _z) && (bodyPos[1][i] <= _z + 5)) ||
        ((bodyPos[0][i] >= _x) && (bodyPos[0][i] <= _x + 5) && (bodyPos[1][i] <= _z) && (bodyPos[1][i] >= _z - 5)))
        return true;
    }
    return false;
}
//This Function will move the snake according to the directions
//Taken from the Keyboard keys
void Run(int value){
    int i;

    _oldX[1] = _x;
    _oldZ[1] = _z;
    switch(direction){
      case RIGHT:
          headRotation =90;
          _x += 6;
          if(_x > _Gfw-2) _x = _Giw-1;//This will check if the snake is going into the border so it will appear on the other side
          break;
      case LEFT:
          headRotation =-90;
          _x -= 6;
         if(_x < 0) _x = _Gfw-2;//This will check if the snake is going into the border so it will appear on the other side
          break;
      case UP:
          headRotation =0;
          _z += 6;
          if(_z > _Gfh-2) _z = _Gih-1;//This will check if the snake is going into the border so it will appear on the other side
          break;
      case Down:
          headRotation =180;
          _z -= 6;
          if(_z < 2) _z = _Gfh-2;//This will check if the snake is going into the border so it will appear on the other side
          break;
    }

    //Checks for Collisoin if yes Game Over
    if(collision()) gameOver = true;

    //Checks if the snake ate the food (check the X and Y)
    // If yes it will increase the points & the size of the snake & create a new food
    if((_x == _bx && _z == _bz) ||
    ((_x >= _bx) && (_x <= _bx + 4) && (_z >= _bz) && (_z <= _bz + 4)) ||
    ((_x <= _bx) && (_x >= _bx - 4) && (_z <= _bz) && (_z >= _bz - 4)) ||
    ((_x <= _bx) && (_x >= _bx - 4) && (_z >= _bz) && (_z <= _bz + 4)) ||
    ((_x >= _bx) && (_x <= _bx + 4) && (_z <= _bz) && (_z >= _bz - 4))){
        points++;
        if(points < 100) size++;
        if(points%5 == 0 && lvl < 15) lvl++;
        newFood();
    }

    for(i = 0; i<size; i++){// Save the positions of the body parts
        _oldX[0] = _oldX[1];
        _oldZ[0] = _oldZ[1];
        _oldX[1] = bodyPos[0][i];
        _oldZ[1] = bodyPos[1][i];
        bodyPos[0][i] = _oldX[0];
        bodyPos[1][i] = _oldZ[0];
    }

    //Set the Timer
    glutTimerFunc(130-lvl*4, Run, 0);
}



void Display(void){//Draw Function
    // Clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    if(EnableLight) initLight();

    glTranslatef (-60.0, 40.0, zoom);
    //Check if the value of the Flag "Game Over is not True it will continue the game"
    if(!gameOver){
        GameStatus();
        DrawFood();
        DrawSnake();
    }
    else
        WelcomeScreen();


    // Updates the screen
    glutPostRedisplay();
    glutSwapBuffers();
}
void Special(int key, int x, int y){
    switch(key){
    case GLUT_KEY_RIGHT     :
        if(direction != LEFT)
            direction = RIGHT;
        break;
    case GLUT_KEY_LEFT      :
        if(direction != RIGHT)
            direction = LEFT;
        break;
    case GLUT_KEY_UP        :
        if(direction != UP)
            direction = Down;
        break;
    case GLUT_KEY_DOWN      :
        if(direction != Down)
            direction = UP;
        break;
    }
}
void keyboard (unsigned char key, int x, int y)
{
    switch (key) {

      case 13: Reset() ;
          glutPostRedisplay();
          break;
      case 32: Reset() ;
          glutPostRedisplay();
          break;
      //ESC to Exit
      case 27:
          exit(0);
          break;
      case 'f':
        glutFullScreen();
        break;
      default:
          break;
    }
}
int main(void){
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(_w,_h);
    glutInitWindowPosition(80,80);
    glutCreateWindow("16101256");
    glutSpecialFunc(Special);
    glutKeyboardFunc(keyboard);
    glutDisplayFunc(Display);
    glutReshapeFunc(resize);

    newFood();
    Run(0);
    //sndPlaySound("C:\\Users\\HP\\Desktop\\New folder\\12th Project Game\\bestmusic.wav",SND_ASYNC|SND_LOOP);

    Initialize();
    glutMainLoop();
}

