const int stripes = 8; //Number of stripes
const int analogNum = 55;
const int analogCh = 16;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000);

  // Configuring channels
  for(int i = analogNum; i < analogNum + 2 * stripes; i++){
    pinMode(i, INPUT);
  }
  // Set unused channels to output HIGH
  for(int i =  analogNum + 2 * stripes; 
      i < analogNum + analogCh; i++){
    pinMode(i, OUTPUT);
    analogWrite(i, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  //oldMethod();
  printResults();
  delay(500);
}

void oldMethod(){
    for(int i = 0; i < stripes; i++){
    int dark = analogRead(2 * i);
    int light = analogRead(2 * i + 1);
    String header1 = "Stripe ";
    header1 += (i + 1);
    header1 += "\n\tDark: ";
    header1 += dark;
    header1 += "\n\tLight: ";
    header1 += light;
    header1 += "\n";
    Serial.println(header1);
  }
}

void printResults(){
  String header = "Stripe";
  String darkHd = "Dark";
  String lightHd = "Light";
  
  for(int i = 0; i <= stripes; i++){
    header += "\t ";
    header += (i + 1);

    darkHd += "\t";
    darkHd += analogRead(2 * i);

    lightHd += "\t";
    lightHd += analogRead(2 * i + 1);
  }
  Serial.println(header);
  Serial.println(darkHd);
  Serial.println(lightHd);
}

