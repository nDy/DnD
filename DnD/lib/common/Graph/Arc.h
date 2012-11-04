/*
 * Arc.h
 *
 *  Created on: Nov 3, 2012
 *      Author: ndy
 */

#ifndef ARC_H_
#define ARC_H_

#include "GraphNode.h"
#include "../List/SList.H"

template<class GT, class LT> class Arc {
// GT se refiere al tipo de dato de los nodos del grafo, LT se refiere al tipo de dato de los arcos
// atributos privados de la clase
private:

	LT arcData;
	GT * start;
	GT * end;

	//atributos publicos de la clase
public:

	//Constructor por omision
	Arc(GT* startNode, GT* endNode, LT cost) {
		this->arcData = cost;
		this->start = startNode;
		this->end = endNode;
	}

	GT *& getStart() {
		return this->start;
	}

	GT *& getEnd() {
		return this->end;
	}

	LT getCost() {
		return this->arcData;
	}

	void setCost(LT Cost) {
		this->arcData = Cost;
	}

	bool operator>(const Arc<GT, LT>*& c) const {
		return this->arcData > c->arcData;
	}

};

#endif /* ARC_H_ */
