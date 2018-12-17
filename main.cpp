#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

#define PI 3.1415
#define theta 90.0f

float mX = 0;
float mY = 0;
void Draw_Figure()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // float dinoEye[2] = {13,13,12,12}
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2d(8 ,12);
    glEnd();

    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2d(mX, mY);
    glEnd();

float dinoPoints[2][32] = {{6,6,7,7,5,5,3,3,4,4,2,2,0,2,3,5,7,7,13,13,9,9,12,12,8,8,10,10,9,9,8,8},
                              {3,1,1,0,0,3,3,1,1,0,0,3,6,9,7,7,10,13,13,11,11,10,10,9,9,8,8,6,6,7,7,5}};
    glBegin(GL_LINE_LOOP);
        for(int i=0;i<32;i++){
            glVertex2f(dinoPoints[0][i] , dinoPoints[1][i]);
        }
        // glVertex2d(6,3);
        // glVertex2d(6,1);
        // glVertex2d(7,1);
        // glVertex2d(7,0);
        // glVertex2d(5,0);
        // glVertex2d(5,3);
    glEnd();

    // glPushMatrix();
    // glLoadIdentity();
    // glTranslatef(0.5, 0.5, 0.0);
    // glRotatef(25.0, 0.0, 0.0, 1.0);
    // glutSolidCube(0.5);
    // glPopMatrix();
}


void dinoPixels(){
    float dinoPoints[2][33] = {{3.5,3.5,4,4,3,3,1,2,2.5,4,5,5,9,9,7,7,8.5,8.5,6,6,7,7,6.5,6.5,6,6,5.5,5.5,7,7,5,5,3.5},
                              {3,1.5,1.5,1,1,3.5,6,10,7,7,9,11,11,9,9,8.5,8.5,8,8,7,7,6,6,6.5,6.5,4.5,3,1,1,0.5,0.5,3,3}};
}

void display()
{
    Draw_Figure();
    glutSwapBuffers();
}

int V = 30;

float VX = V*cos(theta*PI/180);
float VY = V*sin(theta*PI/180);
float time=0.1;



void dontDoAnythingIdle(){

}
void myIdleFunc()
{

    if (mY >= 0)
    {
        time = time + 0.05;
        // mX = VX * time;
        mY = VY * time + 0.5 * (-10) * time * time;
    }
    else{
        glutIdleFunc(dontDoAnythingIdle);   // 1 click == 1 jump
        time=0.1;
        mY=0;
    }

    glutPostRedisplay();
}

void myTimer(int value){
    glutIdleFunc(myIdleFunc);
}
void keyDown(int key, int x, int y)
{
    if(key == GLUT_KEY_UP){
        glutTimerFunc(50,myTimer,0);
    }
}

void myinit() //set attributes
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glColor3f(1.0f, 0.0f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-10, 100, -10, 100);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // GLUT_DOUBLE
    glutInitWindowSize(900, 400);
    glutInitWindowPosition(100, 100);

    // int wid =GLUT_SCREEN_HEIGHT;
    // printf("%d",wid);

    glutCreateWindow("");

    glutDisplayFunc(display);

    // glutIdleFunc(myIdleFunc);
    // glutTimerFunc(50,myTimer,0);    // mili seconds , myTimer(int value), value
    // glutKeyboardFunc(myKeyboardFunc); // myKeyboardFunc(unsigned char key , int x , int y)
    // glutMouseFunc(myMouse); //  myMouse(int button , int state , int x , int y)
    glutSpecialFunc(keyDown); // keyDown(int key , int x , int y)
    // glutSpecialUpFunc(keyUp);   // keyUp(int key , int x , int y)
    glutPostRedisplay();
    // glutReshapeFunc(myReshape);

    myinit();
    glutMainLoop();
    return 0;
}
