#include <GL/glut.h>
#include <math.h>

void myinit() //set attributes
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); 
    glColor3f(1.0f, 0.0f, 1.0f);         
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 100, 0, 100);
    glMatrixMode(GL_MODELVIEW);
}

void Draw_Figure()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 1.0, 0.0);
    
	glPointSize(10.1);
    glBegin(GL_POINTS);
        glVertex2d(10,10);
    glEnd();

    glPushMatrix();
    glLoadIdentity();
    glTranslatef(0.5, 0.5, 0.0);
    glRotatef(25.0, 0.0, 0.0, 1.0);
    glutSolidCube(0.5);
    glPopMatrix();  
}


void display()
{
    Draw_Figure();
    glFlush(); //   glutSwapBuffers();
}

void myIdleFunc(){
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);                       
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // GLUT_DOUBLE
    glutInitWindowSize(600, 600); 
    glutInitWindowPosition(0, 0); 
    glutCreateWindow("");

    glutDisplayFunc(display); 
    
    glutIdleFunc(myIdleFunc);
    glutTimerFunc(50,myTimer,0);    // mili seconds , myTimer(int value), value
    glutKeyboardFunc(myKeyboardFunc); // myKeyboardFunc(unsigned char key , int x , int y)
    glutMouseFunc(myMouse); //  myMouse(int button , int state , int x , int y)
    glutSpecialFunc(keyDown);   // keyDown(int key , int x , int y)
    glutSpecialUpFunc(keyUp);   // keyUp(int key , int x , int y)
    glutPostRedisplay();
    glutReshapeFunc(myReshape);

    myinit(); 
    glutMainLoop(); 
    return 0;
}
