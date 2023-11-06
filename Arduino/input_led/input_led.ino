int main() {
  char data;

  DDRD &= ~(1 << 2);
  PORTD |= (1 << 2);
  DDRB |= (1 << PB5);

  // Habilita a interrupção da serial
  UBRR0L = 103;
  UBRR0H = 0;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);


  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC01);
  sei();

  while (1) {
    char input = UDR0;

    if (input == 'L') {
      PORTB |= (1 << PB5);
    }
    if (input == 'D') {
      PORTB &= ~(1 << PB5);
    }

    if (!(PIND & (1 << PD2))) {
      data = 'X';
      if (UCSR0A & (1 << UDRE0)) UDR0 = data;
    }
  }
}
