#include <LiquidCrystal_I2C.h>

// Dirección del LCD I2C
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pines de botones
int pinIniciar = 2;  // Botón para iniciar
int pinReiniciar = 3;  // Botón para reiniciar
int pinPausa = 4;  // Botón para pausar

//pines de led's
int pinRojo = 9;
int pinVerde =8; 

// Variables para el cronómetro
long tiempoAnterior = 0;
int centesimos = 0;
int segundos = 0;
int minutos = 0;
int horas = 0;
int estado = 0; // 0 = detenido, 1 = corriendo, 2 = pausado

void setup() {
  // Configuración de los pines de los botones como entradas
  pinMode(pinIniciar, INPUT);   
  pinMode(pinReiniciar, INPUT);   
  pinMode(pinPausa, INPUT);  
  
  //configuramos los led's
  pinMode(pinRojo, OUTPUT);
  pinMode(pinVerde, OUTPUT);

  // Configuración del LCD
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DJ CRONOMETRO");
  delay(1500);  // Pausa para mostrar el mensaje

  mostrarTiempo();
}

void loop() {
  // Comprobar los botones
  if (digitalRead(pinIniciar) == LOW) {
    estado = 1; // Iniciar cronómetro
    delay(200);  // Anti-rebote simple
  }
  
  //OMITIRE ESTE IF YA QUE NO NECESITAREMOS EL DE REINICIAR
  /*if (digitalRead(pinReiniciar) == LOW) {
    reiniciarCronometro();  // Reiniciar cronómetro
    delay(200);  // Anti-rebote simple
  }*/ 
  if (digitalRead(pinPausa) == LOW) {
    estado = 2;  // Alternar entre pausar y continuar
    delay(200);  // Anti-rebote simple
  }

  // Si el cronómetro está en ejecución, actualizarlo
  if (estado == 1) {
    actualizarCronometro();
  /*  digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde,HIGH);
    delay(500);
    digitalWrite(pinVerde,LOW);*/
  }
  if(estado == 2){
    digitalWrite(pinRojo, HIGH);
    digitalWrite(pinVerde,LOW);
  }}

void actualizarCronometro() {
  if (millis() - tiempoAnterior >= 10) {  // Actualizar cada 10ms
    tiempoAnterior = millis();
    centesimos++;
    if(centesimos == 20 || centesimos == 60){
    digitalWrite(pinRojo, LOW);
    digitalWrite(pinVerde,HIGH);
    }
    if (centesimos == 100) {
      centesimos = 0;
      segundos++;
    digitalWrite(pinVerde,LOW);
    }
    if (segundos == 60) {
      segundos = 0;
      minutos++;
    }
    if (minutos == 60) {
      minutos = 0;
      horas++;
    }

    mostrarTiempo();
  }
}

void reiniciarCronometro() {
  horas = minutos = segundos = centesimos = 0;
  mostrarTiempo();
}

void mostrarTiempo() {
  lcd.setCursor(0, 1);

  // Mostrar horas
  if (horas < 10) lcd.print("0");
  lcd.print(horas);
  lcd.print(":");

  // Mostrar minutos
  if (minutos < 10) lcd.print("0");
  lcd.print(minutos);
  lcd.print(":");

  // Mostrar segundos
  if (segundos < 10) lcd.print("0");
  lcd.print(segundos);

  // Mostrar centésimos
  lcd.print(".");
  if (centesimos < 10) lcd.print("0");
  lcd.print(centesimos);
}
