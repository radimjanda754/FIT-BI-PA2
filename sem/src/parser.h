#ifndef PARSER_H
#define PARSER_H
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <sstream>
#include "bigdouble.h"
#include "reader.h"
using namespace std;

/**
 *	This structure represents node of n-nary tree where the expression will be parsed. Used by CParser.\n
 *  Also uses CBigDouble since values of nodes are represented by it.
 */

struct TNode
{
	/// Create an instance of CBigDouble, TNode* (upper structure), const int (sign) and const bool (indicates if structure needs to be calculated)
	TNode(const CBigDouble&, TNode*, const int&, const bool&);
	/// Destructor
	~TNode();
	/// Calculates particular node returning CBigDouble
	CBigDouble Calculate(TNode *);
	/// Value, if the node is already calculated.
	CBigDouble m_value;
	/// Pointer to the upper structure.
	TNode * m_upper;
	/// Vector of pointers to the descendants.
	vector<TNode*> m_pointers;
	/// Indicates sign in this node (-1=already calculated, 0=addition, 1=addition*(-1), 2=multiplication)
	int m_action;
	/// Indicates if the node is already calculated
	bool m_ready;
};

/**
 *	This class parses the expression using Parse(CReader) method and then calculates result using Calculate(void).\n
 *	The expression is parsed into the n-nary tree of TNode nodes.\n
 *  When calculated, returns an instance of CBigDouble.
 */

class CParser
{
 public:
	/// Creates an empty instance of CParser
	CParser(void);
	/// Destructor
	~CParser(void);
	/// Parses an expresion of CReader into the n-nary tree starting with firstnode.
	void Parse(CReader&);
	/// Print representation of parsed expression.
	void PrintNodes(const TNode *, const int) const;
	/// Indicates if an error ocurred.
	bool Error(void) const;
	/// Prints error
	void PrintError(char & c,int & charnum);
	/// Calculates the result.
	CBigDouble Calculate(void);
 private:
	/// Points to the first node of parsed expression
	TNode * firstnode;
	/// Indicates if an error ocurred.
	bool error;
};

#endif
