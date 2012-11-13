//============================================================================
// Name        : main.cpp
// Author      : nDy
// Version     : Alpha 1.0
// Description : DnD
//============================================================================

#include "../lib/game/DnD.h"
#include "../lib/bodies/Body.h"
#include "../lib/bodies/Character.h"
#include "../lib/grid/SquareGrid.H"

#include <iostream>

int main(int argc, char **argv) {
	SquareGrid* grid;
	grid = new SquareGrid();

	grid->getTerrain(4,5)->stepOver(false);
	grid->getTerrain(5,5)->stepOver(false);
	grid->getTerrain(6,5)->stepOver(false);

	Character * player;
	player = new Character(5, 1, grid);

	std::list<Character::node> path = player->getAstarPath(5, 7);
	std::cout
			<< "Al llenarse la lista del camino, se pueden ver en ella las propiedades que fueron declaradas"
			<< std::endl;
	std::cout
			<< " en el vertice, en caso de querer revisar el padre de cada uno de los nodos podria hacerse usando"
			<< std::endl;
	std::cout << "el valor parentX y parent Y de la estructura node."
			<< std::endl;
	for (std::list<Character::node>::iterator i = path.begin(); i != path.end();
			++i) {
		std::cout << " Pos X " << (*i).x << " Pos Y " << (*i).y << std::endl;
	}

	return 0;
}

/*
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
 << "esto es una prueba, el valor del entero adentro del nodo de grafo de inicio "
 << *arc->getStart()->getData() << std::endl;
 data = 7;
 std::cout
 << "esto es una prueba, el valor del entero adentro del nodo de grafo de salida "
 << *arc->getEnd()->getData() << std::endl;
 std::cout << "esto es una prueba, el valor del entero costo de arco "
 << arc->getCost() << std::endl;

 ListGraph<int, int> * graph;
 graph = new ListGraph<int, int>();
 std::cout << "no hay fallos creando el grafo "<< std::endl;
 graph->insertNode(gNodeS);

 std::cout << "no hay fallos de segmentacion insertando nodos al grafo "<< std::endl;
 */

/*
 DnD* Game;

 Game = new DnD();

 return Game->Execute();
 */
//BUG!!!!!!!!!!! solo se encuentran caminos diagonales en linea recta.
