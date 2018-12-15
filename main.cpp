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

    glPointSize(10.0);
    glBegin(GL_POINTS);
    glVertex2d(mX, mY);
    glEnd();

    // glPushMatrix();
    // glLoadIdentity();
    // glTranslatef(0.5, 0.5, 0.0);
    // glRotatef(25.0, 0.0, 0.0, 1.0);
    // glutSolidCube(0.5);
    // glPopMatrix();
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
        glutIdleFunc(dontDoAnythingIdle);
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
    gluOrtho2D(-10, 50, -10, 50);
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
