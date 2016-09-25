/*
 *	UDESC - Universidade do Estado de Santa Catarina
 *	Computação Gráfica - CGR0001
 *	T4 - Quadricas - Castelo
 *	Gabriel Guebarra Conejo
 *  Professor - André Tavares da Silva
 *  2016/02
 */

#include <stdio.h>
#include <math.h>
#include <GL/glut.h>
GLfloat dx, y, z;

void display(void)
{
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glBegin(GL_QUADS);                                            // início triângulo
          glColor3f(1.0, 0.0f, 0.0f);
          glNormal3f(10.0f, 0.0f, 0.0f);
          glVertex3f( 0.0f,   0.0f, 0.0f);
          glVertex3f( 0.0f,   0.5f, 0.0f);
          glVertex3f( 0.5f,   0.5f, 0.0f);
          glVertex3f( 0.5f,   0.0f, 0.0f);
        glEnd();

        glBegin(GL_TRIANGLES);
          glColor3f(0,0,0);                                                // início triângulo
          glVertex3f( 0.0f, 2.0f, 0.0f);                                  // Topo
          glVertex3f(1.0f,0.0f, 0.0f);                                  // Esquerda embaixo
          glVertex3f( -1.0f,0.0f, 0.0f);                                  // Direita embaixo
        glEnd();                                                        // fim triângulo

        glBegin(GL_TRIANGLES);                                          // início triângulo
          glColor3f(0,0,0);
          glVertex3f( 2.0f, 0.0f, 0.0f);                                  // Topo
          glVertex3f(3.0f,-1.0f, 0.0f);                                  // Esquerda embaixo
          glVertex3f( 1.0f,-1.0f, 0.0f);                                  // Direita embaixo
        glEnd();                                                        // fim triângulo

        glBegin(GL_TRIANGLES);
        glColor3f(0,0,0);                                                 // início triângulo
        glVertex3f( -2.0f, 0.0f, 0.0f);                                  // Topo
        glVertex3f(-3.0f,-1.0f, 0.0f);                                  // Esquerda embaixo
        glVertex3f( -1.0f,-1.0f, 0.0f);                                  // Direita embaixo
        glEnd();
        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(0.0, -2.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(1.0, -2.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(-1.0, -2.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(-2.0, -2.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(2.0, -2.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(2.0, -1.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0.5, 0, 0);
        glPushMatrix();
        glTranslatef(0.0, -1.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(0.0, 0.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        glColor3f(0, 0, 0);
        glPushMatrix();
        glTranslatef(-2.0, -1.0, 0.0);
        glutSolidCube (1);
        glPopMatrix();

        // fim triângulo
        glutSwapBuffers();
}

//what?
void reshape (int w, int h)
{
        glMatrixMode (GL_PROJECTION);
        if (w <= h)
                glOrtho (-5.0, 5.0, -5.0*(GLfloat)h/(GLfloat)w,
                         5.0*(GLfloat)h/(GLfloat)w, -2.0, 20.0);
        else
                glOrtho (-5.0*(GLfloat)w/(GLfloat)h,
                        5.0*(GLfloat)w/(GLfloat)h, -5.0, 5.0, -2.0, 20.0);
        glMatrixMode(GL_MODELVIEW);
}

void init(void)
{
        GLfloat mat_specular[] = { 0.0, 0.0,0.0, 0.0 };
        GLfloat mat_shininess[] = { 0.0};
        GLfloat light_position[] = { 0.0, 0.0, -1.0, 0.0 }; //algo

        glClearColor (0.5, 0.2, 0.3, 90.0);
        glShadeModel (GL_SMOOTH);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT,light_position);
        glMaterialfv(GL_LIGHT0, GL_AMBIENT, mat_specular);
        glMaterialfv(GL_LIGHT0, GL_DIFFUSE, mat_shininess);
        glLightfv(GL_LIGHT0, GL_POSITION, light_position);

        //colors environment
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_NORMALIZE);

}
//prt
int main(int argc, char** argv)
{

        glutInit(&argc, argv);
        glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glutInitWindowSize (800, 600);
        glutCreateWindow("CGR - Gabriel Conejo - TC4 Castelo");
        glutReshapeFunc(reshape); //call func
        glutDisplayFunc(display); //open interface
        init ();//prt
        glutMainLoop(); //prt
        return 0;
}

//g++ -o prog castelo_GabrielConejo.cpp  -lm -L/usr/local/lib -lglut -lGL -lGLU
