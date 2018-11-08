#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct Road {
	bool check;
	int x;
	int z;
}Road;
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

int road[100][5] = { {1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1},
					{1,1,1,1,1}, };

Road drawRoad[100][5];

void WalkingRobot();//�κ�
void keyboard(unsigned char key, int x, int y);//Ű����
void Timerfunction(int value);
int set = 0;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("Example2");// ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene);// ��� �Լ��� ����	
	glutTimerFunc(100, Timerfunction, 1);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

}// ������ ��� �Լ�

GLvoid drawScene(GLvoid)//�׸���
{
	if (set == 0) {
		//
		int tempZ = 0;
		for (int i = 0; i < 100; i++) {
			int tempX = -90;
			for (int j = 0; j < 5; j++) {
				drawRoad[i][j].x = tempX;
				drawRoad[i][j].z = tempZ;
				tempX += 45;
			}
			tempZ -= 45;
		}


		//
		set = 1;
	}
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 5; j++) {
			if (road[i][j] == 1) {
				glPushMatrix();
				glTranslatef(drawRoad[i][j].x, -100, drawRoad[i][j].z);
				glColor3f(1.0f, 1.0f, 0.5f);
				glScalef(1.0, 0.01, 1.0);
				glutSolidCube(40);
				glPopMatrix();
			}
		}
	}
	glPushMatrix();
	glTranslatef(0, -80, 0);
	glScalef(3, 3, 3);
	glRotatef(90, 0, 1, 0);
	WalkingRobot();

	glPopMatrix();
	glutSwapBuffers();
}

void WalkingRobot() {
	//�ٸ�1
	glPushMatrix();
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(0, 0, 1.5);
	glScalef(0.3, 1.0, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	// �ٸ�2
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(0, 0, -1.5);
	glScalef(0.3, 1.0, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	glPopMatrix();
	//����
	glPushMatrix();
	glColor3f(1.0f, 0.8f, 0.2f);
	glScalef(0.8, 1.0, 1);
	glutSolidCube(5);
	glPopMatrix();

	// ��1
	glTranslatef(0, 3, 0);
	glPushMatrix();
	//����
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -2, 0);
	glTranslatef(0, 0, 3.5);
	glScalef(0.3, 0.5, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	//�Ʒ���
	glTranslatef(0, -4, 0);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	// ��2
	//����
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -2, 0);
	glTranslatef(0, 0, -3.5);
	glScalef(0.3, 0.5, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	//�Ʒ���
	glTranslatef(0, -4, 0);
	glutSolidCube(4);
	glPopMatrix();

	// �Ӹ�
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(3);
	glPopMatrix();
	//��
	glPushMatrix();
	glTranslatef(2, 1, 0);
	glScalef(0.3, 0.3, 0.3);
	glColor3f(1.0f, 0, 0);
	glutSolidCube(3);
	glPopMatrix();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {

	}
	glutPostRedisplay();
}

void Timerfunction(int value) {
	
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(30, Timerfunction, 1); // Ÿ�̸��Լ� �� ����
}

GLvoid Reshape(int w, int h)
{
	//--- ����Ʈ ��ȯ ����
	glViewport(0, 0, w, h);
	// ���� ��� ���� �缳��
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// �� �� ��� ���� �缳��
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}