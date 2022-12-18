#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>        // Header File For The GLut Library
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "iostream"
#define kWindowWidth	1200
#define kWindowHeight	1200
#define N 8

GLfloat axisCam = 0;
glm::vec3 cameraPos = glm::vec3(00.0f, 0.0f, 3.0f);
glm::vec3 cameraFront = glm::vec3(0, 0, -20);
glm::vec3 cameraUp = glm::vec3(0, 1, 0);
GLfloat vertex[] = {-1,-1,0,   1,-1,0,   1,1,0,   -1,1,0};

GLfloat cameraSpeed = 0.1;

GLboolean isCameraSpin = false;
GLboolean isLightSpin = false;
GLboolean isObjectSpin = false;
GLfloat spinObj = 0;
GLfloat spinCamera = 0;
GLfloat spinLight = 0;
GLboolean keys[1024];

using namespace std;

GLvoid InitGL(GLvoid);
GLvoid DrawGLScene(GLvoid);
GLvoid ReSizeGLScene(int Width, int Height);
GLvoid processNormalKeys(unsigned char key, int x, int y);
GLvoid DrawObject(GLvoid);
GLvoid DrawWheel(GLvoid);
GLvoid DrawSuspension(GLvoid);
GLvoid DrawBox(GLvoid);
GLvoid DrawHandle(GLvoid);
GLvoid DrawHandles(GLvoid);
GLvoid DrawLightSource(GLvoid);

GLvoid processSpecialKeys(int key, int x, int y);
GLvoid MoveCamera(GLvoid);
GLvoid processUpKeys(unsigned char, int, int);
GLvoid do_movement(GLvoid);



int main(int argc, char **argv) {

    // инициализация
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(kWindowWidth, kWindowHeight);
    glutCreateWindow("lab2");

    InitGL();
    glutDisplayFunc(DrawGLScene);
    glutReshapeFunc(ReSizeGLScene);
    glutIdleFunc(DrawGLScene);

    // обработка клавиш
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardUpFunc(processUpKeys);
//    glutMouseFunc(processMouseKeys);

    // Основной цикл GLUT
    glutMainLoop();

    return 1;
}

GLvoid DrawGLScene(GLvoid) {
    do_movement();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(0, 0, 0, 0);

    glPushMatrix();
    glTranslated(0, 0, -30);
    MoveCamera();
    glPushMatrix();
    glRotatef(spinLight, 0, 1, 0);
    GLfloat position[] = {0,0,1,0};
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glRotatef(-40, 1, 0,0);
    glTranslatef(0,0,30);
    DrawLightSource();

    glPopMatrix();

    glClear(GL_COLOR_BUFFER_BIT);    // очистка экрана

    // /*** 1-ый пункт ***/
//    glEnable(GL_POINT_SMOOTH); // сглаживание
//    glPointSize(20);  //размер точки
//    glColor3f(0.2, 0.78, 0.0);
//    double x, y;
//    double radius = 3.0;
//
//    glBegin(GL_POINTS);
//    for (int i = 0; i < N; i++)
//    {
//        x = radius * cos(2.0*M_PI*i/N);
//        y = radius * sin(2.0*M_PI*i/N);
//        glVertex2d(x, y);
//    }
//    glDisable(GL_POINT_SMOOTH);

    /*** 2-ой пункт ***/
//    double x[N], y[N];
//    double radius = 10.0;
//    x[0] = radius;
//    y[0] = 0;
//    glColor3f(0.2, 0.78, 0.0);
//    glLineWidth(2); // толщина линии 2 пикселя
//    glLineStipple(2, 3855);   // 0000111100001111
//    glEnable(GL_LINE_STIPPLE);
//    glBegin(GL_LINE_LOOP);
//    for (int i = 1; i < N; i++)
//    {
//        x[i] = radius * cos(2.0*M_PI*i/N);
//        y[i] = radius * sin(2.0*M_PI*i/N);
//        glVertex2d(x[i-1], y[i-1]);
//        glVertex2d(x[i], y[i]);
//    }
//    glDisable(GL_LINE_STIPPLE);


    /*** 3-ий пункт ***/
//    glColor3f(1.0, 1.0, 1.0);
//    glLineWidth(3); // толщина линии 3 пикселя
//    glLineStipple(1, 0xF0F0);   // тип линии - пунктирная
//    glBegin(GL_LINE_STRIP);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(1.0, 3.0);
//    glVertex2d(1.5, -3.0);
//    glVertex2d(1.5, 1.0);
//    glVertex2d(3.5, 1.0);
//    glVertex2d(3.5, 3.0);
//    glVertex2d(6.0, -2.0);

    /*** 4-ый пункт ***/
//    glColor3f(1.0, 1.0, 1.0);
//    glLineWidth(3); // толщина линии 3 пикселя
//    glLineStipple(1, 0xF0F0);   // тип линии - пунктирная
//    glBegin(GL_LINE_LOOP);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(2.0, 4.0);
//    glVertex2d(-4.0, 3.5);
//    glVertex2d(-10.0, -6.0);
//    glVertex2d(-3.0, -3.0);
//    glVertex2d(0.0, -8.0);
//    glVertex2d(0.0, -3.0);
//    glVertex2d(5.0, -3.0);
//    glVertex2d(5.0, 2.0);


    /*** 5-ый пункт ***/
//    srand(time(NULL));
//    glBegin(GL_TRIANGLES);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(2.0, 4.0);
//    glVertex2d(-4.0, 3.5);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-10.0, -6.0);
//    glVertex2d(-4.0, 3.5);
//    glVertex2d(0.0, 0.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(5.0, -3.0);
//    glVertex2d(5.0, 2.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(-5.0, -3.0);
//    glVertex2d(5.0, -3.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-5.0, -3.0);
//    glVertex2d(0.0, -8.0);
//    glVertex2d(0.0, -3.0);

    /*** 6-ой пункт ***/
//    srand(time(NULL));
//    glBegin(GL_TRIANGLE_STRIP);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-4.0, 3.5);
//    glVertex2d(-10.0, -6.0);
//    glVertex2d(2.0, 4.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-5.0, -3.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, -8.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, -3.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(5.0, 2.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(5.0, -3.0);

    /*** 7-ой пункт ***/
//    srand(time(NULL));
//    glBegin(GL_TRIANGLE_FAN);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(5.0, 1.0);
//    glVertex2d(5.0, -3.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(5.0, -3.0);
//    glVertex2d(0.0, -3.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(0.0, -8.0);
//    glVertex2d(-5.0, -3.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(-5.0, -3.0);
//    glVertex2d(-10.0, -6.0);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(-10.0, -6.0);
//    glVertex2d(-4.0, 3.5);
//
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(0.0, 0.0);
//    glVertex2d(-4.0, 3.5);
//    glVertex2d(2.0, 4.0);

    /*** 8-ой пункт ***/
//    double x[N], y[N];
//    double radius = 5.0;
//
//    glColor3f(0.0, 0.5, 0.5);
//    glBegin(GL_POLYGON);
//    for (int i = 0; i < N; i++)
//    {
//        x[i] = radius * cos(2.0*M_PI*i/N);
//        y[i] = radius * sin(2.0*M_PI*i/N);
//        glVertex2d(x[i], y[i]);
//    }

    /*** 9-ый пункт ***/
//    srand(time(NULL));
//    glBegin(GL_POLYGON);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-1.0, 7.0);
//    glVertex2d(8.0, 5.5);
//    glVertex2d(5.5, -8.0);
//    glVertex2d(1.0, -5.0);
//    glVertex2d(-1.2, 5.0);
//    glEnd();
//
//    glBegin(GL_QUADS);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-8.0, 8.0);
//    glVertex2d(-8.0, 2.0);
//    glVertex2d(-1.5, 2.0);
//    glVertex2d(-1.0, 7.0);
//    glEnd();
//
//    glBegin(GL_QUADS);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(5.5, -8.0);
//    glVertex2d(1.0, -5.0);
//    glVertex2d(-1.5, -5.0);
//    glVertex2d(-9.0, -7.0);
//    glEnd();
//
//    glBegin(GL_TRIANGLES);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-1.5, -5.0);
//    glVertex2d(-9.0, -7.0);
//    glVertex2d(-4.75, 2.0);
//    glEnd();

    /*** 10-ый пункт ***/
//    srand(time(NULL));
//    glPolygonMode(GL_FRONT, GL_POINT);
//    glPointSize(5);
//    glBegin(GL_POLYGON);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-1.0, 7.0);
//    glVertex2d(8.0, 5.5);
//    glVertex2d(5.5, -8.0);
//    glVertex2d(1.0, -5.0);
//    glVertex2d(-1.2, 5.0);
//    glEnd();
//
//    glBegin(GL_QUADS);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-8.0, 8.0);
//    glVertex2d(-8.0, 2.0);
//    glVertex2d(-1.5, 2.0);
//    glVertex2d(-1.0, 7.0);
//    glEnd();
//
//    glBegin(GL_QUADS);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(5.5, -8.0);
//    glVertex2d(1.0, -5.0);
//    glVertex2d(-1.5, -5.0);
//    glVertex2d(-9.0, -7.0);
//    glEnd();
//
//    glBegin(GL_TRIANGLES);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-1.5, -5.0);
//    glVertex2d(-9.0, -7.0);
//    glVertex2d(-4.75, 2.0);
//    glEnd();

    /*** 11-ый пункт ***/
//    srand(time(NULL));
//    glPolygonMode(GL_FRONT, GL_FILL);
//    glPolygonMode(GL_BACK, GL_LINE);
//    glLineWidth(5);
//    glBegin(GL_POLYGON);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-1.0, 7.0);
//    glVertex2d(8.0, 5.5);
//    glVertex2d(5.5, -8.0);
//    glVertex2d(1.0, -5.0);
//    glVertex2d(-1.2, 5.0);
//    glEnd();
//
//    glBegin(GL_QUADS);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-8.0, 8.0);
//    glVertex2d(-8.0, 2.0);
//    glVertex2d(-1.5, 2.0);
//    glVertex2d(-1.0, 7.0);
//    glEnd();
//
//    glBegin(GL_QUADS);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(5.5, -8.0);
//    glVertex2d(1.0, -5.0);
//    glVertex2d(-1.5, -5.0);
//    glVertex2d(-9.0, -7.0);
//    glEnd();
//
//    glBegin(GL_TRIANGLES);
//    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
//    glVertex2d(-1.5, -5.0);
//    glVertex2d(-9.0, -7.0);
//    glVertex2d(-4.75, 2.0);
//    glEnd();

    /*** 12-ый пункт ***/
    srand(time(NULL));
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glLineWidth(5);
    glBegin(GL_POLYGON);
    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glVertex2d(-1.0, 7.0);
    glVertex2d(8.0, 5.5);
    glVertex2d(5.5, -8.0);
    glVertex2d(1.0, -5.0);
    glVertex2d(-1.2, 5.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glVertex2d(-8.0, 8.0);
    glVertex2d(-8.0, 2.0);
    glVertex2d(-1.5, 2.0);
    glVertex2d(-1.0, 7.0);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glVertex2d(5.5, -8.0);
    glVertex2d(1.0, -5.0);
    glVertex2d(-1.5, -5.0);
    glVertex2d(-9.0, -7.0);
    glEnd();

    glBegin(GL_TRIANGLES);
    glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
    glVertex2d(-1.5, -5.0);
    glVertex2d(-9.0, -7.0);
    glVertex2d(-4.75, 2.0);
    glEnd();



    glEnd();

    glTranslated(0, 0, 30);
    glPopMatrix();

    glutSwapBuffers();
}

GLvoid MoveCamera(GLvoid) {

    glMatrixMode(GL_MODELVIEW); //видовая матрица
    if (isCameraSpin) {
        spinCamera += 1;
    }
    if (isObjectSpin) {
        spinObj -= 1;
    }
    if (isLightSpin) {
        spinLight +=1;
    }
    gluLookAt(cameraPos.x, cameraPos.y, cameraPos.z, //местоположение камеры
              cameraPos.x + cameraFront.x, cameraPos.y + cameraFront.y,
              cameraPos.z + cameraFront.z, //камера смотрит в эту точку
              cameraUp.x, cameraUp.y, cameraUp.z); //направление вектора «вверх»
    glRotatef(axisCam, 1, 0, 0); //поворот вокруг оси X
    glRotatef(-spinCamera, 0, 1, 0); //поворот вокруг оси Y
}

GLvoid DrawObject(GLvoid) {
    glEnable(GL_COLOR_MATERIAL);
    glColor3f(0.7, 0.7, 0.7);

    glPushMatrix();
    glRotated(spinObj, 0, 1, 0);
    DrawSuspension();
    DrawBox();
    DrawHandles();
    glPopMatrix();
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);


    glBegin(GL_LINES);
    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1000, 0, 0);
    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1000, 0);
    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1000);
    glEnd();
}

GLvoid DrawWheel(GLvoid) {
    GLUquadricObj *spoke = gluNewQuadric();
    glPushMatrix();
    glutSolidTorus(0.6, 2, 20, 30);

    glPushMatrix();
    glRotated(90, 1, 0, 0);
    for (int i = 0; i < 6; ++i) {
        gluCylinder(spoke, 0.1f, 0.1f, 2.0f, 32, 32);
        glRotated(60, 0, 1, 0);
    }
    glPopMatrix();

    glPushMatrix();
    glRotated(-90, 0, 0, 1);
    glRotated(180, 1, 0, 0);
    glutSolidCone(0.2, 0.4, 20, 20);
    glPopMatrix();
    glPopMatrix();
}

GLvoid DrawSuspension(GLvoid) {
    // общая длина подвески = 10
    GLUquadricObj *axis = gluNewQuadric();
    glPushMatrix();
    glTranslated(0, 0, -5);

    DrawWheel();
    glPushMatrix();
    glTranslated(0, 0, 10);
    glRotated(180, 1, 0, 0);
    DrawWheel();
    glPushMatrix();
    gluCylinder(axis, 0.1f, 0.1f, 10.0f, 100, 100);
    glPopMatrix();
    glPopMatrix();
    glPopMatrix();
}

GLvoid DrawBox(GLvoid) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    double eq[] = {8, 20, 0, 0};
    glPushMatrix();
    glRotated(180, 1, 0, 0);
    glTranslated(0, -4.4, 0);
    glClipPlane(GL_CLIP_PLANE0, eq);
    glEnable(GL_CLIP_PLANE0);
    glutSolidCube(8);
    glDisable(GL_CLIP_PLANE0);
    glPopMatrix();
}

GLvoid DrawHandle(GLvoid) {
    GLUquadricObj *handle = gluNewQuadric();
    GLfloat rad = 0.25;
    GLfloat hTube = 9;
    GLfloat hHandle = hTube - 8;

    glPushMatrix();
    glTranslated(0, 3, 0);
    glRotated(-30, 1, 0, 0);
    gluCylinder(handle, 0.2, 0.1, hTube, 32, 32);
    glTranslated(0, 0, hTube - hHandle);
    gluCylinder(handle, rad, rad, hHandle, 32, 32);
    gluDisk(gluNewQuadric(), 0, rad, 32,1);
    glTranslated(0, 0, hHandle);
    gluDisk(gluNewQuadric(), 0, rad, 32,1);
    glPopMatrix();
}

GLvoid DrawHandles(GLvoid) {
    GLfloat distance = 4;
    glPushMatrix();
    glRotated(90, 0, 1, 0);
    glTranslated(distance / 2, 0, 0);
    glTranslated(0, 0, 4);
    DrawHandle();
    glTranslated(-distance, 0, 0);
    DrawHandle();

    glPopMatrix();
}

GLvoid DrawLightSource(GLvoid) {
    glNormal3f(0,0,1);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertex);
    glColor3d(1,1,1);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableClientState(GL_VERTEX_ARRAY);
}

GLvoid do_movement(GLvoid) {
    if(keys[27])
        exit(0);
    if (keys['w'])
        cameraPos += cameraSpeed * cameraFront;
    if (keys['s'])
        cameraPos -= cameraSpeed * cameraFront;
    if (keys['d'])
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys['a'])
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (keys[GLUT_KEY_F1])
        glutFullScreen();
}

GLvoid processNormalKeys(unsigned char key, int x, int y) {
    keys[key] = true;
    switch (key) {
        case 'e':
            isObjectSpin = !isObjectSpin;
            break;
        case 'r':
            isCameraSpin = !isCameraSpin;
            break;
        case 'l':
            isLightSpin = !isLightSpin;
            break;
        default: break;

    }
}

GLvoid processUpKeys(unsigned char key, int, int) {
    keys[key] = false;
}

GLvoid processSpecialKeys(int key, int x, int y) {
    switch (key) {
        case GLUT_KEY_UP:
            axisCam += 2;
            break;
        case GLUT_KEY_DOWN:
            axisCam -= 2;
            break;
        case GLUT_KEY_RIGHT:
            spinCamera += 2;
            break;
        case GLUT_KEY_LEFT:
            spinCamera -= 2;
            break;
        case GLUT_KEY_F1:
            glutFullScreen();
        default: break;
    }
}

GLvoid InitGL(GLvoid) {
//    glShadeModel(GL_SMOOTH);	// Enable Smooth Shading (blends colours across a polygon/smoothed lighting
//
//     Set-up the depth buffer
//    glClearDepth(-1.0f);		// Depth Buffer Setup
    glEnable(GL_DEPTH_TEST);    // Enables Depth Testing
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);
//    glDepthFunc(GL_LEQUAL);		// The Type Of Depth Testing To Do
//
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

}

GLvoid ReSizeGLScene(int w, int h) {
    // предотвращение деления на ноль
    if (h == 0)
        h = 1;
    float ratio = w * 1.0 / h;
    // используем матрицу проекции
    glMatrixMode(GL_PROJECTION);
    // обнуляем матрицу
    glLoadIdentity();
    // установить параметры вьюпорта
    glViewport(0, 0, w, h);
    // установить корректную перспективу
    gluPerspective(40.0f, ratio, 0.1f, 1000.0f);
    // вернуться к матрице проекции
    glMatrixMode(GL_MODELVIEW);
}
