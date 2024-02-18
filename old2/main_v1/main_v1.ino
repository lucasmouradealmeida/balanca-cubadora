//BIBLIOTECAS

//Ultrasonic
#include <Ultrasonic.h>
//Peso

//Barcode

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>


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



//PINAGEM

//Ultrasonic
Ultrasonic ultrasonic1(9,8);   // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(6,7);  // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic3(10,11);  // (Trig PIN,Echo PIN)
//Peso
//Barcode
//LCD
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display

//SETUP GERAL

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  lcd_setup();

}


//LOOP GERAL

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonic_loop();
  lcd_loop();
  delay(120000); //2 minutos para proximo print

}

//Códigos dos componentes
void ultrasonic_loop(){
  // Obtendo as distâncias em centimetros
  x = ultrasonic1.read(CM);
  y = ultrasonic2.read(CM);
  z = ultrasonic3.read(CM);

  //Colocar distância real da caixa
  altura=y;
  largura=x;
  comprimento=z;

  volume = altura*largura*comprimento;

  Serial.print("Altura: ");
  Serial.print(altura);
  Serial.print(" cm   " );
  Serial.print('\n');
  delay(1000);

  Serial.print("Largura: ");
  Serial.print(largura);
  Serial.print(" cm   " );
  Serial.print('\n');
  delay(1000);

  Serial.print("Comprimento: ");
  Serial.print(comprimento);
  Serial.print(" cm   " );
  Serial.print('\n');
  delay(1000); //2 minutos para proximo print
  
}

void lcd_loop(){
    // when characters arrive over the serial port...
  if (Serial.available()) {
    // wait a bit for the entire message to arrive
    delay(100);
    // clear the screen
    lcd.clear();
    // read all the available characters
    while (Serial.available() > 0) {
      // display each character to the LCD
      lcd.write(Serial.read());
    }
  }
}

void lcd_setup(){
  lcd.init();                      // initialize the lcd 
  lcd.backlight();
}
