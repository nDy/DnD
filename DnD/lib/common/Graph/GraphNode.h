/*
 * Graph.h
 *
 *  Created on: Nov 3, 2012
 *      Author: ndy
 */

#ifndef GRAPH_H_
#define GRAPH_H_

#include "../List/SList.H"
#include "Arc.h"

template<class GT, class LTC> class GraphNode {
// GT se refiere al tipo de dato de los nodos del grafo, LT se refiere al tipo de dato de los arcos
//atributos privados de la clase
private:
	GT * nodeData;
	SList<Arc<GraphNode<GT, LTC>, LTC> > *arcList;
	//atributos publicos de la clase
public:

	//Constructor por omision
	GraphNode() {
	}

	GraphNode(GT*& GraphData) {
		nodeData = GraphData;
	}

	GT *& getData() {
		return nodeData;
	}

	void insertArc(Arc<GraphNode<GT, LTC>, LTC>*& Arc) {
		arcList->OrderedInsertion(Arc);
	}

};
//fin clase GraphNode

#endif /* GRAPH_H_ */
