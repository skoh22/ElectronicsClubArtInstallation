//prints LIDAR value to serial monitor
//wire sensor so white wire goes to A0, red wire goes to 5V, and black wire to GND


void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(A0);
  Serial.println(x);
  unsigned long startWait = millis();
  while (millis()-startWait<100){
    }
}
