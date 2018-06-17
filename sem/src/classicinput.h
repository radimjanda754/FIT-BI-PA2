#ifndef CLASSICINPUT_H
#define CLASSICINPUT_H
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "reader.h"
#include "readerwrite.h"
#include "parser.h"
using namespace std;

/**
 *	This class represent the text user interface for loading input expression.\n
 *	After starting the interface user is able to load file with expressions or write expressions into the standard input.\n
 *  Works with CReader and its subclass CReaderWrite to read expressions and CParser to parse and calculate the result.
 */

class CClassicInput
{
 public:
	/// Creates new empty instance of CClassicInput
	CClassicInput(void);
	/// Destructor
	~CClassicInput(void);
	/// Starts the interface
	void Start(void);
};

/// Gets the type of input
int GetInputType(void);

#endif
