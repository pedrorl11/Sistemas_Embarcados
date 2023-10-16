// Utilizando um potenciômetro de 10k Ohms e oito LEDs conectados cada um em um 
// pino do PORTD, construa um medidor que acenda os LEDs, mantendo os anteriores
// acesos, em sequência a medida que o potenciômetro sai de sua posição inicial
// (0 Ohms - todos os LEDs apagados) até a posição final (10k Ohms - todos os LEDs acesos).
// Quando a leitura da entrada analógica for inferior a 5% do fundo de escala, o primeiro LED
// deverá piscar em uma frequência de 2 Hz (utilize a interrupção de timer para gerar a base de tempo).


int lista[8] = {0b10000000, 0b11000000, 0b11100000, 0b11110000, 
0b11111000, 0b11111100, 0b11111110, 0b11111111};

volatile int t = 0;

int main() {
  DDRD = 0b11111111; 
  volatile int adc_value=0;

  ADMUX = 0b01000011;
  ADCSRA |= (1<<ADEN)|(1<<ADPS1)|(1<<ADPS0);
  DIDR0 |= (1<<ADC2D);

  TCCR0A = 0b00000010; // Configura TIMER0 no modo ctc
  TCCR0B = 0b00000010; // Prescale = 8 com t_OV = 128 us
  OCR0A = 249;
  TIMSK0 = 0b00000010; // Habilita interrupcao por overflow
  sei(); // Habilita interrupcoes globais

  while(1){
    ADCSRA |= (1<<ADSC); // inicia a conversao
    while(ADCSRA & (1<<ADSC)); // aguarda fim da conversao
    adc_value = ADC; // salva leitura do ADC na variavel adc_value

    if(adc_value == 0){
      PORTD = 0b00000000;
    }
    else if(adc_value < 50){
      if(t < 800){
        PORTD |= (1 << PD7);
      }else{
        PORTD &=~ (1 << PD7);
      }
    }else{
      int leds = adc_value >>7;
      PORTD = lista[leds];
    }
  }
}


ISR(TIMER0_COMPA_vect) { // Rotina de interrupcao 
  t++;

  if(t>=1600){
    t = 0;
  }
}