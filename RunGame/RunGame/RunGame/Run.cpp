#include <GL/freeglut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define NUM 1000

typedef struct Road {
	int x;
	int z;
}sRoad;
int road[NUM][5];
/*
int road[100][5] = { {1,2,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,2},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,2,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,1,1},
{1,1,1,2,1},
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
*/

GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);

GLvoid menuScreen(GLvoid);

sRoad drawRoad[NUM][5];

int mouseX = 0;
int mouseY = 0;

int TileInterval = 45;
int set = 0;   // �����Է� Ȯ�ο�

int menu = 0;   // �޴� ( 0 = �ʱ�ȭ�� / 1 = ����ȭ�� )
int level = 4;   // ���� ( 1 = 18���� / 2 = 21���� / 3 = 24����)

int moveX = 0;   // ĳ���� x�� Ȯ�� ����
float charX = 0;// ĳ���� x ��ġ

float RoadSpeed = 0;   // �ð� ����

float StudentAngle = 0;   //��,�ٸ�,�Ӹ����� ����
int StudentTemp = 0;   //�л� ���� Ȯ�� ����

void keyboard(unsigned char key, int x, int y);//Ű����

void Roadsetting(); // �� �迭���� �Է�
void RandomRoad(); // ��ֹ� ��������
void Student();//�κ�

void RoadTimer(int value);   //���μӵ�����
void CharTimer(int value);   //ĳ���ͼӵ�����
void MenuTimer(int value);   //�޴� ����Ȯ�ο�
void Road();
void collide();
bool survive = true;
int inRect(int x, int y, int rectx1, int recty1, int rectx2, int recty2); // ������,�簢�� �浹üũ

int main(int argc, char* argv[])
{
	Roadsetting();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // ���÷��� ��� ���� 
	glutInitWindowPosition(100, 100); // �������� ��ġ���� 
	glutInitWindowSize(800, 600); // �������� ũ�� ����
	glutCreateWindow("RunGame");// ������ ���� (������ �̸�)
	glutDisplayFunc(drawScene);// ��� �Լ��� ����   
	glutTimerFunc(10, RoadTimer, 1);
	glutTimerFunc(5, CharTimer, 1);
	glutTimerFunc(100, MenuTimer, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

}// ������ ��� �Լ�

GLvoid drawScene(GLvoid)//�׸���
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // �������� 'black' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�

	if (menu == 0) {
		glPushMatrix();

		glColor3f(1.0f, 1.0f, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		glutSolidCube(100);
		glPopMatrix();

	}
	else if (menu == 1) {
		glPushMatrix();

		glRotatef(3 * moveX, 0, 1, 0); // �л� ��ġ�� ���� �� ��üȸ��

		Road();      //���� & ������ �׸���
		Student();   //�л� �׸���

		glPopMatrix();
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		printf("��ŷ\n");
		for(int i=0;i<10;i++)
		{
		printf("%d.\n",i);
		}
		if (level < 3) level += 1;
		break;
	case '-':
		if (level > 1)level -= 1;
		break;
	case 'a':
		if (survive) {
			moveX -= 1;
			if (moveX < -2) moveX += 1;
		}
		break;
	case 'd':
		if (survive) {
			moveX += 1;
			if (moveX > 2) moveX -= 1;
		}
		break;
	case '1':
		menu = 1;
		RoadSpeed = 0;
		survive = true;
		RandomRoad();
		break;
	case '`':
		menu = 0;
		survive = false;
		break;
	}
	glutPostRedisplay();
}

void RoadTimer(int value) {
	if (survive && menu == 1) {
		RoadSpeed += 1 * level;
	}
	collide();
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(10, RoadTimer, 1); // Ÿ�̸��Լ� �� ����
}
void CharTimer(int value) {
	if (survive && menu == 1) {
		if (moveX == 2) {
			if (charX < 80) charX++;
		}
		if (moveX == 1) {
			if (charX < 40) charX++;
			if (charX > 40) charX--;
		}
		if (moveX == 0) {
			if (charX < 0) charX++;
			if (charX > 0) charX--;
		}
		if (moveX == -1) {
			if (charX > -40) charX--;
			if (charX < -40) charX++;
		}
		if (moveX == -2) {
			if (charX > -80) charX--;
		}

		if (StudentTemp == 0) {
			StudentAngle += 0.2 * level;
			if (StudentAngle > 30) StudentTemp = 1;
		}
		else if (StudentTemp == 1) {
			StudentAngle -= 0.2 * level;
			if (StudentAngle < -30) StudentTemp = 0;
		}
	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, CharTimer, 1); // Ÿ�̸��Լ� �� ����
}
void MenuTimer(int value) {
	if (menu == 0) {

	}
	glutPostRedisplay(); // ȭ�� �� ���
	glutTimerFunc(1, MenuTimer, 1); // Ÿ�̸��Լ� �� ����
}
void collide() {
	double range = 10; // �浹����
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < 5; j++) {
			if (road[i][j] == 2) {
				if (inRect(charX - range, 100 - range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range) ||
					inRect(charX - range, 100 + range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range) ||
					inRect(charX + range, 100 - range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range) ||
					inRect(charX + range, 100 + range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range)) {
					//�浹��
					survive = false;
				}

			}
		}
	}
}
int inRect(int x, int y, int rectx1, int recty1, int rectx2, int recty2) {
	if ((x >= rectx1 && x <= rectx2) && (y >= recty1 && y <= recty2))
		return 1;
	else return 0;
}

void Roadsetting() {
	if (set == 0) {
		int tempZ = 70;
		for (int i = 0; i < NUM; i++) {
			int tempX = -TileInterval * 2;
			for (int j = 0; j < 5; j++) {
				drawRoad[i][j].x = tempX;
				drawRoad[i][j].z = tempZ;
				tempX += TileInterval;
			}
			tempZ -= TileInterval;
		}
		set = 1;
	}

}
void RandomRoad() {
	srand(time(NULL));
	for (int i = 0; i < NUM; i++) {

		for (int j = 0; j < 5; j++) {
			road[i][j] = 1;
		}

		if (i % 7 == 0 && i != 0) {
			int count = 0; // ��ֹ� ���� 0���� �ʱ�ȭ
			while (count < level) {
				for (int j = 0; j < 5; j++) {
					if (road[i][j] != 2) {
						int a = rand() % 2;
						if (a == 1) {
							road[i][j] = 2;
							count++;
							if (count == level) break;
						}
					}
				}
			}
		}


	}
}

void Road() {
	glPushMatrix();
	
	for (int i = 0; i < NUM; i++) {
		if (drawRoad[i][2].z + RoadSpeed < 200 && drawRoad[i][2].z + RoadSpeed > -1000) {
			for (int j = 0; j < 5; j++) {
				// �Ϲ� ��
				if (road[i][j] == 1) {
					glPushMatrix();
					glTranslatef(drawRoad[i][j].x, -100, drawRoad[i][j].z + RoadSpeed); // RoadSpeed ���� ���� �ӵ� ����
					glColor3f(1.0f, 1.0f, 1.0f);
					glScalef(1.0, 0.01, 1.0);
					glutSolidCube(40);
					glPopMatrix();
				}
				// ���� ��( ������ ���� ) - �浹�� ����
				if (road[i][j] == 2) {
					glPushMatrix();
					glTranslatef(drawRoad[i][j].x, -100, drawRoad[i][j].z + RoadSpeed); // RoadSpeed ���� ���� �ӵ� ����
					glColor3f(1.0f, 0.0f, 0.0f);
					glScalef(1.0, 0.01, 1.0);
					glutSolidCube(40);
					glPopMatrix();
				}
			}
		}
	}
	glPopMatrix();
}
void Student() {
	glPushMatrix();
	glTranslatef(0, -80, 100);//�л��� �ʱ���ġ
	glTranslatef(charX, 0, 0);//�л��� x���� �ٲ��ش�.
	glScalef(3, 3, 3);   //�л� Ȯ�� (�⺻ 3,3,3)
	glRotatef(90, 0, 1, 0);//�л��� ���� ������ �ٶ󺸰�
						   //�ٸ�1
	glPushMatrix();
	glRotatef(StudentAngle, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(0, 0, 1.5);
	glScalef(0.3, 1.0, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	// �ٸ�2
	glRotatef(-StudentAngle, 0, 0, 1);
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
	glRotatef(-StudentAngle, 0, 0, 1);
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
	glRotatef(StudentAngle, 0, 0, 1);
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
	glRotatef(StudentAngle / 4, 1, 0, 0);
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
	glPopMatrix();
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