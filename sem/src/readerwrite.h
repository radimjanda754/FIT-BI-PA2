#ifndef READERWRITE_H
#define READERWRITE_H
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include "reader.h"
#include "bigdouble.h"
using namespace std;

/**
*	Writes output into the file (if any output file is selected)\n
*	Subclass of CReader. Also works with CBigDouble\n
*	Polymorphism is used to keep expression in abstract class, so there is no need to copy the expression into the CReaderWrite instance
*/

class CReaderWrite : public CReader
{
 public:
	/// Creates new instance of CWriter
	CReaderWrite(const char*,const string &);
	/// Destructor
	~CReaderWrite(void);
	///	Write into the file
	bool write(const string&,const CBigDouble&);
	///	Get name of file that should be written in
	string& GetWriteFile(void);
 private:
	string writehere;
};

#endif
