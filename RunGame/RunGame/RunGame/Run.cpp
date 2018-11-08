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

void WalkingRobot();//로봇
void keyboard(unsigned char key, int x, int y);//키보드
void Timerfunction(int value);
int set = 0;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("Example2");// 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene);// 출력 함수의 지정	
	glutTimerFunc(100, Timerfunction, 1);
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

}// 윈도우 출력 함수

GLvoid drawScene(GLvoid)//그리기
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

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기
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
	//다리1
	glPushMatrix();
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(0, 0, 1.5);
	glScalef(0.3, 1.0, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	// 다리2
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(0, 0, -1.5);
	glScalef(0.3, 1.0, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	glPopMatrix();
	//몸통
	glPushMatrix();
	glColor3f(1.0f, 0.8f, 0.2f);
	glScalef(0.8, 1.0, 1);
	glutSolidCube(5);
	glPopMatrix();

	// 팔1
	glTranslatef(0, 3, 0);
	glPushMatrix();
	//윗팔
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -2, 0);
	glTranslatef(0, 0, 3.5);
	glScalef(0.3, 0.5, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	//아랫팔
	glTranslatef(0, -4, 0);
	glutSolidCube(4);
	glPopMatrix();

	glPushMatrix();
	// 팔2
	//윗팔
	glRotatef(0, 0, 0, 1);
	glTranslatef(0, -2, 0);
	glTranslatef(0, 0, -3.5);
	glScalef(0.3, 0.5, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	//아랫팔
	glTranslatef(0, -4, 0);
	glutSolidCube(4);
	glPopMatrix();

	// 머리
	glPushMatrix();
	glTranslatef(0, 1, 0);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(3);
	glPopMatrix();
	//코
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
	
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(30, Timerfunction, 1); // 타이머함수 재 설정
}

GLvoid Reshape(int w, int h)
{
	//--- 뷰포트 변환 설정
	glViewport(0, 0, w, h);
	// 투영 행렬 스택 재설정
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)w / (double)h, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// 모델 뷰 행렬 스택 재설정
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}