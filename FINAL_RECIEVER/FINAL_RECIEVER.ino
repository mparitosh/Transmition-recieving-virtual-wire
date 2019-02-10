//reciever
#include <VirtualWire.h>

const int led_pin = 6;
const int transmit_pin = 12;
const int receive_pin = 11;
const int transmit_en_pin = 3;
int motor1_pin = 4;
int motor1_reverse_pin = 5;
int motor2_pin = 6;
int motor2_reverse_pin = 7;
void setup()
{
    delay(1000);
    Serial.begin(9600);  // Debugging only
    Serial.println("setup");

    // Initialise the IO and ISR
    vw_set_tx_pin(transmit_pin);
    vw_set_rx_pin(receive_pin);
    vw_set_ptt_pin(transmit_en_pin);
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(200);  // Bits per sec

    vw_rx_start();       // Start the receiver PLL running
     pinMode(motor1_pin,OUTPUT);
  pinMode(motor1_reverse_pin,OUTPUT);
  pinMode(motor2_pin,OUTPUT);
  pinMode(motor2_reverse_pin,OUTPUT);
}

void loop()
{
    int i=digitalRead(11);
    uint8_t buf[VW_MAX_MESSAGE_LEN];
    uint8_t buflen = VW_MAX_MESSAGE_LEN;
    Serial.println(i);
    if (vw_get_message(buf, &buflen)) // Non-blocking
    {
  

        digitalWrite(led_pin, HIGH); // Flash a light to show received good message
  // Message with a good checksum received, print it.
  Serial.print("Got: ");
      digitalWrite(motor1_pin,buf[0]);
      Serial.print(buf[0]);
      Serial.print(' ');
      digitalWrite(motor1_reverse_pin,buf[1]);
      Serial.print(buf[1]);
      Serial.print(' ');
      digitalWrite(motor2_pin,buf[2]);
      Serial.print(buf[2]);
      Serial.print(' ');
      digitalWrite(motor2_reverse_pin,buf[3]);
      Serial.print(buf[3]);
      Serial.print(' ');
      /*Serial.print(buf[4]);
      Serial.print(' ');
      Serial.print(buf[5]);
      Serial.print(' ');*/
  
  Serial.println();
        digitalWrite(led_pin, LOW);
    }
}
