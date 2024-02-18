//BIBLIOTECAS

//Ultrasonic
#include <Ultrasonic.h>

//Peso
#include <HX711.h>

//Barcode

//LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

//ETHERNET
#include "etherShield.h"
#include "ETHER_28J60.h"



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
float escala = -20560;
#define pesoMin 0.010
#define pesoMax 200
float medida=0;
float pesobj=0;

//Barcode

//ETHERNET
//Define o MAC da placa de rede. Nao eh necessario alterar
static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

//Define o endereco IP da sua placa
static uint8_t ip[4] = {192, 168, 0, 129};
 
static uint16_t port = 80;
 
ETHER_28J60 e;





//------------------------------------------------------------------------------------------------------------------//

//PINAGEM

//Ultrasonic
Ultrasonic ultrasonic1(9,8);   // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic2(6,7);  // (Trig PIN,Echo PIN)
Ultrasonic ultrasonic3(10,11);  // (Trig PIN,Echo PIN)

//Peso
const int LOADCELL_DOUT_PIN = 3;
const int LOADCELL_SCK_PIN = 4;
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
  ethernet_setup();

}

//LOOP GERAL

void loop() {
  // put your main code here, to run repeatedly:
  ultrasonic_loop();
  delay(500);
  peso_loop();
  delay(500);
  lcd_loop();
  delay(500);
  ethernet_loop();
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
  lcd.print(pesobj, 1);
  lcd.print(" kg" );
    

}

void lcd_setup(){
  lcd.init();   // initialize the lcd 
  lcd.backlight();
}


void peso_setup(){
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN); // CONFIHURANDO OS PINOS DA BALANÇA
  scale.set_scale(escala); // ENVIANDO O VALOR DA ESCALA CALIBRADO
  delay(2000);
  scale.tare(); // ZERANDO A BALANÇA PARA DESCONSIDERAR A MASSA DA ESTRUTURA

}

void peso_loop(){
    scale.power_up(); // LIGANDO O SENSOR
    
    medida = scale.get_units(5); // SALVANDO NA VARIAVEL O VALOR DA MÉDIA DE 5 MEDIDAS
    
    if (medida <= pesoMin ){ // CONFERE SE A MASSA ESTÁ NA FAIXA VÁLIDA
      scale.tare(); // ZERA A BALANÇA CASO A MASSA SEJA MENOR QUE O VALOR MIN
      medida = 0;
      //Serial.println("Tara Configurada!");
    } else if ( medida >= pesoMax ){
      scale.tare(); // ZERA A BALANÇA CASO A MASSA SEJA MAIOR QUE O VALOR MÁX
      medida = 0;
      Serial.println("Tara Configurada!");
    } else {
      pesobj = medida;
    }

    scale.power_down(); // DESLIGANDO O SENSOR
}

void ethernet_setup(){
  //Inicializa a placa com as configuracoes fornecidas
  e.setup(mac, ip, port);
}


void ethernet_loop(){
  if (e.serviceRequest())
  {
    e.print("<H1>BALANCA CUBADORA - PROTOTIPO</H1><br/>");
    e.print("<b>Valor potenciometro porta analogica 5 : ");
    e.print("<br/><br/>");
    e.print("Altura: ");
    e.print(altura);
    e.print("&deg<br/><br/>");
    e.print("Largura: ");
    e.print(largura);
    e.print("&deg<br/>");
    e.print("Comprimento: ");
    e.print(comprimento);
    e.print("&deg<br/>");
    e.print("Peso: ");
    e.print(pesobj);
    e.print("&deg<b/>");
    e.respond();
  }
  delay(100);
}
