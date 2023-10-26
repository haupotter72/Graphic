#include <math.h>
#include <time.h>
#include <GL/glut.h>

void init()
{
    glClearColor(2.0,1.0,1.0,0.0);
    glOrtho(0,640,0,480,-1,1);
}

//H�m nhan v�o toa do(x, y) cua diem can t�, m�u sac muon t� (fillColor) v� m�u bi�n (bc).
void bound_it(int x, int y, float* mauCanTo, float* mauBien)
{
    float mauHienTai[3];//Mang mauHienTai c� k�ch thuoc 3 duoc sd de luu tru m�u sac cua diem(x, y)
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,mauHienTai);//read gtri m�u sac cua diem anh tai toa do(x, y).
    if((mauHienTai[0]!=mauBien[0] || mauHienTai[1]!=mauBien[1] || mauHienTai[2]!=mauBien[2])&&(
     mauHienTai[0]!=mauCanTo[0] || mauHienTai[1]!=mauCanTo[1] || mauHienTai[2]!=mauCanTo[2]))
     {//ktra xem m�u sac cua diem (x, y) c� kh�c m�u bi�n (bc) v� kh�c m�u mauCanTo
	 //hay kh�ng. Neu thoa m�n dkien n�y, tuc l� diem (x, y) chua duoc 
	 //t� m�u v� kh�ng phai m�u bi�n hoac fill color, ch�ng ta tien h�nh t� m�u.
        glColor3f(mauCanTo[0],mauCanTo[1],mauCanTo[2]);//Thiet lap m�u fill color bang glColor3f.
        glBegin(GL_POINTS);//Bat dau ve c�c diem
            glVertex2i(x,y);//Ve 1 diem tai (x, y)
        glEnd();//Ket th�c ve
        glFlush();//�am bao c�c lenh ve duoc thuc hien ngay lap tuc
        //Goi de quy de t� m�u c�c diem l�n can cua(x, y).
        //goi bound_it cho c�c diem l�n can (x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1).
        bound_it(x+1,y,mauCanTo,mauBien);//b�n phai cua (x, y)
        bound_it(x-1,y,mauCanTo,mauBien);//b�n tr�i cua (x, y)
        bound_it(x,y+1,mauCanTo,mauBien);//ph�a tr�n (x, y)
        bound_it(x,y-1,mauCanTo,mauBien);//ph�a duoi (x, y)
    }
//Khi h�m bound_it duoc goi de quy cho c�c diem l�n can, qu� tr�nh t� m�u se tiep tuc 
//cho den khi kh�ng c�n diem n�o ph� hop voi dkien ktra, tuc l� kh�ng c�n diem 
//chua duoc t� m�u v� kh�ng phai m�u bi�n hoac mauCanTo
}

void mouse(int btn, int state, int x, int y)
{
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)//ktra xem n�t chuot b�n tr�i d� duoc nhan hay kh�ng.
    {
        if(state==GLUT_DOWN)//ktra xem trang th�i cua n�t chuot l� nhan xuong (GLUT_DOWN) hay kh�ng.
        {
            float bCol[] = {1,0,0};//dai dien cho m�u do (red).
            float color[] = {0,0,1};//dai dien cho m�u xanh duong (blue).\
            //H�m bound_it duoc goi voi c�c tham so l� toa do chuot (x, y) v� m�u fillcolor l� color, m�u bi�n l� bCol.
            bound_it(x,y,color,bCol);
        }
    }
}

void mydisplay(){
//ve 1 h�nh da gi�c kh�ng deu
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1,0,0);
    glBegin(GL_LINE_LOOP);
        glVertex2i(400,400);
        glVertex2i(300,400);
        glVertex2i(150,200);
        glVertex2i(10,300);
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
	
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(0,0);
    glutCreateWindow("Boundary Fill");
    glutDisplayFunc(mydisplay);
    glutMouseFunc(mouse);
    init();
    glutMainLoop();
    return 0;
}
