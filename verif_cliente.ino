void http() {
/*
  const long t_maxConec = 2000;
  unsigned long t_client = millis();
  unsigned long t_antClient = t_client;

  WiFiClient client = server.available();     // ABRE A COMUNICAÇÃO COM O CLIENTE
  if (client) {                             // SE TEM CLIENTE
    Serial.println("New Client.");          // IMPRIME A MENSAGEM
    String currentLine = "";        // faz uma string para conter os dados de entrada do cliente
    while (client.connected() && t_client - t_antClient <= t_maxConec) {         // loop while SE CLIENTE CONECTADO
      t_client = millis();
      if (client.available()) {             // se houver bytes para ler do cliente,
        char c = client.read();             // LER OS byte
        Serial.write(c);                    // ESCREVE O QUE O CLIENTE MANDOU NA SERIAL
        if (c == '\n') {                    // se o byte é um caractere de nova linha
          if (currentLine.length() == 0) {
            // se a linha atual estiver em branco, você terá dois caracteres de nova linha em uma linha.
            // esse é o fim da solicitação HTTP do cliente, então envie uma resposta:
            String html = "";

            html +=  "HTTP/1.1 200 OK\r\n";
            html += "Content-Type:text/html\r\n\r\n";
            html += ""; //do da resposta HTTP segue o cabeçalho:

            html += "<!DOCTYPE html>";
            html += "<html lang=\"pt-br\">";
            html += "<head>";
            html += " <meta charset=\"utf-8\">";
            html += " <meta name=\"viewport\" content=\"width=device-width initial-scale=1.0\">";
            html += " <title>ESP 32 teste</title>";
            html += " <link href=\"style.css\" rel=\"stylesheet\" type=\"text/css\">";
            html += " <style>";
            

            html += " section{border: solid #000 2px;";
            html += "         border-radius: 10px;";
            html += "         background-color: green;";
            html += "         color: #fff;";
            html += "         display: inline-block;";
            html += "         width: 350px;";
            html += "         height: 215px;}";

            html += "  .botao{ position: absolute;";
            html += "          top: 600px;}";

            html += "  .titulo{ font-size: 45px; ";
            html += "           position: absolute;";
            html += "           left: 20px; ";
            html += "           top: 10px;}";

            html += "  .valor{  font-size: 200px;";
            html += "           position: absolute;";
            html += "           left: 10px;";
            html += "           top: 20px;}";

            html += "  .grandeza{ font-size: 100px;";
            html += "             position: absolute;";
            html += "             left: 220px;";
            html += "             top: 115px;}";

            html += " </style>";
            html += " </head>";

            html += "<body>";
            html += "   <section id=\"tempe\">";
            html += "     <span class=\"titulo\">TEMPERATURA</span><br/>";
            html += "     <span class=\"valor\" id=\"vtemp\"></span>";
            html += "     <span class=\"grandeza\"> ºC</span>";
            html += "   </section>";

            html += " <script>";
            html += "   var temp = document.getElementById(\"tempe\");";
            html += "   var entrada=";
            html +=     pot;
            html += ";";
            html += "   document.getElementById(\"vtemp\").innerHTML=entrada;";
            
            html += "   function adicionatemp(){";


            html += "     if(entrada>=30){";
            html += "       temp.style.backgroundColor=\"#f00\";";
            html += "       temp.style.color=\"#fff\";}";

            html += "     else if(entrada>=27){";
            html += "       temp.style.backgroundColor=\"#ff0\";";
            html += "       temp.style.color=\"#000\";}";

            html += "     else if(entrada>20&&entrada<27){";
            html += "       temp.style.backgroundColor=\"green\";";
            html += "       temp.style.color=\"#fff\";}";

            html += "     else if(entrada<=20&&entrada>=17){";
            html += "       temp.style.backgroundColor=\"#ff0\";";
            html += "       temp.style.color=\"#000\";}";

            html += "     else if(entrada<17){";
            html += "       temp.style.backgroundColor=\"#f00\";";
            html += "       temp.style.color=\"#fff\"";
            html += "     }}";
            html += "     adicionatemp();";
            html += "   </script>";
            html += " </body>";
            html += "</html>";





                          client.print(html);
                          break;
                         } else { // se você obteve uma nova linha, limpe currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // se você tiver qualquer outra coisa além de um caractere de retorno
          currentLine += c;     // adicione-o ao final da currentLine
        }

      }
    }



    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
    Serial.println("_______________________________________________________________________________");
    Serial.println();

  }*/
}
