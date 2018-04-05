//Author: Nero Horus [He-Teng Zhang]
#include <sstream>
#include <fstream>
#include <set>
#include <cassert>
#include <cstdlib>
#include "bddNode.h"
#include "bddMgr.h"

std::string translate( const std::string& pattern, int len ){
	std::istringstream istr( pattern );
	int id;
	std::string word;
	char ch;
	bool phase;
	std::string cube;
	cube.resize( len+1 );
	cube[0] = '1';
	for( int i=0; i<cube.size(); i++ )
		cube[i] = '-';
	while( istr >> ch ){
		phase = false;
		if( ch == '!' ){
		 	phase = true;
			istr >> ch; //left parenthesis
		}
		istr >> id;
		istr >> ch; // right parenthesis
		
		cube[id] = phase? '0': '1';
	}

	std::cout <<pattern <<":"<< cube<<std::endl;
	return cube;
}

typedef std::vector< std::string > vstr_t;
vstr_t expand_cube_recur( std::string& pattern, int id );

vstr_t expand_cube( std::string& pattern ){
	return expand_cube_recur( pattern, 0 );
}

vstr_t expand_cube_recur( std::string& pattern, int id ){
	if( id == pattern.size() ){
		vstr_t ret(1);
		ret[0] = pattern;
		return ret;
	}
	if( id == 0 || pattern[id] != '-' )
		return expand_cube_recur( pattern, id+1 );
	vstr_t lret, rret;
	std::string local_pattern = pattern;
	local_pattern[id] = '0';
	lret = expand_cube_recur( local_pattern, id+1 );
	local_pattern[id] = '1';
	rret = expand_cube_recur( local_pattern, id+1 );
	lret.insert( lret.end(), rret.begin(), rret.end() );
	return lret;
}


typedef std::set<std::string> sstr_t;
void Collect_CubeSet( BddNode& f, sstr_t& fsstr, size_t len ){
	std::vector<BddNode> fCubes;
	fCubes = f.getAllCubes();
	for( int i=0; i<fCubes.size(); i++ ){
		std::string fp = translate( fCubes[i].toString(), len );
		vstr_t vstr = expand_cube( fp );
		for( int j=0; j<vstr.size(); j++ ){
			fsstr.insert( vstr[j] );
		}
	}	
}

BddNode Get_ByPattern( const std::string& pattern ){
	BddNode ret = BddNode::_one;
	std::cout << pattern <<std::endl;
	for( int i=1; i<pattern.size(); i++ ){
		std::cout<<pattern[i];
		BddNode cur = bddMgr->getSupport(i);
		ret &= (pattern[i]=='1')? cur: ~cur; 
	}
	std::cout<<std::endl;
	std::cout << ret;
	return ret;
}

BddNode ShannonCofactor( BddNode& f, BddNode& g ){
	sstr_t fsstr, gsstr;
	size_t len = std::max( f.getLevel(), g.getLevel() );
	Collect_CubeSet( f, fsstr, len );
	Collect_CubeSet( g, gsstr, len );
	sstr_t::iterator fitr, gitr;
	/**
	std::cout<<"f cubes" <<std::endl;
	for( fitr = fsstr.begin(); fitr != fsstr.end(); fitr ++ )
		std::cout << * fitr <<std::endl;
	std::cout<<"g cubes" <<std::endl;
	for( gitr = gsstr.begin(); gitr != gsstr.end(); gitr ++ )
		std::cout << * gitr <<std::endl;
	std::cout<< "----" <<std::endl;
	/**/
	BddNode fgTrue = BddNode::_zero;
	BddNode fgFalse= BddNode::_zero;
	for( fitr = fsstr.begin(); fitr != fsstr.end(); fitr ++ ){
		if( gsstr.find( *fitr ) != gsstr.end() ){
			BddNode cur = Get_ByPattern( *fitr );
			std::cout <<cur;
			fgTrue |= cur;
		}

	}/**
	for( fitr = fsstr.begin(); fitr != fsstr.end(); fitr ++ ){
		if( gsstr.find( *fitr ) == gsstr.end() ){
			BddNode cur ;
			cur = Get_ByPattern( *fitr );
			fgFalse |= cur;
		}

	}
	/**/
	std::cout << fgTrue ;
	//std::cout <<fgFalse;
	return BddNode::_zero;
}


