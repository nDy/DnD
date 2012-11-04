/*
 * ListGraph.h
 *
 *  Created on: Nov 3, 2012
 *      Author: ndy
 */

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_

#include "../List/SList.H"
#include "../List/SNode.H"
#include "Arc.h"
#include "GraphNode.h"

template<class GT, class ATC> class ListGraph {
private:
	SList<GraphNode<GT, ATC> > * graph;
public:
	void insertNode(GraphNode<GT, ATC>*& node) {
		SNode<GT> newNode(node->getData());
		graph->insertFirst(&newNode);
	}

	void insertArc(Arc<GT, ATC>* arc) {
		GraphNode<GT, ATC> aux = graph->search(arc->getStart());
		aux.insertArc(arc);
	}

	SList<GraphNode<GT, ATC> >* search(SNode<GT>*& node) {
		return graph->search(node);
	}
};

#endif /* LISTGRAPH_H_ */
