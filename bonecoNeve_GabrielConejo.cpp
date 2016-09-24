/*
 *	UDESC - Universidade do Estado de Santa Catarina
 *	Computação Gráfica - CGR0001
 *	T4 - Quadricas - Boneco de Neve
 *	Gabriel Guebarra Conejo
 *  Professor - André Tavares da Silva
 *  2016/02
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <GL/glut.h>
#include <GL/gl.h>

#define TELAX	1366 //Tamanho da tela em x
#define TELAY	728 //Tamanho da tela em y (Otimizado para a resolução dos pcs da udesc)

// Variaveis Rotação
static GLfloat rotacionaX = 0.0;
static GLfloat rotacionaY = 0.0;

// Função de Reshape
void reshapeFunc(int w, int h)
{
  GLfloat fa;

  // h nao pode ser 0 pois sera dividido abaixo
  if(h == 0)
      h = 1;

  // mudar
  glViewport(0, 0, w, h);

  fa = (GLfloat)w/(GLfloat)h;

  // reseta coordenadas
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // mudar perspectiva
  gluPerspective(35.0, fa, 1.0, 40.0);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
}

// Função para renderização, seta LUZ e CORES DE FUNDO
// Luz simples apensa para ajudar na visualização
void setScene()
{
  // valores de luz
  GLfloat  sourceLight[] = { 0.25, 0.25, 0.25, 1.0 };

  glEnable(GL_DEPTH_TEST);
  glFrontFace(GL_CCW);
  glEnable(GL_CULL_FACE);

  // Ativa luz
  glEnable(GL_LIGHTING);

  // Configuração da luz
  glLightfv(GL_LIGHT0,GL_AMBIENT,sourceLight);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,sourceLight);
  glEnable(GL_LIGHT0);
  // Habilita cor
  glEnable(GL_COLOR_MATERIAL);
  // Seta material para cor
  glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
  // cores do fundo da cena
  glClearColor(0.5, 0.5, 1.0, 0.5);
}

// Função de desenho da cena
void drawObjectScene(void)
{
  GLUquadricObj *pObj;	// cria quadrica

  // Limpa buffers
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Matriz do objeto como um todo
  glPushMatrix();
    // Rotações necessárias para o objeto
    glTranslatef(0.0, -1.0, -5.0);
    glRotatef(rotacionaX, 1.0, 0.0, 0.0);
    glRotatef(rotacionaY, 0.0, 1.0, 0.0);

    // iniciando quadrica
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);

    // corpo do boneco de neve
    glPushMatrix();
      glColor3f(1.0, 1.0, 1.0);
      gluSphere(pObj, .4, 26, 13);  // esfera baixo

      // A esfera do meio é um pouco mais baixa para ter um formato melhor
      glTranslatef(0.0, .36, 0.0); // esfera meio
      gluSphere(pObj, .3, 26, 13);

      glTranslatef(0.0, 0.45, 0.0); // esfera cima
      gluSphere(pObj, 0.24, 26, 13);

      // olho
      glColor3f(0.0, 0.0, 0.0);
      glTranslatef(0.1, 0.1, 0.21);
      gluSphere(pObj, 0.08, 26, 13);

      glTranslatef(-0.2, 0.0, 0.0);
      gluSphere(pObj, 0.08, 26, 13);

      // Nariz
      glColor3f(1.0, 0.3, 0.3);
      glTranslatef(0.1, -0.12, 0.0);
      gluCylinder(pObj, 0.04, 0.0, 0.3, 26, 13);
    glPopMatrix();

    // matriz chapeu
    glPushMatrix();
      // Parte de cima do chapéu
      glColor3f(0.0, 0.0, 0.0);
      glTranslatef(0.0, 1.02, 0.0);
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      gluCylinder(pObj, 0.17, 0.17, 0.4, 26, 13);

      // disco chapeu
      glDisable(GL_CULL_FACE);
      gluDisk(pObj, 0.17, 0.28, 26, 13);
      glEnable(GL_CULL_FACE);

      glTranslatef(0.0, 0.2, 0.40);
      gluDisk(pObj, 0.0, 0.17, 26, 13);
    glPopMatrix();

  // Pop da matriz do objeto
  glPopMatrix();

  // Buffer swap para mudar os buffers na janela atual
  glutSwapBuffers();
}

int main(int argc, char *argv[])
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(TELAX, TELAY);
  glutCreateWindow("CGR - Gabriel Conejo - TC4 Boneco de Neve");
  glutReshapeFunc(reshapeFunc);
  glutDisplayFunc(drawObjectScene);
  setScene();
  glutMainLoop();
  return 0;
}

//g++ -o prog bonecoNeve_GabrielConejo.cpp -lm -L/usr/local/lib -lglut -lGL -lGLU
