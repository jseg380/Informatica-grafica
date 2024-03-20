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
#include <GL/freeglut_std.h>
#include <GL/gl.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>		// Libreria de utilidades de OpenGL
#include "practicasIG.h"


/**	void initModel(int m)

Inicializa el modelo y de las variables globales


**/
void
initModel (int m = 0, const char *archivo = nullptr)
{
  modo = GL_FILL;
  instancias = 8;
  modoCarga = m;
  iluminacion = true;
  sombreadoSmooth = true;

  busto = Malla("./plys/beethoven.ply");
  coche = Malla("./plys/big_dodge.ply");
  peon = MallaRevolucion("./plys/perfil.ply", 4);

  if (m == 1) {
    mallaLoad = Malla(archivo);
  }
  else if (m == 2) {
    mallaSpin = MallaRevolucion(archivo, instancias);
  }
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
  // PRÁCTICA 1

  // glPointSize(3);
  // glEnable(GL_COLOR_MATERIAL);

  // Cubo
  // glColor3fv(color);
  // float ladoCubo = 2;
  // Cubo c(ladoCubo);
  // c.draw();

  // Pirámide
  // float color2[4] = { 0.02, 1, 0.92, 1 };
  // glColor3fv(color2);
  // glTranslatef(ladoCubo * 1.5, 0, 0);
  // Piramide p(ladoCubo, 2 * ladoCubo);
  // p.draw();

  // Prisma
  // float color3[4] = { 0.9, 1, 0.06, 1 };
  // glColor3fv(color3);
  // glTranslatef(ladoCubo * 1.5, 0, 0);
  // Prisma pr(ladoCubo, ladoCubo * 1.5);
  // pr.draw();

  /***************************************************************************/
  // PRÁCTICA 2
  
  glPointSize(1);
  glEnable(GL_COLOR_MATERIAL);

  glTranslatef(7, 6, 5);
  glColor3f(0, 1, 0);

  if (modoCarga == 0) {
    busto.draw(sombreadoSmooth);

    glTranslatef(12, 0, 0);
    glColor3f(1, 0, 1);

    peon.draw(sombreadoSmooth);

    glTranslatef(15, 0, 0);
    glColor3f(1, 0, 0);

    // El coche se dibujará en modo de sombreado contrario al busto
    coche.draw(!sombreadoSmooth);
  }
  else if (modoCarga == 1) {
    mallaLoad.draw(sombreadoSmooth);
  }
  else if (modoCarga == 2) {
    mallaSpin.draw(sombreadoSmooth);
  }


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


/**
  Función de alternación de sombreado
**/
void alternaSombreado()
{
  if (sombreadoSmooth) {
    glShadeModel(GL_FLAT);
    sombreadoSmooth = false;
  }
  else {
    glShadeModel(GL_SMOOTH);
    sombreadoSmooth = true;
  }

  Dibuja();
}



/***************************************************************************/
// PRÁCTICA 1

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
    /*
    glNormal3f (-1.0, 0.0, 0.0);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, lado);
    glVertex3f (0, lado, lado);
    glVertex3f (0, lado, 0);
    */
  glEnd ();
  glBegin (GL_TRIANGLES);
    /* Adición nuevo vértice */
    // vértice nuevo en (x*-0.5, y*0.5, z*0.5)
    glVertex3f (lado*-0.5, lado*0.5, lado*0.5);
    glVertex3f (0, 0, lado);
    glVertex3f (0, lado, lado);
    // Cara
    glVertex3f (lado*-0.5, lado*0.5, lado*0.5);
    glVertex3f (0, lado, lado);
    glVertex3f (0, lado, 0);
    // Cara
    glVertex3f (lado*-0.5, lado*0.5, lado*0.5);
    glVertex3f (0, lado, 0);
    glVertex3f (0, 0, 0);
    // Cara
    glVertex3f (lado*-0.5, lado*0.5, lado*0.5);
    glVertex3f (0, 0, 0);
    glVertex3f (0, 0, lado);
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


/***************************************************************************/
// PRÁCTICA 2

// Funciones auxiliares
std::vector<float> calculaNormalCara(const std::vector<float> & v, 
                                     const std::vector<int> & c,
                                     int numCara)
{
  // pX es un punto de la cara, que contiene el número de vértice
  int v0 = c[numCara * 3 + 0],
      v1 = c[numCara * 3 + 1],
      v2 = c[numCara * 3 + 2];
  float v0v1[3], v0v2[3], producto[3], modulo;
  std::vector<float> resultado(3);

  // Calcular vector v0, v1
  for (int i = 0; i < 3; i++)
    v0v1[i] = v[v1 * 3 + i] - v[v0 * 3 + i];

  // Calcular vector v0, v2
  for (int i = 0; i < 3; i++)
    v0v2[i] = v[v2 * 3 + i] - v[v0 * 3 + i];

  // Calcular producto vectorial de v0v1 x v0v2
  producto[0] = v0v1[1] * v0v2[2] - v0v1[2] * v0v2[1];
  producto[1] = v0v1[2] * v0v2[0] - v0v1[0] * v0v2[2];
  producto[2] = v0v1[0] * v0v2[1] - v0v1[1] * v0v2[0];

  // Calcular modulo del vector
  modulo = pow(producto[0], 2) + pow(producto[1], 2) + pow(producto[2], 2);
  modulo = sqrt(modulo);
  
  // Normalizar el vector
  for (int i = 0; i < 3; i++)
    if (modulo > 0)
      resultado[i] = producto[i] / modulo;

  return resultado;
}


Malla::Malla(){}

Malla::Malla(const char *nombre_archivo_pse)
{
  ply::read(nombre_archivo_pse, vertices, caras);

  // Inicializar el vector de normales de vertices a todo 0
  normalesVertices = std::vector<float>(vertices.size(), 0);
  
  // Para cada cara
  for (int i = 0; i < caras.size()/3; i++)
  {
    std::vector<float> normal = calculaNormalCara(vertices, caras, i);

    // Sumar la normal de cara a los vertices que la componen
    for (int j = 0; j < 3; j++)
    {
      normalesVertices[caras[i * 3 + j] * 3 + 0] += normal[0];
      normalesVertices[caras[i * 3 + j] * 3 + 1] += normal[1];
      normalesVertices[caras[i * 3 + j] * 3 + 2] += normal[2];
    }
  }

  // Para cada vértice normalizar su normal
  for (int i = 0; i < vertices.size()/3; i++)
  {
    int modulo = 0;
    for (int j = 0; j < 3; j++)
      modulo += pow(normalesVertices[i * 3 + j], 2);
    modulo = sqrt(modulo);
    
    // Normalizar la normal de vértice
    for (int j = 0; j < 3; j++)
      if (modulo > 0)
        normalesVertices[i * 3 + j] /= modulo;
  }
}


void
Malla::drawFlat()
{
  glShadeModel(GL_FLAT);

  glBegin(GL_TRIANGLES);
  {
    for (int i = 0; i < caras.size()/3; i++)
    {
      // Normal de cara a partir de la normal de los vértices
      std::vector<float> normal(3, 0);

      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
          normal[k] += normalesVertices[caras[i * 3 + j] * 3 + k];

      int modulo = 0;
      for (int j = 0; j < 3; j++)
        modulo += pow(normal[j], 2);
      modulo = sqrt(modulo);
      
      // Normalizar
      for (int j = 0; j < 3; j++)
        if (modulo > 0)
          normal[j] /= modulo;

      // Normal de cara
      glNormal3f(normal[0], normal[1], normal[2]);

      // Vértices
        glVertex3f(vertices[caras[i * 3 + 0] * 3 + 0],
                   vertices[caras[i * 3 + 0] * 3 + 1],
                   vertices[caras[i * 3 + 0] * 3 + 2]);
        glVertex3f(vertices[caras[i * 3 + 1] * 3 + 0],
                   vertices[caras[i * 3 + 1] * 3 + 1],
                   vertices[caras[i * 3 + 1] * 3 + 2]);
        glVertex3f(vertices[caras[i * 3 + 2] * 3 + 0],
                   vertices[caras[i * 3 + 2] * 3 + 1],
                   vertices[caras[i * 3 + 2] * 3 + 2]);
    }
  }
  glEnd();
}

void
Malla::drawSmooth()
{
  glShadeModel(GL_SMOOTH);

  glBegin(GL_TRIANGLES);
  {
    // Recorriendo por vertices de caras
    for (int i = 0; i < caras.size(); i++)
    {
      // Normal del vértice
      glNormal3f(normalesVertices[caras[i] * 3 + 0],
                 normalesVertices[caras[i] * 3 + 1],
                 normalesVertices[caras[i] * 3 + 2]);

      // Vértice
      glVertex3f(vertices[caras[i] * 3 + 0],
                 vertices[caras[i] * 3 + 1],
                 vertices[caras[i] * 3 + 2]);
    }
  }
  glEnd();
}

void Malla::draw(){}

void
Malla::draw(bool sombreadoSmooth)
{
  if (sombreadoSmooth) {
    drawSmooth();
  }
  else {
    drawFlat();
  }
}

void
Malla::dibujaNormales()
{
  glColor3f(0, 0, 1);
  glPointSize(3);
  glBegin(GL_POINTS);
  for (int i = 0; i < normalesVertices.size()/3; i++)
  {
    glVertex3f(normalesVertices[i * 3 + 0],
               normalesVertices[i * 3 + 1],
               normalesVertices[i * 3 + 2]);
  }
  glEnd();
}


MallaRevolucion::MallaRevolucion() {}

MallaRevolucion::MallaRevolucion(const char *perfil, int instancias)
{
  if (instancias <= 3)
    return;

  ply::read_vertices(perfil, verticesPerfil);

  int m = verticesPerfil.size()/3;

  for (int i = 0; i < instancias; i++)
    for (int j = 0; j < m; j++)
    {
      double angulo = 2 * i * M_PI / (instancias - 1);

      vertices.push_back(verticesPerfil[j] * cos(angulo) + verticesPerfil[j + 2] * sin(angulo));
      vertices.push_back(verticesPerfil[j + 1]);
      vertices.push_back(-verticesPerfil[j] * sin(angulo) + verticesPerfil[j + 2] * cos(angulo));
    }

  for (int i = 0; i < instancias - 1; i++)
    for (int j = 0; j < m - 1; j++)
    {
      int k = i * m + j;

      // Triángulo formado por k, k+m, k+m+1
      caras.push_back(k);
      caras.push_back(k + m);
      caras.push_back(k + m + 1);
      
      // Triángulo formado por k, k+m+1, k+1
      caras.push_back(k);
      caras.push_back(k + m + 1);
      caras.push_back(k + 1);
    }

  // Inicializar el vector de normales de vertices a todo 0
  normalesVertices = std::vector<float>(vertices.size(), 0);
  
  // Para cada cara
  for (int i = 0; i < caras.size()/3; i++)
  {
    std::vector<float> normal = calculaNormalCara(vertices, caras, i);

    // Sumar la normal de cara a los vertices que la componen
    for (int j = 0; j < 3; j++)
    {
      normalesVertices[caras[i * 3 + j] * 3 + 0] += normal[0];
      normalesVertices[caras[i * 3 + j] * 3 + 1] += normal[1];
      normalesVertices[caras[i * 3 + j] * 3 + 2] += normal[2];
    }
  }

  // Para cada vértice normalizar su normal
  for (int i = 0; i < vertices.size()/3; i++)
  {
    int modulo = 0;
    for (int j = 0; j < 3; j++)
      modulo += pow(normalesVertices[i * 3 + j], 2);
    modulo = sqrt(modulo);
    
    // Normalizar la normal de vértice
    for (int j = 0; j < 3; j++)
      if (modulo > 0)
        normalesVertices[i * 3 + j] /= modulo;
  }
}

void
MallaRevolucion::drawFlat()
{
  glShadeModel(GL_FLAT);

  glBegin(GL_TRIANGLES);
  {
    for (int i = 0; i < caras.size()/3; i++)
    {
      // Normal de cara a partir de la normal de los vértices
      std::vector<float> normal(3, 0);

      for (int j = 0; j < 3; j++)
        for (int k = 0; k < 3; k++)
          normal[k] += normalesVertices[caras[i * 3 + j] * 3 + k];

      int modulo = 0;
      for (int j = 0; j < 3; j++)
        modulo += pow(normal[j], 2);
      modulo = sqrt(modulo);
      
      // Normalizar
      for (int j = 0; j < 3; j++)
        if (modulo > 0)
          normal[j] /= modulo;

      // Normal de cara
      glNormal3f(normal[0], normal[1], normal[2]);

      // Vértices
        glVertex3f(vertices[caras[i * 3 + 0] * 3 + 0],
                   vertices[caras[i * 3 + 0] * 3 + 1],
                   vertices[caras[i * 3 + 0] * 3 + 2]);
        glVertex3f(vertices[caras[i * 3 + 1] * 3 + 0],
                   vertices[caras[i * 3 + 1] * 3 + 1],
                   vertices[caras[i * 3 + 1] * 3 + 2]);
        glVertex3f(vertices[caras[i * 3 + 2] * 3 + 0],
                   vertices[caras[i * 3 + 2] * 3 + 1],
                   vertices[caras[i * 3 + 2] * 3 + 2]);
    }
  }
  glEnd();

}

void
MallaRevolucion::drawSmooth()
{
  glShadeModel(GL_SMOOTH);

  glBegin(GL_TRIANGLES);
  {
    // Recorriendo por vertices de caras
    for (int i = 0; i < caras.size(); i++)
    {
      // Normal del vértice
      glNormal3f(normalesVertices[caras[i] * 3 + 0],
                 normalesVertices[caras[i] * 3 + 1],
                 normalesVertices[caras[i] * 3 + 2]);

      // Vértice
      glVertex3f(vertices[caras[i] * 3 + 0],
                 vertices[caras[i] * 3 + 1],
                 vertices[caras[i] * 3 + 2]);
    }
  }
  glEnd();
}

void MallaRevolucion::draw() {}

void
MallaRevolucion::draw(bool sombreadoSmooth)
{
  if (sombreadoSmooth) {
    drawSmooth();
  }
  else {
    drawFlat();
  }
}
