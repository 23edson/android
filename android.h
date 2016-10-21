#include <GL/glut.h>
#include <math.h>

#include <stdio.h>
//#include <string.h>


GLfloat gfPosX = 0.0;
GLfloat gfDeltaX = .03;
float VELOCIDADE_SKATE = 1.1;
float BRACO_VEL = 1.5;
float skyRotate = 0.0;
float angle=0.0,deltaAngle = 0.0,ratio;
float x=0.0f,y=1.75f,z=5.0f;
float lx=0.0f,ly=0.0f,lz=-1.0f;
int deltaMove = 0,h,w;
int font= 10;
static GLint snowman_display_list;
int bitmapHeight=13;
GLUquadricObj *quadratic;
GLUquadricObj *quadratic2;
int frame,time,timebase=0;
char s[30];
GLfloat alpha = 360;
GLfloat alpha2 = 360.0;
GLfloat giraL = 360.0;
GLfloat giraR = 0.0;
GLfloat giraX = 360.0;

GLfloat BODY_LENGTH=3.0f;
GLfloat BODY_RADIUS=1.5f;
GLfloat LIMB_LENGTH=1.7f;
GLfloat LIMB_RADIUS=0.4f;
GLfloat HORN_LENGTH=0.6f;
GLfloat HORN_RADIUS=0.1f;
    
    // drawing precision
GLfloat SLICES=30;
GLfloat STACKS=30;    
     
    // animation    
GLfloat ARM_SWING=0.0f;
GLfloat DELTA_ARM_SWING=5.0f;
GLfloat MAX_ARM_SWING=50.0f;
    
GLfloat TALK_SWING=0.0f;
GLfloat MAX_TALK_SWING=5.0f;
GLfloat DELTA_TALK_SWING=2.0f;

GLfloat CHANGE_CAMERA = 0;
GLuint id;
int flag = 0;

double cutplane[4]={1.0f,0.0f,0.0f,0.0f};
double cutplane2[4]={0.0f,1.0f,0.0f,0.0f};
GLint dir,dir2,dir3,dir4 = 0;
GLint passo,passo2,passo3,passo4 = 0;

//luz
GLfloat luzAmbiente1[4] = { 0.2,0.2,0.2,1.0 };
GLfloat luzDifusa1[4] = { 0.5,0.5,0.5,1.0 };	   // "cor"
GLfloat luzEspecular1[4] = { 1,1,1, 1.0 };// "brilho"
GLfloat posicaoLuz1[4] = { 0.0, 25, 25, 1.0 };

GLfloat especularidade1[4] = { 1.0,1.0,1.0,.0 };
GLint especMaterial1 = 4;

GLfloat luzAmbiente2[4] = { 0.6,0.5,0.5,1.0 };
GLfloat luzDifusa2[4] = { 0.9,0.3,1.9,1.0 };	   // "cor"
GLfloat luzEspecular2[4] = { 1,1.1,1.1, 0.0 };// "brilho"
GLfloat posicaoLuz2[4] = { skyRotate, 0, 0, 1.0 };

GLfloat especularidade2[4] = { 0.8,0.8,0.8,.0 };
GLint especMaterial2 = 300;


void initWindow();
void Redesenha(int);
unsigned char *  loadBMP_custom(const char *, unsigned int&, unsigned int&);

unsigned char *texture = NULL;