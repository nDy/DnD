#ifndef SNODE_H
#define SNODE_H
#include <iostream>

template<class T> class SNode {
private:
	T* data; //Dato a almacenar en el nodo
	SNode<T> *next; //Puntero al siguiente Nodo

	//atributos publicos de la clase
public:

	//Constructor por omision
	SNode() {
		next = this;
	}
	//constructor por copia
	SNode(SNode<T> & node) {
		this->data = node.data;
		this->next = node.next;
	}
	//constructor por copia pasando puntero
	SNode(SNode<T> * node) {
		this->data = node->data;
		this->next = node->next;
	}

	SNode(SNode<T> *& node) {
		this->data = node->data;
		this->next = node->next;
	}
	//destructor por omision
	~SNode() {
	}
	;
	//Constructor por copia
	SNode(T & dat) {
		this->data = &dat;
	}

	SNode(T *& dat) {
			this->data = dat;
		}

	//Obtener el valor de dato
	T*& getData() {
		return data;
	}
	//reseteamos el valor del nodo
	void reset() {
		next = this;
	}
	//verificamos si esta vacia la lista
	bool isEmpty() {
		return next == this;
	}

	//obtener el siguiente nodo
	SNode<T>* getNext() {
		return next;
	}
	void setNext(SNode<T>* Next) {
		next = Next;
	}

	//inserto un nodo despues de este
	void insertNext(SNode<T> * node) {
		node->next = this->next; //siguiente del nodo a insertar sera el siguiente de mi nodo actual
		this->next = node; //el siguiente de mi nodo actual sera el nodo a insertar
	}

	//remover el nodo siguiente
	void removeNext() {
		SNode<T> *aux; //definimos un nodo auxiliar donde se almacenara la informacion para no perderla
		aux = this->next; //nodo aux sera el siguiente a mi nodo actual
		if (aux == this->next->next) //Si el siguiente nodo es el final de la lista
			this->reset(); // se convierte en el final de la lista
		else
			this->next = aux->next; //el siguiente de mi nodo actual sera el siguiente aux
		delete aux; // se borra la instancia del nodo al que apunta aux
	}

};
//fin clase SNode

#endif 
