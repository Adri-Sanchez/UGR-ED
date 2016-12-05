
// CONSTRUCTORES
template <typename T, typename CMP>
conjunto<T, CMP>::conjunto(){
	vm.clear();
}

template <typename T, typename CMP>
conjunto<T, CMP>::conjunto(const conjunto<T,CMP> &d){
	for(const_iterator it=d.cbegin(); it<d.cend(); it++)
		vm.push_back(*it);
}


// FIND
template <typename T, typename CMP>
typename conjunto<T, CMP>::iterator conjunto<T, CMP>::find (const value_type & s) {
	iterator it;
	for(it=begin(); it!=end() ; it++)
		if(!comp(*it, s) && !comp(s,*it)) // Es decir, si s==*it
			return it;
	return it; // Sino devuelve iterator a end
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_iterator conjunto<T, CMP>::find  (const value_type & s) const{
	const_iterator it;
	for(it=cbegin(); it!=cend() ; it++)
		if(!comp(*it, s) && !comp(s,*it)) // Es decir, si s==*it
			return it;
	return it; // Sino devuelve iterator a end
}


// COUNT
template <typename T, typename CMP>
typename conjunto<T, CMP>::size_type conjunto<T, CMP>::count (const value_type & e) const{
	return find(e) < cend() ? 1 : 0;
}


// INSERT
template <typename T, typename CMP>
pair<typename conjunto<T, CMP>::iterator,bool> conjunto<T, CMP>::insert (const value_type& val){
	if(find(val)==end()){
		iterator up=upper_bound(val);
		
		vm.insert(up.it, val);
		return std::make_pair(up--, true);
	}else
		return std::make_pair(end(), false);
}
	

// ERASE
template <typename T, typename CMP>
typename conjunto<T, CMP>::iterator conjunto<T, CMP>::erase (const iterator position){
	vm.erase(position.it);
	return position;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::size_type conjunto<T, CMP>::erase (const value_type& val){
	iterator busca = find(val);
	if(busca!=end()){
		vm.erase(busca.it);
		return 1;
	}else
		return 0;
}
    

// 	CLEAR
template <typename T, typename CMP>
void conjunto<T, CMP>::clear(){
	vm.clear();
}


// SIZE
template <typename T, typename CMP>
typename conjunto<T, CMP>::size_type conjunto<T, CMP>::size() const{
	return vm.size();
}


// EMPTY
template <typename T, typename CMP>
bool conjunto<T, CMP>::empty() const{
	return vm.empty();
}


// OPERATOR=
template <typename T, typename CMP>
conjunto<T, CMP> & conjunto<T, CMP>::operator= (const conjunto & org){
	if(this!=&org){
		clear();
		for(const_iterator it=org.cbegin(); it<org.cend(); it++)
			vm.push_back(*it);
	}
	return *this;
}


// ITERADORES
template <typename T, typename CMP>
typename conjunto<T, CMP>::iterator conjunto<T, CMP>::begin(){
	iterator it;
	it.elvector=&vm;
	it.it=vm.begin();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::iterator conjunto<T, CMP>::end(){
	iterator it;
	it.elvector=&vm;
	it.it=vm.end();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_iterator conjunto<T, CMP>::cbegin() const{
	const_iterator it;
	it.elvector=&vm;
	it.it=vm.cbegin();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_iterator conjunto<T, CMP>::cend() const{
	const_iterator it;
	it.elvector=&vm;
	it.it=vm.cend();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::secure_iterator conjunto<T, CMP>::sbegin (){
	secure_iterator it;
	it.elvector=&vm;
	it.it=vm.begin();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_secure_iterator conjunto<T, CMP>::csbegin( ) const{
	const_secure_iterator it;
	it.elvector=&vm;
	it.it=vm.cbegin();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::secure_iterator conjunto<T, CMP>::send (){
	secure_iterator it;
	it.elvector=&vm;
	it.it=vm.end();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_secure_iterator conjunto<T, CMP>::csend( ) const{
	const_secure_iterator it;
	it.elvector=&vm;
	it.it=vm.cbegin();
	return it;
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::impar_iterator conjunto<T, CMP>::ibegin(){
	impar_iterator it;
	it.elvector=&vm;
	it.it=vm.begin();
	// Si no es impar hacemos un ++ para tener la siguiente posicion impar
	if(it.it%2==0)
		it++;

	return it;
}

/*


	POR AQUI!!!!!!!!!!!



*/
template <typename T, typename CMP>
typename conjunto<T, CMP>::const_impar_iterator conjunto<T, CMP>::cibegin( ) const{

}

template <typename T, typename CMP>
typename conjunto<T, CMP>::impar_iterator conjunto<T, CMP>::iend(){

}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_impar_iterator conjunto<T, CMP>::ciend( ) const{

}







// LOWER_BOUND
template <typename T, typename CMP>
typename conjunto<T, CMP>::iterator conjunto<T, CMP>::lower_bound (const value_type & val) {
	iterator it;
	
	for(it=end()--; it!=begin() ; it--)
		if(comp(*it, val))
			return it;
	
	return end();
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_iterator conjunto<T, CMP>::lower_bound (const value_type& val) const{
	const_iterator it;
	
	for(it=cend()-1; it!=cbegin() ; it--)
		if(comp(*it, val))
			return it;
	
	return cend();
}


// UPPER_BOUND
template <typename T, typename CMP>
typename conjunto<T, CMP>::iterator conjunto<T, CMP>::upper_bound (const value_type& val){
	iterator it;
	
	// Para que el método insert vaya más rápido a la hora de hacer el parseo,
	// empezamos por el final ya que los elementos en clinvar estan ordenados
	for(it=end()--; it!=begin() ; it--)
		if(comp(*it, val))
			return it++;
		
	return end();
}

template <typename T, typename CMP>
typename conjunto<T, CMP>::const_iterator conjunto<T, CMP>::upper_bound (const value_type& val) const{
	const_iterator it;
	
	// Para que el método insert vaya más rápido a la hora de hacer el parseo,
	// empezamos por el final ya que los elementos en clinvar estan ordenados
	for(it=cend()--; it!=cbegin() ; it--)
		if(comp(*it, val))
			return it++;
		
	return cend();
}









// OPERATOR << 
template <typename T, typename CMP>
std::ostream & operator<< (std::ostream &sal, const conjunto<T, CMP> &C){
	typename conjunto<T,CMP>::const_iterator it(C.cbegin());
	for(; it!=C.cend(); it++){
		sal << *it << endl;
	}

	return sal;
}