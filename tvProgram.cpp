
/*********
CTIS164
----------
STUDENT : Mustafa Asrın Değirmenci
SECTION : 02
HOMEWORK:  01
----------
PROBLEMS: NO PROBLEM!!!
----------
ADDITIONAL FEATURES:
 --- Changing Vehicles (Rocket - UFO)
 --- Falling Stars
 --- Local Time  Digital Clock Work
 
*********/

#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <OpenGL/OpenGL.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>


#define WINDOW_WIDTH  1400
#define WINDOW_HEIGHT 800
#define randnum(min, max) ((rand() % (int) (((max) + 1) - (min))) + (min))

#define TIMER_PERIOD  16 // Period for the timer.
#define TIMER_ON         1 // 0:disable timer, 1:enable timer

#define D2R 0.0174532
#define PI 3.1415



/* Global Variables for Template File */
bool up = false, down = false, right = false, left = false;
int  winWidth, winHeight; // current Window width and height
                //Space Shuttle Coordinates
//Body initialization
int xB = 0, yB = 0;
int xS = -300, yS = 200;
bool initialPauseButton = 0;
bool initialStartButton = 0;
bool initialChangeButton = 0;


void circle(int x, int y, int r);

void DrawEllipse(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

void DrawEllipse1(float cx, float cy, float rx, float ry, int num_segments)
{
    float theta = 2 * 3.1415926 / float(num_segments);
    float c = cosf(theta);//precalculate the sine and cosine
    float s = sinf(theta);
    float t;

    float x = 1;//we start at angle = 0
    float y = 0;

    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
        //apply radius and offset
        glVertex2f(x * rx + cx, y * ry + cy);//output vertex

        //apply the rotation matrix
        t = x;
        x = c * x - s * y;
        y = s * t + c * y;
    }
    glEnd();
}

//
// to draw circle, center at (x,y)
// radius r
//
void circle( int x, int y, int r )
{
   float angle ;
   glBegin(GL_POLYGON) ;
   for ( int i = 0 ; i < 100 ; i++ )
   {
      angle = 2*PI*i/100;
      glVertex2f( x+r*cos(angle), y+r*sin(angle)) ;
   }
   glEnd();
}

void circle_wire(int x, int y, int r)
{
   float angle;

   glBegin(GL_LINE_LOOP);
   for (int i = 0; i < 100; i++)
   {
      angle = 2 * PI*i / 100;
      glVertex2f(x + r*cos(angle), y + r*sin(angle));
   }
   glEnd();
}

void print(int x, int y, const char *string, void *font )
{
   int len, i ;

   glRasterPos2f( x, y );
   len = (int) strlen( string );
   for ( i =0; i<len; i++ )
   {
      glutBitmapCharacter( font, string[i]);
   }
}

// display text with variables.
// vprint(-winWidth / 2 + 10, winHeight / 2 - 20, GLUT_BITMAP_8_BY_13, "ERROR: %d", numClicks);
void vprint(int x, int y, void *font, const char *string , ...)
{
   va_list ap;
   va_start ( ap, string );
   char str[1024] ;
   vsprintf( str, string, ap ) ;
   va_end(ap) ;
   
   int len, i ;
   glRasterPos2f( x, y );
   len = (int) strlen( str );
   for ( i =0; i<len; i++ )
   {
      glutBitmapCharacter( font, str[i]);
   }
}

// vprint2(-50, 0, 0.35, "00:%02d", timeCounter);
void vprint2(int x, int y, float size, const char *string, ...) {
   va_list ap;
   va_start(ap, string);
   char str[1024];
   vsprintf(str, string, ap);
   va_end(ap);
   glPushMatrix();
      glTranslatef(x, y, 0);
      glScalef(size, size, 1);
      
      int len, i;
      len = (int)strlen(str);
      for (i = 0; i<len; i++)
      {
         glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
      }
   glPopMatrix();
}

//
// To display onto window using OpenGL commands
//
void drawRectangle(){
    glRectf(600, 300, -600, -300);
}


void drawStars(int x, int y){
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(x + 12, y + 10);
    glVertex2f(x + 7, y - 2);
    glVertex2f(x + 2, y + 5);
    
    glVertex2f(x - 2, y + 20);
    glVertex2f(x + 2, y + 5);
    glVertex2f(x - 5, y + 5);
    
    glVertex2f(x - 5, y + 5);
    glVertex2f(x - 7, y - 2);
    glVertex2f(x - 17, y + 10);
    
    glVertex2f(x - 7, y - 2);
    glVertex2f(x - 3, y - 7);
    glVertex2f(x - 16, y - 13);
    
    glVertex2f(x - 3, y - 7);
    glVertex2f(x + 7, y - 2);
    glVertex2f(x + 10, y - 13);
    
    glEnd();
    
    glBegin(GL_POLYGON);
    
    glVertex2f(x + 2, y + 5);
    glVertex2f(x - 5, y + 5);
    glVertex2f(x - 7, y - 2);
    glVertex2f(x - 3, y - 7);
    glVertex2f(x + 7, y - 2);
    
    glEnd();
}
void draw_star_sliding(){
    
    
    
    glColor3f(1, 1, 1);
    drawStars(xS, yS);
    drawStars(xS - 40, yS + 200);
    drawStars(xS - 180, yS + 200);
    drawStars(xS - 160, yS + 80);
    drawStars(xS + 400, yS);
    drawStars(xS + 320, yS + 150);
    drawStars(xS + 490, yS + 50);
    drawStars(xS - 400, yS + 30);
    drawStars(xS - 320, yS + 100);
    drawStars(xS -100, yS + 350);
    drawStars(xS + 50, yS + 400);
    drawStars(xS + 500, yS + 250);
    drawStars(xS - 200, yS + 500);
    drawStars(xS + 500, yS + 400);
    drawStars(xS + 600, yS + 470);
    drawStars(xS + 550, yS + 500);
    drawStars(xS + 400, yS + 600);
    drawStars(xS - 300, yS - 100);
    drawStars(xS - 340, yS - 200);
    drawStars(xS - 500, yS - 150);
    drawStars(xS - 480, yS - 250);
    drawStars(xS - 600, yS - 300);
    drawStars(xS - 700, yS - 400);
    drawStars(xS - 100, yS + 500);
    drawStars(xS - 140, yS + 600);
    drawStars(xS - 400, yS + 550);
    drawStars(xS - 300, yS + 700);
    drawStars(xS - 270, yS + 800);
    drawStars(xS - 600, yS + 650);
    drawStars(xS -700, yS + 320);
    drawStars(xS - 550, yS + 380);
    
    
    
}

void drawQuads(){
    
    glColor3ub(77, 86, 86);
    
    glBegin(GL_QUADS);
    
    glVertex2f(xB-140,yB +51);
    glVertex2f(xB-175,yB +100);
    glVertex2f(xB-185,yB +100);
    glVertex2f(xB-145,yB +45);
    
    
    glVertex2f(xB-185,yB +100);
    glVertex2f(xB-300,yB +100);
    glVertex2f(xB-300,yB +90);
    glVertex2f(xB-178,yB +90);
    
    
    glVertex2f(xB-140,yB -51);
    glVertex2f(xB-175,yB -100);
    glVertex2f(xB-185,yB -100);
    glVertex2f(xB-145,yB -45);
    
    
    glVertex2f(xB-185,yB -100);
    glVertex2f(xB-300,yB -100);
    glVertex2f(xB-300,yB -90);
    glVertex2f(xB-178,yB -90);
    
    
    
    glEnd();
}

void drawNASA(){
    glColor3f(0, 0, 1);
    circle(xB + 195, yB, 30);
    
    glColor3f(1, 1, 1);
    glLineWidth(3);
    vprint2(xB + 170,yB -8, 0.15, "NASA");
    glLineWidth(1);
}

void drawMirrors(){
    circle(xB + 70,yB, 30);
    circle(xB -70, yB, 30);
    
    glColor3f(1, 0, 0);
    glLineWidth(5);
    circle_wire(xB + 70, yB, 32);
    circle_wire(xB -70, yB, 32);
    glLineWidth(1);
    
    glColor3ub(174, 214, 241);
    circle(xB + 70, yB, 22);
    circle(xB  -70, yB, 22);
}

void drawNails(){
    glPointSize(2);
    
    glBegin(GL_POINTS);
    
    glVertex2f(xB + 5, yB  );
    glVertex2f(xB + 5, yB );
    glVertex2f(xB + 5, yB + 15 );
    glVertex2f(xB + 5, yB + 30 );
    glVertex2f(xB + 5, yB + 45 );
    glVertex2f(xB + 5, yB - 15);
    glVertex2f(xB + 5, yB - 30);
    glVertex2f(xB + 5, yB - 45 );
    
    glVertex2f(xB + 145, yB );
    glVertex2f(xB + 145, yB +15);
    glVertex2f(xB + 145, yB +30);
    glVertex2f(xB + 145, yB -15);
    glVertex2f(xB + 145, yB -30);
    
    glVertex2f(xB - 145, yB );
    glVertex2f(xB - 145, yB + 15);
    glVertex2f(xB - 145, yB +30);
    glVertex2f(xB - 145, yB -15);
    glVertex2f(xB - 145, yB -30);
    
    glEnd();
    
    glPointSize(1);
}

void drawbodySegments(){
    
    glColor3f(1, 1, 1);
    
    DrawEllipse(xB, yB, 250, -60, 100);
    
    glColor3f(0, 0, 0);
    glLineWidth(3);
    DrawEllipse1(xB, yB, 250, -60, 100);
    glLineWidth(1);
    
    glColor3ub(144, 148, 151);
    
    glLineWidth(2);
    
    glBegin(GL_LINES);
    
    glVertex2f( xB + 140, yB + 51);
    glVertex2f( xB + 140, yB + -51);
    
    glVertex2f(xB , yB + 60);
    glVertex2f(xB, yB - 60);
    
    glVertex2f(xB - 140, yB + 51);
    glVertex2f(xB - 140, yB - 51);
    
    glEnd();
    
    glLineWidth(1);
}

void drawAfterBurner(){
    glColor3ub(227, 54, 23);
    
    glBegin(GL_TRIANGLES);
    
    glVertex2f(xB-200,yB +35);
    glVertex2f(xB-200,yB -35);
    glVertex2f(xB-350,yB );
    
    glColor3ub(244, 208, 63);
    
    glVertex2f(xB-200,yB +25);
    glVertex2f(xB-200,yB -25);
    glVertex2f(xB-315,yB );
    
    glEnd();
}

void display_tv(){
    glColor3ub(20, 9, 86);
    
    glRectf(550, 250, -550, -200);
    
    glColor3f(1, 1, 1);
   /* drawStars(490, 190);
    drawStars(300, 140);
    drawStars(-450, 20);
    drawStars(0,0);
    drawStars(-90, 150);
    drawStars(-290, 190);
    drawStars(100, 200);
    drawStars(400, -50);
    drawStars(-490, -150);
    drawStars(-250, -100);
    drawStars(170, -90);*/
    
}

void display_time(){
    time_t rawtime;
     struct tm * timeinfo;

     time (&rawtime);
     timeinfo = localtime (&rawtime);
    glLineWidth(3);
    glColor3f(1, 0, 0);
    vprint2(-170, 328, 0.20, "%s", asctime(timeinfo));
    glLineWidth(1);
}

void draw_ufo_body(){
//    body
    glColor4ub(76, 250, 213, 80);
    circle(xB, yB, 75);
    glColor4ub(239, 244, 243, 200);
    circle(xB + 40, yB +45, 7);
    
    glColor3f(0, 0.2, 0.2);
    circle(xB - 120, yB -75, 13);
    glColor3f(1, 1, 1);
    circle(xB -120, yB -75, 7);
    
    glColor3f(0, 0.2, 0.2);
    circle(xB + 120, yB -75, 13);
    glColor3f(1, 1, 1);
    circle(xB +120, yB -75, 7);
    
    glBegin(GL_QUADS);
    glColor3ub( 150, 161, 161);
    glVertex2f(xB + 75, yB);
    glVertex2f(xB - 75, yB);
    glVertex2f(xB - 170, yB - 75);
    glVertex2f(xB + 170, yB - 75);
    glEnd();
    
//    lights
    glColor4ub(240, 251, 2, 80);
    
    glBegin(GL_TRIANGLES);
    
    glVertex2f(xB -110, yB - 40);
    glVertex2f(xB -240, yB + 30);
    glVertex2f(xB -240, yB - 110);
    
    glVertex2f(xB +110, yB - 40);
    glVertex2f(xB +240, yB + 30);
    glVertex2f(xB +240, yB - 110);
    
    glEnd();
    
//    tires
    glColor3f(0, 0, 0);
    circle(xB -110, yB -40, 13);
    circle(xB +110, yB -40, 13);
    glColor4ub(240, 251, 2, 232);
    circle(xB -110,yB -40, 9);
    circle(xB + 110, yB - 40, 9);
    
//    glColor4ub(242, 253, 7, 80);
    
//    body segments_lines
    glColor3f(0, 0, 0);
    glLineWidth(3);
    glBegin(GL_LINES);
    
    glVertex2f(xB + 75, yB);
    glVertex2f(xB + 75 , yB -75);
    
    glVertex2f(xB - 75, yB);
    glVertex2f(xB - 75, yB -75);
    
    glEnd();
    glLineWidth(1);
    
}

void display_background(){
    
    glColor3f(0, 0, 0);
    vprint(-650, 380, GLUT_BITMAP_9_BY_15, "Mustafa Asrin Degirmenci");
    vprint(-650, 360, GLUT_BITMAP_9_BY_15, "22001699");
    vprint(-610, 340, GLUT_BITMAP_9_BY_15, "-HOMEWORK 01-");
    
    
    /*
    glLineWidth(5);
    glBegin(GL_LINES);
    glVertex2f(-25, 340);
    glVertex2f(-125, 370);
    glVertex2f(30, 340);
    glVertex2f(125, 370);
    glEnd();
    glLineWidth(1);
     
    
    circle(-125, 370, 7);
    circle(125, 370, 7);
     
    
    glColor3ub(172, 168, 168);
    circle(0, 250, 100);
    */
    
    glColor3ub(87, 44, 44);
    drawRectangle();

//    digital clock body
    glColor3ub(113, 121, 121);
    glBegin(GL_POLYGON);
    glVertex2f(-400, 300);
    glVertex2f(400, 300);
    glVertex2f(330, 375);
    glVertex2f(-330, 375);
    glEnd();
    
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    
    glVertex2f(-402, 300);
    glVertex2f(-332, 370);
    
    glVertex2f(402, 300);
    glVertex2f(332, 370);
    
    glVertex2f(-329, 375);
    glVertex2f(329, 375);
    
    glVertex2f(-600, 300);
    glVertex2f(600, 300);
    
    
    glEnd();
    glLineWidth(1);
    
    
    circle(-300, 340, 5);
    
    glColor3f(1, 0, 0);
    circle(-280, 340, 5);
    
    
    glColor3f(0, 0, 0);
    glRectf(-220, 313, 220, 363);

    display_time();

    
//   smoothing the edges of the tv and line parts
    glColor3f(0, 0, 0);
    glLineWidth(4);
    glBegin(GL_LINES);
    glVertex2f(-540, 240);
    glVertex2f(-600, 298);
    glVertex2f(550, 250);
    glVertex2f(600, 298);
    glEnd();
    glLineWidth(1);
    
    
    
    glColor3ub(172, 168, 168);
    circle(-500, -250, 35);
    circle(-400, -250, 35);
    
//    button symbols
    glLineWidth(4);
    glColor3ub(0, 0, 0);
    circle_wire(-500, -250, 15);
    glBegin(GL_LINES);
    
    glVertex2f(-500, -245);
    glVertex2f(-500, -225);
    
    glVertex2f(-410, -268);
    glVertex2f(-410, -232);
    
    glVertex2f(-390, -268);
    glVertex2f(-390, -232);
    
    glEnd();
    glLineWidth(1);
    
    
    glColor3ub(172, 168, 168);
    glRectf(-200, -270, 200, -240);
    vprint(450, -255, GLUT_BITMAP_TIMES_ROMAN_24, "ASRINTV");
    
    glColor3f(1, 0, 0);
    vprint(-110, -263, GLUT_BITMAP_TIMES_ROMAN_24, "CHANGE VEHICLE");
    
}

void display_start(){
    xB = 0;
    xS = -300;
    yS = 200;
    glColor3ub(0, 0, 0);
    glRectf(550, 250, -550, -200);
}

void display_run_ufo(){
    display_tv();
//    play and its orbits
    glColor3ub(71, 205, 207);
    DrawEllipse(-410, 150, 60, 63, 100);
    glLineWidth(3);
    glColor3ub(183, 222, 241);
    DrawEllipse(-410, 150, 120, 20, 100);
    glColor3ub(124, 147, 209);
    DrawEllipse(-410, 150, 100, 15, 100);
    glColor3ub(20, 9, 86);
    DrawEllipse(-410, 150, 90, 10, 100);
    glColor3ub(71, 205, 207);
    DrawEllipse(-410, 150, 60, 5, 100);
    DrawEllipse(-410, 162, 60, 10, 100);
    DrawEllipse(-410, 160, 60, 10, 100);
    DrawEllipse(-410, 158, 60, 10, 100);
    DrawEllipse(-410, 156, 60, 10, 100);
    DrawEllipse(-410, 154, 60, 10, 100);
    DrawEllipse(-410, 164, 60, 10, 100);
    DrawEllipse(-410, 153, 60, 10, 100);
    glLineWidth(1);
    
    draw_star_sliding();
//  digital clock body
    glColor3ub(113, 121, 121);
    glBegin(GL_POLYGON);
    glVertex2f(-400, 300);
    glVertex2f(400, 300);
    glVertex2f(330, 375);
    glVertex2f(-330, 375);
    glEnd();
//    smoothing edges
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    
    glVertex2f(-402, 300);
    glVertex2f(-332, 370);
    
    glVertex2f(402, 300);
    glVertex2f(332, 370);
    
    glVertex2f(-329, 375);
    glVertex2f(329, 375);
    
    glVertex2f(-600, 300);
    glVertex2f(600, 300);
    
    
    glEnd();
    glLineWidth(1);
    
//    signal transmitter lights
    circle(-300, 340, 5);
    
    glColor3f(1, 0, 0);
    circle(-280, 340, 5);
    
    
    glColor3f(0, 0, 0);
    glRectf(-220, 313, 220, 363);

    display_time();
//
//    tv body
    glColor3ub(87, 44, 44);
    glRectf(600, 300, -600, 250);
    glRectf(600, -300, -600, -200);
    glColor3ub(172, 168, 168);
    circle(-500, -250, 35);
    circle(-400, -250, 35);
    glLineWidth(4);
    glColor3ub(0, 0, 0);
    circle_wire(-500, -250, 15);
    
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINES);
    glVertex2f(-540, 240);
    glVertex2f(-600, 298);
    glVertex2f(550, 250);
    glVertex2f(600, 298);
    glEnd();
    
    
    glBegin(GL_LINES);
    
    glVertex2f(-500, -245);
    glVertex2f(-500, -225);
    
    glVertex2f(-410, -268);
    glVertex2f(-410, -232);
    
    glVertex2f(-390, -268);
    glVertex2f(-390, -232);
    
    glEnd();
    glLineWidth(1);
    glColor3ub(172, 168, 168);
    glRectf(-200, -270, 200, -240);
    vprint(450, -255, GLUT_BITMAP_TIMES_ROMAN_24, "OKYAYTV");
    
    glColor3f(1, 0, 0);
    vprint(-110, -263, GLUT_BITMAP_TIMES_ROMAN_24, "CHANGE VEHICLE");

    draw_ufo_body();
//    putting more shapes so the falling stars will not be outside of the tv
    glColor3ub(87, 44, 44);
    glRectf(550, 250, 600, -200);
    glRectf(-550, 250, -600, -200);
    glColor3f(1, 1, 1);
    glRectf(600, 250, 1000, -200);
    glRectf(-600, 250, -1000, -200);
    
    glColor3f(0, 0, 0);
    vprint(-650, 380, GLUT_BITMAP_9_BY_15, "Mustafa Asrin Degirmenci");
    vprint(-650, 360, GLUT_BITMAP_9_BY_15, "CTIS");
    vprint(-610, 340, GLUT_BITMAP_9_BY_15, "PROJECT");
    
    
    
}

void display_run_rocket(){
   
    
    display_tv();
//    planet and its orbits
    glColor3ub(71, 205, 207);
    DrawEllipse(-410, 150, 60, 63, 100);
    glLineWidth(3);
    glColor3ub(183, 222, 241);
    DrawEllipse(-410, 150, 120, 20, 100);
    glColor3ub(124, 147, 209);
    DrawEllipse(-410, 150, 100, 15, 100);
    glColor3ub(20, 9, 86);
    DrawEllipse(-410, 150, 90, 10, 100);
    glColor3ub(71, 205, 207);
    DrawEllipse(-410, 150, 60, 5, 100);
    DrawEllipse(-410, 162, 60, 10, 100);
    DrawEllipse(-410, 160, 60, 10, 100);
    DrawEllipse(-410, 158, 60, 10, 100);
    DrawEllipse(-410, 156, 60, 10, 100);
    DrawEllipse(-410, 154, 60, 10, 100);
    DrawEllipse(-410, 164, 60, 10, 100);
    DrawEllipse(-410, 153, 60, 10, 100);
    glLineWidth(1);
    
    draw_star_sliding();
//  digital clock
    glColor3ub(113, 121, 121);
    glBegin(GL_POLYGON);
    glVertex2f(-400, 300);
    glVertex2f(400, 300);
    glVertex2f(330, 375);
    glVertex2f(-330, 375);
    glEnd();
    
    glLineWidth(3);
    glColor3f(0, 0, 0);
    glBegin(GL_LINES);
    
    glVertex2f(-402, 300);
    glVertex2f(-332, 370);
    
    glVertex2f(402, 300);
    glVertex2f(332, 370);
    
    glVertex2f(-329, 375);
    glVertex2f(329, 375);
    
    glVertex2f(-600, 300);
    glVertex2f(600, 300);
    
    
    glEnd();
    glLineWidth(1);
    
//    signal transmitter lights
    circle(-300, 340, 5);
    
    glColor3f(1, 0, 0);
    circle(-280, 340, 5);
    
//    black backscreen of the clock
    glColor3f(0, 0, 0);
    glRectf(-220, 313, 220, 363);

    display_time();
//
//    tv body
    glColor3ub(87, 44, 44);
    glRectf(600, 300, -600, 250);
    glRectf(600, -300, -600, -200);
    glColor3ub(172, 168, 168);
    circle(-500, -250, 35);
    circle(-400, -250, 35);
    glLineWidth(4);
    glColor3ub(0, 0, 0);
    circle_wire(-500, -250, 15);
    
    glColor3f(0, 0, 0);
    
    glBegin(GL_LINES);
    glVertex2f(-540, 240);
    glVertex2f(-600, 298);
    glVertex2f(550, 250);
    glVertex2f(600, 298);
    glEnd();
    
    
    glBegin(GL_LINES);
    
    glVertex2f(-500, -245);
    glVertex2f(-500, -225);
    
    glVertex2f(-410, -268);
    glVertex2f(-410, -232);
    
    glVertex2f(-390, -268);
    glVertex2f(-390, -232);
    
    glEnd();
    glLineWidth(1);
    glColor3ub(172, 168, 168);
    glRectf(-200, -270, 200, -240);
    vprint(450, -255, GLUT_BITMAP_TIMES_ROMAN_24, "OKYAYTV");
    
    glColor3f(1, 0, 0);
    vprint(-110, -263, GLUT_BITMAP_TIMES_ROMAN_24, "CHANGE VEHICLE");
//    show time
    display_time();
//    show the afterburner
    drawAfterBurner();
//    draw the rocket
    drawbodySegments();
//    give details
    drawNails();
    
    drawMirrors();
    
    drawQuads();
    
    drawNASA();
//    making sure that the falling starts will not be outside of the screen
    glColor3ub(87, 44, 44);
    glRectf(550, 250, 600, -200);
    glRectf(-550, 250, -600, -200);
    glColor3f(1, 1, 1);
    glRectf(600, 250, 1000, -200);
    glRectf(-600, 250, -1000, -200);
    
    glColor3f(0, 0, 0);
    vprint(-650, 380, GLUT_BITMAP_9_BY_15, "Mustafa Asrin Degirmenci");
    vprint(-650, 360, GLUT_BITMAP_9_BY_15, "22001699");
    vprint(-610, 340, GLUT_BITMAP_9_BY_15, "-HOMEWORK 01-");
    
}

void display_pause_rocket(){
    
    display_run_rocket();
//    pausing the the screen for the rocket
    xB = xB ;
    glColor3ub(229, 25, 25);
    glLineWidth(5);
    vprint2(-125, 100, 0.5, "PAUSED..");
    glLineWidth(1);
}

void display_pause_ufo(){
    display_run_ufo();
    xB = xB;
//    pausing the the screen for the ufo
    glColor3ub(229, 25, 25);
    glLineWidth(5);
    vprint2(-125, 100, 0.5, "PAUSED..");
    glLineWidth(1);
}




void display() {
   //
   // clear window to black
   //
   glClearColor(1, 1, 1, 0);
   glClear(GL_COLOR_BUFFER_BIT);
    
    display_background();
   
//      compartmmentalizing the buttons
    if (initialPauseButton == 0) {
        if (initialStartButton == 0) {
            display_start();
        }
        else if (initialStartButton == 1){
            if (initialChangeButton == 0) {
                display_run_rocket();
            }
            else if (initialChangeButton == 1){
                display_run_ufo();
            }
        }
                 
    }
    else if (initialPauseButton == 1){
        if (initialStartButton == 0) {
            display_start();
        }
        else if (initialStartButton == 1){
            if (initialChangeButton == 0) {
                display_pause_rocket();
            }
            else if (initialChangeButton == 1){
                display_pause_ufo();
            }
        }
    }
    
    
   glutSwapBuffers();
}

//
// key function for ASCII charachters like ESC, a,b,c..,A,B,..Z
//
void onKeyDown(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
   if ( key == 27 )
      exit(0);
    
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

void onKeyUp(unsigned char key, int x, int y )
{
   // exit when ESC is pressed.
   if ( key == 27 )
      exit(0);
    
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyDown( int key, int x, int y )
{
   // Write your codes here.
   switch (key) {
   case GLUT_KEY_UP: up = true; break;
   case GLUT_KEY_DOWN: down = true; break;
   case GLUT_KEY_LEFT: left = true; break;
   case GLUT_KEY_RIGHT: right = true; break;
   }

   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// Special Key like GLUT_KEY_F1, F2, F3,...
// Arrow Keys, GLUT_KEY_UP, GLUT_KEY_DOWN, GLUT_KEY_RIGHT, GLUT_KEY_RIGHT
//
void onSpecialKeyUp( int key, int x, int y )
{
   // Write your codes here.
   switch (key) {
   case GLUT_KEY_UP: up = false; break;
   case GLUT_KEY_DOWN: down = false; break;
   case GLUT_KEY_LEFT: left = false; break;
   case GLUT_KEY_RIGHT: right = false; break;
   }

   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}
//return 1 if the position of the coordinates inside the designated coordinates, otherwise return 0
bool checkCircle(float px, float py, float cx, float cy, float R) {
   float dx = px - cx;
   float dy = py - cy;
   float d = sqrt(dx*dx + dy*dy);
   return d <= R;
}


//
// When a click occurs in the window,
// It provides which button
// buttons : GLUT_LEFT_BUTTON , GLUT_RIGHT_BUTTON
// states  : GLUT_UP , GLUT_DOWN
// x, y is the coordinate of the point that mouse clicked.
//
void onClick( int button, int stat, int x, int y )
{
   // Write your codes here.
    int mx = x - winWidth / 2;
    int my = winHeight / 2 - y;
    
    
    if (button == GLUT_LEFT_BUTTON && stat == GLUT_DOWN) {
        if (checkCircle(mx, my, -500, -250, 35)) {
            if (initialStartButton == 0) {
                initialStartButton = 1;
            }
            else if (initialStartButton == 1){
                initialStartButton = 0;
            }
        }
        else if (checkCircle(mx, my, -400, -250, 35)){
            if(initialStartButton == 1){
            if (initialPauseButton == 0) {
                initialPauseButton = 1;
            }
            else if (initialStartButton == 1){
                initialPauseButton = 0;
            }
        }
        }
        else if (mx > -200 && mx < 200 && my > -270 && my < -240){
            if (initialStartButton == 1) {
                if (initialChangeButton == 0) {
                    initialChangeButton = 1;
                }
                else if (initialChangeButton == 1){
                    initialChangeButton = 0;
                }
            }
        }
//        -200, -270, 200, -240
    }
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

//
// This function is called when the window size changes.
// w : is the new width of the window in pixels.
// h : is the new height of the window in pixels.
//
void onResize( int w, int h )
{
   winWidth = w;
   winHeight = h;
   glViewport( 0, 0, w, h ) ;
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   glOrtho( -w/2, w/2, -h/2, h/2, -1, 1);
   glMatrixMode( GL_MODELVIEW);
   glLoadIdentity();
   display(); // refresh window.
}

void onMoveDown( int x, int y ) {
   // Write your codes here.


   
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}



// GLUT to OpenGL coordinate conversion:
//   x2 = x1 - winWidth / 2
//   y2 = winHeight / 2 - y1
void onMove( int x, int y ) {
   // Write your codes here.
    int mx = x - winWidth / 2;
    int my = winHeight / 2 - y;
    

   
   // to refresh the window it calls display() function
   glutPostRedisplay() ;
}

#if TIMER_ON == 1
void onTimer( int v ) {
    
   glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
   // Write your codes here.
//    making sure onjects come back to the screen after reaching the end of the tv
    if (initialPauseButton == 1) {
        if (initialStartButton == 1) {
            xB = xB;
            xS = xS;
            yS = yS;
        }
    }
    else if (initialPauseButton == 0){
        if (initialStartButton == 1) {
            xB += 4;
            xS += 12;
            yS -= 12;
            if (xB -350 > winWidth / 2) {
                xB = -950;
        }
            if (yS < -1000 || xS > 1500) {
                xS = -300;
                yS = 400;
            }
    }
    }
   // to refresh the window it calls display() function
   glutPostRedisplay() ; // display()

}
#endif

void Init() {
   
   // Smoothing shapes
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   
}

int main( int argc, char *argv[] ) {
   glutInit(&argc, argv );
   glutInitDisplayMode( GLUT_RGB | GLUT_DOUBLE );
   glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
   //glutInitWindowPosition(100, 100);
   glutCreateWindow("Television Program");

   glutDisplayFunc(display);
   glutReshapeFunc(onResize);

   //
   // keyboard registration
   //
   glutKeyboardFunc(onKeyDown);
   glutSpecialFunc(onSpecialKeyDown);

   glutKeyboardUpFunc(onKeyUp);
   glutSpecialUpFunc(onSpecialKeyUp);

   //
   // mouse registration
   //
   glutMouseFunc(onClick);
   glutMotionFunc(onMoveDown);
   glutPassiveMotionFunc(onMove);
   
   #if  TIMER_ON == 1
   // timer event
   glutTimerFunc( TIMER_PERIOD, onTimer, 0 ) ;
   #endif

   Init();
   
   glutMainLoop();
}
