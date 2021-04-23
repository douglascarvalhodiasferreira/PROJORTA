bool salvar_dados(String t) {
  String Dados = t;
  const char* host = "192.168.0.14"; // site que irá acessar

  Serial.println("conectando a: ");
  Serial.println(host);


  // Use WiFiClient class para criar TCP conecção
  WiFiClient client;
  const int httpPort = 80;
  //Serial.println("teste1");

  if (!client.connect(host, httpPort)) {
    Serial.println("falha na conexao");
    Serial.println("conexao fechada");
    Serial.println("###########################################################");
    return 0;
  }

  // We now create a URI for the request
  
  Serial.println("Requesitando URL: ");
  Serial.print(Dados);

  // This will send the request to the server
  client.print(String("GET ") + Dados + " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      Serial.println("conexao fechada");
      Serial.println("###########################################################");
      return 0;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.println(line);

    if (line.indexOf("salvo_com_sucesso") != -1) {
      Serial.println("conexao fechada");
      Serial.println("###########################################################");
      return 1;
      
    } else if (line.indexOf("erro_ao_salvar") != -1) {
      Serial.println("conexao fechada erro ao salvar no BD");
      Serial.println("###########################################################");
      return 0;
    } 
  }

  Serial.println();
}
