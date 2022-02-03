#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include "png_texture.h"

#define PI 3.1415

#define COORD_tex_airplane 1.0
#define COR_DO_PLANO 1.0,1.0,1.0,1.0
#define COR_DO_AVIAO 1.0,1.0,1.0,1.0
#define TEXTURA_DO_PLANO "mcz.png"
#define TEXTURA_DO_AVIAO "camuflagem.png"

GLfloat ambient[] = {0.5,0.5,0.5,1.0}; 
GLfloat diffuse[] = {0.8,0.8,0.8,1.0};
GLfloat light_position[] = {0.5, 2.0,0.5, 1.0};
GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
GLfloat spec_material[] = {1.0,1.0,1.0,1.0}; 
GLint shininess = 90;

GLint WIDTH =800;
GLint HEIGHT=600;

GLfloat adjust_factor = 50;
GLfloat obs[3]={0.0,2.0/adjust_factor,0.0};
GLfloat look[3]={0.0,1.0/adjust_factor,0.0};
GLuint  tex_plane;
GLuint  tex_airplane;

GLshort texturas=1;
GLfloat txz=0;
GLfloat xz=6;
GLuint  jato;

int rot_angle = 0;
GLfloat dist = 0;
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
  {-COORD_tex_airplane,-COORD_tex_airplane},
  {+COORD_tex_airplane,-COORD_tex_airplane},
  {+COORD_tex_airplane,+COORD_tex_airplane},
  {-COORD_tex_airplane,+COORD_tex_airplane}
};

void ilum(void){

    glShadeModel (GL_SMOOTH);
    glMaterialfv (GL_FRONT,GL_SPECULAR, spec_material);
    glMateriali (GL_FRONT,GL_SHININESS,shininess);
    glLightModelfv (GL_LIGHT_MODEL_AMBIENT, ambient);

    glLightfv (GL_LIGHT0, GL_AMBIENT, ambient); 

    glLightfv (GL_LIGHT0, GL_DIFFUSE, diffuse );
    glLightfv (GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv (GL_LIGHT0, GL_POSITION, light_position);

}

void reshape(int width, int height){
  WIDTH=width;
  HEIGHT=height;
  glViewport(0,0,(GLint)width,(GLint)height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(70.0,width/(float)height,0.1,10.0);
  glMatrixMode(GL_MODELVIEW);
}

void _drawAirplane(void){
  GLUquadricObj *quadric;

  /* inicia a composicao do jato */
  jato = glGenLists(1);
  glNewList(jato, GL_COMPILE);

  // Asas
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

  // Tronco
  glPushMatrix();
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0,-dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist  * cos(rad)/adjust_factor);
  gluCylinder(quadric, 0.5/adjust_factor, 0.5/adjust_factor, 4.0/adjust_factor, 12, 3);
  glPopMatrix();

  // Bico
  quadric = gluNewQuadric();
  gluQuadricTexture(quadric, GL_TRUE);
  glPushMatrix();
  glTranslatef(dist *sin(rad)/adjust_factor,0,dist * cos(rad)/adjust_factor);
  glRotatef (rot_angle, 0.0, 1.0, 0.0);
  glTranslatef(-dist *sin(rad)/adjust_factor,0,-dist * cos(rad)/adjust_factor);
  glTranslatef(dist *sin(rad)/adjust_factor,0, (4.0 + dist * cos(rad))/adjust_factor);
  
  gluCylinder(quadric, 0.5/adjust_factor, 0.0, 1.5/adjust_factor, 12, 3);
  glPopMatrix();

  // Cauda
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


  // Vidro
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
  _drawAirplane();
  glPushMatrix();

  obs[0]=xz*cos(2*PI*txz/360)/adjust_factor;
  obs[2]=xz*sin(2*PI*txz/360)/adjust_factor;
  gluLookAt(obs[0],obs[1],obs[2],look[0],look[1],look[2],0.0,2.0,0.0);

  glEnable(GL_TEXTURE_2D);  

  glColor4f(COR_DO_PLANO);
  glBindTexture(GL_TEXTURE_2D,tex_plane);
   
  glBegin(GL_QUADS);
  glTexCoord2fv(ctp[0]);  glVertex3f(0,0,1.0);
  glTexCoord2fv(ctp[1]);  glVertex3f(1.0,0,1.0);
  glTexCoord2fv(ctp[2]);  glVertex3f(1.0,0,0.0);
  glTexCoord2fv(ctp[3]);  glVertex3f(0.0,0,0.0);
  glEnd();
  glTranslatef(0.0,0.2,0.0);

  glColor4f(COR_DO_AVIAO);
  glBindTexture(GL_TEXTURE_2D,tex_airplane);
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
    txz=txz+2;
    glutPostRedisplay();
    break;
  case GLUT_KEY_RIGHT:
    txz=txz-2;
    glutPostRedisplay();
    break;
  }
}

void keyboard(unsigned char key, int x, int y){
  switch (key) {
  case 27:
    exit(0);
    break;
  case 'e':
    xz++;
    glutPostRedisplay();
    break;
  case 'd':
    xz--;
    if(xz==0){
      xz=1;
    }
    glutPostRedisplay();
    break;
  
  case 'g':
    rot_angle = (rot_angle + 5) % 360;

    rad = ((float) rot_angle)/180.0 * PI;

    glutPostRedisplay();
    break;

  case 'h':
    rot_angle = (rot_angle - 5) % 360;   
    rad = ((float) rot_angle)/180.0 * PI;

    glutPostRedisplay();
    break;
  
  case 'f':
  
    if ((dist *sin(rad)/adjust_factor >= 0 && dist *sin(rad)/adjust_factor<= 1.0) && (dist *cos(rad)/adjust_factor >= 0 && dist *cos(rad)/adjust_factor <= 1.0 )){
      dist+=1.0/adjust_factor;
    }
    else{
      dist=0.0;
    }
    
    glutPostRedisplay();
    break;
  

  case 'v':

    if ((dist *sin(rad)/adjust_factor >= 0 && dist *sin(rad)/adjust_factor<= 1.0) && (dist *cos(rad)/adjust_factor >= 0 && dist *cos(rad)/adjust_factor <= 1.0 )){
      dist-=1.0/adjust_factor;
    }
    else{
      dist=0.0;
    }
    
    glutPostRedisplay();
    break;
  }
}

void loadTex(void){
  tex_plane = png_texture_load(TEXTURA_DO_PLANO, NULL, NULL);
  tex_airplane = png_texture_load(TEXTURA_DO_AVIAO, NULL, NULL);
}

void init(){
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_BLEND);
    
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_LIGHTING);  
  glEnable(GL_LIGHT0);
  glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
  ilum();
  loadTex();
  _drawAirplane();
  
  glEnable(GL_TEXTURE_2D);
}


int main(int argc,char **argv){
  glutInitWindowPosition(0,0);
  glutInitWindowSize(WIDTH,HEIGHT);
  glutInit(&argc,argv);
  glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE|GLUT_ALPHA);
  glutCreateWindow ("Voo");
  init();
  
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(special);
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();

  return 0;
}