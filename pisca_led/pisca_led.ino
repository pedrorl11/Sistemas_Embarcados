int main()
{
   DDRB |= (1<<DDB5); // Configura PB5 como saida (LED interno
                                      // da placa Arduino - pino D13)
   PORTB &= ~(1<<PB5); // Inicia PB5 com nivel logico zero

   while(1)
   {
      PORTB |= (1<<PB5); // Liga LED
      _delay_ms(100); // Espera 500 ms
      PORTB &= ~(1<<PB5); // Desliga LED
      _delay_ms(500); // Espera 500 ms
   }
}