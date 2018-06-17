#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */


class CTaxRegister
 {
	#define zero -998745918
   	public: // ---------------------------------------------------------------------------------
	// Konstruktor + dekonstruktor
         CTaxRegister ( void ) {N=0;DIV="r|d";};
        ~CTaxRegister ( void ) {};

	// Narozani
    bool Birth        ( const string    & name,
                        const string    & addr,
						const string	& account ){
		// Kontrola Accountu
		vector<infoStruct>::iterator it=info.begin();
		for(it=info.begin();it!=info.end();++it)
			if(it->m_acc==account)
				return false;
		// Hledani pozice pro prirazeni
		int pos=findAddOnly(name,addr);	
		if(pos>=0)
			return false;	
		N++;
		if(pos==zero)
			pos=0;
		else
			pos=pos*(-1);
		infoStruct tmp(name,addr,account);
		info.insert(info.begin()+pos,tmp);
		/*int i=N-1;
		while(i>0)
		{
			if((info[i].m_name+info[i].m_res)<(info[i-1].m_name+info[i-1].m_res))
			{
				swap(info[i],info[i-1]);
				i--;
			}
			else
			{
				break;
			}
		}*/
		//cout << "ADDING --------- " << name << addr <<endl;
		//for(it=info.begin();it!=info.end();++it)
		//	cout << it->m_both << endl;
		return true;
	};
	// Umrti
    bool Death        ( const string    & name,
                        const string    & addr ){
		//vector<infoStruct>::iterator it=info.begin();
		//if(it==info.end())
		//	return false;
		int pos=find(name,addr);
		if(pos==-1)
			return false;
		N--;
		info.erase(info.begin()+pos);
		//cout << "ERASING --------- " << name << addr <<endl;
		//for(it=info.begin();it!=info.end();++it)
		//	cout << it->m_both << endl;
		return true;
	};
	// Prijem
    bool Income       ( const string    & name,
                        const string    & addr,
                        int               amount ){
		//vector<infoStruct>::iterator it=find_if(info.begin(),info.end(),FindInVector(name,addr));
		//if(it==info.end())
		//	return false;
		int pos=find(name,addr);
		if(pos==-1)
			return false;
		info[pos].m_inc+=amount;
		return true;
	};
    bool Income       ( const string    & acc,
                        int               amount ){
		vector<infoStruct>::iterator it=info.begin();
		for(it=info.begin();it!=info.end();++it)
			if(it->m_acc==acc)
				break;
		if(it==info.end())
			return false;
		it->m_inc+=amount;
		return true;
	};
	// Vydaje
    bool Expense      ( const string    & name,
                        const string    & addr,
                        int               amount ){
		//vector<infoStruct>::iterator it=find_if(info.begin(),info.end(),FindInVector(name,addr));
		//if(it==info.end())
		//	return false;
		int pos=find(name,addr);
		if(pos==-1)
			return false;
		info[pos].m_exp+=amount;
		return true;
 	};
    bool Expense      ( const string    & acc,
                        int               amount ){
		vector<infoStruct>::iterator it=info.begin();
		for(it=info.begin();it!=info.end();++it)
			if(it->m_acc==acc)
				break;
		if(it==info.end())
			return false;
		it->m_exp+=amount;
		return true;
 	};
	// Zjisteni informaci
    bool Audit        ( const string    & name,
                        const string    & addr,
						string			& account,
                        int             & sumIncome,
                        int             & sumExpense )const{
		//vector<infoStruct>::iterator it=find_if(info.begin(),info.end(),FindInVector(name,addr));
		//vector<infoStruct>::iterator it=info.begin();
		//if(it==info.end())
		//	return false;
		int pos=find(name,addr);
		if(pos==-1)
			return false;
		sumIncome=info[pos].m_inc;
		sumExpense=info[pos].m_exp;
		account=info[pos].m_acc;
		return true;
 	};
	private: // --------------------------------------------------------------------------------
	// Struktura pro ukladani informaci	
	struct infoStruct{
		infoStruct(const string & name,const string & res,const string & account) {
			m_both=name+"r|d"+res;
			m_acc=account;
			m_inc=0;
			m_exp=0;
		};
		string m_both;
		string m_acc;
		int m_inc;
		int m_exp;
	};
	// Struktura pro hledani ve vektoru struktur
	/*struct FindInVector{
	    string name;
		string residence;
	    FindInVector(const string &a, const string &b) {
			name=a;
			residence=b;
		};
	    bool operator()(const infoStruct& stc) const { 
	        return ((stc.m_name == name)&&(stc.m_res == residence)); 
    	}
	};*/
	// Vektor struktur
	vector<infoStruct> info;
	int N;
	string DIV; // Oddelovatko :D
	int findAddOnly(const string &name, const string &residence) const{
		if(N==0)
			return(zero);
		int i=N-1;
		int Loffset=0;
		int Roffset=N-1;
		string findname=name+"r|d"+residence;
		//if((name+residence)>(info[i].m_name+info[i].m_res))
		//	return(-N);
		// Najde to priblizne
		while(Loffset!=Roffset)
		{
			i=((Roffset-Loffset)/2)+Loffset;
			if(Loffset==(Roffset-1))
				break;
			if(findname<info[i].m_both)
				Roffset=i;
			else
				Loffset=i;
		}
		// Dokonceni hledani
		if(findname==info[i].m_both)
			return i;

		if(findname>info[i].m_both)
		{
			if(i==Roffset)
				return(-i-1);
			if(findname==info[Roffset].m_both)
				return(Roffset);
			else
			{
				if(findname>info[Roffset].m_both)
				return(-Roffset-1);
			}
			return(-i-1);
		}
		else
		{

			if(i==Loffset)
			{
				if(i==0)
					return(zero);
				else
					return(-i);
			}
			if(findname==info[Loffset].m_both)
				return(Loffset);
			else
			{
				if(findname<info[Loffset].m_both)
				{
					if(Loffset==0)
						return(zero);
					else
						return(-Loffset);
				}
			}
				if(i==0)
					return(zero);
				else
					return(-i);
		}
	};
	
	int find(const string &name, const string &residence) const{
		if(N==0)
			return(-1);
		int i=N-1;
		int Loffset=0;
		int Roffset=N-1;
		string findname=name+"r|d"+residence;
		//if((name+residence)>(info[i].m_name+info[i].m_res))
		//	return(-N);
		// Najde to priblizne
		while((Roffset-Loffset)>1)
		{
			i=((Roffset-Loffset)/2)+Loffset;
			if(findname<info[i].m_both)
				Roffset=i;
			else
				Loffset=i;
		}
		// Dokonceni hledani
		if(findname==info[Loffset].m_both)
			return(Loffset);
		if(findname==info[Roffset].m_both)
			return(Roffset);
		return(-1);
	};
 };


