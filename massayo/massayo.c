#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PI 3.14159265


const int n_orbs = 8;

typedef struct Orb
{
  GLfloat r, g, b;
  GLfloat radius, orb_radius, angle, grow;
  GLfloat x_velocity, y_velocity, z_velocity;

} orb;

typedef struct Names
{
  char *name;
} names;



orb orbs[n_orbs] = {{241/255.0, 250/255.0, 140/255.0,0.7f, 0.0f, 0.0f, 0.0f, 0.0f,0.0f,-8.0f},
                   {1.0, 85/255.0, 85/255.0,0.1f, 1.1f, 0.0f, 0.05f, 0.0f,1.1f,-8.0f},
                   {139/255.0, 233/255.0, 253/255.0,0.15f, 1.5f, 0.0f, 0.03f, 0.0f,1.5f,-8.0f},
                    {1.0, 121.0/255.0, 198/255.0,0.25f, 2.2f, 0.0f, 0.02f, 0.0f,2.2f,-8.0f},
                   {80.0/255.0, 250.0/255.0, 123.0/255.0,0.2f, 2.8f, 0.0f, 0.045f, 0.0f,2.8f,-8.0f},
                    {1.0, 184.0/255.0, 108.0/255.0, 0.07f, 3.2f, 0.0f, 0.01f,  0.0,3.2f,-8.0f},
                   {189.0/255.0, 147.0/255.0, 249.0/255.0,0.05f, 0.45f, 0.0f, 0.05f, 0.0f,1.75f, -8.0f},
                   {189.0/255.0, 147.0/255.0, 249.0/255.0,0.03f, 0.3f, 0.0f, 0.05f, 0.0f,2.20f, -7.7f}};


names orb_names[] =  { {"Biu"}, {"Antares"}, {"Jacintinho"}, {"Ufal"}, {"Txosa"},
  {"Riacho Doce"}, {"Dor"}, {"Sofrimento"} };


void init (void)
{
    glutInitWindowSize (1000, 1000);
    glutCreateWindow ("Massayo");
    glutInitDisplayMode (GLUT_DEPTH);
    glEnable (GL_DEPTH_TEST);
    glMatrixMode (GL_MODELVIEW);
    glClear (GL_COLOR_BUFFER_BIT);
    glLoadIdentity ();
}

void _move (int value)
{


  for (int i = 1; i < n_orbs; i++)
    {
      if (orbs[i].angle + orbs[i].grow < 2)
	{

	  if (i == 6)
	    {
	      orbs[i].x_velocity = orbs[3].x_velocity;
	      orbs[i].y_velocity =
		orbs[3].y_velocity -
		cos (orbs[i].angle * PI) * orbs[i].orb_radius;
	      orbs[i].z_velocity =
		sin (orbs[i].angle * PI) * orbs[i].orb_radius - 8.0;

	    }
	  else if (i == 7)
	    {
	      orbs[i].x_velocity =
		orbs[3].x_velocity -
		sin (orbs[i].angle * PI) * orbs[i].orb_radius;
	      orbs[i].y_velocity =
		orbs[3].y_velocity -
		sin (orbs[i].angle * PI) * orbs[i].orb_radius;
	      orbs[i].z_velocity =
		cos (orbs[i].angle * PI) * orbs[i].orb_radius - 7.7;

	    }
	  else
	    {
	      orbs[i].x_velocity =
		sin (orbs[i].angle * PI) * orbs[i].orb_radius;

	      orbs[i].y_velocity =
		cos (orbs[i].angle * PI) * orbs[i].orb_radius;
	    }

	  orbs[i].angle += orbs[i].grow;
	}
      else
	orbs[i].angle = 0;
    }


  glutPostRedisplay ();
}


void _names ()
{
  for (int i = 0; i < n_orbs; i++)
    {
      glColor3f (248 / 255.0, 248 / 255.0, 242 / 255.0);
      glRasterPos3f (orbs[i].x_velocity + orbs[i].radius * 0.7,
		     orbs[i].y_velocity + orbs[i].radius * 0.7, -7.7f);


      int len = (int) strlen (orb_names[i].name);

      for (int j = 0; j < len; j++)
	{
	  glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12,
			       orb_names[i].name[j]);
	}
    }

  glutPostRedisplay ();

}


void _go (unsigned char key, int x, int y)
{

  if (key == 'y')
    _move (1);

}

void _drawStars(void){


  for (int i = 0; i < 150; i++)
    {
      glBegin (GL_POINTS);
      float x = 20.0 * (random()/ ((double)RAND_MAX + 1)) - 10;
      float y = 20.0 * (random()/ ((double)RAND_MAX + 1)) - 10;

      glColor3d (248.0 / 255.0, 248.0 / 255.0, 242.0 / 255.0);

      glVertex3f(x, y, -7.7f);

      glEnd ();
    }

}

void _drawSystem (void)
{

  for (int i = 0; i < n_orbs; i++)
    {

      glPushMatrix ();

      glTranslatef (orbs[i].x_velocity, orbs[i].y_velocity,
		    orbs[i].z_velocity);
      glColor3f (orbs[i].r, orbs[i].g, orbs[i].b);

      glScalef (1.0, 1.0, 1.0);

      glutSolidSphere (orbs[i].radius, 20, 20);

      glPopMatrix ();

    }

}

void _drawCircle (void)
{
  for (int j = 1; j < n_orbs - 2; j++)
    {
      glBegin (GL_LINE_LOOP);

      glColor3d (248 / 255.0, 248 / 255.0, 242 / 255.0);

      for (int i = 0; i <= 100; i++)
	{
	  glVertex3f ((orbs[j].orb_radius * cos (i * 2.0f * PI / 100)),
		      (orbs[j].orb_radius * sin (i * 2.0f * PI / 100)),
		      -8.0f);
	}

      glEnd ();
    }
}

void display (void)
{
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  _drawCircle ();
  _drawSystem ();
  _names ();
  _drawStars ();
  glutSwapBuffers ();
}


void reshape (int x, int y)
{
  if (y == 0 || x == 0)
    return;

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective (45, (GLdouble) x / (GLdouble) y, 0.6, 21.0);
  glMatrixMode (GL_MODELVIEW);
  glViewport (0, 0, x, y);
  glClearColor (40.0 / 255.0, 42.0 / 255.0, 54.0 / 255.0, 1.0);

}


int main (int argc, char **argv)
{
  glutInit (&argc, argv);

  init ();
  glutDisplayFunc (display);
  glutReshapeFunc (reshape);
  glutKeyboardFunc (_go);
  glutMainLoop ();
  return 0;
}
