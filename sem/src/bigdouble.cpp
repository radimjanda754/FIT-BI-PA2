#include "bigdouble.h"

// Constructors
/**	leftvalue is set to 0\n
*	right value is set to 0\n
*	minus is set to 0
*/
CBigDouble::CBigDouble ( void ) {
	leftvalue="0";
	rightvalue="0";
	minus=0;
}

/** Parameter will mean digits before decimal point, digits after decimal point will be 0 */
CBigDouble::CBigDouble ( const int& IntValue ) {
	minus=0;
	stringstream ss;
	ss << IntValue;
	rightvalue="0";
	leftvalue=ss.str();
	RemoveZeroes();
}
/** Parameter will mean digits before and after decimal point. String will be normalized using RemoveZeroes() method.*/
CBigDouble::CBigDouble ( const string& StrValue ) {

	minus=0;
	stringstream ss;
	ss << StrValue;
	getline(ss,leftvalue,',');
	getline(ss,rightvalue,',');
	RemoveZeroes();
}
// Destructor
/**
*Empty by default
*/
CBigDouble::~CBigDouble (void) {}

// Assignment operators
/** Parameter will mean digits before and after decimal point. String will be normalized using RemoveZeroes() method.*/
CBigDouble& CBigDouble::operator = (const string& add) {
	minus=0;
	stringstream ss;
	ss << add;
	getline(ss,leftvalue,',');
	getline(ss,rightvalue,',');
	RemoveZeroes();
	return *this;
}
/** Parameter will be directly assinged into the current instance */
CBigDouble& CBigDouble::operator = (const CBigDouble& add) {
	leftvalue=add.leftvalue;
	rightvalue=add.rightvalue;
	minus=add.minus;
	return *this;
}
/** Parameter will mean digits before decimal point, digits after decimal point will be 0 */
CBigDouble& CBigDouble::operator = (const int& IntValue) {
	minus=0;
	stringstream ss;
	ss << IntValue;
	rightvalue="0";
	leftvalue=ss.str();
	RemoveZeroes();
	return *this;
}

// Other methods
/** If there are no digits before or after decimal point, the determined value will be changed to zero.\n
* 	for example: [,456]	will be changed to	[0,456]\n
  	[00045,]	will be changed to	[45,0]
*/
void CBigDouble::RemoveZeroes( void )
{
	int llen=leftvalue.length();
	int rlen=rightvalue.length();
	// Removes unnecessary zeroes before the decimal point.
	if(!rlen)
	{
		rightvalue="0";
		rlen=1;
	}
	while(rlen>1)
	{
		if(*(rightvalue.rbegin())=='0')
		{
			rightvalue.erase(rightvalue.end()-1);
			rlen--;
		}
		else
			break;
	}
	// Removes unnecessary zeroes after the decimal point and sets a sign.
	if(!llen)
	{
		leftvalue="0";
		llen=1;
	}
	else
	{
		if(leftvalue[0]=='-')
		{
			leftvalue.erase(leftvalue.begin());
			llen--;
			while(llen>1)
			{
				if(leftvalue[0]=='0')
				{
					leftvalue.erase(leftvalue.begin());
					llen--;
				}
				else
					break;
			}
			if(llen==1&&rlen==1)
			{
				if(leftvalue[0]=='0'&&rightvalue[0]=='0')
					minus=0;
				else
					minus=1;
			}
			else
				minus=1;
		}
	}
	while(llen>1)
	{
		if(leftvalue[0]=='0')
		{
			leftvalue.erase(leftvalue.begin());
			llen--;
		}
		else
			break;
	}
}

// Mathematical operators
/** The operator first determines if the operation will be addiction or subtraction (depends on sings of both numbers)
	and then performs the chosen action.\n
	Creates temporary strings and returns new instance of CBigDouble(string).
*/
CBigDouble operator + (const CBigDouble& leftA,const CBigDouble& rightB) 
{
	// Creates temporary string
	string left(leftA.leftvalue+leftA.rightvalue);
	string right(rightB.leftvalue+rightB.rightvalue);
	int rightmove;
	if(leftA.rightvalue.length()>rightB.rightvalue.length())
	{
		rightmove=leftA.rightvalue.length();
		int AddZeroes=leftA.rightvalue.length()-rightB.rightvalue.length();
		while(AddZeroes>0)
		{
			right+='0';
			AddZeroes--;
		}
	}
	else
	{
		rightmove=rightB.rightvalue.length();
		int AddZeroes=rightB.rightvalue.length()-leftA.rightvalue.length();
		while(AddZeroes>0)
		{
			left+='0';
			AddZeroes--;
		}	
	}

	// Variable declaration
	bool minusoutput=0; // Indicates if the result is a minus
	int minuses=0; // Indicetas if the both numbers are 
	int trans=0; // Transfer
	int add=0; // Assistant int
	string tmp; // Assistant string
	string* upper; // Assistant string pointer
	string* bottom; // Assistant string pointer
	// Indicate if the input numbers are minus
	if(leftA.minus)
		minuses++;
	if(rightB.minus)
		minuses++;

	int lindex=left.length()-1;
	int rindex=right.length()-1;

	// Only one number is mins, subtraction will be performed
	if(minuses==1)
	{
		// Preselection of assistant pointers
		if(lindex>rindex)
		{
			upper=&left;
			bottom=&right;
			if(leftA.minus)
				minusoutput=1;
		}
		if(rindex>lindex)
		{
			upper=&right;
			bottom=&left;
			if(rightB.minus)
				minusoutput=1;
		}
		if(lindex==rindex)
		{
			bool UndBset=0;
			for(int i=0;i<=lindex;i++)
			{
				if(left[i]>right[i])
				{
					UndBset=1;
				 	upper=&left;
					bottom=&right;
					if(leftA.minus)
						minusoutput=1;
					break;
				}
				if(left[i]<right[i])
				{
					UndBset=1;
				 	upper=&right;
					bottom=&left;
					if(rightB.minus)
						minusoutput=1;
					break;
				}
			}
			if(!UndBset)
			{
				CBigDouble returnzis;
				return returnzis;
			}
		}
		int uindex=upper->length()-1;
		int bindex=bottom->length()-1;
		for(int i=0;i<=bindex;i++)
		{
			int upint=(int)((*upper)[uindex-i]-'0');
			int botint=(trans+(int)((*bottom)[bindex-i]-'0'));
			if(botint<=upint)
			{
				tmp.insert(tmp.begin(),(char)('0'+(upint-botint)));
				trans=0;
			}
			else
			{
				tmp.insert(tmp.begin(),(char)('0'+(10+upint-botint)));
				trans=1;
			}
		}
		for(int i=bindex+1;i<=uindex;i++)
		{
			int upint=(int)((*upper)[uindex-i]-'0');
			int botint=trans;
			if(botint<=upint)
			{
				add=upint-botint;
				tmp.insert(tmp.begin(),(char)('0'+(add)));
				trans=0;
			}
			else
			{
				add=10+upint-botint;
				tmp.insert(tmp.begin(),(char)('0'+(add)));
				trans=1;
			}
		}
		tmp.insert(tmp.end()-rightmove,',');
		CBigDouble output(tmp);
		if(minusoutput)
			output.minus=1;
		output.RemoveZeroes();
		return output;
	}

	// No minus or both numbers are minus, addiction will be performed.
	int upperindex;
	int bottomindex;
	// Preselection of assistant pointers
	if(lindex>rindex)
	{	
		upper=&left;
		bottom=&right;
		upperindex=lindex;
		bottomindex=rindex;
	}
	else
	{
		upper=&right;
		bottom=&left;
		upperindex=rindex;
		bottomindex=lindex;
	}
	for(int i=0;i<=upperindex;i++) // Go by greater number
	{
		if(i>bottomindex) // No other digits left from smaller number
		{
			add=trans+(int)((*upper)[upperindex-i]-'0');
			if(add>=10)
			{
				add=add-10;
				tmp.insert(tmp.begin(),(char)('0'+add));
				trans=1;
			}
			else
			{
				tmp.insert(tmp.begin(),(char)('0'+add));
				trans=0;
			}
		}
		else
		{
			add=trans+(int)(left[lindex-i]-'0')+(int)(right[rindex-i]-'0');
			if(add>=10)
			{
				tmp.insert(tmp.begin(),(char)('0'+(add-10)));
				trans=1;
			}
			else
			{
				tmp.insert(tmp.begin(),(char)('0'+add));
				trans=0;
			}
		}
	}
	if(trans==1)
		tmp.insert(tmp.begin(),'1');
	tmp.insert(tmp.end()-rightmove,',');

	CBigDouble output(tmp);

	if(minuses==2)
		output.minus=1;
	output.RemoveZeroes();
	return output;
}
/** The operator first determines if the result will be minus (depends on sings of both numbers)
*	and then starts multipling.\n
*	Multipling is performed simply number by number and particular results are added to output.\n
*	Creates temporary strings and returns new instance of CBigDouble(string).
*/
CBigDouble operator * (const CBigDouble& leftA,const CBigDouble& rightB)
{
	// Creates temporary strings
	string left(leftA.leftvalue+leftA.rightvalue);
	string right(rightB.leftvalue+rightB.rightvalue);

	// Indicates if the result is minus
	int minuses=0;
	if(leftA.minus)
		minuses++;
	if(rightB.minus)
		minuses++;

	int trans=0; // Transfer
	int add; // Assistant int
	CBigDouble output; // Result will be saved there
	string calcString; // Assistant string

	int lindex=left.length()-1; // Total digits of first number -1
	int rindex=right.length()-1; // Total digits of second number -1

	for(int i=0;i<=rindex;i++)
	{
		trans=0;
		calcString.clear();
		for(int i2=0;i2<=lindex;i2++)
		{
			add=trans+(int)(left[lindex-i2]-'0')*(int)(right[rindex-i]-'0');
			if(add>=10)
			{
				trans=add/10;
				add=add-(10*trans);
				calcString.insert(calcString.begin(),(char)('0'+add));
			}
			else
			{
				calcString.insert(calcString.begin(),(char)('0'+add));
				trans=0;
			}
		}
		if(trans>0)
			calcString.insert(calcString.begin(),(char)('0'+trans));
		for(int i3=0;i3<i;i3++)
			calcString+='0';
		output+=calcString;
	}
	
	// Adds decimal point
	output.rightvalue.clear();
	if((leftA.rightvalue.length()+rightB.rightvalue.length())>=output.leftvalue.length())
	{
		while((leftA.rightvalue.length()+rightB.rightvalue.length())!=output.leftvalue.length())
			output.leftvalue.insert(output.leftvalue.begin(),'0');
		output.rightvalue=output.leftvalue;
		output.leftvalue="0";
		output.RemoveZeroes();
	}
	else
	{
		output.rightvalue.insert(output.rightvalue.begin(),output.leftvalue.end()-(leftA.rightvalue.length()+rightB.rightvalue.length()),output.leftvalue.end());
		output.leftvalue.erase(output.leftvalue.end()-(leftA.rightvalue.length()+rightB.rightvalue.length()),output.leftvalue.end());
		output.RemoveZeroes();
	}
	// Changes sign if needed
	if(minuses==1)
		output.minus=1;

	return CBigDouble(output);
}

CBigDouble operator * (const CBigDouble& left,const int& AddThis) 
{
	/**Makes a new instance of CBigDouble(Parameter 2) and then work exactly like operator* (const CBigDouble &, const CBigDouble &)*/
	CBigDouble tmp(AddThis);
	const CBigDouble& output=left*tmp;
	return output;
}

CBigDouble operator * (const CBigDouble& left,const string& AddThis) 
{
	/**Makes a new instance of CBigDouble(Parameter 2) and then work exactly like operator* (const CBigDouble &, const CBigDouble &)*/
	CBigDouble tmp(AddThis);
	const CBigDouble& output=left*tmp;
	return output;
}

CBigDouble operator + (const CBigDouble& left,const int& AddThis) 
{
	/**Makes a new instance of CBigDouble(Parameter 2) and then work exactly like operator+ (const CBigDouble &, const CBigDouble &)*/
	CBigDouble tmp(AddThis);
	const CBigDouble& output=left+tmp;
	return output;
}

CBigDouble operator + (const CBigDouble& left,const string& AddThis) 
{
	/**Makes a new instance of CBigDouble(Parameter 2) and then work exactly like operator+ (const CBigDouble &, const CBigDouble &)*/
	CBigDouble tmp(AddThis);
	const CBigDouble& output=left+tmp;
	return output;
}

// Output operator
ostream& operator << (ostream& os, const CBigDouble& cbi)
{
	/**Parameter 1 is stream where the currant value will be printed\n
	*Parameter 2 is value which has to be printed*/
	if(cbi.minus)
		os << '-';
	os << cbi.leftvalue << ',' << cbi.rightvalue;
	return os;
}

// Other mathematical operators
CBigDouble& CBigDouble::operator += (const string& add){
/** returns *this+Parameter*/
	*this=*this+add;
	return *this;
}

CBigDouble& CBigDouble::operator += (const int& add){
/** returns *this+Parameter*/
	*this=*this+add;
	return *this;
}

CBigDouble& CBigDouble::operator += (const CBigDouble& add){
/** returns *this+Parameter*/
	*this=*this+add;
	return *this;
}

CBigDouble& CBigDouble::operator *= (const string& add){
/** returns *this*Parameter*/
	*this=*this*add;
	return *this;
}

CBigDouble& CBigDouble::operator *= (const int& add){
/** returns *this*Parameter*/
	*this=*this*add;
	return *this;
}

CBigDouble& CBigDouble::operator *= (const CBigDouble& add){
/** returns *this*Parameter*/
	*this=*this*add;
	return *this;
}
