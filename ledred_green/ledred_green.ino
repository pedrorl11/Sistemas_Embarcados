int main(){
  DDRB &=~ (1<<2) | (1<<3);
  PORTD |= (1<<PD2) | (1<<PD3);
  DDRD |= (1<<6) | (1<<7);

  while(1){

  }
}