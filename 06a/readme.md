Úkolem je realizovat sadu tříd, které budou simulovat datové struktury použité v DNS serveru.

DNS je síťová služba, která slouží k překladu adres z textové do binární podoby. Například adresa progtest.fit.cvut.cz je v současnosti přeložena na adresu 147.32.232.142. Tento překlad je realizován záznamem typu A (IPv4 adresa) v zóně fit.cvut.cz pro jméno progtest. DNS umožňuje ukládat i další informace (AAAA pro IPv6 adresy, MX pro informaci o poštovním serveru, CNAME pro aliasy, ...). Pro jedno jméno lze zaznamenat více záznamů různého typu (např. lze zadat A a zároveň AAAA záznam, viz např. imap.fit.cvut.cz), dokonce lze zadat více záznamů stejného typu s různým obsahem (například lze k jednomu jménu zaznamenat více záznamů typu A s různými adresami, klient náhodnou volbou adresy rozkládá zátěž, používá např. google.cz). Nepřípustné je pouze duplikování identických záznamů.

Reálné DNS je distribuované a redundantní. Naše implementace bude realizovat zjednodušení, které pomocí tříd realizuje ukládané záznamy a kontejnerový objekt, který tyto záznamu umožní vkládat, mazat a vyhledávat. Při implementaci se navíc omezíme pouze na záznamy A, AAAA a MX.

Úkolem je realizovat třídy CRecA, CRecAAAA a CRecMX, které budou reprezentovat záznamy v DNS. Dále je pak úkolem realizovat třídu CZone, která bude sloužit jako kontejner DNS záznamů. Při realizaci si můžete (a budete muset) vytvořit i další vlastní třídy. Dále budete používat třídy již připravené: CIPv4 a CIPv6 pro reprezentaci adres a třídy InvalidIPAddressFormatException a InvalidIndexException pro reprezentaci výjimek. Připravené třídy jsou realizované v testovacím prostředí a v přiloženém archivu máte jejich základní implementaci, kterou budete potřebovat při ladění vašich tříd.

CRecA
Třída CRecA reprezentuje záznam typu A - překlad jména na IPv4 adresu. Rozhraní třídy musí obsahovat:

konstruktor
připraví novou instanci záznamu ze zadaného jména a objektu IPv4 adresy.
Name()
metoda vrátí jméno ze záznamu.
Type()
metoda vrátí typ záznamu (zde A).
zobrazení ve streamu
Záznam musí jít zobrazit do zadaného výstupního streamu (viz ukázka), zobrazení je včetně odřádkování.
další
do rozhraní můžete přidat další metody podle potřeby.
CRecAAAA
Třída CRecAAAA reprezentuje záznam typu AAAA - překlad jména na IPv6 adresu. Rozhraní třídy musí obsahovat:

konstruktor
připraví novou instanci záznamu ze zadaného jména a objektu IPv6 adresy.
Name()
metoda vrátí jméno ze záznamu.
Type()
metoda vrátí typ záznamu (zde AAAA).
zobrazení ve streamu
Záznam musí jít zobrazit do zadaného výstupního streamu (viz ukázka), zobrazení je včetně odřádkování.
další
do rozhraní můžete přidat další metody podle potřeby.
CRecMX
Třída CRecMX reprezentuje záznam typu MX - mail server pro zadanou doménu. Rozhraní třídy musí obsahovat:

konstruktor
připraví novou instanci záznamu ze zadaného jména, jména mail serveru a jeho priority.
Name()
metoda vrátí jméno ze záznamu.
Type()
metoda vrátí typ záznamu (zde MX).
zobrazení ve streamu
Záznam musí jít zobrazit do zadaného výstupního streamu (viz ukázka), zobnrazení je včetně odřádkování.
další
do rozhraní můžete přidat další metody podle potřeby.
CZone
Třída CZone reprezentuje zónu - kolekci DNS záznamů. Rozhraní musí umožňovat:

konstruktor
připraví novou prázdnou instanci pro zónu zadaného jména,
Add()
metoda přidá záznam (A/AAAA/MX) do zadané zóny. Nový záznam je vždy přidáván na konec seznamu. Metoda vrátí true pro úspěch, false pro neúspěch (pokud by identický záznam v zóně již existoval).
Del()
metoda smaže zadaný záznam. Kromě odstranění záznamu metoda nesmí měnit pořadí záznamů v zóně obsažených. Metoda vrátí true pro úspěch, false pro neúspěch (identický záznam v zóně neexistuje).
Search()
metoda vyhledá v zóně záznam (záznamy) zadaného jména. S hodnotou, kterou metoda Search vrátí, půjde provádět následující operace:
zobrazení ve výstupním streamu - záznamy se zobrazí v podobě dle ukázek. Pořadí záznamů bude respektovat pořadí při vkládání,
aplikováním metody Count na výsledek půjde zjistit počet nalezených záznamů,
aplikováním indexu půjde zpřístupnit jednotlivé nalezené záznamy, tedy na výsledek indexování půjde aplikovat metody Type, Name a výstupní operátor. Přetypováním hodnoty získané indexací pak půjde zpřístupnit i případné další metody z rozhraní CRecA/CRecAAAA/CRecMX. Použití je zřejmé z ukázek. Navíc, aplikace indexu mimo meze povede k vyhození výjimky InvalidIndexException.
zobrazení ve streamu
zónu musí jít zobrazit do zadaného výstupního streamu, zobrazí se všechny obsažené záznamy (viz ukázka). Pořadí respektuje pořadí záznamů při vkládání.
kopírování
objekty zón se musí správně kopírovat/přiřazovat.
další
do rozhraní můžete přidat další metody podle potřeby.
Než začnete programovat věnujte dostatek času návrhu řešení. Zaměřte se na objektový návrh tak, abyste zbytečně neduplikovali kód. Správné řešení vyžaduje polymorfismus, testovací prostředí navíc zkoumá, zda jste třídy navrhli správně. Řešení bez polymorfismu nepůjde zkompilovat. Nepoužívejte RTTI (typeid nebude fungovat, úmyslně chybí hlavičkový soubor typeinfo), pokud možno nepoužívejte dynamic_cast. Pokud návrh podceníte, budete muset používat mnoho zbytečných větvení a výsledný program bude zbytečně dlouhý, nepřehledný a neodladitelný.

Odevzdávejte zdrojový kód s implementací požadovaných tříd (a dalších Vašich podpůrných tříd). Využijte přiložený archiv. Naleznete v něm soubor solution.cpp, do kterého můžete umístit Vaši implementaci, hlavičkový soubor common.h s implementací pomocných tříd a soubor tests.inc s testy a očekávanými výsledky. Pokud implementaci požadovaných tříd umístíte do solution.cpp a zachováte bloky podmíněného překladu, můžete tento soubor rovnou odevzdávat Progtestu.

Pro zvládnutí povinných testů postačí implementace používající naivní algoritmy. Ke zvládnutí bonusu je potřeba rychlé vyhledávání v zóně, kde je mnoho záznamů.

Ukázka běhu a požadované rozhraní není tentokrát vloženo do textu zadání. Naleznete jej v přiloženém archivu.