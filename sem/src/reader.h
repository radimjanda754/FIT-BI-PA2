#ifndef READER_H
#define READER_H
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "bigdouble.h"
using namespace std;

/**
 *	This class loads expression from standard input or file.\n
 *	The class is driven from CClassicInput.\n
 *  Also works with CBigDouble.
 */

class CReader
{
 public:
	/// This constructor load expression from standard input
	CReader(void);
	/// This constructor assigns a string to the expression
	CReader(const char*);
	/// This constructor load expression from the file(const char*) of a given line (const int&)
	CReader(const char* ,const int&);
	/// Destructor
	virtual ~CReader(void);
	/// Load expression from standard input
	void Read(void);
	/// Load expression from the given file
	void Read(const char*);
	/// Load expression from the file(const char*) of a given line (const int&)
	void Read(const char* ,const int&);
	///	Write into the file, only works with CReaderWrite
	virtual bool write(const string&,const CBigDouble&);
	///	Get name of file that should be written in, only works with CReaderWrite
	virtual string& GetWriteFile(void);
	/// Indicates if an error occured while reading expression
	bool Error(void) const;
	/// Indicates if the reader reached the end of file
	bool Eof(void) const;
	/// Removes all white spaces from loaded expression
	void RemoveWhiteSpaces(void);
	/// Gets reference to the loaded expression
	string& GetString(void);
	/// Output operator
	friend ostream& operator << (ostream& os, const CReader&);
 private:
	/// Represents the expression
	string value;
	/// Indicates if an error ocurred while reading expression
	bool error;
	/// Indicates if the reader reached the end of file
	bool eof;
};

#endif
