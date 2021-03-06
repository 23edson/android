
/**
*   Universidade Federal da Fronteira Sul
*
*   TRABALHO I
*   Disciplina: Computação gráfica
*   Professor: José Carlos Bins Filho
*
*
* 	 Aluno : Edson Lemes da Silva
*   
*   
*   As funções a seguir fazem a renderização do android andando de skate, 
*   a textura utilizada para o céu está no arquivo 'sky.bmp', a leitura é feito
*   dentro da função Inicializar(). A imagem 'sky.bmp' foi retirada da Internet.
* 	
*
*
**/

#include "android.h"


/**
 * @function MudarLuz
 *
 * 
 * A função define a rotina para inicializar luz no material.
 *
 **/

void MudarLuz(){

	 float ambiente[]={0.0f, 0.0f, 0.0f, 1.0f};
    float difusa[]={0.01f, 0.01f, 0.01f, 1.0f};
    float especular[]={0.50f, 0.50f, 0.50f, 1.0f };
    float spec=32.0f;
	 
	 glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,ambiente);
    glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,difusa);
    glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,especular);
    glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,spec);

}

/**
 * @function DesenhaMetadeEsfera
 *
 * @param int scaley - define escala de y;
 * @param int scalex - define escala de x.
 * @param GLfloat r  - define o raio r.
 *
 * A função renderiza metade da esfera, definindo duas cores .
 * para a esfera desenhada.
 **/ 
 
 void DesenhaMetadeEsfera(int scaley, int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][3];
 
   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*2*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }
 
   glBegin(GL_QUADS);
   int k = scalex/2;
   int f;
     for (i=0; i<scalex-1; ++i) {
		 f = 0;
		 if(i < k)glColor3f(1.0f,0.0f,1.0f);
		 else glColor3f(0.0f,0.0f,1.0f);
       for (j=0; j<scaley; ++j) {
		 
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         
         glVertex3fv(v[(i+1)*scaley+j]);
         if(j == scaley-2)glColor3f(0.0f,0.0f,1.0f);
       }f++;
     }
   glEnd();
 }
 
/**
 * @function DesenhaMembro
 *
 * Auxilia na renderização do Android para desenhar os braços e pernas. .
 * 
 **/ 
void DesenhaMembro(){
	glPushMatrix();
   glRotatef(0,1.0f,0.0f,0.0f);
   gluSphere(quadratic2, RAIO_MEMBROS, 15, 15);
   glPopMatrix();
   glPushMatrix();
   glRotatef(180.0f,1.0f,0.0f,0.0f);
   gluCylinder(quadratic2, RAIO_MEMBROS, RAIO_MEMBROS, TAMANHO_MEMBROS, 15, 15);
   glTranslated(0.0f, 0.0f, TAMANHO_MEMBROS);
   gluSphere(quadratic2, RAIO_MEMBROS, 15, 15);       
   glPopMatrix();

	
}


/**
 * @function Android
 * 
 * 
 * A função renderiza o boneco Android, também já simula o movimento
 * dos braços e das antenas. A iluminação do material também é realizada
 * na rotina. Os objetos utilizados para desenhar o boneco, são implementados
 * no opengl, tais como: Disco, esfera e cilindro. O corpo do Android é representado 
 * por um cilindro "tampados" com dois discos em seus extremos, a cabeça é representada
 * por uma semi-esfera(esfera 'cortada' ao meio). As antenas são 
 * cilindros no alto da cabeça, os olhos são esferas pretas. E os membros do Android,
 * são cilindros "tampados" com das esferas nos seus extremos.
 *
 **/ 

void Android(){
	
	//Define opcoes para o desenho
	gluQuadricDrawStyle(quadratic2, GLU_FILL);
	gluQuadricOrientation(quadratic2, GLU_OUTSIDE);
	gluQuadricNormals(quadratic2, GLU_SMOOTH);
	
	//luz do objeto
	glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT,luzAmbiente1);
   glMaterialfv(GL_FRONT_AND_BACK,GL_DIFFUSE,luzDifusa1);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,luzEspecular2);
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,90.0);
	
   //Desenha o Corpo do Android
	glPushMatrix();
   gluCylinder(quadratic2, RAIO_CORPO, RAIO_CORPO, TAMANHO_CORPO, 15, 15);
   gluDisk(quadratic2, 0.0f, RAIO_CORPO, 15, 15);
   glTranslatef(0.0f, 0.0f, TAMANHO_CORPO);
   gluDisk(quadratic2, 0.0f, RAIO_CORPO, 15, 15);
    
   glColor3f(1.0f, 1.0f, 1.0f);
   glRotatef(0., 1.0f, 0.0f, 0.0f);
   glTranslatef(0.0f, 0.0f, 0.07f+0.05f);
   gluDisk(quadratic2, 0.0f, RAIO_CORPO, 15, 15);

   //Desenha a cabeca do Android, contorna ao meio a esfera renderizada
   glPushMatrix();
   glColor3f(0.0f, 1.0f, 0.0f);
   glTranslatef(0,0,0);
   glRotatef(270,0,1,0);
   glTranslatef(0.001,0,0);
   glClipPlane(GL_CLIP_PLANE0,planoX);
   glEnable(GL_CLIP_PLANE0);
   glutSolidSphere( RAIO_CORPO, 15, 15);
   glDisable(GL_CLIP_PLANE0);
   glPopMatrix();
   
   //Desenha as antenas e simula o movimento delas
   glColor3f(0.0f, 1.0f, 0.0f);
   glPushMatrix();
   glRotatef(10.0f,1.0f,0.0f,0.0f);
   glRotatef(30.0f,0.0f,1.0f,1.0f);
   glTranslatef(0.0f, 0.0f, RAIO_CORPO-0.1f);
   if (passo3 >= 20) {
     dir3 = dir3 == 0 ? 1 : 0;
     passo3 = 0;
   }
   passo3++;
   glPushMatrix();
   if (dir3 == 0)glRotatef(giraX-=BRACO_VEL,1,0,0);
   else glRotatef(giraX+=BRACO_VEL,1,0,0);
   gluCylinder(quadratic2, RAIO_ANTENA, RAIO_ANTENA, TAMANHO_ANTENA, 15, 15);
   glPopMatrix();
   glPopMatrix();
    
   glPushMatrix();
   glRotatef(10.0f,1.0f,0.0f,0.0f);
   glRotatef(-30.0f,0.0f,1.0f,1.0f);
   glTranslatef(0.0f, 0.0f, RAIO_CORPO-0.1f);
   glPushMatrix();
   if (dir3 == 0)glRotatef(giraX-=BRACO_VEL,1,0,0);
   else glRotatef(giraX+=BRACO_VEL,1,0,0);
   gluCylinder(quadratic2, RAIO_ANTENA, RAIO_ANTENA, TAMANHO_ANTENA, 15, 15);
   glPopMatrix();
   glPopMatrix(); 
        
   //Desenha os olhos
   glColor3f(0.0f, 0.0f, 0.0f);
   glPushMatrix();
   glRotatef(-20.0f,1.0f,0.0f,0.0f);
   glRotatef(70.0f,0.0f,1.0f,1.0f);
   glTranslated(0.0f, 0.4f, RAIO_CORPO -0.89f*RAIO_MEMBROS);
   gluSphere(quadratic2, 0.39, 15, 15);
   glPopMatrix();
   
   glPushMatrix();
   glRotatef(-20.0f,1.0f,0.0f,0.0f);
   glRotatef(-70.0f,0.0f,1.0f,1.0f);
   glTranslated(0.0f, 0.2f, RAIO_CORPO -0.85f*RAIO_MEMBROS);
   gluSphere(quadratic2, 0.39, 15, 15);
   glPopMatrix();
   glPopMatrix()  ;

   //Desenha os Braços e simula o movimento
   glColor3f(0.0f, 1.0f, 0.0f);
   glPushMatrix();
   glTranslatef(RAIO_CORPO +RAIO_MEMBROS+0.1f, 0.0f, TAMANHO_CORPO-RAIO_MEMBROS);
   if (passo >= 100) {
   	dir = dir == 0 ? 1 : 0;
   	passo = 0;
   }
   passo++;
   glPushMatrix();
   if (dir == 0)glRotatef(giraL-=BRACO_VEL,0,1,0);
   else glRotatef(giraL+=BRACO_VEL,0,1,0);
   DesenhaMembro();
   glPopMatrix();
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-(RAIO_CORPO+RAIO_MEMBROS+0.1f), 0.0f, TAMANHO_CORPO-RAIO_MEMBROS);
   if (passo2 >= 70) {
   	dir2 = dir2 == 0 ? 1 : 0;
      passo2 = 0;
  	}
   passo2++;
   glPushMatrix();
   if (dir2 == 0)glRotatef(giraR+=BRACO_VEL,0,1,0);
   else glRotatef(giraR-=BRACO_VEL,0,1,0);
   DesenhaMembro();
   glPopMatrix();
   glPopMatrix();
   
   //Desenha as Pernas do Android
   glPushMatrix();
   glTranslatef(RAIO_CORPO-RAIO_MEMBROS*2.0f, 0.0f, 0.2f);
   DesenhaMembro();
        
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-(RAIO_CORPO-RAIO_MEMBROS*2.0f), 0.0f, 0.2f);
   DesenhaMembro();       
   glPopMatrix();


	
}
//funcao para desenhar metade de torus, (não usada)
/*static void torus(int numc, int numt)
{
   int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * 3.14;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (1+.1*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (1+.1*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = .1 * sin(s * twopi / numc);
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}*/


/**
 * @function Skate
 * 
 *
 * A função é responsável pela renderização do Skate, utilizando-se 
 * os objetos definitos no opengl, como : Disco, cilindro. E também a função
 * que renderiza metade de uma esfera (para as rodas). A prancha do Skate é renderizada
 * através de vários discos desenhados com deslocamento de 0.0001 cada disco. A base do eixo
 * e o eixo são representados por cilindros, e por último as rodas são simuladas por metade de 
 * esferas já aplicando as rotações e também a luz em todo o Skate. 
 **/ 
void Skate(){
	 MudarLuz();
    int i;
    glPushMatrix();
    
    //Desenha a prancha do Skate
	 gluDisk(quadratic2, 0.2f, 1.4, 40, 40);
	
	 float limiar = 0.0;
	 glColor3f(1.0f, 0.4f, 0.0f);
	 for(i =0;i < 40;i++){
	 	glTranslatef(0,0,limiar+=0.0001);
	 	gluDisk(quadratic2, 0.f, 1.4, 40, 40);
	 
	 }
	 glColor3f(1.0f, 0.0f, 0.0f);
	 glTranslatef(0,0,limiar);
	 gluDisk(quadratic2, 0.2f, 1.4, 40, 40);
	 glPopMatrix();
	 
	 //Desenha os eixos e a base deles
	  
	 glPushMatrix();
    glColor3f(0.6f,0.5f,0.2f);
    
    //Desenha base 1 e 2   
    glPushMatrix();
    glTranslatef(0.61,0,-0.103);
    gluCylinder(quadratic,0.03f,0.06f,0.1f,20,3);
    glTranslatef(-1.41,0,0);
    gluCylinder(quadratic,0.03f,0.06f,0.1f,20,3);
    glPopMatrix();
	
	 //Desenha eixos 1 e 2	
	 glColor3f(1.0f,1.0f,0.f);
    glTranslatef(0,0,0);
	 glRotatef(90,1,0,0);	 
    glTranslatef(0.61,-0.15,-1.15);
    gluCylinder(quadratic,0.08f,0.1f,2.25f,20,3);
    glTranslatef(-1.41,0,0);
    gluCylinder(quadratic,0.08f,0.1f,2.25f,20,3);
         
    //Desenha as rodas conforme a sua rotacao    	
    glPushMatrix();
	 glColor3f(1.0f,0.0f,1.0f);
	 glTranslatef(0,0,0);
	 glScalef(0.7,0.7,0.7);
	 glRotatef(270,1,0,0);
	 glTranslatef(0,-0.11,0);
	 
	 //Desenha roda 1
	 glPushMatrix();
	 glTranslatef(0,0,0);
	 if(!flag)
		glRotatef(alpha-=VELOCIDADE_SKATE,0,1,0);
	 else glRotatef(alpha+=VELOCIDADE_SKATE,0,1,0);
	 DesenhaMetadeEsfera(10,10,0.2);
	 glPopMatrix();
	 
	 //Desenha roda 2
	 glTranslatef(2.01,0,0);
	 glPushMatrix();
	 glTranslatef(0,0,0);
	 if(!flag)
	 	glRotatef(alpha-=VELOCIDADE_SKATE,0,1,0);
	 else glRotatef(alpha+=VELOCIDADE_SKATE,0,1,0);
	 DesenhaMetadeEsfera(10,10,0.2);
	 glPopMatrix();
	 	
	 glTranslatef(0,-3,0);
	 glRotatef(180,1,0,0);
	 
	 //Desenha roda 3
	 glPushMatrix();
	 glTranslatef(0,0,0);
	 if(!flag)
	   glRotatef(alpha2+=VELOCIDADE_SKATE,0,1,0);
	 else glRotatef(alpha2-=VELOCIDADE_SKATE,0,1,0);
	 DesenhaMetadeEsfera(10,10,0.2);
	 glPopMatrix();
	
	 //Desenha roda 4
	 glTranslatef(-2.01,0,0);
	 glPushMatrix();
	 glTranslatef(0,0,0);
	 if(!flag)
	  glRotatef(alpha2+=VELOCIDADE_SKATE,0,1,0);
	 else glRotatef(alpha2-=VELOCIDADE_SKATE,0,1,0);
	 DesenhaMetadeEsfera(10,10,0.2);
	 glPopMatrix();
	 	
	 glPopMatrix();
    glPopMatrix();

}



/**
 * @function OlharPara
 *
 * A função controla o deslocamento da camera conforme os eventos do teclado.
 * 
 **/ 
void OlharPara(){
	glLoadIdentity();
 	gluLookAt(x, y+CHANGE_CAMERA, z,x + Deltax,y + Deltay,z + Deltaz,0.0f,1.0f,0.0f);



}


/**
 * @function CorrigirCamera
 *
 * @param float angulo - ângulo atual.
 * A função é responsável por corrigir o movimento da câmera, caso for necessário. As
 * coordenadas são corrigidas conforme o ângulo atual, calculando as direções no plano xyz;
 * 
 * 
 **/ 
void CorrigirCamera(float angulo) {


 Deltax = sin(angulo);
 Deltaz = -cos(angulo);
 OlharPara();
 
}


/**
 * @function MovimentarCamera
 *
 * @param int i - Valor da variação (intervalo de [-1,1] inclusive.)
 * A função é responsável por aplicar o movimento da câmera, no eixo x e z.
 * Também é possível controlar a velocidade da câmera através da constante
 * CAM_VELOCIDADE. 
 * 
 * 
 **/ 

void MovimentarCamera(int i) {
 x = x + i*(Deltax)*CAM_VELOCIDADE;
 z = z + i*(Deltaz)*CAM_VELOCIDADE;
 OlharPara();
}


/**
 * @function Desenha
 *
 * 
 * Função de callback responsável por desenhar todos os objetos da aplicação.
 * Nela, são gerenciados os fatores da câmera, e renderizados o "chão", a esfera
 * externa simulada como "céu" e também os demais objetos. Nesta mesma função,
 * é renderizado as iluminações do sol e do ambiente em relação aos objetos.
 * 
 **/ 

void Desenha(void) {
 
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
 	
 	if (delta2){
		MovimentarCamera(delta2);
	}
	if (delta) {
		angulo += delta;
		CorrigirCamera(angulo);
	}
	//Desenha o ceu (esfera com textura)
	glPushMatrix();
	glTranslatef(0,-3,0);
 	glRotatef(90,0,0,1);
 	glRotatef(SKY_ROTATE+=0.1,1,0,0);
 	glEnable(GL_TEXTURE_2D);
  	glColor3f(0.196078f, 0.6f, 0.8f);
 
 
  	//GLUquadricObj * esfera = NULL;
  	//esfera = gluNewQuadric();
   gluQuadricTexture(quadratic,1);
	gluSphere(quadratic,36,20,20);
 	glDisable(GL_TEXTURE_2D);
 	glColor3f(1.0,0.7,0.1);
 	glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade2);
 	glMateriali(GL_FRONT, GL_SHININESS, especMaterial2);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente2);
 	glEnable(GL_LIGHT0);
      
   //Desenha o Sol e atribui a iluminacao 
   glTranslatef(25,25,0); 
 	glutSolidSphere(4,30,30);
 	glDisable(GL_LIGHT0);
 	glPopMatrix();
 	glColor3f(0.9f, 0.9f, 0.9f);
	 	
	//Desenha o chao do cenario 	
 	glBegin(GL_QUADS);
  	glVertex3f(-35.0f, 0.0f, -35.0f);
  	glVertex3f(-35.0f, 0.0f,  35.0f);
  	glVertex3f( 35.0f, 0.0f,  35.0f);
  	glVertex3f( 35.0f, 0.0f, -35.0f);
 	glEnd();
   
   //Controle para Renderizacao dos objetivos como animacao
	if (passo4 >= 300) {
   	dir4 = dir4 == 0 ? 1 : 0;
   	passo4 = 0;
   }
   passo4++;
   glPushMatrix();
   if (dir4 == 0){
      glTranslatef(objPos-0.0001,0,0);
  	}
   else{
      glTranslatef(0.0001+objPos,0,0);
   }
  
  	glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0,1.0,0);
	glScalef(0.5,0.5,0.5);
  	
  	//Desenha o Android
	glRotatef(-90,1,0,0);
	glRotatef(180,0,0,1);
	glPushMatrix();
	glTranslatef(0,0,0.1);
	Android();
	glPopMatrix();
 			
 	//Desenha o Skate
 	glTranslatef(0,0,-1.7);
	glScalef(1.4,0.6,1);
   glColor3f(1.0f, 0.0f, 0.0f);
	Skate();
  	glPopMatrix();
  	glPopMatrix();
   glFlush();
   objPos += objDelta;
   //Define os limites de deslocamento dos objetos
	if (objPos >= 20 || objPos <= -20.0) {
		objDelta = -objDelta;
		if(!flag)flag = 1;
		else flag = 0;
	}
	//Controle de Quadros por segundos da aplicacao
   frame++;
   time=glutGet(GLUT_ELAPSED_TIME);
 
   if (time - base > 1000) {
 	   printf("FPS:%4.2f\n" , frame*1000.0/(time-base));
      base = time;  
      frame = 0;
   }
   glutSwapBuffers();
   glFinish();
 
}

/**
 * @function Inicializa
 *
 * 
 * A função é responsável por inicializar as opções necessárias para a aplicação,
 * tais como: definição do z-buffer, quadricas, textura do céu, e as duas fontes de 
 * iluminação; as normais são calculadas pelo opengl. 
 * 
 * 
 **/ 

void Inicializa() {
	glEnable(GL_DEPTH_TEST);
 	quadratic = gluNewQuadric();
 	quadratic2 = gluNewQuadric();
	
	unsigned int ih=320, iw=240;
	texture = loadBMP_custom("sky.bmp", iw, ih);
	glShadeModel(GL_SMOOTH);
	GLuint texnum[1];
	
	// Define a textura corrente
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glGenTextures(1, texnum);
	glBindTexture(GL_TEXTURE_2D, texnum[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iw, ih, 0,
		GL_RGB, GL_UNSIGNED_BYTE, texture);
	gluBuild2DMipmaps(texnum[0], GL_RGB, iw, ih, GL_RGB, GL_UNSIGNED_BYTE, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
   delete texture;
   
   glShadeModel(GL_SMOOTH);
   
	// Define a refletancia do material
	//glMaterialfv(GL_FRONT, GL_SPECULAR, especularidade);
	// Define a concentracao do brilho
	//glMateriali(GL_FRONT, GL_SHININESS, especMaterial);

	// Ativa o uso da luz ambiente
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente1);

	// Define os parametros da luz de numero 0
	glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente1);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa1);
	glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular1);
	glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz1);
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente2);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa2);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular2);
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz2);

	// Habilita a definicao da cor do material a partir da cor corrente
	glEnable(GL_COLOR_MATERIAL);
	//Habilita o uso de iluminacao
	glEnable(GL_LIGHTING);
	// Habilita a luz de numero 0
	glEnable(GL_LIGHT1);
	glEnable(GL_NORMALIZE);

}

/**
 * @function Teclado
 *
 * @param unsigned char key - Obter a tecla apertada do teclado
 * @param int x - coordenada x
 * @param int y - coordenada y
 *
 * A função é responsável por: caso for pressionada a tecla 'esc', então
 * a aplicação é finalizada, caso for pressionado 'w', a câmera é deslocada
 * para cima, e caso for 's', a câmera é deslocada para baixo. 
 * 
 * 
 **/ 

void Teclado(unsigned char key, int x, int y) {

 if (key == 27)exit(0);
  
  if(key == 119){
  		CHANGE_CAMERA += DESLOCAMENTO_VISAO; 
	 	//if(CHANGE_CAMERA > 20)flag = 1;
	}
  else if(key == 115){
	CHANGE_CAMERA -= DESLOCAMENTO_VISAO;
		//if(CHANGE_CAMERA < -10) flag =0;	
	
	}
	printf("Ponto de visao:%f\n", CHANGE_CAMERA);
}

/**
 * @function RotacionaCamera
 *
 * @param unsigned char key - Obter a tecla apertada do teclado
 * @param int x - coordenada x
 * @param int y - coordenada y
 *
 * A função é responsável pelo controle das direções da câmera conforme o evento
 * de teclado, nesta função as teclas: UP,DOWN,LEFT e RIGHT são gerenciados para
 * o controle da câmera, de modo que a mesma será direcionada conforme a respectiva
 * tecla seja pressionada.
 * 
 * 
 **/ 

void RotacionaCamera(int key, int x, int y) {
 
	switch (key) {
  		case GLUT_KEY_LEFT : delta = -0.05f;break;
  		case GLUT_KEY_RIGHT : delta = 0.05f;break;
  		case GLUT_KEY_UP : delta2 = 1;break;
  		case GLUT_KEY_DOWN : delta2 = -1;break;
  	}

}

/**
 * @function ParaRotacaoCamera
 *
 * @param unsigned char key - Obter a tecla apertada do teclado
 * @param int x - coordenada x
 * @param int y - coordenada y
 *
 * Esta função é necessária para a correção do movimento da câmera, isto é,
 * quando uma tecla direcional é pressionada, ela permanece "pressionada", então
 * esta função faz com que a mesma seja definida como  'zero'.
 * 
 **/ 

void ParaRotacaoCamera(int key, int x, int y) {

	switch (key) {
  		case GLUT_KEY_LEFT : if (delta < 0.0f)delta = 0.0f; break;
  		case GLUT_KEY_RIGHT : if (delta > 0.0f)delta = 0.0f;break;
  		case GLUT_KEY_UP : if (delta2 > 0) delta2 = 0; break;
  		case GLUT_KEY_DOWN : if (delta2 < 0)delta2 = 0;break;
 	}
}

/**
 * @function AlteraTamanhoJanela
 *
 * @param GLsizei w - define a largura;
 * @param GLsizei h - define a altura.
 *
 * A função define a rotina para o redimensionar a tela.
 *
 **/

void AlteraTamanhoJanela(GLsizei w, GLsizei h){


 if(h == 0) h = 1;
 
 AspRatio = (float)w / (float)h;

 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 
 glViewport(0, 0, w, h);

 gluPerspective(45,AspRatio,0.4,500);
 glMatrixMode(GL_MODELVIEW);
 OlharPara();

}

/**
 * @function idle
 *
 *
 * A função define a rotina para atualizar a posição da câmera
 * quando necessário.
 *
 **/
void idle(void){
	glutPostRedisplay();
	OlharPara();
}
//Inicializa o opengl
int main(int argc, char **argv){
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);
 glutInitWindowSize(600,300);
 glutCreateWindow("Android Robot");
 glutDisplayFunc(Desenha);
 glutReshapeFunc(AlteraTamanhoJanela);
 
 glutKeyboardFunc(Teclado);
 glutSpecialFunc(RotacionaCamera);
 glutSpecialUpFunc(ParaRotacaoCamera);
 
 glutIdleFunc(idle);
 Inicializa();


 glutMainLoop();


}
