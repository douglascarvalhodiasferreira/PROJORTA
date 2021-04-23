void Internet() {

  unsigned long tempoAn = 0;
  unsigned long tempoA = millis();
  unsigned long tempoConec = 10000;
  byte mac[6]; // imprime endereço mac
  const char* ssid = "2.4_DOUGLAS";// QUAL REDE SE CONECTAR
  const char* password = "moedavirtual";// SENHA DA REDE

  Serial.print("Conectando com: ");
  Serial.println(ssid);

  //WiFi.setHostname("ESP32");  //Instancio o nome do AP
  WiFi.mode(WIFI_STA);     //Defino como AP e STA a rede
  //WiFi.softAP("ESP32_AP", "Miriante");  // defino a senha
  //Serial.print("WIFI_AP_STA");              // Imprimo o modo do WiFi

  WiFi.begin(ssid, password); //INICIA A INTERNET

  while (WiFi.status() != WL_CONNECTED) { //AGUARDA A CONEXÃO COM A INTERNET
    tempoAn = tempoA;

    if (tempoA - tempoAn < tempoConec) {
      Serial.print(".");
      delay(500);
    }

    else {
      Serial.println("Falha na conexão");
      Serial.println("Resetando ESP32");
      ESP.restart();
    } //Reseta o esp              }

    Serial.println("");
    Serial.println("WiFi Conectado.");
    Serial.print("IP address: ");
    Serial.print(WiFi.localIP());
    Serial.print("  SSID: ");
    Serial.print(WiFi.SSID());
    Serial.print("  Canal:  ");
    Serial.print(WiFi.channel());
    Serial.print("  RSSI:  ");
    Serial.print(WiFi.RSSI());
    WiFi.macAddress(mac);
    Serial.print("  MAC: ");
    Serial.print(mac[0], HEX);
    Serial.print(":");
    Serial.print(mac[1], HEX);
    Serial.print(":");
    Serial.print(mac[2], HEX);
    Serial.print(":");
    Serial.print(mac[3], HEX);
    Serial.print(":");
    Serial.print(mac[4], HEX);
    Serial.print(":");
    Serial.print(mac[5], HEX  );
    Serial.println();

    Serial.printf("Conectado a %s ", ssid);
    Serial.println();
    //server.begin();
    //Serial.println("Server iniciado");

  }

}
