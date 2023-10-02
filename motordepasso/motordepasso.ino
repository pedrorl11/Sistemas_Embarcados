volatile int t = 0;
int lista[8] = {0b00001000, 0b00011000, 0b00010000, 0b00110000, 
0b00100000, 0b01100000, 0b01000000, 0b01001000};
int contador = 0;

int main() {
  DDRB &=~ (1<<0) | (1<<1); // entrada 
  PORTB |= (1<<0) | (1<<1); // pullup
  DDRD |= (1<<PD3) | (1<<PD4) | (1<<PD5) | (1<<PD6); // saida

  TCCR0A = 0b00000010; // Configura TIMER0 no modo ctc
  TCCR0B = 0b00000010; // Prescale = 8 com t_OV = 128 us
  OCR0A = 249;
  TIMSK0 = 0b00000010; // Habilita interrupcao por overflow
  sei(); // Habilita interrupcoes globais

  
  while(1) {
    if (t == 800) {
      if (!(PINB & (1<<0)) && (PINB & (1<<1))){
        PORTD = lista[contador];
        if (contador == 7){
          contador = 0;
        } else {
          contador++;
        }
      } else if ((PINB & (1<<0)) && !(PINB & (1<<1))){
        if (contador == 0){
          contador = 7;
        } else {
          contador--;
        }
        PORTD = lista[contador];
      }     
      t = 0;
    }
  }
}

ISR(TIMER0_COMPA_vect) { // Rotina de interrupcao 
  t++;
}