#include "conjunto.h"


// CONSTRUCTORES
conjunto::conjunto(){
	vm.clear();
}

conjunto::conjunto (const conjunto & d){
	for(const_iterator it=d.cbegin(); it<d.cend(); it++)
		vm.push_back(*it);
}


// FUNCIONES AUXILIARES
// Estas son unas funciones auxiliares que me ayudarán con las que vienen a continuación
conjunto::const_iterator conjunto::posicion(const str &chr, const unsigned int &pos) const{
	const_iterator it;
	for(it=cbegin(); it<cend() ; it++)
		if((*it).getChr()==chr && (*it).getPos()==pos)
			return it;
	// Si no lo encuentra devuelve el end		
	return it;
}

conjunto::const_iterator conjunto::posicion(const str & ID) const{
	const_iterator it;
	for(it=cbegin(); it<cend() ; it++)
		if((*it).getID()==ID)
			return it;
	return it;
}

conjunto::const_iterator conjunto::posicion(const conjunto::value_type &e) const{
	// Si me dan un objeto mutación miraré el ID pues es lo mas sencillo 
	const_iterator it;
	for(it=cbegin(); it<cend() ; it++)
		if((*it).getID()==e.getID())
			return it;
	return it;
}



// FIND
pair<conjunto::value_type,bool> conjunto::find (const str &chr, const unsigned int &pos) const{
	bool found=false;
	value_type mutacion;
	const_iterator it = posicion(chr, pos);
	
	if(it<cend()){
		found=true;
		mutacion = *it;
	}

	return std::make_pair(mutacion, found);
}

pair<conjunto::value_type,bool> conjunto::find (const str & ID) const{
	bool found=false;
	value_type mutacion;
	const_iterator it = posicion(ID);
	
	if(it<cend()){
		found=true;
		mutacion = *it;
	}

	return std::make_pair(mutacion, found);
}
	
pair<conjunto::value_type,bool> conjunto::find (const conjunto::value_type & e) const{
	return find(e.getID());
}



// COUNT
conjunto::size_type conjunto::count (const str & chr, const unsigned int & pos) const{
	return posicion(chr, pos)<cend() ? 1 : 0;
}

conjunto::size_type conjunto::count (const str & ID) const{	
	return posicion(ID)<cend() ? 1 : 0;
}

conjunto::size_type conjunto::count (const conjunto::value_type & e) const{
	return posicion(e)<cend() ? 1 : 0;
} 


 
// INSERT
bool conjunto::insert( const conjunto::value_type & e){
	if(posicion(e)==cend()){
		iterator up=upper_bound(e);
		
		vm.insert(up, e);
		return true;
	}else
		return false;
}




// ERASE
bool conjunto::erase(const str & chr, const unsigned int & pos){
	const_iterator it=posicion(chr, pos);
	if(it<cend()){
		vm.erase(it);
		return true;
	}else
		return false;
}

bool conjunto::erase(const string & ID){
	const_iterator it=posicion(ID);
	if(it<cend()){
		vm.erase(it);
		return true;
	}else
		return false;	
}

bool conjunto::erase(const conjunto::value_type & e){
	const_iterator it=posicion(e);
	if(it<cend()){
		vm.erase(it);
		return true;
	}else
		return false;
}




// CLEAR
void conjunto::clear(){
	vm.clear();
}



// SIZE
conjunto::size_type conjunto::size() const{
	return vm.size();
}


// EMPTY
bool conjunto::empty() const{
	return size()==0;
}


// OPERATOR=
conjunto & conjunto::operator=( const conjunto & org){
	if(this!=&org){
		vm.clear();
		for(const_iterator it=org.cbegin(); it<org.cend(); it++)
			vm.push_back(*it);
	}
	return *this;
}



// ITERADORES
conjunto::iterator conjunto::begin(){
	return vm.begin();
}

conjunto::iterator conjunto::end(){
	return vm.end();
}

conjunto::const_iterator conjunto::cbegin() const{
	return vm.begin();
}

conjunto::const_iterator conjunto::cend() const{
	return vm.end();
}


// LOWER_BOUND
conjunto::iterator conjunto::lower_bound (const str & chr, const unsigned int & pos) {
	// Lo mas fácil es crear una mutacion con este chr y pos y compararlas igual que abajo
	value_type mut;
	mut.setChr(chr);
	mut.setPos(pos);
	
	return lower_bound(mut);
}
	
conjunto::iterator conjunto::lower_bound (const conjunto::value_type & e) {
	iterator it;
	
	for(it=end()-1; it>=begin() ; it--)
		if(*it < e)
			return it;
	
	return end();
}




// UPPER_BOUND
conjunto::iterator conjunto::upper_bound (const str & chr, const unsigned int & pos) {
	// Lo mismo de lower_bound
	value_type mut;
	mut.setChr(chr);
	mut.setPos(pos);
	
	return upper_bound(mut);
}
	
conjunto::iterator conjunto::upper_bound (const conjunto::value_type & e) {
	iterator it;
	
	// Para que el método insert vaya más rápido a la hora de hacer el parseo,
	// empezamos por el final ya que los elementos en clinvar estan ordenados
	for(it=end()-1; it<begin() ; it--)
		if(*it < e)
			return it+1;
		
	return end();
}














