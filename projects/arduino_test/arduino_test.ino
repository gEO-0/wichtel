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
