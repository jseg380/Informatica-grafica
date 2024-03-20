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


class Objeto3D 
{ 
public: 

virtual void draw( ) = 0; // Dibuja el objeto
} ; 


class Cubo : public Objeto3D {
protected:
  float lado;

public:
  Cubo (float lado);

  void draw();
};


class Piramide : public Objeto3D {
protected:
  float lado;
  float altura;

public:
  Piramide (float lado, float altura);

  void draw();
};


class Prisma : public Objeto3D {
protected:
  float lado;
  float altura;

public:
  Prisma (float lado, float altura);

  void draw();
};


class Malla : public Objeto3D {
protected:
  std::vector<float> vertices;
  std::vector<int> caras;
  std::vector<float> normalesVertices;

  void dibujaNormales();

public:
  Malla();

  Malla(const char *nombre_archivo_pse);

  void drawFlat();

  void drawSmooth();

  void draw();

  void draw(bool sombreadoSmooth);
};

class MallaRevolucion : public Malla {
protected:
  std::vector<float> verticesPerfil;

public:
  MallaRevolucion();

  MallaRevolucion(const char *perfil, int instancias);

  void drawFlat();

  void drawSmooth();

  void draw();

  void draw(bool sombreadoSmooth);
};




/**
  Variables globales
**/
static int modo, instancias, modoCarga;
static bool iluminacion,
            sombreadoSmooth;
static Malla busto,
             coche,
             mallaLoad;
static MallaRevolucion peon,
                       mallaSpin;
