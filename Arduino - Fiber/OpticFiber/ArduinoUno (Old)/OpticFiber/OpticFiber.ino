
//Essentials
byte clk = B000;
const int numFibersPerRow = 2;
const int stripes = 2;
int dark[numFibersPerRow], light[numFibersPerRow];

//SpeedTest
bool speedTest = true;
int time0, time1;
bool speedFlag = false;

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
    if(!speedFlag){
      time0 = millis();
      speedFlag = !speedFlag;
    }
    else{
      //delay(500);
      time1 = millis();
//      Serial.print("Program speed: ");
//      Serial.println(time1 - time0);
      speedFlag = !speedFlag;
    }
  }
  
  // Header
  String header1 = "Stripe ";
  header1 += clk+1;
  header1 += ':';
  Serial.println(header1);
  String header2 = "\t\t";
  for(int i = 0; i < numFibersPerRow; i++){
    header2 += (i + 1);
    header2 +=  "\t";
  }
  Serial.println(header2);
  

  String darkPrint = "\tDark\t";
  String lightPrint = "\tLight\t";
  //Read from the phototransistors
  for(int i = 0; i < numFibersPerRow; i++){
    dark[i] = analogRead(i);
    light[i] = analogRead(i + 2); 

    //Print Dark
    darkPrint += dark[i];
    darkPrint += "\t";

    //Print Light
    lightPrint += light[i];
    lightPrint += "\t";
  }
  
  Serial.println(darkPrint);
  Serial.println(lightPrint + "\n");
  
  //Update the control
  clk = (clk + 1) % stripes;
  updateControl();

}

//Update control for muxes
void updateControl(){
  for(int i = 0; i < 3; i++){
    digitalWrite(i + 2, bitRead(clk, i));
  }
}

