#ifndef __CONJUNTOIT_H
#define __CONJUNTOIT_H
#include <string>
#include <vector>
#include <iostream> 

#include <assert.h>

using namespace std;


//! Clase conjunto
 /*! conjunto::conjunto, find, size,  
 * Tipos conjunto::value_type, conjunto::size_type 
 * Iteradores:iterator, impar_iterator, secure_iterator;
 * Descripción

* Un conjunto es un contenedor que permite almacenar en orden creciente un conjunto de elementos no repetidos.  

* Asociado al conjunto, tendremos el tipo  \code conjunto::value_type \endcode que permite hacer referencia al elemento  almacenados en cada una de las posiciones del conjunto. Es requisito que el tipo conjunto::value_type tenga definidos los operadores operator< y operator= .

* El número de elementos en el conjunto puede variar dinámicamente; la gestión de la memoria es automática. 
 
 @todo Implementa esta clase siguiendo la especificación asociada
 */




template <typename T, class CMP>
class conjunto
{
public:
	typedef T value_type;
	typedef unsigned int size_type;

	//Clases de iteradores. Atributos y métodos definidos abajo.
	//@todo Implementa las clases de iteradores.  
	class iterator;
	class impar_iterator;
	class secure_iterator;
	//Clases de iteradores constantes. 
	//@todo Implementa las clases de iteradores constantes. 
	class const_iterator;
	class const_impar_iterator;
	class const_secure_iterator;

	
	/** @brief constructor primitivo. 
	*/
	conjunto( );
	

	/** @brief constructor de copia
	@param[in] d conjunto a copiar
	*/
	conjunto (const conjunto<T,CMP> & d);
		

	/** @brief busca una entrada en el conjunto
	@param[in] s: entrada  a buscar. 
	@return Si existe una entrada en el conjunto con ese valor devuelve el iterador a su posicion, en caso contrario devuelve iterador al final de conjunto
	@post no modifica el conjunto.
	*/
	iterator  find (const value_type & s) ;
	const_iterator  find (const value_type & s) const;



	/** @brief cuenta cuantas entradas coinciden con los parámetros dados. 
	@param[in] e entrada. 
	@return Como el conjunto de mutaciones no puede tener entradas repetidas, devuelve 1 (si se encuentra la entrada) o 0 (si no se encuentra).
	@post no modifica el conjunto.
	*/
	
	size_type count (const value_type & e) const; 



	/** @brief Inserta una entrada en el conjunto
	@param val entrada a insertar
	@return un par donde el segundo campo vale true si la entrada se ha podido insertar con éxito, esto es, no existe una mutación con igual valor en el conjunto. False en caso contrario. 
    El primer campo del par devuelve un iterador al elemento insertado, o end() si no fue posible la insercion
   	@post Si e no esta en el conjunto, el size() sera incrementado en 1.
	*/
	pair<iterator,bool> insert (const value_type& val);
	
	
	/** @brief Borra una entrada en el conjunto .
	Busca la entrada y si la encuentra la borra.
	
	@param[in] val entrada a borrar.
	@param[in] position itarador que apunta a la  entrada que geremos borrar
	@return devuelve la posicion siguiente al elemento borrado (para la version con iterador) o el numero de elementos borrados
	@post Si esta en el conjunto su tamaño se decrementa en 1.
	*/
	iterator  erase (const iterator position);
	size_type erase (const value_type& val);


	/** @brief Borra todas las entradas del conjunto, dejandolo vacio.
	@post El conjunto se modifica, quedando vacio. 
	*/
	void clear();

	/** @brief numero de entradas en el conjunto
	@post  No se modifica el conjunto.
	@return numero de entradas en el conjunto
	*/
	size_type size() const ;


	/** @brief Chequea si el conjunto esta vacio (size()==0)
	@post  No se modifica el conjunto.
	*/
	bool empty() const;


	/** @brief operador de asignación
	@param[in] org conjunto a copiar.
	@return Crea y devuelve un conjunto duplicado exacto de org.
	*/
	conjunto & operator=( const conjunto & org);

	/** @brief begin del conjunto
	@return Devuelve un iterador (o iterador constante, respectivamente) al primer elemento del conjunto. Si no existe devuelve end
	*/
	iterator begin ();
	const_iterator cbegin () const;

	/** @brief end del conjunto
	@return Devuelve un iterador (o iterador constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
	@post no modifica el conjunto.
	*/
	iterator end ();
	const_iterator cend () const;


	/** @brief begin del conjunto
	@return Devuelve un iterador seguro (o iterador seguro constante, respectivamente) al primer elemento del conjunto. Si no existe devuelve end
	*/
	secure_iterator sbegin ();
	const_secure_iterator csbegin( ) const;

	/** @brief end del conjunto
	@return Devuelve un iterador seguro (o iterador seguro constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
	@post no modifica el conjunto.
	*/
	secure_iterator send ();
	const_secure_iterator csend( ) const;

	/** @brief begin del conjunto
	@return Devuelve un iterador impar (o iterador impar constante, respectivamente) al primer elemento (de posición impar) del conjunto. Si no existe devuelve end
	*/
	impar_iterator ibegin();
	const_impar_iterator cibegin( ) const;

	/** @brief end del conjunto
	@return Devuelve un iterador impar (o iterador impar constante, respectivamente) al final del conjunto (posicion siguiente al ultimo.
	*/
	impar_iterator iend();
	const_impar_iterator ciend( ) const;


	/** @brief busca primer elemento por debajo ('antes', '<') de los parámetros dados. 
	@param[in] val entrada.  
	@return Devuelve un iterador al primer elemento que cumple que "elemento<e" es falso, esto es, el primer elemento que  es mayor o igual que val
	Si no existe devuelve end
	@post no modifica el conjunto.
	*/
	iterator lower_bound (const value_type& val);
	const_iterator lower_bound (const value_type& val) const;


	/** @brief busca primer elemento por encima ('después', '>') de los parámetros dados. 
	@param[in] val entrada. Devuelve un iterador al primer elemento que cumple que "elemento>e", esto es, el primer elemento ESTRICTAMENTE mayor que val
	Si no existe devuelve end
	@post no modifica el conjunto.
	*/
	iterator upper_bound (const value_type& val);
	const_iterator upper_bound (const value_type& val) const;



	// Implementamos en .h para ahorrarnos las cabeceras

	class iterator{
	public:
		iterator(){	
			elvector=NULL;
		}
		iterator(const iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		// Transforma secure_iterator en iterator;
		iterator(const secure_iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		
		const T & operator*(){
			return *it;
		}
		iterator & operator++(){
			it++;
			return *this;
		}
		iterator operator++(int i){
			while(i-- > 0)
				it++;

			return *this;			
		}
		iterator & operator--(){
			it--;
			return *this;			
		}
		iterator operator--(int i){
			while(i-- > 0)
				it--;
		
			return *this;			
		}
		bool operator==(const iterator & x) const{
			// Diremos que dos iterator son iguales si apuntan al mismo elemento,
			// y son del mismo vector
			return it==x.it && elvector==x.elvector;
		}
		bool operator!=(const iterator & x) const{
			return !(*this==x);
		}
		iterator & operator=(const iterator & x){
			if(this!=&x){
				elvector=x.elvector;
				it=x.it;
			}
			return *this;
		}

	public:
		friend class conjunto<T,CMP>;
		typename vector<T>::iterator it;
		vector<T> *elvector;
	};

	class secure_iterator{
	public:
		secure_iterator(){	
			elvector=NULL;
		}
		secure_iterator(const secure_iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		
		const T & operator*(){
			assert(it<elvector->end() && it>=elvector->begin());
			return *it;
		}
		secure_iterator & operator++(){
			it++;
			assert(it<elvector->end() && it>=elvector->begin());
			return *this;
		}
		secure_iterator operator++(int i){
			while(i-- > 0)
				it++;

			assert(it<elvector->end() && it>=elvector->begin());
			return *this;			
		}
		secure_iterator & operator--(){
			it--;
			return *this;			
		}
		secure_iterator operator--(int i){
			while(i-- > 0)
				it--;

			assert(it<elvector->end() && it>=elvector->begin());
			return *this;			
		}
		bool operator==(const secure_iterator & x) const{
			// Diremos que dos iterator son iguales si apuntan al mismo elemento,
			// y son del mismo vector
			return it==x.it && elvector==x.elvector;
		}
		bool operator!=(const secure_iterator & x) const{
			return !(*this==x);
		}
		secure_iterator & operator=(const secure_iterator & x){
			if(this!=&x){
				elvector=x.elvector;
				it=x.it;
			}
			return *this;
		}	

	public:
		friend class conjunto<T,CMP>;
		typename vector<T>::iterator it;
		const vector<T> *elvector;
	};

	class impar_iterator{
	public:
		impar_iterator(){	
			elvector=NULL;
		}
		impar_iterator(const impar_iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		const T & operator*(){
			return *it;
		}
		impar_iterator & operator++(){
			do{
				it++;
			}while((*it).getPos()%2==0 && it<elvector->end());
			
			return *this;
		}
		impar_iterator operator++(int i){
			while(i-- > 0)
				(*this)++;

			return *this;			
		}
		impar_iterator & operator--(){
			do{
				it--;
			}while((*it).getPos()%2==0 && it>=elvector->begin());

			return *this;			
		}
		impar_iterator operator--(int i){
			while(i-- > 0)
				(*this)--;
		
			return *this;			
		}
		bool operator==(const impar_iterator & x) const{
			// Diremos que dos iterator son iguales si apuntan al mismo elemento,
			// y son del mismo vector(en misma posición)
			return it==x.it && elvector==x.elvector;
		}
		bool operator!=(const impar_iterator & x) const{
			return !(*this==x);
		}
		impar_iterator & operator=(const impar_iterator & x){
			if(this!=&x){
				elvector=x.elvector;
				it=x.it;
			}
			return *this;
		}

	public:
		friend class conjunto<T,CMP>;
		typename vector<T>::iterator it;
		const vector<T> *elvector;
	};

	class const_iterator{
	public:
		const_iterator(){	
			elvector=NULL;
		}
		const_iterator(const const_iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		const T & operator*(){
			return *it;
		}
		const_iterator & operator++(){
			it++;
			
			return *this;
		}
		const_iterator operator++(int i){
			while(i-- > 0)
				it++;

			return *this;			
		}
		const_iterator & operator--(){
			it--;
			
			return *this;			
		}
		const_iterator operator--(int i){
			while(i-- > 0)
				it--;
		
			return *this;			
		}
		bool operator==(const const_iterator & x) const{
			// Diremos que dos iterator son iguales si apuntan al mismo elemento,
			// y son del mismo vector(en misma posición)
			return it==x.it && elvector==x.elvector;
		}
		bool operator!=(const const_iterator & x) const{
			return !(*this==x);
		}
		const_iterator & operator=(const const_iterator & x){
			if(this!=&x){
				elvector=x.elvector;
				it=x.it;
			}
			return *this;
		}

	public:
		friend class conjunto<T,CMP>;
		typename vector<T>::const_iterator it;
		const vector<T> *elvector;
	};

	class const_impar_iterator{
	public:
		const_impar_iterator(){	
			elvector=NULL;
		}
		const_impar_iterator(const const_impar_iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		const T & operator*(){
			return *it;
		}
		const_impar_iterator & operator++(){
			do{
				it++;
			}while((*it).getPos()%2==0 && it<elvector->end());
			
			return *this;

		}
		const_impar_iterator operator++(int i){
			while(i-- > 0)
				(*this)++;
		
			return *this;			
		}
		const_impar_iterator & operator--(){
			do{
				it--;
			}while((*it).getPos()%2==0 && it>=elvector->begin());
			
			return *this;
			
		}
		const_impar_iterator operator--(int i){
			while(i-- > 0)
				(*this)--;
		
			return *this;			
		}
		bool operator==(const const_impar_iterator & x) const{
			// Diremos que dos iterator son iguales si apuntan al mismo elemento,
			// y son del mismo vector(en misma posición)
			return it==x.it && elvector==x.elvector;
		}
		bool operator!=(const const_impar_iterator & x) const{
			return !(*this==x);
		}
		const_impar_iterator & operator=(const const_impar_iterator & x){
			if(this!=&x){
				elvector=x.elvector;
				it=x.it;
			}
			return *this;
		}

	public:
		friend class conjunto<T,CMP>;
		typename vector<T>::const_iterator it;
		const vector<T> *elvector;
	};

	class const_secure_iterator{
	public:
		const_secure_iterator(){	
			elvector=NULL;
		}
		const_secure_iterator(const const_secure_iterator &  x){
			it=x.it;
			elvector = x.elvector;
		}
		
		const T & operator*(){
			assert(it<elvector->end() && it>=elvector->begin());
			return *it;
		}
		const_secure_iterator & operator++(){
			it++;
			assert(it<elvector->end() && it>=elvector->begin());
			return *this;
		}
		const_secure_iterator operator++(int i){
			while(i-- > 0)
				it++;

			assert(it<elvector->end() && it>=elvector->begin());
			return *this;			
		}
		const_secure_iterator & operator--(){
			it--;
			return *this;			
		}
		const_secure_iterator operator--(int i){
			while(i-- > 0)
				it--;

			assert(it<elvector->end() && it>=elvector->begin());
			return *this;			
		}
		bool operator==(const const_secure_iterator & x) const{
			// Diremos que dos iterator son iguales si apuntan al mismo elemento,
			// y son del mismo vector
			return it==x.it && elvector==x.elvector;
		}
		bool operator!=(const const_secure_iterator & x) const{
			return !(*this==x);
		}
		const_secure_iterator & operator=(const const_secure_iterator & x){
			if(this!=&x){
				elvector=x.elvector;
				it=x.it;
			}
			return *this;
		}	
	public:
		friend class conjunto<T,CMP>;
		typename vector<T>::const_iterator it;
		const vector<T> *elvector;
	};
	
private:
	friend class impar_iterator;
	friend class secure_iterator;
	friend class iterator;
	friend class const_iterator;
	friend class const_impar_iterator;	
	friend class const_secure_iterator;

	vector<value_type> vm; // vector que almacena los elementos del conjunto
	CMP comp; // criterio para guiar la ordenacion
	

		
	/** @brief Chequea el Invariante de la representacion 
		@return true si el invariante es correcto, falso en caso contrario
	*/
	bool cheq_rep( ) const;
	 
};

/** @brief imprime todas las entradas del conjunto 
@post No se modifica el conjunto.
Implementar tambien esta funcion
	*/
template <typename T, typename CMP>
ostream &  operator << ( ostream & sal, const conjunto<T,CMP> & C);

#include "conjuntoIt.hxx"

#endif
