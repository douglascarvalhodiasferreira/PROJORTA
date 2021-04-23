// ______________ PREENCHE STRUCT DATE______

Date getDate()
{

  // Serial.println (timeClient.getFormattedDate());
  //Serial.println ("!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
  //Recupera os dados de data e horário usando o client NTP
  char* strDate = (char*)timeClient.getFormattedDate().c_str();

  //Passa os dados da string para a struct
  Date date;
  sscanf(strDate, "%d-%d-%dT%d:%d:%dZ",
         &date.ano,
         &date.mes,
         &date.dia,
         &date.hora,
         &date.minutos,
         &date.segundos);

  //Dia da semana de 0 a 6, sendo 0 o domingo
  date.diadasemana = timeClient.getDay();
  return date;
}


//char letra= 'a';
/*if (Serial.find('a')){

  Serial. print ("hora formatada: ");
  Serial. println (timeClient.getFormattedTime ());
  char* diasemana=dayOfWeekNames[date.diadasemana];
  //int epoch = timeClient. getEpochTime();

  Serial. print ("dia da semana: ");
  Serial. println (diasemana);
  Serial. print ("dia: ");
  Serial. println (date.dia);
  Serial. print ("mes: ");
  Serial. println (date.mes);
  Serial. print ("ano: ");
  Serial. println (date.ano);
  Serial. print ("hora: ");
  Serial. println (date.hora);
  Serial. print ("minuto: ");
  Serial. println (date.minutos);
  Serial. print ("segundo: ");
  Serial. println (date.segundos);
  Serial. println ("############################################# ");
  //Serial. println (epoch);
  }*/

//Serial.println("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
//Serial.println(hora);
