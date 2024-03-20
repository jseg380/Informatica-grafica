/*	Prácticas de Informática Gráfica

	Grupo C					Curso 2022-23
 	
	Codigo base para la realización de las practicas de IG
	
	Estudiante: Juan Manuel Segura Duarte

	Programa principal
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

=======================================================

	practicasIG.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"
//#include "hiply.h"


Cubo::Cubo(float l)
    : lado(l)
{
}

void
Cubo::draw ()
{
  glBegin (GL_QUAD_STRIP);
    /* Caras transversales */
    glNormal3f (0.0, 0.0, 1.0);	/*Vertical delantera */
    glVertex3f (lado, lado, lado);
    glVertex3f (0, lado, lado);
    glVertex3f (lado, 0, lado);
    glVertex3f (0, 0, lado);
    glNormal3f (0.0, -1.0, 0.0);	/*Inferior */
    glVertex3f (lado, 0, 0);
    glVertex3f (0, 0, 0);
    glNormal3f (0.0, 0.0, -1.0);	/* Vertical hacia atras */
    glVertex3f (lado, lado, 0);
    glVertex3f (0, lado, 0);
    glNormal3f (0.0, 1.0, 0.0);	/* Superior, horizontal */
    glVertex3f (lado, lado, lado);
    glVertex3f (0, lado, lado);
  
  glEnd ();
  glBegin (GL_QUADS);
    /* Costado derecho */
    glNormal3f (1.0, 0.0, 0.0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, lado, 0);
    glVertex3f (lado, lado, lado);
    glVertex3f (lado, 0, lado);
    /* Costado izquierdo */
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, lado);
    glVertex3f (0, lado, lado);
    glVertex3f (0, lado, 0);
  
  glEnd ();
}

Piramide::Piramide(float l, float a)
    : lado(l),
      altura(a)
{
}

void
Piramide::draw ()
{
  glBegin(GL_QUADS);
    /* Base */
    glNormal3f (0.0, -1.0, 0.0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, 0, lado);
    glVertex3f (0, 0, lado);
    glVertex3f (0, 0, 0);
  glEnd();
  glBegin(GL_TRIANGLES);
    // Las normales han sido calculadas con la fórmula del guión
    // Hasta que no se ha creado el prisma la iluminación no se aplicaba a
    // la pirámide
    /* Delantera */
    glNormal3f (0, 1/sqrt(17), 4/sqrt(17)); // Calculada con esos P0, P1 y P2
    glVertex3f (lado, 0, lado); // P0
    glVertex3f (lado/2, altura, lado/2); // P1
    glVertex3f (0, 0, lado); // P2
    /* Derecha */
    glNormal3f (4/sqrt(17), 1/sqrt(17), 0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado/2, altura, lado/2);
    glVertex3f (lado, 0, lado);
    /* Trasera */
    glNormal3f (0, 1/sqrt(17), -4/sqrt(17));
    glVertex3f (0, 0, 0);
    glVertex3f (lado/2, altura, lado/2);
    glVertex3f (lado, 0, 0);
    /* Izquierda */
    glNormal3f (-4/sqrt(17), 1/sqrt(17), 0);
    glVertex3f (0, 0, lado);
    glVertex3f (lado/2, altura, lado/2);
    glVertex3f (0, 0, 0);
  glEnd();
}

Prisma::Prisma(float l, float a)
    : lado(l),
      altura(a)
{
}

void
Prisma::draw()
{
  glBegin(GL_TRIANGLES);
    /* Base inferior */
    glNormal3f (0.0, -1.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado/2, 0, lado);
    /* Base superior */
    glNormal3f (0.0, 1.0, 0.0);
    glVertex3f (0, altura, 0);
    glVertex3f (lado/2, altura, lado);
    glVertex3f (lado, altura, 0);
  glEnd();
  glBegin(GL_QUAD_STRIP);
    /* Lado trasero */
    glNormal3f (0.0, 0.0, -1.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, altura, 0);
    glVertex3f (lado, 0, 0);
    glVertex3f (lado, altura, 0);
    /* Lado derecho */
    glNormal3f (1/sqrt(2), 0.0, 1/sqrt(2));
    glVertex3f (lado/2, 0, lado);
    glVertex3f (lado/2, altura, lado);
    /* Lado izquierdo */
    glNormal3f (-1/sqrt(2), 0.0, 1/sqrt(2));
    glVertex3f (0, 0, 0);
    glVertex3f (0, altura, 0);
  glEnd();
}




/*=================================================*/

/**	int main( int argc, char *argv[] )	
	Programa principal.
	
	Inicializa glut y openGL
	Crea la ventana X
	Inicializa las variables globales
	lanza los gestores de eventos	
**/

int main (int argc, char *argv[])
{
// Inicializa glu y openGL
  glutInit (&argc, argv);

// Crea una ventana X para la salida grafica en la posicion 0,0 con tamaño 800x800, con colores RGB-alfa, con doble buffer, y 
// buffer de profundidad



  glutInitWindowPosition (0, 0);
  glutInitWindowSize (800, 800);
  glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutCreateWindow ("IG. Curso 2023/24. Autor: Juan Manuel Segura Duarte");

// Inicializa las variables del modelo
  initModel ();

// Inicializa las funciones de dibujo y cambio de tamanyo de la ventana X
  glutDisplayFunc (Dibuja);
  glutReshapeFunc (inicializaVentana);

// FUNCIONES DE INTERACCION
  glutKeyboardFunc (letra);
  glutSpecialFunc (especial);

  glutMouseFunc (clickRaton);
  glutMotionFunc (RatonMovido);

// Funcion de fondo
  glutTimerFunc (30, idle, 0);

// Inicializa parametros de openGL
  glEnable (GL_DEPTH_TEST);
  glEnable (GL_CULL_FACE);
  glEnable (GL_LIGHTING);
  glEnable (GL_LIGHT0);


// Lanza el gestor de eventos de glut
  glutMainLoop ();
  return 0;
}
