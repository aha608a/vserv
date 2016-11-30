
//Essentials
byte clk = B000;
const int numFibersPerRow = 8;
int dark[numFibersPerRow], light[numFibersPerRow];

//SpeedTest
bool speedTest = true;
int time0, time1;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(250000); // Start serial port

  //Mux controller pins
  for(int i = 2; i < 5; i++){
    pinMode(i, OUTPUT);
  }
  updateControl();
}

void loop() {
  // put your main code here, to run repeatedly:
  // Speed Test
  if(speedTest && clk == 0){
    time0 = millis();
  }
  
  // Header
  Serial.print("Stripe ");
  Serial.print(clk + 1);
  Serial.println(':');

  //Read from the phototransistors
  for(int i = 0; i < numFibersPerRow; i++){
    dark[i] = analogRead(i);
    light[i] = analogRead(i + 8); 

    //Print Dark
    Serial.print("\tDark ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(dark[i]);

    //Print Light
    Serial.print("\tLight ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.println(light[i]);

    Serial.println();
  }
  Serial.println();
  //Update the control
  clk = (clk + 1) % 8;
  updateControl();

  if(speedTest && clk == 7){
    time1 = millis();
    //Serial.print("Program speed: ");
    //Serial.println(time1 - time0);
    delay(500);
  }
}

//Update control for muxes
void updateControl(){
  for(int i = 0; i < 3; i++){
    digitalWrite(i + 2, bitRead(clk, i));
  }
}

