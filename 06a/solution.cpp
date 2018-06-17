#ifndef __PROGTEST__
#include "common.h"
using namespace std;
#endif /* __PROGTEST__ */

class CHead
{
 public:
	CHead (const string & name) : m_name(name) {};
	virtual ~CHead () {};
	virtual void print(ostream & os)const{os << "ERROR" << endl;};
	virtual string Type()const{return "ERROR";};
	virtual string Name()const{return m_name;};
	virtual CIPv4 Get4()const{return CIPv4();};
	virtual CIPv6 Get6()const{return CIPv6();};
	virtual string GetIPS()const{return "ERROR";};
	virtual int GetIPSnm()const{return 0;};
	virtual int GetMX()const{return 0;};
	friend ostream & operator << ( ostream & os, const CHead & x )
	{
		x.print(os);
		return os;
	}
 private:
	string m_name;
};

class CRecA : public CHead
{
 public:
	CRecA (const string & name, const CIPv4 & ip) : CHead(name) , m_ip(ip) {};
	~CRecA () {};
	virtual string Type()const{return "A";};
	virtual CIPv4 Get4()const{return m_ip;};
	virtual void print(ostream & os)const{os << *this;};
	friend ostream & operator << ( ostream & os, const CRecA & x )
	{
		os << x.Name() << " A " << x.m_ip << endl;
		return os;
	};
 private:
	CIPv4 m_ip;
};

class CRecAAAA : public CHead
{
 public:
	CRecAAAA (const string & name, const CIPv6 & ip) : CHead(name) , m_ip(ip) {};
	~CRecAAAA () {};
	virtual string Type()const{return "AAAA";};
	virtual CIPv6 Get6()const{return m_ip;};
	virtual void print(ostream & os)const{os << *this;};
	friend ostream & operator << ( ostream & os, const CRecAAAA & x )
	{
		os << x.Name() << " AAAA " << x.m_ip << endl;
		return os;
	};
 private:
	CIPv6 m_ip;
};

class CRecMX : public CHead
{
 public:
	CRecMX (const string & name, const string & ip, const int & mx) : CHead(name) , m_ip(ip) , m_mx(mx) {};
	~CRecMX() {};
	virtual string Type()const{return "MX";};
	virtual string GetIPS()const{return m_ip;};
	virtual int GetMX()const{return m_mx;}
	virtual int GetIPSnm()const{return m_mx;};
	virtual void print(ostream & os)const{os << *this;};
	friend ostream & operator << ( ostream & os, const CRecMX & x )
	{
		os << x.Name() << " MX " << x.m_mx << ' ' << x.m_ip << endl;
		return os;
	};
 private:
	string m_ip;
	int m_mx;
};

class CSearch 
{
 public:
	CSearch(const string & searchthis,const vector<const CHead*> & INdns)
	{
		m_cnt=0;
		vector<const CHead*>::const_iterator it=INdns.begin();
		for(it=INdns.begin();it!=INdns.end();++it)
		{
			if((*it)->Name()==searchthis)
			{
				t_dns.push_back(*it);
				m_cnt++;
			}
		}
	};
	~CSearch() {};
	friend ostream & operator << ( ostream & os, const CSearch & x )
	{
		vector<const CHead*>::const_iterator it=x.t_dns.begin();
		for(it=x.t_dns.begin();it!=x.t_dns.end();++it)
			(*it)->print(os);
		return os;
	};
	const CHead & operator [] (const int & x)
	{
		if(x>=m_cnt) throw InvalidIndexException(x);
		if(x<0) throw InvalidIndexException(x);
		return *t_dns[x];
		//return CHead b;
	};
	int Count(){return m_cnt;};
 private:	
	int m_cnt;
	vector <const CHead*> t_dns;
};

class CZone
{
 public:
	CZone (const string & name) : m_zonename(name) {};
	CZone (const CZone & copy)
	{
		m_zonename=copy.m_zonename;
		vector<const CHead*>::const_iterator it=copy.dns.begin();
		for(it=copy.dns.begin();it!=copy.dns.end();++it)
		{
			if((*it)->Type()=="A")
				dns.push_back(new CRecA((*it)->Name(),(*it)->Get4()));
			if((*it)->Type()=="AAAA")
				dns.push_back(new CRecAAAA((*it)->Name(),(*it)->Get6()));
			if((*it)->Type()=="MX")
				dns.push_back(new CRecMX((*it)->Name(),(*it)->GetIPS(),(*it)->GetMX()));
		}
	};	
	~CZone() {
		vector<const CHead*>::const_iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			delete *it;
		}
	};
// ADD --------------------------------------------------------------------
	bool Add(const CRecA & addthis) {
		string type="A";
		vector<const CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Get4()==addthis.Get4())
					return false;
			}
		}
		dns.push_back(new CRecA(addthis));
		return true;
	};
	bool Add(const CRecAAAA & addthis) {
		string type="AAAA";
		vector<const CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Get6()==addthis.Get6())
					return false;
			}
		}
		dns.push_back(new CRecAAAA(addthis));
		return true;
	};
	bool Add(const CRecMX & addthis) {
		string type="MX";
		vector<const CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if(((*it)->GetIPS()==addthis.GetIPS())&&((*it)->GetIPSnm()==addthis.GetIPSnm()))
					return false;
			}
		}
		dns.push_back(new CRecMX(addthis));
		return true;
	};
// DEL --------------------------------------------------------------------
	bool Del(const CRecA & addthis)
	{
		string type="A";
		vector<const CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Get4()==addthis.Get4())
				{
					delete *it;
					dns.erase(it);
					return true;
				}
			}
		}
		return false;
	}
	bool Del(const CRecAAAA & addthis)
	{
		string type="AAAA";
		vector<const CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Get6()==addthis.Get6())
				{
					delete *it;
					dns.erase(it);
					return true;
				}
			}
		}
		return false;	
	}
	bool Del(const CRecMX & addthis)
	{
		string type="MX";
		vector<const CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if(((*it)->GetIPS()==addthis.GetIPS())&&((*it)->GetIPSnm()==addthis.GetIPSnm()))
				{
					delete *it;
					dns.erase(it);
					return true;
				}
			}
		}
		return false;	
	}	
	CSearch Search(const string & searchthis) const
	{
		return CSearch (searchthis,dns);
	}
// ------------------------------------------------------------------------
	friend ostream & operator << ( ostream & os, const CZone & x )
	{
		os << x.m_zonename << endl;
		vector<const CHead*>::const_iterator it=x.dns.begin();
		for(it=x.dns.begin();it!=x.dns.end();++it)
		{
			if((it+1)==x.dns.end())
				os << " \\- ";
			else
				os << " +- ";
			(*it)->print(os);
		}	
		return os;
	}
	CZone & operator = ( const CZone & copy )
	{
		m_zonename=copy.m_zonename;	
		vector<const CHead*>::const_iterator it=copy.dns.begin();

		for(it=dns.begin();it!=dns.end();++it)
		{
			delete *it;
		}
		dns.erase(dns.begin(),dns.end());

		for(it=copy.dns.begin();it!=copy.dns.end();++it)
		{
			if((*it)->Type()=="A")
				dns.push_back(new CRecA((*it)->Name(),(*it)->Get4()));
			if((*it)->Type()=="AAAA")
				dns.push_back(new CRecAAAA((*it)->Name(),(*it)->Get6()));
			if((*it)->Type()=="MX")
				dns.push_back(new CRecMX((*it)->Name(),(*it)->GetIPS(),(*it)->GetMX()));
		}
		return *this;
	};	

 private:
	string m_zonename;
	vector <const CHead*> dns;
};

#ifndef __PROGTEST__

#endif /* __PROGTEST__ */
