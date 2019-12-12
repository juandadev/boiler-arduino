#include <LiquidCrystal.h>

/* Conexión
PIN8 - LCD4 (RS)
PIN9 - LCD6 (E)
 
PIN10 - LCD11 (D4)
PIN11 - LCD12 (D5)
PIN12 - LCD13 (D6)
PIN13 - LCD14 (D7)
*/

//Inicializar objeto del LCD
LiquidCrystal lcd(8, 9, 10, 11, 12, 13); //(RS, E, D4,D5, D6, D7)

const int potenc = A0;//Declarando el pin del potenciometro
int potencValue = 0;//Variable para almacenar el valor del potenciometro

//LEDs indicadores de configuración
const int apagado = 7;
const int invierno = 6;
const int verano = 5;

//LEDs indicadores de estado
const int funcionando = 4;
const int detenido = 1;

//Botón para iniciar proceso de calentamiento
const int iniciar = 2;
const int elegir = 3;//Botón para elegir el tiempo de calentamiento
int contador = 1;//Timer para el tiempo de calentamiento del boiler
String actual = "";//Variable para almacenar la configuración que se usa al momento de empezar el contador

//Variables para el debounce
const int timeThreshold = 150;
long startTime = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);   // Inicia un LCD 16x02 (columnas,fila)
  lcd.setCursor(0, 0);   // Pone el cursor en las coordenadas (0,0)
  lcd.print("Boiler");   // Escribe en el LCD
  lcd.setCursor(0, 1);
  lcd.print("Electrico!");

  //Establecer pines de salida (LEDs)
  pinMode(verano, OUTPUT);  
  pinMode(invierno, OUTPUT);  
  pinMode(apagado, OUTPUT);  
  pinMode(funcionando, OUTPUT);  
  pinMode(detenido, OUTPUT);
  digitalWrite(detenido, HIGH);
  
  //Establecer pin de entrada (Boton)
  pinMode(iniciar, INPUT);
  pinMode(elegir, INPUT);
  attachInterrupt(digitalPinToInterrupt(iniciar), startCount, FALLING);//Declarando interrupción cuando el botón pase de HIGH a LOW
  attachInterrupt(digitalPinToInterrupt(elegir), chooseConf, FALLING);
}

void loop() {
  // put your main code here, to run repeatedly:
  potencValue = analogRead(potenc);//Almacenar valor que arroja el potenciometro

  //Prender LEDs a medida que cambia valor del potenciometro
  switch (potencValue) {
    case 100:
      contador = 1;

      digitalWrite(apagado, LOW);
      digitalWrite(invierno, LOW);
      digitalWrite(verano, HIGH);

      lcd.clear();
      lcd.print("Verano");
      lcd.setCursor(0, 1);
    break;

    case 500:
      contador = 1;

      digitalWrite(verano, LOW);
      digitalWrite(invierno, HIGH);
      digitalWrite(apagado, LOW);

      lcd.clear();
      lcd.print("Invierno");
      lcd.setCursor(0, 1);
    break;

    case 900:
      contador = 1;

      digitalWrite(apagado, HIGH);
      digitalWrite(invierno, LOW);
      digitalWrite(verano, LOW);

      lcd.clear();
      lcd.print("Apagado");
      lcd.setCursor(0, 1);
    break;
  }

  if (digitalRead(funcionando) == HIGH) {
    do {
      if (contador == 1) {
        digitalWrite(funcionando, LOW);
        digitalWrite(detenido, HIGH);
      }
      
      contador--;
      lcd.clear();
      lcd.print(actual);
      lcd.setCursor(0, 1);
      lcd.print(contador);
      delay(1100);
    } while (contador == 1);
  }
}

void startCount() {
  if (millis() - startTime > timeThreshold) {//Método para evitar el rebote del botón (Debounce)
    //Lógica de la interrupción
    if (digitalRead(verano) == HIGH && contador > 1) {
      actual = "Verano";
      lcd.print(contador);

      digitalWrite(detenido, LOW);
      digitalWrite(funcionando, HIGH);
    } else if (digitalRead(invierno) == HIGH && contador > 1) {
      actual = "Invierno";
      lcd.print(contador);

      digitalWrite(detenido, LOW);
      digitalWrite(funcionando, HIGH);
    } else if (digitalRead(apagado) == HIGH) {
      contador = 1;
      actual = "Apagado";
      lcd.clear();
      lcd.print("Selecciona una");
      lcd.setCursor(0, 1);
      lcd.print("configuracion!");
    } else if (digitalRead(verano) == LOW && digitalRead(invierno) == LOW && digitalRead(apagado) == LOW) {
      contador = 1;
      actual = "Apagado";
      lcd.clear();
      lcd.print("Selecciona una");
      lcd.setCursor(0, 1);
      lcd.print("configuracion!");
    } else if (contador == 0) {
      contador = 1;

      lcd.clear();
      lcd.print("Selecciona el");
      lcd.setCursor(0, 1);
      lcd.print("tiempo!");
    } else {
      lcd.clear();
      lcd.print("Selecciona el");
      lcd.setCursor(0, 1);
      lcd.print("tiempo!");
    }
    startTime = millis();//Termina método para el debounce
  }
}

void chooseConf() {
  if (millis() - startTime > timeThreshold) {//Método para evitar el rebote del botón (Debounce)
    //Lógica de la interrupción
    if (digitalRead(verano) == HIGH || digitalRead(invierno) == HIGH) {
      switch (contador) {
        case 0:
          contador = 16;
          lcd.clear();
          lcd.print("Tiempo:");
          lcd.setCursor(0, 1);
          lcd.print("15s");
        break;

        case 1:
          contador = 16;
          lcd.clear();
          lcd.print("Tiempo:");
          lcd.setCursor(0, 1);
          lcd.print("15s");
        break;

        case 16:
          contador = 21;
          lcd.clear();
          lcd.print("Tiempo:");
          lcd.setCursor(0, 1);
          lcd.print("20s");
        break;

        case 21:
          contador = 26;
          lcd.clear();
          lcd.print("Tiempo:");
          lcd.setCursor(0, 1);
          lcd.print("25s");
        break;

        case 26:
          contador = 16;
          lcd.clear();
          lcd.print("Tiempo:");
          lcd.setCursor(0, 1);
          lcd.print("15s");
        break;
      }
    } else {
      lcd.clear();
      lcd.print("Selecciona una");
      lcd.setCursor(0, 1);
      lcd.print("configuracion!");
    }
    startTime = millis();//Termina método para el debounce
  }
}