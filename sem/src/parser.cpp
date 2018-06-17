#include "parser.h"

// TNode --------------
/**
*The nodes can be divided into two types. The node that is already calculated and doesnt need to perform any other action (only returns value) and the node that yet
*needs to be calculated by multipling or adding values of descendants.\n
*Parameter 1: CBigDouble value of current node (if already calculated) else "0,0"\n
*Parameter 2: Pointer to the upper node. NULL if top node or node is already calculated\n
*Parameter 3: Determines what operation is about to be performed in this node (0=addition, 1=addition*(-1), 2=multiplication). -1 if node is already calculated\n
*Parameter 4: Indicates if node is already calculated (1=yes, 0=no)
*/
TNode::TNode(const CBigDouble& value, TNode * upper, const int& action, const bool& calculated)
: m_value(value) , m_upper(upper) , m_action(action) , m_ready(calculated) {}

/**
*Destructor simply removes all nodes allocated in the process of parsing.
*/
TNode::~TNode(void) 
{
	vector<TNode*>::iterator it;
	for(it=m_pointers.begin();it!=m_pointers.end();++it)
		delete *it;
}

// CBigDouble-------------
/**
*Parameter indicates which node has to be calculated. All descendants will be calculated aswell but not upper nodes.
*/
CBigDouble TNode::Calculate(TNode * calculatenode)
{
	if(!calculatenode)
		return CBigDouble("0");
	if(calculatenode->m_ready)
		return calculatenode->m_value;
	CBigDouble output;
	if(calculatenode->m_pointers.empty())
	{
		cerr << "WARNING: Some errors occured while parsing the equation. Some characters may not be counted." << endl;
		output="0";
		return output;
	}
	output=Calculate(calculatenode->m_pointers.front());
	vector<TNode*>::iterator it;
	for(it=calculatenode->m_pointers.begin()+1;it!=calculatenode->m_pointers.end();++it)
	{
		if(calculatenode->m_action==0||calculatenode->m_action==1)
			output+=Calculate(*it);
		else
			output*=Calculate(*it);
	}
	if(calculatenode->m_action==1)
	output*=-1;
	return output;
}

/**
*	firstnode is set to NULL\n
*	error is set to 0
*/
CParser::CParser(void)
{
	firstnode=NULL;
	error=0;
}

/**
*	Recursively deletes firstnode and all its descendants.
*/
CParser::~CParser(void) 
{
	if(firstnode)
		delete firstnode;
}

/**
*Parameter determines which CReader instance is about to be parsed.\n
*The expression will be parsed into the current instance of CParser
*/
void CParser::Parse(CReader& input)
{
	firstnode=new TNode(CBigDouble(0),NULL,0,0);
	TNode * currentnode=firstnode;
	char c;
	bool pointadded=0;
	/*
	*	Indicates the last sign
	*	-1 = Digit
	*	0 = No sign
	*	1 = Plus
	*	2 = Minus
	*	3 = Multiplication
	*	4 = Opening bracket
	*	5 = Closing bracket
	*/
	int lastsign=0;
	string number;
	stringstream in(input.GetString());
	int charnum=0;

	while(in.get(c))
	{
		charnum++;
		// Adds a digit or a decimal point into the string -------------------------------------------------
		if(isdigit(c)||c==','||c=='.')
		{
			if(number.empty())
			{
				if(lastsign==2)
					number+='-';
			}
			if(c==','||c=='.')
			{
				if(pointadded==0)
				{
					pointadded=1;
					number+=',';
				}
				else
				{
					PrintError(c,charnum);
					return;
				}
			}
			else
			{
				number+=c;
			}
			lastsign=-1;
		}
		// Current character is not a digit or decimal point --------------------------------------------------
		else
		{
			// Unknown character
			if(c!='+'&&c!='-'&&c!='('&&c!=')'&&c!='*')
			{
					cerr << "ERROR: Unrecognized character \'" << c << "\' [" << charnum << "]." << endl;
					error=1;
					return;
			}
			// Last character was a digit or dec point ---------------------------------------------------------
			if(lastsign==-1)
			{
				if(c=='(')
				{
					PrintError(c,charnum);
					return;
				}
				if(c==')')
				{
					currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
					number.clear();
					pointadded=0;
					if(currentnode->m_action==2)
					{
						if(currentnode->m_upper)
						{
							currentnode=currentnode->m_upper;
						}
						else
						{
							PrintError(c,charnum);
							return;
						}
					}
					if(currentnode->m_upper)
					{
						currentnode=currentnode->m_upper;
					}
					else
					{
						PrintError(c,charnum);
						return;
					}
					lastsign=5;
				}
				// Current character is not a bracket
				else
				{
					// We are currently in addiction node
					if(currentnode->m_action==1||currentnode->m_action==0)
					{
						if(c=='*')
						{
							TNode * tmp=new TNode(CBigDouble("0"),currentnode,2,0);
							currentnode->m_pointers.push_back(tmp);
							currentnode=tmp;
							currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
							number.clear();
							pointadded=0;
							lastsign=3;
						}
						if(c=='-')
						{
							currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
							number.clear();
							pointadded=0;
							lastsign=2;
						}
						if(c=='+')
						{
							currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
							number.clear();
							pointadded=0;
							lastsign=1;
						}
					}
					// We are currently in multiplication node
					else
					{
						if(c=='-'||c=='+')
						{
							currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
							number.clear();
							pointadded=0;
							if(currentnode->m_upper)
							{
								currentnode=currentnode->m_upper;
							}
							else
							{
								cerr << "ERROR: Unrecognized multiplication error [" << charnum << "]." << endl;
								error=1;
								return;
							}
							if(c=='-')
								lastsign=2;
							else
								lastsign=1;
						}
						else
						{
							currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
							number.clear();
							pointadded=0;
							lastsign=3;
						}
					}
				}			
			}
			// Last character was not a digit or dec point -------------------------------------------------------
			else
			{
				// We are at the begining of expression
				if(lastsign==0&&c!='(')
				{
					if(c=='-'||c=='+')
					{
						if(c=='-')
							lastsign=2;
						else
							lastsign=1;
					}
					if(c==')'||c=='*')
					{
						PrintError(c,charnum);
						return;
					}
				}
				// We are not at the begining of expression
				else
				{
					// Current character is a bracket
					if(c=='('||c==')')
					{
						// Current character is an opening bracket
						if(c=='(')
						{
							TNode * tmp;
							if(lastsign==2)
							{
								tmp = new TNode(CBigDouble("0"),currentnode,1,0);
							}					
							else
							{
								tmp = new TNode(CBigDouble("0"),currentnode,0,0);	
							}
							currentnode->m_pointers.push_back(tmp);
							currentnode=tmp;
							lastsign=4;
						}
						// Current character is an closing bracket
						else
						{
							if(lastsign==5)
							{
								if(currentnode->m_action==2)
								{
									if(currentnode->m_upper)
									{
										currentnode=currentnode->m_upper;
									}
									else
									{
										PrintError(c,charnum);
										return;
									}
								}
								if(currentnode->m_upper)
								{
									currentnode=currentnode->m_upper;
								}
								else
								{
									PrintError(c,charnum);
									return;
								}
								lastsign=5;
							}
							else
							{
								PrintError(c,charnum);
								return;
							}
						}
					}
					// Current character is not a bracket
					else
					{
						// Current character is plus or minus and last character was a bracket
						if((lastsign==4||lastsign==5)&&(c=='-'||c=='+'))
						{
							if(currentnode->m_action==2)
							{
								if(currentnode->m_upper)
								{
									currentnode=currentnode->m_upper;
								}
								else
								{
									PrintError(c,charnum);
									return;
								}
							}
							if(c=='-')
								lastsign=2;
							else
								lastsign=1;
						}
						// Current character is not plus or minus, or last character was not a bracket
						else
						{
							if(c=='*'&&lastsign==5)
							{
								if(currentnode->m_action==2)
								{
									lastsign=3;
								}
								else
								{
									if(!currentnode->m_pointers.empty())
									{
										TNode * tmp;
										tmp=currentnode->m_pointers.back();							
										currentnode->m_pointers.pop_back();
										currentnode->m_pointers.push_back(new TNode(CBigDouble("0"),currentnode,2,0));
										currentnode=currentnode->m_pointers.back();;
										currentnode->m_pointers.push_back(tmp);
										lastsign=3;
									}
									else
									{
										PrintError(c,charnum);
										return;
									}
								}
							}
							else
							{
								PrintError(c,charnum);
								return;
							}
						}				
					}
				}			
			}
		}
	}
	if(lastsign==3||lastsign==4)
	{
		PrintError(c,charnum);
		return;
	}
	if(lastsign==-1)
		currentnode->m_pointers.push_back(new TNode(CBigDouble(number),NULL,-1,1));
	//PrintNodes(firstnode,0);
}

/**
*Parameter 1: First node to be printed, all descendants will be printed aswell.\n
*Parameter 2: Determinates offset of the first node.
*/
void CParser::PrintNodes(const TNode * node, const int deep) const
{
	for(int i=0;i<deep;i++)
		cout << " > ";
	cout << "NODE: " << node << " SIGN: " << node->m_action << endl;
	for(int i=0;i<deep;i++)
		cout << " > ";
	cout << "UPPER: " << node->m_upper << endl;
	vector<TNode*>::const_iterator it;
	for(it=node->m_pointers.begin();it!=node->m_pointers.end();++it)
	{
		if((*it)->m_ready)
		{
			for(int i=0;i<deep;i++)
				cout << " > ";
			cout<<(*it)->m_value<<endl;
		}
		else
			PrintNodes(*it,deep+1);
	}
}

/**
*	Return value 0: No error occured during parsing or calculating.\n
*	Retur value 1: An error occured during parsing or calculaating.
*/
bool CParser::Error(void) const
{
	return error;
}

/**
*	Parameter 1: Char that error occured at\n
*	Parameter 2: Possition of char that error occured at\n
*	Prints: ERROR: Unexpected character PAR1 [PAR2].\n
*	Also sets error to 1.
*/
void CParser::PrintError(char & c,int & charnum)
{
	cerr << "ERROR: Unexpected character \'" << c << "\' [" << charnum << "]." << endl;
	error=1;
	return;
}

/**
*Performs action TNode::Calculate(first)
*/
CBigDouble CParser::Calculate(void)
{
	if(!firstnode)
		return CBigDouble("0");
	return firstnode->Calculate(firstnode);
}

