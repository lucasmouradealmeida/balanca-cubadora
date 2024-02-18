#include <Ultrasonic.h>

int x=0;
int y=0;
int z=0;
int altura=0;
int comprimento=0;
int largura=0;
int volume=0;


Ultrasonic ultrasonic1(2,3);   // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(5,4);  // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic3(7,6);  // (Trig PIN,Echo PIN)


void setup() {
  Serial.begin(9600);
}

void loop() {

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
  Serial.print(" cm" );
  delay(500);
  Serial.print('\n');
  Serial.print("Largura: ");
  Serial.print(largura);
  Serial.print(" cm" );
  delay(500);
  Serial.print('\n');
  Serial.print("Comprimento: ");
  Serial.print(comprimento);
  Serial.print(" cm" );
  delay(500);
  Serial.print('\n');
  Serial.print("Volume: ");
  Serial.print(volume);
  Serial.print(" cm³" );
  delay(500);
  Serial.print('\n');
}
