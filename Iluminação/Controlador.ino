#include <IRremote.h>

//Pinos de entrada
int RECV_PIN = 10; //Entrada decodificador de controle

//Pinos de saída
int led = 11; //LEDs vermelhos

//Inicialização das variáveis
int iVer = 0; //LEDs começam desligados
IRrecv irrecv(RECV_PIN);
decode_results results;

void setup() {
      Serial.begin(9600);      // Inicia saída serial
      irrecv.enableIRIn();     // Start the receiver

      // Pisca luzes para determinar que ligou
      pinMode(led, OUTPUT);    // initialize the digital pin as an output.
      digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
      delay(100);              // wait for a 1/10 second
      digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
}

void loop() {
    if (irrecv.decode(&results)) {
        unsigned long resultado = results.value;
        Serial.println(resultado);
        irrecv.resume(); // Receive the next value
        if      (resultado == 16236607) { // LIGA
            iVer = 10;
        }
        else if (resultado == 16203967) { // DESLIGA
            iVer = 0;
        }
        else if (resultado == 16187647) { // AUMENTA INTENSIDADE
            if (iVer < 10)
            iVer++;
        }
        else if (resultado == 16220287) { // DIMINUI INTENSIDADE
            if (iVer > 0)
                iVer--;
        }
        // Imprime intesidade atual
        Serial.print("Verm: ");
        Serial.println(iVer);

    }
    digitalWrite(led, LOW);  // turn the LED off by making the voltage LOW
    delay((10 - iVer));
    digitalWrite(led, HIGH); // turn the LED on (HIGH is the voltage level)
    delay(iVer);
}
/*
digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)

digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW

*/
