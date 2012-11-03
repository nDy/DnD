#ifndef SLIST_H
#define SLIST_H

#include <iostream>
#include "SNode.H"

using namespace std;

template<class T> class SList: public SNode<T> {
private:
	SNode<T>* first; //Puntero al siguiente Nodo

public:

	SList() {
	}
	;

	~SList() {
	}
	;

	//insertar odenado siguiendo el criterio de menor a mayor
	void OrderedInsertion(SNode<T> *node) {
		if (this->first == NULL) {
			this->first = node;
		} else {
			SNode<T> * aux;
			SNode<T> * aux2;
			aux = first;
			aux2 = NULL;
			while (aux != aux->getNext()) {
				if (node->data < aux->data) {
					break;
				}
				aux2 = aux;
				aux = aux->getNext();
			}

			if (aux2 == NULL)
				this->insertFirst(node);
			else
				aux2->insertNext(node);

		}
	}

	//Insertar un elemento al inicio
	void insertFirst(SNode<T> *node) {
		if (first == NULL) {
			first = node;
			first->next = first; // mecanismo de seguridad para evitar insertar una lista
			return;
		}
		node->getNext() = first;
		first = node;
	}
	;

//devuelve el Primer elemento de la lista
	SNode<T>* getFirst() {
		return first;
	}
	;

//remueve el primer elemento de la lista
	SNode<T>* removeFirst() {
		SNode<T>* aux = first;
		if (first->next == first) { //Si el primero es el ultimo de la lista

			first = NULL; // Se vacia la lista
		} else {

			first = first->next; // Se coloca de cabecera de lista al segundo nodo

		}
		return aux; // Se retorna el nodo que se elimina de la lista
	}
	;
}
;
//fin clase SList

#endif 
