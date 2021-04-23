//########### INCLUDES ##############
#include <WiFi.h> // para conectar wifi
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <OneWire.h> //temperatura
#include <DallasTemperature.h> //temperatura
#include "teste_canos.h"
#include "manda_fluxo.h"
#include <queue>

using namespace std;

//########## INICIA FUNÇÕES ##############
/*
void Internet();
bool salvar_dados(String); //nova guia
void http(); // nova guia
void interrupcao( void *pvParameters ); //Guia fluxo
void fila (String);*/

//_____________INSTANCIAS CANO_______________________
cano C1(33); // Guia teste_canos.h
cano C2(32);
cano C3(35);
cano C4(34);

//____________ FILA IMPRESSÃO ___________________

queue <String> Envia; // Inicia a queue Envia
queue <String> Cerial;

//___________ VARIÁVEIS INTERNET ___________________

String url = ""; // envia os dados para internet
bool flag;        //Flag usada para enviar somente uma vez o volume do sensor de fluxo

//____________VARIÁVEIS TEMPERATURA__________________

#define DS18B20 27 //DEFINE O PINO DIGITAL UTILIZADO PELO SENSOR

OneWire ourWire(DS18B20); //CONFIGURA UMA INSTÂNCIA ONEWIRE PARA SE COMUNICAR COM O SENSOR
DallasTemperature sensors(&ourWire); //BIBLIOTECA DallasTemperature UTILIZA A OneWire

int sens_temp = 25;
int controle_temp;
int tempMin = 999;
int tempMax = 0;

// ______________NTC_TEMPO_______________

int timeZone = -3; //fusorario

//Struct com os dados do dia e hora
struct Date {int diadasemana;int dia;int mes;int ano;int hora;int minutos;int segundos;};

int hora;
int minuto;
int segundo;
int dia;
int mes;
int ano;


WiFiUDP ntpUDP;
// Por padrão, 'pool.ntp.org' é usado com intervalo de atualização de 60 segundos e
// sem deslocamento
NTPClient timeClient (
  ntpUDP,
  "a.st1.ntp.br",
  timeZone * 3600,
  60000);//atualização da hora

//Nomes dos dias da semana
char* dayOfWeekNames[] = {"DOMINGO", "SEGUNDA", "TERÇA", "QUARTA", "QUINTA", "SEXTA", "SABADO"};

//____________INTANCIAS SENSOR FLUXO____________
fluxo rep_agua("agua" ); // Guia manda_fluxo.h
fluxo horta   ("horta");
fluxo peixe   ("peixe");

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%% INICIO SETUP %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%5

void setup() {
  //#######-INICIA PORTA SERIAL-###################
  Serial.begin(115200);
  Serial.println();
  Serial.println("CONECTADO NA SERIAL");

  delay(10);

  //########-COMEÇA A CONEÇÃO COM A INTERNET-#######

  Internet(); // chama a função para conectar a internet - Guia Inicia_internet

  //#######-INICIA SENSOR TEMPERATURA-##############

  sensors.begin(); //inicia sensor temperatura
  Serial.println("Sensor temperatura iniciado");
  Serial.println();

  //###############  HORA ###########
  //____________INICIA RELÓGIO____________

  timeClient.begin();

  //_______________ Inicia a task

  xTaskCreatePinnedToCore(  // Guia fluxo
    interrupcao
    ,  "interrupcao"   // A name just for humans
    ,  10000  // This stack size can be checked & adjusted by reading the Stack Highwater
    ,  NULL
    ,  2  // Priority, with 3 (configMAX_PRIORITIES - 1) being the highest, and 0 being the lowest.
    ,  NULL
    ,  0);

}

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% FIM SETUP %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

void loop() {

  // ####### VERIFICA STATUS INTERNET ###########
  while (WiFi.status() != WL_CONNECTED) {
    switch (WiFi.status()) {
      case WL_NO_SSID_AVAIL:
        Serial.println("SSID não avaliada");
        break;
      case WL_CONNECTION_LOST:
        Serial.println("Conexão perdida");
        break;
      case WL_DISCONNECTED:
        Serial.println("Desconectado");
        break;
    }
    delay (10);
    Internet();
  }


  //########## TESTA RELÓGIO ######################
  while (!timeClient.update()) {                    //Verifica se a hora está alualizada?
    int cont;                                       //contador para não prender no loop
    do {
      cont++;
      timeClient.forceUpdate();
      //Serial.println("Relógio NÃO Atualizado");
      delay(500);
    } while (!(timeClient.update() || cont >= 5));
    break;
  }

  Date getDate();         //inicia o armazenamento das horas
  Date date = getDate();  //instancia um objeto para armazenar as horas

  while (date.hora >= 25) {                 // verifica se a hora esta dentro dos conformes
    Serial.println("hora não atualizada");
    Serial.println(date.hora);
    Date date = getDate();
    //delay(1000);
  }

  hora    = date.hora;
  minuto  = date.minutos;
  segundo = date.segundos;
  dia     = date.dia;
  mes     = date.mes;
  ano     = date.ano;
  delay (1000);

  // ##### ENVIA DADOS TEMPERATURA ######

  //sensors.requestTemperatures();//SOLICITA QUE A FUNÇÃO INFORME A TEMPERATURA DO SENSOR
  //sens_temp = (sensors.getTempCByIndex(0)); //VALOR DE TEMPERATURA MEDIDO
  sens_temp = 21;
  //delay(250);//INTERVALO DE 250 MILISSEGUNDOS


  if (sens_temp != controle_temp) { //Verifica se a temperatura registrada é igual a medida
    controle_temp = sens_temp;      //Atualiza a temperatura registrada
    String url = "";
    String * envia = &url;
    *envia = "/ESP32/salvart.php?"; //Monta a String para ser enviada
    *envia += "sens_temp=";
    *envia += sens_temp;
    *envia += "&d=";
    *envia += dia;
    *envia += "&m=";
    *envia += mes;
    *envia += "&a=";
    *envia += ano;
    *envia += "&h=";
    *envia += hora;

    Envia.push(*envia);                //Coloca na fila os dados para serem enviados

    url = "";
  }

  //#######-ENVIA DADOS DOS CANOS-################
  bool c1 = C1.testa_cano();  //Grava na variável o retorno boleano da função testa_cano da classe cano
  bool c2 = C2.testa_cano();
  bool c3 = C3.testa_cano();
  bool c4 = C4.testa_cano();

  if ( c1 || c2 || c3 || c4) {        //Verifica se houve alguma alteração para enviar
    String url = "";
    String * envia = &url;
    *envia = "/ESP32/salvarc.php?";   //Monta a String para ser enviada
    *envia += "v=sim";
    *envia += "&cano1=";
    *envia += C1.get_StatusCano();     //Pega o retorno boleano dos canos
    *envia += "&cano2=";
    *envia += C2.get_StatusCano();
    *envia += "&cano3=";
    *envia += C3.get_StatusCano();
    *envia += "&cano4=";
    *envia += C4.get_StatusCano();
    *envia += "&d=";
    *envia += dia;
    *envia += "&m=";
    *envia += mes;
    *envia += "&a=";
    *envia += ano;
    *envia += "&h=";
    *envia += hora;
    Envia.push(*envia);                //Coloca na fila os dados para serem enviados
    url = "";
  }

  //############## ENVIA DADOS Sensor de fluxo ##################

  if (segundo == 16) {               //Verifica se é hora
    if (flag == 0) {              //Verifica se é a primeira vez que ocorre
      rep_agua.organiza_dados();  // Monta a string _Dados para ser enviada
      horta   .organiza_dados();
      peixe   .organiza_dados();

      delay (100);

      fila(rep_agua.getdados(), dia, mes, ano, hora); // Pega a String _Dados e coloca na fila de envio
      fila(horta   .getdados(), dia, mes, ano, hora);
      fila(peixe   .getdados(), dia, mes, ano, hora);

      rep_agua.apaga_cp_contador(); // Zera a _cp_contador da class
      horta   .apaga_cp_contador();
      peixe   .apaga_cp_contador();

      flag = 1;                     // Atualiza a flag para não enviar novamente os dados
    }
  } else {flag = 0;} // Mantem a flag em 0 para quando for a hora ser enviado os dados
  

  //############## VERIFICAÇÃO DOS DADOS DA FILA PARA ENVIO ##################

  while (!Envia.empty()) {   //Verifica se tem algo para enviar no queue
    int cont = 0;              //Para não travar o sistema
    bool enviado = 0;
    do {  // bloco de comandos
      delay(100);
      cont++;
      enviado = salvar_dados(Envia.front());
    } while (!(enviado || cont >= 5)); // envia os dados para internet e verifica se foi enviado com retorno boleano
    
    if (enviado) {
      Envia.pop(); // se tiver enviado, retira da fila
    }
  }
  
  while (!Cerial.empty()) {           //inicia a fila de impressão da serial
    Serial.println(Cerial.front());
    Cerial.pop();
  }

  //http();

}
