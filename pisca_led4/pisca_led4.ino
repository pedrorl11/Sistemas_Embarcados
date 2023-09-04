int main(){
  DDRB  |= (1<<DDB5);
  PORTB &= ~(1<<PB5);
  PORTD |= (1<<PD2);
  
  EICRA |= (1<<ISC00);
  EIMSK |= (1<<INT0);
  sei();

  while(1){
  }
}

ISR(INT0_vect){
  PORTB ^=(1<<PB5);
}