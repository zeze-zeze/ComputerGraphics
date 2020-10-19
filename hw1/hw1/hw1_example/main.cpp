#include "glut.h"
#include <iostream>

int WinNumber = NULL;                      //�Ψө�m�����N�X

int old_rot_x = 0;                       //����U�ƹ��ɪ������y��
int old_rot_y = 0;

int rot_x = 0;                           //�즲�᪺�۹�y�СA�γo�M�w�n����X��
int rot_y = 0;

int record_x = 0;                        //�����W�@�����઺����
int record_y = 0;

float distance = 0;                      //�b�����x�}(glTranslatef();)���ϥ�
float light_position[] = { -20, 20, 0 };  //��������m

void WindowSize(int, int);             //�t�d������ø�Ϥ��e�����
void Keyboard(unsigned char, int, int); //�����L��J
void Mouse(int, int, int, int);         //����ƹ����U�M��}�ɪ��T��
void MotionMouse(int, int);             //����ƹ����U�������T��
void Display(void);                      //�yø

void SetLightSource(void);               //�]�w�����ݩ�
void SetMaterial(void);                  //�]�w�����ݩ�

int main()
{
    printf("��w�Ms��վ㻷��\n��Esc��������{��\n");
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(400, 400);                     //�������e
    glutInitWindowPosition(600, 80);                  //�������W������m
    WinNumber = glutCreateWindow("test");   //�إߵ���

    //�U�����ӬO�Ψӫ��wCallback���
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
    glClearColor(1.0, 1.0, 1.0, 1.0);                            //�Υզ��I��
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPolygonMode(GL_FRONT, GL_FILL);                            //�]�w�����I���νu�����

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0, 0, 30.0, 0, 0, 0, 0, 1, 0);                    //���u���y�ФΤ�V
    glTranslatef(0, 0, distance);                               //�u��z�b����
    glRotatef((float)rot_y + (float)record_y, 1.0, 0.0, 0.0);   //�Hx�b�����b
    glRotatef((float)rot_x + (float)record_x, 0.0, 1.0, 0.0);   //�Hy�b�����b

    //�e�@�ӨS��������box
    glBegin(GL_QUADS);
    //����
    glNormal3f(0, 0, 1);        //�]�w�k�V�q
    glVertex3f(-7, 7, 7);
    glVertex3f(-7, -7, 7);
    glVertex3f(7, -7, 7);
    glVertex3f(7, 7, 7);
    //�I��
    glNormal3f(0, 0, -1);
    glVertex3f(-7, 7, -7);
    glVertex3f(7, 7, -7);
    glVertex3f(7, -7, -7);
    glVertex3f(-7, -7, -7);
    //�k����
    glNormal3f(1, 0, 0);
    glVertex3f(7, 7, 7);
    glVertex3f(7, -7, 7);
    glVertex3f(7, -7, -7);
    glVertex3f(7, 7, -7);
    //������
    glNormal3f(-1, 0, 0);
    glVertex3f(-7, 7, -7);
    glVertex3f(-7, -7, -7);
    glVertex3f(-7, -7, 7);
    glVertex3f(-7, 7, 7);
    //�W��
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
    glutPostRedisplay();            //�O������ø
}

void WindowSize(int w, int h)
{
    float rate;
    if (h == 0) h = 1;                        //����h���s�A�����i���ର�s��
    glViewport(0, 0, w, h);                 //��������e���ܮɡA�e���]�����
    rate = (float)w / (float)h;                //�e�������ܤF�A�����e���ܧ�

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, rate, 1.0, 500.0);   //�z����v

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void Mouse(int button, int state, int x, int y)
{
    if (state)
    {
        record_x += x - old_rot_x;
        record_y += y - old_rot_y;

        rot_x = 0;   //�S���k�s�|�����z�Q�����G
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

    glEnable(GL_LIGHTING);                                 //�}�O

    // �]�w�o���骺�������S��
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);      //���ҥ�(Ambient Light)
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);      //���g��(Diffuse Light)
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);     //�Ϯg��(Specular Light)

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);     //�����y��

    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);                               //�Ұʲ`�״���
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