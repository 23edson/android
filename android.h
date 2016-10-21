/**
*   Universidade Federal da Fronteira Sul
*
*   TRABALHO I
*   Disciplina: Computação gráfica
*   Professor: José Carlos Bins Filho
*
*
* 	 Aluno : Edson Lemes da Silva
*   Compilação pelo arquivo Makefile
*   ou g++ android.cpp bmp.cpp android.h  -o  m -lGL -lGLU -lglut && ./m
*
*   Este programa representa a renderização do robô do Android sob um skate.
*   Assim, é feito a simulação dele andando de skate; a paisagem é simulada
* 	 dentro de uma esfera, utlizando-se textura do "céu" no horizonte.
*
*
**/

#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

//Variaveis de reshape
float AspRatio;

//Controle de Velocidade
float VELOCIDADE_SKATE = 1.1;
float CAM_VELOCIDADE = 0.3;
float BRACO_VEL = 1.5;
GLfloat objPos = 0.0; //deslocamento dos objetos
GLfloat objDelta = .03;

//Rotacoes
GLfloat alpha = 360; //rodas do skate
GLfloat alpha2 = 360.0;

GLfloat giraL = 360.0; //braco esquerdo
GLfloat giraR = 0.0; //braco direito
GLfloat giraX = 360.0; //antenas do android
float SKY_ROTATE = 0.0;

//Fatores de correcao da camera
float angulo=0.0,delta = 0.0;
int delta2 = 0;
//posicao inicial da camera
float x=0.0f,y=0.5f,z=5.0f;
//Deslocamento das coordenadas da camera 
float Deltax=0.0f,Deltay=0.f,Deltaz=-2.0f;

float DESLOCAMENTO_VISAO = 0.5;  //Distancia de deslocamento quando usado as teclas 'w' ou 's'

//Quadricas para desenhar os objetos
GLUquadricObj *quadratic;
GLUquadricObj *quadratic2;

//Controle de FPS
int frame,time,base=0;


//Raio e tamanho do Android
GLfloat TAMANHO_CORPO=2.8f;
GLfloat RAIO_CORPO=1.3f;
GLfloat TAMANHO_MEMBROS=1.5f;
GLfloat RAIO_MEMBROS=0.4f;
GLfloat TAMANHO_ANTENA=0.5f;
GLfloat RAIO_ANTENA=0.1f;
         
GLfloat CHANGE_CAMERA = 0; //distancia de deslocamento da camera
GLuint id; //usada para renderizar esfera
int flag = 0; //controle de animaçao

double planoX[4]={1.0f,0.0f,0.0f,0.0f};

//Controle de temporizacao para rotacoes
GLint dir,dir2,dir3,dir4 = 0;
GLint passo,passo2,passo3,passo4 = 0;

//Definicao das duas fontes de luz
//fonte 1
GLfloat luzAmbiente1[4] = { 0.2,0.2,0.2,1.0 };
GLfloat luzDifusa1[4] = { 0.5,0.5,0.5,1.0 };	   // "cor"
GLfloat luzEspecular1[4] = { 1,1,1, 1.0 };// "brilho"
GLfloat posicaoLuz1[4] = { 0.0, 25, 25, 1.0 };

GLfloat especularidade1[4] = { 1.0,1.0,1.0,.0 };
GLint especMaterial1 = 4;

//fonte2
GLfloat luzAmbiente2[4] = { 0.6,0.5,0.5,1.0 };
GLfloat luzDifusa2[4] = { 0.9,0.3,1.9,1.0 };	   // "cor"
GLfloat luzEspecular2[4] = { 1,1.1,1.1, 0.0 };// "brilho"
GLfloat posicaoLuz2[4] = { SKY_ROTATE, 0, 0, 1.0 };

GLfloat especularidade2[4] = { 0.8,0.8,0.8,.0 };
GLint especMaterial2 = 300;

unsigned char *  loadBMP_custom(const char *, unsigned int&, unsigned int&);

//Leitura de textura
unsigned char *texture = NULL;