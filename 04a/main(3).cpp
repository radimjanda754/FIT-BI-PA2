#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
#endif /* __PROGTEST__ */

// STRUKTURA PRO TRANSQUEUE---------------------------------------------------------
	struct TTransNode{
		TTransNode(const char * & OID, int & Osize, const char * & sign, int & signsize, int & value, bool & dir) {
			m_OIDsize=Osize;
			m_SIGsize=signsize;
			m_OtherID=new char[m_OIDsize];
			strncpy(m_OtherID,OID,m_OIDsize);
			m_sign=new char[m_SIGsize];
			strncpy(m_sign,sign,m_SIGsize);	
			m_value=value;			
			m_dir=dir;
			m_next=NULL;		
		};
		TTransNode(const TTransNode & copy) {
			m_OIDsize=copy.m_OIDsize;
			m_SIGsize=copy.m_SIGsize;
			m_OtherID=new char[m_OIDsize];
			strncpy(m_OtherID,copy.m_OtherID,m_OIDsize);
			m_sign=new char[m_SIGsize];
			strncpy(m_sign,copy.m_sign,m_SIGsize);	
			m_value=copy.m_value;			
			m_dir=copy.m_dir;
			m_next=NULL;		
		};
		~TTransNode() {
			delete[] m_OtherID;
			delete[] m_sign;
		};
		char * m_OtherID;
		int m_OIDsize;
		char * m_sign;
		int m_SIGsize;
		int m_value;
		bool m_dir; // 0=from , 1=to 
		TTransNode * m_next;
	};
// 1111111111111111111111111111111111111111111111111111111111111111111111111111111111
// Fronta pro transakci (vnitrni fronta) --------------------------------------------
class CTransQueue{
public:
	CTransQueue(char * & ID,int & bal){TOP=NULL;END=NULL;ThisID=ID;initBal=&bal;};
	CTransQueue(const CTransQueue & copy,int & bal, char * & ID){
		initBal=&bal;
		ThisID=ID;
		if(!copy.TOP)
		{
			TOP=NULL;END=NULL;
		}
		else
		{
			TTransNode * move=copy.TOP;
			TOP=new TTransNode(*copy.TOP);
			END=TOP;
			TTransNode * tmp;
			move=move->m_next;
			while(move!=NULL)
			{
				tmp=new TTransNode(*move);
				END->m_next=tmp;
				END=tmp;
				move=move->m_next;
			}

		}
	};
	~CTransQueue(){
		TTransNode * move = TOP;
		while (move!=NULL)
		{
			TTransNode * delthis=move;
			move=move->m_next;
			delete delthis;
		}
	};
	bool addTransaction(const char * & OID,const char * & SIG,int & val,bool dir,int OIDsize){
		// Vypocitani delky retezce (+1 for some reason, ale bez toho to segfaultne :D)
		int SIGsize=0;
		while(SIG[SIGsize])
			SIGsize++;
		SIGsize++;
		// Fronta je prazdna
		if(TOP==NULL)
		{
			// Pridani na zacatek fronty
			TTransNode * tmp= new TTransNode(OID,OIDsize,SIG,SIGsize,val,dir);
			TOP=tmp;
			END=tmp;
			return true;
		} // Fronta neni prazdna
		else
		{
			// Pridani na konec fronty
			TTransNode * tmp= new TTransNode(OID,OIDsize,SIG,SIGsize,val,dir);
			END->m_next=tmp;
			END=tmp;
			return true;
		}
		return false;
	};
	int Balance()
	{
		int initial=*initBal;
		TTransNode * move = TOP;
		while (move!=NULL)
		{
			if(move->m_dir)
			{
				initial=initial+move->m_value;
			}
			else
			{
				initial=initial-move->m_value;
			}
			move=move->m_next;
		}
		return initial;
	};
	void TrimItBro()
	{
		int initial=*initBal;
		TTransNode * move = TOP;
		TTransNode * delthis = move;
		while (move!=NULL)
		{
			if(move->m_dir)
			{
				initial=initial+move->m_value;
			}
			else
			{
				initial=initial-move->m_value;
			}
			delthis=move;
			move=move->m_next;
			delete delthis;
			delthis=NULL;
		}
		TOP=NULL;
		END=NULL;
		*initBal=initial;
	};
	friend ostream& operator << (ostream& os, const CTransQueue & cbk);
private:
	TTransNode * TOP;
	TTransNode * END;
	const char * ThisID;
	int * initBal;
};


// 22222222222222222222222222222222222222222222222222222222222222222222222222222222222
// Fronta pro ukladani uctu, init balance atp (vnejsi fronta) ------------------------
class CQueue{
public:
	CQueue(){TOP=NULL;n=1;};	
	CQueue(const CQueue & copy){
		n=1;
		if(copy.TOP==NULL)
		{
			TOP=NULL;
		}
		else
		{
			TNode * move=copy.TOP;
			TOP=new TNode(*copy.TOP);
			TNode * thismove=TOP;
			TNode * tmp;
			move=move->m_next;
			while(move!=NULL)
			{
				tmp=new TNode(*move);
				thismove->m_next=tmp;
				thismove=tmp;
				move=move->m_next;
			}
		}
	};
	~CQueue(){
		TNode * move = TOP;
		while (move!=NULL)
		{
			TNode * delthis=move;
			move=move->m_next;
			if(delthis->trans)
				delete delthis->trans;
			delete delthis;
		}
	};
	bool add(const char * & ID,int & Bal){
		// Vypocitani delky retezce (+1 for some reason, ale bez toho to segfaultne :D)
		int size=0;
		while(ID[size])
			size++;
		size++;
		// Fronta je prazdna
		if(TOP==NULL)
		{
			TNode * tmp= new TNode(ID,Bal,size);
			TOP=tmp;
			return true;
		} // Fronta neni prazdna
		else
		{
			// Linearni zkontrolovani zda-li se jiz ID nenachazi ve fronte
			TNode * move=TOP;
			TNode * prevmove=move;
			while (move!=NULL)
			{
				if(size==move->m_size)
				{
					if(!strncmp(ID,move->m_ID,size))
						return false;
				}
				prevmove=move;
				move=move->m_next;
			}
			// Pridani na konec
			TNode * tmp= new TNode(ID,Bal,size);
			prevmove->m_next=tmp;
			return true;
		}
		return false;
	};
	bool addTrans(const char * & debID, int & debsize, const char * & credID, int & credsize, const char * & sign, int & value)
	{
		TNode * move = TOP;
		TNode * deb=NULL;
		TNode * cred=NULL;
		// Hledani tech uctu
		while ((move!=NULL)&&((deb==NULL)||(cred==NULL)))
		{
			if(debsize==move->m_size)
			{
				if(!strncmp(debID,move->m_ID,debsize))
					deb=move;
			}
			if(credsize==move->m_size)
			{
				if(!strncmp(credID,move->m_ID,credsize))
					cred=move;
			}
			move=move->m_next;
		}
		// Pokud oba ucty byli nalezeny, zapis do nich transakce
		if((deb!=NULL)&&(cred!=NULL))
		{
			// Pridani pro debitovany ucet
			if(!deb->trans)
				deb->trans=new CTransQueue(deb->m_ID,deb->m_initBal);
			deb->trans->addTransaction(credID,sign,value,0,credsize);
			//cout << deb->m_ID << ":" << endl;
			//deb->trans->printTransactions(deb->m_initBal);
			// Pridani pro kreditovany ucet
			if(!cred->trans)
				cred->trans=new CTransQueue(cred->m_ID,cred->m_initBal);
			cred->trans->addTransaction(debID,sign,value,1,debsize);
			//cout << cred->m_ID << ":" << endl;
			//cred->trans->printTransactions(cred->m_initBal);

			return true;
		}
		return false;
	};
	bool Trim (const char * & ID, int & size)
	{
		TNode * move=TOP;
		while(move!=NULL)
		{
			if(size==move->m_size)
			{
				if(!strncmp(ID,move->m_ID,size))
				{
					if(!move->trans)
						return true;
					move->trans->TrimItBro();
					return true;
				}
			}
			move=move->m_next;
		}
		return false;
	};
	CTransQueue * FindTQueue(const char * & ID, int & size)
	{
		TNode * move=TOP;
		while(move!=NULL)
		{
			if(size==move->m_size)
			{
				if(!strncmp(ID,move->m_ID,size))
					return move->trans;
			}
			move=move->m_next;
		}
		return NULL;
	};
	int n;
private:
	// STRUNTURA UCTU -----
	struct TNode{
		TNode(const char * & ID, int & initBal, int & size) {
			m_size=size;	
			m_ID=new char[m_size];
			strncpy(m_ID,ID,m_size);
			m_initBal=initBal;	
			m_next=NULL;	
			trans=NULL;	
		};
		TNode(const TNode & copy)
		{
			m_size=copy.m_size;
			m_ID=new char[m_size];
			strncpy(m_ID,copy.m_ID,m_size);
			m_initBal=copy.m_initBal;
			m_next=NULL;
			if(copy.trans==NULL)
			{
				trans=NULL;
			}
			else
			{
				trans=new CTransQueue(*copy.trans,m_initBal,m_ID);
			}
		}
		~TNode() {
			delete[] m_ID;
		};
		int m_size;
		TNode * m_next;
		char * m_ID;
		int m_initBal;
		CTransQueue * trans;
	};
	TNode * TOP;
};

// 333333333333333333333333333333333333333333333333333333333333333333
// CBank ------------------------------------------------------------
class CBank{
public:
	CBank() {accs=new CQueue();};
    // default constructor
    // copy constructor
    // destructor
    // operator =
	CBank(const CBank& copy) {accs=copy.accs;accs->n++;};
	~CBank(){
		if(accs->n==1)
			delete accs;
		else
			accs->n--;
	};
	bool	NewAccount	( const char	* accID,
                       	int      		initialBalance ){
		if(accs->n>1)
		{
			accs->n--;
			CQueue * tmp=accs;
			accs=new CQueue(*tmp);
		}
		return accs->add(accID,initialBalance);
	};

    bool	Transaction	( const char	* debAccID,
                     	const char		* credAccID,
                      	int				amount,
                     	const char		* signature ){
		if(accs->n>1)
		{
			accs->n--;
			CQueue * tmp=accs;
			accs=new CQueue(*tmp);
		}
		int debsize=0;
		while(debAccID[debsize])
			debsize++;
		debsize++;
		int credsize=0;
		while(credAccID[credsize])
			credsize++;
		credsize++;
		if(debsize==credsize)
		{
			if(!strncmp(debAccID,credAccID,debsize))
				return false;
		}
		return accs->addTrans(debAccID,debsize,credAccID,credsize,signature,amount);
	};
    bool  	TrimAccount	( const char	* accID )
	{
		if(accs->n>1)
		{
			accs->n--;
			CQueue * tmp=accs;
			accs=new CQueue(*tmp);
		}
		int size=0;
		while(accID[size])
			size++;
		size++;
		return accs->Trim(accID,size);
	};
	CTransQueue & Account (const char * accID)
	{
		int size=0;
		while(accID[size])
			size++;
		size++;
		CTransQueue * tmp = accs->FindTQueue(accID,size);
		if(!tmp)
			throw "Not found";
		
		return *tmp;
	};
	CBank & operator = (const CBank & copy)
	{
		if(accs->n==1)
			delete accs;
		else
			accs->n--;
		accs=copy.accs;
		accs->n++;
		return *this;
	}
    // Account ( accID )
private:
	CQueue * accs;
	CQueue ** pointr;
    // todo
};


// 444444444444444444444444444444444444444444444444444444444444444444444444444
// DALSI ----------------------------------------------------------------------
ostream& operator << (ostream& os, const CTransQueue & cbk)
{
	int finalbal=*cbk.initBal;
	os << cbk.ThisID << ':' << endl;
	os << "   " << *cbk.initBal << endl;
	TTransNode * move = cbk.TOP;
	while (move!=NULL)
	{
		if(move->m_dir)
		{
			os << " + ";
			finalbal=finalbal+move->m_value;
		}
		else
		{
			os << " - ";
			finalbal=finalbal-move->m_value;
		}
		os << move->m_value << ", ";
		if(move->m_dir)
			os << "from: ";
		else
			os << "to: ";
		os << move->m_OtherID << ", " << "sign: " << move->m_sign << endl;
		move=move->m_next;
	}
	os << " = " << finalbal << endl;
	return os;
}

















