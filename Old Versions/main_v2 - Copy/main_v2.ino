//BIBLIOTECAS

//Ultrasonic
#include <Ultrasonic.h>

//Peso
#include <HX711.h>

//Barcode

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//------------------------------------------------------------------------------------------------------------------//

//VARIÁVEIS

//Ultrasonic
int x=0;
int y=0;
int z=0;
int altura=0;
int comprimento=0;
int largura=0;
int volume=0;

//Peso


//Barcode

//------------------------------------------------------------------------------------------------------------------//

//PINAGEM

//Ultrasonic
Ultrasonic ultrasonic1(9,8);   // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(6,7);  // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic3(10,11);  // (Trig PIN,Echo PIN)

//Peso
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;
HX711 scale;

//Barcode
//LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//------------------------------------------------------------------------------------------------------------------//

//SETUP GERAL

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  peso_setup();
  lcd_setup();
  

}

//LOOP GERAL

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonic_loop();
  peso_loop();
  delay(5000);
  lcd_loop();
  delay(1000);
  
}

//------------------------------------------------------------------------------------------------------------------//

//Códigos dos componentes
void ultrasonic_loop(){
  // Obtendo as distâncias em centimetros
  x = ultrasonic1.read(CM);
  y = ultrasonic2.read(CM);
  z = ultrasonic3.read(CM);

  //Colocar distância real da caixa
  altura=10-y;
  largura=8-x;
  comprimento=z;

  volume = altura*largura*comprimento;

  Serial.print("Altura: ");
  Serial.print(altura);
  Serial.print(" cm" );
  Serial.print('\n');
  delay(500);

  Serial.print("Largura: ");
  Serial.print(largura);
  Serial.print(" cm" );
  Serial.print('\n');
  delay(500);

  Serial.print("Comprimento: ");
  Serial.print(comprimento);
  Serial.print(" cm" );
  Serial.print('\n');
  delay(500);
  
}

void lcd_loop(){
  lcd.clear();
  lcd.setCursor(3,0);
  lcd.print("Altura: ");
  lcd.print(altura);
  lcd.print(" cm" );
  lcd.setCursor(2,1);
  lcd.print("Largura: ");
  lcd.print(largura);
  lcd.print(" cm" );
  lcd.setCursor(1,2);
  lcd.print("Comprimento:");
  lcd.print(comprimento);
  lcd.print(" cm" );
  lcd.setCursor(4,3);
  lcd.print("Peso: ");
  lcd.print(scale.get_units(), 1);
  lcd.print(" kg" );
    

}

void lcd_setup(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}


void peso_setup(){
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // CONFIHURANDO OS PINOS DA BALANÇA
  scale.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO
  delay(2000);
  scale.tare(); // ZERANDO A BALANÇA PARA DESCONSIDERAR A MASSA DA ESTRUTURA

}

void peso_loop(){
  Serial.print("Peso: ");
  Serial.print("\n");
  Serial.print(scale.get_units(), 1);
  Serial.print("\n");
  Serial.print("kg");  

  scale.power_down(); // put the ADC in sleep mode
  delay(500);
  scale.power_up();
}
