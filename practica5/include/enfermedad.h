/* 
 * enfermedad.h
 * 
 * Copyright  (C) Juan F. Huete y Carlos Cano 
*/
#ifndef __ENFERMEDAD_H
#define __ENFERMEDAD_H

#include <string>
#include <iostream> 


//! Clase enfermedad, asociada al TDA enfermedad
/*! enfermedad::enfermedad,  .....
 * Descripción contiene toda la información asociada a una enfermedad almacenada en la BD ClinVar-dbSNP (nombre de la enfermedad, id, BD que provee el id)
 
 @todo Implementa esta clase, junto con su documentación asociada

*/

class enfermedad {
private:
  std::string  name;       // nombre de la enfermedad. Almacenar completo en minúscula.
  std::string  ID;         // ID único para la enfermedad
  std::string  database;   // Base de datos que provee el ID

public:
 enfermedad (); //Constructor de enfermedad por defecto
 enfermedad (const std::string & name, const std::string & ID, const std::string & database); 

 void setName(const std::string & name);
 void setID(const std::string & ID);
 void setDatabase(const std::string & database);

 std::string getName( ) const;
 std::string getID( ) const;
 std::string getDatabase( ) const;

 enfermedad & operator=(const enfermedad & e);
 std::string toString() const;

// Operadores relacionales
 bool operator==(const enfermedad & e) const; 
 bool operator!=(const enfermedad & e) const;
 bool operator<(const enfermedad & e) const;	//Orden alfabético por campo name. 

 bool nameContains(const std::string & str) const;   //Devuelve True si str está incluido en el nombre de la enfermedad, aunque no se trate del nombre completo. No debe ser sensible a mayúsculas/minúsculas. 

};

 std::ostream& operator<< ( std::ostream& os, const enfermedad & e); //imprime enfermedad (con TODOS sus campos)

// Vamos a meter un método para transformar un string a minúscula ya que lo usamos en 3 métodos distintos
 std::string aMinuscula(std::string str);



#endif
