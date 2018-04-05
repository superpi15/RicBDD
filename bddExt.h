#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdlib>
#include "bddNode.h"
#include "bddMgr.h"

BddNode ShannonCofactor( BddNode& f, BddNode& g );
