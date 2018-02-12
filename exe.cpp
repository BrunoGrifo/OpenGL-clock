/* ===================================================================================
		Computacao Grafica - 2018
	................................................... JHenriques
	Trabalho 0 - Introducao ao OpenGL
======================================================================================= */


//.................................................... Bibliotecas necessarias
#include <stdio.h>			// printf
#include <GL/glut.h>		// openGL


//.................................................... Variaveis
GLfloat r,g,b;						// cor RGB


//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------
void Inicializa (void)
{   
    glClearColor(0.0, 0.0, 0.0, 1.0);	//....	Cor para apagar ecran (Preto)
	gluOrtho2D(-50, 50, -50, 50);		//....	Definicao sistema coordenadas area de desenho
	glShadeModel(GL_SMOOTH);				//....  Interpolacao de cor com base na cor dos vertices

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	r=1; g=0; b=0;						//....  Vermelho
}


//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------
//จจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจจFun็ใo callback eventos teclado 
void Teclado(unsigned char key, int x, int y){

	
	switch (key) {	  
	case 'r':
		r=1.0; g=0.0; b=1.0;
		glutPostRedisplay();
		break;
	case 'g':
		r=0.0; g=1.0; b=0.0;
		glutPostRedisplay();
		break;
	case 'b':
		r=0.0; g=0.0; b=1.0;
		glutPostRedisplay();
		break;	  
	
	case 27:					//ESC
		exit(0);
		break;
	}
}


//---------------------------------------- Fun็ใo callback de desenho (principal)
void Desenha(void)
{
 	glClear(GL_COLOR_BUFFER_BIT);		//.. Limpa de acordo com cor predefinida
	
	
	glColor3f(r,g,b);					//.. Inicializa cor 
	glBegin(GL_POLYGON);
		glVertex2f(-25.0f, -25.0f);
     	 glVertex2f(-25.0f,  25.0f);
        glVertex2f( 25.0f,  25.0f);
        glVertex2f(25.0f,  -25.0f);
	glEnd();
	
	
	glColor3f(1,0.8,0.2);					//.. Inicializa cor 
	glBegin(GL_TRIANGLES);
		glVertex2f(  25.0f, 45.0f);
    	glColor3f(0,0.8,0.9);					//.. Inicializa cor 
	 	 glVertex2f( 5.0f,  25.0f);
        glVertex2f( 15.0f,  45.0f);
	glEnd();
	
	
	glutSwapBuffers();						//.. actualiza ecran
}
  


//-----------------------------------------------------------------------------------
//																		         MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 glutInit(&argc, argv);							//===1:Inicia janela
	 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //		:Single mode, RBG
     glutInitWindowSize(600,500);					//		:dimensoes (pixeis)
     glutInitWindowPosition(200,100);				//		:localizacao
	 glutCreateWindow(" Exemplo inicial ");

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 Inicializa();									//===2:Inicializacao estado/parametros 

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
													//===3:Definicao callbaks	
	 glutDisplayFunc(Desenha);						//		:desenho
	 glutKeyboardFunc(Teclado);						//		:eventos teclado
	 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 glutMainLoop();								//===4:Inicia processamento
	 return 1;
}
