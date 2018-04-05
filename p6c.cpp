/****************************************************************************
  FileName     [ testBdd.cpp ]
  PackageName  [ ]
  Synopsis     [ Define main() ]
  Author       [ Chung-Yang (Ric) Huang ]
  Copyright    [ Copyleft(c) 2005-present DVLab, GIEE, NTU, Taiwan ]
****************************************************************************/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include "bddNode.h"
#include "bddMgr.h"
#include "bddExt.h"

using namespace std;

/**************************************************************************/
/*                        Define Global BDD Manager                       */
/**************************************************************************/
BddMgr bm;

/**************************************************************************/
/*                    Define Static Function Prototypes                   */
/**************************************************************************/
static void initBdd(size_t nSupports, size_t hashSize, size_t cacheSize);


/**************************************************************************/
/*                             Define main()                              */
/**************************************************************************/
int
main()
{
	initBdd(6, 127, 61);
	
	/*-------- THIS IS JUST A TEST CODE ---------*/
	BddNode a(bm.getSupport(1));
	BddNode b(bm.getSupport(2));
	BddNode c(bm.getSupport(3));
	BddNode d(bm.getSupport(4));
	BddNode e(bm.getSupport(5));
	BddNode f(bm.getSupport(6));

	printf(" %s(%d), %s(%d), %s(%d), %s(%d), %s(%d), %s(%d) \n","a", 1, "b", 2, "c", 3, "d", 4, "e", 5, "f", 6 );	

	BddNode g1 = b & d;
	BddNode g2 = e & ~c;
	BddNode g3 = a & b;
	BddNode g4 = c & g1;
	BddNode g5 = g1 | g2;
	BddNode g6 = d  | g2;
	BddNode g7 = g3 & g6;
	BddNode g8 = g4 | g7;
	BddNode g9 = f  & g8;
	
	//Compute Cofactor
	//BddNode g9pos = f & g8;
	//BddNode g9neg = f ;//BddNode::_zero;
	//BddNode diff = g9pos ^ g9neg;

	ShannonCofactor( g9, g5 );
	//ofstream ofile("i.dot");
	//i.drawBdd("i", ofile);
	//system("dot -o i.png -Tpng i.dot");
	
	/*----------- END OF TEST CODE ------------*/
}


/**************************************************************************/
/*                          Define Static Functions                       */
/**************************************************************************/
static void
initBdd(size_t nin, size_t h, size_t c)
{
   BddNode::_debugBddAddr = true;
   BddNode::_debugRefCount = true;

//   bm.reset();
   bm.init(nin, h, c);
}

