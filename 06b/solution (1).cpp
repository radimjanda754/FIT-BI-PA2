#ifndef __PROGTEST__
#include "common.h"
using namespace std;
#endif /* __PROGTEST__ */
// ----------------------------------------------------------------------------
class CHead
{
 public:
	CHead (const string & name) : m_name(name) {};
	virtual ~CHead () {};
	virtual void print(ostream & os)const{os << "ERROR-Print" << endl;};
	virtual void print(ostream & os,vector<string> & deep)const{os << "ERROR-Print-deep"<<endl;};
	virtual string Type()const{return "ERROR-Type";};
	virtual string Name()const{return m_name;};
	virtual CIPv4 Get4()const{return CIPv4();};
	virtual CIPv6 Get6()const{return CIPv6();};
	virtual string GetIPS()const{return "ERROR-GetIPS";};
	virtual int GetIPSnm()const{return 0;};
	virtual int GetMX()const{return 0;};
	virtual string & GetNameAddr(){return m_name;};
	virtual const vector <CHead*> & GetDNS() const {static vector <CHead*> a;return a;};
	virtual vector<string> GetVec()const{return vector<string>{"SERIOUS","ERROR"};};
	virtual bool Add(const CHead & addthis) {return false;};
	friend ostream & operator << ( ostream & os, const CHead & x )
	{
		x.print(os);
		return os;
	}
 private:
	string m_name;
};
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
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
// ----------------------------------------------------------------------------
class CRecSPF : public CHead
{
 public:
	CRecSPF(const string & name) : CHead(name) {};
	CRecSPF(const string & name,const vector<string> & stringvec) : CHead(name) , m_data(stringvec) {};
	~CRecSPF() {};
	virtual string Type()const{return "SPF";};
	virtual CRecSPF & Add (const string & addthis){m_data.push_back(addthis);return *this;};
	virtual void print(ostream & os)const{os << *this;};
	virtual vector<string> GetVec()const{return m_data;};
	friend ostream & operator << ( ostream & os, const CRecSPF & x )
	{
		os << x.Name() << " SPF";
		vector<string>::const_iterator it;	
		for(it=x.m_data.begin();it!=x.m_data.end();++it)
		{
			os << ' ' << *it;
			if((it+1)!=x.m_data.end())
				os << ',';
		}
		os << endl;
		return os;
	};
 private:
	vector<string> m_data;
};
// ----------------------------------------------------------------------------
class CRecCNAME : public CHead
{
 public:
	CRecCNAME (const string & name, const string & ip) : CHead(name) , m_ip(ip) {};
	~CRecCNAME() {};
	virtual string Type()const{return "CNAME";};
	virtual string GetIPS()const{return m_ip;};
	virtual void print(ostream & os)const{os << *this;};
	friend ostream & operator << ( ostream & os, const CRecCNAME & x )
	{
		os << x.Name() << " CNAME " << x.m_ip << endl;
		return os;
	};
 private:
	string m_ip;
};
// ----------------------------------------------------------------------------
class CSearch 
{
 public:
	CSearch(const string & searchthis,const vector<CHead*> & INdnsx)
	{
		m_cnt=0;
		const vector<CHead*> * INdns=&INdnsx;
		vector<CHead*>::const_iterator it=INdns->begin();
		vector<string>::iterator its;
		stringstream ss(searchthis);
		vector<string> hr;
		string tmp;
		while(getline(ss,tmp,'.'))
			hr.insert(hr.begin(),tmp);
		for(its=hr.begin();its<(hr.end()-1);++its)
		{
			for(it=INdns->begin();it!=INdns->end();++it)
			{
				if((*it)->Type()=="Z")
				{
					if((*it)->Name()==(*its))
					{
						INdns=&(*it)->GetDNS();
						break;
					}
				}
			}
		}

		for(it=INdns->begin();it!=INdns->end();++it)
		{
			if((*it)->Name()==hr.back())
			{
				t_dns.push_back(*it);
				m_cnt++;
			}
		}
	};
	~CSearch() {};
	friend ostream & operator << ( ostream & os, const CSearch & x )
	{
		vector<CHead*>::const_iterator it=x.t_dns.begin();
		for(it=x.t_dns.begin();it!=x.t_dns.end();++it)
			(*it)->print(os);
		return os;
	};
	CHead & operator [] (const int & x)
	{
		if(x>=m_cnt) throw InvalidIndexException(x);
		if(x<0) throw InvalidIndexException(x);
		return *t_dns[x];
		//return CHead b;
	};
	int Count(){return m_cnt;};
 private:	
	int m_cnt;
	vector <CHead*> t_dns;
};
// ----------------------------------------------------------------------------
class CZone : public CHead
{
 public:
	CZone (const string & name) : CHead(name) {};
	CZone (const CZone & copy) : CHead(copy.Name()) 
	{
		vector<CHead*>::const_iterator it=copy.dns.begin();
		for(it=copy.dns.begin();it!=copy.dns.end();++it)
		{
			if((*it)->Type()=="A")
				dns.push_back(new CRecA((*it)->Name(),(*it)->Get4()));
			if((*it)->Type()=="AAAA")
				dns.push_back(new CRecAAAA((*it)->Name(),(*it)->Get6()));
			if((*it)->Type()=="MX")
				dns.push_back(new CRecMX((*it)->Name(),(*it)->GetIPS(),(*it)->GetMX()));
			if((*it)->Type()=="CNAME")
				dns.push_back(new CRecCNAME((*it)->Name(),(*it)->GetIPS()));
			if((*it)->Type()=="SPF")
				dns.push_back(new CRecSPF((*it)->Name(),(*it)->GetVec()));
			if((*it)->Type()=="Z")
				dns.push_back(new CZone(**it));
		}
	};
	CZone (const CHead & copy) : CHead(copy.Name()) 
	{
		const vector<CHead*> & tmp=copy.GetDNS();
		vector<CHead*>::const_iterator it=tmp.begin();
		for(it=tmp.begin();it!=tmp.end();++it)
		{
			if((*it)->Type()=="A")
				dns.push_back(new CRecA((*it)->Name(),(*it)->Get4()));
			if((*it)->Type()=="AAAA")
				dns.push_back(new CRecAAAA((*it)->Name(),(*it)->Get6()));
			if((*it)->Type()=="MX")
				dns.push_back(new CRecMX((*it)->Name(),(*it)->GetIPS(),(*it)->GetMX()));
			if((*it)->Type()=="CNAME")
				dns.push_back(new CRecCNAME((*it)->Name(),(*it)->GetIPS()));
			if((*it)->Type()=="SPF")
				dns.push_back(new CRecSPF((*it)->Name(),(*it)->GetVec()));
			if((*it)->Type()=="Z")
				dns.push_back(new CZone(**it));
		}
	};
	~CZone() {
		vector<CHead*>::const_iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			delete *it;
		}
	};
	virtual const vector <CHead*> & GetDNS() const {return dns;};
	virtual string Type()const{return "Z";};
	virtual void print(ostream & os)const{os << *this;};
	virtual void print(ostream & os,vector<string> & deep)const{
		vector<string>::iterator its;
		os << this->Name() << endl;
		vector<CHead*>::const_iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((it+1)==dns.end())
			{
				for(its=deep.begin();its!=deep.end();++its)
					os << *its;
				os << " \\- ";
				if((*it)->Type()=="Z")
				{
					deep.push_back("   ");
					(*it)->print(os,deep);
					deep.erase(deep.end());
				}
				else
				{
					(*it)->print(os);
				}
			}
			else
			{
				for(its=deep.begin();its!=deep.end();++its)
					os << *its;
				os << " +- ";
				if((*it)->Type()=="Z")
				{
					deep.push_back(" | ");
					(*it)->print(os,deep);
					deep.erase(deep.end());
				}
				else
				{
					(*it)->print(os);
				}
			}

		}
	};
// ADD --------------------------------------------------------------------
	bool Add(const CRecA & addthis) {
		string type="A";
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Get4()==addthis.Get4())
					return false;
			}
			if((*it)->Type()=="CNAME"||(*it)->Type()=="Z")
			{
				if((*it)->Name()==addthis.Name())
					return false;
			}
		}
		dns.push_back(new CRecA(addthis));
		return true;
	};
	bool Add(const CRecAAAA & addthis) {
		string type="AAAA";
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Get6()==addthis.Get6())
					return false;
			}
			if((*it)->Type()=="CNAME"||(*it)->Type()=="Z")
			{
				if((*it)->Name()==addthis.Name())
					return false;
			}
		}
		dns.push_back(new CRecAAAA(addthis));
		return true;
	};
	bool Add(const CRecMX & addthis) {
		string type="MX";
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if(((*it)->GetIPS()==addthis.GetIPS())&&((*it)->GetIPSnm()==addthis.GetIPSnm()))
					return false;
			}
			if((*it)->Type()=="CNAME"||(*it)->Type()=="Z")
			{
				if((*it)->Name()==addthis.Name())
					return false;
			}
		}
		dns.push_back(new CRecMX(addthis));
		return true;
	};
	bool Add(const CRecSPF & addthis) {
		string type="SPF";
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Name()==addthis.Name())
				{
					if((*it)->GetVec()==addthis.GetVec())
						return false;
				}
			}
			if((*it)->Type()=="CNAME"||(*it)->Type()=="Z")
			{
				if((*it)->Name()==addthis.Name())
					return false;
			}
		}
		dns.push_back(new CRecSPF(addthis));
		return true;
	};
	bool Add(const CRecCNAME & addthis) {
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Name()==addthis.Name())
				return false;
		}
		dns.push_back(new CRecCNAME(addthis));
		return true;
	};
	bool Add(const CZone & addthis) {
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Name()==addthis.Name())
				return false;
		}
		dns.push_back(new CZone(addthis));
		return true;
	};
// DEL --------------------------------------------------------------------
	bool Del(const CRecA & addthis)
	{
		string type="A";
		vector<CHead*>::iterator it=dns.begin();
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
		vector<CHead*>::iterator it=dns.begin();
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
		vector<CHead*>::iterator it=dns.begin();
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
	bool Del(const CRecSPF & addthis)
	{
		string type="SPF";
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Type()==type)
			{
				if((*it)->Name()==addthis.Name())
				{
					if((*it)->GetVec()==addthis.GetVec())
					{
						delete *it;
						dns.erase(it);
						return true;
					}				
				}
			}
		}
		return false;	
	}
	bool Del(const CRecCNAME & addthis)
	{
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Name()==addthis.Name())
			{
				delete *it;
				dns.erase(it);
				return true;
			}
		}
		return false;	
	}	
	bool Del(const CZone & addthis)
	{
		vector<CHead*>::iterator it=dns.begin();
		for(it=dns.begin();it!=dns.end();++it)
		{
			if((*it)->Name()==addthis.Name())
			{
				delete *it;
				dns.erase(it);
				return true;
			}
		}
		return false;	
	}	
	CSearch Search(const string & searchthis) const
	{
		return CSearch (searchthis,dns);
	}
// OPERATORY ----------------------------------------------------------------
	friend ostream & operator << ( ostream & os, const CZone & x )
	{
		vector<string> deep;
		os << x.Name() << endl;
		vector<CHead*>::const_iterator it=x.dns.begin();
		for(it=x.dns.begin();it!=x.dns.end();++it)
		{
			if((it+1)==x.dns.end())
			{
				os << " \\- ";
				if((*it)->Type()=="Z")
				{
					deep.push_back("   ");
					(*it)->print(os,deep);
					deep.erase(deep.end());
				}
				else
				{
					(*it)->print(os);
				}
			}
			else
			{
				os << " +- ";
				if((*it)->Type()=="Z")
				{
					deep.push_back(" | ");
					(*it)->print(os,deep);
					deep.erase(deep.end());
				}
				else
				{
					(*it)->print(os);
				}
			}

		}	
		return os;
	}
	CZone & operator = ( const CHead & copy )
	{
		GetNameAddr()=copy.Name();
		vector<CHead*>::const_iterator it;

		for(it=dns.begin();it!=dns.end();++it)
		{
			delete *it;
		}
		dns.erase(dns.begin(),dns.end());

		const vector<CHead*> & tmp=copy.GetDNS();
		for(it=tmp.begin();it!=tmp.end();++it)
		{
			if((*it)->Type()=="A")
				dns.push_back(new CRecA((*it)->Name(),(*it)->Get4()));
			if((*it)->Type()=="AAAA")
				dns.push_back(new CRecAAAA((*it)->Name(),(*it)->Get6()));
			if((*it)->Type()=="MX")
				dns.push_back(new CRecMX((*it)->Name(),(*it)->GetIPS(),(*it)->GetMX()));
			if((*it)->Type()=="CNAME")
				dns.push_back(new CRecCNAME((*it)->Name(),(*it)->GetIPS()));
			if((*it)->Type()=="SPF")
				dns.push_back(new CRecSPF((*it)->Name(),(*it)->GetVec()));
			if((*it)->Type()=="Z")
				dns.push_back(new CZone(**it));
		}
		return *this;
	};	
	CZone & operator = ( const CZone & copy )
	{
		GetNameAddr()=copy.Name();
		vector<CHead*>::const_iterator it;

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
			if((*it)->Type()=="CNAME")
				dns.push_back(new CRecCNAME((*it)->Name(),(*it)->GetIPS()));
			if((*it)->Type()=="SPF")
				dns.push_back(new CRecSPF((*it)->Name(),(*it)->GetVec()));
			if((*it)->Type()=="Z")
				dns.push_back(new CZone(**it));
		}
		return *this;
	};	

 private:
	vector <CHead*> dns;
};
// ----------------------------------------------------------------------------

#ifndef __PROGTEST__

#endif /* __PROGTEST__ */

