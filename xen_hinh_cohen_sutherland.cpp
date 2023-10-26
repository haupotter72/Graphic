#include <GL/glut.h>

int windowWidth = 600;
int windowHeight = 600;
int x1, y1, x2, y2;
int rectX1, rectY1, rectX2, rectY2;

#define INSIDE 0
#define LEFT 1
#define RIGHT 2
#define BOTTOM 4
#define TOP 8

int computeOutCode(int x, int y) {
    int code = INSIDE;

    if (x < rectX1)
        code |= LEFT;
    else if (x > rectX2)
        code |= RIGHT;

    if (y < rectY1)
        code |= BOTTOM;
    else if (y > rectY2)
        code |= TOP;

    return code;
}

void cohenSutherlandClip(int &x1, int &y1, int &x2, int &y2) {
    int outcode1 = computeOutCode(x1, y1);
    int outcode2 = computeOutCode(x2, y2);
    bool accept = false;

    while (true) {
        if (!(outcode1 | outcode2)) { // Trivially accept
            accept = true;
            break;
        } else if (outcode1 & outcode2) { // Trivially reject
            break;
        } else {
            int x, y;


            // Select the endpoint outside the clip window
            int outcodeOut = outcode1 ? outcode1 : outcode2;

            // Find intersection point
            if (outcodeOut & TOP) {
                x = x1 + (x2 - x1) * (rectY2 - y1) / (y2 - y1);
                y = rectY2;
            } else if (outcodeOut & BOTTOM) {
                x = x1 + (x2 - x1) * (rectY1 - y1) / (y2 - y1);
                y = rectY1;
            } else if (outcodeOut & RIGHT) {
                y = y1 + (y2 - y1) * (rectX2 - x1) / (x2 - x1);
                x = rectX2;
            } else if (outcodeOut & LEFT) {
                y = y1 + (y2 - y1) * (rectX1 - x1) / (x2 - x1);
                x = rectX1;
            }

            // Move outside point to intersection point to clip
            if (outcodeOut == outcode1) {
                x1 = x;
                y1 = y;
                outcode1 = computeOutCode(x1, y1);
            } else {
                x2 = x;
                y2 = y;
                outcode2 = computeOutCode(x2, y2);
            }
        }
    }

    if (accept) {
        glColor3f(0.0, 1.0, 0.0); // Màu xanh lá cây cho do?n th?ng dã xén
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        glFlush();
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Màu d? cho hình ch? nh?t g?c
    glBegin(GL_LINE_LOOP);
    glVertex2i(rectX1, rectY1);
    glVertex2i(rectX2, rectY1);
    glVertex2i(rectX2, rectY2);
    glVertex2i(rectX1, rectY2);
    glEnd();

    glColor3f(1.0, 0.0, 0.0); // Màu d? cho do?n th?ng g?c
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();

    glFlush();
}

void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = x;
        y1 = windowHeight - y; // Ð?o ngu?c t?a d? y
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        x2 = x;
        y2 = windowHeight - y; // Ð?o ngu?c t?a d? y

        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(1.0, 0.0, 0.0); // Màu d? cho hình ch? nh?t g?c
        glBegin(GL_LINE_LOOP);
        glVertex2i(rectX1, rectY1);
        glVertex2i(rectX2, rectY1);
        glVertex2i(rectX2, rectY2);
        glVertex2i(rectX1, rectY2);
        glEnd();

        glColor3f(1.0, 0.0, 0.0); // Màu d? cho do?n th?ng g?c
        glBegin(GL_LINES);
        glVertex2i(x1, y1);
        glVertex2i(x2, y2);
        glEnd();
        glFlush();

        cohenSutherlandClip(x1, y1, x2, y2);
    }
}

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    gluOrtho2D(0, windowWidth, 0, windowHeight);

    rectX1 = 200;
    rectY1 = 200;
    rectX2 = 400;
    rectY2 = 400;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Cohen-Sutherland Line Clipping");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);

    glutMainLoop();

    return 0;
}

