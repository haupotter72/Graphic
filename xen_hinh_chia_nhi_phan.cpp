#include <GL/glut.h>

int windowWidth = 600;
int windowHeight = 600;
int x1, y1, x2, y2;
bool drawRectangle = false;

void drawRectangleWithMouse(int x, int y) {
    if (drawRectangle) {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0); // Red color for the rectangle
        glBegin(GL_LINE_LOOP);
        glVertex2i(x1, y1);
        glVertex2i(x, y1);
        glVertex2i(x, y);
        glVertex2i(x1, y);
        glEnd();
        glFlush();
    }
}

void cropRectangle(int x1, int y1, int x2, int y2) {
    glColor3f(0.0, 1.0, 0.0); // Green color for the cropped rectangle
    glBegin(GL_LINE_LOOP);
    glVertex2i(x1, y1);
    glVertex2i(x2, y1);
    glVertex2i(x2, y2);
    glVertex2i(x1, y2);
    glEnd();
    glFlush();
}





void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    if (drawRectangle) {
        glColor3f(1.0, 0.0, 0.0); // Red color for the rectangle
        glBegin(GL_LINE_LOOP);
        glVertex2i(x1, y1);
        glVertex2i(x2, y1);
        glVertex2i(x2, y2);
        glVertex2i(x1, y2);
        glEnd();
    }


    glFlush();
}





void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = x;
        y1 = windowHeight - y; // Invert y-coordinate
        drawRectangle = true;
    } else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        x2 = x;
        y2 = windowHeight - y; // Invert y-coordinate
        drawRectangleWithMouse(x2, y2);
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN && drawRectangle) {
        int cropX = x;
        int cropY = windowHeight - y; // Invert y-coordinate
        drawRectangle = false;
        cropRectangle(x1, y1, cropX, cropY);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Binary Division Cropping");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}

