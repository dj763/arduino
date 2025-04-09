// Colocamos las variables
int pinsPWM[5];
int pinA = A0;  //un pin analogico
int valorPot = 0;  // almacenamos el valor del  potenciometro

void empezar(){
 //damos un número de pin
  pinsPWM[0] = 11;
  pinsPWM[1] = 10;
  pinsPWM[2] = 9;
  pinsPWM[3] = 6;
  pinsPWM[4] = 5;
}

void setup(){
  empezar();  //  llamamos  a que declare cada numero

  // le decimso en esta lista pon todos como salida
  for (int i = 0; i < 5; i++) {
    pinMode(pinsPWM[i], OUTPUT);
  }

  // le decimos que recibiremos señal de este pin un valor
  pinMode(pinA, INPUT);

  // esto nos sirve para que el arduino mande la info a la computadora
  Serial.begin(9600);
}

void loop(){
  // leer el valor de potenciometro
  valorPot = analogRead(pinA);

  // imprimir lo que veiamos arriba en un aparatado llamado monitor
  Serial.println(valorPot);

  // Apagar todos los led's
  for (int i = 0; i < 5; i++) {
    analogWrite(pinsPWM[i], 0);    // Apagar todos los LEDs
  }

  // Verificar el ensendido de cada led
  if (valorPot >= 0 && valorPot < 205) {   //  (0 a 204)
    analogWrite(pinsPWM[0], 255); 
  } 
  else if (valorPot >= 205 && valorPot < 410){ //{ (205 a 409)
    analogWrite(pinsPWM[1], 255);  
  } 
  else if (valorPot >= 410 && valorPot < 615) {   //(410 a 614)
    analogWrite(pinsPWM[2], 255); 
  } 
  else if (valorPot >= 615 && valorPot < 820) {  // (615 a 819)
    analogWrite(pinsPWM[3], 255);  
  } 
  else if (valorPot >= 820 && valorPot <= 1023) { // (820 a 1023)
    analogWrite(pinsPWM[4], 255);  
  }
  
  delay(100); //brinda estabilidad
}
