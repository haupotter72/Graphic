#include <GL/glut.h>
#include <cmath>

GLuint g_sun;
GLuint g_earth;
GLuint g_moon;

GLfloat g_angle_day = 0.0;
GLfloat g_angle_year = 0.0;
GLfloat g_angle_moon = 0.0;
GLfloat g_speed = 0.5;
GLfloat g_zoom = 15.0;
GLfloat g_rotation_angle = 0.0;

void DrawOrbit(float radius) {
    glBegin(GL_LINE_LOOP); 				//bat dau ve = 1 chuoi cac doan thang
    for (int i = 0; i < 360; ++i) {
        float radian = i * M_PI / 180.0; 	//voi moi góc i thì tim dc r, x, y, z tuong ung
        float x = radius * cos(radian);
        float y = 0.0;
        float z = radius * sin(radian);
        glVertex3f(x, y, z);		//ve cac diem tai toa do xyz
    }
    glEnd();
}

GLuint MakeSphere(const GLfloat& radius, GLfloat r, GLfloat g, GLfloat b) {
    GLuint sphereDisplay;    			
    sphereDisplay = glGenLists(1);			//tao ds hien thi de luu tru cac lenh ve hinh cau
    glNewList(sphereDisplay, GL_COMPILE);
    GLfloat mat_diffuse[] = {r, g, b, 1.0};  // mang luu thong tin mau sac
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glutSolidSphere(radius, 64, 32);
    glEndList();
    return sphereDisplay;
}

void DrawLine(float x1, float y1, float x2, float y2) {
    glBegin(GL_LINES);
    glVertex3f(x1, y1, 0.0);
    glVertex3f(x2, y2, 0.0);
    glEnd();
}

void DrawEllipse(float a, float b) {
    glBegin(GL_LINE_LOOP);
    //khoi tao bien va tinh gia tri ban dau
    float x = 0, y = b;
    float d1 = b * b - a * a * b + 0.25 * a * a;
    float dx = 2 * b * b * x;
    float dy = 2 * a * a * y;
	//ve nua tren hinh elip
    while (dx < dy) {
        glVertex3f(x, y, 0.0); //ve cac diem hinh elip va doi xung qua truc xy
        glVertex3f(-x, y, 0.0);
        glVertex3f(x, -y, 0.0);
        glVertex3f(-x, -y, 0.0);

        x++;
	//tinh toa gia tri cua d1 de di chuyen den diem tiep theo
        if (d1 < 0) {
            dx += 2 * b * b;
            d1 += dx + b * b;
        } else {
            y--;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d1 += dx - dy + b * b;
        }
    }
	//tinh gia tri ban dau cho vong lap 2
    float d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
	//ve nua duoi elip
    while (y >= 0) {
        glVertex3f(x, y, 0.0);
        glVertex3f(-x, y, 0.0);
        glVertex3f(x, -y, 0.0);
        glVertex3f(-x, -y, 0.0);

        y--;

        if (d2 > 0) {
            dy -= 2 * a * a;
            d2 += a * a - dy;
        } else {
            x++;
            dx += 2 * b * b;
            dy -= 2 * a * a;
            d2 += dx - dy + a * a;
        }
    }

    glEnd();
}

void RenderScene() { //thiet lap goc nhin, vitri, quy dao cua vat the
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //xoa bo dem mau va bo dem do sau
    glLoadIdentity(); 	//thiet lap ma tran don vi

    gluLookAt(0.0, 0.0, g_zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(g_rotation_angle, 1.0f, 0.0f, 0.0f); //xoay sence theo goc g_ quanh truc x

    // Sun
    glPushMatrix();
glRotatef(g_angle_year, 0.0f, 1.0f, 0.0f);
    DrawOrbit(8.0);
    glCallList(g_sun);
    glPopMatrix();

    // Earth
    glPushMatrix();
    glRotatef(g_angle_year, 0.0f, 1.0f, 0.0f);
    glTranslated(8.0, 0.0, 0.0);
    glRotatef(g_angle_day, 0.0f, 1.0f, 0.0f);
    DrawOrbit(8.0);
    glCallList(g_earth);

    // Draw line from Earth to Moon
    float moonX = 8.0 + 2.0 * cos(g_angle_moon * M_PI / 180.0);
    float moonY = 2.0 * sin(g_angle_moon * M_PI / 180.0);
    DrawLine(8.0, 0.0, moonX, moonY);

    glPopMatrix();

    // Moon
    glPushMatrix();glRotatef(g_angle_year, 0.0f, 1.0f, 0.0f);
    glTranslated(8.0, 0.0, 0.0);
    glRotatef(g_angle_day, 0.0f, 1.0f, 0.0f);
    glRotatef(g_angle_moon, 0.0f, 1.0f, 0.0f);
    glTranslated(2.0, 0.0, 0.0);
    DrawOrbit(2.0);
    glCallList(g_moon);

    // Draw ellipse around Moon
    DrawEllipse(2.0, 0.2);

    glPopMatrix();

    glutSwapBuffers(); //hoan doi bufer hien thi
    glutPostRedisplay(); //thong bao cua anh sau moi lan cap nhat
}

void Reshape(int width, int height) {
    glViewport(0, 0, width, height); //cap nhat viewoort de phù hop voi kich thuoc moi cua cua so
    glMatrixMode(GL_PROJECTION); //chuyen sang ma tran chieu
    glLoadIdentity();  //dat ma tran chieu thanhh matran don vi
    float ratio = (float)width / (float)height; //tinh t? le khung hinh moi (r)
    gluPerspective(45.0, ratio, 1, 100.0); //cap nhat ma tran chieu de thich hop voi ti le khung hinh moi
    glMatrixMode(GL_MODELVIEW);//chuyen lai sang che do ma tran ...
}

void Init() {
    glClearColor(0.0, 0.0, 0.0, 0.0); //den
    glEnable(GL_DEPTH_TEST); //do sau
    glEnable(GL_LIGHTING); //chieu sang
    glEnable(GL_LIGHT0);

    GLfloat light_pos[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_pos); //thiet lap vi tri anh sang den so 0 tai toa do xyz

    // Sun
    g_sun = MakeSphere(2.0, 1.0, 1.0, 0.0);
    // Earth
    g_earth = MakeSphere(1.0, 0.0, 0.0, 1.0);
    // Moon
    g_moon = MakeSphere(0.2, 0.7, 0.7, 0.7);
}

void UpdateScene(int value) {
    g_angle_moon += 2.0 * g_speed;
    if (g_angle_moon >= 360.0) {
        g_angle_moon = 0.0;
    }

    g_angle_day += 0.5 * g_speed;
    if (g_angle_day >= 360.0) {
        g_angle_day = 0.0;
    }

    g_angle_year += 0.1 * g_speed;
    if (g_angle_year >= 360.0) {
        g_angle_year = 0.0;
    }

    glutPostRedisplay(); //ve lai canh (thay doi goc quay, vi tri moi)
    glutTimerFunc(16, UpdateScene, 0); 
}

void SpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            g_zoom -= 0.5;
            break;
        case GLUT_KEY_DOWN:
            g_zoom += 0.5;
            break;
        case GLUT_KEY_LEFT:
            g_rotation_angle += 5.0;
            break;
        case GLUT_KEY_RIGHT:
            g_rotation_angle -= 5.0;
            break;
    }

    glutPostRedisplay();
}

void Keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case '+':
            g_speed += 0.1;
break;
        case '-':
            g_speed -= 0.1;
            if (g_speed < 0.1) {
                g_speed = 0.1;
            }
            break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Mo phong vong quay mat troi");

    Init();
    glutReshapeFunc(Reshape);
    glutDisplayFunc(RenderScene);
    glutTimerFunc(25, UpdateScene, 0);
    glutSpecialFunc(SpecialKeys);
    glutKeyboardFunc(Keyboard);

    glutMainLoop();

    return 0;
}
