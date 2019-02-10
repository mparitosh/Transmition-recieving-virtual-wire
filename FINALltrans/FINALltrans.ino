#include <VirtualWire.h>

const int led_pin = 11;
const int transmit_pin = 12;
const int receive_pin = 2;
const int transmit_en_pin = 3;
int motor1_pin = 4;
int motor1_reverse_pin = 5;
int motor2_pin = 6;
int motor2_reverse_pin = 7;
void setup()
{
  // Initialise the IO and ISR

  Serial.begin(9600);
  vw_set_tx_pin(transmit_pin);
  vw_set_rx_pin(receive_pin);
  vw_set_ptt_pin(transmit_en_pin);
  vw_set_ptt_inverted(true); // Required for DR3100
  vw_setup(200);   // Bits per sec
  pinMode(motor1_pin, INPUT);
  pinMode(motor1_reverse_pin, INPUT);
  pinMode(motor2_pin, INPUT);
  pinMode(motor2_reverse_pin, INPUT);
}

byte count = 1;

void loop()
{
  digitalWrite(8, HIGH);
  char msg[6] = {digitalRead(motor1_pin), digitalRead(motor1_reverse_pin), digitalRead(motor2_pin), digitalRead(motor2_reverse_pin), ' ', '#'};
  Serial.print(digitalRead(motor1_pin));
  Serial.print(digitalRead(motor1_reverse_pin));
  Serial.print(digitalRead(motor2_pin));
  Serial.print(digitalRead(motor2_reverse_pin));
  Serial.println();
  msg[5] = count;
  digitalWrite(led_pin, HIGH); // Flash a light to show transmitting
  vw_send((uint8_t *)msg, 6);
  vw_wait_tx(); // Wait until the whole message is gone
  digitalWrite(led_pin, LOW);
  delay(10);
  count = count + 1;
}
