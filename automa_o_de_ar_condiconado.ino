#include <Wire.h>
#include <Adafruit_LiquidCrystal.h>

// Configuração do LCD I2C com a biblioteca Adafruit_LiquidCrystal
Adafruit_LiquidCrystal lcd_1(0);

const int relayPin = 7;  // Pino do relé
const int ledPin = 13;   // Pino do LED

unsigned long previousMillis = 0;
const long interval = 1000; // Intervalo de 1 segundo

int hours = 18;  // Hora inicial
int minutes = 0; // Minuto inicial
int seconds = 0; // Segundo inicial

int onHour = 18;  // Hora para ligar
int offHour = 18; // Hora para desligar

void setup() {
    // Inicializa o LCD
    lcd_1.begin(16, 2);   
    lcd_1.setBacklight(1);  // Liga o backlight do LCD
    lcd_1.setCursor(0, 0);
    lcd_1.print("Hora: ");
    
    // Configura os pinos de saída
    pinMode(relayPin, OUTPUT);
    
    
    // Inicialmente, desliga o relé e o LED
    digitalWrite(relayPin, LOW); 
    digitalWrite(ledPin, LOW);
}

void loop() {
    unsigned long currentMillis = millis();

    // Atualiza o tempo a cada segundo
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;
        seconds++;

        if (seconds >= 60) {
            seconds = 0;
            minutes++;
        }

        if (minutes >= 60) {
            minutes = 0;
            hours++;
        }

        if (hours >= 24) {
            hours = 0;
        }

        // Exibe a hora no LCD
        lcd_1.setCursor(6, 0);
        if (hours < 10) lcd_1.print("0");
        lcd_1.print(hours);
        lcd_1.print(":");
        if (minutes < 10) lcd_1.print("0");
        lcd_1.print(minutes);
        lcd_1.print(":");
        if (seconds < 10) lcd_1.print("0");
        lcd_1.print(seconds);

        // Liga ou desliga o ar condicionado
        if (hours == onHour && minutes < 1) {
            digitalWrite(relayPin, HIGH);  // Liga o relé (simulando o ar condicionado ligado)
            digitalWrite(ledPin, HIGH);    // Liga o LED
        } else if (hours == offHour && minutes >= 1) {
            digitalWrite(relayPin, LOW);   // Desliga o relé
            digitalWrite(ledPin, LOW);     // Desliga o LED
        }
    }
}
