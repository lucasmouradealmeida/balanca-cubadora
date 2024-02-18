#include <HX711.h>


// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;


HX711 scale;

void setup() {
  Serial.begin(9600);

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  scale.set_scale();    // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();         // reset the scale to 0
}

void loop() {
  Serial.print("Peso: ");
  Serial.print(scale.get_units(10));
  Serial.print(" kg");	
  Serial.print("\n");
  delay(1000);

  //scale.power_down(); // put the ADC in sleep mode
  //delay(500);
  //scale.power_up();
}
