#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "bddNode.h"
#include "bddMgr.h"

BddNode ShannonCofactor( BddMgr&, BddNode& f, BddNode& g );
