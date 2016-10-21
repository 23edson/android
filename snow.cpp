
//http://www.it.hiof.no/~borres/j3d/JOGL/android/p-android.html
//g++ snow.cpp -o  m -lGL -lGLU -lglut

#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
//#include <cstdlib>
//if you got error in exit() by compiler then does not incluede stdlib.h because //exit() is also defined in glut.h file.

GLfloat v[8][3] = { {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
					{1,-1,1}, {-1,-1,1}, {-1,1,1}, {1,1,1}};

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
void initWindow();
void Redesenha(int);
unsigned char *  loadBMP_custom(const char *, unsigned int&, unsigned int&);

unsigned char *texture = NULL;


void changeSize(int w1, int h1){

 // Prevent a divide by zero, when window is too short
 // (you cant make a window of zero width).
 if(h1 == 0)
  h1 = 1;

 w = w1;
 h = h1;
 ratio = 1.0f * w / h;
 // Reset the coordinate system before modifying
 glMatrixMode(GL_PROJECTION);
 glLoadIdentity();
 
 // Set the viewport to be the entire window
    glViewport(0, 0, w, h);

 // Set the clipping volume
 gluPerspective(45,ratio,0.1,1000);
 glMatrixMode(GL_MODELVIEW);
 glLoadIdentity();
 gluLookAt(x, y, z,
       x + lx,y + ly,z + lz,
    0.0f,1.0f,0.0f);

}
 
 void drawHalfSphere(int scaley, int scalex, GLfloat r) {
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
void drawpart(float swing){
	glPushMatrix();
    glRotatef(swing,1.0f,0.0f,0.0f);
    gluSphere(quadratic2, LIMB_RADIUS, SLICES, STACKS);
    glPopMatrix();
    glPushMatrix();
    glRotatef(180.0f+swing,1.0f,0.0f,0.0f);
    gluCylinder(quadratic2, LIMB_RADIUS, LIMB_RADIUS, LIMB_LENGTH, SLICES, STACKS);
    glTranslated(0.0f, 0.0f, LIMB_LENGTH);
    gluSphere(quadratic2, LIMB_RADIUS, SLICES, STACKS);       
    glPopMatrix();

	
}

void drawAndroid(){
	gluQuadricDrawStyle(quadratic2, GLU_FILL);
	gluQuadricOrientation(quadratic2, GLU_OUTSIDE);
	gluQuadricNormals(quadratic2, GLU_SMOOTH);
	
	glPushMatrix();
    gluCylinder(quadratic2, BODY_RADIUS, BODY_RADIUS, BODY_LENGTH, SLICES, STACKS);
    gluDisk(quadratic2, 0.0f, BODY_RADIUS, SLICES, STACKS);
    glTranslatef(0.0f, 0.0f, BODY_LENGTH);
    gluDisk(quadratic2, 0.0f, BODY_RADIUS, SLICES, STACKS);
    
        // draw head top 
        // talk
        glColor3f(1.0f, 1.0f, 1.0f);
    glRotatef(TALK_SWING, 1.0f, 0.0f, 0.0f);
    glTranslatef(0.0f, 0.0f, 0.07f+0.05f*TALK_SWING);
    gluDisk(quadratic2, 0.0f, BODY_RADIUS, SLICES, STACKS);
    //glPushMatrix();
    //glTranslatef(0.0f, 0.0f, 0.2);
    //glRotatef(-280, 1.0f, 0.0,0.0);
    //glRotatef(8, 1.0f, 0.0,0.0);
    //drawHalfSphere(SLICES,STACKS,BODY_RADIUS);
    
    //double[] 
    glPushMatrix();
    glColor3f(0.0f, 1.0f, 0.0f);
    glTranslatef(0,0,0);
    glRotatef(270,0,1,0);
    glTranslatef(0.01,0,0);
     glClipPlane(GL_CLIP_PLANE0,cutplane);
     //glColor3f(1.0f, 1.0f, 1.0f);
   
    glEnable(GL_CLIP_PLANE0);
    //glTranslatef(0.0f, 0.0f, 0.96);
    //glRotatef(180,1,0,0);
    
    glutSolidSphere( BODY_RADIUS, SLICES, STACKS);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
    
    //chifres
       glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
		glRotatef(10.0f,1.0f,0.0f,0.0f);
        glRotatef(30.0f,0.0f,1.0f,1.0f);
        glTranslatef(0.0f, 0.0f, BODY_RADIUS-0.1f);
        if (passo3 >= 20) {
        dir3 = dir3 == 0 ? 1 : 0;
        passo3 = 0;
    }
    passo3++;
      //  glPushMatrix();
        glPushMatrix();
    if (dir3 == 0)
		glRotatef(giraX-=BRACO_VEL,1,0,0);
      //glTranslatef(passo-0.01,0,0);
     else
        glRotatef(giraX+=BRACO_VEL,1,0,0);
        gluCylinder(quadratic2, HORN_RADIUS, HORN_RADIUS, HORN_LENGTH, SLICES, STACKS);
        glPopMatrix();
    glPopMatrix();
    glPushMatrix();
        glRotatef(10.0f,1.0f,0.0f,0.0f);
        glRotatef(-30.0f,0.0f,1.0f,1.0f);
        glTranslatef(0.0f, 0.0f, BODY_RADIUS-0.1f);
        glPushMatrix();
        if (dir3 == 0)
		glRotatef(giraX-=BRACO_VEL,1,0,0);
      //glTranslatef(passo-0.01,0,0);
     else
        glRotatef(giraX+=BRACO_VEL,1,0,0);
        gluCylinder(quadratic2, HORN_RADIUS, HORN_RADIUS, HORN_LENGTH, SLICES, STACKS);
        glPopMatrix();
        glPopMatrix(); 
        
        
    //olhos
    glColor3f(0.0f, 0.0f, 0.0f);
     glPushMatrix();
		glRotatef(-20.0f,1.0f,0.0f,0.0f);
		glRotatef(70.0f,0.0f,1.0f,1.0f);
		glTranslated(0.0f, 0.4f, BODY_RADIUS -0.89f*LIMB_RADIUS);
		gluSphere(quadratic2, LIMB_RADIUS, SLICES, STACKS);
     glPopMatrix();
     glPushMatrix();
        glRotatef(-20.0f,1.0f,0.0f,0.0f);
        glRotatef(-70.0f,0.0f,1.0f,1.0f);
        glTranslated(0.0f, 0.2f, BODY_RADIUS -0.85f*LIMB_RADIUS);
        gluSphere(quadratic2, LIMB_RADIUS, SLICES, STACKS);
        glPopMatrix();
       //glPopMatrix();     
     glPopMatrix()  ;

    //glPopMatrix(); 
    
    //Braços
    glColor3f(0.0f, 1.0f, 0.0f);
    glPushMatrix();
    glTranslatef(BODY_RADIUS+LIMB_RADIUS+0.1f, 0.0f, BODY_LENGTH-LIMB_RADIUS);
    if (passo >= 100) {
        dir = dir == 0 ? 1 : 0;
        passo = 0;
    }
    passo++;
    glPushMatrix();
    if (dir == 0)
		glRotatef(giraL-=BRACO_VEL,0,1,0);
      //glTranslatef(passo-0.01,0,0);
     else
        glRotatef(giraL+=BRACO_VEL,0,1,0);
        //glTranslatef(0.1-passo-0.01,0,0);
   // glPushMatrix();
    //if(gira < 180) gira= 360;
    //glRotatef(gira-=BRACO_VEL,0,1,0);
    drawpart(-ARM_SWING);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
    glTranslatef(-(BODY_RADIUS+LIMB_RADIUS+0.1f), 0.0f, BODY_LENGTH-LIMB_RADIUS);
    if (passo2 >= 70) {
        dir2 = dir2 == 0 ? 1 : 0;
        passo2 = 0;
    }
    passo2++;
    glPushMatrix();
    if (dir2 == 0)
		glRotatef(giraR+=BRACO_VEL,0,1,0);
      //glTranslatef(passo-0.01,0,0);
     else
        glRotatef(giraR-=BRACO_VEL,0,1,0);
    drawpart(ARM_SWING);
    glPopMatrix();
   glPopMatrix();
   
   //Pernas
   glPushMatrix();
   glTranslatef(BODY_RADIUS-LIMB_RADIUS*2.0f, 0.0f, 0.2f);
   drawpart(ARM_SWING);
        
   glPopMatrix();
   glPushMatrix();
   glTranslatef(-(BODY_RADIUS-LIMB_RADIUS*2.0f), 0.0f, 0.2f);
   drawpart(-ARM_SWING);       
   glPopMatrix();


	
}
static void torus(int numc, int numt)
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
}
void skate2(){
    int i;
    glPushMatrix();
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
	  glPushMatrix();
       glColor3f(0.6f,0.5f,0.2f);
       glPushMatrix();
       glTranslatef(0.61,0,-0.103);
       gluCylinder(quadratic,0.03f,0.06f,0.1f,20,3);
       glTranslatef(-1.41,0,0);
       gluCylinder(quadratic,0.03f,0.06f,0.1f,20,3);
       glPopMatrix();
		 //glScalef(1,1,1);
		 glColor3f(1.0f,1.0f,0.f);
    	glTranslatef(0,0,0);
	 	glRotatef(90,1,0,0);	 
    	glTranslatef(0.61,-0.15,-1.15);
    	gluCylinder(quadratic,0.08f,0.1f,2.25f,20,3);
     	glTranslatef(-1.41,0,0);
    	gluCylinder(quadratic,0.08f,0.1f,2.25f,20,3);
    
    	glPushMatrix();
	 	glColor3f(1.0f,0.0f,1.0f);
	 	glTranslatef(0,0,0);
	 	glScalef(0.7,0.7,0.7);
	 	glRotatef(270,1,0,0);
	  	glTranslatef(0,-0.11,0);
	 //glTranslatef(5,2,0);
	 	glPushMatrix();
	 	glTranslatef(0,0,0);
	 	if(!flag)
			glRotatef(alpha-=VELOCIDADE_SKATE,0,1,0);
		else glRotatef(alpha+=VELOCIDADE_SKATE,0,1,0);
	 	drawHalfSphere(10,10,0.2);
	 //glPopMatrix();
	 	glPopMatrix();
	 	
	 	glTranslatef(2.01,0,0);
	 	glPushMatrix();
	 	glTranslatef(0,0,0);
	 	if(!flag)
	 		glRotatef(alpha-=VELOCIDADE_SKATE,0,1,0);
	 	else glRotatef(alpha+=VELOCIDADE_SKATE,0,1,0);
	 	drawHalfSphere(10,10,0.2);
	 	glPopMatrix();
	 	
	 	glTranslatef(0,-3,0);
	   glRotatef(180,1,0,0);
	 
	   glPushMatrix();
	   glTranslatef(0,0,0);
	   if(!flag)
	   	glRotatef(alpha2+=VELOCIDADE_SKATE,0,1,0);
	   else glRotatef(alpha2-=VELOCIDADE_SKATE,0,1,0);
	   drawHalfSphere(10,10,0.2);
	   glPopMatrix();
	
	   glTranslatef(-2.01,0,0);
	   glPushMatrix();
	   glTranslatef(0,0,0);
	   if(!flag)
	   	glRotatef(alpha2+=VELOCIDADE_SKATE,0,1,0);
	   else glRotatef(alpha2-=VELOCIDADE_SKATE,0,1,0);
	   drawHalfSphere(10,10,0.2);
	   glPopMatrix();
	 	
	glPopMatrix();
glPopMatrix();

}
void drawSkate(){

	//glutSolidTorus(0.4, 0.1, 3,50);
	glPushMatrix();
	glTranslatef(0,0,0);
	glScalef(7,0.8,1.7);
	
	glTranslatef(0,2,0);
//glutSolidCube(0.1);

	//glTranslatef(0,0,0);
	//glScalef(0.2,0.2,0.2);
	glScalef(0.1,0.1,0.1);
	glRotatef(90.0,0.0,1.0,0.0);
	//glScalef(5,1,1);	
  // glTranslatef(0,-5,-1);
   
//torus(10,40);
   //glClipPlane(GL_CLIP_PLANE0,cutplane);
     //glColor3f(1.0f, 1.0f, 1.0f);
   
   // glEnable(GL_CLIP_PLANE0);
    //glTranslatef(0.0f, 0.0f, 1);
    //gluSphere(quadratic2, 2, 20, 5);
    
    glutSolidTorus(0.7, 0.15, 10,20);
    //glScalef(0.1,0.1,0.1);
      //glutSolidTorus(0.2, 0.1, 10,20);,g
      glColor3f(1.0f,1.0f,1.0f);
      glTranslatef(0,1.613,0.080);
      glScalef(0.1,0.2,0.1);
      //glRotatef(90,1,0,0);
      //glRotatef(4,0,1,0);
      //gluDisk(quadratic,  0., 0.13, 30, 1);
      //glutSolidCube(0.3);
      glPopMatrix();
      glPushMatrix();
      
      glPopMatrix();
      
      glPushMatrix();
       glColor3f(1.0f,1.0f,0.0f);
       glTranslatef(0,0,0);
       //glScalef(1,1,1);
       glTranslatef(0.24,1.54,-0.1);
    gluCylinder(quadratic,0.01f,0.01f,0.2f,20,3);
     glTranslatef(-0.50,0,-0);
    gluCylinder(quadratic,0.01f,0.01f,0.2f,20,3);
	//glPopMatrix();
	 glPushMatrix();
	 glColor3f(1.0f,0.0f,1.0f);
	 glTranslatef(0,0,0);
	 glScalef(0.1,0.1,0.1);
	  glRotatef(90,1,0,0);
	 glTranslatef(5,2,0);
	 glPushMatrix();
	glRotatef(alpha+=VELOCIDADE_SKATE,0,1,0);
	 drawHalfSphere(10,10,0.2);
	 glPopMatrix();
	 
	 glTranslatef(-5,0,0);
	 glPushMatrix();
	 glRotatef(alpha+=VELOCIDADE_SKATE,0,1,0);
	 drawHalfSphere(10,10,0.2);
	 glPopMatrix();
	  
	  glTranslatef(0,-2,0);
	 glRotatef(180,1,0,0);
	 
	 glPushMatrix();
	 glRotatef(alpha2+=VELOCIDADE_SKATE,0,1,0);
	 drawHalfSphere(10,10,0.2);
	 glPopMatrix();
	
	glTranslatef(5,0,0);
	glPushMatrix();
	glRotatef(alpha2+=VELOCIDADE_SKATE,0,1,0);
	 drawHalfSphere(10,10,0.2);
	  glPopMatrix();
    //glDisable(GL_CLIP_PLANE0);
	
	//cubo();
glPopMatrix();

}

void drawSnowMan() {


 glColor3f(1.0f, 1.0f, 1.0f);

// Draw Body 
 glTranslatef(0.0f ,0.75f, 0.0f);
 glutSolidSphere(0.75f,20,20);


// Draw Head
 glTranslatef(0.0f, 1.0f, 0.0f);
 glutSolidSphere(0.25f,20,20);

// Draw Eyes
 glPushMatrix();
 glColor3f(0.0f,0.0f,0.0f);
 glTranslatef(0.05f, 0.10f, 0.18f);
 glutSolidSphere(0.05f,10,10);
 glTranslatef(-0.1f, 0.0f, 0.0f);
 glutSolidSphere(0.05f,10,10);
 glPopMatrix();

// Draw Nose
 glColor3f(1.0f, 0.5f , 0.5f);
 glRotatef(0.0f,1.0f, 0.0f, 0.0f);
 glutSolidCone(0.08f,0.5f,10,2);
}



GLuint createDL() {
 GLuint snowManDL;

 // Create the id for the list
 snowManDL = glGenLists(2);

 glNewList(snowManDL+1,GL_COMPILE);
  drawSnowMan();
 glEndList();
 // start list
 glNewList(snowManDL,GL_COMPILE);

 // call the function that contains the rendering commands
 for(int i = -3; i < 3; i++)
  for(int j=-3; j < 3; j++) {
   glPushMatrix();
   glTranslatef(i*10.0,0,j * 10.0);
   glCallList(snowManDL+1);
   glPopMatrix();
  }

 // endList
 glEndList();

 return(snowManDL);
}

void initScene() {

 glEnable(GL_DEPTH_TEST);
 snowman_display_list = createDL();

  unsigned int ih=320, iw=240;
	//unsigned char * texture = NULL;
	texture = loadBMP_custom("sky.bmp", iw, ih);
	glShadeModel(GL_SMOOTH);
//	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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

}

void orientMe(float ang) {


 lx = sin(ang);
 lz = -cos(ang);
 glLoadIdentity();
 gluLookAt(x, y+CHANGE_CAMERA, z,
       x + lx,y + ly,z + lz,
    0.0f,1.0f,0.0f);
}


void moveMeFlat(int i) {
 x = x + i*(lx)*0.1;
 z = z + i*(lz)*0.1;
 glLoadIdentity();
 gluLookAt(x, y+CHANGE_CAMERA, z,
       x + lx,y + ly,z + lz,
    0.0f,1.0f,0.0f);
}

void setOrthographicProjection() {

 // switch to projection mode
 glMatrixMode(GL_PROJECTION);
 // save previous matrix which contains the
 //settings for the perspective projection
 glPushMatrix();
 // reset matrix
 glLoadIdentity();
 // set a 2D orthographic projection
 gluOrtho2D(0, w, 0, h);
 // invert the y axis, down is positive
 glScalef(1, -1, 1);
 // mover the origin from the bottom left corner
 // to the upper left corner
 glTranslatef(0, -h, 0);
 glMatrixMode(GL_MODELVIEW);
}

void resetPerspectiveProjection() {
 // set the current matrix to GL_PROJECTION
 glMatrixMode(GL_PROJECTION);
 // restore previous settings
 glPopMatrix();
 // get back to GL_MODELVIEW matrix
 glMatrixMode(GL_MODELVIEW);
}
 
void renderBitmapString(float x, float y, void *font,char *string)
{

  char *c;
  // set position to start drawing fonts
  glRasterPos2f(x, y);
  // loop all the characters in the string
  for (c=string; *c != '\0'; c++) {
    glutBitmapCharacter(font, *c);
  }
}

void renderScene(void) {
 //glutTimerFunc(10000,Redesenha,12);
 
 //printf("%d\n", deltaMove);
	if (deltaMove){
		moveMeFlat(deltaMove);
	
	}
	if (deltaAngle) {
		angle += deltaAngle;
		orientMe(angle);
	}
	

  

 glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

// Draw ground
 //Desenha o Chao
 glPushMatrix();
 glTranslatef(0,-3,0);
 glRotatef(90,0,0,1);
 glRotatef(skyRotate+=0.1,1,0,0);
 glEnable(GL_TEXTURE_2D);
  glColor3f(0.196078f, 0.6f, 0.8f);
 //glutSolidSphere(36.f,10,10);
 
  GLUquadricObj * esfera = NULL;
  esfera = gluNewQuadric();
    gluQuadricTexture(esfera,1);


    gluSphere(esfera,36,20,20);
 glDisable(GL_TEXTURE_2D);
 glPopMatrix();
 glColor3f(0.9f, 0.9f, 0.9f);
 glBegin(GL_QUADS);
  glVertex3f(-35.0f, 0.0f, -35.0f);
  glVertex3f(-35.0f, 0.0f,  35.0f);
  glVertex3f( 35.0f, 0.0f,  35.0f);
  glVertex3f( 35.0f, 0.0f, -35.0f);
 glEnd();


  
    if (passo4 >= 300) {
        dir4 = dir4 == 0 ? 1 : 0;
        passo4 = 0;
    }
    passo4++;//glutTimerFunc(10000,Redesenha,12);
    glPushMatrix();
    //glutTimerFunc(10000,Redesenha,1);
    if (dir4 == 0){
      glTranslatef(gfPosX-0.0001,0,0);
      
      //printf("%d\n",passo4);
  }
     else{
        glTranslatef(0.0001+gfPosX,0,0);
        
	}
   //glTranslatef(10,0,0);
  glPushMatrix();
	glColor3f(0.0f, 1.0f, 0.0f);
	glTranslatef(0,1.0,0);
	glScalef(0.5,0.5,0.5);
  
	glRotatef(-90,1,0,0);
	glRotatef(180,0,0,1);
	glPushMatrix();
	glTranslatef(0,0,0.1);
	drawAndroid();
	glPopMatrix();
 
	//glTranslatef(0,0,-7.6);
	glTranslatef(0,0,-1.7);
	//glRotatef(90,1,0,0);
	glScalef(1.4,0.6,1);
   
	glColor3f(1.0f, 0.0f, 0.0f);
	//drawSkate();
	skate2();
  glPopMatrix();
  glPopMatrix();
 //glPopMatrix();
 glFlush();
 gfPosX += gfDeltaX;
	if (gfPosX >= 20 || gfPosX <= -20.0) {
		gfDeltaX = -gfDeltaX;
		if(!flag)
			flag = 1;
		else flag = 0;
		//alpha = alpha+360;
      // alpha2 = -alpha2; 
	}
 //glTranslatef(0,0,0);
 
 //glTranslatef(0,0,apha+=0.1);
 //glRotatef(alpha+=0.4,1,0,0);
 //drawSnowMan();
 frame++;
 time=glutGet(GLUT_ELAPSED_TIME);
 if (time - timebase > 1000) {
  sprintf(s,"FPS:%4.2f",frame*1000.0/(time-timebase));
  timebase = time;  
  frame = 0;
 }

 /*glColor3f(0.0f,1.0f,1.0f);
 setOrthographicProjection();
 glPushMatrix();
 glLoadIdentity();
 renderBitmapString(30,15,(void *)font,"GLUT Tutorial @ 3D Tech");
 renderBitmapString(30,35,(void *)font,s);
 renderBitmapString(30,55,(void *)font,"Esc - Quit");
 glPopMatrix();*/
 //resetPerspectiveProjection();

 glutSwapBuffers();
 glFinish();
 
}

void processNormalKeys(unsigned char key, int x, int y) {

 if (key == 27)
  exit(0);
  
  if(key == 'w'){
  		CHANGE_CAMERA = CHANGE_CAMERA + 0.5; 
	 	//if(CHANGE_CAMERA > 20)flag = 1;
	}
  else if(key = 's'){
	CHANGE_CAMERA = CHANGE_CAMERA - 0.5;
		//if(CHANGE_CAMERA < -10) flag =0;	
	
	}
	printf("Ponto de visao:%f\n", CHANGE_CAMERA);
}

void pressKey(int key, int x, int y) {
 
 switch (key) {
  case GLUT_KEY_LEFT : deltaAngle = -0.01f;break;
  case GLUT_KEY_RIGHT : deltaAngle = 0.01f;break;
  case GLUT_KEY_UP : deltaMove = 1;break;
  case GLUT_KEY_DOWN : deltaMove = -1;break;
  
  
 }

}

void releaseKey(int key, int x, int y) {

 switch (key) {
  case GLUT_KEY_LEFT : if (deltaAngle < 0.0f)
        deltaAngle = 0.0f;
       break;
  case GLUT_KEY_RIGHT : if (deltaAngle > 0.0f)
        deltaAngle = 0.0f;
       break;
  case GLUT_KEY_UP : if (deltaMove > 0)
        deltaMove = 0;
       break;
  case GLUT_KEY_DOWN : if (deltaMove < 0)
        deltaMove = 0;
       break;
 }
}

void idle(){
	if(!CHANGE_CAMERA){
	gluLookAt(x, 10, 15,
				0,0,0,
				0.0f,1.0f,0.0f);
}
    glutPostRedisplay();
	}
void initWindow() {
 glutIgnoreKeyRepeat(1);
 glutKeyboardFunc(processNormalKeys);
 glutSpecialFunc(pressKey);
 glutSpecialUpFunc(releaseKey);
 glutDisplayFunc(renderScene);
 glutIdleFunc(renderScene);
 glutReshapeFunc(changeSize);
 quadratic = gluNewQuadric();
 quadratic2 = gluNewQuadric();
 initScene();

}

int main(int argc, char **argv)
{
 glutInit(&argc, argv);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 glutInitWindowPosition(100,100);
 glutInitWindowSize(640,360);
 glutCreateWindow("sniow");
 //glutTimerFunc(4000,Redesenha,2);

 // register all callbacks
 initWindow();

 glutMainLoop();

 return(0);
}
