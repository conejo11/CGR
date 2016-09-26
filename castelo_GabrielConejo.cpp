/*
 *  UDESC - Universidade do Estado de Santa Catarina
 *  Computação Gráfica - CGR0001
 *  T4 - Quadricas - Boneco de Neve
 *  Gabriel Guebarra Conejo
 *  Professor - André Tavares da Silva
 *  2016/02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <time.h>

#define TELAX   1366 //Tamanho da tela em x
#define TELAY   728 //Tamanho da tela em y (Otimizado para a resolução dos pcs da udesc)

// funçoes Globais
static int slices = 25;
static int stacks = 25;
GLUquadricObj *quadric;
GLUquadricObj *fundosEsq;
GLUquadricObj *fundosDir;
GLUquadricObj *frenteEsq;
GLUquadricObj *frenteDir;
GLUquadricObj *telhadoFundosEsq;
GLUquadricObj *telhadoFrenteDir;
GLUquadricObj *telhadoFrenteEsq;
GLUquadricObj *telhadoTorre;

void castle() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glColor3d(1, 0.5, 0.0);

    glTranslated(-1, 0, -4);
    glRotated(87, 1, 0, 0);
    glRotated(-30, 0, 0, 1);
    glBegin (GL_QUADS);

    //muros
    //lado esquerdo
    glVertex3f(-0.1f, 0.0f, 0.1f);
    glVertex3f(-0.1f, 0.0f, 0.6f);
    glVertex3f(-0.1f, 2.0f, 0.6f);
    glVertex3f(-0.1f, 2.0f, 0.1f);
    //parte de trás
    glVertex3f(0.0f, -0.1f, 0.1f);
    glVertex3f(2.0f, -0.1f, 0.6f);
    glVertex3f(2.0f, -0.1f, 0.6f);
    glVertex3f(2.0f, -0.1f, 0.1f);
    //lado direito
    glVertex3f(2.1f, 2.0f, 0.6f);
    glVertex3f(2.1f, 2.0f, 0.1f);
    glVertex3f(2.1f, 0.0f, 0.1f);
    glVertex3f(2.1f, 0.0f, 0.6f);
    //frente
    glVertex3f(2.0f, 2.1f, 0.6f);
    glVertex3f(2.0f, 2.1f, 0.1f);
    glVertex3f(0.0f, 2.1f, 0.1f);
    glVertex3f(0.0f, 2.1f, 0.6f);
    glEnd;

    glVertex3f(0.15f, 2.5f, 0.5f);
    glVertex3f(0.15f, 2.5f, -0.2f);
    glVertex3f(0.0f, 2.5f, -0.2f);
    glVertex3f(0.0f, 2.5f, 0.5f);

    //Entrada
    //Torres
    glBegin(GL_QUADS);
    //Fundos esquerda
    fundosEsq = gluNewQuadric();
    gluCylinder(fundosEsq, 0.2, 0.2, 0.6, slices, stacks);
    glTranslated(0, 2, 0);
    //Frente esquerda
    frenteDir = gluNewQuadric();
    gluCylinder(frenteDir, 0.2, 0.2, 0.6, slices, stacks);
    glTranslated(2, 0, 0);
    //Frente direita
    frenteDir = gluNewQuadric();
    gluCylinder(frenteDir, 0.2, 0.2, 0.6, slices, stacks);
    glEnd;
    glPopMatrix();


    //telhado
    glPushMatrix();
    glColor3d(1, 0.5, 0.2);
    glTranslated(-1, 0, -4);
    glRotated(87, 1, 0, 0);
    glRotated(-30, 0, 0, 1);
    //Fundos esquerdo
    telhadoFundosEsq = gluNewQuadric();
    glTranslated(0, 0, -0.58);
    gluCylinder(telhadoFundosEsq, 0.0, 0.23, 0.6, slices, stacks);
    //Frente esquerda
    telhadoFrenteEsq = gluNewQuadric();
    glTranslated(0, 2, 0);
    gluCylinder(telhadoFrenteEsq, 0.0, 0.23, 0.6, slices, stacks);
    //Frente direita
    telhadoFrenteDir = gluNewQuadric();
    glTranslated(2, 0, 0);
    gluCylinder(telhadoFrenteDir, 0.0, 0.23, 0.6, slices, stacks);
    //Torre quadrada
    telhadoTorre = gluNewQuadric();
    glTranslated(-0.2, -1.6, -0.8);
    gluCylinder(telhadoTorre, 0.0, 0.23, 0.6, slices, stacks);
    glPopMatrix();

    glutSwapBuffers();
}

// Desenha cena
void drawScene() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
    glRotatef(0.0, 0.0, 1.0, 0.0);
    glRotatef(0.0, 1.0, 0.0, 0.0);
    glEnd();
    castle();
    glutSwapBuffers();
}

// Funçao Reshape FINALMENTE ARRUMEI ISSO AEEEEES
void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-(float) w / (float) h, (float) w / (float) h, -1.0, 1.0, 1.0,
            100.0);
    glMatrixMode (GL_MODELVIEW);
    glLoadIdentity();
}

void idle() {
    glutPostRedisplay();
}

// LUZES E AMBIENTE
const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat high_shininess[] = { 100.0f };

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(TELAX, TELAY); //tamanho da tela
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("CGR - Gabriel Conejo - TC4 Boneco de Neve");
    glutReshapeFunc(reshape);
    glutDisplayFunc(drawScene); //callback, qual função vai ser chamada para mostrar
    glutIdleFunc(idle);

    glClearColor(0.5, 0.25, 0.25, 0.25);
    glEnable (GL_CULL_FACE);
    glCullFace (GL_BACK);

    glEnable (GL_DEPTH_TEST);
    glDepthFunc (GL_LESS);

    glEnable (GL_LIGHT0);
    glEnable (GL_NORMALIZE);
    glEnable (GL_COLOR_MATERIAL);
    glEnable (GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

    glutMainLoop();
    return 0;
}