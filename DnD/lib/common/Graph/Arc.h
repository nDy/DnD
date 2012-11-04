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
	Arc(GT* startNode, GT* endNode, LT* cost = NULL) {
		this->arcData = cost;
		this->start = startNode;
		this->end = endNode;
	}

};

#endif /* ARC_H_ */
