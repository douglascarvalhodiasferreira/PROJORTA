#ifndef MANDA_FLUXO_H
#define MANDA_FLUXO_H


class fluxo {
  
  private:
    
    unsigned long int _tempo_antes = millis();
    int _fator_calibracao = 7;
    int _L_minuto;
    int _volume;                   // = fluxo / 60;
    int _volume_total;             // += volume;
    long unsigned int _cp_contador;   //copia do contador
    volatile unsigned long _contador; //contador
    String _Dados;
    String _nome;

  public:
    fluxo(String n): _nome(n) {} //

    void Acumula_contado() {
      _cp_contador   += _contador;
      _L_minuto       = (((millis() - _tempo_antes) / 1000) * _cp_contador) / _fator_calibracao; //conversao do valor de pulsos para L/min
      _volume         = _L_minuto / 60;
      _volume_total  += _volume;
      _tempo_antes = millis();
      _contador = 0;
    }
    
    void organiza_dados() {
      _Dados  = "/ESP32/salvarf.php?";
      _Dados += "n=";
      _Dados += _nome;
      _Dados += "&vt=";
      _Dados += _volume_total;
    }
    
    String getdados()   {return _Dados;}

    void set_contador() {_contador++;  }

    void apaga_cp_contador() {
      _cp_contador  = 0;
      _volume       = 0;
      _volume_total = 0;
    }
};
#endif
