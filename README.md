# pr0gramm Wichteln 2019

Hallo **useruser**!

Ich hoffe dir hat mein Wichtelpaket bis hierhin gefallen. Die folgenden Kapitel sollten viele deiner Fragen über das *Programmieren*, das *Arduino-Board* und den *Floppotron* klären :) Falls nicht schreib mir einfach ne pm ;)

Wenn du jetzt erstmal das Floppylaufwerk zum musizieren bringen willst dann gehe einfach zum Kapitel [Der Floppotron](#Der-Floppotron) ;)


# Inhaltsverzeichnis
1. [Was ist das hier?](#Was-ist-das-hier?)
2. [Wie und wo fange ich mit Programmieren am besten an?](#Wie-und-wo-fange-ich-mit-Programmieren-am-besten-an?)
2. [Quickstart: Arduino](#Quickstart-Arduino)
3. [Der Floppotron](#Der-Floppotron)
---

## Was ist das hier?
Erstmal zur Website selbst: GitHub stellt seinen Nutzern die Möglichkeit bereit in sogenannten *Repositories* den Quellcode ihrer Softwareprojekte zu verwalten. Dafür wird das Versionsverwaltungssystem *Git* genutzt, was jedoch erstmal uninteressant ist. 

Viel wichtiger sind die *Arduino-Projekte* die sich in den Dateien und Verzeichnisse hier verbergen, sowie dieses Dokument. Letzters soll dir als Startrampe in die Welt des Programmieren dienen :) 

## Wie und wo fange ich mit Programmieren am besten an?
Das ist eine sehr gute Frage zu der es wahrscheinlich keine richtige Antwort gibt. Es gibt sehr viele Programmiersprachen von denen du sicherlich schonmal irgendwo etwas gehört hast. Am [beliebtesten](https://fossbytes.com/most-popular-programming-languages/) sind:

* [C++](https://www.wikiwand.com/de/C%2B%2B): von C++ in seiner "Reinform" würde ich als Anfänger abraten. Auf Arduinos kann man da ne Ausnahme machen, das ist deutlich einfacher zu lernen ;)
* [Java](https://www.wikiwand.com/de/Java_(Programmiersprache)): Meiner Meinung nach für Anfänger gut geeignet. Es gibt sehr gute Tutorials auf YouTube die dich in das Thema Java einführen. 
* [Python](https://www.wikiwand.com/de/Python_(Programmiersprache)): Ebenfalls sehr gut für Einsteiger geeignet. Ein kurzes Python-Programm schreibt man schneller, da es mit deutlich weniger Overhead kommt.

Was du garantiert brauchen wirst sind gute Englischkenntnisse, da die meisten Inhalte auf Englisch sind. Die geeignetste Anlaufstelle sind wahrscheinlich YouTube-Tutorials. Hier werden dir eigentlich alles Schritt für Schritt erklärt. Falls doch mal etwas unklar ist, hilft meistens eine Google-Suche.

### Tutorials:
* Arduino: ***←** Fang am besten hier an :) Java und Python kannst du dir anschauen wenn es dich interessiert*
    * [You can learn Arduino in 15 minutes](https://www.youtube.com/watch?v=nL34zDTPkcs) 
    * [Arduino Course for Absolute Beginners](https://www.youtube.com/playlist?list=PLZfay8jtbyJt6gkkOgeeapCS_UrsgfuJA)
    * [Die wesentlichen Bestandteile der Arduino-Programmiersprache](https://www.arduino.cc/reference/de/)
* Java: 
    * [Java Tutorial for Beginners [2019]](https://www.youtube.com/watch?v=eIrMbAQSU34)
* Python:
    * [Lerne Python - Komplett Kurs für Anfänger](https://www.youtube.com/watch?v=rfscVS0vtbw)


## Quickstart Arduino
Am besten lädst du dir die [Arduino IDE](https://www.arduino.cc/en/Main/Software) für dein Betriebssystem runter. **IDE** steht für **Integrated Development Environment** bzw. *Integrierte Entwicklungsumgebung*. 

Das ist einfach gesagt ein Programm, das dir das Programmieren deutlich erleichtert in dem es beispielsweise deinen geschriebenen Code farblich markiert und dadruch lesbarer macht, oder auch eine Verbindung zum Arduino aufbaut um den Code zu übertragen. So sieht die *IDE* mit einem geöffneten Projekt aus:

![Arduino IDE Bild](imgs\arduino_ide.png)

Sobald du das Programm runtergeladen und gestartet hast, kannst du deinen Arduino (bzw. Elegoo) Uno an deinen Rechner anschließen. Ich bin mir gerade nicht sicher ob er automatisch erkannt wird, deshalb mache sicherheitshalber folgendes:

1. Klicke oben auf den Reiter Werkzeuge und wähle deinen Board-Type aus: **Arduino/Genuino Uno**
    ![Board-Type-Selection](imgs\board_selection.png)
2. Wähle den Port aus über den das Board angeschlossen ist. Ist üblicherweise nur einer, anderenfalls trenne die Verbindung zum Arduino und schaue welcher COM Port verschwunden ist.
    ![Port_Selection](imgs\port_selection.png)

Um zu testen ob alles funktioniert kannst du ein Programm ans Arduino übertragen. Dazu eignet sich der Code unter diesem Abschnitt ;) Dieser Code bringt die eingebaute LED im 500ms Takt zum Blinken. Kopiere das einfach in deine *IDE* und speichere ihn ab.

    /* 
     * Diese Methode wird einmalig und als erstens aufgerufen. Sie dient zur Initialisierung
     */
    void setup() {
        // Der Pin der eingbauten LED soll ein Ausgabepin sein
        pinMode(LED_BUILTIN, OUTPUT);
    }

    /* 
     * Diese Methode wird endlos wiederholt
     */
    void loop() {
        digitalWrite(LED_BUILTIN, HIGH);  // LED anschalten 
        delay(500);                       // Halbe Sekunde (500ms) warten
        digitalWrite(LED_BUILTIN, LOW);   // LED ausschalten
        delay(500);                       // Halbe Sekunde (500ms) warten
    }

 Sobald das erledigt ist klicke auf den Knopf mit dem Pfeil nach rechts:

 ![Controls](imgs\controls.png)

Nun sollte das Programm an deinen Arduino übertragen worden sein und die interne LED blinken :)


## Der Floppotron
Im folgenden Kapitel werden Funktionsweise und Aufbau des Floppotrons näher erläutert.

### Funktionsweise
folgt...

### Aufbau
folgt...


