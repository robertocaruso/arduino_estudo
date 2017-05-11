/*
Desenvolvido por Roberto Caruso
Controle de temperatura
25-04-2017 - um sensor LM35 e um rele
Posteriormente substituir sensor para DS18B20
*/
	//---BIBLIOTECAS
#include <LiquidCrystal.h>
  //---CONSTANTES
const int LM35 = 0;
float temperatura =0;
int ADClido = 0;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int Botao1 = 7;
int Botao2 = 6;
int aumenta, diminui;
int Rele = 9;
int EstadoBotao1, EstadoBotao2 = 0;
int EstadoRele = 0;
int temp_max = 0;
unsigned long previousMillis = 0;
const long interval = 1000;
  //---SETUP
void setup() {
analogReference(INTERNAL);
pinMode(Botao1, INPUT);
pinMode(Botao2, INPUT);
pinMode(Rele, OUTPUT);
}
   //---LOOP
void loop() {
  EstadoBotao1 = digitalRead(Botao1);
  EstadoBotao2 = digitalRead(Botao2);
  //EstadoRele = digitalWrite(Rele);
  ADClido = analogRead(LM35);
   unsigned long currentMillis = millis();
   //Timer para ler o valor da temperatura
  if (currentMillis - previousMillis >= interval)
  {
    temperatura = ADClido * 0.1075268817204301;
    previousMillis = currentMillis;
   
  }
  if (EstadoBotao1 == HIGH){
    temp_max = temp_max + 1;
  }
  if (EstadoBotao2 == HIGH){
    temp_max = temp_max - 1;
  }
   //---INFO no LCD 
   lcd.begin(16, 2);
   lcd.setCursor(0,0);
   lcd.print("HTL");
   lcd.setCursor(5,0);
   lcd.print(temperatura);
   lcd.setCursor(0,1);
   lcd.print("TrG");
   lcd.setCursor(5,1);
   lcd.print(temp_max);
   delay(500);
   //---RELE
   if (temperatura < (temp_max - 0.2)){
   digitalWrite(Rele, HIGH);
   }
     else {
       digitalWrite(Rele, LOW);
   }
   
}
