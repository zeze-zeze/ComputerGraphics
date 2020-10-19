#include "glut.h"
#include <iostream>

int WinNumber = NULL;                      //用來放置視窗代碼

int old_rot_x = 0;                       //剛按下滑鼠時的視窗座標
int old_rot_y = 0;

int rot_x = 0;                           //拖曳後的相對座標，用這決定要旋轉幾度
int rot_y = 0;

int record_x = 0;                        //紀錄上一次旋轉的角度
int record_y = 0;

float distance = 0;                      //在平移矩陣(glTranslatef();)中使用
float light_position[] = { -20, 20, 0 };  //光源的位置

void WindowSize(int, int);             //負責視窗及繪圖內容的比例
void Keyboard(unsigned char, int, int); //獲取鍵盤輸入
void Mouse(int, int, int, int);         //獲取滑鼠按下和放開時的訊息
void MotionMouse(int, int);             //獲取滑鼠按下期間的訊息
void Display(void);                      //描繪

void SetLightSource(void);               //設定光源屬性
void SetMaterial(void);                  //設定材質屬性

int main()
{
    printf("按w和s鍵調整遠近\n用Esc鍵來關閉程式\n");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);                     //視窗長寬
    glutInitWindowPosition(600, 80);                  //視窗左上角的位置
    WinNumber = glutCreateWindow("test");   //建立視窗

    //下面五個是用來指定Callback函數
    glutReshapeFunc(WindowSize);
    glutKeyboardFunc(Keyboard);
    glutMouseFunc(Mouse);
    glutMotionFunc(MotionMouse);
    glutDisplayFunc(Display);

    SetLightSource();
    SetMaterial();

    glutMainLoop();

    return 0;
}

void Display(void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);                            //用白色塗背景
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);                            //設定面的背面用線條顯示

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 30.0, 0, 0, 0, 0, 1, 0);                    //視線的座標及方向
    glTranslatef(0, 0, distance);                               //沿著z軸平移
    glRotatef((float)rot_y + (float)record_y, 1.0, 0.0, 0.0);   //以x軸當旋轉軸
    glRotatef((float)rot_x + (float)record_x, 0.0, 1.0, 0.0);   //以y軸當旋轉軸

    //畫一個沒有底面的box
    glBegin(GL_QUADS);
    //正面
    glNormal3f(0, 0, 1);        //設定法向量
    glVertex3f(-7, 7, 7);
    glVertex3f(-7, -7, 7);
    glVertex3f(7, -7, 7);
    glVertex3f(7, 7, 7);
    //背面
    glNormal3f(0, 0, -1);
    glVertex3f(-7, 7, -7);
    glVertex3f(7, 7, -7);
    glVertex3f(7, -7, -7);
    glVertex3f(-7, -7, -7);
    //右側面
    glNormal3f(1, 0, 0);
    glVertex3f(7, 7, 7);
    glVertex3f(7, -7, 7);
    glVertex3f(7, -7, -7);
    glVertex3f(7, 7, -7);
    //左側面
    glNormal3f(-1, 0, 0);
    glVertex3f(-7, 7, -7);
    glVertex3f(-7, -7, -7);
    glVertex3f(-7, -7, 7);
    glVertex3f(-7, 7, 7);
    //上面
    glNormal3f(0, 1, 0);
    glVertex3f(-7, 7, -7);
    glVertex3f(-7, 7, 7);
    glVertex3f(7, 7, 7);
    glVertex3f(7, 7, -7);

    glNormal3f(0, -1, 0);
    glVertex3f(-7, -7, 7);
    glVertex3f(7, -7, 7);
    glVertex3f(7, -7, -7);
    glVertex3f(-7, -7, -7);
    glEnd();

    glutSwapBuffers();
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
        distance += 1;
        break;
    case 's':
        distance -= 1;
        break;
    case 27:
        glDisable(GL_LIGHT0);
        glDisable(GL_LIGHTING);
        glDisable(GL_DEPTH_TEST);
        glutDestroyWindow(WinNumber);
        exit(0);
        break;
    }
    glutPostRedisplay();            //令視窗重繪
}

void WindowSize(int w, int h)
{
    float rate;
    if (h == 0) h = 1;                        //阻止h為零，分母可不能為零啊
    glViewport(0, 0, w, h);                 //當視窗長寬改變時，畫面也跟著變
    rate = (float)w / (float)h;                //畫面視野變了，但內容不變形

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, rate, 1.0, 500.0);   //透視投影

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Mouse(int button, int state, int x, int y)
{
    if (state)
    {
        record_x += x - old_rot_x;
        record_y += y - old_rot_y;

        rot_x = 0;   //沒有歸零會有不理想的結果
        rot_y = 0;
    }
    else
    {
        old_rot_x = x;
        old_rot_y = y;
    }
}

void MotionMouse(int x, int y)
{
    rot_x = x - old_rot_x;
    rot_y = y - old_rot_y;
    glutPostRedisplay();
}

void SetLightSource()
{
    float light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);                                 //開燈

    // 設定發光體的光源的特性
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);      //環境光(Ambient Light)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);      //散射光(Diffuse Light)
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);     //反射光(Specular Light)

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);     //光的座標

    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);                               //啟動深度測試
}

void SetMaterial()
{
    float material_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
    float material_diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
    float material_specular[] = { 0.2, 0.2, 0.2, 1.0 };

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
}