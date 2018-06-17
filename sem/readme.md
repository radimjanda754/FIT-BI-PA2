Kalkulačka s neomezenou přesností

Vytvořte aplikaci implementující kalkulačku s neomezenou přesností.

Kalkulačka musí implementovat:

práci s celými i desetinnými čísly
základní operace: sčítání, odčítání a násobení
pro celá čísla navíc celočíselné dělení a zbytek
efektivní paměťovou reprezentaci (jeden znak pro jednu číslici není akceptovatelné)
proměnné (uložení výrazu do proměnné, využití proměnné ve výpočtu)
Výraz je tvořen závorkami, čísly, proměnnými a operátory + - *. Závorky mohou být ve výrazu libovolně vnořené.

Umožněte uložit stav kalkulátoru (proměnné, historie výrazů) do souboru a zase jej opětovně načíst. Navrhněte vhodnou reprezentaci.

Použití polymorfismu (doporučeně)

typ čísla: proměnná, celé, desetinné
operace: sčítání, odčítání, násobení, dělení, funkce, ...
paměťová reprezentace: int (pro malá čísla), pole intů, zápis dvojice index exponentu a hodnota (pro čísla s řídkým výskytem číslic)
Další informace:

parsování výrazu (shunting-yard algoritmus) http://en.wikipedia.org/wiki/Shunting-yard_algorithm