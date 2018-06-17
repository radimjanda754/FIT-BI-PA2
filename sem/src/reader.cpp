#include "reader.h"

// Constructors and destructor
/**
*	Calls the Read() method
*/
CReader::CReader(void)
{
	Read();
}

/**
*	Parameter: Will be directly assinged into the reader.\n
*/
CReader::CReader(const char* input)
{
	value=input;
	eof=0;
	error=0;
	RemoveWhiteSpaces();
}

/**
*	Parameter 1: Represents name file which will be readed.\n
*	Parameter 2: Represents line number which containst required expression.
*/
CReader::CReader(const char* file,const int& linenumber)
{
	Read(file,linenumber);
}

/**
*	Empty by default.
*/
CReader::~CReader(void) {}

// Reads from standard input
/**
*	User is asked to enter expression directly into the standard input.
*/
void CReader::Read(void)
{
	error=0;
	eof=0;
	getline(cin,value);
	if(cin.eof())
	{
		eof=1;
		return;
	}
	if(value.empty())
	{
		cerr << "ERROR: Input is empty." << endl;
		value="0";
		error=1;
	}
	RemoveWhiteSpaces();
}

// Reads first line of file
/**
*	Parameter: Represents name file which will be readed.\n
*/
void CReader::Read(const char* file)
{
	Read(file,1);
}

// Reads given line of file
/**
*	Parameter 1: Represents name file which will be readed.\n
*	Parameter 2: Represents line number which containst required expression.
*/
void CReader::Read(const char* file,const int& linenumber)
{
	// Line number check
	eof=0;
	if(linenumber<1)
	{
		cerr << "ERROR: Wrong line number." << endl;
		error=1;
		return;
	}
	error=0;
	ifstream input(file,ios::in);
	// File seems to exists
	if(input.is_open())
	{
		for(int i=0;i<linenumber;i++)
		{
			getline(input,value);
			// Eof check
			if(input.eof())
			{
				eof=1;
				error=1;
				return;
			}
		}
		if(value.empty())
		{
			cerr << "ERROR: Line " << linenumber << " is empty." << endl;
			value="0";
			error=1;
		}
	}
	else
	{
		cerr << "ERROR: Can't open file \"" << file << "\"." << endl;
		value="0";
		error=1;
		eof=1;
	}
	input.close();
	RemoveWhiteSpaces();
}

// Other methods
/**
*	Return value 0: No error occured during reading input.\n
*	Retur value 1: An error occured during reading input.
*/
bool CReader::Error(void) const
{
	return error;
}

/**
*	Return value 0: Reader hasnt reached end of file yet.\n
*	Retur value 1: Reader has already reached end of file.
*/
bool CReader::Eof(void) const
{
	return eof;
}

/**
*	Uses std::remove_if
*/
void CReader::RemoveWhiteSpaces(void)
{
	value.erase( std::remove_if( value.begin(), value.end(), ::isspace ), value.end() );
}

/**
*	Reference to string::value is returned.
*/
string& CReader::GetString(void)
{
	return value;
}

/**
*Parameter 1 is stream where the currant value will be printed\n
*Parameter 2 is value which has to be printed 
*/
ostream& operator << (ostream& os, const CReader& cr)
{
	os << cr.value;
	return os;
}


bool CReader::write(const string&,const CBigDouble&)
{
	cerr << "ERROR: Invalid ose of CReader class." << endl;
	return 0;
}

string& CReader::GetWriteFile(void)
{
	cerr << "ERROR: Invalid ose of CReader class." << endl;
	return value;
}

