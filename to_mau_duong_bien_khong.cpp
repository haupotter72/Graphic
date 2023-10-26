#include <GL/glut.h>
#include <vector>
#include <iostream>

struct Point {
    int x, y;
    Point(int _x, int _y) : x(_x), y(_y) {}
};

std::vector<Point> polygonVertices;

void drawLine(int x1, int y1, int x2, int y2) {
    glBegin(GL_LINES);
    glVertex2i(x1, y1);
    glVertex2i(x2, y2);
    glEnd();
}

void drawPolygon() {
    int numVertices = polygonVertices.size();

    for (int i = 0; i < numVertices - 1; i++) {
        drawLine(polygonVertices[i].x, polygonVertices[i].y, polygonVertices[i + 1].x, polygonVertices[i + 1].y);
    }

    // Connect the last vertex to the first vertex
    drawLine(polygonVertices[numVertices - 1].x, polygonVertices[numVertices - 1].y, polygonVertices[0].x, polygonVertices[0].y);
}

void floodFill(int x, int y, float interiorColor[3], float borderColor[3]) {
    std::vector<Point> stack;
    stack.push_back(Point(x, y));

    while (!stack.empty()) {
        Point current = stack.back();
        stack.pop_back();

        if (current.x < 0 || current.x >= glutGet(GLUT_WINDOW_WIDTH) || current.y < 0 || current.y >= glutGet(GLUT_WINDOW_HEIGHT)) {
            continue;  // Skip points outside the window
        }

        float currentColor[3];
        glReadPixels(current.x, current.y, 1, 1, GL_RGB, GL_FLOAT, currentColor);

        if (currentColor[0] == borderColor[0] && currentColor[1] == borderColor[1] && currentColor[2] == borderColor[2]) {
            continue;  // Skip border pixels
        }

        if (currentColor[0] != interiorColor[0] || currentColor[1] != interiorColor[1] || currentColor[2] != interiorColor[2]) {
            // If the current pixel is not filled with the interior color, fill it and add adjacent pixels to the stack
            glColor3fv(interiorColor);
            glBegin(GL_POINTS);
            glVertex2i(current.x, current.y);
            glEnd();
            glFlush();

            stack.push_back(Point(current.x + 1, current.y));
            stack.push_back(Point(current.x - 1, current.y));
            stack.push_back(Point(current.x, current.y + 1));
            stack.push_back(Point(current.x, current.y - 1));
        }
    }
}




void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        polygonVertices.push_back(Point(x, glutGet(GLUT_WINDOW_HEIGHT) - y));
        glutPostRedisplay();
    } else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        // Right click to start filling the polygon
        float interiorColor[] = {1.0, 1.0, 1.0};  // White interior color
        float borderColor[] = {1.0, 0.0, 0.0};  // Red border color

        // Filling the polygon using flood fill
        floodFill(polygonVertices[0].x, polygonVertices[0].y, interiorColor, borderColor);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);  // Red color for polygon boundary
    drawPolygon();
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Boundary Fill Algorithm");

    gluOrtho2D(0, 600, 0, 600);

    glutMouseFunc(mouseClick);
    glutDisplayFunc(display);

    glClearColor(0.0, 0.0, 0.0, 1.0);  // Black background

    glutMainLoop();
    return 0;
}

