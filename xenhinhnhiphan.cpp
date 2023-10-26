#include <GL/glut.h>
#include <stdio.h>

int winWidth = 800;
int winHeight = 600;
int x1, y1, x2, y2;
int clip_xmin = 100;
int clip_ymin = 100;
int clip_xmax = 400;
int clip_ymax = 400;

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0); // Red color

    // Draw the clip window
    glBegin(GL_LINE_LOOP);
    glVertex2i(clip_xmin, clip_ymin);
    glVertex2i(clip_xmax, clip_ymin);
    glVertex2i(clip_xmax, clip_ymax);
    glVertex2i(clip_xmin, clip_ymax);
    glEnd();

    // Draw the line segment
    glColor3f(0.0, 0.0, 1.0); // Blue color
    drawLine(x1, y1, x2, y2);

    glutSwapBuffers();
}

void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        x1 = x;
        y1 = winHeight - y; // Invert y-coordinate
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP) {
        x2 = x;
        y2 = winHeight - y; // Invert y-coordinate

        // Clip the line against the window
        int xmin = clip_xmin;
        int ymin = clip_ymin;
        int xmax = clip_xmax;
        int ymax = clip_ymax;

        if (x1 < xmin && x2 < xmin) {
            // Both endpoints are to the left of the clip window
            return;
        }
        if (x1 > xmax && x2 > xmax) {
            // Both endpoints are to the right of the clip window
            return;
        }
        if (y1 < ymin && y2 < ymin) {
            // Both endpoints are below the clip window
            return;
        }
        if (y1 > ymax && y2 > ymax) {
            // Both endpoints are above the clip window
            return;
        }

        // Clipping logic (Cohen-Sutherland algorithm)
        if (x1 < xmin) {
            y1 = y1 + (y2 - y1) * (xmin - x1) / (x2 - x1);
            x1 = xmin;
        }
        if (x1 > xmax) {
            y1 = y1 + (y2 - y1) * (xmax - x1) / (x2 - x1);
            x1 = xmax;
        }
        if (y1 < ymin) {
            x1 = x1 + (x2 - x1) * (ymin - y1) / (y2 - y1);
            y1 = ymin;
        }
        if (y1 > ymax) {
            x1 = x1 + (x2 - x1) * (ymax - y1) / (y2 - y1);
            y1 = ymax;
        }

        if (x2 < xmin) {
            y2 = y2 + (y1 - y2) * (xmin - x2) / (x1 - x2);
            x2 = xmin;
        }
        if (x2 > xmax) {
            y2 = y2 + (y1 - y2) * (xmax - x2) / (x1 - x2);
            x2 = xmax;
        }
        if (y2 < ymin) {
            x2 = x2 + (x1 - x2) * (ymin - y2) / (y1 - y2);
            y2 = ymin;
        }
        if (y2 > ymax) {
            x2 = x2 + (x1 - x2) * (ymax - y2) / (y1 - y2);
            y2 = ymax;
        }

        glutPostRedisplay();
    }
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, static_cast<double>(w), 0.0, static_cast<double>(h));
    winWidth = w;
    winHeight = h;
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("XEN HINH NHI PHAN");

    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutReshapeFunc(reshape);

    glClearColor(1.0, 1.0, 1.0, 1.0); // White background color

    glutMainLoop();
    return 0;
}
//xén hình nh? phân
