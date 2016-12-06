/**
	@brief Copia características de m en el objeto que invoca el método
	@param m: Referencia constante de un objeto mutación. 
*/

#include <mutacion.h>


void mutacion::copiar( const mutacion &m ){
	setID(m.getID());
	setChr(m.getChr());
	setPos(m.getPos());
	setRef_alt(m.getRef_alt());
	setGenes(m.getGenes());
	setCommon(m.getCommon());
	setCaf(m.getCaf());
	setEnfermedades(m.getEnfermedades());
	setClnsig(m.getClnsig());
}

/**
	@brief Constructor sin prámetros de la clase 'mutacion'.
*/
mutacion::mutacion(){
	ID = "";
	chr = "1";
	pos = 0;
	common = false;	
}

/**
	@brief Constructor de copia de la clase 'mutacion'
	@param m: Objeto de tipo mutacion que se pasa como referencia constante
*/
mutacion::mutacion(const mutacion& m){
	copiar(m);
}

/**
	@brief Constructor a partir de la cadena representativa de mutación
	@param str: Cadena de caracteres que contiene una línea completa del fichero de entrada
*/
mutacion::mutacion(const std::string & str){
	// Nos dan un string de donde tenemos que sacar la información
	// Lo primero que nos encontramos es el número de cromosoma
	std::size_t inicio=0, delimitador = str.find("\t");
	// Desde inicio(0) a delimitador-1 tenemos chr
	setChr(str.substr(inicio, delimitador-inicio));
	
	// Lo siguiente que encontramos es pos
	inicio=delimitador+1;
	// Buscamos a partir del último que encontramos anteriormente (sin incluirlo)
	delimitador=str.find("\t", inicio);
	setPos(std::stoi(str.substr(inicio,delimitador)));
	
	// Ahora encontramos ID
	inicio=delimitador+1;
	delimitador=str.find("\t", inicio);
	setID(str.substr(inicio,delimitador-inicio));
	
	// Ahora tenemos ref_alt
	// En la primera posición guardamos el de referencia
	inicio=delimitador+1;
	delimitador=str.find("\t", inicio);
	ref_alt.push_back(str.substr(inicio,delimitador-inicio));
	// Las alternativas están separadas por comas
	// Nunca puede pasar del siguiente \t
	inicio=delimitador+1;
	std::size_t limite = str.find("\t", inicio);
	while(delimitador<limite){ // Al menos hay una alternativa
		delimitador=str.find(",", inicio);
		// Hay que tener cuidado de no pasarnos del límite
		if(delimitador<limite){
			ref_alt.push_back(str.substr(inicio, delimitador-inicio));
			inicio=delimitador+1;
		}else
			ref_alt.push_back(str.substr(inicio, limite-inicio));
	}
	
	// Lo próximo que miramos es genes
	// Buscamos "GENEINFO=" para saber donde empiezan
	// Pero nos interesa lo que viene despues de la cadena
	// Busco desde límite para que no mire desde el principio
	inicio=str.find("GENEINFO=", limite)+9; 
	// No podemos pasar del ";" esta vez
	limite=str.find(";", inicio); 
	delimitador = inicio;
	while(delimitador<limite){ 
		delimitador=str.find("|", inicio);
		// Hay que tener cuidado de no pasarnos del límite
		if(delimitador<limite){
			genes.push_back(str.substr(inicio, delimitador-inicio));
			inicio=delimitador+1;
		}else
			genes.push_back(str.substr(inicio, limite-inicio));
	}
	
	// caf
	// caf puede estar o no estar
	if(str.find("CAF=", limite)!=std::string::npos){
		inicio=str.find("CAF=", limite)+4;
		delimitador=inicio;
		limite=str.find(";", inicio);
		while(delimitador<limite){ 
			delimitador=str.find(",", inicio);
			// Hay que tener cuidado de no pasarnos del límite
			if(delimitador<limite){
				// Si encontramos un ".", ponemos un 0
				if(str.substr(inicio, delimitador-inicio)==".")
					caf.push_back(0);
				else
					caf.push_back(std::stof(str.substr(inicio, delimitador-inicio)));
				inicio=delimitador+1;
			}else{
				// Si encontramos un ".", ponemos un 0
				if(str.substr(inicio, limite-inicio)==".")
					caf.push_back(0);
				else 
					caf.push_back(std::stof(str.substr(inicio, limite-inicio)));
			}
		}
	} // Si no está lo dejamos vacío
	
	// common
	// También puede no estar
	if(str.find("COMMON=")!=std::string::npos){
		inicio=str.find("COMMON=", limite)+7;
		// Como es un booleano se que solo estará en la posición inicio
		common = (str[inicio]=='1');
	}else{ // Si no está lo pongo a false
		common=false;
	}
	
	// clnsig
	// este si está siempre
	inicio=str.find("CLNSIG=", limite)+7;
	delimitador=inicio;
	limite=str.find(";", inicio);

	while(delimitador<limite){ 
		delimitador=str.find("|", inicio);
		// Hay que tener cuidado de no pasarnos del límite
		if(delimitador<limite){
			clnsig.push_back(std::stoi(str.substr(inicio, delimitador-inicio)));
			inicio=delimitador+1;		
		}else
			clnsig.push_back(std::stoi(str.substr(inicio, limite-inicio)));
	}		
	
	// enfermedades 
	// Las enfermedades tienen varios campos diferentes, en cada uno de ellos encontraré
	// información sobre la enfermedad
	size_t sdb=str.find("CLNDSDB=", inicio)+8, sdbid=str.find("CLNDSDBID=", inicio)+10, bn=str.find("CLNDBN=", inicio)+7;
	size_t del2=0, del3=0, lim2=str.find(";", sdbid), lim3=str.find(";", bn);
	// Lo que encontraré en cada lugar será bn:nombre, sdbid:ID, sdb:database
	// Los delimitadores vuelven a ser "|"
	// Debe haber el mismo número de campos para cada uno
	std::string name, ID, database;
	delimitador=sdb;
	// Solo necesito comprobar un limite, pues tienen el mismo número de variables cada campo
	limite=str.find(";", sdb);
	while(delimitador<limite){
		delimitador=str.find("|", sdb);
		
		// Primero miro si hay más enfermedades
		if(delimitador<limite){
			del2=str.find("|", sdbid);
			del3=str.find("|", bn);
			name=str.substr(bn, del3-bn);
			ID=str.substr(sdbid, del2-sdbid);
			database=str.substr(sdb, delimitador-sdb);
		}else{ // Sino hay hemos acabado
			name=str.substr(bn, lim3-bn);
			ID=str.substr(sdbid, lim2-sdbid);
			database=str.substr(sdb, limite-sdb);
		}
		
		sdb=delimitador+1;
		sdbid=del2+1;
		bn=del3+1;
		enfermedades.push_back(enfermedad(name,ID,database));
	}
}




/**
	@brief Cambia el Identificador (ID) de la mutación.
	@param id: Identificador del SNP/mutación (string).
*/
void mutacion::setID( const std::string &id ){
	if( id[0] == 'r' && id[1] == 's' ){	
		ID = id;
	}
}

/**
	@brief Cambia el valor de chr
	@param chr: Identificador del cromosoma
*/
void mutacion::setChr( const std::string &chr ){
	this->chr = chr;
}

/**
	@brief Cambio el valor de la posición.
	@param pos: Identificador de la posición dentro del cromosoma.
*/
void mutacion::setPos(const unsigned int & pos){
	this->pos = pos;
}

/**
	@brief Cambia el vector de string de la base en el genoma
	@param ref_alt: Base(s) en el genoma de referencia y alternativa(s) posible(s).
*/
void mutacion::setRef_alt(const std::vector<std::string> & ref_alt){
	this->ref_alt = ref_alt;
}

/**
	@brief Cambia la secuencia de genes.
	@param genes: Genes asociados al SNP.
*/
void mutacion::setGenes (const std::vector<std::string> & genes){
	this->genes = genes;
}

/**
	@brief Cambia entre común y no común.
	@param common: Indica si el SNP es común en la población. 
*/
void mutacion::setCommon (const bool & common){
	this->common = common;
}

/**
	@brief Cambia la frecuencia
	@param caf: Frecuencia de cada base del SNP en la población.
*/
void mutacion::setCaf (const std::vector<float> & caf){
	this->caf = caf;
}

/**
	@brief Cambia las enfermedades
	@param enfermedades: Enfermedades asociadas al SNP.
*/
void mutacion::setEnfermedades (const std::vector<enfermedad> & enfermedades){
	this->enfermedades = enfermedades;
}

/**
	@brief Cambia la relevancia clínica.
	@param clnsig: Relevancia clínica del SNP para cada enfermedad utilizando el código numérico del campo CLNSIG.
*/
void mutacion::setClnsig (const std::vector<int> & clnsig){
	this->clnsig = clnsig;
}

/**
	@brief Consultor ID
	@return ID de la mutación
*/
std::string mutacion::getID( ) const{
	return ID;
}

/** 
	@brief Consultor chr
	@return Identificador del cromosoma
*/
std::string mutacion::getChr( ) const{
	return chr;
}  

/** 
	@brief Consultor pos
	@return Posicion dentro del cromosoma
*/  
unsigned int mutacion::getPos( ) const{
	return pos;
}

/** 
	@brief Consultor ref_alt
	@return Vector con base en genoma de referencia, seguido de las distintas alternativas que tiene
*/ 
const std::vector<std::string> & mutacion::getRef_alt () const{
	return ref_alt;
}

/** 
	@brief Consultor genes
	@return Genes asociados al SNP
*/ 
const std::vector<std::string> & mutacion::getGenes () const{
	return genes;
}

/** 
	@brief Consultor common
	@return Booleano indicando si SNP es común
*/ 
bool mutacion::getCommon () const{
	return common;
}

/** 
	@brief Consultor caf 
	@return Vector con las frecuencias de cada base
*/ 
const std::vector<float> & mutacion::getCaf () const{
	return caf;
}

/** 
	@brief Consultor enfermedades
	@return Vector con enfermedades asociadas a cada base
*/ 
const std::vector<enfermedad> & mutacion::getEnfermedades () const{
	return enfermedades;
}

/** @brief Consultor clnsig
	@return Vector con la relevancia clínica de cada base
*/ 
const std::vector<int> & mutacion::getClnsig () const{
	return clnsig;
}

/**
	@brief Operador de asignación.
	@param m: Objeto mutación
	@return Referencia
*/
mutacion & mutacion::operator=(const mutacion & m){
	if( this != &m ){
		copiar(m);
	}

	return *this;
}

/**
	@brief Operador de comparación de igualdad
	@param m: Objeto mutación referencia constante
	@return Booleano indicando resultado
*/
bool mutacion::operator==(const mutacion & m) const{
	return getID()==m.getID() && getChr()==m.getChr() && getPos()==m.getPos() && getRef_alt()==m.getRef_alt() && 
  	   	   getGenes()==m.getGenes() && getCommon()==m.getCommon() && getCaf()==m.getCaf() &&		   
           getEnfermedades()==m.getEnfermedades() && getClnsig()==m.getClnsig();
}

/**
	@brief Devuelve un entero que representa al número de cromosoma de un objeto mutación como parametro.
	@return Entero representativo orden cromosoma
*/

int mutacion::numCromosoma() const{
	int num;

	if( this->getChr()=="X" )
		num = 23;
	else if( this->getChr()=="Y" )
		num = 24;
	else if( this->getChr()=="MT" )
		num = 25;
	else
		num = std::stoi(this->getChr());
	
	return num;
}

/**
	@brief Operador de orden
	@param m: Objeto mutación referencia constante
	@return Booleano indicando cual es mayor
*/

bool mutacion::operator<(const mutacion & m) const{
	bool resultado;

	if( this->numCromosoma() < m.numCromosoma() )
	{
		resultado = true;
	}
	else if( this->numCromosoma() == m.numCromosoma() )
	{
		if( this->getPos() < m.getPos() )
			resultado = true;
		else
			resultado = false;
	}	
	else
		resultado = false;

	return resultado;
}

/**
	@brief Manda los datos de la mutacion m por os
	@param os: flujo de salida utilizado
	@param m: mutacion
	@return flujo de salida os por referencia
*/
std::ostream& operator<< ( std::ostream& os, const mutacion& m){
	os << "-ID: " << m.getID() << "\n-Cromosoma: " << m.getChr() << "\tPosicion: " << m.getPos();
	
	os << "\n-Referencia Alternativa: [ ";
	for(unsigned i=0; i<m.getRef_alt().size(); i++)
		os << m.getRef_alt()[i] << " ";
	os << "]";
	
	os << "\n-Genes: [ ";
	for(unsigned i=0; i<m.getGenes().size(); i++)
		os << m.getGenes().at(i) << " ";
	os << "]";
	
	os << "\n-Comun: " << m.getCommon();
	
	os << "\n-Caf: [ ";
	for(unsigned i=0; i<m.getCaf().size(); i++)
		os << m.getCaf()[i] << " ";
	os << "]";
	
	os << "\n-Enfermedades: [\n";
	for(unsigned i=0; i<m.getEnfermedades().size(); i++)
		os << m.getEnfermedades()[i];
	os << "]";
	
	os << "\n-Relevancia Clínica: [ ";
	for(unsigned i=0; i<m.getClnsig().size(); i++)
		os << m.getClnsig()[i] << " ";
	os << "]";
	os << std::endl;
	
	
	return os;
}




















