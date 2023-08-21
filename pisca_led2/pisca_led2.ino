int main()
{
   DDRB |= (1<<5); // configura pino D13 do arduino como saida
   PORTB &=~(1<<5); // apaga LED no pino D13
   DDRD &=~(1<<7); // configura pino D7 do arduino como entrada
   PORTD |= (1<<7); // habilita pull-up interno do pino D7 do arduino

   while(1)
   {
      if(!(PIND & (1<<7))) PORTB |= (1<<5);
      else PORTB &=~(1<<5);
   }
}