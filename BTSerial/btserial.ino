#define LED_1 10
#define LED_2 11
#define LED_3 12
#define LED_4 13

void setup()
{
  int i = 0;
  Serial.begin(9600);
  for (i = LED_1; i < (LED_4 + 1); ++i) {
    pinMode(i, OUTPUT);
    digitalWrite(i, LOW);
  }
}

void enable_led(int led) 
{
  int i = 0;
  for (i = LED_1; i < (LED_4 + 1); ++i) {
    if (i == led) {
      digitalWrite(i, HIGH);
    } else {
      digitalWrite(i, LOW);
    }
  }
}

void loop()
{
    if (Serial.available() > 0) {
        char ch = Serial.read();
        Serial.print("Received: ");
        Serial.println(ch);
	switch(ch) {
	case '1':
	  enable_led(LED_1);
	  break;
	case '2':
	  enable_led(LED_2);
	  break;
	case '3':
	  enable_led(LED_3);
	  break;
	case '4':
	  enable_led(LED_4);
	  break;
	}
    }
}