/* ===================================================================================
	LEI - CG
	Computacao Grafica - 2018
	..............................................................  JH /PM
	Trabalho 1 - relogio - Transformacoes geometricas
	
======================================================================================= */


//.................................................... Bibliotecas necessarias
#include <stdio.h>			
#include <math.h>
#include <time.h>
#include <GL/glut.h>
#define PI  3.14159

struct tm *current_time;
GLint second,min,hour;
char texto[30];		            //.. texto, i.e, numeros do relogio = [1..12]


//.................................................... Variaveis
GLint   msecDelay=1000;				//.. definicao do timer (actualizacao)
GLfloat angulo=0.0;
GLfloat angulo1=0.0;
GLfloat angulo2=0.0;
GLfloat raio=70;

//-----------------------------------------------------------------------------------
//																		Inicializacao
//-----------------------------------------------------------------------------------
void inicializa (void)
{   
    glClearColor(0.8, 0.8, 0.6, 1.0);	    //....	Cor para apagar (Preto)
	gluOrtho2D( -100, 100, -100, 100);		//....	Definicao sistema coordenadas area de desenho
	glShadeModel(GL_SMOOTH);				//....  Interpolacao de cor com base na cor dos vertices

}


//-----------------------------------------------------------------------------------
//-------------------------------------------------------------------- INTERACCAO
//-----------------------------------------------------------------------------------
void teclado(unsigned char key, int x, int y){

	switch (key) {	  	
	case 27:					//ESC
		exit(0);
		break;
	}
}



//-----------------------------------------------------------------------------------
//------------------------------------------------------------------------- DESENHO 
//-----------------------------------------------------------------------------------
void desenhaTriangulo(int tam)
{
     glBegin(GL_TRIANGLES);
		glColor3f(0,0,1);
        glVertex3f(-tam,  tam, 0.0);
        glColor3f(0,0,1);
        glVertex3f( tam,  tam, 0.0);
		glColor3f(1,0,0);        
        glVertex3f( 0.0, -tam, 0.0);              
     glEnd();
}

void desenhaTexto(char *string, GLfloat x, GLfloat y) 
{  
	glRasterPos2f(x,y); 
	while (*string)
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++); 
}

void desenhaCirculo(float raio, float lineW)
{
   float rad;	 
   int i;
   glLineWidth(lineW);
   glBegin(GL_LINE_LOOP);
     for (i=0; i<370; i++) {
       rad = i*PI/180.0;
       glVertex2f( raio*cos(rad), raio*sin(rad));
     }
   glEnd();
}


//---------------------------------------- Função callback de desenho (principal)
void desenhaJanela(void)
{
   float r, angrad,angrad1,angrad2, rotacao,rotacao1,rotacao2;
	 
   glClear(GL_COLOR_BUFFER_BIT);		//.. Limpa de acordo com cor predefinida
  
   //-------------------------------- determiar horas, minutos segundos
   time_t timer = time(0);
   current_time = localtime(&timer);
   second = current_time->tm_sec;
   min = current_time->tm_min;
	hour = current_time->tm_hour;

   
	//----------------------------- Circulos
	   glColor3d(1,1,1);
	   desenhaCirculo(raio, 50);
	   sprintf(texto, "%2d", second);
	   desenhaTexto(texto, 8,0);

	   glColor3d(1,0,1);
	   desenhaCirculo((2*raio)/3, 50);
	   sprintf(texto, "%2d:", min);
	   desenhaTexto(texto, 0,0);

	   glColor3d(1,1,0);
	   desenhaCirculo((raio)/3, 50);
	   sprintf(texto, "%2d:", hour);
	   desenhaTexto(texto, -8,0);
	   glColor3d(1,1,1);

  //----------------------------- Traingulo = ponteiro
   angulo = 90 - 6*second;
   angrad= (angulo*PI)/180.0;
   
   angulo1 = 90 - 6*min;
   angrad1= (angulo1*PI)/180.0;
   
   angulo2 = 90 - 30*hour;
   angrad2= (angulo2*PI)/180.0;
   
   rotacao= angulo -90;
   rotacao1= angulo1 -90;
   rotacao2= angulo2 -90;
   
   glPushMatrix();
      glTranslatef( 70*cos(angrad), 70*sin(angrad), 0);
      glRotatef( rotacao, 0,0,1);
      glScalef(0.5, 1.5, 1);
      desenhaTriangulo(10);                                
   glPopMatrix();

   glPushMatrix();
      glTranslatef( 40*cos(angrad1), 40*sin(angrad1), 0);
      glRotatef( rotacao1, 0,0,1);
      glScalef(0.4, 1, 1);
      desenhaTriangulo(10);                                
   glPopMatrix();

   glPushMatrix();
      glTranslatef( 20*cos(angrad2), 20*sin(angrad2), 0);
      glRotatef( rotacao2, 0,0,1);
      glScalef(0.3, 0.5, 1);
      desenhaTriangulo(10);                                
   glPopMatrix();


  

   
   glutSwapBuffers();					//.. actualiza ecran
 
}
  
void Timer(int value) 
{
	glutPostRedisplay();
	glutTimerFunc(msecDelay,Timer, 1);
}




//-----------------------------------------------------------------------------------
//																		         MAIN
//-----------------------------------------------------------------------------------
int main(int argc, char** argv)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 glutInit(&argc, argv);							//===1:Inicia janela
	 glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);   //	  :Single mode, RBG
     glutInitWindowSize(600,600);					//	  :dimensoes (pixeis)
     glutInitWindowPosition(200,100);				//	  :localizacao
	 glutCreateWindow("Relogio");

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 inicializa();									//===2:Inicializacao estado/parametros 

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
													//===3:Definicao callbaks	
	 glutDisplayFunc(desenhaJanela);						//	  :desenho
	 glutKeyboardFunc(teclado);						//	  :eventos teclado
 	 glutTimerFunc(msecDelay, Timer, 1);			//    :controlar o tempo de actualizao do Desenha
	 
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	 glutMainLoop();								//===4:Inicia processamento
	 return 1;
}

