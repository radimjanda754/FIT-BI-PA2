#ifndef __PROGTEST__
#include <cstring>  
#include <iostream> 
#include <iomanip>  
#include <set>
#include <list>
#include <vector>
#include <map>   
#include <algorithm>
#include <functional>
using namespace std; 
#endif /* __PROGTEST__ */

// --------------------------------------------------------------------------------
// _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY
template <typename _Type, typename _Comparator = less <typename _Type::value_type> >
class CIndex
 {
   public:
// ---------------------------------------------------------------------------------
             CIndex ( const _Type & sequenceToIndex,
                      const _Comparator & comparator = _Comparator () )
: cmp(comparator) , m_data(sequenceToIndex) {};
// ---------------------------------------------------------------------------------
            ~CIndex ( void ) {};
// ---------------------------------------------------------------------------------
    set<int> Search ( const _Type & searchFor ) const	{
		set<int> output;
		int position=0;
		bool ucantdothis=0;
		typename _Type::const_iterator it_data=m_data.begin();
		typename _Type::const_iterator it_search=searchFor.begin();
		typename _Type::const_iterator GoBack=m_data.begin();
		// searchFor je prazdne
		if(it_search==searchFor.end())
		{
			for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
			{
				output.insert(position);
				position++;
			}
			return output;
		}
		// Hledej - HODNE NAIVNI ALGORITMUS xD
		for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
		{
			GoBack=it_data;
			it_search=searchFor.begin();
			while(!ucantdothis)
			{
				if(it_search==searchFor.end())
				{
					output.insert(position);
					break;
				}
				if(it_data==m_data.end())
				{
					ucantdothis=1;
					break;
				}
				if((cmp(*it_data,*it_search))||(cmp(*it_search,*it_data)))
					break;
				++it_data;
				++it_search;
			}
			if(ucantdothis)
				break;
			it_data=GoBack;
			position++;
		}
		return output;
	};
// ---------------------------------------------------------------------------------
   private:
    _Comparator cmp;
	_Type m_data;
 };

// --------------------------------------------------------------------------------
// LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST 
template <typename _Type, typename _Comparator>
class CIndex<list<_Type>,_Comparator>
{
   public:
// ---------------------------------------------------------------------------------
			CIndex ( const list<_Type> & sequenceToIndex,
                     const _Comparator & comparator = _Comparator () )
: cmp(comparator) , m_data(sequenceToIndex) {};
// ---------------------------------------------------------------------------------
		   ~CIndex ( void ) {};
// ---------------------------------------------------------------------------------
	set<int> Search ( const list<_Type> & searchFor ) const	{
		set<int> output;
		int position=0;
		bool ucantdothis=0;
		typename list<_Type>::const_iterator it_data=m_data.begin();
		typename list<_Type>::const_iterator it_search=searchFor.begin();
		typename list<_Type>::const_iterator GoBack=m_data.begin();
		// searchFor je prazdne
		if(it_search==searchFor.end())
		{
			for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
			{
				output.insert(position);
				position++;
			}
			return output;
		}
		// Hledej - HODNE NAIVNI ALGORITMUS xD
		for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
		{
			GoBack=it_data;
			it_search=searchFor.begin();
			while(!ucantdothis)
			{
				if(it_search==searchFor.end())
				{
					output.insert(position);
					break;
				}
				if(it_data==m_data.end())
				{
					ucantdothis=1;
					break;
				}
				if((cmp(*it_data,*it_search))||(cmp(*it_search,*it_data)))
					break;
				++it_data;
				++it_search;
			}
			if(ucantdothis)
				break;
			it_data=GoBack;
			position++;
		}
		return output;
	};
// ---------------------------------------------------------------------------------
   private:
	_Comparator cmp;
    list<_Type> m_data;
};
// --------------------------------------------------------------------------------
// VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR
template <typename _Type, typename _Comparator>
class CIndex<vector<_Type>,_Comparator>
{
   public:
			CIndex ( const vector<_Type> & sequenceToIndex,
                     const _Comparator & comparator = _Comparator () )
: cmp(comparator) , m_data(sequenceToIndex) {};
// ---------------------------------------------------------------------------------
		   ~CIndex ( void ) {};
// ---------------------------------------------------------------------------------
	set<int> Search ( const vector<_Type> & searchFor ) const	{
		set<int> output;
		int position=0;
		bool ucantdothis=0;
		typename vector<_Type>::const_iterator it_data=m_data.begin();
		typename vector<_Type>::const_iterator it_search=searchFor.begin();
		typename vector<_Type>::const_iterator GoBack=m_data.begin();
		// searchFor je prazdne
		if(it_search==searchFor.end())
		{
			for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
			{
				output.insert(position);
				position++;
			}
			return output;
		}
		// Hledej - HODNE NAIVNI ALGORITMUS xD
		for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
		{
			GoBack=it_data;
			it_search=searchFor.begin();
			while(!ucantdothis)
			{
				if(it_search==searchFor.end())
				{
					output.insert(position);
					break;
				}
				if(it_data==m_data.end())
				{
					ucantdothis=1;
					break;
				}
				if((cmp(*it_data,*it_search))||(cmp(*it_search,*it_data)))
					break;
				++it_data;
				++it_search;
			}
			if(ucantdothis)
				break;
			it_data=GoBack;
			position++;
		}
		return output;
	};
// ---------------------------------------------------------------------------------
   private:
	_Comparator cmp;
    vector<_Type> m_data;
};
// --------------------------------------------------------------------------------




// --------------------------------------------------------------------------------
// LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST - LIST 

/*template <typename _Type, typename _Comparator>
CIndex<list<_Type>,_Comparator>::CIndex ( const list<_Type> & sequenceToIndex, const _Comparator & comparator) 
{
	m_data=sequenceToIndex;
	cmp=comparator;
}
// --------------------------------------------------------------------------------
template <typename _Type, typename _Comparator>
CIndex<list<_Type>,_Comparator>::~CIndex (void) { }
// --------------------------------------------------------------------------------
template <typename _Type, typename _Comparator>
set<int> CIndex<list<_Type>,_Comparator>::Search ( const list<_Type> & searchFor ) const
	{
		set<int> output;
		int position=0;
		bool ucantdothis=0;
		typename list<_Type>::const_iterator it_data=m_data.begin();
		typename list<_Type>::const_iterator it_search=searchFor.begin();
		typename list<_Type>::const_iterator GoBack=m_data.begin();
		// searchFor je prazdne
		if(it_search==searchFor.end())
		{
			for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
			{
				output.insert(position);
				position++;
			}
			return output;
		}
		// Hledej - HODNE NAIVNI ALGORITMUS xD
		for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
		{
			GoBack=it_data;
			it_search=searchFor.begin();
			while(!ucantdothis)
			{
				if(it_search==searchFor.end())
				{
					output.insert(position);
					break;
				}
				if(it_data==m_data.end())
				{
					ucantdothis=1;
					break;
				}
				if((cmp(*it_data,*it_search))||(cmp(*it_search,*it_data)))
					break;
				++it_data;
				++it_search;
			}
			if(ucantdothis)
				break;
			it_data=GoBack;
			position++;
		}
		return output;
	}

// --------------------------------------------------------------------------------
// VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR - VECTOR

template <typename _Type, typename _Comparator>
CIndex<vector<_Type>,_Comparator>::CIndex ( const vector<_Type> & sequenceToIndex, const _Comparator & comparator) 
{
	m_data=sequenceToIndex;
	cmp=comparator;
}
// --------------------------------------------------------------------------------
template <typename _Type, typename _Comparator>
CIndex<vector<_Type>,_Comparator>::~CIndex (void) { }
// --------------------------------------------------------------------------------
template <typename _Type, typename _Comparator>
set<int> CIndex<vector<_Type>,_Comparator>::Search ( const vector<_Type> & searchFor ) const
	{
		set<int> output;
		int position=0;
		bool ucantdothis=0;
		typename vector<_Type>::const_iterator it_data=m_data.begin();
		typename vector<_Type>::const_iterator it_search=searchFor.begin();
		typename vector<_Type>::const_iterator GoBack=m_data.begin();
		// searchFor je prazdne
		if(it_search==searchFor.end())
		{
			for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
			{
				output.insert(position);
				position++;
			}
			return output;
		}
		// Hledej - HODNE NAIVNI ALGORITMUS xD
		for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
		{
			GoBack=it_data;
			it_search=searchFor.begin();
			while(!ucantdothis)
			{
				if(it_search==searchFor.end())
				{
					output.insert(position);
					break;
				}
				if(it_data==m_data.end())
				{
					ucantdothis=1;
					break;
				}
				if((cmp(*it_data,*it_search))||(cmp(*it_search,*it_data)))
					break;
				++it_data;
				++it_search;
			}
			if(ucantdothis)
				break;
			it_data=GoBack;
			position++;
		}
		return output;
	}
*/

// --------------------------------------------------------------------------------
// _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY - _TYPE ONLY

/*template <typename _Type, typename _Comparator>
CIndex<_Type,_Comparator>::CIndex ( const _Type & sequenceToIndex, const _Comparator & comparator) 
: cmp(comparator) , m_data(sequenceToIndex)
{
}*/
// --------------------------------------------------------------------------------
/*template <typename _Type, typename _Comparator>
CIndex<_Type,_Comparator>::~CIndex (void) { }*/
// --------------------------------------------------------------------------------
/*template <typename _Type, typename _Comparator>
set<int> CIndex<_Type,_Comparator>::Search ( const _Type & searchFor ) const
	{
		set<int> output;
		int position=0;
		bool ucantdothis=0;
		typename _Type::const_iterator it_data=m_data.begin();
		typename _Type::const_iterator it_search=searchFor.begin();
		typename _Type::const_iterator GoBack=m_data.begin();
		// searchFor je prazdne
		if(it_search==searchFor.end())
		{
			for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
			{
				output.insert(position);
				position++;
			}
			return output;
		}
		// Hledej - HODNE NAIVNI ALGORITMUS xD
		for(it_data=m_data.begin();it_data!=m_data.end();++it_data)
		{
			GoBack=it_data;
			it_search=searchFor.begin();
			while(!ucantdothis)
			{
				if(it_search==searchFor.end())
				{
					output.insert(position);
					break;
				}
				if(it_data==m_data.end())
				{
					ucantdothis=1;
					break;
				}
				if((cmp(*it_data,*it_search))||(cmp(*it_search,*it_data)))
					break;
				++it_data;
				++it_search;
			}
			if(ucantdothis)
				break;
			it_data=GoBack;
			position++;
		}
		return output;
	}*/
// --------------------------------------------------------------------------------

