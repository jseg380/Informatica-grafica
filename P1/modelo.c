/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Juan Manuel Segura Duarte

=======================================================
	G. Arroyo, J.C. Torres 
	Dpto. Lenguajes y Sistemas Informticos
	(Univ. de Granada)

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details 
 http://www.gnu.org/copyleft/gpl.html

=======================================================/
modulo modelo.c
    Representación del modelo
    Funciones de dibujo
    Función Idle

*/
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


int modo = GL_FILL;
bool iluminacion = true;


/**	void initModel()

Inicializa el modelo y de las variables globales


**/
void
initModel ()
{

}



class Ejes:Objeto3D 
{ 
public: 
    float longitud = 30;
// Dibuja el objeto
void draw( )
{
  glDisable (GL_LIGHTING);
  glBegin (GL_LINES);
  {
    glColor3f (0, 1, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, longitud, 0);

    glColor3f (1, 0, 0);
    glVertex3f (0, 0, 0);
    glVertex3f (longitud, 0, 0);

    glColor3f (0, 0, 1);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, longitud);
  }
  glEnd ();
  // Activar modelo de iluminación solo si el modo es Sólido
  if (modo == GL_FILL && iluminacion)
    glEnable (GL_LIGHTING);

}
} ; 

Ejes ejesCoordenadas;


/**	void Dibuja( void )

Procedimiento de dibujo del modelo. Es llamado por glut cada vez que se debe redibujar.

**/

void Dibuja (void)
{
  static GLfloat  pos[4] = { 5.0, 5.0, 10.0, 0.0 };	// Posicion de la fuente de luz

  float  color[4] = { 0.8, 0.0, 1, 1 };

  glPushMatrix ();		// Apila la transformacion geometrica actual

  glClearColor (0.0, 0.0, 0.0, 1.0);	// Fija el color de fondo a negro

  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Inicializa el buffer de color y el Z-Buffer

  transformacionVisualizacion ();	// Carga transformacion de visualizacion

  glLightfv (GL_LIGHT0, GL_POSITION, pos);	// Declaracion de luz. Colocada aqui esta fija en la escena

  ejesCoordenadas.draw();			// Dibuja los ejes

  glMaterialfv (GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

  /***************************************************************************/
  
  // Dibuja el modelo (A rellenar en prácticas 1,2 y 3)          
  float ladoCubo = 2;

  Cubo c(ladoCubo);

  c.draw();

  float color2[4] = { 0.02, 1, 0.92, 1 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color2);

  glTranslatef(ladoCubo * 1.5, 0, 0);

  Piramide p(ladoCubo, 2 * ladoCubo);

  p.draw();

  float color3[4] = { 0.9, 1, 0.06, 1 };

  glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color3);

  glTranslatef(ladoCubo * 1.5, 0, 0);

  Prisma pr(ladoCubo, ladoCubo * 1.5);

  pr.draw();

  /***************************************************************************/

  glPopMatrix ();		// Desapila la transformacion geometrica


  glutSwapBuffers ();		// Intercambia el buffer de dibujo y visualizacion
}


/**	void idle()

Procedimiento de fondo. Es llamado por glut cuando no hay eventos pendientes.

**/
void idle (int v)
{

  glutPostRedisplay ();		// Redibuja
  glutTimerFunc (30, idle, 0);	// Vuelve a activarse dentro de 30 ms
}


/**
	Funcion de selección de modo
**/
void setModo(int M)
{
  if (iluminacion && modo != GL_FILL)
    alternaIluminacion();
  modo = M;
  glPolygonMode(GL_FRONT_AND_BACK, M);
}


/**
	Funcion de selección de iluminación
**/
void alternaIluminacion()
{
  if (modo == GL_FILL) {
    if (iluminacion) {
      iluminacion = false;
      glDisable(GL_LIGHTING);
    }
    else {
      iluminacion = true;
      glEnable(GL_LIGHTING);
    }
  }
}
