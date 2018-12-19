#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

void drawGround();
void myTimer(int);
void myTimerDoNothing(int);
void jumpFunc();

#define PI 3.1415
#define theta 90.0f

bool startGame = false;

float mX = 0;
float mY = 0;
float dinoPoints[2][32] = {{6, 6, 7, 7, 5, 5, 3, 3, 4, 4, 2, 2, 0, 2, 3, 5, 7, 7, 13, 13, 9, 9, 12, 12, 8, 8, 10, 10, 9, 9, 8, 8},
                           {3, 1, 1, 0, 0, 3, 3, 1, 1, 0, 0, 3, 6, 9, 7, 7, 10, 13, 13, 11, 11, 10, 10, 9, 9, 8, 8, 6, 6, 7, 7, 5}};
float tempDinoPoints[2][32] = {{6, 6, 7, 7, 5, 5, 3, 3, 4, 4, 2, 2, 0, 2, 3, 5, 7, 7, 13, 13, 9, 9, 12, 12, 8, 8, 10, 10, 9, 9, 8, 8},
                               {3, 1, 1, 0, 0, 3, 3, 1, 1, 0, 0, 3, 6, 9, 7, 7, 10, 13, 13, 11, 11, 10, 10, 9, 9, 8, 8, 6, 6, 7, 7, 5}};
float dinoEye[2] = {8, 12};
float tempDinoEye[2] = {8, 12};

int treeLastPointPosition = 128;
float treePoints[2][16] = {{125, 125, 122, 122, 123, 123, 125, 125, 128, 128, 130, 130, 131, 131, 128, 128},
                           {0, 8, 8, 12, 12, 9, 9, 13, 13, 8, 8, 11, 11, 7, 7, 0}};

float dinoRunningLegs = false;
void Draw_Figure()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 0.0);

    // float dinoEye[2] = {13,13,12,12}
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glVertex2d(tempDinoEye[0], tempDinoEye[1]);
    glEnd();

    // glPointSize(10.0);
    // glBegin(GL_POINTS);
    // glVertex2d(mX, mY);
    // glEnd();

    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 32; i++)
    {
        glVertex2f(tempDinoPoints[0][i], tempDinoPoints[1][i]);
    }
    // glVertex2d(6,3);
    // glVertex2d(6,1);
    // glVertex2d(7,1);
    // glVertex2d(7,0);
    // glVertex2d(5,0);
    // glVertex2d(5,3);
    glEnd();

    if (startGame && mY <= 0 && dinoRunningLegs)
    {
        glBegin(GL_POLYGON);
        glVertex2f(5, 1);
        glVertex2f(7, 1);
        glVertex2f(7, 0);
        glVertex2f(5, 0);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(2, 1);
        glVertex2f(4, 1);
        glVertex2f(4, 0);
        glVertex2f(2, 0);
        glEnd();
        dinoRunningLegs = false;
    }
    else
    {
        dinoRunningLegs = true;
    }
    // glPushMatrix();
    // glLoadIdentity();
    // glTranslatef(0.5, 0.5, 0.0);
    // glRotatef(25.0, 0.0, 0.0, 1.0);
    // glutSolidCube(0.5);
    // glPopMatrix();
}

float groundDust[2][3] = {{100, 130, 170}, {-2, -2, -2}};
void drawGround()
{
    glPointSize(2.0);
    glBegin(GL_LINES);
    glVertex2f(-10, 0);
    glVertex2f(100, 0);
    glEnd();

    if (groundDust[0][0] < -10)
    {
        for (int i = 0; i < 2; i++)
        {
            groundDust[0][i] = groundDust[0][i + 1];
        }
        groundDust[0][2] = 100;
    }
    glBegin(GL_POINTS);
    for (int i = 0; i < 3; i++)
    {
        glVertex2f(groundDust[0][i], groundDust[1][i]);
        glVertex2f(groundDust[0][i] + 2, groundDust[1][i]);
        glVertex2f(groundDust[0][i] + 1, groundDust[1][i] - 1);
        groundDust[0][i] += -1;
    }
    glEnd();
}

void drawTree()
{
    if (treeLastPointPosition < 0)
    {
        for (int i = 0; i < 16; i++)
        {

            treePoints[0][i] += 128+1;
            
            // treePoints[0][i] += 128;
            printf("%.0f,", treePoints[0][i] );
        }
        printf("\n");
        treeLastPointPosition = 128;
    }
    glBegin(GL_LINE_LOOP);

    for (int i = 0; i < 16; i++)
    {
        glVertex2f(treePoints[0][i], treePoints[1][i]);
        treePoints[0][i] += -1;
        
        // treePoints[0][i] += 120;
        // printf("%.0f,", treePoints[0][i] );
    }treeLastPointPosition--;
    glEnd();
}

void dinoPixels()
{
}

void display()
{

    Draw_Figure();
    drawGround();
    drawTree();
    glutSwapBuffers();
}

int V = 25;
int gravity = -10;

float VX = V * cos(theta * PI / 180);
float VY = V * sin(theta * PI / 180);
float time = 0.1;

void dontDoAnythingIdle()
{
}
void myIdleFunc()
{

    if (startGame)
    {
        jumpFunc();
        glutPostRedisplay();
    }
}

bool jump = false;

void jumpFunc()
{
    if (jump)
    {
        if (mY >= 0)
        {
            time = time + 0.05;
            // mX = VX * time;
            mY = VY * time + 0.5 * (gravity)*time * time;

            // printf("%f--\n", mY);
            for (int i = 0; i < 32; i++)
            {
                tempDinoPoints[1][i] = dinoPoints[1][i] + mY;

                // printf("%f----\n",dinoPoints[1][i]);
            }
            // tempDinoEye[0] = dinoEye[0]+mY;
            tempDinoEye[1] = dinoEye[1] + mY;
            // glutTimerFunc(50, myTimerDoNothing, 0);
        }
        else
        {
            // glutIdleFunc(dontDoAnythingIdle); // 1 click == 1 jump
            // glutTimerFunc(50, myTimer, 0);
            time = 0.1;
            mY = 0;
            jump = false;
        }
    }
}

void myTimer(int value)
{
    // glutIdleFunc(myIdleFunc);
    if (startGame)
    {
        jumpFunc();
        glutPostRedisplay();
    }
    glutTimerFunc(50, myTimer, 0);
}
void myTimerDoNothing(int value)
{
}
void keyDown(int key, int x, int y)
{

    if (key == GLUT_KEY_UP)
    {
        if (startGame)
        {
            jump = true;
            // glutTimerFunc(50, myTimer, 0);
            glutIdleFunc(myIdleFunc);
        }
        else
        {
            startGame = true;
        }
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
    // glutTimerFunc(50, myTimer, 0); // mili seconds , myTimer(int value), value
    // glutKeyboardFunc(myKeyboardFunc); // myKeyboardFunc(unsigned char key , int x , int y)
    // glutMouseFunc(myMouse); //  myMouse(int button , int state , int x , int y)
    glutSpecialFunc(keyDown); // keyDown(int key , int x , int y)
    // glutSpecialUpFunc(keyUp);   // keyUp(int key , int x , int y)
    // glutPostRedisplay();
    // glutReshapeFunc(myReshape);

    myinit();
    glutMainLoop();
    return 0;
}
