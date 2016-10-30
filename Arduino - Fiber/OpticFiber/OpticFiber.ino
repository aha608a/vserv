
static const int channel = 3;
static const int lightth = 200;
static const int darkth = 1023-lightth;
int dark[channel];
int light[channel];

void setup() {
  // put your setup code here, to run once:
  pinMode[13, OUTPUT];
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  // Dark array is 1 if it dark
  for(int i = 0; i < channel; i++){
    int readval = analogRead(i);
    Serial.print("Dark ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(readval);
    if(readval >= darkth) {
      dark[i] = 1;
    }
    else{
      dark[i] = 0;
    }
  }
  //Light array is 1 if it light
  for(int i = channel; i < 2 * channel; i++){
    int readval = analogRead(i);
    Serial.print("Light ");
    Serial.print(i);
    Serial.print(": ");
    Serial.println(readval);
    if(readval <= lightth) {
      light[i - channel] = 1;
    }
    else{
      light[i - channel] = 0;
    }
  }

  Serial.println("\n");
  //Find error
  for(int i = 0; i < channel; i++){
    if(dark[i] == 0 || light[i] == 0){
      digitalWrite(13, HIGH);
      break; //Maintain error
    }
    else{
      digitalWrite(13, LOW);
    }
  }
  delay(500);
}
