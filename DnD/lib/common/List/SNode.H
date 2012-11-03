#ifndef SNODE_H
#define SNODE_H
#include <iostream>

using namespace std;


template<class T> class SNode
{

	//atributos publicos de la clase
	public:
		T data;					//Dato a almacenar en el nodo
		SNode<T> *next;				//Puntero al siguiente Nodo

	//Constructor por omision
	SNode(){
		next=this;
	}
	//constructor por copia
	SNode(SNode<T> & node){
		this->data=node.data;
		this->next=node.next;
	}
	//constructor por copia pasando puntero
	SNode(SNode<T> * node){
		this->data=node->data;
		this->next=node->next;
	}
	//destructor por omision
	~SNode(){};
	//Constructor por copia
	SNode(const T & dat){
		data=dat;
	}

	//Obtener el valor de dato
	T& getData(){
		return data;	
	}
	//reseteamos el valor del nodo
	void reset(){
			next = this;
	}
	//verificamos si esta vacia la lista
	bool isEmpty(){
			return next == this;
	}
	
	//obtener el siguiente nodo
	SNode<T>* getNext(){	
			return next;	
	}

	//inserto un nodo
	void insertNext(SNode<T> * node){
		node->next = this->next;		//siguiente del nodo a insertar sera el siguiente de mi nodo actual
		this->next = node;			//el siguiente de mi nodo actual sera el nodo a insertar
	}

	//remover el nodo siguiente
	SNode<T>* removeNext(){
		SNode<T> *aux;				//definimos un nodo auxiliar donde se almacenara la informacion para no perderla
		aux = this->next;			//nodo aux sera el siguiente a mi nodo actual
		this->next = aux->next;			//el siguiente de mi nodo actual sera el siguiente aux
		aux->reset();				//reseteo el nodo aux y queda eliminado de la lista
		return aux;
	}

	//insertar odenado siguiendo el criterio de menor a mayor
	void OrderedInsertion(SNode<T> *node){
		SNode *aux;
		SNode *aux2;
		aux = this->getNext();				//obtengo el siguiente nodo a mi nodo actual
		aux2 = this;					//mantengo una referencia a mi nodo actual

		while(aux != this){				//mientras mi nodo siguiente no sea mi nodo actual
			if(node->data < aux->data){		//verifico que el dato de mi nodo a insertar sea menor al nodo siguiente
				aux2->insertNext(node);		//inserto y termino el metodo
				return;
			}
			aux2 = aux;				//me muevo al siguiente nodo de la lista
			aux = aux->getNext();
		}
		aux->insertNext(node);				//inserto el nodo en la ultima posicion de la lista		
	}

};//fin clase SNode



#endif 
