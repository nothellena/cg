#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "png_texture.h"

#define PI 3.1415

#define COORD_TEXTURA_PLANO 1.0
#define COORD_TEXTURA_AVIAO 1.0
#define COR_DO_PLANO 0.52,0.52,0.78,1.0
#define COR_DO_AVIAO 0.3,0.52,0.18,1.0
#define TEXTURA_DO_PLANO "mcz.png"
#define TEXTURA_DO_AVIAO "camuflagem.png"

GLfloat adjust_factor = 50;
GLint WIDTH =600;
GLint HEIGHT=600;

GLfloat obs[3]={0.0,2.0/adjust_factor,0.0};
GLfloat look[3]={0.0,1.0/adjust_factor,0.0};
GLuint  textura_plano;
GLuint  textura_aviao;

GLshort texturas=1;
GLfloat tetaxz=0;
GLfloat raioxz=6;
GLuint  jato;
GLfloat dist = 0;
int rot_angle = 0;
GLfloat rad;
GLfloat asa[][3]={
    {-4.0/adjust_factor,0.0,0.0},
    {+4.0/adjust_factor,0.0,0.0},
    {0.0,0.0,3.0/adjust_factor}
  };

GLfloat cauda[][3]={
    {0.0,0.0,0.0},
    {0.0,2.0/adjust_factor,-1.0/adjust_factor},
    {0.0,2.0/adjust_factor,0.0},
    {0.0,0.0,2.0/adjust_factor}
  };

GLfloat ctp[4][2]={
  {0.0,1.0},
  {1.0,0.0},
  {1.0,0.0},
  {0.0, 0.0}
};

GLfloat cta[4][2]={
  {-COORD_TEXTURA_AVIAO,-COORD_TEXTURA_AVIAO},
  {+COORD_TEXTURA_AVIAO,-COORD_TEXTURA_AVIAO},
  {+COORD_TEXTURA_AVIAO,+COORD_TEXTURA_AVIAO},
  {-COORD_TEXTURA_AVIAO,+COORD_TEXTURA_AVIAO}
};


void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,10.0);
  glMatrixMode(GL_MODELVIEW);
}

void compoe_jato(void){
  GLUquadricObj *quadric;

  /* inicia a composicao do jato */
  jato = glGenLists(1);
  glNewList(jato, GL_COMPILE);

  /* asas */
  glPushMatrix();
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0,-dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist  * cos(rad)/adjust_factor);
  glBegin(GL_TRIANGLES); 
  glTexCoord2fv(cta[0]); glVertex3fv(asa[0]);
  glTexCoord2fv(cta[1]); glVertex3fv(asa[1]);
  glTexCoord2fv(cta[3]); glVertex3fv(asa[2]);
  glEnd();
  glPopMatrix();
  
  /* corpo */
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  
  glPushMatrix();
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0,-dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist  * cos(rad)/adjust_factor);
  gluCylinder(quadric, 0.5/adjust_factor, 0.5/adjust_factor, 4.0/adjust_factor, 12, 3);
  glPopMatrix();

  /* nariz */
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  glPushMatrix();
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0,-dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0, (4.0 + dist * cos(rad))/adjust_factor);
  
  gluCylinder(quadric, 0.5/adjust_factor, 0.0, 1.5/adjust_factor, 12, 3);
  glPopMatrix();

  /* cauda */
  glPushMatrix();
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0,-dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist  * cos(rad)/adjust_factor);
  glBegin(GL_POLYGON); 
  glTexCoord2fv(cta[0]); glVertex3fv(cauda[0]);
  glTexCoord2fv(cta[1]); glVertex3fv(cauda[1]);
  glTexCoord2fv(cta[2]); glVertex3fv(cauda[2]);
  glTexCoord2fv(cta[3]); glVertex3fv(cauda[3]);
  glEnd();
  glPopMatrix();


  /* cabine do piloto */

  glPushMatrix();

  glTranslatef(dist *sin(rad)/adjust_factor,0.0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0.0,- dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0.3/adjust_factor, (3.5  +  dist * cos(rad))/adjust_factor);
  glScalef(0.7,0.7,2.0);
  glColor4f(0.3,0.5,1,0.5);
  glDisable(GL_TEXTURE_2D);
  gluSphere(quadric,0.5/adjust_factor,12,12);
  glPopMatrix();

   glEndList();}

void display(void){
  glEnable(GL_DEPTH_TEST);
  
  glDepthMask(GL_TRUE);
  glClearColor(1.0,1.0,1.0,1.0);
  glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  compoe_jato();
  glPushMatrix();

  /* calcula a posicao do observador */
  obs[0]=raioxz*cos(2*PI*tetaxz/360)/adjust_factor;
  obs[2]=raioxz*sin(2*PI*tetaxz/360)/adjust_factor;
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,2.0,0.0);

  /* habilita/desabilita uso de texturas*/
  if(texturas){
    glEnable(GL_TEXTURE_2D);  
  }
  else{
    glDisable(GL_TEXTURE_2D);
  }

  glColor4f(COR_DO_PLANO);
  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
  glBindTexture(GL_TEXTURE_2D,textura_plano);
   
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(0,0,1.0);
  glTexCoord2fv(ctp[1]);  glVertex3f(1.0,0,1.0);
  glTexCoord2fv(ctp[2]);  glVertex3f(1.0,0,0.0);
  glTexCoord2fv(ctp[3]);  glVertex3f(0.0,0,0.0);
  glEnd();
  glTranslatef(0.0,0.4,0.0);

  glColor4f(COR_DO_AVIAO);
  glBindTexture(GL_TEXTURE_2D,textura_aviao);
  glCallList(jato);

  glPopMatrix();
  glutSwapBuffers();
}


void special(int key, int x, int y){
  switch (key) {
  case GLUT_KEY_UP:
    obs[1]=obs[1]+0.1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_DOWN:
    obs[1] =obs[1]-0.1;
    glutPostRedisplay();
    break;
  case GLUT_KEY_LEFT:
    tetaxz=tetaxz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    tetaxz=tetaxz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 't':
    texturas = !texturas;
    glutPostRedisplay();
    break;
  case 'r':
    raioxz=raioxz+1;
    glutPostRedisplay();
    break;
  case 'R':
    raioxz=raioxz-1;
    if(raioxz==0){
      raioxz=1;
    }
    glutPostRedisplay();
    break;
  
  case 'g':
    rot_angle = (rot_angle + 5) % 360;
    rad = ((float) rot_angle)/180.0 * PI;
  //  printf("%d\n", rot_aHEIGHTngle);
    printf("%f \n", rad) ;
    glutPostRedisplay();
    break;
  
  case 'f':
  // pra frente
    // printf("%f \n", dist *sin(rad)) ;
  
    if ((dist *sin(rad)/adjust_factor >= 0 && dist *sin(rad)/adjust_factor<= 1.2) && (dist *cos(rad)/adjust_factor >= 0 && dist *cos(rad)/adjust_factor <= 1.2 )){
     
         printf("%f \n", dist *cos(rad)) ;
      dist++;
    }
    else{
      dist=0.0;
    }
    
    glutPostRedisplay();
    break;
  }
}

void carregar_texturas(void){
  textura_plano = png_texture_load(TEXTURA_DO_PLANO, NULL, NULL);
  textura_aviao = png_texture_load(TEXTURA_DO_AVIAO, NULL, NULL);
}

void init(){
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  carregar_texturas();
  compoe_jato();
  glEnable(GL_TEXTURE_2D);
}


int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_ALPHA);

  if(!glutCreateWindow("Avião a jato")) {
    fprintf(stderr,"Error opening a window.\n");
    exit(-1);
  }

  init();
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 0;
}