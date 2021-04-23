void interrupcao(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  //___________ #define sensor de fluxo ________

#define REPOSICAO_AGUA 12
#define HORTA          13
#define PEIXE          14

  pinMode(REPOSICAO_AGUA, INPUT);
  pinMode(HORTA         , INPUT);
  pinMode(PEIXE         , INPUT);

  /*Serial.println("Task1 running on core ");
    Serial.print(xPortGetCoreID());*/

  attachInterrupt(digitalPinToInterrupt(REPOSICAO_AGUA), contador_pulso , FALLING);
  attachInterrupt(digitalPinToInterrupt(HORTA)         , contador_pulso1, FALLING);
  attachInterrupt(digitalPinToInterrupt(PEIXE)         , contador_pulso2, FALLING);


  String tas = "agora eu quero ver";
  for (;;) { // A Task shall never return or exit.
    rep_agua.Acumula_contado();
    horta   .Acumula_contado();
    peixe   .Acumula_contado();

    //serial(tas); imprime na serial usando a função de fila serial
    vTaskDelay(5000);
  }

  /*void incrementa_contador(fluxo* c){c->set_contador();} // outra função de incremento do contador caso necessário
    incrementa_contador(&rep_agua);
    incrementa_contador(&horta);
    incrementa_contador(&peixe);*/
}

void contador_pulso () {rep_agua.set_contador();}
void contador_pulso1() {horta   .set_contador();}
void contador_pulso2() {peixe   .set_contador();}

void serial (String u) {   //função para colocar na fila de impressão na serial
  Cerial.push(u);
}

void fila (String u, int D, int M, int A, int H) { // função para mandar para fila de envio para internet
  String url = "";
  String * envia = &url;
  *envia = u;
  *envia += "&d=";
  *envia += D;
  *envia += "&m=";
  *envia += M;
  *envia += "&a=";
  *envia += A;
  *envia += "&h=";
  *envia += H;
  Envia.push(*envia);
  url = "";
}
