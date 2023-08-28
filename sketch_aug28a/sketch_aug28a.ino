int main(){
  DDRD = 0b01111111; //configura pinos de entrada e saida
  DDRB &=~(1<<0); // configura pino D7 do arduino como entrada
  PORTB |= (1<<0);
  char cont = 0;

  while(1){

    if(!(PINB & (1<<0))){
      _delay_ms(200);
      cont ++;
    }

    if(cont == 0){
      //0 abcdef
      PORTD = 0b00111111;
    }
    
    else if(cont == 1){
      //1 bc
      PORTD = 0b00000110;
    }

    else if(cont == 2){
      //2 abged
      PORTD = 0b01011011;
    }

    else if(cont == 3){
      //3 abgcd
      PORTD = 0b01001111;
    }

    else if(cont == 4){
      //4 fgbc
      PORTD = 0b01100110;
    }
    else if(cont == 5){
      //5 afgcd
      PORTD = 0b01101101;
    }

    else if(cont == 6){
      //6 afgedc
      PORTD = 0b01111101;
    }

    else if(cont == 7){
      //7 abc
      PORTD = 0b00000111;
    }

    else if(cont == 8){
      //8 abcdefg
      PORTD = 0b01111111;
    }

    else if(cont == 9){
      //9 abcdfg
      PORTD = 0b01101111;
      cont = -1;
    }
  }
}