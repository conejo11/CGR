/*
 *	UDESC - Universidade do Estado de Santa Catarina
 *	Computação Gráfica - CGR0001
 *	T3 - Partículas
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


#define NROPART 2000 //Número Maximo de Particulas em tela (2000 tá lagando um pouco)
#define TELAX	1366 //Tamanho da tela em x
#define TELAY	728 //Tamanho da tela em y (Otimizado para a resolução dos pcs da udesc)


float queda = 1.0; // queda da particula
float velocidade = 1.0; // velocidade da particula
float zoom = -13.0; // Zoom da tela
int i;

// Estrutura que define os atributos das particulas
typedef struct {
  bool existe;	// Diz se a particula existe atualmente
  float desaparece,tempoExistente; // tempo da particula em tela
  float xpos,zpos,ypos; // posição da particula
  float gravidade, vel;  // Gravidade da cena e velocidade
}particulas;

// vetor de particulas
particulas particula[NROPART];

//Função para setar os atributos das particulas definidos anteriormente na struct
//Auto Explicativo
void inicializaParticula(int i) {
    particula[i].existe = true;
    particula[i].tempoExistente = 1.0;
    particula[i].desaparece = float(rand()%100)/1000.0f+0.003f;
    particula[i].xpos = (float) (rand() % 21) - 10;
    particula[i].ypos = 10.0;
    particula[i].zpos = (float) (rand() % 21) - 10;
    particula[i].vel = velocidade;
    particula[i].gravidade = -0.8;
}

void inicializa( ) {
  //int x, z;

    glShadeModel(GL_SMOOTH); // Smooth Shading selecionado (não testei com flat shading)
    glClearColor(0.5, 0.5, 1.0, 0.5);//Cores do fundo
    glClearDepth(1.0); // para limpar o buffer de profundidade
    glEnable(GL_DEPTH_TEST); // Habilita teste de profundidade

    // Inicia as particulas
    for (i = 0; i < NROPART; i++) {
        inicializaParticula(i);
    }

}

// Função para desenhar as particulas de neve
void desenhaParticulasNeve() {
  float x, y, z;
  for (i = 0; i < NROPART; i=i+2) {
    if (particula[i].existe == true) {
      x = particula[i].xpos;
      y = particula[i].ypos;
      z = particula[i].zpos + zoom;
      glColor3f(1.0, 1.0, 1.0); // para cor branca
      glPushMatrix(); // Para adicionar matriz na pilha
      glTranslatef(x, y, z); // Cria matriz de tradução, matriz atual será multiplicada por esta
      glutSolidSphere(0.1, 10, 10); // Formato da particula (circulo)
      glPopMatrix(); // para retirar matriz da pilha
      particula[i].ypos += particula[i].vel / (queda*1000); //Queda para baixo
      particula[i].xpos += particula[i].vel / (queda*3000); //Queda para esquerda em velocidade menor
      particula[i].vel += particula[i].gravidade; //Queda pela gravidade
      particula[i].tempoExistente -= particula[i].desaparece; //Tempo de vida da particula sendo decrementado
      //Reinicia particula caso seu tempo de vida esgote
      if (particula[i].tempoExistente < 0.0) {
        inicializaParticula(i);
      }
    }
  }
}

// Cria o cenário e desenha as particulas
void criaCenario( ) {
//  int i, j;
  //float x, y, z;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpar Buffers
  glMatrixMode(GL_MODELVIEW); //Aplica operações sobre a pilha  de matrizes modelview
  glLoadIdentity(); // Substitui matriz pela matriz identidade
  desenhaParticulasNeve(); // Função para desenhar neve
  glutSwapBuffers(); // Troca buffers na janela atual
}

void redimensiona(int w, int h) {
    if (h == 0) h = 1;

    glViewport(0, 0, w, h); // Seta a porta de visão, no caso w = width e h = hight
    glMatrixMode(GL_PROJECTION); //Aplica operações sobre a pilha  de matrizes de projeção
    glLoadIdentity(); // Substitui matriz pela matriz identidade

    gluPerspective(45, (float) w / (float) h, .1, 200); // Matriz de perspectiva

    glMatrixMode(GL_MODELVIEW); //Aplica operações sobre a pilha  de matrizes modelview
    glLoadIdentity(); // Substitui matriz pela matriz identidade
}

void janelaInativa( ) {
  glutPostRedisplay(); // Marca janela para ser mostrada novamente
}

int main (int argc, char** argv) {
  glutInit(&argc, argv); // Inicia Janela
  glutInitDisplayMode(GLUT_DEPTH | GLUT_RGB | GLUT_DOUBLE);
  glutInitWindowSize(TELAX, TELAY); // Inicia a resolução
  glutCreateWindow("CGR - Trabalho 3 - Neve - Gabriel Conejo"); // Nome da janela
  inicializa(); // Inicializa funções
  glutDisplayFunc(criaCenario); // Cria o cenário
  glutReshapeFunc(redimensiona); // Para o redimensionamento da tela
  glutIdleFunc(janelaInativa); // Marca janela para ser mostrada novamente
  glutMainLoop();
  return 0;
}

//g++ -o prog particulas.cpp -lm -L/usr/local/lib -lglut -lGL -lGLU
