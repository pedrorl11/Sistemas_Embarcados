int main(){
  DDRB &=~ (1<<2) | (1<<3);//entrada 
  PORTD |= (1<<PD2) | (1<<PD3); //pullup
  DDRD |= (1<<6) | (1<<7);//saida

  EICRA |= (1<< ISC01) | (1<< ISC11);//interrompe ao descer
  EIMSK |= (1<< INT0) | (1<< INT1);// configura que os dois pinos tem interrupcao
  sei(); //habilita as interrupções
  while(1){
  }
}

ISR(INT1_vect){//vermelho
  PORTD ^= (1<<7);//troca o estado do vermelho
  if (!(PIND &(1<<3))){//apaga o verde se tiver ligado
    PORTD &=~(1<<6);
  }
}

ISR(INT0_vect){//verde
  if(!(PIND & (1<<2)) & !(PORTD & (1<<7))){//se foi pressionado e se o vermelho ta apagado
    PORTD ^= (1<<6);//troca o estado do verde
  }
}