#include <GL/gl.h>
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#define SIN_60 0.86602540378
#define PI 3.14159265

float angular_vel = PI / 4;

typedef struct Vertex
{
    GLfloat x, y;

} Vertex;

Vertex petals[] = {
    {50.0f, SIN_60 * 100},
    {-50.0f,  SIN_60 * 100},
    {100.0f, 0.0f},
    {50.0, - SIN_60 * 100},
    {-100.0f, 0.0f},
    {-50.0, -SIN_60 * 100}};

Vertex stalk[] = {
    {-5.0, 0.0},
    {5.0, 0.0},
    {-5.0, -200.0},
    {5.0, -200.0}
};

void rotate(float angle){
    
    Vertex previous;

    for (int i = 0; i < 6; i = i + 2)
    {

        for (int j = i; j < i + 2; j++)
        {   previous = petals[j];

            petals[j].x = previous.x * cos(angle) - previous.y * sin(angle);
            petals[j].y = previous.y * cos(angle) + previous.x * sin(angle); 
        }   
       
    }
    glutPostRedisplay();
}

void velocity(int value){

    float change = angular_vel + value * PI / 16;

    if (change >= PI / 16 && change <= PI)
        angular_vel = change;    

}

void _go(unsigned char key, int x, int y)
{

    if (key == 'e')
    {
        rotate(angular_vel);
    }

    if (key == 'd')
    {
        rotate(-angular_vel);
    }

    if (key == 'r'){
        velocity(1);
    }

    if (key == 'l'){
        velocity(-1);
    }
}

void _flower(){
    glClear(GL_COLOR_BUFFER_BIT);
        for (int i = 0; i < 6; i = i + 2)
    {

        glBegin(GL_TRIANGLES);
        glColor3d(1.0f, 0.0f, 0.0f); 
        // Center
        glVertex2f(0.0f,0.0f);

        for (int j = i; j < i + 2; j++)
        {   
            GLfloat x = petals[j].x;
            GLfloat y = petals[j].y;

            glVertex2f(x,y);             
                      
        }   
        glEnd();
       
    }

}

void _stalk(){

    for (int i=0; i<2; i++){
        glBegin(GL_TRIANGLES);
        glColor3d(1.0, 1.0, 0.0);  

        for (int j=i; j < i + 3; j++){
        

        GLfloat x = stalk[j].x;
        GLfloat y = stalk[j].y;

        glVertex2i(x, y);
        }

        glEnd();
        
    }

}

void _msg(const char *s, float x, float y)
{

    glRasterPos2f(x, y);

    int len = (int)strlen(s);

    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, s[i]);
    }

}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
    _stalk();
    _flower();
    _msg("Girar: E - esquerda, D - Direita", -350.0, 200.0);
    _msg("Velocidade: R - mais rapido, L - mais lento", -350.0, 170.0);
    glutSwapBuffers();
    
}

void init(void){
    glClearColor(0.0f, 1.0f, 1.0f, 0.0f);
    glutReshapeWindow(400, 400);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-400, 400, -400, 400);
}

int main(int argc, char **argv){

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Flor de abril");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(_go);
    glutMainLoop();

    return 0;
}