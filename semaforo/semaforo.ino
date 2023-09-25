char sec = 1;
char apertou = false;
volatile int t = 0;

int main(){
  DDRB &=~ (1<<2);//entrada 
  PORTD |= (1<<PD2); //pullup
  DDRD |=  (1<<3) | (1<<4) | (1<<5) | (1<<6) | (1<<7); //saida
  EICRA |= (1<<1);//interrompe ao descer
  EIMSK |= (1<<0);// configura que o pino tem interrupcao

  // Configura TIMER0 no modo normal
  TCCR0A = 0b00000010; 
  TCCR0B = 0b00000010; 
  OCR0A = 249;
  TIMSK0 = 0b00000010; 
  PORTD |= (1<<5);
  PORTD |= (1<<6);

  sei(); //habilita as interrupções

  while(1){
    if (t == 8000 & apertou == true){   
      sec++;                          
      t = 0;
    }
    if(sec == 12){
      sec = 1;
      apertou = false;
      PORTD &=~ (1<<3);
    }
    if(sec <= 6){// Verde (siga): 6 segundos
      PORTD &=~ (1<<7);
      PORTD |= (1<<6);
      PORTD |= (1<<5);
    }
    if(sec == 7){// Amarelo (atenção): 1 segundos
      PORTD &=~ (1<<5);
      PORTD |= (1<<4);
    }
    if(sec == 8 & sec <= 11){// Vermelho (parado): 4 segundos
      PORTD &=~ (1<<4);
      PORTD |= (1<<3);
    }
    if(sec == 9){// Verde (siga): 3 segundos
      PORTD &=~ (1<<6);
      PORTD |= (1<<7);
    }
    if(sec >= 10){// Vermelho (parado): Pisca em uma frequência de aproximadamente 4 Hz durante 2 segundos, depois fica em vermelho até um próximo ciclo.
      PORTD &=~ (1<<7);
      if(t % 500 == 0){
        PORTD ^= (1<<6);
      }
    }
  }
}

ISR(INT0_vect){//apertou = comeca a alterar
  sec = 1;
  apertou = true;
}

ISR(TIMER0_COMPA_vect) // Rotina de interrupcao
{
 t++;
}