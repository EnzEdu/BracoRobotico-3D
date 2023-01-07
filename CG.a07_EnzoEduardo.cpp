/*
 * Atividade 07 - Computacao Grafica
 * Codigo OpenGL/GLUT que desenha um braco robotico 3D
 * Autor: Enzo Eduardo
 * Data: xx/01/2023
*/






// Bibliotecas utilizadas pelo OpenGL
#ifdef __APPLE__                        // Mac OS
    #define GL_SILENCE_DEPRECATION
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#else                                   // Windows/Linux
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif


// Bibliotecas
#include <stdio.h>
#include <stdlib.h>


// Teclas do teclado e seus valores ASCII
#define ESC 27


/*
 * Declaracao de constantes e variaveis
 */
static int rotacaoDDD = 0;
static int ombro = 0, cotovelo = 0, mao = 0;
static int garraIndicador = 0, garraPolegar = 0, garraAnelar = 0;


/*
 * Declaracoes antecipadas (forward) das funcoes (assinaturas)
 */
void init(void);
void keyboard (unsigned char key, int x, int y);
void display(void);
void reshape (int w, int h);





// Funcao principal
int main(int argc, char** argv)
{
    glutInit(&argc,argv);                                           // Inicia o GLUT com a passagem de parametros C
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);       // Inicia o Display com o sistema RGB, double-buffering e z-buffering
    glutInitWindowSize(800,600);                                    // Tamanho da janela do OpenGL
    glutInitWindowPosition(100,100);                                // Posicao inicial da janela do OpenGL
    glutCreateWindow("Computacao Grafica: Braco Robotico");         // Da nome para uma janela OpenGL

    init();                                                         // Chama a funcao init()

    glutDisplayFunc(display);                                       // Funcao callback de desenho
    glutReshapeFunc(reshape);                                       // Funcao callback para redesenhar a tela
    glutKeyboardFunc(keyboard);                                     // Funcao callback para tratar interrupcao do teclado
    glutMainLoop();                                                 // Executa o loop do OpenGL

    return EXIT_SUCCESS;                                            // Retorna 0 para o tipo inteiro da funcao main()
}





// Funcao com alguns comandos para a inicializacao do OpenGL
void init(void)
{
    glClearColor (1.0, 1.0, 1.0, 1.0);      // Limpa a tela com a cor branca
    glEnable(GL_DEPTH_TEST);                // Habilita o algoritmo Z-Buffer
}



// Funcao callback para controle das teclas comuns
void keyboard(unsigned char key, int x, int y) 
{
    switch (key) {

        // lowerCase = sentido horario
        // upperCase = sentido anti-horario
        case 'o':          ombro = (ombro - 5) % 360;               break;
        case 'O':          ombro = (ombro + 5) % 360;               break;
        case 'c':       cotovelo = (cotovelo - 5) % 360;            break;
        case 'C':       cotovelo = (cotovelo + 5) % 360;            break;
        case 'm':            mao = (mao - 5) % 360;                 break;
        case 'M':            mao = (mao + 5) % 360;                 break;

        case 'i': garraIndicador = (garraIndicador) - 5 % 360;      break;
        case 'I': garraIndicador = (garraIndicador) + 5 % 360;      break;
        case 'p':   garraPolegar = (garraPolegar) - 5 % 360;        break;
        case 'P':   garraPolegar = (garraPolegar) + 5 % 360;        break;
        case 'a':    garraAnelar = (garraAnelar) - 5 % 360;         break;
        case 'A':    garraAnelar = (garraAnelar) + 5 % 360;         break;

        case 'y':     rotacaoDDD = (rotacaoDDD - 5) % 360;          break;
        case 'Y':     rotacaoDDD = (rotacaoDDD + 5) % 360;          break;


        // Sai do programa
        case ESC: exit(EXIT_SUCCESS);                               break;
    }

    glutPostRedisplay();
}



// Funcao callback para o reshape da janela
void reshape(int w, int h) 
{
    glMatrixMode (GL_PROJECTION);   // Muda pro modo de projecao
    glLoadIdentity();               // Carrega a matriz identidade

    // Define o tamanho da area de desenho da janela
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);

    // Define a forma do volume de visualizacao para termos uma projecao perspectiva (3D)
    // (angulo, aspecto, ponto_proximo, ponto distante)
    gluPerspective(60, (float)w/(float)h , 1.0, 11.0);

    gluLookAt(0.0, 0.0, 7.0,  // Posicao da camera
              0.0, 1.0, 0.0,  // Direcao da camera                <<<< |=| >>>>
              0.0, 1.0, 0.0); // Sentido ou orientacao da camera  ^^^^ |=| vvvv
}



// Funcao callback para desenhar na janela
void display(void) 
{
    glMatrixMode(GL_MODELVIEW);                             // Muda pro modo de desenho
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);    // Limpa o Buffer de Cores
    glLoadIdentity();                                       // Carrega a matriz identidade

    
    // Braco robotico
    glPushMatrix();

        // Rotacao 3D
        glRotatef((GLfloat) rotacaoDDD, 0.0, 1.0, 0.0);

        // Base
        glPushMatrix();
            glTranslatef(0.0, -2.0, 0.0);
            glRotatef(-90, 1, 0, 0);
            glColor3f(0.33, 0.33, 0.33);
            glutSolidCone(1.0, 1.0, 30, 30);
        glPopMatrix();

    
        // Ombro
        glPushMatrix();
            glTranslatef(0.0, -1.0, 0.0);
            glColor3f(0.33, 0.33, 0.33);
            glutSolidSphere(0.5, 30, 30);
        glPopMatrix();


        // Movimento do braco
        glPushMatrix();

            // Ajuste do ponto de origem
            glTranslatef (0.0, -1.0, 0.0);  // Origem no ombro
            glRotatef ((GLfloat) ombro, 0.0, 0.0, 1.0);
            glTranslatef (0.0, 1.0, 0.0);   // Origem no centro do braco

                // Braco
                glPushMatrix();
                    glRotatef(90, 0, 0, 1);
                    glScalef (2.0, 0.5, 0.5);
                    glColor3f(1.0, 1.0, 0.0);
                    glutSolidCube(1.0);
                glPopMatrix();

                // Cotovelo
                glPushMatrix();
                    glTranslatef(0.0, 1.0, 0.0);
                    glColor3f(0.33, 0.33, 0.33);
                    glutSolidSphere(0.4, 30, 30);
                glPopMatrix();


                // Movimento do antebraco
                glPushMatrix();

                    // Ajuste do ponto de origem
                    glTranslatef (0.0, 1.0, 0.0);   // Origem no cotovelo
                    glRotatef ((GLfloat) cotovelo, 0.0, 0.0, 1.0);
                    glTranslatef (0.0, 1.0, 0.0);   // Nova origem no cotovelo

                    // Antebraco
                    glPushMatrix();
                        glRotatef(90, 0, 0, 1);
                        glScalef(2.0, 0.4, 0.4);
                        glColor3f(1.0, 1.0, 0.0);
                        glutSolidCube(1.0);
                    glPopMatrix();

                    // Pulso
                    glPushMatrix();
                        glTranslatef(0.0, 1.0, 0.0);
                        glColor3f(0.33, 0.33, 0.33);
                        glutSolidSphere(0.3, 30, 30);
                    glPopMatrix();


                    // Movimento da mao
                    glPushMatrix();

                        // Ajuste do ponto de origem
                        glTranslatef(0.0, 1.0, 0.0);
                        glRotatef((GLfloat) mao, 0.0, 0.0, 1.0);
                        glTranslatef(0.0, 0.5, 0.0);

                        // Mao
                        glPushMatrix();
                            glRotatef(90, 0, 0, 1.0);
                            glScalef(2.0, 0.4, 0.4);
                            glColor3f(0.53, 0.53, 0.53);
                            glutSolidCube(0.5);
                        glPopMatrix();


                        // Movimento do polegar
                        glPushMatrix();

                            // Ajuste do ponto de origem
                            glTranslatef(0.06, 0.5, 0.0);
                            glRotatef((GLfloat) garraPolegar, 0.0, 0.0, 1.0);
                            glTranslatef(0.0, 0.2, 0.0);

                            // Polegar
                            glPushMatrix();
                                glRotatef(90, 0, 0, 1.0);
                                glScalef(2.0, 0.4, 0.4);
                                glColor3f(0.0, 0.0, 0.0);
                                glutSolidCube(0.2);
                            glPopMatrix();

                        glPopMatrix();


                        // Movimento do anelar
                        glPushMatrix();

                            // Ajuste do ponto de origem
                            glTranslatef(-0.06, 0.5, 0.06);
                            glRotatef((GLfloat) garraAnelar, 0.0, 0.0, 1.0);
                            glTranslatef(0.0, 0.2, 0.0);

                            // Anelar
                            glPushMatrix();
                                glRotatef(90, 0, 0, 1.0);
                                glScalef(2.0, 0.4, 0.4);
                                glColor3f(0.0, 0.0, 0.0);
                                glutSolidCube(0.2);
                            glPopMatrix();

                        glPopMatrix();


                        // Movimento do indicador
                        glPushMatrix();

                            // Ajuste do ponto de origem
                            glTranslatef(-0.06, 0.5, -0.06);
                            glRotatef((GLfloat) garraIndicador, 0.0, 0.0, 1.0);
                            glTranslatef(0.0, 0.2, 0.0);

                            // Indicador
                            glPushMatrix();
                                glRotatef(90, 0, 0, 1.0);
                                glScalef(2.0, 0.4, 0.4);
                                glColor3f(0.0, 0.0, 0.0);
                                glutSolidCube(0.2);
                            glPopMatrix();

                        glPopMatrix();

                    glPopMatrix();
                glPopMatrix();
        glPopMatrix();
    glPopMatrix();


    // Troca os buffers, mostrando o que acabou de ser desenhado
    glutSwapBuffers();
}

