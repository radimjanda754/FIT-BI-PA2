#ifndef __PROGTEST__ // !! DO NOT remove
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>
#include <set>
#include <list>
#include <algorithm>
using namespace std;
//=================================================================================================
class CTimeStamp
{
	public:
		CTimeStamp                             ( int               year,
		                                         int               month,
		                                         int               day,
		                                         int               hour,
		                                         int               minute,
		                                         int               sec )
			: Y(year),Mo(month),D(day),H(hour),Mi(minute),S(sec) {};
	
	int            Compare                     ( const CTimeStamp & x ) const
	{
		if(Y==x.Y)
		{
			if(Mo==x.Mo)
			{
				if(D==x.D)
				{
					if(H==x.H)
					{
						if(Mi==x.Mi)
						{
							if(S==x.S)
								return 0;
							if(S<x.S)
								return -1;
							else
								return 1;
						}
						if(Mi<x.Mi)
							return -1;
						else
							return 1;
					}
					if(H<x.H)
						return -1;
					else
						return 1;
				}
				if(D<x.D)
					return -1;
				else
					return 1;
			}
			if(Mo<x.Mo)
				return -1;
			else
				return 1;
		}
		if(Y<x.Y)
			return -1;
		else
			return 1;
	};
	friend ostream & operator <<             ( ostream          & os,
		                                         const CTimeStamp & x )
	{
		return os << x.Y << '-' << x.Mo << '-' << x.D << ' ' << x.H << ':' << x.Mi << ':' << x.S;
	};
	private:
	int Y;
	int Mo;
	int D;
	int H;
	int Mi;
	int S;
};
//=================================================================================================
class CMailBody
{
	public:
	  	CMailBody                               ( int               size,
			                                     const char      * data )
			: m_Size(size) {};
		~CMailBody() {};
	// copy cons/op=/destructor implemented in the class
	friend ostream & operator <<             ( ostream         & os,
			                                     const CMailBody & x )
	{
		return os << "mail body: " << x . m_Size << " B";
	}
	private:
	int            m_Size;
};
//=================================================================================================
class CAttach
{
	public:
	   CAttach                                 ( int               x )
		: m_X (x), m_RefCnt ( 1 ) { }
	void           AddRef                                  ( void ) const { m_RefCnt ++;}
	void           Release                                 ( void ) const { if ( !--m_RefCnt ) delete this; }
	
	int            m_X;
	mutable int    m_RefCnt;
	   CAttach                                 ( const CAttach   & x );
	CAttach      & operator =                 ( const CAttach   & x );
	  ~CAttach                                 ( void ) { }
	friend ostream & operator <<             ( ostream         & os,
		                                         const CAttach   & x )
	{
		return os << "attachment: " << x . m_X << " B";
	}
};
//=================================================================================================
#endif /* __PROGTEST__, DO NOT remove */

class CMail
{
	public:
		CMail						( const CTimeStamp & timeStamp,
		                              const string     & from,
		                              const CMailBody  & body,
		                              const CAttach    * attach )
	: m_time(timeStamp), m_body(body), m_from(from), m_attach(attach)
	{
		if (m_attach)
		{	
			//cout << "Adding ref to: " << m_attach->m_X << endl;	
			m_attach->AddRef();
			
			//cout << "-> now has " << m_attach->m_RefCnt << " refs" << endl;
		}
	};
		CMail						( const CMail & x )
	: m_time(x.TimeStamp()), m_body(x.Body()), m_from(x.From()), m_attach(x.m_attach)
	{
		if (m_attach)
		{		
			//cout << "CopyAdding ref to: " << m_attach->m_X << endl;	
			m_attach->AddRef();
			m_attach->AddRef();
			//cout << "-> now has " << m_attach->m_RefCnt << " refs" << endl;
		}
	};
		~CMail() 
	{
		if (m_attach)
		{
			//cout << "Removing ref from: " << m_attach->m_X << " which had " << m_attach->m_RefCnt << " refs" << endl;	
			m_attach->Release();
			//cout << "-> now has " << m_attach->m_RefCnt << " refs" << endl;
		}	
	};
	const string     & From                                ( void ) const {return m_from;};
	const CMailBody  & Body                                ( void ) const {return m_body;};
	const CTimeStamp & TimeStamp                           ( void ) const {return m_time;};
	const CAttach* Attachment                              ( void ) const {return m_attach;};

	friend ostream & operator << ( ostream          & os,
		                             const CMail      & x )
	{
		os << x.TimeStamp() << ' ' << x.From() << ' ' << x.Body();
		if(x.m_attach)
			os << " + " << *(x.Attachment());
		return os;
	};
	private:
	CTimeStamp m_time;
	CMailBody m_body;
	string m_from;
	const CAttach * m_attach;
};
//=================================================================================================
class CMailBox
{
	public:
				   CMailBox                                ( void )	{};
	bool           Delivery                                ( const CMail      & mail )
	{
		//const CMail * mailpoint=&mail;
		vector<CMail>::iterator it=lower_bound(inbox.m_Mails.begin(),inbox.m_Mails.end(),mail,CompareMails());
		inbox.m_Mails.insert(it,mail);
		//cout << endl << "ADDING : " << mail << endl;
		//for (it=inbox.m_Mails.begin();it!=inbox.m_Mails.end();++it)
		//	cout << *it << endl;
		return true;
	};
	bool           NewFolder                               ( const string     & folderName )
	{
		vector<TFolder>::iterator it=lower_bound(folders.begin(),folders.end(),folderName,CompareFolders());
		// Kontrola zda adresar jiz nahodou neexistuje
		if(folderName=="inbox")
			return false;		
		if(it!=folders.end())
			if(it->m_FolderName==folderName)
				return false;
		// Vlozeni adresare do vektoru
		TFolder tmp(folderName);
		folders.insert(it,tmp);
		// Vse bylo OK
		return true;
	};
	bool           MoveMail                                ( const string     & fromFolder,
			                                                 const string     & toFolder )
	{
		if(fromFolder==toFolder)
			return true;
		vector<TFolder>::iterator from;
		vector<TFolder>::iterator to;
		TFolder * frompoint;
		TFolder * topoint;
		// Vyhledani adresaru
		if(fromFolder=="inbox")
		{
			frompoint=&inbox;
		}
		else
		{
			from=lower_bound(folders.begin(),folders.end(),fromFolder,CompareFolders());
			if(from==folders.end())
				return false;
			if(from->m_FolderName!=fromFolder)
				return false;
			frompoint=&(*from);
		}

		if(toFolder=="inbox")
		{
			topoint=&inbox;
		}		
		else
		{
			to=lower_bound(folders.begin(),folders.end(),toFolder,CompareFolders());
			if(to==folders.end())
				return false;
			if(to->m_FolderName!=toFolder)
				return false;
			topoint=&(*to);
		}
		// Presun
		//cout << endl << " ------------------------------------ " << endl;
		vector<CMail>::iterator it=frompoint->m_Mails.begin();
		vector<CMail>::iterator itTO=topoint->m_Mails.begin();
		/*for(it=topoint->m_Mails.begin();it!=topoint->m_Mails.end();++it)
		{
			cout << '-' << *it << endl;
		}*/
		for(it=frompoint->m_Mails.begin();it!=frompoint->m_Mails.end();++it)
		{
			itTO=lower_bound(topoint->m_Mails.begin(),topoint->m_Mails.end(),it->TimeStamp(),CompareMails());
			/*if(itTO!=topoint->m_Mails.end())
			{
				cout << "ADDING: " << *it << endl;
				cout << "BEFORE: " << *itTO << endl;
			}
			else
			{
				cout << "UNKNOWN: " << *it << endl;
			}*/

			topoint->m_Mails.insert(itTO,*it);
		}
		frompoint->m_Mails.erase(frompoint->m_Mails.begin(),frompoint->m_Mails.end());
		return true;
	};
	list<CMail>    ListMail                                ( const string     & folderName,
		                     	                       	     const CTimeStamp & from,
		                          	         		   	    const CTimeStamp & to )
	{
		list<CMail> output;	
		vector<TFolder>::iterator folderit;
		TFolder * folderpoint;
		// Vyhledani adresare
		if(folderName=="inbox")
		{
			folderpoint=&inbox;
		}
		else
		{
			folderit=lower_bound(folders.begin(),folders.end(),folderName,CompareFolders());
			if(folderit==folders.end())
			{
				return output;
			}
			if(folderit->m_FolderName!=folderName)
			{
				return output;
			}
			folderpoint=&(*folderit);
		}
		// Vkladani do listu
		vector<CMail>::iterator itB=lower_bound(folderpoint->m_Mails.begin(),folderpoint->m_Mails.end(),from,CompareMails());
		vector<CMail>::iterator itU=upper_bound(folderpoint->m_Mails.begin(),folderpoint->m_Mails.end(),to,CompareMails());
		output.insert(output.begin(),itB,itU);
		return output;
	};
	set<string>    ListAddr                                ( const CTimeStamp & from,
			                                  	           const CTimeStamp & to )
	{
		set<string> output;
		// Prohledani inboxu
		vector<CMail>::iterator itB=lower_bound(inbox.m_Mails.begin(),inbox.m_Mails.end(),from,CompareMails());
		while(itB!=inbox.m_Mails.end())
		{
			if(itB->TimeStamp().Compare(to)<=0)
				output.insert(itB->From());
			else
				break;
			itB++;
		}
		// Prohledani ostatnich slozek
		vector<TFolder>::iterator itF;
		for(itF=folders.begin();itF!=folders.end();++itF)
		{
			itB=lower_bound(itF->m_Mails.begin(),itF->m_Mails.end(),from,CompareMails());
			while(itB!=itF->m_Mails.end())
			{
				if(itB->TimeStamp().Compare(to)<=0)
					output.insert(itB->From());
				else
					break;
				itB++;
			}
		}
		return output;
	};
	private:
	// Struktura adresaru
	struct TFolder{
		TFolder(void) {};
		TFolder(const string & name)
		{
			m_FolderName=name;
		};
		string m_FolderName;
		vector<CMail> m_Mails;
	};
	// Struktura pro hledani lower_bound
	struct CompareFolders{
		bool operator() (const TFolder & left, const TFolder & right)
		{
			return left.m_FolderName < right.m_FolderName;
		}
		bool operator() (const string & left, const TFolder & right)
		{
			return left < right.m_FolderName;
		}
		bool operator() (const TFolder & left, const string & right)
		{
			return left.m_FolderName < right;
		}
	};
	struct CompareMails{
		bool operator() (const CMail & left, const CMail & right)
		{
			return left.TimeStamp().Compare(right.TimeStamp()) < 0;
		}
		bool operator() (const CTimeStamp & left, const CMail & right)
		{
			return left.Compare(right.TimeStamp()) < 0;
		}
		bool operator() (const CMail & left, const CTimeStamp & right)
		{
			return left.TimeStamp().Compare(right) < 0;
		}
	};
	// Adresare a inbox
	vector<TFolder> folders;
	TFolder inbox;
};
//=================================================================================================

#ifndef __PROGTEST__ /* DO NOT remove */
void showMail ( const list<CMail> & l )
 {
	//cout << "---8<---8<---8<---8<---8<---8<---" << endl;
   for ( list<CMail>::const_iterator it = l . begin (); it != l . end (); ++it )
   	cout << *it << endl;
	//cout << "---8<---8<---8<---8<---8<---8<---" << endl;
 }
void showUsers ( const set<string> & s )
 {
	//cout << "---8<---8<---8<---8<---8<---8<---" << endl;
   for ( set<string>::const_iterator it = s . begin (); it != s . end (); ++it )
    cout << *it << endl;
	//cout << "---8<---8<---8<---8<---8<---8<---" << endl;
 }


#endif /* __PROGTEST__, DO NOT remove */
