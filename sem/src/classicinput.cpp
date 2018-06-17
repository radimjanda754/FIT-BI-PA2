#include "classicinput.h"

// Gets type of input
/**
*	Constantly requesting user to select type of input or exit the sequence.\n
*	Return value shows the selection of the user:\n
*	0  = "exit" or eof\n
*	1  = "std"\n
*	-1 = "file\n
*/
int GetInputType(void)
{
	string input;
	getline (cin,input);
	if(cin.eof())
		return 0;
	if(input=="file")
		return -1;
	if(input=="std")
		return 1;
	if(input=="exit")
		return 0;
	if(input=="output")
		return 2;
	while(1)
	{
		cerr << "ERROR: Wrong input, please try again (\"file\"/\"std\"/\"output\"/\"exit\")." << endl;
		getline (cin,input);
		if(cin.eof())
			return 0;
		if(input=="file")
			return -1;
		if(input=="std")
			return 1;
		if(input=="exit")
			return 0;
		if(input=="output")
			return 2;
	}
}

// Constructor
/**
* Empty by default
*/
CClassicInput::CClassicInput(void) {}

// Destructor
/**
* Empty by default
*/
CClassicInput::~CClassicInput(void) {}

// Starts the user interface
/**
*	This method constantly keep asking for type of input and after type is selected user is able to choose his expression which is saved through CReader 
*	class and then parsed and calculated through CParser class.\n
*	Through the GetInputType() function, user is requested to type "file" or "std" what decises if the expression will be loaded from standard input or file.\n
*	User can also quit the sequence by typing "exit" or with EOF.
*/
void CClassicInput::Start(void)
{
	cout << "-> Press input type \"file\" (for input from file) / \"std\" (for standard input from console) / \"output\" (to change output) or \"exit\" to quit: " << endl;
	CReaderWrite readinput("0","");	
	string file;
	string linenum;
	int inputtype;

	while(1)
	{
		// Gets the type of input
		inputtype=GetInputType();
		// Change output is chosen
		if(inputtype==2)
		{
			cout << "Enter filename of new output (or leave empty): ";
			getline (cin,readinput.GetWriteFile());
			if(cin.eof())
				break;
			cout << "Output changed" << endl;
		}
		// Standard input is chosen
		if(inputtype==1)
		{
			cout << "Enter expression: ";
			readinput.Read();
			if(readinput.Eof())
				break;
			if(!readinput.Error())
			{
				CParser parser;
				if(readinput.GetWriteFile().empty())
				{
					parser.Parse(readinput);
					if(!parser.Error())
						cout << " = " << parser.Calculate() << endl;
				}
				else
				{
					parser.Parse(readinput);
					if(!parser.Error())
					{
						if(readinput.write(readinput.GetString(),parser.Calculate()))
							cout << "Done. (current output \"" << readinput.GetWriteFile() << "\")" << endl;
						else
						{
							cerr << "ERROR: Some errors occured while trying to write in \"" << readinput.GetWriteFile() << "\" output was reset." << endl;
							readinput.GetWriteFile()="";
						}
					}
				}
			}
		}
		// Exit is chosen
		if(!inputtype)
		{
			break;	
		}
		// Input from file is chosen
		if(inputtype==-1)
		{
			cout << "FILE: ";
			getline(cin,file);
			if(cin.eof())
				break;
			cout << "LINE NUMBERS separated with \',\' (or \"all\"): ";
			if(cin.eof())
				break;
			getline(cin,linenum);
			stringstream lines(linenum);
			cout << endl;
			// Load all lines
			if(linenum=="all")
			{
				int readall=1;
				readinput.Read(file.c_str(),readall);		
				while(!readinput.Eof())
				{
					CParser parser;
					if(!readinput.Error())
					{
						if(readinput.GetWriteFile().empty())
						{
							cout << "[LINE:" << readall << "] " << readinput << endl;
							parser.Parse(readinput);
							if(!parser.Error())
								cout << " = " << parser.Calculate() << endl;
						}
						else
						{
							cout << "[LINE:" << readall << "] ";
							parser.Parse(readinput);
							if(!parser.Error())
							{
								if(!readinput.write(readinput.GetString(),parser.Calculate()))
								{
									cerr << "ERROR: Some errors occured while trying to write in \"" << readinput.GetWriteFile() << "\" output was reset." << endl;
									readinput.GetWriteFile()="";
									break;
								}
							}
						}
					}
					if(!readinput.GetWriteFile().empty()&&!readinput.Error()&&!readinput.Eof()&&!parser.Error())
						cout << "Done. (current output \"" << readinput.GetWriteFile() << "\")" << endl;
					cout << endl;
					readall++;
					readinput.Read(file.c_str(),readall);
				}
			}
			// Load direct lines
			else
			{
				while(!lines.eof())
				{
					getline(lines,linenum,',');
					readinput.Read(file.c_str(),atoi( linenum.c_str() ));
					CParser parser;
					if(readinput.Eof())
					{
						cerr << "ERROR: Line " << linenum << " is beyond the end of file." << endl;

					}
					if(!readinput.Error())
					{
						if(readinput.GetWriteFile().empty())
						{
							cout << "[LINE:" << linenum << "] " << readinput << endl;
							parser.Parse(readinput);
							if(!parser.Error())
								cout << " = " << parser.Calculate() << endl;
						}						
						else
						{
							cout << "[LINE:" << linenum << "] ";
							parser.Parse(readinput);
							if(!parser.Error())
							{
								if(!readinput.write(readinput.GetString(),parser.Calculate()))
								{
									cerr << "ERROR: Some errors occured while trying to write in \"" << readinput.GetWriteFile() << "\" output was reset." << endl;
									readinput.GetWriteFile()="";
									break;
								}
							}
						}
					}
					if(!readinput.GetWriteFile().empty()&&!readinput.Error()&&!readinput.Eof()&&!parser.Error())
						cout << "Done. (current output \"" << readinput.GetWriteFile() << "\")" << endl;
					cout << endl;
				}
			}
		}
	}
}
