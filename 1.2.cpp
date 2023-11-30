#include <GL/glut.h>
#include <iostream>
#include <cmath>

using namespace std;

int centerX = -1, centerY = -1; // Tọa độ tâm của đường tròn
int radius = 0;               // Bán kính của đường tròn
bool isCenterSelected = false;



void Put8Pixel(int xc, int yc, int x, int y) {
    glBegin(GL_POINTS);

    glColor3f(1.0, 0.0, 0.0); // Đỏ cho điểm thứ 1
    glVertex2i(x + xc, y + yc);

    glColor3f(0.0, 1.0, 0.0); // Xanh lá cho điểm thứ 2
    glVertex2i(y + xc, x + yc);

    glColor3f(0.0, 0.0, 1.0); // Xanh dương cho điểm thứ 3
    glVertex2i(y + xc, -x + yc);

    glColor3f(1.0, 1.0, 0.0); // Vàng cho điểm thứ 4
    glVertex2i(x + xc, -y + yc);

    glColor3f(0.0, 1.0, 1.0); // Cyan cho điểm thứ 5
    glVertex2i(-x + xc, -y + yc);

    glColor3f(1.0, 0.0, 1.0); // Tím cho điểm thứ 6
    glVertex2i(-y + xc, -x + yc);

    glColor3f(0.5, 0.5, 0.5); // Xám cho điểm thứ 7
    glVertex2i(-y + xc, x + yc);

    glColor3f(1.0, 0.5, 0.0); // Cam cho điểm thứ 8
    glVertex2i(-x + xc, y + yc);

    glEnd();
}
void CircleMidpoint(int xc, int yc, int r) {
    int x, y, p;
    x = 0; y = r; p = 5 / 4 - r;
    while (x <= y) {
        Put8Pixel(xc, yc, x, y);
        if (p < 0) p += 2 * x + 3; //chon diem p
        else { //chon diem s
            p += 2 * (x - y) + 5;
            y--;
        }
        x++;
    }
}

void CircleBresenham(int xc, int yc, int r) {
    int x, y, p;
    x = 0; y = r; p = 3 - 2 * r;
    while (x <= y) {
        Put8Pixel(xc, yc, x, y);
        if (p < 0) p += 4 * x + 6; // chon diem p
        else { // chon diem s
            p += 4 * (x - y) + 10;
            y--;
        }
        x++;
    }
}



void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);

    if (isCenterSelected) {
        CircleMidpoint(centerX, centerY, radius);
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
        else {
            // Click lần thứ hai để chọn bán kính từ tâm đến đường tròn
            int newCenterX = mouseX;
            int newCenterY = 500 - mouseY; // Đảm bảo hệ tọa độ ngược lại
            radius = sqrt((newCenterX - centerX) * (newCenterX - centerX) +
                (newCenterY - centerY) * (newCenterY - centerY));
            glutPostRedisplay();
        }
    }
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Circle Drawing Algorithm");

    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500);

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}
