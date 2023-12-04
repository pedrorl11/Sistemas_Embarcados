volatile bool brunetti = true;
volatile int cont = 0;
int main() {
  DDRD &= ~(1 << 2);
  PORTD |= (1 << 2);
  DDRB |= (1 << PB5);

  // Habilita a interrupção da serial
  UBRR0L = 103;
  UBRR0H = 0;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);


  EICRA = 0b00000011;  // configura interrupcao por borda de subida
  EIMSK = 0b00000001;  // habilita interrupcao do pino INT0
  sei();

  while (1) {
    char input = UDR0;
    if (input == 'X') {
      PORTB |= (1 << PB5);
    }
    if (input == 'Y') {
      PORTB &= ~(1 << PB5);
    }
    if (!(PIND & (1 << PD2)) && cont == 0) {
      if (UCSR0A & (1 << UDRE0)) UDR0 = 'L';
      cont = 1;
    } 

    if(PIND & (1 << PD2) && cont == 1){
      cont = 0;
      if (UCSR0A & (1 << UDRE0)) UDR0 = 'D';
    }
  }
}

ISR(INT0_vect){
  UDR0 = 'D';
}