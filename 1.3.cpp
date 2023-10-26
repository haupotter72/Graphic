#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int centerX = -1, centerY = -1; // Tọa độ tâm của ellipse
int radiusX = 0, radiusY = 0;   // Bán kính theo trục X và Y
bool isCenterSelected = false;
bool isFirstRadiusSelected = false;

void Put4Pixel(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);
    glColor3f(0.0, 0.0, 1.0);
    glVertex2i(x + xc, y + yc);
    glColor3f(0.0, 1.0, 0.0);
    glVertex2i(x + xc, -y + yc);
    glColor3f(1.0, 0.0, 0.0);
    glVertex2i(xc - x, yc - y);
    glColor3f(1.0, 1.0, 1.0);
    glVertex2i(xc - x, yc + y);
    glEnd();
}

void ElipMidpoint(int xc, int yc, int a, int b) {
    int x, y; float x0, y0, a2, b2, p;
    a2 = a * a; b2 = b * b;
    x0 = (int)(a2 / sqrt(a2 + b2)); y0 = (int)(b2 / sqrt(a2 + b2));
    p = b2 - a2 * b + (1 / 4) * a2; x = 0; y = b;
    while (x <= x0) {
        Put4Pixel(xc, yc, x, y);
        if (p < 0) p += (2 * x + 3) * b2;
        else {
            p += (2 * x + 3) * b2 - 2 * a2 * (y - 1);
            y--;
        }
        
        x++;
    }
    x = a; y = 0; p = a2 - a * b2 + (1 / 4) * b2;
    while (y <= y0) {
        Put4Pixel(xc, yc, x, y);
        if (p < 0)
            p += a2 * (2 * y + 3);
        else {
            p += (2 * y + 3) * a2 - 2 * b2 * (x - 1);
            x--;
        }
        y++;
    }
}
void ElipBresenham(int xc, int yc, int a, int b) {
    double x, y, p, x0, y0, a2, b2;
    a2 = a * a; b2 = b * b;
    x = 0; y = b; p = -2 * b + 1 + 2 * b2 / (a2);
    x0 = a2 / (sqrt(a2 + b2)); y0 = b2 / (sqrt(a2 + b2));
    while (x <= x0) {
        Put4Pixel(xc, yc, x, y);
        if (p < 0) p += 2 * b2 * (2 * x + 3) / a2;
        else {
            p += 4 * (1 - y) + 2 * b2 * (2 * x + 3) / a2;
            y--;
        }
        x++;
    }
    x = a; y = 0; p = 2 * a2 / b2 - 2 * a + 1;
    while (y <= y0) {
        Put4Pixel(xc, yc, x, y);
        if (p < 0) p += 2 * a2 * (2 * y + 3) / b2;
        else {
            p += 4 * (1 - x) + 2 * a2 * (2 * y + 3) / b2;
            x--;
        }
        y++;
    }
}





void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    if (isFirstRadiusSelected) {
        ElipMidpoint(centerX, centerY, radiusX, radiusY);
    }

    glFlush();
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (!isCenterSelected) {
            // Click lần đầu để chọn tâm
            centerX = mouseX;
            centerY = 500 - mouseY; // Đảm bảo hệ tọa độ ngược lại
            isCenterSelected = true;
        }
        else if (!isFirstRadiusSelected) {
            // Click lần thứ hai để chọn bán kính theo trục X
            int newRadiusX = abs(mouseX - centerX);
            radiusX = newRadiusX;
            isFirstRadiusSelected = true;
        }
        else {
            // Click lần thứ ba để chọn bán kính theo trục Y
            int newRadiusY = abs(500 - mouseY - centerY);
            radiusY = newRadiusY;
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Ellipse Drawing Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
