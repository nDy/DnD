//============================================================================
// Name        : main.cpp
// Author      : nDy
// Version     : Alpha 1.0
// Description : DnD
//============================================================================

#include "../lib/game/DnD.h"
#include "../lib/bodies/Body.h"
#include "../lib/grid/SquareGrid.H"
#include "../lib/common/List/SList.H"
#include "../lib/common/Graph/GraphNode.h"
#include "../lib/common/Graph/Arc.h"
#include "../lib/common/Graph/ListGraph.h"

#include <iostream>

int main(int argc, char **argv) {

	//prueba de nodos y listas
	int data = 5;
	SList<int> * test;
	test = new SList<int>();
	SNode<int> * testnode;
	testnode = new SNode<int>();
	testnode->getData() = &data;
	test->insertFirst(testnode);

	std::cout
			<< "esto es una prueba, el valor del primer entero en la lista es "
			<< *test->getFirst()->getData() << std::endl;
	//prueba del nodo del grafo

	GraphNode<int, int>* gNodeS;
	gNodeS = new GraphNode<int, int>();
	gNodeS->getData() = &data;

	GraphNode<int, int>* gNodeE;
	gNodeE = new GraphNode<int, int>();
	gNodeE->getData() = &data;

	Arc<GraphNode<int, int>, int>* arc;
	arc = new Arc<GraphNode<int, int>, int>(gNodeS, gNodeE, 47);
	data = 6;
	std::cout
			<< "esto es una prueba, el valor del entero dentro del nodo de grafo de inicio "
			<< *arc->getStart()->getData() << std::endl;
	data = 7;
	std::cout
			<< "esto es una prueba, el valor del entero dentro del nodo de grafo de salida "
			<< *arc->getEnd()->getData() << std::endl;
	std::cout << "esto es una prueba, el valor del entero costo de arco "
			<< arc->getCost() << std::endl;

	/*
	 DnD* Game;

	 Game = new DnD();

	 return Game->Execute();
	 */
}
