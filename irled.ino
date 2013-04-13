#include <IRremote.h>

int RECV_PIN = 5;
int START_LED = 8;
IRrecv irrecv(RECV_PIN);
decode_results results;

long MASK = 0x40BF0000; /* mask for remote */
long key_mask = 0xFFFF;
long val = 0;

/* For debug */
char* key_names[] = {
  "UP",
  "DOWN", 
  "LEFT",
  "RIGHT",
  "OK"
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
  Serial1.println("GO ");

}

void loop() {
  char* key_name = NULL;
  if (irrecv.decode(&results)) {
    if ((results.value >> 16)& (MASK >> 16)) {
      key_name = NULL;
      val = results.value & key_mask;
      for (index = 0; index < nb_elem; ++index) {
	if (keys[index] == val) {
	  key_name = key_names[index];
	  digitalWrite(START_LED + index, HIGH);
	} else {
	  digitalWrite(START_LED + index, LOW);
	}
      }
      if (NULL != key_name) {
	Serial1.print("Received: ");
	Serial1.println(key_name);
      }
    }
    irrecv.resume(); // Receive the next value
  }
}
