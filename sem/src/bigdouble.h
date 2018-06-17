#ifndef BIGDOUBLE_H
#define BIGDOUBLE_H
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
using namespace std;

/**
 *	This class represent a data type of a "big double" which can teoretically have unlimited number of digits before and after a decimal point.\n
 *	Using overloaded operators is able to perform mathematical operations of addition(subtraction) and multiplication.\n
 *  The digits are saved in two strings ( leftvalue and rightvalue )\n
 *  leftvalue = contains digits before the decimal point\n
 *  rightvalue = contains digits after the decimal point
 */

class CBigDouble
{
 public:
	/// Creates an instance of CBigDouble with 0,0 value.
	CBigDouble (void);
	/// Creates an instance of CBigDouble with (integer),0 value.
	CBigDouble (const int&);
	/// Creates an instance equal to the string value.
	CBigDouble (const string&);
	/// Destructor
	~CBigDouble (void);
	// Assingment operators
	/// Assigns a string into the current instance
	CBigDouble& operator = (const string&);
	/// Assigns another CBigDouble into the current instance (deep copy)
	CBigDouble& operator = (const CBigDouble&);
	/// Assigns int into the current instance (deep copy)
	CBigDouble& operator = (const int&);
	// Mathematical operators
	/// Addition (and subtraction) operator, adding another CBigDouble into the current instance
	friend CBigDouble operator + (const CBigDouble&,const CBigDouble&);
	/// Addition (and subtraction) operator, makes new CBigDouble(const string&) and adds it into the current instance
	friend CBigDouble operator + (const CBigDouble&,const string&);
	/// Addition (and subtraction) operator, makes new CBigDouble(const int&) and adds it into the current instance
	friend CBigDouble operator + (const CBigDouble&,const int&);
	/// Multiplication operator, multiplicating current instance with another CBigDouble instance
	friend CBigDouble operator * (const CBigDouble&,const CBigDouble&);
	/// Multiplication operator, multiplicating current instance with new CBigDouble(const string&)
	friend CBigDouble operator * (const CBigDouble&,const string&);
	/// Multiplication operator, multiplicating current instance with new CBigDouble(const int&)
	friend CBigDouble operator * (const CBigDouble&,const int&);
	/// Prints value of current instance.
	friend ostream& operator << (ostream& os, const CBigDouble&);
	// Other mathematical operators
	/// Almost equal to + (const CBigDouble&,const string& add) operator
	CBigDouble& operator += (const string& add);
	/// Almost equal to + (const CBigDouble&,const int& add) operator
	CBigDouble& operator += (const int& add);
	/// Almost equal to + (const CBigDouble&,CBigDouble& add) operator
	CBigDouble& operator += (const CBigDouble& add);
	/// Almost equal to * (const CBigDouble&,const string& add) operator
	CBigDouble& operator *= (const string& add);
	/// Almost equal to * (const CBigDouble&,const int& add) operator
	CBigDouble& operator *= (const int& add);
	/// Almost equal to * (const CBigDouble&,CBigDouble& add) operator
	CBigDouble& operator *= (const CBigDouble& add);
	/// This method removes unnecessary zeroes and improves the form of instalce overall.
	void RemoveZeroes(void);
 private:
	/// Represents digits before decimal point.
	string leftvalue; 
	/// Represents digits after decimal point.
	string rightvalue;
	/// Represents sign (0=plus , 1=minus)
	bool minus;
};

#endif
