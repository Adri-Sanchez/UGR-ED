/** @brief Fichero de implementacion de la clase enfermedad

*/

/** 
	@brief Constructor por defecto, crea una enfermedad vacía
*/
enfermedad::enfermedad(){
  name="";
  ID="";
  database="";
}
/** 
	@brief Constructor dados los parámetros
	@param name: Nombre enfermedad
	@param ID: Identificador enfermedad
	@param database: Base de datos que provee el ID
*/
enfermedad::enfermedad(const std::string & name, const std::string & ID, const std::string & database){
	this->name=aMinuscula(name);
	this->ID=ID ;
	this->database=database;
}


/** 
	@brief Cambia el nombre de la enfermedad
	@param name: Nuevo nombre
*/
void enfermedad::setName(const std::string & name){
	this->name=aMinuscula(name);
}
/** 
	@brief Cambia el ID de la enfermedad
	@param ID: Nuevo ID
*/
void enfermedad::setID(const std::string & ID){
	this->ID=ID;
}
/** 
	@brief Cambia el database de la enfermedad
	@param database: Nuevo database
*/
void enfermedad::setDatabase(const std::string & database){
	this->database=database;
}
  
/** 
	@brief Consultor name
	@return Nombre de la enfermedad
*/
std::string enfermedad::getName() const{
	return name;
}
/** 
	@brief Consultor ID
	@return ID de la enfermedad
*/
std::string enfermedad::getID() const{
	return ID;
}
/** 
	@brief Consultor database
	@return Database de la enfermedad
*/
std::string enfermedad::getDatabase() const{
	return database;
}

/** 
	@brief Operador de asignación
	@param e: Enfermedad que se asigna
	@return Referencia a enfermedad que llama al método
*/
enfermedad & enfermedad::operator=(const enfermedad & e){
	if(this!=&e){
		setName(e.getName());
		setID(e.getID());
		setDatabase(e.getDatabase());
	}
	
	return *this;
}

/** 
	@brief Genera un string con los atributos de la enfermedad
	@return String con los atributos
*/
std::string enfermedad::toString() const{
	return ("Name: "+getName()+"\tID: "+getID()+"\tDatabase: "+getDatabase()+"\n");
}

/** 
	@brief Compara los atributos de 'e' y la enfermedad que llama al método
	@param e: Enfermedad con la que comparar
	@return Booleano indicando si son iguales
*/
bool enfermedad::operator==(const enfermedad & e) const{
	return getName()==e.getName() && getID()==e.getID() && getDatabase()==e.getDatabase();
}
/** 
	@brief Compara los atributos de 'e' y la enfermedad que llama al método
	@param e: Enfermedad con la que comparar
	@return Booleano indicando si son distintos
*/
bool enfermedad::operator!=(const enfermedad & e) const{
	return getName()!=e.getName() || getID()!=e.getID() || getDatabase()!=e.getDatabase();
}
/** 
	@brief Compara el nombre de 'e' y la enfermedad que llama al método
	@param e: Enfermedad con la que comparar
	@return Booleano indicando orden lexicográfico de los name
*/
bool enfermedad::operator<(const enfermedad & e) const{
	return getName()<e.getName();
}

/** 
	@brief Indica si str está contenido en name
	@param str: String que buscamos
	@return Booleano indicando si son iguales
*/
bool enfermedad::nameContains(const std::string & str) const{
	// Como name está en minúscula, paso str a minúscula primero
	// Como str es const, hago una copia (equivalente a no pasarlo por referencia y sin const)
	std::string copia = aMinuscula(str);
	
			
	// Ahora busco la segunda cadena en la que llama al metodo
	// find busca la cadena pasada como argumento en la que invoca el método, si no la encuentra devuelve npos
	std::size_t found = name.find(str);
	return found != std::string::npos;
}

/** 
	@brief Manda los datos de la enfermedad 'e' por os
	@param os: Flujo de salida que utilizamos
	@param e: Enfermedad de la que se envian los datos
	@return Flujo de salida os por referencia
*/
std::ostream& operator<< (std::ostream& os, const enfermedad & e){
	os << e.toString();
   
	return os;
}
    
/** 
	@brief Transforma un string a minúscula
	@param str: String que cambiamos
	@return El string con las letras en minúscula
*/     
std::string aMinuscula(std::string str){
	for(unsigned i=0; i<str.size(); i++)
		if(str[i]>'A' && str[i]<'Z')
			str[i]=str[i]-('A'-'a');
			
	return str;
} 
