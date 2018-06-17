Úkolem je realizovat funkci, která transformuje soubor s popisem rozvržení výuky.

Předpokládáme, že máme uložený seznam učitelů s předměty, které učí. Soubor je textově orientovaný, na každém řádku je zapsáno jméno učitele, dvojtečka a čárkou oddělený seznam vyučovaných předmětů. Jména učitelů i předmětů jsou tvořena výhradně znaky anglické abecedy (malá i velká písmena) a číslicemi. Před a za jmény mohou být bílé znaky (které nehrají žádnou roli, budou přeskočeny). Pokud řádka začíná znakem #, jedná se o komentář (přeskočit řádku). Soubor může vypadat např. takto:

 lada : PA1  ,  PA2,OSY
#toto je komentar
pepa: PA1, PA2
Úkolem programu je načíst takový soubor, zkontrolovat jeho správnost a zapsat obdobný soubor na disk. Ve výstupním souboru bude uveden seznam předmětů, pro každý předmět bude uveden seznam jejich vyučujících. Pro ukázku bude výstupní soubor obsahovat:

OSY: lada
PA1: lada, pepa
PA2: lada, pepa
Výstupní soubor po transformaci bude podobný vstupu. Navíc bude hezky formátovaný:

nebude obsahovat komentáře,
nebude obsahovat zbytečné bílé znaky. Za čárkou a za dvojtečkou bude jedna mezera, ale pouze pokud následuje nějaké slovo,
předměty budou seřazené podle abecedy,
jména vyučujících na řádce budou rovněž seřazena podle abecedy,
za každou řádkou bude odřádkování.
Přepočet seznamu bude mít na starosti funkce s následujícím rozhraním:

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

bool transform  ( const char * inFile,
                  const char * outFile )
 {
   // todo
 }

#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
 {
   // tests
   return 0;
 }
#endif /* __PROGTEST__ */
Parametry funkce jsou:

inFile
jméno vstupního souboru (ASCIIZ řetězec). Funkce může soubor pouze číst, nesmí jej změnit/smazat,
outFile
jméno souboru, do kterého má být uložen výsledný seznam (ASCIIZ řetězec),
návratová hodnota
signalizace úspěchu (true) nebo neúspěchu (false).
Pokud vstupní soubor nelze zpracovat, funkce musí vrátit neúspěch (false). Za chybu považujte:

chybu při práci se souborem (nelze jej číst, zapisovat, neexistuje, ...),
vstupní soubor obsahuje nesprávná data (podoba jmen, správné umístění dvojtečky a čárek),
jména vyučujících ve vstupním souboru nejsou unikátní (jméno vyučujícího se opakuje na více řádcích),
seznam vyučovaných předmětů nějakého vyučujícího obsahuje duplicitní předmět (na řádce nesmí být duplicitní jména předmětů).
Odevzdávejte zdrojový kód, který obsahuje Vaši implementaci požadované funkce. Do odevzdávaného souboru samozřejmě patří ještě další Vaše funkce, které jsou z této funkce volané. Naopak, v odevzdávaném souboru nesmí být vkládání hlavičkových souborů a funkce main(pokud vkládání hlavičkových souborů a funkci main zabalíte do bloku podmíněného překladu, mohou zůstat). Za základ řešení použijte ukázku výše. Ukázku si zkopírujte a doplňte pouze implementaci požadované funkce (případně další Vaše funkce). Pokud zachováte bloky podmíněného překladu, můžete takový soubor odevzdávat Progtestu. V ukázce je zároveň vidět i seznam hlavičkových souborů, které jsou k dispozici v testovacím prostředí.

Pro tuto úlohu nejsou k dispozici ukázky použití funkcí. Význam parametrů a volání funkcí je zřejmé. V přiloženém archivu máte k dispozici sadu testovacích souborů, které budou předkládány Vašim funkcím v základním testu. Vstupní data in_2.txt a in_3.txt jsou neplatná, proto pro ně v archivu neexistují odpovídající výstupní soubory.

Vkládané hlavičkové soubory umožňují použít datové struktury z STL (vector, string, map, set). Jejich použití je možné, ale není povinné. Úlohu lze vyřešit i při použití čistě C konstrukcí a C funkcí pro práci se soubory.