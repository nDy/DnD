/*
 * ListGraph.h
 *
 *  Created on: Nov 3, 2012
 *      Author: ndy
 */

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_

#include "../List/SList.H"
#include "Arc.h"
#include "GraphNode.h"

template<class GT, class ATC> class ListGraph {
private:
	SList<GraphNode<GT, ATC> > graph;
public:
	void insertNode() {
	}
	void insertArc() {
	}
};

#endif /* LISTGRAPH_H_ */
