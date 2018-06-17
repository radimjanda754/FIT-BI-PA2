Úkolem je vytvořit šablonu třídy, který bude implementovat generický index.

Implementovaná třída CIndex dostane při vytváření parametrem kolekci s posloupností prvků. Tuto posloupnost prvků bude indexovat. Posloupnost může být:

string - řetězec znaků (C++ string prvků typu char),
vector<T> - vektorem hodnot (nějakého typu T),
list<T> - seznamem hodnot (nějakého typu T).
Nad takto zaindexovanou posloupností chceme vyhledávat. Tedy zadáme nějakou posloupnost prvků (stejného typu) a chceme zjistit, zda ji indexovaná posloupnost někde obsahuje. Výsledkem bude množina pozic, kde je hledaná posloupnost nalezena.

Aby byla indexovací třída obecnější, je vylepšena ještě možností zadat vlastní porovnávač (nepovinný druhý generický parametr). Vyhledávání tedy nemusí probíhat na přesnou shodu, pomocí vlastního porovnávače můžeme zadat, že při porovnávání např. nerozlišujeme malá a velká písmena. Porovnávač bude mít podobu jakou mají porovnávače v STL: bude se jednat o funkci, funktor nebo C++11 lambda výraz, který pro dvojici prvků typu T v posloupnosti rozhodne, který je v požadovaném porovnání menší. Pokud porovnávač není zadán, použije pro porovnávání prvků operátor < platný pro ukládané hodnoty prvků.

Vlastní prvky v posloupnostech (prvky typu T) mohou být libovolné. Příkladem je znak (char), celé číslo (int) nebo řetězec (string). Obecně víte, že pro typ T jsou definované následující operace:

kopírování (operátorem = a kopírujícím konstruktorem),
porovnávání "menší než" operátorem < nebo dodaným komparátorem,
uvolňování (destruktor),
další operace mohou, ale nemusí být s typem T dostupné, tedy Vaše implementace se na ně obecně nemůže spolehnout. Pozor, nemusí být k dispozici implicitní konstruktor, operátor ==, operátor !=, ...
Rozhraní třídy je následující:

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


template <typename _Type, typename _Comparator = ...>
class CIndex
 {
   public:
             CIndex ( const _Type & sequenceToIndex,
                      const _Comparator & comparator = _Comparator () );
            ~CIndex ( void );
    set<int> Search ( const _Type & searchFor ) const;

   private:
    // todo
 };
Odevzdávejte soubor, který obsahuje implementovanou šablonu třídy CIndex a další Vaše podpůrné třídy. Třída musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí obsahovat vkládání hlavičkových souborů a funkci main. Funkce main a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu jako v ukázce níže.

Při řešení úlohy využijte STL. Můžete využívat prvky C++11, upozorňuji ale, že používaný kompilátor má určité problémy při kompilování lambda výrazů, kde je zachycovaný this. Takovým lambda výrazům se doporučuji vyhnout a zachycovat this pomocí lokální proměnné nastavené na hodnotu this.

Úloha obsahuje povinné a bonusové testy. Základním testem projde řešení hledající výskyty naivním algoritmem. Pro získání bonusů je potřeba implementovat algoritmy efektivnější. Při návrhu můžete předpokládat:

Jednou zaindexovaná posloupnost je prohledávaná vícekrát. Je tedy rozumné věnovat čas předzpracování, kterým se zkrátí vlastní vyhledávání. Můžete počítat s tím, že metoda Search je volaná v průměru 100x na jednu instanci.
Obecná implementace s generickým typem prvku a s obecným komparátorem se testuje v povinných testech. Testy rychlosti pracují s datovým typem string a používají implicitní komparátor. Částečná specializace šablony třídy pro takto omezené vstupy může výrazně zrychlit výpočet.
Pro zrychlení vyhledávání se hodí algoritmus KMP, pro indexaci se dá využít suffixové pole nebo DAWG.
Ukázka práce třídy:

class CStrComparator
 {
   public:
                   CStrComparator ( bool caseSensitive )
                    : m_CaseSensitive ( caseSensitive ) { }
    bool           operator () ( const string & a, const string & b ) const
     {
       return m_CaseSensitive ? strcasecmp ( a . c_str (), b . c_str () ) < 0 : a < b ;
     }
    bool           m_CaseSensitive;
 };

bool upperCaseCompare ( const char & a, const char & b )
 {
   return toupper ( a ) < toupper ( b );
 }

...

CIndex <string> t0 ( "abcabcabc" );
set<int> r0 = t0 . Search ( "a" );
 // 0 3 6
set<int> r1 = t0 . Search ( "abc" );
 // 0 3 6
set<int> r2 = t0 . Search ( "abcabc" );
 // 0 3

CIndex <string> t1 ( "abcababc" );
set<int> r3 = t1 . Search ( "a" );
 // 0 3 5
set<int> r4 = t1 . Search ( "abc" );
 // 0 5
set<int> r5 = t1 . Search ( "abcabc" );
 //

CIndex <string> t2 ( "kokokokoskokosokos" );
set<int> r6 = t2 . Search ( "kos" );
 // 6 11 15
set<int> r7 = t2 . Search ( "kokos" );
 // 4 9

CIndex <string> t3 ( "aaaaaaau aaauaaaau" );
set<int> r8 = t3 . Search ( "aa" );
 // 0 1 2 3 4 5 9 10 13 14 15
set<int> r9 = t3 . Search ( "aaa" );
 // 0 1 2 3 4 9 13 14
set<int> r10 = t3 . Search ( "aaaa" );
 // 0 1 2 3 13

CIndex <string> t4 ( "automatIc authentication automotive auTOmation raut" );
set<int> r11 = t4 . Search ( "auto" );
 // 0 25
set<int> r12 = t4 . Search ( "aut" );
 // 0 10 25 48
set<int> r13 = t4 . Search ( "tic" );
 // 16
set<int> r14 = t4 . Search ( "trunk" );
 //
set<int> r15 = t4 . Search ( "a" );
 // 0 5 10 19 25 36 41 48
set<int> r16 = t4 . Search ( "" );
 // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 
 // 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50

CIndex <string, bool(*)(const char &, const char & )> t5 ( "automatIc authentication automotive auTOmation raut", upperCaseCompare );
set<int> r17 = t5 . Search ( "auto" );
 // 0 25 36
set<int> r18 = t5 . Search ( "aut" );
 // 0 10 25 36 48
set<int> r19 = t5 . Search ( "tic" );
 // 6 16
set<int> r20 = t5 . Search ( "trunk" );
 //
set<int> r21 = t5 . Search ( "a" );
 // 0 5 10 19 25 36 41 48
set<int> r22 = t5 . Search ( "" );
 // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 
 // 26 27 28 29 30 31 32 33 34 35 36 37 38 39 40 41 42 43 44 45 46 47 48 49 50

CIndex <list<string>, CStrComparator> t6 ( list<string>{ "Hello", "world", "test", "this", "foo", "TEsT", "this", "done" }, CStrComparator ( false ) );
set<int> r23 = t6 . Search ( list<string>{"test", "this", "foo"} );
 // 2
set<int> r24 = t6 . Search ( list<string>{"test", "this"} );
 // 2

CIndex <list<string>, CStrComparator> t7 ( list<string>{ "Hello", "world", "test", "this", "foo", "TEsT", "this", "done" }, CStrComparator ( true ) );
set<int> r25 = t7 . Search ( list<string>{"test", "this", "foo"} );
 // 2
set<int> r26 = t7 . Search ( list<string>{"test", "this"} );
 // 2 5
