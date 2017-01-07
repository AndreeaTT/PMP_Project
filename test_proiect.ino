#include <IRremote.h>

#define front 0xFF18E7  //2
#define back 0xFF38C7   //5
#define left 0xFF10EF   //4
#define right 0xFF5AA5  //6
#define repeat 0xFFFFFFFF  
#define powerOff 0xFFA25D
#define startButton 0xFFB04F
#define stopButton 0xFFE21D
int RECV_PIN = 11;

//primul motor 
int enA = 4;
int in1 = 2;
int in2 = 3;
//al doilea motor
int enB = 5;
int in3 = 6;
int in4 = 7;

//telecomanda
IRrecv irrecv(RECV_PIN);
decode_results results;


void setup() {
//pinii de la motoare setati ca si output
  pinMode(enA, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
 if (irrecv.decode(&results)) {
      irrecv.resume();
  }
  if (results.value == front){ 
 //ambele motoare merg inainte
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 analogWrite(enB, 200);
 
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enA, 200);
  }
 if (results.value == back){
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 analogWrite(enB, 200);

 digitalWrite(in2, HIGH);
 digitalWrite(in1, LOW);
 analogWrite(enA, 200);
  }
 if (results.value == left){
 analogWrite(enA, 100);
 delay(2000);
 analogWrite(enA, 200);
 }
 if (results.value == right){;
 analogWrite(enB, 100);
 delay(2000);
 analogWrite(enB,200);
 
 }
 if (results.value == powerOff){
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW); 
 digitalWrite(in2, LOW);
 digitalWrite(in1, LOW);
 digitalWrite(enA,LOW);
 digitalWrite(enB,LOW);
 }
 
  
   }

