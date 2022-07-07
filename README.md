# ESP-Project
Herkansing Project 3 BattleBot

## Follow The Line
**Bestanden**:
- FollowTheLine/Display.h
- FollowTheLine/FollowTheLine.ino
- FollowTheLine/Move.h
- FollowTheLine/Sensor.h

**Beschrijving**:
De robot zal bij het opstarten eerst 5 seconden wachten. Dat doet de robot om de waardes van de LDR sensoren te neutraliseren. Hier wordt er geen gemiddelde van gepakt, omdat de waardes dan te hoog uit kunnen pakken.

Nadat de waardes geneutraliseerd zijn, slaat hij deze op. Hier worden, aan zowel de linker als de rechter sensor, 300 bij op geteld als drempel waarde voor het volgen van de donkere lijn. 

Daarna gaat de robot eerst recht vooruit rijden. Net zolang één van de sensoren de drempelwaarde bereiken, dan draait hij naar links en rechts. De robot is niet in staat rechtdoor over de lijn te volgen. Als oplossing hiervoor draait hij continu naar links en rechts en komt hij langzaam vooruit.

Op deze manier volgt de robot erg nauwkeurig de donkere lijn.

**Mogelijkheden**:
- De robot is in staat om een dunne zwarte lijn te volgen (getest met zwarte klustape van ongeveer 1,5 cm).
- De robot kan op zowel lichte vloeren als donkere vloeren de lijn volgen.
- De robot kan van een lichtere kleur vloer naar een donkere kleur vloer de lijn volgen, hij wordt welliswaar iets minder nauwkeurig (getest van wit naar paars). *LET OP:* van donker naar licht zal niet werken.
- De robot draait zodra de lijn ophoud.

**Voorwaardes**:
1. De robot moet voldoende grip op de banden hebben. Glijden de banden? Gebruik elastiekjes voor om de banden voor grip.
2. De robot moet voldoende stroomtoevoer hebben. Bij het continu opnieuw opstarten van de robot of het niet meer nauwkeurig volgen van de lijn, gebruik nieuwe of volledig opgeladen batterijen.
3. De robot bevat minstens 2 LDR sensoren, 2 motoren en een ESP32 bordje.