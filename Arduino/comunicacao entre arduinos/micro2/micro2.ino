volatile bool send = false;
volatile int t;
volatile char input = UDR0;

int main() {
  DDRD &= ~(1 << 2);
  PORTD |= (1 << 2);
  DDRB |= (1 << DDB5);

  // Habilita a interrupção da serial
  UBRR0L = 103;
  UBRR0H = 0;
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
  UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);

  EICRA = 0b00000011;  // configura interrupcao por borda de subida
  EIMSK = 0b00000001;  // habilita interrupcao do pino INT0

  TCCR0A = 0b00000010;
  TCCR0B = 0b00000010;
  TIMSK0 = 0b00000010;
  OCR0A = 249;
  sei();

  while (1) {
    if ((t >= 2000) && (input == 'L')) {
      t = 0;
      PORTB ^= (1 << PB5);
    }

    if(input == 'D'){
      PORTB &= ~(1 << PB5);
    }
  }
}

ISR(INT0_vect) {
  char data;
  if (send == false) {
    send = true;
    data = 'X';
    if (UCSR0A & (1 << UDRE0)) UDR0 = data;
  } else {
    send = false;
    data = 'Y';
    if (UCSR0A & (1 << UDRE0)) UDR0 = data;
  }
}

ISR(USART_RX_vect) {
  input = UDR0;
}

ISR(TIMER0_COMPA_vect) {
  t++; 
}