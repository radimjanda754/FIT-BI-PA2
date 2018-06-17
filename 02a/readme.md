Úkolem je realizovat třídu CTaxRegister, která bude implementovat databázi příjmů a výdajů obyvatelstva.

Toto zadání je rozšířením jednodušší úlohy "Daňový registr I". Doporučujeme nejprve realizovat řešení jednodušší, otestovat jej, odevzdat jej a pak jej rozšířit podle tohoto zadání. Rozšíření spočívá v možnosti identifikovat občana v databázi nejen pomocí jména a adresy, ale i pomocí jednoznačného určeného ID účtu.

Pro plánované důslednější potírání daňových úniků je potřeba vybudovat databázi všech obyvatel, ve které budou archivované jejích příjmy a výdaje. Předpokládáme, že v databázi je zaveden každý občan v okamžiku jeho narození. Od té doby se mu počítají všechny příjmy a všechny výdaje. Záznam je z databáze odstraněn v okamžiku jeho úmrtí. Občan je identifikován svým jménem, adresou a číslem účtu. Číslo účtu je unikátní přes celou databázi. Jména a adresy se mohou opakovat, ale dvojice (jméno, adresa) je opět v databázi unikátní. Tedy v databázi může být mnoho jmen Jan Novak, mnoho lidí může mít adresu Hlavni 60, ale Jan Novak bydlící na adrese Hlavni 60 může být v databázi pouze jeden.

Veřejné rozhraní je uvedeno níže. Obsahuje následující:

Konstruktor bez parametrů. Tento konstruktor inicializuje instanci třídy tak, že vzniklá instance je zatím prázdná (neobsahuje žádné záznamy).
Destruktor. Uvolňuje prostředky, které instance alokovala.
Metoda Birth(Name, Addr, Acct) přidá do existující databáze další záznam. Parametry Name a Addr reprezentují jméno a adresu občana, parametr Acct udává číslo účtu. Metoda vrací hodnotu true, pokud byl záznam přidán, nebo hodnotu false, pokud přidán nebyl (protože již v databázi existoval záznam se stejným jménem a adresou, nebo záznam se stejným číslem účtu).
Metoda Death (Name, Addr) odstraní záznam z databáze. Parametrem je jednoznačná identifikace pomocí jména a adresy. Pokud byl záznam skutečně odstraněn, vrátí metoda hodnotu true. Pokud záznam neodstraní (protože neexistoval občan s touto identifikací), vrátí metoda hodnotu false.
Metody Income zaznamenají na účet pro daného občana příjem ve výši Amount. Varianty jsou dvě - občan je buď identifikován svým jménem a adresou, nebo identifikátorem jeho účtu. Pokud metoda uspěje, vrací true, pro neúspěch vrací false (neexistující občan/účet).
Metody Expense zaznamenají na účet daného občana výdaj ve výši Amount. Varianty jsou dvě - občan je buď identifikován svým jménem a adresou, nebo identifikátorem jeho účtu. Pokud metoda uspěje, vrací true, pro neúspěch vrací false (neexistující občan/účet).
Metoda Audit ( Name, Addr, Acct, SumIncome, SumExpense ) vyhledá pro občana se zadaným jménem a adresou a všechny dostupné informace (účet, součet příjmů a součet výdajů). Nalezené informace uloží do zadaných výstupních parametrů. Metoda vrátí true pro úspěch, false pro selhání (neexistující číslo účtu).
Odevzdávejte soubor, který obsahuje implementovanou třídu CTaxRegister. Třída musí splňovat veřejné rozhraní podle ukázky - pokud Vámi odevzdané řešení nebude obsahovat popsané rozhraní, dojde k chybě při kompilaci. Do třídy si ale můžete doplnit další metody (veřejné nebo i privátní) a členské proměnné. Odevzdávaný soubor musí obsahovat jak deklaraci třídy (popis rozhraní) tak i definice metod, konstruktoru a destruktoru. Je jedno, zda jsou metody implementované inline nebo odděleně. Odevzdávaný soubor nesmí kromě implementace třídy CTaxRegister obsahovat nic jiného, zejména ne vkládání hlavičkových souborů a funkci main (funkce main a vkládání hlavičkových souborů může zůstat, ale pouze obalené direktivami podmíněného překladu jako v ukázce níže).

Třída je testovaná v omezeném prostředí, kde je limitovaná dostupná paměť (dostačuje k uložení seznamu) a je omezena dobou běhu. Implementovaná třída se nemusí zabývat kopírujícím konstruktorem ani přetěžováním operátoru =. V této úloze ProgTest neprovádí testy této funkčnosti.

Implementace třídy musí být efektivní z hlediska nároků na čas i nároků na paměť. Jednoduché lineární řešení nestačí (pro testovací data vyžaduje čas přes 5 minut). Předpokládejte, že narození a úmrtí jsou řádově méně časté než ostatní operace. Proto vyhovuje řešení s polem seřazených hodnot, kde vyhledávání probíhá půlením intervalu s logaritmickou složitostí. Méně časté operace vkládání a výmaz je pak doporučeno implementovat postupem, který v logaritmickém čase najde pozici vkládaného/odebíraného prvku a pak v lineárním čase posune obsah pole.

Pro uložení hodnot alokujte pole dynamicky případně použijte STL. Pozor Pokud budete pole alokovat ve vlastní režii, zvolte počáteční velikost malou (např. tisíc prvků) a velikost zvětšujte/zmenšujte podle potřeby. Při zaplnění pole není vhodné alokovat nové pole větší pouze o jednu hodnotu, takový postup má obrovskou režii na kopírování obsahu. Je rozumné pole rozšiřovat s krokem řádově tisíců prvků, nebo geometrickou řadou s kvocientem ~1.5 až 2.

Pokud budete používat STL, nemusíte se starat o problémy s alokací. Pozor - v STL máte zakázané kontejnery map.

Požadované veřejné rozhraní třídy:

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
   public:
         CTaxRegister ( void );
        ~CTaxRegister ( void );
    bool Birth        ( const string    & name,
                        const string    & addr,
                        const string    & account );
    bool Death        ( const string    & name,
                        const string    & addr );
    bool Income       ( const string    & account,
                        int               amount );
    bool Income       ( const string    & name,
                        const string    & addr,
                        int               amount );
    bool Expense      ( const string    & acount,
                        int               amount );
    bool Expense      ( const string    & name,
                        const string    & addr,
                        int               amount );
    bool Audit        ( const string    & name,
                        const string    & addr,
                        string          & account,
                        int             & sumIncome,
                        int             & sumExpense ) const;
    // todo 
 };
Ukázka použití třídy:

bool   status;
string acct;
int    sumIncome, sumExpense;

CTaxRegister b1;
status = b1 . Birth ( "John Smith", "Oak Road 23", "123/456/789" );
// status = true
status = b1 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" );
// status = true
status = b1 . Birth ( "Peter Hacker", "Main Street 17", "634oddT" );
// status = true
status = b1 . Birth ( "John Smith", "Main Street 17", "Z343rwZ" );
// status = true
status = b1 . Income ( "Xuj5#94", 1000 );
// status = true
status = b1 . Income ( "634oddT", 2000 );
// status = true
status = b1 . Income ( "123/456/789", 3000 );
// status = true
status = b1 . Income ( "634oddT", 4000 );
// status = true
status = b1 . Income ( "Peter Hacker", "Main Street 17", 2000 );
// status = true
status = b1 . Expense ( "Jane Hacker", "Main Street 17", 2000 );
// status = true
status = b1 . Expense ( "John Smith", "Main Street 17", 500 );
// status = true
status = b1 . Expense ( "Jane Hacker", "Main Street 17", 1000 );
// status = true
status = b1 . Expense ( "Xuj5#94", 1300 );
// status = true
status = b1 . Audit ( "John Smith", "Oak Road 23", acct, sumIncome, sumExpense );
// status = true, acct = "123/456/789", sumIncome=3000, sumExpense=0
status = b1 . Audit ( "Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense );
// status = true, acct = "Xuj5#94", sumIncome=1000, sumExpense=4300
status = b1 . Audit ( "Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense );
// status = true, acct = "634oddT", sumIncome=8000, sumExpense=0
status = b1 . Audit ( "John Smith", "Main Street 17", acct, sumIncome, sumExpense );
// status = true, acct = "Z343rwZ", sumIncome=0, sumExpense=500
status = b1 . Death ( "John Smith", "Main Street 17" );
// status = true

CTaxRegister b2;
status = b2 . Birth ( "John Smith", "Oak Road 23", "123/456/789" );
// status = true
status = b2 . Birth ( "Jane Hacker", "Main Street 17", "Xuj5#94" );
// status = true
status = b2 . Income ( "634oddT", 4000 );
// status = false
status = b2 . Expense ( "John Smith", "Main Street 18", 500 );
// status = false
status = b2 . Audit ( "John Nowak", "Second Street 23", acct, sumIncome, sumExpense );
// status = false
status = b2 . Death ( "Peter Nowak", "5-th Avenue" );
// status = false
status = b2 . Birth ( "Jane Hacker", "Main Street 17", "4et689A" );
// status = false
status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" );
// status = false
status = b2 . Death ( "Jane Hacker", "Main Street 17" );
// status = true
status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "Xuj5#94" );
// status = true
status = b2 . Audit ( "Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense );
// status = true, acct = "Xuj5#94", sumIncome=0, sumExpense=0
status = b2 . Birth ( "Joe Hacker", "Elm Street 23", "AAj5#94" );
// status = false