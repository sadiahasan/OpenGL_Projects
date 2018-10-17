

#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <array>

/* makeCircle method
 * makes circle and puts in random spot on screen
 */

void makeCircle(float radius, float rX, float rY){
    double w = 0.0;
    double b = 1.0;
    bool con = rand() & 1; //random bool value to determine if concave or convex
    
    for(int i = 0; i < 100; i++){ //for loop to make circle out of lines
        float y = -radius + (i*2*radius) /100;
        float x = sqrt(radius*radius -(y*y));
        
        w=w+.01;
        b = 1.0 - w;
        
        if(con) { // convex
            glColor3f(w, w, w);
        }else{ //convex
            glColor3f(b, b, b);
        }
        glVertex2f(-x + rX, y -rY);
        glVertex2f(x + rX, y -rY);
    }
}

/*
 * noOverlap method
 * checks viability of each potentiol circle by checking that its center point is not within the diameter of any other circles already created
 */

bool noOverlap(float z, float x, float y, float r, float a[]){
    
    double distance;
    double diameter = 2*r+.2 * 10000;
    
    for(int j = 0; j < z*2; j+=2){
        double x1 = a[j];
        double y1 = a[j+1];
        distance = sqrt(((x-x1)*(x-x1)) + ((y-y1)*(y-y1))) * 10000;
        
        if((diameter >= distance) ){
            return 0;
        }
 }
    return 1;
 }

void display(void){
    
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);
    int t = 0;
    srand((unsigned)time(0));
    int randNum = rand() % (10 + 1 - 5) + 5; //random number between 5 - 10, determines how many circles are created
    
    float points[randNum*2]; //array to hold x,y coordinates of center point of each circle
    
    for(int i = 0; i < randNum*2; i++){
        points[i] = 0.0;
    }
    
    float radius = .122; //radius of the circles
    
    for(int i = 0; i < randNum; i++){ //for loop iterates for each circle for randNum
        
        float randX = rand()%9999; //random value for x
        randX = randX / 10000;
        bool randboolX = rand() & 1; //bool determines if x is positive or negative
            if(randboolX) randX = randX * -1;
        
        float randY = rand()%9999; //random value for y
        randY = randY / 10000;
        bool randboolY = rand() & 1; //bool determines if y is positive or negative
            if(randboolY) randY = randY *-1;
        
        if(noOverlap(randNum,randX, randY, radius, points)){ //if circle has no overlap add to array
            points[t++] = randX;
            points[t++] = randY;
            makeCircle(radius, randX, randY); //put circle on screen
        }
        else { //if circle will overlap decrease counter by 1
            i--;
        }
    }
    glEnd();
    glFlush();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 500);
    glutInitWindowPosition(200, 100);
    glutCreateWindow("circles");
    glClearColor(0.5, 0.5, 0.5, 0.1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-2.0, 2.0, -1.5, 1.5);
    glutDisplayFunc(display);
    glutMainLoop();
    
    
}
