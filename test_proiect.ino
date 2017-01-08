#include <IRremote.h>

#define front 0xFF18E7  //2
#define back 0xFF38C7   //5
#define left 0xFF10EF   //4
#define right 0xFF5AA5  //6
#define repeat 0xFFFFFFFF  
#define powerOffOn 0xFFA25D
#define rotateLeft 0xFF22DD
#define rotateRight 0xFFC23D
#define plus 0xFF629D
#define minus 0xFFA857
int RECV_PIN = 11;

//primul motor 
int enA = 4;
int in1 = 2;
int in2 = 3;
//al doilea motor
int enB = 5;
int in3 = 6;
int in4 = 7;

int speedA = 0;
int speedB = 0;
int directionMovement = 0;
bool isStateChange = true;

//telecomanda
IRrecv irrecv(RECV_PIN);
decode_results results;
decode_results auxResults;

void setup() {
//pinii de la motoare setati ca si output
  pinMode(enA, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);

  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
}

void loop() {
 if (irrecv.decode(&auxResults)) {
      //Serial.println(auxResults.value,HEX);
      isStateChange = true;
      irrecv.resume();
 }
 else{
    isStateChange = false;
 }

 if (auxResults.value == front || auxResults.value == back || auxResults.value == left || auxResults.value == right || auxResults.value == powerOffOn || 
     auxResults.value == repeat || auxResults.value == plus || auxResults.value == minus  || auxResults.value == rotateLeft || auxResults.value == rotateRight){
     results = auxResults;
 }

 if (results.value == front){ 
 //ambele motoare merg inainte
 speedA = 110;
 speedB = 110;
 directionMovement = 0;
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 analogWrite(enB, speedB);
 
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 analogWrite(enA, speedA);
 }
 
 if (results.value == back){
 speedA = 110;
 speedB = 110;
 directionMovement = 1;
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 analogWrite(enB, speedB);

 digitalWrite(in2, HIGH);
 digitalWrite(in1, LOW);
 analogWrite(enA, speedA);
 }
 
 if (results.value == left){
   Serial.println("stanga");
 analogWrite(enB, speedB / 2);
 delay(2000);
 analogWrite(enB, speedB);
 }
 
 if (results.value == right){
  Serial.println("dreapta");
 analogWrite(enA, speedA / 2);
 delay(2000);
 analogWrite(enA, speedA);
 }

 if (results.value == plus){
 // Serial.println("plus");
 if (isStateChange){
 if (speedA != 0)
    speedA += speedA > 160 ? 0 :30;
 if (speedB != 0)
 speedB += speedB > 160 ? 0 :30;
 }
 analogWrite(enA, speedA);
 analogWrite(enB, speedB);
 Serial.println(speedA);
 Serial.println(speedB);
 }

 if (results.value == minus){
// Serial.println("plus");
 if (isStateChange){
 speedA -= speedA < 120 ? 0 :30;
 speedB -= speedB < 120 ? 0 :30;
 }
 analogWrite(enA, speedA);
 analogWrite(enB, speedB);
 Serial.println(speedA);
 Serial.println(speedB);
 }

 if (results.value == rotateRight){
 if (directionMovement == 0){
 digitalWrite(in2, HIGH);
 digitalWrite(in1, LOW);
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 }
 else{
 digitalWrite(in3, HIGH);
 digitalWrite(in4, LOW);
 digitalWrite(in1, LOW);
 digitalWrite(in2, HIGH);
 }
 analogWrite(enA, speedA);
 analogWrite(enB, speedB);
 }

 if (results.value == rotateLeft){
 if (directionMovement == 0){
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 }
 else{
 digitalWrite(in3, LOW);
 digitalWrite(in4, HIGH);
 digitalWrite(in1, HIGH);
 digitalWrite(in2, LOW);
 }
 analogWrite(enA, speedA);
 analogWrite(enB, speedB);
 }
 
 if (results.value == powerOffOn){
 digitalWrite(in3, LOW);
 digitalWrite(in4, LOW); 
 digitalWrite(in2, LOW);
 digitalWrite(in1, LOW);
 digitalWrite(enA,LOW);
 digitalWrite(enB,LOW);
 speedA = 0;
 speedB = 0;
 }
}
