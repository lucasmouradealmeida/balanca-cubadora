//Programa : Modulo ethernet ENC28J60
//Autor : FILIPEFLOP
#include "etherShield.h"
#include "ETHER_28J60.h"
 
//Define o MAC da placa de rede. Nao eh necessario alterar
static uint8_t mac[6] = {0x54, 0x55, 0x58, 0x10, 0x00, 0x24};

//Define o endereco IP da sua placa
static uint8_t ip[4] = {192, 168, 0, 129};
 
static uint16_t port = 80; 
 
ETHER_28J60 e;

 
void setup()
{ 
  //Inicializa a placa com as configuracoes fornecidas
  e.setup(mac, ip, port);
}
 
void loop()
{

  if (e.serviceRequest())
  {
    e.print("<H1>FILIPEFLOP - Teste ENC28J60</H1><br/>");
    e.print("<b>Valor potenciometro porta analogica 5 : ");
    e.print("<br/><br/>");
    e.print("Valor temperatura : ");
    e.print("&deg<br/><br/>");
    e.print("Temperatura minima : ");
    e.print("&deg<br/>");
    e.print("Temperatura maxima : ");
    e.print("&deg<b/>");
    e.respond();
  }
  delay(100);
}
