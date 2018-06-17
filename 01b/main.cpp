#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
#endif /* __PROGTEST__ */

struct t_items{
	string m_item;
	vector<string> m_teachers;
};

bool cmp ( const t_items & left, const t_items & right )
{
	return left.m_item<right.m_item;
}



bool transform  ( const char * inFile,
                  const char * outFile )
 {
	// Definice
	int itemsN=0;
	string line;
	string tmp;
	string tmp2;
	string teacher;
	vector<t_items> items;
	vector<string> UsedItemNames;
	vector<string> UsedTeacherNames;
	vector<string> ItemNamesOnLine;
	vector<string>::iterator it;
	vector<t_items>::iterator itstruc;
	ifstream inF ( inFile, ios::in );

	// Kontrola souboru
	if (inF.fail())
		return (false);

	// Nacitani radek
	while(getline(inF,line))
	{
		// Preskoceni komentaru
		if(line[0]=='#') continue;

		// Dalsi kontrola.... (mezeri tam kde nemaji byt)
		char c;
		int ThereWasALetter=0;
		int ZisIsGettinSrs=0;
		stringstream cs (line);
		while(cs.get(c))
		{
			if((c==':')or(c==','))
			{
				ThereWasALetter=0;ZisIsGettinSrs=0;continue;
			}
			if((!isalpha(c))&&(!isdigit(c))&&(!isspace(c)))
				return(false);
			if(ZisIsGettinSrs==1&&!isspace(c))
				return(false);
			if(isspace(c)&&ThereWasALetter==1)
				ZisIsGettinSrs=1;
			if(!isspace(c))
				ThereWasALetter=1;
			
		}

		line.erase(remove_if(line.begin(), line.end(), ::isspace), line.end());
			//odstraneni white spacu
			//::isspace pro osetreni overloadu
			//remove_if samo o sobe neumi zkracovat delku retezce, pouze prepisuje, proto nutno pouzit line.erase
		if(line.empty())
			continue;
		/*{
			getline(inF,line);
			if(inF.eof())
				break;
			else
				return(false);
		}	*/
		// Predkontrola - Chybejici dvojtecka -> error
		if(line.find(':')==string::npos) return(false);	


		// -------- Prvni cast vstupniho retezce = jmeno ucitele:
		// Kontrola 1.0 - Neni nic pred dvojteckou -> skip
		stringstream ss (line);
		tmp.clear();
		getline(ss, tmp, ':');
		if(tmp.empty()) return(false);
		// Kontrola 1.1 - Carka v prvni casti -> error
		if(tmp.find(',')!=string::npos) return(false);
		teacher=tmp;
		// Kontrola 1.2 - Ucitel jiz byl na nejake radce -> error
		if(find(UsedTeacherNames.begin(), UsedTeacherNames.end(), teacher) != UsedTeacherNames.end())
			return (false);
		else
			UsedTeacherNames.push_back(teacher);


		// -------- Druha cast vstupniho retezce = predmety:
		// Kontrola 2.0 - Neni nic za dvojteckou -> skip
		tmp.clear();
		getline(ss, tmp);
		if(tmp.empty()) continue;
		// Kontrola 2.1 - Dvojtecka navic -> error
		if(tmp.find(':')!=string::npos) return(false);
		// Kontrola 2.2 - Carka nakonci -> error
		if(tmp[tmp.length()-1]==',') return(false);

		// Rozporcovani predmetu:
		ItemNamesOnLine.clear();
		stringstream ssItems (tmp);
		while(getline(ssItems, tmp2, ','))
		{
			// Kontrola 3.0 - Dve carky vedle sebe -> error
			if(tmp2.empty()) return(false);
			// Kontrola 3.1 - Predmet uz byl na radce -> error
			if(find(ItemNamesOnLine.begin(), ItemNamesOnLine.end(), tmp2) != ItemNamesOnLine.end())
				return (false);
			else	
				ItemNamesOnLine.push_back(tmp2);
			
			// Je tento predmet uz ve vektoru?			
			if (find(UsedItemNames.begin(), UsedItemNames.end(), tmp2) != UsedItemNames.end())
			{
				// Jo
				for(int i=0;i<itemsN;i++)
				{
					// Tak ho najdi a prihod to tam
					if(items[i].m_item==tmp2)
					{
						items[i].m_teachers.push_back(teacher);					
						break;
					}
				}
			}
			else
			{
				// Neni (pridat do vektoru)
				itemsN++;
				t_items p;
				p.m_item=tmp2;
				p.m_teachers.push_back(teacher);
				UsedItemNames.push_back(tmp2);
				items.push_back(p);
			}
		}
	}
	inF.close();

	// Serad predmety
	sort(items.begin(),items.end(),cmp);	
	// Serad ucitele
	for(int i=0;i<itemsN;i++)
		sort(items[i].m_teachers.begin(),items[i].m_teachers.end());
	
	
	// ------------- Vypis
	ofstream oF (outFile, ios::out);
	if (oF.fail()) return(false);
	for(itstruc=items.begin(); itstruc!=items.end(); itstruc++)
	{
		oF << itstruc->m_item << ':';
		for(it=itstruc->m_teachers.begin(); it!=itstruc->m_teachers.end(); it++)
		{
			if(it==(itstruc->m_teachers.end()-1))
				oF << ' ' << *it << endl;
			else
				oF << ' ' << *it << ',';
		}
	}
	oF.close();

	return (true);
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
	//bool check;
	//check = transform("testfile","output");	
	//cout << check << endl;
   return 0;
 }
#endif /* __PROGTEST__ */


























