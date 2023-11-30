#include <math.h>
#include <time.h>
#include <GL/glut.h>

void init()
{
    glClearColor(2.0,1.0,1.0,0.0);
    glOrtho(0,640,0,480,-1,1);
}

//Hàm nhan vào toa do(x, y) cua diem can tô, màu sac muon tô (fillColor) và màu biên (bc).
void bound_it(int x, int y, float* mauCanTo, float* mauBien)
{
    float mauHienTai[3];//Mang mauHienTai có kích thuoc 3 duoc sd de luu tru màu sac cua diem(x, y)
    glReadPixels(x,y,1.0,1.0,GL_RGB,GL_FLOAT,mauHienTai);//read gtri màu sac cua diem anh tai toa do(x, y).
    if((mauHienTai[0]!=mauBien[0] || mauHienTai[1]!=mauBien[1] || mauHienTai[2]!=mauBien[2])&&(
     mauHienTai[0]!=mauCanTo[0] || mauHienTai[1]!=mauCanTo[1] || mauHienTai[2]!=mauCanTo[2]))
     {//ktra xem màu sac cua diem (x, y) có khác màu biên (bc) và khác màu mauCanTo
	 //hay không. Neu thoa mãn dkien này, tuc là diem (x, y) chua duoc 
	 //tô màu và không phai màu biên hoac fill color, chúng ta tien hành tô màu.
        glColor3f(mauCanTo[0],mauCanTo[1],mauCanTo[2]);//Thiet lap màu fill color bang glColor3f.
        glBegin(GL_POINTS);//Bat dau ve các diem
            glVertex2i(x,y);//Ve 1 diem tai (x, y)
        glEnd();//Ket thúc ve
        glFlush();//Ðam bao các lenh ve duoc thuc hien ngay lap tuc
        //Goi de quy de tô màu các diem lân can cua(x, y).
        //goi bound_it cho các diem lân can (x + 1, y), (x - 1, y), (x, y + 1), (x, y - 1).
        bound_it(x+1,y,mauCanTo,mauBien);//bên phai cua (x, y)
        bound_it(x-1,y,mauCanTo,mauBien);//bên trái cua (x, y)
        bound_it(x,y+1,mauCanTo,mauBien);//phía trên (x, y)
        bound_it(x,y-1,mauCanTo,mauBien);//phía duoi (x, y)
    }
//Khi hàm bound_it duoc goi de quy cho các diem lân can, quá trình tô màu se tiep tuc 
//cho den khi không còn diem nào phù hop voi dkien ktra, tuc là không còn diem 
//chua duoc tô màu và không phai màu biên hoac mauCanTo
}

void mouse(int btn, int state, int x, int y)
{
    y = 480-y;
    if(btn==GLUT_LEFT_BUTTON)//ktra xem nút chuot bên trái dã duoc nhan hay không.
    {
        if(state==GLUT_DOWN)//ktra xem trang thái cua nút chuot là nhan xuong (GLUT_DOWN) hay không.
        {
            float bCol[] = {1,0,0};//dai dien cho màu do (red).
            float color[] = {0,0,1};//dai dien cho màu xanh duong (blue).\
            //Hàm bound_it duoc goi voi các tham so là toa do chuot (x, y) và màu fillcolor là color, màu biên là bCol.
            bound_it(x,y,color,bCol);
        }
    }
}

void mydisplay(){
//ve 1 hình da giác không deu
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
