//Bibliotecas
#include <Ultrasonic.h>
#include <HX711.h>


//Variáveis
//Ultrasonic
int x=0;
int y=0;
int z=0;
int altura=0;
int comprimento=0;
int largura=0;
int volume=0;
//Peso
HX711 scale;



//Pinagem
//Ultrasonic
Ultrasonic ultrasonic1(9,8);   // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(6,7);  // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic3(10,11);  // (Trig PIN,Echo PIN)
//Peso
const int LOADCELL_DOUT_PIN = 2; //PIN DT
const int LOADCELL_SCK_PIN = 3; // PIN SCK


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  peso_setup();

}

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonic();
  peso();

}

//Códigos dos componentes
void ultrasonic(){
  // Obtendo as distâncias em centimetros
  x = ultrasonic1.read(CM);
  y = ultrasonic2.read(CM);
  z = ultrasonic3.read(CM);

  //Colocar distância real da caixa
  altura=21-y;
  largura=24-x;
  comprimento=16-z;

  volume = altura*largura*comprimento;

  Serial.print("Altura: ");
  Serial.print(altura);
  Serial.print(" cm   " );
  delay(50);

  Serial.print("Largura: ");
  Serial.print(largura);
  Serial.print(" cm   " );
  delay(50);

  Serial.print("Comprimento: ");
  Serial.print(comprimento);
  Serial.print(" cm   " );
  delay(50);
  
  Serial.print("Volume: ");
  Serial.print(volume);
  Serial.print(" cm³   " );
  delay(50);
  
}

void peso_setup(){
  Serial.println("Initializing the scale");

  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);

  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());      // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0

  Serial.println("After setting up the scale:");

  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC

  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC

  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale

  Serial.println("Readings:");
  
}

void peso(){
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 1);

  scale.power_down();              // put the ADC in sleep mode
  delay(5000);
  scale.power_up();
  
}

void barcode(){
  
}

void lcd(){
  
}
