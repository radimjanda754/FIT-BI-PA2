#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void RemoveZeroes(string& fromthis);
class CBigInt
{
public:
	CBigInt ( void ) {
		value="0";
	};
	CBigInt ( const int IntValue ) {
		stringstream ss;
		ss << IntValue;
		value=ss.str();
	};
	CBigInt ( const string StrValue ) {
		value=StrValue;
		RemoveZeroes(value);
	};
	~CBigInt (void) { };

	CBigInt& operator = (const string add) {
		value=add;
		RemoveZeroes(value);
		return *this;
	}
	CBigInt& operator = (const CBigInt& add) {
		value=add.value;
		RemoveZeroes(value);
		return *this;
	}
	CBigInt& operator = (const int IntValue) {
		stringstream ss;
		ss << IntValue;
		value=ss.str();
		return *this;
	}
	friend CBigInt operator + (const CBigInt&,const CBigInt&);
	friend CBigInt operator + (const CBigInt&,const string);
	friend CBigInt operator + (const CBigInt&,const int);
	friend CBigInt operator * (const CBigInt&,const CBigInt&);
	friend CBigInt operator * (const CBigInt&,const string);
	friend CBigInt operator * (const CBigInt&,const int);
	friend ostream& operator << (ostream& os, const CBigInt&);
	friend istream& operator >> (istream& is, CBigInt&);
	CBigInt& operator += (const string add);
	CBigInt& operator += (const int add);
	CBigInt& operator += (const CBigInt& add);
	CBigInt& operator *= (const string add);
	CBigInt& operator *= (const int add);
	CBigInt& operator *= (const CBigInt& add);
private:
	string value;
};

// DEFINICE OPERATORU ------------------------------------------------
void RemoveZeroes(string& fromthis)
{
	int it=0;
	while(fromthis[it]=='0'||fromthis[it]=='-')
	{
		if(fromthis[it]=='0')
		{
			fromthis.erase(fromthis.begin()+it);
			continue;
		}
		it++;				
	}
	if(fromthis.empty())
	{
		fromthis.clear();
		fromthis="0";
	}
	else
	{
		if(fromthis.length()==1&&fromthis[0]=='-')
		{
			fromthis.clear();
			fromthis="0";
		}
	}
}

CBigInt operator + (const CBigInt& leftA,const CBigInt& rightB) 
{
	CBigInt left(leftA.value);
	CBigInt right(rightB.value);
	RemoveZeroes(left.value);
	RemoveZeroes(right.value);
	// Deklarace promenych
	bool lminus=0;
	bool rminus=0;
	bool minusoutput=0;
	int minuses=0;
	int trans=0;
	int add=0;
	string tmp;
	CBigInt* upper;
	CBigInt* bottom;
	// Zjisteni jak sme na tom s minusama
	if(left.value[0]=='-')
	{
		left.value.erase(left.value.begin());
		minuses++;
		lminus=1;
	}
	if(right.value[0]=='-')
	{
		right.value.erase(right.value.begin());
		rminus=1;
		minuses++;
	}
	int lindex=left.value.length()-1;
	int rindex=right.value.length()-1;

	//Pokud budeme odecitat ---------------------------------------------------
	if(minuses==1)
	{
		if(lindex>rindex)
		{
			upper=&left;
			bottom=&right;
			if(lminus)
				minusoutput=1;
		}
		if(rindex>lindex)
		{
			upper=&right;
			bottom=&left;
			if(rminus)
				minusoutput=1;
		}
		if(lindex==rindex)
		{
			bool UndBset=0;
			for(int i=0;i<=lindex;i++)
			{
				if(left.value[i]>right.value[i])
				{
					UndBset=1;
				 	upper=&left;
					bottom=&right;
					if(lminus)
						minusoutput=1;
					break;
				}
				if(left.value[i]<right.value[i])
				{
					UndBset=1;
				 	upper=&right;
					bottom=&left;
					if(rminus)
						minusoutput=1;
					break;
				}
			}
			if(!UndBset)
			{
				CBigInt returnzis;
				return returnzis;
			}
		}
		int uindex=upper->value.length()-1;
		int bindex=bottom->value.length()-1;
		for(int i=0;i<=bindex;i++)
		{
			int upint=(int)(upper->value[uindex-i]-'0');
			int botint=(trans+(int)(bottom->value[bindex-i]-'0'));
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
			int upint=(int)(upper->value[uindex-i]-'0');
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
		if(minusoutput)
			tmp.insert(tmp.begin(),'-');
		if(lminus==1)
			left.value.insert(left.value.begin(),'-');
		if(rminus==1)
			right.value.insert(right.value.begin(),'-');
			RemoveZeroes(tmp);
		CBigInt output(tmp);
		return output;
	}

	//Pokud sou oba ++ nebo oba -- -----------------------------------------------------
	if(lindex>rindex) // Pokud leve cislo ma vice cifer
	{
		for(int i=0;i<=lindex;i++) // Pojede se podle leveho cisla
		{
			if(i>rindex) // Pokud nezbivaji zadne dalsi znaky z praveho cisla
			{
				add=trans+(int)(left.value[lindex-i]-'0');
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
				add=trans+(int)(left.value[lindex-i]-'0')+(int)(right.value[rindex-i]-'0');
				if(add>=10)
				{
					tmp.insert(tmp.begin(),(char)('0'+(add-10)));
					//cout << "[2:" << add-10 << ']';
					trans=1;
				}
				else
				{
					tmp.insert(tmp.begin(),(char)('0'+add));
					//cout << "[3:" << add << ']';
					trans=0;
				}
			}
		}
		if(trans==1)
			tmp.insert(tmp.begin(),'1');
	}
	else // Pokud prave cislo ma vice cifer --------------------------------------------------
	{
		for(int i=0;i<=rindex;i++) // Jed podle praveho cisla
		{
			if(i>lindex) // Pokud nezbivaji zadne dalsi znaky z leveho cisla
			{
				add=trans+(int)(right.value[rindex-i]-'0');
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
				add=trans+(int)(left.value[lindex-i]-'0')+(int)(right.value[rindex-i]-'0');
				if(add>=10)
				{
					tmp.insert(tmp.begin(),(char)('0'+(add-10)));
					//cout << "[2:" << add-10 << ']';
					trans=1;
				}
				else
				{
					tmp.insert(tmp.begin(),(char)('0'+add));
					//cout << "[3:" << add << ']';
					trans=0;
				}
			}
		}
		if(trans==1)
			tmp.insert(tmp.begin(),'1');
	}
	CBigInt output(tmp);
	if(lminus==1)
		left.value.insert(left.value.begin(),'-');
	if(rminus==1)
		right.value.insert(right.value.begin(),'-');
	if(minuses==2)
		output.value.insert(output.value.begin(),'-');
	RemoveZeroes(output.value);
	return output;
}

CBigInt operator * (const CBigInt& leftA,const CBigInt& rightB)
{
	CBigInt left(leftA.value);
	CBigInt right(rightB.value);
	RemoveZeroes(left.value);
	RemoveZeroes(right.value);
	bool lminus=0;
	bool rminus=0;
	int minuses=0;
	if(left.value[0]=='-')
	{
		left.value.erase(left.value.begin());
		minuses++;
		lminus=1;
	}
	if(right.value[0]=='-')
	{
		right.value.erase(right.value.begin());
		rminus=1;
		minuses++;
	}
	int trans=0;
	int add;
	CBigInt output;
	string calcString;
	int lindex=left.value.length()-1;
	int rindex=right.value.length()-1;
	for(int i=0;i<=rindex;i++)
	{
		trans=0;
		calcString.clear();
		for(int i2=0;i2<=lindex;i2++)
		{
			add=trans+(int)(left.value[lindex-i2]-'0')*(int)(right.value[rindex-i]-'0');
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
		//cout << "ADDING STRING: " << calcString << endl;
		output+=calcString;
	}
	if(lminus==1)
		left.value.insert(left.value.begin(),'-');
	if(rminus==1)
		right.value.insert(right.value.begin(),'-');
	if(minuses==1)
		output.value.insert(output.value.begin(),'-');
	RemoveZeroes(output.value);
	return output;
}

CBigInt operator * (const CBigInt& left,const int AddThis) 
{
	CBigInt tmp(AddThis);
	const CBigInt& output=left*tmp;
	return output;
}

CBigInt operator * (const CBigInt& left,const string AddThis) 
{
	CBigInt tmp(AddThis);
	const CBigInt& output=left*tmp;
	return output;
}

CBigInt operator + (const CBigInt& left,const int AddThis) 
{
	CBigInt tmp(AddThis);
	const CBigInt& output=left+tmp;
	return output;
}

CBigInt operator + (const CBigInt& left,const string AddThis) 
{
	CBigInt tmp(AddThis);
	const CBigInt& output=left+tmp;
	return output;
}


ostream& operator << (ostream& os, const CBigInt& cbi)
{
	os << cbi.value;
	return os;
}

istream& operator >> (istream& is, CBigInt& cbi)
{
	char tmpC;
	string tmpString;
	tmpString.clear();
	while(is.get(tmpC))
	{
		if(isdigit(tmpC)||(tmpC=='-'&&tmpString.empty()))
		{
			tmpString+=tmpC;
		}
		else
		{
			if(!tmpString.empty())
				break;
		}
	}
	if(tmpString.empty())
	{
		is.clear();
		is.setstate(ios::failbit);
		return is;
	}
	if(tmpString.length()==1&&tmpString[0]=='-')
	{
		is.clear();
		is.setstate(ios::failbit);
		return is;
	}
	is.clear();
	is.setstate(ios::goodbit);
	RemoveZeroes(tmpString);
	cbi.value=tmpString;
	return is;
}

CBigInt& CBigInt::operator += (const string add){
	*this=*this+add;
	return *this;
}

CBigInt& CBigInt::operator += (const int add){
	*this=*this+add;
	return *this;
}

CBigInt& CBigInt::operator += (const CBigInt& add){
	*this=*this+add;
	return *this;
}

CBigInt& CBigInt::operator *= (const string add){
	*this=*this*add;
	return *this;
}

CBigInt& CBigInt::operator *= (const int add){
	*this=*this*add;
	return *this;
}

CBigInt& CBigInt::operator *= (const CBigInt& add){
	*this=*this*add;
	return *this;
}

// MAIN -------------------------------------------------------







