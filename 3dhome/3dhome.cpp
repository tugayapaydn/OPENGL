// 3dhome.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<GL/glut.h>
using namespace std;

constexpr auto NO_VERTICES = 8;
constexpr auto NO_EDGES = 12;

constexpr auto NO_WINDOW_VERTICES = 4;
constexpr auto NO_WINDOW_EDGES = 4;

constexpr auto NO_DOOR_VERTICES = 4;
constexpr auto NO_DOOR_EDGES = 4;

constexpr auto NO_ROOF_VERTICES = 6;
constexpr auto NO_ROOF_EDGES = 8;

constexpr auto NO_CHIMNEY_VERTICES = 8;
constexpr auto NO_CHIMNEY_EDGES = 12;


/* Coordinates of home vertices */
float vertices[NO_VERTICES][3] = {{0.8, 0.8, 0.4},            
						{0.8, 0.2, 0.4},
						{-0.8, 0.2, 0.4},
						{-0.8, 0.8, 0.4},
						{-0.8, 0.8, -0.4},
						{0.8, 0.8, -0.4},
						{0.8, 0.2, -0.4},
						{-0.8, 0.2, -0.4}};

int edges[NO_EDGES][2] = {{0, 1}, {0, 3}, {2, 1}, {2, 3}, {0, 5}, {4, 3}, {4, 5}, {2, 7}, {6, 7}, {6, 1}, {6, 5}, {4, 7} };

/* Coordinates of chimney vertices */
float chimney_vertices[NO_CHIMNEY_VERTICES][3] = {  {-0.7, 1.2, -0.3},
                                                    {-0.5, 1.2, -0.3},
                                                    {-0.5, 1.2, -0.1},
                                                    {-0.7, 1.2, -0.1},
                                                    {-0.7, 0.8001, -0.1},
                                                    {-0.5, 0.8001, -0.1},
                                                    {-0.5, 0.8001, -0.3},
                                                    {-0.7, 0.8001, -0.3}};

int chimney_edges[NO_CHIMNEY_EDGES][2] = {  {0, 1}, {0, 3}, {0, 7}, {2, 1}, {2, 3}, {2, 5}, {4, 3}, {4, 7}, 
                                            {4, 5}, {6, 5}, {6, 7}, {6, 1}};

/* Coordinates of window vertices */
float window_vertices[NO_WINDOW_VERTICES][3] = {{0.0, 0.6, 0.41},
                              {0.0, 0.4, 0.41},
                              {0.6, 0.4, 0.41},
                              {0.6, 0.6, 0.41}};

int window_edges[NO_WINDOW_EDGES][2] = { {0,1}, {1,2}, {2,3}, {0,3}};

/* Coordinates of door vertices */
float door_vertices[NO_DOOR_VERTICES][3] = { {-0.6, 0.6, 0.41},
                              {-0.6, 0.2, 0.41},
                              {-0.4, 0.2, 0.41},
                              {-0.4, 0.6, 0.41} };

int door_edges[NO_DOOR_EDGES][2] = { {0,1}, {1,2}, {2,3}, {0,3} };

/* Coordinates of roof vertices */
float roof_vertices[NO_ROOF_VERTICES][3] = { {0.8, 0.8001, 0.43},
                              {-0.8, 0.8001, 0.43},
                              {-0.8, 0.8001, -0.40},
                              {0.8, 0.8001, -0.40},
                              {0.8, 1, -0.40},
                              {-0.8, 1, -0.40} };

int roof_edges[NO_ROOF_EDGES][2] = { {0,1}, {1,2}, {2,3}, {3,4}, {4,5}, {4, 0}, {5,2}, {5,1}};

/* Rotation angle values*/
float angle_x = 0.0f;
float angle_y = 0.0f;

/* Scale Rate */
float scale_rate = 1.0f;

/* Center points of the home */
float center_points[3] = { 0.0f, 0.5f, 0.0f };
float neg_center_points[3] = { 0.0f, -0.5f, 0.0f };

/* Transformation Rate */
float trans_points[3] = { 0.0f, 0.0f, 0.0f };

void keyboardHandler(unsigned char key, int x, int y) {
	if (key == 27) { // ESC KEY function
        exit(EXIT_SUCCESS);
    } 
}


/* Rotation, scaling and transformation activities are handled by keyboard input.
 * Keyboard UP:     Rotate up
 * Keyboard DOWN:   Rotate down
 * Keyboard LEFT:   Rotate left
 * Keyboard RIGHT:  Rotate right
 * 
 * F1:  Increase Scale Rate
 * F2:  Decrease Scale Rate
 * F5:  Move left (Decrease x coordinate)
 * F6:  Move right (Increase x coordinate)
 * F7:  Move Down (Decrease y coordinate)
 * F8:  Move Up (Increase y coordinate)
 */
void specialKeyboardHandler(int key, int x, int y) {
    if (key == GLUT_KEY_UP) {   //Up Arrow
        angle_x += 5.0f;
        angle_x = fmod(angle_x, 360);
    }
    else if (key == GLUT_KEY_DOWN) {   //Down Arrow
        angle_x -= 5.0f;
        angle_x = fmod(angle_x, 360);
    }
    else if (key == GLUT_KEY_RIGHT) {   //Right Arrow
        angle_y += 5.0f;
        angle_y = fmod(angle_y, 360);
    }
    else if (key == GLUT_KEY_LEFT) {   //Left Arrow
        angle_y -= 5.0f;
        angle_y = fmod(angle_y, 360);
    }
    else if (key == GLUT_KEY_F1) {
        scale_rate += 0.1;
    }
    else if (key == GLUT_KEY_F2) {
        scale_rate -= 0.1;
    } 
    else if (key == GLUT_KEY_F6) {
        trans_points[0] += 0.5;
    }
    else if (key == GLUT_KEY_F5) {
        trans_points[0] -= 0.5;
    }
    else if (key == GLUT_KEY_F8) {
        trans_points[1] += 0.5;
    }
    else if (key == GLUT_KEY_F7) {
        trans_points[1] -= 0.5;
    }
    glutPostRedisplay();
}

/* Resize window according to window size*/
void resizer(int width, int height) {
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)width / (double)height, 1.0, 200.0);
}

/* Main display algorithm that draws 3D Home */
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Set camera to a location (0,0.5,4)
    gluLookAt(0,0.5,4.0, center_points[0], center_points[1], center_points[2], 0, 1, 1);
    
    glPushMatrix();

    /* Transform the object according to transformation rate (which is changed by keyboard inputs (F5-F6-F7-F8))*/
    glTranslatef(trans_points[0], trans_points[1], trans_points[2]);

    /* Make rotations on the object according to rotation angle (which is changed by keyboard inputs (arrow keys)) 
     * Object is translated before and after rotation in order to rotate it around it's center. */
    glTranslatef(center_points[0], center_points[1], center_points[2]);
    
    // Rotate around y axis
    glRotatef(angle_y, 0.0f, 1.0f, 0.0f);
    // Rotate around x axis
    glRotatef(angle_x, 1.0f, 0.0f, 0.0f);
    // Rescale the object
    glScalef(scale_rate, scale_rate, scale_rate);

    glTranslatef(neg_center_points[0], neg_center_points[1], neg_center_points[2]);

    /* Construct 3D Home */
    glClear(GL_COLOR_BUFFER_BIT);

    /* Draw home base */
    glBegin(GL_POLYGON);
    glColor3f(0.9, 0.9, 0);
    for (size_t i = 0; i < NO_EDGES; i++) {
        for (size_t j = 0; j < 2; j++) {
            glVertex3f(vertices[edges[i][j]][0], vertices[edges[i][j]][1], vertices[edges[i][j]][2]);
        }
    }
    glEnd();

    /* Draw the window of the home */
    glBegin(GL_POLYGON);
    glColor3f(1, 0, 0);
    for (size_t i = 0; i < NO_WINDOW_EDGES; i++) {
        for (size_t j = 0; j < 2; j++) {
            glVertex3f(window_vertices[window_edges[i][j]][0], window_vertices[window_edges[i][j]][1], window_vertices[window_edges[i][j]][2]);
        }
    }
    glEnd();

    /* Draw the door of the home*/
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 1);
    for (size_t i = 0; i < NO_DOOR_EDGES; i++) {
        for (size_t j = 0; j < 2; j++) {
            glVertex3f(door_vertices[door_edges[i][j]][0], door_vertices[door_edges[i][j]][1], door_vertices[door_edges[i][j]][2]);
        }
    }
    glEnd();

    /* Draw the roof of the home*/
    glBegin(GL_POLYGON);
    glColor3f(0, 1, 0);
    for (size_t i = 0; i < NO_ROOF_EDGES; i++) {
        for (size_t j = 0; j < 2; j++) {
            glVertex3f(roof_vertices[roof_edges[i][j]][0], roof_vertices[roof_edges[i][j]][1], roof_vertices[roof_edges[i][j]][2]);
        }
    }
    glEnd();

    /* Draw the chimney of the home*/
    glBegin(GL_POLYGON);
    glColor3f(0.3, 0.3, 0.3);
    for (size_t i = 0; i < NO_CHIMNEY_EDGES; i++) {
        for (size_t j = 0; j < 2; j++) {
            glVertex3f(chimney_vertices[chimney_edges[i][j]][0], chimney_vertices[chimney_edges[i][j]][1], chimney_vertices[chimney_edges[i][j]][2]);
        }
    }
    glEnd();

    glFlush();
    glPopMatrix();
    glutSwapBuffers();
}


/* Main algorithm to start construction of 3D home*/
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        
    /* Set initial window size */
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);

    glutCreateWindow("My House");
    glEnable(GL_DEPTH_TEST);

    /* Set display function and keyboard handlers */
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboardHandler);
    glutSpecialFunc(specialKeyboardHandler);

    /* Set resizer function*/
    glutReshapeFunc(resizer);
    glutMainLoop();
    return 0;
}
