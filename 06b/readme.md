Úkol je vylepšením jednoduší varianty zadání DNS. Vylepšení spočívá v přidání dalších typů záznamů a v možnosti skládat zóny hierarchicky.

Úlohu je vhodné řešit až po odladění jednodušší varianty. Pokud je objektový návrh vymyšlen správně, je rozšíření na tuto variantu snadné - stačí implementovat přidané třídy a upravit výpisy. Přidávané třídy jsou:

CRecSPF
Tato třída reprezentuje záznam typu SPF (volitelný záznam udávající, ze kterých adres je odesílaná pošta). Záznam může sloužit jako nápověda při rozeznávání spamu. Protože odesilatelů pošty může být více, záznam musí umožnit vložit více adres (řetězců). Rozhraní proto bude:

konstruktor
připraví novou instanci záznamu ze zadaného jména. Seznam adres je vytvořen jako prázdný.
Name()
metoda vrátí jméno ze záznamu.
Type()
metoda vrátí typ záznamu (zde SPF).
Add()
metoda přidá další adresu do seznamu.
zobrazení ve streamu
Záznam musí jít zobrazit do zadaného výstupního streamu (viz ukázka), zobrazení je včetně odřádkování.
další
do rozhraní můžete přidat další metody podle potřeby.
CRecCNAME
Tato třída reprezentuje alias (odkaz, obdobu symbolického linku v systému souborů). Odlišné je však chování: pokud pro nějaké jméno v zóně existuje CNAME, nesmí pro toto jméno v dané zóně existovat žádný jiný záznam (záznamy A/AAAA/MX/SPF mohly existovat ve více výskytech). Rozhraní třídy je:

konstruktor
připraví novou instanci záznamu ze zadaného jména a jména odkazovaného záznamu.
Name()
metoda vrátí jméno ze záznamu.
Type()
metoda vrátí typ záznamu (zde CNAME).
zobrazení ve streamu
Záznam musí jít zobrazit do zadaného výstupního streamu (viz ukázka), zobrazení je včetně odřádkování.
další
do rozhraní můžete přidat další metody podle potřeby.
CZone
Tato třída reprezentuje kolekci DNS záznamů pro nějakou zónu. V rozšířené variantě půjde tyto objekty vkládat do jiných zón a tím vytvářet hierarchický systém jmen. Vložené zóny se chovají podobně jako CNAME - nesmí kolidovat jméno subzóny a jméno jiného záznamu v zóně.

S možností vkládat zóny hierarchicky souvisí i rozšíření metody Search. Metoda musí umět vyhledávat záznamy hierarchicky podle zadaného vstupu. Podobně jako u verze DNS 1 půjde hodnotu navrácenou metodou Search zobrazit ve streamu, zjistit počet záznamů (metoda Count) a zpřístupnit jednotlivé záznamy operací indexace. Zpřístupněním záznamů a jejich přetypováním musíme získat přístup k celému rozhraní CRecA, CRecAAAA, CRecMX, CRecCNAME, CRecSPF resp. CZone (viz ukázky).

Podobně jako v jednodušší variantě i zde máte k dispozici archiv se základem řešení, sadou testovacích dat a s požadovanými výsledky.