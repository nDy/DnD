#ifndef SLIST_H
#define SLIST_H

#include <iostream>
#include "SNode.H"

using namespace std;


template<class T> class SList: public SNode<T>{

	
	public:
		
	SNode<T> Node;				//Puntero al siguiente Nodo
	
	SList(){};
	
	~SList(){};

	//Insertar un elemento al inicio
	void insertFirst(SNode<T> *node){
		Node.insertNext(node);	
	};

	//devuelve el Primer elemento de la lista
	SNode<T>* getFirst(){
		return Node.getNext();
	};
	
	//remueve el primer elemento de la lista
	SNode<T>* removeFirst(){
		return Node.removeNext();
	};
	
	//insertar odenado siguiendo el criterio de menor a mayor
	void orderedInsert(SNode<T> * node){
		Node.OrderedInsertion(node);
	};

	//obtener Node
	SNode<T>& getNode(){
		return Node;
	};
	
	//verifica si la lista esta vacia
	bool isEmpty(){
		return Node->isEmpty();
	};


	/*Clase Iterador que permite el manejo de la lista*/


	class Iterator{

		private:
			
			SList<T> * list;
			
			SNode<T> * current;
		public:

			//constructor por copia
			Iterator(SList<T> & l){
				list = &l;
				current=list->getFirst();
			};

			//permiteverificar si todavia faltan elementos por revisar
			bool hasCurrent(){ 
				return current != &list->getNode(); 
			};
	
			//obtener el nodo en el que se encuentra posicionado actualmente
			SNode<T> * getCurrent(){
				if ( !this->hasCurrent())
					return NULL;

				return current;
			};

			//me posiciona en el siguiente elemento de la lista
			void next(){
				current = current->getNext();
			};

			//resetea el Iterador con el primer elemento de la lista
			void resetFirst() { 
				current = list->getNext(); 
			};
			

	};//fin clase Iterator




};//fin clase SList



#endif 
