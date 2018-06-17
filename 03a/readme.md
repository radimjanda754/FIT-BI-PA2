Úkolem je realizovat třídu CBigInt, která bude reprezentovat celá čísla (kladná i záporná) s (téměř) neomezeným rozsahem.

Celá čísla typu int, long long int, ... mají fixní velikost, tedy omezený rozsah. Pokud potřebujeme výpočty ve větším rozsahu hodnot, musíme si pro ně vytvořit vlastní datový typ. Třída implementující tento datový typ bude číslo ukládat ve vnitřní reprezentaci, kterou bude podle potřeby natahovat (alokovat větší prostor). Vaším úkolem je takovou třídu realizovat. Pro zjednodušení implementace jsou následující omezení:

Ukládáme pouze celá čísla (kladná, nulu i záporná). Nezabýváme se desetinnou částí.
Z matematických operací implementujeme pouze sčítání a násobení.
Realizovaná třída tedy musí splňovat následující rozhraní:

konstruktor implicitní
inicializuje objekt, který bude reprezentovat hodnotu 0.
konstruktor s parametrem celého čísla int
inicializuje objekt, reprezentující toto číslo.
konstruktor s parametrem řetězce (ASCIIZ)
inicializuje objekt s hodnotou, jejíž desítková reprezentace je v předávaném řetězci.
kopírující konstruktor
bude implementován, pokud to vnitřní struktury Vaší třídy vyžadují.
destruktor
bude implementován, pokud to vnitřní struktury Vaší třídy vyžadují.
přetížený operátor =
bude umožňovat přiřazení z celého čísla, řetězce a jiné instance CBigInt.
operátor <<
bude umožňovat výstup objektu do C++ streamu (desítková reprezentace, bez zbytečných úvodních nul).
operátor >>
bude umožňovat načtení ze vstupního streamu (vstup bude v desítkovém zápisu).
operátor +
umožní sečíst dvě čísla typu CBigInt, a dále CBigInt a celé číslo a CBigInt a ASCIIZ řetězec reprezentující celé číslo.
operátor +=
umožní k číslu CBigInt přičíst jiné číslo CBigInt, celé číslo nebo číslo v podobě ASCIIZ řetězce.
operátor *
umožní vynásobit dvě čísla typu CBigInt, a dále CBigInt a celé číslo a CBigInt a ASCIIZ řetězec reprezentující celé číslo.
operátor *=
umožní číslo typu CBigInt přenásobit jiným číslem CBigInt, celým číslem nebo číslem v podobě ASCIIZ řetězce.
Odevzdávejte zdrojový soubor, který obsahuje Vaší implementaci třídy CBigInt. V odevzdávaném souboru nenechávejte vkládání hlavičkových souborů, Vaše testovací funkce a funkci main. Pokud v souboru chcete ponechat main nebo vkládání hlavičkových souborů, vložte je do bloku podmíněného překladu.

V tomto příkladu není poskytnutý předpis pro požadované rozhraní třídy. Z textového popisu, ukázky použití níže a znalostí přetěžování operátorů byste měli být schopni toto rozhraní vymyslet.

Ukázka použití třídy:
CBigInt       a, b;
istringstream is;
a = 10;
a += 20;  // a = 30 
a *= 5;  // a = 150 
cout << a;  // 150
b = a + 3;  // b = 153 
b = a * 7;  // b = 1050 
cout << a;  // 150

a = 10;
a += -20;  // a = -10 
a *= 5;  // a = -50 
cout << a;  // -50
b = a + 73;  // b = 23 
b = a * -7;  // b = 350 
cout << a;  // -50

a = "12345678901234567890";
a += "-99999999999999999999";  // a = -87654321098765432109 
a *= "54321987654321987654";  // a = -4761556948575111126880627366067073182286 
cout << a;  // -4761556948575111126880627366067073182286
a *= 0;  // a = 0 
cout << a;  // 0
a = 10;
b = a + "400";  // b = 410 
b = a * "15";  // b = 150 
cout << a;  // 10

is . clear ();
is . str ( " 1234" );
is >> b; // b = 1234, is . fail() = 0
is . clear ();
is . str ( " 12 34" );
is >> b; // b = 12, is . fail() = 0
is . clear ();
is . str ( "999z" );
is >> b; // b = 999, is . fail() = 0
is . clear ();
is . str ( "abcd" );
is >> b; // b = 999, is . fail() = 1
Nápověda
Testovací prostředí kontroluje hodnoty ve Vašich objektech tím, že si je zašle do výstupního proudu a kontroluje jejich textovou podobu. Dokud Vám nebude správně fungovat výstup, budou všechny testy negativní.
Operátor pro výstup implementujte správně -- neposílejte data na cout, posílejte je do předaného výstupního proudu. Za výstupem čísla do proudu nepřidávejte odřádkování ani jiné bílé znaky.
Pokud Vám program nejde zkompilovat, ujistěte se, že máte správně přetížené operátory. Zejména si zkontrolujte kvalifikátory const.
V jednoduché variantě lze velká čísla reprezentovat uvnitř třídy jako řetězec jejich desítkové absolutní hodnoty a oddělené znaménko. Sčítání a násobení lze provádět tak, jak jsme se jej učili na základní škole. Tento postup není moc rychlý, ale správně implementované řešení na tomto principu vyhoví všem testům kromě bonusového testu rychlosti.
Bonusový test (rychlost) vyžaduje rychlé násobení. Test spočívá ve výpočtu faktoriálů velkých čísel (např. 5000!). Desítková reprezentace z minulého bodu není vhodná. Lepší výsledky dává binární reprezentace.
Načítání ze streamu musí správně manipulovat s příznakem chyby (fail bit). Chování CBigInt má být stejné jako chování pro celá čísla (čtou se desítkové cifry dokud to lze, úvodní bílé znaky se přeskakují, pokud je načtena alespoň jedna cifra, čtení uspěje). Pokud je na vstupu nečíselná hodnota (nelze načíst ani jednu cifru), musíte nastavit fail bit a nechat v proměnné její nezměněnou původní hodnotu (viz ukázka, hodnota 999). Pro nastavení příznaku chyby se hodí is . setstate (ios::failbit). Dále, pro načtení jednoho znaku dopředu bez jeho faktického odstranění ze streamu se hodí metoda is . peek().
Pokud se v operandu objeví celé číslo reprezentované jako ASCIIZ řetězec (např. operand pro +, +=, *, *=, =, ...), je v testovacím prostředí garantováno, že se skutečně jedná o platný zápis desítkového čísla (obsahuje pouze znaky 0 až 9 a případné znaménko). Pokud chcete mít implementaci zcela robustní, můžete při detekci chyby formátu vyhodit výjimku. Ale tato vlastnost nebude (vzhledem k platným vstupům) testovaná.
Použití třídy předpokládá pouze 4 operátory, ale přetížené pro mnoho datových typů. Navrhněte rozhraní tak, abyste neměli zbytečně dlouhou implementaci. Využijte vlastností C++ (konstruktor uživ. konverze, implicitní parametry).
Při implementaci můžete použít std::vector a std::string. Zbývající třídy z STL ale nejsou dostupné.