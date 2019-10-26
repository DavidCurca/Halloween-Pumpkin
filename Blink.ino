#define echoPin 2 // Echo Pin (OUTPUT pin in RB URF02)
#define trigPin 3 // Trigger Pin (INPUT pin in RB URF02)

int led1 = 5;
int led2 = 4;
int maximumRange = 350; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance
int brightness;

long previousMillis = 0;
long closeReadings = 0;

void setup() {
 randomSeed(analogRead(0));
 Serial.begin(9600);
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
 pinMode(led1, OUTPUT);
 pinMode(led2, OUTPUT);
}

void loop() {
// The following trigPin/echoPin cycle is used to determine the distance of the nearest object by bouncing soundwaves off of it.
 digitalWrite(trigPin, LOW);
 delayMicroseconds(2);
 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 distance = duration/58.2; //Calculate the distance (in cm) based on the speed of sound.
 //Serial.println(distance); // distance in cm
 brightness= map(distance,1,100,0,255);
 if(distance <= 10){
  closeReadings++;
  digitalWrite(led1, HIGH);
  digitalWrite(led2, LOW);
 }else{
  digitalWrite(led1, LOW);
  closeReadings = 0;
  unsigned long currentMillis = millis();
  if(currentMillis - previousMillis > 25)
  {
    previousMillis = currentMillis;
    analogWrite(led2, random(0, 256));
  }
 }
 delay(50); //Delay 50 ms
}

/**    
digitalWrite(5, LOW);
unsigned long currentMillis = millis();
if(currentMillis - previousMillis > 25)
{
  previousMillis = currentMillis;
  analogWrite(4, random(0, 256));
}
 */
