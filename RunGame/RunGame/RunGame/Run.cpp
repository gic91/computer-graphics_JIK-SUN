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
int set = 0;   // 도로입력 확인용

int menu = 0;   // 메뉴 ( 0 = 초기화면 / 1 = 게임화면 )
int level = 4;   // 레벨 ( 1 = 18학점 / 2 = 21학점 / 3 = 24학점)

int moveX = 0;   // 캐릭터 x값 확인 변수
float charX = 0;// 캐릭터 x 위치

float RoadSpeed = 0;   // 시간 증가

float StudentAngle = 0;   //팔,다리,머리흔드는 각도
int StudentTemp = 0;   //학생 각도 확인 변수

void keyboard(unsigned char key, int x, int y);//키보드

void Roadsetting(); // 길 배열정보 입력
void RandomRoad(); // 장애물 랜덤설정
void Student();//로봇

void RoadTimer(int value);   //도로속도조절
void CharTimer(int value);   //캐릭터속도조절
void MenuTimer(int value);   //메뉴 선택확인용
void Road();
void collide();
bool survive = true;
int inRect(int x, int y, int rectx1, int recty1, int rectx2, int recty2); // 꼭지점,사각형 충돌체크

int main(int argc, char* argv[])
{
	Roadsetting();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH); // 디스플레이 모드 설정 
	glutInitWindowPosition(100, 100); // 윈도우의 위치지정 
	glutInitWindowSize(800, 600); // 윈도우의 크기 지정
	glutCreateWindow("RunGame");// 윈도우 생성 (윈도우 이름)
	glutDisplayFunc(drawScene);// 출력 함수의 지정   
	glutTimerFunc(10, RoadTimer, 1);
	glutTimerFunc(5, CharTimer, 1);
	glutTimerFunc(100, MenuTimer, 1);
	glutKeyboardFunc(keyboard);
	glutReshapeFunc(Reshape);
	glutMainLoop();

}// 윈도우 출력 함수

GLvoid drawScene(GLvoid)//그리기
{
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // 바탕색을 'black' 로 지정
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 설정된 색으로 전체를 칠하기

	if (menu == 0) {
		glPushMatrix();

		glColor3f(1.0f, 1.0f, 0.0f);
		glScalef(1.0, 1.0, 1.0);
		glutSolidCube(100);
		glPopMatrix();

	}
	else if (menu == 1) {
		glPushMatrix();

		glRotatef(3 * moveX, 0, 1, 0); // 학생 위치에 따라 맵 전체회전

		Road();      //도로 & 아이템 그리기
		Student();   //학생 그리기

		glPopMatrix();
	}
	glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case '+':
		printf("랭킹\n");
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
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(10, RoadTimer, 1); // 타이머함수 재 설정
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
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, CharTimer, 1); // 타이머함수 재 설정
}
void MenuTimer(int value) {
	if (menu == 0) {

	}
	glutPostRedisplay(); // 화면 재 출력
	glutTimerFunc(1, MenuTimer, 1); // 타이머함수 재 설정
}
void collide() {
	double range = 10; // 충돌범위
	for (int i = 0; i < NUM; i++) {
		for (int j = 0; j < 5; j++) {
			if (road[i][j] == 2) {
				if (inRect(charX - range, 100 - range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range) ||
					inRect(charX - range, 100 + range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range) ||
					inRect(charX + range, 100 - range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range) ||
					inRect(charX + range, 100 + range, drawRoad[i][j].x - range, drawRoad[i][j].z + RoadSpeed - range, drawRoad[i][j].x + range, drawRoad[i][j].z + RoadSpeed + range)) {
					//충돌시
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
			int count = 0; // 장애물 개수 0으로 초기화
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
				// 일반 길
				if (road[i][j] == 1) {
					glPushMatrix();
					glTranslatef(drawRoad[i][j].x, -100, drawRoad[i][j].z + RoadSpeed); // RoadSpeed 으로 도로 속도 조절
					glColor3f(1.0f, 1.0f, 1.0f);
					glScalef(1.0, 0.01, 1.0);
					glutSolidCube(40);
					glPopMatrix();
				}
				// 빨간 길( 아이템 미정 ) - 충돌시 멈춤
				if (road[i][j] == 2) {
					glPushMatrix();
					glTranslatef(drawRoad[i][j].x, -100, drawRoad[i][j].z + RoadSpeed); // RoadSpeed 으로 도로 속도 조절
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
	glTranslatef(0, -80, 100);//학생의 초기위치
	glTranslatef(charX, 0, 0);//학생의 x값을 바꿔준다.
	glScalef(3, 3, 3);   //학생 확대 (기본 3,3,3)
	glRotatef(90, 0, 1, 0);//학생이 가는 방향을 바라보게
						   //다리1
	glPushMatrix();
	glRotatef(StudentAngle, 0, 0, 1);
	glTranslatef(0, -3, 0);
	glTranslatef(0, 0, 1.5);
	glScalef(0.3, 1.0, 0.3);
	glColor3f(1.0f, 0.7f, 0.2f);
	glutSolidCube(4);
	glPopMatrix();
	glPushMatrix();
	// 다리2
	glRotatef(-StudentAngle, 0, 0, 1);
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
	glRotatef(-StudentAngle, 0, 0, 1);
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
	glRotatef(StudentAngle, 0, 0, 1);
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
	glRotatef(StudentAngle / 4, 1, 0, 0);
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
	glPopMatrix();
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