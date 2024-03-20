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

=======================================================

	 modelo.h
*/

#include <vector>


/**
	Funcion de redibujado. Se ejecuta con los eventos postRedisplay
**/
void Dibuja (void);

/**
	Funcion de fondo
**/
void idle (int v);

/**
	Funcion de inicializacion del modelo y de las variables globales
**/
void initModel (int m, const char * archivo);

/**
	Funcion de selección de modo
**/
void setModo(int M);

/**
	Funcion de selección de iluminación
**/
void alternaIluminacion();

/**
  Función de alternación de sombreado
**/
void alternaSombreado();

/**
  Función para resetear los valores de las transformaciones
**/
void reseteaTransformaciones();

/**
  Función para modificar el ángulo del mástil
**/
bool cambiaAnguloMastil(float cambio);

/**
  Función para modificar la translación de las horquillas
**/
bool cambiaDesplazamientoHorquillas(float cambio);

/**
  Función para modificar el ángulo de las horquillas
**/
bool cambiaAnguloHorquillas(float cambio);

/**
  Función de alternación de animación
**/
void alternaAnimacion();

/**
  Función para modificar un valor de transformacion
**/
void modificaValorTransformacion(float & var, float nuevoValor);



class Objeto3D 
{ 
protected:
  std::vector<Objeto3D *> hijos;

public:
  Objeto3D();

  virtual void draw();
  
  virtual void draw(bool sombreadoSmooth);

  void aniadeHijo(Objeto3D * nuevoHijo);
}; 

typedef Objeto3D Nodo;



/*****************************************************************************/
// Práctica 1

class Cubo : public Objeto3D {
protected:
  float lado;

public:
  Cubo();

  Cubo(float lado);

  void draw() override;

  void draw(bool sombreadoSmooth) override;
};


class Piramide : public Objeto3D {
protected:
  float lado;
  float altura;

public:
  Piramide();

  Piramide(float lado, float altura);

  void draw() override;

  void draw(bool sombreadoSmooth) override;
};


class Prisma : public Objeto3D {
protected:
  float lado;
  float altura;

public:
  Prisma();
  
  Prisma(float lado, float altura);

  void draw() override;

  void draw(bool sombreadoSmooth) override;
};



/*****************************************************************************/
// Práctica 2

class Malla : public Objeto3D {
protected:
  std::vector<float> vertices;
  std::vector<int> caras;
  std::vector<float> normalesVertices;

  void dibujaNormales(bool sombreadoSmooth);

public:
  Malla();

  void drawFlat();

  void drawSmooth();

  void draw() override;

  void draw(bool sombreadoSmooth) override;
};

class MallaPly : public Malla {
public:
  MallaPly();

  MallaPly(const char *nombre_archivo_pse);
};

class MallaRevolucion : public Malla {
protected:
  std::vector<float> verticesPerfil;

public:
  MallaRevolucion();

  MallaRevolucion(const char *perfil, int instancias);
};



/*****************************************************************************/
// Práctica 3

class Transformacion : public Nodo {
public:
  void draw(bool sombreadoSmooth) override;

  virtual void transform() = 0;
};

class Translacion : public Transformacion {
protected:
  float x, y, z;

public:
  Translacion(float x, float y, float z);

  void transform() override;
};

class Rotacion : public Transformacion {
protected:
  float angulo, x, y, z;

public:
  Rotacion(float angulo, float x, float y, float z);

  void transform() override;
};



/*****************************************************************************/
// Variables

// Functions
void dibujaLinea(float x, float y, float z, char dir, float lenght);


static int practica, 
           modo, 
           instancias, 
           modoCarga;
static float raValor,
             rbValor,
             taValor,
             DEFAULT_ROTATION_A = 0.2,
             DEFAULT_ROTATION_B = 0.3,
             DEFAULT_TRANSLATION_A = 0.05;
static bool iluminacion,
            sombreadoSmooth,
            animacion,
            estadoAnimacion[3];

static Cubo c;
static Piramide p;
static Prisma pr;
static Malla busto,
             coche,
             mallaLoad,
             forkliftBody,
             forkliftMast,
             forkliftFork;
static MallaRevolucion peon,
                       mallaSpin;
