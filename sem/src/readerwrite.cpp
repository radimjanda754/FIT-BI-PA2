#include "readerwrite.h"

/**
*	Parameter 1 will be saved into the abstract class, represent expression.\n
*	Parameter 2 represents name of output file.
*/
CReaderWrite::CReaderWrite(const char* exp,const string & output) : CReader(exp) , writehere(output) {}

/**
*	Empty by default.
*/
CReaderWrite::~CReaderWrite(void) {}

/**
*	Parameter 1: is the expression from CReader class that is going to be written before the result.\n
*	Parameter 2: is result that is going to be written into the file.
*/
bool CReaderWrite::write(const string& exp,const CBigDouble& writeoutput)
{
	ofstream output(writehere.c_str(),ios::out | ios::app);
	if(!output.is_open())
		return 0;
	if(output.bad())
		return 0;
	output << exp << " = " << writeoutput << endl;
	if(output.bad())
		return 0;
	output.close();
	return 1;
}

/**
*	Returns reference to the name of written file.
*/
string& CReaderWrite::GetWriteFile(void)
{
	return writehere;
}
