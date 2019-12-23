/* *************** */
/*  Bibliotheken   */
/* *************** */
#include <TimerOne.h>         // Bibliotheken können über die Arduino IDE über den Reiter (Sketch --> Bibliothek einbinden --> Bibliotheken verwalten) installiert und eingebunden werden

/* *************** */
/*   Konstanten    */
/* *************** */
#define TIMER_RESOLUTION 40   // Intervall in dem der Timer auslösen soll --> alle 40 µSekunden
#define STEP_PIN 8            // Der STEP_PIN des Floppys ist an Pin 8 des Arduinos angebunden
#define DIRECTION_PIN 10      // Der DIRECTION_PIN des Floppys ist an Pin 10 des Arduinos angebunden

#define MAX_HEAD_POSITION 82  // Maximale Anzahl an Schritten die der Lesekopf des Floppys in eine Richtung machen kann

/* ************************************************* *
 *           Frequenz und Dauer der Noten            *
 *                                                   *
 *  Diese Werte sind programmatisch erzeugt worden!  *
 *                                                   *
/* ************************************************* */
int noteFrequencies[] = {-1,392, 392, 262, 392, 330, 392, 330, 392, 523, 659, 587, 587, 587, 587, 523, 587, 659, 587, 523, 392, 392, 523, 392, 330, 392, 330, 392, 523, 659, 587, 587, 587, 587, 659, 587, 523, -1, 659, 587, 392, 392, 392, 659, 587, 392, 392, 392, 659, 587, 659, 587, 659, 587, 392, 392, 392, 392, 392, 523, 392, 330, 392, 330, 392, 523, 659, 587, 587, 587, 587, 659, 587, 523, -1, 659, 587, 392, 392, 392, 659, 587, 392, 392, 392, 659, 587, 659, 587, 659, 587, 392, 392, 392, 392, 392, 523, 392, 330, 392, 330, 392, 523, 659, 587, 587, 587, 587, 659, 587, 523};
int noteDurations[] = {100,250,250, 250,250,250,250, 250,250,250,250, 250,125,125,250,125,125, 250,250,250,125,125, 250,250,250,250, 250,250,250,250, 250,125,125,250,125,125,375,250,125, 250,125,125,250,250, 250,125,125,250,250, 250,250,250,250, 250,125,125,250,125,125, 250,250,250,250, 250,250,250,250, 250,125,125,250,125,125,375,250,125, 250,125,125,250,250, 250,125,125,250,250, 250,250,250,250, 250,125,125,250,125,125, 250,250,250,250, 250,250,250,250, 250,125,125,250,125,125,375};
int amountOfNotes = (sizeof(noteFrequencies) / sizeof(int));    // Bestimmt die Gesamtanzahl an Noten

/* *************** */
/*    Variablen    */
/* *************** */
byte headPosition;              // Beinhaltet die momentane Position des Lesekopfs
int headState = LOW;            // Sagt aus ob gerade 5V oder 0V am STEP_PIN anliegen
boolean headingForward = false; // Sagt aus in welche Richtung sich der Lesekopf bewegt

unsigned int currentFloppyNote; // Die zu spielende Floppynote
unsigned int timerTick;         // Zähler im Timer um Floppynote zu spielen
long timeUntilNextNote;         // Zeitstempel ab wann zur nächsten Note gewechselt werden soll

int currentNote;                // Der Index der momentanen Note (für die Arrays 'noteFrequencies' und 'noteDurations')

/*
 * Initialisiert das Programm
 */
void setup() {
  pinMode(STEP_PIN, OUTPUT);            // Den Step-Pin als Ausgabepin setzen
  pinMode(DIRECTION_PIN, OUTPUT);       // Den Direction-Pin als Ausgabepin setzen

  resetHead();                          // Lesekopf des Floppys zurücksetzen

  Timer1.initialize(TIMER_RESOLUTION);  // Timer mit der angegebenen Auflösung initialisieren
  Timer1.attachInterrupt(tick);         // Die aufzurufende Methode definieren die aufgerufen werden soll sobald der Timer bis zur Auflösung gezählt hat. Danach setzt der Timer seinen Zähler automatisch zurück
}


/*
 * Diese Methode wird immer wieder ausgeführt. Deshalb auch der Name 'loop' bzw. Schleife
 */
void loop() {
  if(millis() > timeUntilNextNote){                                 // Ist die momentane Note lang genug gespielt worden und kann jetzt die nächste gespielt werden?
    if(currentNote < amountOfNotes){                                // Ist die momentan zu spielende Note kleiner als die Anzahl an Noten?

      timeUntilNextNote += 20;                                      // Künstliche Pause von 20ms zwischen der momentanen und nächsten Note
      currentFloppyNote = 0;                                        // Spiele keinen Ton
      while(millis() < timeUntilNextNote);                          // Warte die künstliche Pause ab...

      currentNote++;                                                // Die nächste Note ist nun die momentane Note

      currentFloppyNote = calculateFloppyNote();                    // Berechne die FloppyNote
      timeUntilNextNote = millis() + noteDurations[currentNote];    // Berechne die Dauer wie lange die momentane Note gespielt werden soll
    } else {                                                        // Sollte die momentan zu spielnde Note größer oder gleich sein als die Anzahl an Noten:
      currentFloppyNote = 0;                                        // Spiele keinen Ton
    }
  }
}

/*
 * Interrupt, wird vom Timer zuverlässig alle 40 µSekunden aufgerufen
 */
void tick() {
  if (currentFloppyNote > 0){             // Gibt es eine Note die gespielt werden kann?

    timerTick++;                          // Zähle den timerTick-Counter hoch

    if (timerTick >= currentFloppyNote){  // Sobald die Notendauer erreicht ist
      stepHead();                         // Bewege den Lesekopf
      timerTick = 0;                      // Setze den timerTick-Counter zurück
    }
  }
}

/*
 * Berechnet eine 'Floppynote'. Das ist die Zeit in der der Motor des Floppylaufwerks einmal an und ausgeschaltet werden muss, um den gewünschten Ton zu erzeugen.
 */
int calculateFloppyNote(){
  int durationInMicroSeconds = (1000000 / noteFrequencies[currentNote]);  // Eine Sekunde hat eine Millionen Microsekunden. Um die Dauer der Note in µSekunden zu ermitteln, muss man die 1000000 durch die Frequenz der Note teilen
  return durationInMicroSeconds / (TIMER_RESOLUTION * 0.5);               // Da der Timer nur alle 40µSekunden die tick()-Methode aufruft, wird die Dauer in µSekunden noch durch die Auflösung des Timers geteilt. Da der Lesekopf sich nur beim Wechsel von LOW auf HIGH bewegt wird dieser Wert nochmal halbiert
}

/*
 * Zustand des Lesekopf toggeln und dabei auf Position und Richtung achten
 */
void stepHead() {
  checkHeadDirection();                                       // Überprüfe ob sich der Lesekopf am Anfang/Ende befindet
  digitalWrite(DIRECTION_PIN, headingForward ? LOW : HIGH);   // Setze die Richtung (LOW = vorwärts, HIGH = rückwärts)

  if(headState == LOW){                                       // Der Kopf bewegt sich nur beim Wechsel von LOW auf HIGH
    headPosition += (headingForward ? 1 : -1);                // Inkrementiere bwz. dekrementiere die Position mit jeder Bewegung (abhängig von der Bewegungsrichtung)
  }

  digitalWrite(STEP_PIN, headState);                          // Setze LOW/HIGH am STEP_PIN um den Lesekopf zu bewegen (Bewegen tut er sich jedoch nur beim Wechsel von LOW auf HIGH)
  headState = ~headState;                                     // Invertiere den Zustand des Lesekopfs (HIGH wird zu LOW bzw. LOW wird zu HIGH)
}

/*
 * Sorge dafür das die Bewegungsrichtung gewechselt wird, sobald der Lesekopf bzw. Motor am Ende/Anfang angekommen ist
 */
void checkHeadDirection(){
  if(headingForward){                         // Bewegt sich der Lesekopf gerade nach vorne?
    if(headPosition >= MAX_HEAD_POSITION){    // und ist er am Ende angelangt?
      headingForward = false;                 // dann soll er sich ab sofort nach hinten bewegen
    }
  } else {                                    // Bewegt sich der Lesekopf gerade nach hinten?
    if(headPosition <= 0){                    // und ist er am Anfang angelangt?
      headingForward = true;                  // dann soll er sich ab sofort nach vorde bewegen
    }
  }
}


/*
 * Setzt den Lesekopf in die Startposition (nach ganz hinten fahren)
 */
void resetHead() {
  digitalWrite(DIRECTION_PIN, HIGH);          // Der Lesekopf soll sich nach hinten bewegen
  digitalWrite(STEP_PIN, LOW);                // Der Lesekopf bewegt sich nur beim Wechsel von LOW auf HIGH

  for(int i = 0; i < MAX_HEAD_POSITION; i++){ // Führe folgendes MAX_HEAD_POSITION-mal aus:
     digitalWrite(STEP_PIN, HIGH);            // Setze den Zustand des STEP_PIN auf HIGH
     delay(5);                                // Warte bis der Lesekopf sich bewegt hat
     digitalWrite(STEP_PIN, LOW);             // Setze den Zustand des STEP_PIN wieder auf LOW
  }

  headPosition = 0;                           // Da der Lesekopf am Ende angelangt ist, kann die Position zurückgesetzt werden
  headingForward = true;                      // Der Lesekopf bewegt sich wieder vorwärts

  digitalWrite(DIRECTION_PIN, LOW);           // Der Lesekopf soll sich nach vorne bewegen

  delay(1000);                                // Warte 1 Sekunde
}