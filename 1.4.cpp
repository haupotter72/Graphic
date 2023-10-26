#include <GL/glut.h>
#include <math.h>


void display(double x1, double y1, double x2, double y2) {
    // Đặt màu cho điểm (đây là màu trắng)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_LINES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glEnd();
    glFlush();
}

double fx(double x) {
    return sin(x);
    //return (7 * x * x + 7 * x + 7);
}

void curve(int a, int b) {
    double x = a;
    int n = 100;
    double dx = 40 / (b - a);
    while (x < b) {
        display(x, fx(x), x + dx, fx(x + dx));
        x = x + dx;
    }
}

void initPlay() {
    curve(-15, 15);
}



int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Cài đặt chế độ hiển thị
    glutInitWindowSize(350, 350); // Cài đặt kích thước cửa sổ
    glutCreateWindow("Ve"); // Tạo cửa sổ
    glOrtho(-30, 30, -30, 30, -30, 30);
    glutDisplayFunc(initPlay); // Đăng ký hàm vẽ
    glutMainLoop(); // Bắt đầu vòng lặp chính của GLUT

    return 0;
}
