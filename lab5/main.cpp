#define GL_SILENCE_DEPRECATION
#include <GLUT/glut.h>        // Header File For The GLut Library
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "iostream"
#define kWindowWidth	1200
#define kWindowHeight	1200

GLfloat axisCam = 20;
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
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
GLvoid DrawVase(GLvoid);
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
    glutCreateWindow("lab5");

    InitGL();
    glutDisplayFunc(DrawGLScene);
    glutReshapeFunc(ReSizeGLScene);
    glutIdleFunc(DrawGLScene);

    // обработка клавиш
    glutKeyboardFunc(processNormalKeys);
    glutSpecialFunc(processSpecialKeys);
    glutKeyboardUpFunc(processUpKeys);

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
    DrawObject();
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
    DrawVase();
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

GLvoid DrawVase(GLvoid) {
    GLUquadricObj *spoke = gluNewQuadric();
    glPushMatrix();
    glRotated(-90, 0, 0, 0);
    glutSolidCone(2.0, 2.0, 20, 20);
    glTranslatef(0, 0, 3.0);
    glutSolidSphere(3, 20, 20);
    glTranslatef(0, 0, 3.0);
    glutSolidTorus(1.0,1.0,20,20);
    glPushMatrix();
    glTranslated(0, 0, 3.0);
    glRotated(180, 1, 0, 0);
    glutSolidCone(2.0, 7.0, 20, 20);
    glPopMatrix();
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
    glEnable(GL_DEPTH_TEST);    // Enables Depth Testing
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_NORMALIZE);

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
