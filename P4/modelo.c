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
#include "lector-jpg.h"


/**	void initModel(int m)

Inicializa el modelo y de las variables globales


**/
void
initModel (int m = 0, const char *archivo = nullptr)
{
  practica = 4;
  modo = GL_FILL;
  instancias = 9;
  modoCarga = m;
  iluminacion = true;
  sombreadoSmooth = true;

  if (m == 1) {
    mallaLoad = MallaPly(archivo);
  }
  else if (m == 2) {
    mallaSpin = MallaRevolucion(archivo, instancias);
  }
  else {
    if (practica == 1) {
      float ladoCubo = 2;
      c = Cubo(ladoCubo);
      p = Piramide(ladoCubo, 2 * ladoCubo);
      pr = Prisma(ladoCubo, 1.5 * ladoCubo);
    }
    else if (practica == 2) {
      busto = MallaPly("./plys/beethoven.ply");
      coche = MallaPly("./plys/big_dodge.ply");
      peon = MallaRevolucion("./plys/perfil.ply", instancias);
    }
    else if (practica == 3) {
      raValor = 0;
      rbValor = 0;
      taValor = 0;
      animacion = false;
      for (int i = 0; i < 3; i++)
        estadoAnimacion[i] = true;

      forkliftBody = MallaPly("./plys/forklift_body.ply");
      forkliftMast = MallaPly("./plys/forklift_mast.ply");
      forkliftFork = MallaPly("./plys/forklift_forks.ply");
    }
    else if (practica == 4) {
      dado = Dado(1);
      dado.aplicarTextura("./texturas/dado.jpg");

      lata = Lata("./plys/lata-pcue.ply", instancias);
      lata.aplicarTextura("./texturas/lata_pepsi.jpg");
      tapaSuperior = Tapa("./plys/lata-psup.ply", instancias);
      tapaInferior = Tapa("./plys/lata-pinf.ply", instancias);
    }
    else {
      exit(2);
    }
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
  // PRÁCTICAS

  glPointSize(2);
  glEnable(GL_COLOR_MATERIAL);

  if (modoCarga == 1) {
    glColor3f(0, 1, 0);
    mallaLoad.draw(sombreadoSmooth);
  }
  else if (modoCarga == 2) {
    glColor3f(1, 0, 1);
    mallaSpin.draw(sombreadoSmooth);
  }
  else if (practica == 1) {
    // PRÁCTICA 1

    // Cubo
    glColor3fv(color);
    float ladoCubo = 2;
    c.draw();

    // Pirámide
    float color2[4] = { 0.02, 1, 0.92, 1 };
    glColor3fv(color2);
    glTranslatef(ladoCubo * 1.5, 0, 0);
    p.draw();

    // Prisma
    float color3[4] = { 0.9, 1, 0.06, 1 };
    glColor3fv(color3);
    glTranslatef(ladoCubo * 1.5, 0, 0);
    pr.draw();
  }
  else if (practica == 2) {
    // PRÁCTICA 2
    
    glTranslatef(7, 6, 5);
    glColor3f(0, 1, 0);

    busto.draw(sombreadoSmooth);

    glTranslatef(12, 0, 0);
    glColor3f(1, 0, 1);

    peon.draw(sombreadoSmooth);

    glTranslatef(15, 0, 0);
    glColor3f(1, 0, 0);

    // El coche se dibujará en modo de sombreado contrario al busto
    coche.draw(!sombreadoSmooth);
  }
  else if (practica == 3) {
    // PRÁCTICA 3
    Nodo n;
    Translacion t1(1, 0, 3.2),
                ta(0, taValor, 0);
    Rotacion ra(raValor, 1, 0, 0),
             rb(rbValor, 0, 0, 1);

    n.aniadeHijo(&t1);

    t1.aniadeHijo(&forkliftBody);
    t1.aniadeHijo(&ra);

    ra.aniadeHijo(&forkliftMast);
    ra.aniadeHijo(&ta);

    ta.aniadeHijo(&rb);

    rb.aniadeHijo(&forkliftFork);

    glColor3f(0.5, 0.5, 0.5);
    n.draw(sombreadoSmooth);
  }
  else if (practica == 4) {
    // PRÁCTICA 4
  
    Nodo d, l;
    Translacion t1(2, 0, 0);
    Rotacion r1(170, 0, 1, 0);

    // Dado
    d.aniadeHijo(&dado);

    glColor3f(0.95, 0.95, 0.95);
    d.draw(sombreadoSmooth);

    // Lata
    l.aniadeHijo(&t1);
    t1.aniadeHijo(&r1);
    r1.aniadeHijo(&lata);
    r1.aniadeHijo(&tapaSuperior);
    r1.aniadeHijo(&tapaInferior);

    glColor3f(0.8, 0.8, 0.8);
    l.draw(sombreadoSmooth);
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
  if (animacion) {
    int salida;
    if (estadoAnimacion[0])
      salida = cambiaAnguloMastil(DEFAULT_ROTATION_A);
    else
      salida = cambiaAnguloMastil(-DEFAULT_ROTATION_A);
    if (!salida)
      estadoAnimacion[0] = !estadoAnimacion[0];

    if (estadoAnimacion[1])
      salida = cambiaDesplazamientoHorquillas(DEFAULT_TRANSLATION_A);
    else
      salida = cambiaDesplazamientoHorquillas(-DEFAULT_TRANSLATION_A);
    if (!salida)
      estadoAnimacion[1] = !estadoAnimacion[1];

    if (estadoAnimacion[2])
      salida = cambiaAnguloHorquillas(DEFAULT_ROTATION_B);
    else
      salida = cambiaAnguloHorquillas(-DEFAULT_ROTATION_B);
    if (!salida)
      estadoAnimacion[2] = !estadoAnimacion[2];
  }
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


/**
  Función para resetear los valores de las transformaciones
**/
void reseteaTransformaciones()
{
  raValor = 0;
  taValor = 0;
  rbValor = 0;
}


/**
  Función para modificar el ángulo del mástil
**/
bool cambiaAnguloMastil(float cambio)
{
  float resultado = raValor + cambio;
  if (resultado > -3.2 && resultado < 15.0) {
    raValor = resultado;
    return true;
  }
  return false;
}


/**
  Función para modificar la translación de las horquillas
**/
bool cambiaDesplazamientoHorquillas(float cambio)
{
  float resultado = taValor + cambio;
  if (resultado > -0.2 && resultado < 3.6) {
    taValor = resultado;
    return true;
  }
  return false;
}


/**
  Función para modificar el ángulo de las horquillas
**/
bool cambiaAnguloHorquillas(float cambio)
{
  float resultado = rbValor + cambio,
        limite = 10;
  if (resultado > -limite && resultado < limite) {
    rbValor = resultado;
    return true;
  }
  return false;
}

/**
  Función de alternación de animación
**/
void alternaAnimacion()
{
  animacion = !animacion;
}


/**
  Función para modificar un valor de transformacion
**/
void modificaValorTransformacion(float & var, float cambio)
{
  float resultado = var + cambio;
  if (resultado > 0.01 && resultado < 3)
    var = resultado;
}




/***************************************************************************/
// Práctica 1

Objeto3D::Objeto3D() {
  texId = 0;
};

void Objeto3D::draw() {}

void Objeto3D::draw(bool sombreadoSmooth) {
  for (auto hijo : hijos) {
    hijo->draw(sombreadoSmooth);
  }
}

void Objeto3D::aniadeHijo(Objeto3D *nuevoHijo) {
  hijos.push_back(nuevoHijo);
}

void Objeto3D::aplicarTextura(const char * nombreTextura)
{
  jpeg = LeerArchivoJPEG(nombreTextura, anchura, altura);

  glGenTextures(1, &texId);
  glBindTexture(GL_TEXTURE_2D, texId);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchura, altura, 0, GL_RGB,
               GL_UNSIGNED_BYTE, jpeg);
}


///////////////////////////////////////////////////////////
// Cubo
Cubo::Cubo() {}

Cubo::Cubo(float l)
    : lado(l)
{}

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
    // glNormal3f (-1.0, 0.0, 0.0);
    // glVertex3f (0, 0, 0);
    // glVertex3f (0, 0, lado);
    // glVertex3f (0, lado, lado);
    // glVertex3f (0, lado, 0);
  glEnd ();

  // Defensa práctica
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

void Cubo::draw (bool sombreadoSmooth) {this->draw();}


///////////////////////////////////////////////////////////
// Piramide
Piramide::Piramide() {}

Piramide::Piramide(float l, float a)
    : lado(l),
      altura(a)
{}

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

void Piramide::draw (bool sombreadoSmooth) {this->draw();}


///////////////////////////////////////////////////////////
// Prisma
Prisma::Prisma() {}

Prisma::Prisma(float l, float a)
    : lado(l),
      altura(a)
{}

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

void Prisma::draw (bool sombreadoSmooth) {this->draw();}


/***************************************************************************/
// Práctica 2

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
Malla::dibujaNormales(bool sombreadoSmooth)
{
  glColor3f(0, 0, 1);
  glPointSize(3);
  if (sombreadoSmooth) {
    glBegin(GL_POINTS);
    for (int i = 0; i < normalesVertices.size()/3; i++)
    {
      glVertex3f(normalesVertices[i * 3 + 0],
                 normalesVertices[i * 3 + 1],
                 normalesVertices[i * 3 + 2]);
    }
    glEnd();
  }
  else {
  }
}


MallaPly::MallaPly(){}

MallaPly::MallaPly(const char *nombre_archivo_pse)
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


MallaRevolucion::MallaRevolucion() {}

MallaRevolucion::MallaRevolucion(const char *perfil, int instancias)
{
  if (instancias <= 3)
    return;

  ply::read_vertices(perfil, verticesPerfil);

  int m = verticesPerfil.size()/3;

  for (int i = 0; i < instancias; i++) {
    double angulo = (2 * i * M_PI) / (instancias - 1);
    for (int j = 0; j < m; j++) {
      vertices.push_back(verticesPerfil[j * 3 + 0] * cos(angulo) - verticesPerfil[j * 3 + 2] * sin(angulo));
      vertices.push_back(verticesPerfil[j * 3 + 1]);
      vertices.push_back(verticesPerfil[j * 3 + 2] * cos(angulo) + verticesPerfil[j * 3 + 0] * sin(angulo));
    }
  }

  int mod = (instancias - 1) * verticesPerfil.size()/3;
  for (int i = 0; i < instancias - 1; i++)
    for (int j = 0; j < m - 1; j++)
    {
      int k = i * m + j;

      // Triángulo formado por k, k+m, k+m+1
      caras.push_back((k + m) % mod);
      caras.push_back((k) % mod);
      caras.push_back((k + m + 1) % mod);
      
      // Triángulo formado por k, k+m+1, k+1
      caras.push_back((k + m + 1) % mod);
      caras.push_back((k) % mod);
      caras.push_back((k + 1) % mod);
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

void MallaRevolucion::drawFlat()
{
  Malla::drawFlat();

  // Tapa superior
  glBegin(GL_TRIANGLES);
  int m = verticesPerfil.size() / 3;
  for (int i = 0; i < instancias - 1; i++) {
    glNormal3f(0, 1, 0);
    glVertex3f(vertices[(i + 1) * m * 3 - 3],
               vertices[(i + 1) * m * 3 - 2],
               vertices[(i + 1) * m * 3 - 1]);
    glVertex3f(0,
               vertices[(i + 1) * m * 3 - 2],
               0);
    glVertex3f(vertices[(i + 2) * m * 3 - 3],
               vertices[(i + 2) * m * 3 - 2],
               vertices[(i + 2) * m * 3 - 1]);
  }
  glEnd();

  // Tapa inferior
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < instancias - 1; i++) {
    glNormal3f(0, -1, 0);
    glVertex3f(vertices[(i + 1) * m * 3 + 0],
               vertices[(i + 1) * m * 3 + 1],
               vertices[(i + 1) * m * 3 + 2]);
    glVertex3f(0,
               vertices[i * m * 3 + 1],
               0);
    glVertex3f(vertices[i * m * 3 + 0],
               vertices[i * m * 3 + 1],
               vertices[i * m * 3 + 2]);
  }
  glEnd();
}

void MallaRevolucion::drawSmooth()
{
  Malla::drawSmooth();

  // Tapa superior
  glBegin(GL_TRIANGLES);
  int m = verticesPerfil.size() / 3;
  for (int i = 0; i < instancias - 1; i++) {
    glNormal3f(0, 1, 0);
    glVertex3f(vertices[(i + 1) * m * 3 - 3],
               vertices[(i + 1) * m * 3 - 2],
               vertices[(i + 1) * m * 3 - 1]);
    glNormal3f(0, 1, 0);
    glVertex3f(0,
               vertices[(i + 1) * m * 3 - 2],
               0);
    glNormal3f(0, 1, 0);
    glVertex3f(vertices[(i + 2) * m * 3 - 3],
               vertices[(i + 2) * m * 3 - 2],
               vertices[(i + 2) * m * 3 - 1]);
  }
  glEnd();

  // Tapa inferior
  glBegin(GL_TRIANGLES);
  for (int i = 0; i < instancias - 1; i++) {
    glNormal3f(0, -1, 0);
    glVertex3f(vertices[(i + 1) * m * 3 + 0],
               vertices[(i + 1) * m * 3 + 1],
               vertices[(i + 1) * m * 3 + 2]);
    glNormal3f(0, -1, 0);
    glVertex3f(0,
               vertices[i * m * 3 + 1],
               0);
    glNormal3f(0, -1, 0);
    glVertex3f(vertices[i * m * 3 + 0],
               vertices[i * m * 3 + 1],
               vertices[i * m * 3 + 2]);
  }
  glEnd();
}

float MallaRevolucion::calcularDistanciaPuntos(int p1, int p2)
{
  float restaX = verticesPerfil[p2 * 3 + 0] - verticesPerfil[p1 * 3 + 0],
        restaY = verticesPerfil[p2 * 3 + 1] - verticesPerfil[p1 * 3 + 1],
        restaZ = verticesPerfil[p2 * 3 + 2] - verticesPerfil[p1 * 3 + 2];

  return sqrtf(pow(restaX, 2) + pow(restaY, 2) + pow(restaZ, 2));
}



/*****************************************************************************/
// Práctica 3

void Transformacion::draw(bool sombreadoSmooth)
{
  glPushMatrix();
  transform();
  for (auto hijo : hijos) {
    hijo->draw(sombreadoSmooth);
  }
  glPopMatrix();
}


Translacion::Translacion (float x, float y, float z)
{
  this->x = x;
  this->y = y;
  this->z = z;
}

void Translacion::transform()
{
  glTranslatef(x, y, z);
}


Rotacion::Rotacion (float angulo, float x, float y, float z)
{
  this->angulo = angulo;
  this->x = x;
  this->y = y;
  this->z = z;
}

void Rotacion::transform()
{
  glRotatef(angulo, x, y, z);
}

/***************************************************************************/
// Práctica 4

Dado::Dado() {}

Dado::Dado(float lado):Cubo(lado) {}

void Dado::draw()
{
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texId);

  glBegin (GL_QUADS);
    // Cara delantera (+z)
    glNormal3f (0.0, 0.0, 1.0);
    glTexCoord2f (0.5, 0.51); glVertex3f (lado, lado, lado);
    glTexCoord2f (0.74, 0.51); glVertex3f (0, lado, lado);
    glTexCoord2f (0.74, 0.743); glVertex3f (0, 0, lado);
    glTexCoord2f (0.5, 0.743); glVertex3f (lado, 0, lado);


    // Tapa inferior (-y)
    glNormal3f (0.0, -1.0, 0.0);
    glTexCoord2f (0.97, 0.505); glVertex3f (lado, 0, 0);
    glTexCoord2f (0.77, 0.505); glVertex3f (lado, 0, lado);
    glTexCoord2f (0.77, 0.745); glVertex3f (0, 0, lado);
    glTexCoord2f (0.97, 0.745); glVertex3f (0, 0, 0);


    // Cara trasera (-z)
    glNormal3f (0.0, 0.0, -1.0);
    glTexCoord2f (0.013, 0.745); glVertex3f (0, 0, 0);
    glTexCoord2f (0.245, 0.745); glVertex3f (0, lado, 0);
    glTexCoord2f (0.245, 0.505); glVertex3f (lado, lado, 0);
    glTexCoord2f (0.013, 0.505); glVertex3f (lado, 0, 0);


    // Tapa superior (+y)
    glNormal3f (0.0, 1.0, 0.0);
    glTexCoord2f (0.49, 0.74); glVertex3f (lado, lado, 0);
    glTexCoord2f (0.253, 0.74); glVertex3f (0, lado, 0);
    glTexCoord2f (0.253, 0.51); glVertex3f (0, lado, lado);
    glTexCoord2f (0.49, 0.51); glVertex3f (lado, lado, lado);


    // Cara derecha (+x)
    glNormal3f (1.0, 0.0, 0.0);
    glTexCoord2f (0.51, 0.27); glVertex3f (lado, 0, 0);
    glTexCoord2f (0.51, 0.49); glVertex3f (lado, lado, 0);
    glTexCoord2f (0.74, 0.49); glVertex3f (lado, lado, lado);
    glTexCoord2f (0.74, 0.27); glVertex3f (lado, 0, lado);


    // Cara izquierda (-x)
    glNormal3f (-1.0, 0.0, 0.0);
    glTexCoord2f (0.74, 0.99); glVertex3f (0, 0, 0);
    glTexCoord2f (0.74, 0.755); glVertex3f (0, 0, lado);
    glTexCoord2f (0.5, 0.755); glVertex3f (0, lado, lado);
    glTexCoord2f (0.5, 0.99); glVertex3f (0, lado, 0);
  glEnd ();

  glDisable(GL_TEXTURE_2D);
}


Lata::Lata() {}

Lata::Lata(const char * perfil, int instancias)
{
  if (instancias <= 3)
    return;

  ply::read_vertices(perfil, verticesPerfil);

  int m = verticesPerfil.size()/3;

  for (int i = 0; i < instancias; i++) {
    double angulo = (2 * i * M_PI) / (instancias - 1);
    for (int j = 0; j < m; j++) {
      vertices.push_back(verticesPerfil[j * 3 + 2] * cos(angulo) + verticesPerfil[j * 3 + 0] * sin(angulo));
      vertices.push_back(verticesPerfil[j * 3 + 1]);
      vertices.push_back(verticesPerfil[j * 3 + 0] * cos(angulo) - verticesPerfil[j * 3 + 2] * sin(angulo));
    }
  }

  int mod = (instancias - 1) * verticesPerfil.size()/3;
  for (int i = 0; i < instancias - 1; i++)
    for (int j = 0; j < m - 1; j++)
    {
      int k = i * m + j;

      // Triángulo formado por k, k+m, k+m+1
      caras.push_back((k) % mod);
      caras.push_back((k + m) % mod);
      caras.push_back((k + m + 1) % mod);
      
      // Triángulo formado por k, k+m+1, k+1
      caras.push_back((k) % mod);
      caras.push_back((k + m + 1) % mod);
      caras.push_back((k + 1) % mod);
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

void Lata::drawFlat()
{
  if (texId != 0) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
  }


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
      if (texId != 0)
        glTexCoord2f(coordTextura[caras[i * 3 + 0]].first, coordTextura[caras[i * 3 + 0]].second);
      glVertex3f(vertices[caras[i * 3 + 0] * 3 + 0],
                 vertices[caras[i * 3 + 0] * 3 + 1],
                 vertices[caras[i * 3 + 0] * 3 + 2]);
      if (texId != 0)
        glTexCoord2f(coordTextura[caras[i * 3 + 1]].first, coordTextura[caras[i * 3 + 1]].second);
      glVertex3f(vertices[caras[i * 3 + 1] * 3 + 0],
                 vertices[caras[i * 3 + 1] * 3 + 1],
                 vertices[caras[i * 3 + 1] * 3 + 2]);
      if (texId != 0)
        glTexCoord2f(coordTextura[caras[i * 3 + 2]].first, coordTextura[caras[i * 3 + 2]].second);
      glVertex3f(vertices[caras[i * 3 + 2] * 3 + 0],
                 vertices[caras[i * 3 + 2] * 3 + 1],
                 vertices[caras[i * 3 + 2] * 3 + 2]);
    }
  }
  glEnd();

  if (texId != 0)
    glDisable(GL_TEXTURE_2D);
}

void Lata::drawSmooth()
{
  if (texId != 0) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texId);
  }

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
      if (texId != 0)
        glTexCoord2f(coordTextura[caras[i]].first, coordTextura[caras[i]].second);
      glVertex3f(vertices[caras[i] * 3 + 0],
                 vertices[caras[i] * 3 + 1],
                 vertices[caras[i] * 3 + 2]);
    }
  }
  glEnd();

  if (texId != 0)
    glDisable(GL_TEXTURE_2D);
}

void Lata::aplicarTextura(const char * nombreTextura)
{
  Objeto3D::aplicarTextura(nombreTextura);

  calcCoordTextura();
}

void Lata::calcCoordTextura()
{
  float minAltura = verticesPerfil[1],
        maxAltura = verticesPerfil[1],
        maxDistancia = 0;

  // Calcular altura 
  for (int i = 0; i < verticesPerfil.size()/3; i++) {
    if (verticesPerfil[i * 3 + 1] < minAltura)
      minAltura = verticesPerfil[i * 3 + 1];
    else if (verticesPerfil[i * 3 + 1] > maxAltura)
      maxAltura = verticesPerfil[i * 3 + 1];
  }

  // Calcular distancia entre puntos
  for (int i = 1; i < verticesPerfil.size()/3; i++) {
    maxDistancia += calcularDistanciaPuntos(i, i-1);
  }

  coordTextura.resize(vertices.size()/3);
  std::vector<float> alturas(verticesPerfil.size()/3);

  alturas[0] = 1;
  alturas[1] = 0;
  for (int i = 1; i < verticesPerfil.size()/3 - 1; i++) {
    alturas[i] = 1 - (calcularDistanciaPuntos(0, i) / maxDistancia);
  }

  for (int i = 0; i < instancias; i++) {
    for (int j = 0; j < verticesPerfil.size()/3; j++) {
        int indice = i * verticesPerfil.size()/3 + j;
        coordTextura[indice].first = (float)i / (instancias - 1);
        coordTextura[indice].second = alturas[j];
    }
  }
}


Tapa::Tapa() {}

Tapa::Tapa(const char * perfil, int instancias)
{
  if (instancias <= 3)
    return;

  ply::read_vertices(perfil, verticesPerfil);

  int m = verticesPerfil.size()/3;

  for (int i = 0; i < instancias; i++) {
    double angulo = (2 * i * M_PI) / (instancias - 1);
    for (int j = 0; j < m; j++) {
      vertices.push_back(verticesPerfil[j * 3 + 0] * cos(angulo) - verticesPerfil[j * 3 + 2] * sin(angulo));
      vertices.push_back(verticesPerfil[j * 3 + 1]);
      vertices.push_back(verticesPerfil[j * 3 + 2] * cos(angulo) + verticesPerfil[j * 3 + 0] * sin(angulo));
    }
  }

  int mod = (instancias - 1) * verticesPerfil.size()/3;
  for (int i = 0; i < instancias - 1; i++)
    for (int j = 0; j < m - 1; j++)
    {
      int k = i * m + j;

      // Triángulo formado por k, k+m, k+m+1
      caras.push_back((k + m) % mod);
      caras.push_back((k) % mod);
      caras.push_back((k + m + 1) % mod);
      
      // Triángulo formado por k, k+m+1, k+1
      caras.push_back((k + m + 1) % mod);
      caras.push_back((k) % mod);
      caras.push_back((k + 1) % mod);
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





void dibujaLinea(float x, float y, float z, char dir, float l)
{
  GLfloat *colorOriginal = new GLfloat[4],
          pointOriginal;
  glGetFloatv(GL_CURRENT_COLOR, colorOriginal);
  glGetFloatv(GL_POINT_SIZE, &pointOriginal);

  glColor3f(0, 0, 1);
  
  glBegin(GL_LINES);
    glVertex3f(x, y, z);
    if (dir == 'x')
      glVertex3f(x + l, y, z);
    else if (dir == 'y')
      glVertex3f(x, y + l, z);
    else if (dir == 'z')
      glVertex3f(x, y, z + l);
  glEnd();

  glPointSize(4);
  glColor3f(1, 0, 0);

  glBegin(GL_POINTS);
    glVertex3f(x, y, z);
  glEnd();

  glColor4fv(colorOriginal);
  glPointSize(pointOriginal);
}
