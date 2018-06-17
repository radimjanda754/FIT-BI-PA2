#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#include <stdint.h>
using namespace std;
#endif /* __PROGTEST__ */

// ------------- DEFINICE A STRUKTURY -------------------------
#define FAIL {ClearNodes(FirstNode);delete [] input;return false;}
#define CFAIL {ClearNodes(FirstNode);return false;}
#define NewByteCheck if(!inF.get(TMPinC)) return false;if(!(TMPinC>>7)) return false;if((TMPinC>>6)&1) return false;inS+=TMPinC;
struct t_node{
	t_node (t_node * father) {
		m_father=father;
		m_value.clear();
		m_left=NULL;
		m_right=NULL;
		CanGoRight=1;
	}
	t_node (string value) {
		m_father=NULL;
		m_value=value;
		m_left=NULL;
		m_right=NULL;
		CanGoRight=1;
	}
	t_node * Connect(t_node * left, t_node * right) { // Pouze u komprese
		t_node * tmp=new t_node(NULL);
		left->m_father=tmp;
		right->m_father=tmp;
		tmp->m_left=left;
		tmp->m_right=right;
		return(tmp);
	}
	t_node * AddLeft(t_node * current) { // Pouze u dekomprese
		t_node * tmp=new t_node(current);
		current->m_left=tmp;
		return(tmp);
	}
	t_node * AddRight(t_node * current) { // Pouze u dekomprese
		while(current->m_right!=NULL||!current->m_value.empty())
		{
			if(!current->m_father)
				return(NULL);
			current=current->m_father;
		}
		t_node * tmp=new t_node(current);
		current->m_right=tmp;
		return(tmp);
	}
	string m_value;
	t_node * m_father;
	t_node * m_left;
	t_node * m_right;
	int CanGoRight;
};
struct StructIntVector{
	string charcode;
	int value;
	string path;
	t_node * adress;
};


// ------------------------------- FUNKCE -------------------------------------
bool cmp ( const StructIntVector & left, const StructIntVector & right )
{
	return left.value>right.value;
}

/*
void PrintNodes(t_node * TOP) {
	cout << "[This:" << TOP << ']';
	cout << "[Value:" << hex << TOP->m_value;
	cout << "][L:" << TOP->m_left << ']';
	cout << "[R:" << TOP->m_right << ']' << endl;
	if(TOP->m_left)
		PrintNodes(TOP->m_left);
	if(TOP->m_right)
		PrintNodes(TOP->m_right);
}*/

void ClearNodes(t_node * node)
{ // Vycisti pamet od uzlu
	if(node->m_left)
		ClearNodes(node->m_left);
	if(node->m_right)
		ClearNodes(node->m_right);
	delete node;
}

int getb(char c, int & BitNum, int & ByteNum, int & i,int iMAX)
{ // Funkce vrati bit ktery nasleduje v poradi, pokud je neco spatne vrati -1
	if (i==iMAX)
		return -1;
	
	int out=(int)((c>>BitNum)&1);
	BitNum--;
	i++;
//	cout << out;
	if(BitNum<0)
	{
		ByteNum++;
		BitNum=7;	
//		cout << ' ';
	}
	return out;
}

void writeb(string & output, int & BitNum, int & ByteNum, int value)
{ // Funkce vrati bit ktery nasleduje v poradi, pokud je neco spatne vrati -1
	if(BitNum<0)
	{
		BitNum=7;
		ByteNum++;
		output+=(char)0x00;
	}
	if(value)
	{
		//cout << 1;
		output[ByteNum] |= 1<<BitNum;
	}
	else
	{
		//cout << 0;
		output[ByteNum] &= ~(1<<BitNum);
	}
	BitNum--;
}		

void removeb(int & BitNum, int & ByteNum)
{ // Posune ukazatele bitu o bit zpet
	BitNum++;
	if(BitNum>7)
	{
		ByteNum--;
		BitNum=0;
	}
}		

bool compressFile ( const char * inFile, const char * outFile )
 {
	char inC;
	char TMPinC;
	int Nchars=0;
	string inS;
	map<string, int> CharNums;
	map<string, int>::iterator it = CharNums.begin();
	vector<StructIntVector> Adr;
	vector<StructIntVector> Bottom;
	vector<StructIntVector>::iterator vecit = Bottom.begin();
	
	ifstream inF (inFile,ios::in);
	if(inF.fail()) return false;
	while(inF.get(inC))
	{
		inS.clear();
		if(((inC>>7)&1)==1) // Nacteni vicebytovich znaku
		{
			inS+=inC;
			if(((inC>>6)&1)==1)
			{
				NewByteCheck
				if(((inC>>5)&1)==1)
				{
					NewByteCheck
					if(((inC>>4)&1)==1)
					{
						NewByteCheck
						if(((inC>>3)&1)==1) return false;
					}
				}
			}
			else
			{
				return false;
			}
		}
		else // Nacteni jednobytoveho znaku
		{
			inS+=inC;
		}
		
		// Zapis znaku do mapy
		if(CharNums.find(inS)==CharNums.end())
		{
			Nchars++;CharNums[inS]=1;
		}
		else
		{
			CharNums[inS]++;
		}
	}
	if(Nchars==0) {
		ofstream oF (outFile, ios::out);
		if(oF.fail()) return false;
		if(oF.bad()) return false;
		oF.close();
		return true;
	}
	
	// Presun z mapy do adresointoveho vectoru
	for(it=CharNums.begin();it!=CharNums.end();++it)
	{
		StructIntVector megatemp;
		megatemp.value=it->second;
		t_node * temp= new t_node(it->first);		
		megatemp.adress=temp;
		Adr.push_back(megatemp);
	}
	// Bezmyslenkovite pridanu ENDu :D
	StructIntVector evenmoretemp;
	string powerfulltemp;
	powerfulltemp.clear();
	evenmoretemp.value=1;
	powerfulltemp+=(char)0xf4;powerfulltemp+=(char)0x90;
	powerfulltemp+=(char)0x80;powerfulltemp+=(char)0x80;
	t_node  * supermegatemp = new t_node(powerfulltemp);
	evenmoretemp.adress=supermegatemp;
	Adr.push_back(evenmoretemp);
	Nchars++;

	
	// Vytvareni stromu
	while(Nchars>2)
	{
		sort(Adr.begin(),Adr.end(),cmp);
		StructIntVector gigatemp;
		gigatemp.value=Adr[Nchars-2].value+Adr[Nchars-1].value;
		gigatemp.adress=gigatemp.adress->Connect(Adr[Nchars-1].adress,Adr[Nchars-2].adress);
		Adr.pop_back();
		Adr.pop_back();
		Adr.push_back(gigatemp);
		Nchars--;
	}
	// Vytvoreni spicky stromu
	t_node * FirstNode=new t_node(NULL);
	t_node * giantictmp=FirstNode;
	FirstNode=FirstNode->Connect(Adr[0].adress,Adr[1].adress);
	delete giantictmp;

	// Priprava na zapsani do outFile
	string output;
	output.clear();
	string current;
	current.clear();
	int WriteByte=-1;
	int WriteBit=-1;
	int CurrentByte=-1;
	int CurrentBit=-1;
	int steps=0;
	//int UselessInt=0;
	//int BitNum=7;
	//int ByteNum=0;
	
	// Zapsani stromu
	t_node * move = FirstNode;
	while(move->CanGoRight)
	{
		// Jed doleva dolu dokud muzes
		while(move->m_left)
		{
			steps++;
			move=move->m_left;
			writeb(output,WriteBit,WriteByte,0);
			writeb(current,CurrentBit,CurrentByte,0);
		}
		// Dosel si k pismenu, zapis vse co potrebujes
		StructIntVector TMP99;
		TMP99.value=steps;
		TMP99.path=current;
		TMP99.charcode=move->m_value;
		Bottom.push_back(TMP99);
		writeb(output,WriteBit,WriteByte,1);
		// Jed nahoru a az to bude vhodne tak dopravva
		while((!move->CanGoRight||!move->m_right)&&move->m_father)
		{
			move=move->m_father;
			steps--;
			removeb(CurrentBit,CurrentByte);
		}
		//cout << "C:[";
		for(int i=0;i<(int)TMP99.charcode.length();i++)
			for(int i2=7;i2>=0;i2--)
					writeb(output,WriteBit,WriteByte,(TMP99.charcode[i]>>i2)&1);
		//cout << ']';
		// Uz si vsude byl? -> break
		if(!move->m_right||!move->CanGoRight)
			break;
		// Jdi doprava a uz tudy vickrat nechod
		move->CanGoRight=0;				
		move=move->m_right;
		steps++;
		writeb(current,CurrentBit,CurrentByte,1);
	}

	inF.clear();
	inF.seekg(0, ios::beg);
	while(inF.get(inC))
	{
		// --------------------- TOTO JE ZDE PODRUHE, trochu vyupgradovane
		inS.clear();
		if(((inC>>7)&1)==1) // Nacteni vicebytovich znaku
		{
			inS+=inC;
			if(((inC>>6)&1)==1)
			{
				NewByteCheck
				if(((inC>>5)&1)==1)
				{
					NewByteCheck
					if(((inC>>4)&1)==1)
					{
						NewByteCheck
						if(((inC>>3)&1)==1) CFAIL
					}
				}
			}
			else
			{
				CFAIL
			}
		}
		else // Nacteni jednobytoveho znaku
		{
			inS+=inC;
		}
		int foundsmth=0;
		
		for(vecit=Bottom.begin();vecit!=Bottom.end();++vecit)
		{
			if(inS==vecit->charcode)
			{
				if(vecit->value>8)
				{
					//cout << "HERE->";
					for(int i=0;i<=((int)vecit->value/8);i++)
						for(int i2=0;i2<=7;i2++)
							{
								if((i2+1+i*8)==(vecit->value+1)) break;
								writeb(output,WriteBit,WriteByte,((vecit->path[i]) >> (7-i2))&1);
								//cout << (((vecit->path[i]) >> (7-i2))&1);
							}
				}
				else
				{
					for(int i=0;i<vecit->value;i++)
						writeb(output,WriteBit,WriteByte,((vecit->path[0]) >> (7-i))&1);
						//cout << (((vecit->path[0]) >> (7-i))&1);
				}
				foundsmth=1;
				break;
			}
			
		}
		if(!foundsmth) CFAIL
		// --------------------------------------------
		//cout << "Now reading:[" << inC <<']';
		//for (vecit=Bottom.begin();vecit!=Bottom.end();++vecit)
		//	if(vecit->charcode
		
	}

	inS.clear();
	inS+=(char)0xf4;inS+=(char)0x90;
	inS+=(char)0x80;inS+=(char)0x80;
	// Vytisknuti ENDu
		int foundsmth=0;
		
		for(vecit=Bottom.begin();vecit!=Bottom.end();++vecit)
		{
			if(inS==vecit->charcode)
			{
				if(vecit->value>8)
				{
					//cout << "HERE->";
					for(int i=0;i<=((int)vecit->value/8);i++)
						for(int i2=0;i2<=7;i2++)
							{
								if((i2+1+i*8)==(vecit->value+1)) break;
								writeb(output,WriteBit,WriteByte,((vecit->path[i]) >> (7-i2))&1);
								//cout << (((vecit->path[i]) >> (7-i2))&1);
							}
				}
				else
				{
					for(int i=0;i<vecit->value;i++)
						writeb(output,WriteBit,WriteByte,((vecit->path[0]) >> (7-i))&1);
						//cout << (((vecit->path[0]) >> (7-i))&1);
				}
				foundsmth=1;
				break;
			}
			
		}
		if(!foundsmth) CFAIL
	// TED UZ BY VSE MELO BYT V OUTPUTU
	ofstream oF (outFile, ios::out);
	if(oF.fail()) CFAIL
	oF << output;
	if(oF.bad()) CFAIL
	oF.close();
	inF.close();

	//endl << "TOP: " << FirstNode << endl;
	//PrintNodes(FirstNode);
	ClearNodes(FirstNode);
   return true;
 }

bool decompressFile ( const char * inFile, const char * outFile ) 
 {
	int BitNum=7;
	int ByteNum=0;
	int iC=0;
	int iMAX=0;
	ifstream inF(inFile,  ios::binary | ios::in | ios::ate);

	if (!inF.is_open()) return(false);
	//if (inF.fail()) return(false);
	//if (inF.bad()) return(false);

	// Nacteni vstupu do pameti
	int size = inF.tellg();
	//Prazdny soubor
	if (size==0)
	{
		inF.close();
		ofstream of (outFile, ios::out | ios::binary );
		if (of.fail()) return false;
		of.close();
		return true;
	}
	if (size<=5)
	{
		inF.close(); return false;
	}
	// Neprazdny soubor
	iMAX=size*8;
	char * input=new char[size];
	inF.seekg(0, ios::beg);	
	//if(inF.bad()) {inF.close();return false;}
	//if(inF.fail()) {inF.close();return false;}
	inF.read (input, size);
	//if(inF.bad()) {inF.close();return false;}
	//if(inF.fail()) {inF.close();return false;}
	inF.close();

	// Vytvoreni spicky stromu
	t_node * FirstNode=new t_node(NULL);
	t_node * CurrentNode=FirstNode;
	
	// Zpracovavani bitu
	int tmpBit;
	while(iC<iMAX)
	{	
		// Nacti bit, pokud nacteni selhalo -> return false
		tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX);
		if(tmpBit==-1) FAIL
		
		if(!tmpBit)	// Pokud je bit nulovi, pouze v levo vytvor uzel
		{
			CurrentNode=CurrentNode->AddLeft(CurrentNode);
		}
		else // Pokud bit neni nulovi nacitej bity UTF-8 znaku
		{
			char tmpC='A';
			int tmpBytes=1;
			tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX);
			if(tmpBit==-1) FAIL
			
			if(tmpBit==0) // V pripade ze znak ma pouze 1 byte
			{
				// Zapis uvodni bit do charu
				tmpC &= ~(1<<7);
				// Pokracuj v zapisu ostatnich bitu
				for(int i=6;i>=0;i--)
				{
					tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX);
					if(tmpBit==-1) FAIL
					if(tmpBit)
						tmpC |= 1<<i;
					else
						tmpC &= ~(1<<i);
				}
				// Zapis UTF-8 znak do stromu
				CurrentNode->m_value+=tmpC;
				// Pokracuj ve strome
				CurrentNode=CurrentNode->AddRight(CurrentNode);
				// Strom uzavren
				if(!CurrentNode)
					break;
			}
			else // V pripade ze znak ma vice bytu
			{
				// Zjisti kolik teda ma bytu a uloz to do tmpBytes
				while((tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX)))
				{
					if(tmpBit==-1) FAIL
					tmpBytes++;
					if(tmpBytes>4) FAIL
				}
				if(tmpBytes==1) FAIL
				// Zapis uvodni biti do charu
				for(int i=0;i<=tmpBytes;i++)
				{
					if(i==tmpBytes)
						tmpC &= ~(1<<(7-i));
					else
						tmpC |= 1<<(7-i);
				}
				// Zapis zbytek bitu do prvniho bytu
				for(int i=6-tmpBytes;i>=0;i--)
				{
					tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX);
					if(tmpBit==-1) FAIL
					if(tmpBit)
						tmpC |= 1<<i;
					else
						tmpC &= ~(1<<i);
				}
				// Zapis prvni byte UTF-8 znaku do stromu
				CurrentNode->m_value+=tmpC;
				// Pokracuj s ostatnimi byti
				for(int Byte=1;Byte<tmpBytes;Byte++)
				{
					for(int i=7;i>=0;i--)
					{
						tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX);
						if(tmpBit==-1) FAIL
						if(tmpBit)
						{
							if(i==6) FAIL
							tmpC |= 1<<i;
						}
						else
						{
							if(i==7) FAIL
							tmpC &= ~(1<<i);
						}
					}
					// Zapis byte UTF-8 znaku do stromu
					CurrentNode->m_value+=tmpC;
				}
				// Pokracuj ve strome
				CurrentNode=CurrentNode->AddRight(CurrentNode);
				// Strom uzavren
				if(!CurrentNode)
					break;
			}
		}
	}
	
	// Zapis do sounoru - priprava veci
	ofstream oF(outFile, ios::out | ios::binary);
	if(!oF.is_open()) FAIL
	if(oF.fail()) FAIL
	CurrentNode=FirstNode;
	// Zapis do souboru - cyklus
	while((tmpBit=getb(input[ByteNum],BitNum,ByteNum,iC,iMAX))!=-1)
	{
		if(tmpBit==-1) {oF.close();FAIL}
		if(tmpBit)
			CurrentNode=CurrentNode->m_right;
		else
			CurrentNode=CurrentNode->m_left;

		if(!CurrentNode) {oF.close();FAIL}

		if(!CurrentNode->m_value.empty())
		{
			if(CurrentNode->m_value.length()==4)
				if(CurrentNode->m_value[0]==(char)0xf4)
					if(CurrentNode->m_value[1]==(char)0x90)
						if(CurrentNode->m_value[2]==(char)0x80)
							if(CurrentNode->m_value[3]==(char)0x80)
								break;
			oF << CurrentNode->m_value;
			if(oF.fail()) {oF.close();FAIL}
			if(oF.bad()) {oF.close();FAIL}
			CurrentNode=FirstNode;
		}

	}
	oF.close();
	if(tmpBit==-1) FAIL
	
	//cout << endl << "TOP: " << FirstNode << endl;
	//PrintNodes(FirstNode);
	ClearNodes(FirstNode);
	delete [] input;
	return true;
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {/*
	bool check;
	check=compressFile("test3.huff","compressed");
	cout << "COMPRESS: " << check << endl;
	check=decompressFile("compressed","output");
	cout << "DECOMPRESS: " << check << endl;
*/
	/*bool check;
	check=decompressFile("test4.huf","output");
	cout << "CHECK: " << check << endl;*/
	// tests
   return 0;
 }
#endif /* __PROGTEST__ */

