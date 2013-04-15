#include <IRremote.h>

#define REPEAT_DELAY 20

int RECV_PIN = 5;
int START_LED = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

long MASK = 0x40BF0000; /* mask for remote */
long key_mask = 0xFFFF;
long repeat = 0xFFFFFFFF;
long val = 0;

/* For debug */
char* key_names[] = {
  "UP",
  "DOWN", 
  "LEFT",
  "RIGHT",
  "OK"
};

long keycodes[] = {
  0x52, /* UP */
  0x54, /* DOWN */
  0x51, /* LEFT */
  0x53, /* RIGHT */
  0x0D, /* OK */
};

long keys[] = {
  0xB04F, /* UP */
  0xF20D, /* DOWN */
  0x728D, /* LEFT */
  0x30CF, /* RIGHT */
  0x9867, /* OK */
};

int nb_elem = sizeof(keys) / sizeof(keys[0]);
int index = 0;

void setup()
{
  Serial1.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  for (index = 0; index < nb_elem; ++index) {
    pinMode(START_LED + index, OUTPUT);
  }
  Serial.println("GO ");

}

void loop() {
  char* key_name = NULL;
  static int last = -1;
  long tmp = 0;
  if (irrecv.decode(&results)) {
    if ((repeat == results.value)  && (last >= 0)) {
      /* we have to repeat last value */
      digitalWrite(START_LED + last, HIGH);
      Serial1.write(keycodes[last]);
    } else if ((results.value >> 16)& (MASK >> 16)) {
      key_name = NULL;
      val = results.value & key_mask;
      for (index = 0; index < nb_elem; ++index) {
	if (keys[index] == val) {
	  key_name = key_names[index];
	  digitalWrite(START_LED + index, HIGH);
	  Serial1.write(keycodes[index]);
	  last = index;
	} else {
	  digitalWrite(START_LED + index, LOW);
	}
      }
      if (NULL != key_name) {
	Serial.println(key_name);	
      }
    }
    delay(REPEAT_DELAY); /* To avoid repeat issue */
    /* clear LEDs */
    for (index = 0; index < nb_elem; ++index) {
      digitalWrite(START_LED + index, LOW);
    }
    irrecv.resume(); // Receive the next value
  }
}
