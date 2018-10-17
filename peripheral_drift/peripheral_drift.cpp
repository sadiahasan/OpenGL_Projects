////
////

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <array>
#include <iostream>

GLfloat rectangle[4][3] = {{8,0,0},{8,30,0},{-8,30,0},{-8,0,0}};
GLboolean color = true;

void draw_rectangle(void){
    int b = 1;
    int w = 0;
    
    glBegin(GL_QUADS); //draw rectangles
    for(int i=0; i<4; i++){
       glVertex3fv(rectangle[i]);
    }
    glEnd();
    
    if(color){ //for alternating borders between rings
         b = 0;
         w = 1;
    }
    
    glLineWidth(4.0);
    
    glBegin(GL_LINE_STRIP); //half of rectangle's border
    glColor3d(b, b, b);
    glVertex2d(0, 0);
    glVertex2d(8, 0);
    glVertex2d(8, 30);
    glVertex2d(0, 30);
    glEnd();
    
    glBegin(GL_LINE_STRIP); //half of rectangle's border
    glColor3d(w, w, w);
    glVertex2d(0, 30);
    glVertex2d(-8, 30);
    glVertex2d(-8, 0);
    glVertex2d(0, 0);
    
    glEnd();
    
}

void draw_ring(void) {
    
    for(int r = 0; r<360; r+=45){ //draw ring of rectangles
        glColor3f(0.2f,0.28f,1.34f); //color for rectangle
        glPushMatrix();
        glRotated(r, 0, 0, 1); // rotate at 45 degree angle
        glTranslated(0, 35, 0);
        draw_rectangle();
        glPopMatrix();
    }
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    int n = 0;
    int y = 150;
    
    for(int i = 0; i < 8; i++){
     //   glColor3f(0.2f,0.28f,1.34f);
        glPushMatrix();
        color = !color; //to alternate borders between rings
        
        int x = -218 + (n * 150); //x position of rings
        n++;
        
        glTranslated(x, y, 0);
        draw_ring();
        glPopMatrix();
        
        if(x >= 232){ //reset for second row of rings
            n = 0;
            y = -120;
            color = !color;
        }
    }
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(700, 400);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("Peripheral Drift");
    glClearColor(126.0f /180.0f, 177.0f /180.0f, 1.0f /180.0f, 0.0); // color for background
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-300, 300, -300, 300, 0, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glutDisplayFunc(display);
    glutMainLoop();
}
