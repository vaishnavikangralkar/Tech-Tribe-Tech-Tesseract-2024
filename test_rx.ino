
// SimpleRx - the slave or the receiver

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define CE_PIN   9
#define CSN_PIN 10

#define RED_LED_PIN_1 2
#define GREEN_LED_PIN_1 3

#define RED_LED_PIN_2 4
#define GREEN_LED_PIN_2 5

#define RED_LED_PIN_3 6
#define GREEN_LED_PIN_3 7


int cnt1 = 0;

const byte thisSlaveAddress[5] = {'R','x','A','A','A'};

RF24 radio(CE_PIN, CSN_PIN);

uint8_t dataReceived; // this must match dataToSend in the TX
bool newData = false;

//===========

void setup() {

    Serial.begin(9600);

    Serial.println("SimpleRx Starting");
    radio.begin();
    radio.setDataRate( RF24_250KBPS );
    radio.openReadingPipe(1, thisSlaveAddress);
    radio.startListening();
    pinMode(GREEN_LED_PIN_1, OUTPUT);
    pinMode(GREEN_LED_PIN_2, OUTPUT);
    pinMode(GREEN_LED_PIN_3, OUTPUT);
  
    pinMode(RED_LED_PIN_1, OUTPUT);
    pinMode(RED_LED_PIN_2, OUTPUT);
    pinMode(RED_LED_PIN_3, OUTPUT);
   
}

//=============

void loop() {
    getData();
    showData();
}

//==============

void getData() {
    if ( radio.available() ) {
        radio.read( &dataReceived, sizeof(dataReceived) );
        newData = true;

        if (dataReceived == 0)
        {
          digitalWrite(GREEN_LED_PIN_1, HIGH);
          digitalWrite(RED_LED_PIN_1, LOW);
          
          digitalWrite(GREEN_LED_PIN_2, LOW);
          digitalWrite(RED_LED_PIN_2, HIGH);

          digitalWrite(GREEN_LED_PIN_3, LOW);
          digitalWrite(RED_LED_PIN_3, HIGH);

          delay(7000);

        }
        if (dataReceived == 1)
        {
          digitalWrite(GREEN_LED_PIN_1, LOW);
          digitalWrite(RED_LED_PIN_1, HIGH);
          
          digitalWrite(GREEN_LED_PIN_2, HIGH);
          digitalWrite(RED_LED_PIN_2, LOW);

          digitalWrite(GREEN_LED_PIN_3, LOW);
          digitalWrite(RED_LED_PIN_3, HIGH);

          delay(7000);
        }
        if (dataReceived == 2)
        {
          digitalWrite(GREEN_LED_PIN_1, LOW);
          digitalWrite(RED_LED_PIN_1, HIGH);
          
          digitalWrite(GREEN_LED_PIN_2, LOW);
          digitalWrite(RED_LED_PIN_2, HIGH);

          digitalWrite(GREEN_LED_PIN_3, HIGH);
          digitalWrite(RED_LED_PIN_3, LOW);

          delay(7000);
        }
        if (dataReceived == 3)
        {
          cycle();
        }
    }
}

void cycle() {
  digitalWrite(GREEN_LED_PIN_1, HIGH);
  digitalWrite(RED_LED_PIN_1, LOW);
          
  digitalWrite(GREEN_LED_PIN_2, LOW);
  digitalWrite(RED_LED_PIN_2, HIGH);

  digitalWrite(GREEN_LED_PIN_3, LOW);
  digitalWrite(RED_LED_PIN_3, HIGH);

  delay(1000);

  digitalWrite(GREEN_LED_PIN_1, LOW);
  digitalWrite(RED_LED_PIN_1, HIGH);
          
  digitalWrite(GREEN_LED_PIN_2, HIGH);
  digitalWrite(RED_LED_PIN_2, LOW);

  digitalWrite(GREEN_LED_PIN_3, LOW);
  digitalWrite(RED_LED_PIN_3, HIGH);

  delay(1000);

  digitalWrite(GREEN_LED_PIN_1, LOW);
  digitalWrite(RED_LED_PIN_1, HIGH);
          
  digitalWrite(GREEN_LED_PIN_2, LOW);
  digitalWrite(RED_LED_PIN_2, HIGH);

  digitalWrite(GREEN_LED_PIN_3, HIGH);
  digitalWrite(RED_LED_PIN_3, LOW);

  delay(1000);
}

void showData() {
    if (newData == true) {
        Serial.print("Data received ");
        Serial.println(dataReceived);
//        Serial.println(cnt1);
        newData = false;
    }
}
