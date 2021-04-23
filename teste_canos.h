#ifndef TESTE_CANOS_H_INCLUDE
#define TESTE_CANOS_H_INCLUDE

#include <arduino.h>

class cano {
  
  private:
    int  _Pino;
    bool _Cano_teste = 1;
    bool _Cano;
    
    
  public:
    cano(int p): _Pino(p) {pinMode(_Pino, INPUT);}
    
    bool get_StatusCano() {return _Cano;}
    
    bool testa_cano() {
      _Cano = digitalRead(_Pino);
      bool * cano = &_Cano;
      if (*cano != _Cano_teste) {
        vTaskDelay(1000);
        if (*cano != _Cano_teste) {
          _Cano_teste = *cano;
          return true;
        }
      } else {return false;}
    }
};

#endif
