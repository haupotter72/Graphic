#include <GL/glut.h>
#include <iostream>

using namespace std;
 
int x1, y1, x2, y2;


void display(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}
void LineBres(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dy;
    const2 = 2 * (Dy - Dx);
    P = 2 * Dy - Dx;
    x = x1; y = y1;
    while (x <= x2) {
        display(x, y);
        if (P < 0) {
            P += const1;
        }
        else {
            P += const2;
            y++;
        }
        x++;
    }
    
} 
void LineMidPoint(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1; Dy = y2 - y1;
    const1 = 2 * Dy;
    const2 = 2 * (Dy - Dx);
    P = 2 * Dy - Dx; x = x1;
    y = y1;
    while (x <= x2) {
        display(x, y);
        if (P < 0) {
            P += const1;
        }
        else {
            P += const2;
            y++;
        }
        x++;
    }
}

// Với  m > 1
void LineBresTren(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dx;
    const2 = 2 * (Dx - Dy);
    P = 2 * Dx - Dy;
    x = x1;
    y = y1;
    while (y <= y2) {
        display(x, y);
        if (P < 0) {
            P = P + const1;
        }
        else {
            P = P + const2;
            x++;
        }
        y++;
    }
    
}
void LineMidPointTren(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dx;
    const2 = 2 * (Dy - Dx);
    P = Dy - 2 * Dx;
    x = x1;
    y = y1;
    while (y <= y2) {
        display(x, y);
        if (P > 0) {
            P -= const1;
        }
        else {
            P += const2;
            x++;
        }
        y++;
    }
}
// Với -1 < m < 0:
void LineBresAm(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dy;
    const2 = 2 * (Dy + Dx);
    P = 2 * Dy + Dx;
    x = x1;
    y = y1;
    while (x <= x2) {
        display(x, y);
        if (P < 0) {
            P -= const1;
        }
        else {
            P -= const2;
            y--;
        }
        x++;
    }
}
void LineMidPointAm(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dy;
    const2 = 2 * (Dx - Dy);
    P = 2 * Dy - Dx;
    x = x1;
    y = y1;
    while (x <= x2) {
        display(x, y);
        if (P < 0) {
            P += const2;
        }
        else {
            P -= const1;
            y--;
        }
        x++;
    }
}
// Với m < -1:
void LineBresDuoi(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dx;
    const2 = 2 * (Dx + Dy);
    P = 2 * Dx + Dy;
    x = x1; y = y1;
    while (y >= y2) {
        display(x, y);
        if (P < 0) {
            P += const1;
        }
        else {
            P += const2;
            x++;
        }
        y--;
    }
}

void LineMidPointDuoi(int x1, int x2, int y1, int y2) {
    int Dx, Dy, P, x, y, const1, const2;
    Dx = x2 - x1;
    Dy = y2 - y1;
    const1 = 2 * Dx;
    const2 = 2 * (Dx - Dy);
    P = 2 * Dx - Dy;
    x = x1;
    y = y1;
    while (y > y2) {
        display(x, y);
        if (P < 0) {
            P += const1;
        }
        else {
            x++;
            P += const2;
        } y--;
    }
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0); // Màu vẽ là trắng

    if (x1 != -1 && x2 != -1 && y1 != -1 && y2 != -1) {
        int dx = x2 - x1;
        int dy = y2 - y1;

        float m = (float)dy / dx;

        if (m >= 0 && m <= 1) {
            // Trường hợp 0 <= m <= 1
            LineBres(x1, x2, y1, y2);
        }
        else if (m > 1) {
            // Trường hợp m > 1
            LineBresTren(x1, x2, y1, y2);
        }
        else if (m >= -1 && m < 0) {
            // Trường hợp -1 <= m < 0
            LineBresAm(x1, x2, y1, y2);
        }
        else if (m < -1) {
            // Trường hợp m < -1
            LineBresDuoi(x1, x2, y1, y2);
        }
    }
    glFlush();
    
    
}

void mouse(int button, int state, int mouseX, int mouseY) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Lưu tọa độ điểm đầu và điểm cuối khi click chuột
        if (x1 == -1) {
            x1 = mouseX;
            y1 = 500 - mouseY; // Đảm bảo hệ tọa độ ngược lại
        }
        else {
            x2 = mouseX;
            y2 = 500 - mouseY; // Đảm bảo hệ tọa độ ngược lại
            glutPostRedisplay();
        }
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500); // Kích thước cửa sổ
    glutCreateWindow("Bresenham & Midpoint Line Drawing Algorithms");

    glClearColor(0.0, 0.0, 0.0, 0.0);//thiet lap che do mau
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 500, 0, 500); // thiet lap toa do ve

    x1 = y1 = x2 = y2 = -1;

    glutDisplayFunc(display);
    glutMouseFunc(mouse);

    glutMainLoop();
    return 0;
}




































