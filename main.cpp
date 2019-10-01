#include<stdio.h>
#include<windows.h>
#ifdef __APPLE__
#include<GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>

void circle(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy,int init, int section);
void background();
void horizone();
void bird(GLfloat x, GLfloat y);
void birds();
void wave1();
void wave2();
void sand();
void stones();
void grass();
void waterTree();
void bushes();
void smallGrass(GLfloat x, GLfloat y);
void fish1();
void fish2();
void jellyFish();
void boat();
void boatMovement();
void waveMovement1();
void fishMoveMent();
void jellyFishMovement();
void birdsMovement();

float	fx1	=  -120.0;
float	fx2	=  100.0;
float	fy1	=  0.0;
float	fy2	=  0.0;

float jfx = 0;
float jfy = 0;
float wmm = 0;
float bmm = 120;
float birdMX = -170;
float birdMY = 0;

int identBot = 0;
int state = 1;
int jfState = 0;

bool boatState = true;
bool birdStatus = false;

void display(void)
{
    fishMoveMent();
    jellyFishMovement();
    waveMovement1();
    boatMovement();
    birdsMovement();
    glClear(GL_COLOR_BUFFER_BIT);
    horizone();
    birds();
    boat();
    background();

    glPushMatrix();
    glTranslated(wmm,-0.5,0);
    wave1();
    wave2();
    glPopMatrix();

    sand();
    grass();

    glPushMatrix();
    glTranslated(fx2,fy2,0);
    fish2();
    glPopMatrix();

    jellyFish();
    fish1();
    waterTree();
    bushes();
    stones();

    glutSwapBuffers();
}

void circle(GLfloat rx,GLfloat ry,GLfloat cx,GLfloat cy,int init, int section)
{
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx,cy);

    for(int i=init; i<=section; i++)

    {
        float angle = 2.0f * 3.1416f * i/100;

        float x = rx * cosf(angle);
        float y = ry * sinf(angle);

        glVertex2f((x+cx),(y+cy));
    }
    glEnd();
}


//movement
void boatMovement()
{
    identBot++;
    bmm = bmm-0.4;
    if(bmm<=-140)
    {
        identBot = 0;
        bmm=120;
    }
    if(identBot == 44)
    {
        PlaySound("shipHorn.wav", NULL, SND_ASYNC|SND_FILENAME|SND_ASYNC);
    }
    if(identBot==69)
    {
        PlaySound("beach.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    }
    if(identBot == 510)
    {
        PlaySound("shipHorn.wav", NULL, SND_ASYNC|SND_FILENAME|SND_ASYNC);
    }
    if(identBot==535)
    {
        PlaySound("beach.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    }
    glutSwapBuffers();
}

void waveMovement1()
{
    wmm = wmm+0.25;
    if(wmm >=200)
    {
        wmm = 0;
    }
    glutSwapBuffers();
}

void jellyFishMovement()
{
    if(jfState==0)
    {
        jfx = 0;
        jfy = jfy+0.1;
        if(jfy>=10)
        {
            jfState=1;
        }
    }
    else if(jfState==1)
    {
        jfx=jfx-0.1;
        jfy=jfy+0.1;
        if(jfy>=30)
        {
            jfState = 2;
        }
    }
    else if(jfState==2)
    {
        //jfx=jfx+0.1;
        jfy=jfy+0.1;
        if(jfy>=40)
        {
            jfState = 3;
        }
    }
    else if(jfState==3)
    {
        jfx=jfx+0.1;
        jfy=jfy+0.1;
        if(jfy>=60)
        {
            jfState = 4;
        }
    }
    else if(jfState==4)
    {
        jfx=jfx+0.1;
        jfy=jfy-0.1;
        if(jfy<=40)
        {
            jfState = 5;
        }
    }
    else if(jfState==5)
    {
        //jfx=jfx+0.1;
        jfy=jfy-0.1;
        if(jfy<=30)
        {
            jfState = 6;
        }
    }
    else if(jfState==6)
    {
        jfx=jfx-0.1;
        jfy=jfy-0.1;
        if(jfy<=10)
        {
            jfState = 7;
        }
    }
    else if(jfState==7)
    {
        //jfx=jfx+0.1;
        jfy=jfy-0.1;
        if(jfy<=0)
        {
            jfState = 0;
        }
    }
    glutSwapBuffers();
}

void fishMoveMent()
{

    //fish 1
    fx1 = fx1 + 0.3;
    if(fx1>=120)
    {
        fx1 = -120;
    }

    if(state==1)
    {
        if(fy1>=10)
        {
            state = 0;

        }
        fy1 = fy1 + 0.3;
    }
    else
    {
        if(fy1<=-10)
        {
            state = 1;

        }
        fy1 = fy1 -0.3;
    }


    //fish 2
    fx2 = fx2 -0.3;
    if(fx2<=-160)
    {
        fx2 = 100;
    }
    if(state==1)
    {
        if(fy2<=-10)
        {
            state = 1;

        }
        fy2 = fy2 -0.3;
    }
    else
    {
        if(fy2>=10)
        {
            state = 0;

        }
        fy2 = fy2 + 0.3;
    }
    glutPostRedisplay();
}

void birdsMovement()
{
    if(birdStatus)
    {
        birdMX = birdMX - 0.25;
        birdMY = birdMY + 0.03;
    }
    else
    {
        birdMX = birdMX + 0.25;
        birdMY = birdMY + 0.03;
    }
    if(birdMY > 19 && !birdStatus)
    {
        birdMX = 60;
        birdMY = 0;
        birdStatus = true;
    }
    if(birdMY > 19 && birdStatus)
    {
        birdMX = -170;
        birdMY = 0;
        birdStatus = false;
    }

    glutPostRedisplay();
}


//others
void horizone()
{
    glBegin(GL_POLYGON);
    glColor3f(.97,.47,.05);
    glVertex2f(-100,65);
    glColor3f(1.0,1.0,1.0);
    glVertex2f(100,65);
    glVertex2f(100,100);
    glVertex2f(-100,100);
    glEnd();

    glColor3f(0.96,0.71,0.01);
    circle(6,8,-93,65,0,50);
}
void background()
{
    glColor3f(0.21, 0.58, 0.71);
    glRectf(-100,-100,100,65);
}

void birds()
{
    glPushMatrix();
    glTranslated(birdMX,birdMY,0);
    bird(0,3);
    bird(4,3);
    bird(8,3);
    bird(-2,0);
    bird(2,0);
    bird(6,0);
    bird(10,0);
    glPopMatrix();
}

void bird(GLfloat x, GLfloat y)
{
    glPushMatrix();
    glTranslated(x,y,0);
    glColor3f(0,0,0);
    glRectf(50.75,82.5,52.75,83);
    glBegin(GL_POLYGON);
    glVertex2f(51.5,83);
    glVertex2f(52,83);
    glVertex2f(53,85);
    glVertex2f(52.5,85);
    glEnd();
    glBegin(GL_POLYGON);
    glVertex2f(51.5,83);
    glVertex2f(52,83);
    glVertex2f(51,85);
    glVertex2f(50.5,85);
    glEnd();
    glPopMatrix();
}

void wave1()
{

    for(int i =-97; i<=97; i=i+10)
    {
        glColor3f(0.21, 0.58, 0.71);
        circle(3,1.25,i,65,0,50);
    }
}

void wave2()
{
    for(int i =-297; i<=-103; i=i+10)
    {
        glColor3f(0.21, 0.58, 0.71);
        circle(3,1.25,i,65,0,50);
    }
}

void boat()
{
    glPushMatrix();
    glTranslated(bmm,-15,0);
    glBegin(GL_POLYGON);
    glColor3f(0.26,0.14,0.09);
    glVertex2f(27,86);
    glVertex2f(3,86);
    glVertex2f(0,80);
    glVertex2f(32,80);
    glVertex2f(32,90);
    glVertex2f(29,90);
    glEnd();
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0,80);
    glVertex2f(3,86);
    glVertex2f(-3,90);
    glEnd();
    glColor3f(0.51,0.42,0.40);
    glRectf(11,86,22,95);
    glColor3f(0.41,0.31,0.28);
    glRectf(14,95,19,99);


    glBegin(GL_POLYGON);
    glColor3f(0.0,1.0,0.0);
    glVertex2f(23.75,99);
    glVertex2f(23.75,95);
    glVertex2f(29.0,95);
    glVertex2f(28,99);
    glEnd();

    /*glColor3f(1.0,1.0,1.0);
    circle(2,2.6,22.25,97,75,125);*/

    glColor3f(0.41,0.31,0.28);
    glRectf(23,86,23.75,99);

    glColor3f(1.0,0.0,0.0);
    circle(.75,1.25,26,97,0,100);
    glPopMatrix();
}

void sand(void)
{
    glColor3f(.91,0.73,0.18);
    circle(90,100,90,-140,0,50);

    glColor3f(.77,0.57,0.06);
    circle(110,85,0,-130,0,50);

    glColor3f(.91,0.80,0.22);
    circle(120,95,-110,-140,0,50);

}

void stones(void)
{
    glColor3f(.73,0.67,0.55);
    circle(16,15,30.0,-70.0,0,100);
    glColor3f(.73,0.67,0.55);
    circle(9,7,32.0,-59.0,0,100);
    glColor3f(.77,0.57,0.06);
    circle(30,5,40.0,-85.0,0,50);

    glColor3f(.82,0.78,0.70);
    circle(18,12,55.0,-75.0,0,100);
    glColor3f(.82,0.78,0.70);
    circle(10,16,58.0,-75.0,0,50);
    glColor3f(.77,0.57,0.06);
    circle(30,5,58.0,-88.0,0,50);

    glColor3f(.73,0.67,0.55);
    circle(7,6,0.0,-70.0,0,100);
    glColor3f(.73,0.67,0.55);
    circle(3,5,1,-67.5,0,50);

    glColor3f(.82,0.78,0.70);
    circle(18,12,-20.0,-85.0,0,100);
    glColor3f(.82,0.78,0.70);
    circle(10,16,-25.0,-85.0,0,50);
    glBegin(GL_POLYGON);
    glColor3f(.91,0.80,0.22);
    glVertex2f(-30,-100);
    glVertex2f(-9,-100);
    glVertex2f(-9,-95);
    glVertex2f(-30,-95);
    glEnd();

    glColor3f(.73,0.67,0.55);
    circle(7,6,-80.0,-70.0,0,100);
    glColor3f(.73,0.67,0.55);
    circle(3,5,-81.0,-67.5,0,50);

    //small grasses
    smallGrass(80,-87);

    glColor3f(.73,0.67,0.55);
    circle(5,4,80.0,-90.0,0,100);
    glColor3f(.73,0.67,0.55);
    circle(1,3,81.0,-87.5,0,50);

    /*glColor3f(.73,0.67,0.55);
    circle(5,4,-20.0,-90.0,0,100);
    glColor3f(.73,0.67,0.55);
    circle(1,3,-21.0,-87.5,0,50);*/
    glEnd();
}

void grass()
{
    //bigger
    glColor3f(0.01,0.40,0.0);
    circle(2.0,20,-20,-55,0,100);

    glPushMatrix();
    glTranslatef(-37,-16,0);
    glRotatef(35,0,0,.5);
    circle(2.0,30,-20,-55,0,50);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30,-40,0);
    glRotatef(-35,0,0,.5);
    circle(2.0,30,-20,-55,0,50);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(23,-15,0);
    glRotatef(-20,0,0,.5);
    circle(2.0,20,-20,-55,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-25,0,0);
    glRotatef(20,0,0,.5);
    circle(2.0,20,-20,-55,0,100);
    glEnd();
    glPopMatrix();


    //small 1
    glColor3f(0.01,0.40,0.0);
    circle(1.0,10,0,-55,0,100);

    glPushMatrix();
    glTranslatef(-34,-18,0);
    glRotatef(35,0,0,.5);
    circle(1.0,10,0,-55,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30.5,-15,0);
    glRotatef(-30,0,0,.5);
    circle(1.0,10,0,-55,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(19,-8,0);
    glRotatef(-18,0,0,.5);
    circle(1.0,10,0,-55,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-19,-8,0);
    glRotatef(18,0,0,.5);
    circle(1.0,10,0,-55,0,100);
    glEnd();
    glPopMatrix();

    //small 2
    glColor3f(0.01,0.40,0.0);
    circle(1.0,10,-80,-38,0,100);

    glPushMatrix();
    glTranslatef(-40,34,0);
    glRotatef(35,0,0,.5);
    circle(1.0,7,-80,-38,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(12,-49.5,0);
    glRotatef(-30,0,0,.5);
    circle(1.0,7,-80,-38,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(10,-30,0);
    glRotatef(-18,0,0,.5);
    circle(1.0,8,-80,-38,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,20,0);
    glRotatef(18,0,0,.5);
    circle(1.0,8,-80,-38,0,100);
    glEnd();
    glPopMatrix();


    //small grasses
    smallGrass(45,-100);
    smallGrass(0,-100);
    smallGrass(-45,-70);
    smallGrass(-80,-65);
}

void waterTree()
{
    //water tree
    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(45,-65);
    glVertex2f(45.5,-65);
    glVertex2f(45.5,-8.5);
    glVertex2f(45,-8.5);

    glVertex2f(45,-65);
    glVertex2f(45.5,-65);
    glVertex2f(60.5,-15.5);
    glVertex2f(60,-15.5);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(-53,-56.5);
    glVertex2f(-53.35,-56.5);
    glVertex2f(-53.35,-18.5);
    glVertex2f(-53,-18.5);

    glColor3f(0.01,0.40,0.0);
    glVertex2f(-53,-56.5);
    glVertex2f(-53.35,-56.5);
    glVertex2f(-63.35,-24.5);
    glVertex2f(-63,-24.5);

    glColor3f(0.01,0.40,0.0);
    glVertex2f(-53,-56.5);
    glVertex2f(-53.35,-56.5);
    glVertex2f(-43.35,-22.5);
    glVertex2f(-43,-22.5);
    glEnd();
    glEnd();

    //tree leaf
    glColor3f(0.01,0.40,0.0);
    circle(2.0,6,45.25,-8.5,0,100);

    glPushMatrix();
    glTranslatef(0,-35,0);
    glRotatef(35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();


    glPushMatrix();
    glTranslatef(16.5,17,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-43,0);
    glRotatef(35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-51.5,0);
    glRotatef(35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-59,0);
    glRotatef(35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-67,0);
    glRotatef(35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-75,0);
    glRotatef(35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5,9,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5,1,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5,-7,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5,-15,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5,-23,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(16.5,-31,0);
    glRotatef(-35,0,0,.5);
    circle(2.5,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    //second tree leaf
    glPushMatrix();
    glTranslatef(18.5,5,0);
    glRotatef(-10,0,0,.5);
    circle(2,5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(36,19,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(34,13,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(32,7,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(30.5,1,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(28.5,-6,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(26.5,-12,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(24.5,-18,0);
    glRotatef(-45,0,0,.5);
    circle(2.5,3,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glColor3f(0.01,0.40,0.0);
    circle(2.0,6,45.25,-8.5,0,100);

    glPushMatrix();
    glTranslatef(11.5,-15,0);
    glRotatef(10,0,0,1);
    circle(2.0,4.5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(9.5,-23.5,0);
    glRotatef(13,0,0,1);
    circle(2.0,4.5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.5,-29.5,0);
    glRotatef(13,0,0,1);
    circle(2.0,4.5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6,-35.5,0);
    glRotatef(13,0,0,1);
    circle(2.0,4.5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-41.5,0);
    glRotatef(13,0,0,1);
    circle(2.0,4.5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0,-53.5,0);
    glRotatef(13,0,0,1);
    circle(2.0,4.5,45.25,-8.5,0,100);
    glEnd();
    glPopMatrix();

    glColor3f(0.01,0.40,0.0);
    circle(1.5,4,-53.25,-18,0,100);

    glPushMatrix();
    glTranslatef(-18,18,0);
    glRotatef(30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,12,0);
    glRotatef(30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,6,0);
    glRotatef(30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,0,0);
    glRotatef(30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-18,-6,0);
    glRotatef(30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-35,0);
    glRotatef(-30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-41,0);
    glRotatef(-30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-47,0);
    glRotatef(-30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-53,0);
    glRotatef(-30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4,-59,0);
    glRotatef(-30,0,0,1);
    circle(1.8,3,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();



    glColor3f(0.01,0.40,0.0);
    circle(1.5,4,-53.25,-18,0,100);

    glPushMatrix();
    glTranslatef(13.75,-13.5,0);
    glRotatef(-13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,7,0);
    glRotatef(13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(1,2,0);
    glRotatef(13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-.5,-3,0);
    glRotatef(13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2,-8,0);
    glRotatef(13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-3.5,-13,0);
    glRotatef(13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.75,-50,0);
    glRotatef(-45,0,0,1);
    circle(2.0,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(6.5,-57,0);
    glRotatef(-47,0,0,1);
    circle(2.0,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(4.5,-63,0);
    glRotatef(-47,0,0,1);
    circle(2.0,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.5,-69,0);
    glRotatef(-47,0,0,1);
    circle(2.0,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.5,-75,0);
    glRotatef(-47,0,0,1);
    circle(2.0,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();



    glColor3f(0.01,0.40,0.0);
    circle(1.5,4,-53.25,-18,0,100);

    glPushMatrix();
    glTranslatef(-16.5,8,0);
    glRotatef(13,0,0,1);
    circle(1.5,4,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-41.0,23.0,0);
    glRotatef(47,0,0,1);
    circle(2.1,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-39.5,17.0,0);
    glRotatef(47,0,0,1);
    circle(2.1,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-37.5,11.0,0);
    glRotatef(47,0,0,1);
    circle(2.1,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-35.5,5.0,0);
    glRotatef(47,0,0,1);
    circle(2.1,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-33.5,-1.0,0);
    glRotatef(47,0,0,1);
    circle(2.1,3.0,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glColor3f(0.01,0.40,0.0);
    circle(1.5,4,-53.25,-18,0,100);

    glPushMatrix();
    glTranslatef(-4.0,-25.0,0);
    glRotatef(-18,0,0,1);
    circle(1.5,3.5,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.5,-31.0,0);
    glRotatef(-18,0,0,1);
    circle(1.5,3.5,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-1.0,-37.0,0);
    glRotatef(-18,0,0,1);
    circle(1.5,3.5,-53.25,-18,0,100);
    glEnd();
    glPopMatrix();

}

void bushes()
{
    glBegin(GL_POLYGON);
    glColor3f(0.72,0.05,0.09);
    glVertex2f(80,-80);
    glVertex2f(83,-80);
    glVertex2f(86,-30);
    glVertex2f(75,-30);
    glEnd();

    glColor3f(0.44,0.07,0.31);
    circle(5.5,3,80.5,-30,0,100);

    glBegin(GL_POLYGON);
    glColor3f(0.69,0.05,0.11);
    glVertex2f(79,-80);
    glVertex2f(81,-80);
    glVertex2f(76,-43);
    glVertex2f(70,-43);
    glEnd();

    glColor3f(0.44,0.07,0.31);
    circle(3.0,1.75,73.10,-43.75,0,100);

    glBegin(GL_POLYGON);
    glColor3f(0.69,0.05,0.11);
    glVertex2f(70.5,-49);
    glVertex2f(72,-50);
    glVertex2f(67.5,-40);
    glVertex2f(68,-38);
    glVertex2f(66,-38);
    glVertex2f(67,-40);
    glEnd();

    glColor3f(0.44,0.07,0.31);
    circle(1.05,1.0,67.05,-37.75,0,100);

    glBegin(GL_POLYGON);
    glColor3f(0.69,0.05,0.11);
    glVertex2f(72.5,-55);
    glVertex2f(74,-56);
    glVertex2f(68.5,-48);
    glVertex2f(69,-47);
    glVertex2f(67,-47);
    glVertex2f(68,-48);
    glEnd();

    glColor3f(0.44,0.07,0.31);
    circle(1.05,1.0,68,-46.75,0,100);
}

void smallGrass(GLfloat x, GLfloat y)
{
    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x+0.25,y+10);
    glVertex2f(x,y+10);
    glEnd();
    //right side
    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x+1.25,y+9);
    glVertex2f(x+1.0,y+9);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x+2.25,y+8);
    glVertex2f(x+2.0,y+8);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x+3.25,y+7);
    glVertex2f(x+3.0,y+7);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x+4.25,y+6);
    glVertex2f(x+4.0,y+6);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x+5.25,y+5);
    glVertex2f(x+5.0,y+5);
    glEnd();

    //Left side
    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x-1.0+0.25,y+9);
    glVertex2f(x-1,y+9);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x-2.0+0.25,y+8);
    glVertex2f(x-2,y+8);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x-3.0+0.25,y+7);
    glVertex2f(x-3,y+7);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x-4.0+0.25,y+6);
    glVertex2f(x-4,y+6);
    glEnd();

    glBegin(GL_POLYGON);
    glColor3f(0.01,0.40,0.0);
    glVertex2f(x,y);
    glVertex2f(x+0.25,y);
    glVertex2f(x-5.0+0.25,y+5);
    glVertex2f(x-5,y+5);
    glEnd();
}

void fish1()
{
    //tail
    glPushMatrix();
    glTranslated(fx1,fy1,0);
    glColor3f(0.49,0.18,0.09);
    circle(3,5,-10,0,0,100);

    //wings
    circle(5,3,-.5,9,0,100);
    circle(4,3,-1,-9,0,100);
    //body
    glColor3f(.75,.85,.18);
    circle(9,7.75,0,0,25,75);
    circle(7,9,0,0,0,100);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(5.5,-6);
    glVertex2f(8.5,0);
    glVertex2f(5.5,6);
    glEnd();

    glColor3f(0.0,0.0,0.0);
    circle(6,7,7,0,37.5,62.5);

    glColor3f(.75,.85,.18);
    circle(5.55,7,7,0,37.5,62.5);

    glColor3f(0.49,0.18,0.09);
    circle(3,4,2,-2,37.5,62.5);

    //eyes
    glColor3f(0.0,0.0,0.0);
    circle(1.0,1.75,5,1,0,100);
    glColor3f(1.0,1.0,1.0);
    circle(0.5,.75,5,1.5,0,100);
    glColor3f(0.0,0.0,0.0);
    circle(0.25,.5,5,1.75,0,100);
    glPopMatrix();
}

void fish2()
{
    //tail;

    glPushMatrix();
    glTranslated(0,-30,0);
    glColor3f(.72,.28,.07);
    circle(3,5,60,50,0,100);
    //body
    glColor3f(1.0,1.0,1.0);
    circle(9,7.75,50,50,0,100);
    glColor3f(.85,.34,.04);
    circle(9,7.75,50,50,25,75);

    glColor3f(.85,.34,.04);
    circle(2,10,53,50,0,100);
    glColor3f(1.0,1.0,1.0);
    circle(2,10,50,50,0,100);

    glColor3f(.85,.34,.04);
    circle(2,10,48,50,0,100);
    glColor3f(1.0,1.0,1.0);
    circle(1.25,10,44.5,50,0,100);

    glColor3f(.85,.34,.04);
    circle(4,10,41,50,87.5,112.5);

    //polish
    glColor3f(0.21, 0.58, 0.71);
    glRectf(41,57.0,59,60.0);
    glRectf(41,40.0,59,43.0);
    circle(4,5,43,61,62.5,87.5);
    circle(4,5,43,39,12.5,37.5);

    //fins
    glColor3f(.72,.28,.07);
    circle(2.5,4.5,47.5,56.5,0,50);
    circle(2,3.5,53,56.5,0,50);

    circle(2.5,4.5,47.5,43.5,50,100);
    circle(2,3.5,53,43.5,50,100);
    circle(4,5,46,50,87.5,112.5);
    //eyes
    glColor3f(1.0,1.0,1.0);
    circle(0.5,.75,43,51,0,100);
    glPopMatrix();
}

void jellyFish()
{
    glPushMatrix();
    glTranslated(jfx,jfy,0);
    glColor3f(.48,.13,.43);
    circle(4,8,20,-30,0,50);
    glRectf(17,-40,17.25,-30);
    glRectf(19,-38,19.25,-30);
    glRectf(21,-42,21.25,-30);
    glRectf(23,-41,23.25,-30);
    glPopMatrix();
}

void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 0.0); // Background Color
    glOrtho(-100.0, 100.0, -100.0, 100.0, -100.0, 100.0); // To specify the coordinate & Specify the distances to the nearer and farther depth clipping planes.

}

int main()
{
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB); //Single Frame
    glutInitWindowSize (1200, 700);
    glutInitWindowPosition (0, 0);
    glutCreateWindow ("Under The Water");
    init();                              // Set up constants with default values
    glutDisplayFunc(display);
    PlaySound("beach.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);
    glutMainLoop(); // It enters the GLUT event processing loop.called at most once in a GLUT
    return 0;
}
