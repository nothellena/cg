#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI 3.14159265

typedef struct Vertex
{
    GLfloat x, y;
    GLfloat r, g, b;
} Vertex;

// Vertex and color for each square
Vertex vertices[] = {
    {10.0f, 50.0f, 0.0f, 1.0f, 1.0f},
    {70.0f, 50.0f, 0.0f, 0.0f, 1.0f},
    {130.0f, 50.0f, 0.0f, 1.0f, 0.0f},
    {190.0f, 50.0f, 1.0f, 1.0f, 0.0f},
    {250.0f, 50.0f, 1.0f, 0.0f, 0.0f},
    {310.0f, 50.0f, 0.0f, 0.0f, 0.0f},
    {370.0f, 50.0f, 1.0f, 0.0f, 1.0f},
    {430.0f, 50.0f, 1.0f, 1.0f, 1.0f}};

// Square's size
GLsizei side_size = 50;

// Auxiliar variable to update cossine function value
int x_cos_func = 0;

/**
 * Description: Updates position of each square. The calculation for
    the new positions is based on the cos(x) function.
 */
void update(int value)
{

    int tmp = x_cos_func;

    for (int i = 0; i < 8; i++)
    {

        if (2 * round(cos(tmp * PI / 180.0) * 100) > 0)
        {
            vertices[i].y = 2 * round(cos(tmp * PI / 180.0) * 100);
        }

        tmp += 10;
    }
    x_cos_func += 10;

    glutPostRedisplay();
}

/**
 * Description: Draws squares.
 */
void _wave(void)
{

    glClear(GL_COLOR_BUFFER_BIT);

    for (int i = 0; i < 8; i++)
    {
        glBegin(GL_QUADS);

        GLfloat x = vertices[i].x;
        GLfloat y = vertices[i].y;
        GLint r = vertices[i].r;
        GLint g = vertices[i].g;
        GLint b = vertices[i].b;

        glVertex2i(x, y + side_size);
        glVertex2i(x, y);
        glVertex2i(x + side_size, y);
        glVertex2i(x + side_size, y + side_size);

        glColor3d(r, g, b);

        glEnd();
    }

    
}

/**
 * @param key: pressed key.
 * 
 * Description: Run wave.
 */
void _go(unsigned char key, int x, int y)
{

    if (key == 't')
    {
        update(1);
    }
}

/**
 * @param s: string.
 * 
 * Description: Prints string on screen.
 */
void _msg(const char *s)
{

    glRasterPos2f(100.0f, 400.0f);
    glColor3f(1.0f, 1.0f, 1.0f);

    int len = (int)strlen(s);

    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }

}

void display(void)
{
    _wave();
    _msg("Aperte t para iniciar o Tchakabum :)");  

    glutSwapBuffers();
}

void init(void)
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutCreateWindow("Onda, onda, olha a onda!");

    glClearColor(1.0f, 0.5f, 0.0f, 0.0f);
    gluOrtho2D(0.0f, 500, 0.0f, 500);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);

    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(_go);
    glutMainLoop();
}