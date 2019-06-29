#include <LiquidCrystal.h> //INCLUSÃO DE BIBLIOTECA

//Serial Config:
//Baud Rate: 9600
//Parity: 8bit / no
//Stop bit: 1
//EOL: <CR><LR> / <013><010>
//Request Value: 5


// constants won't change. They're used here to set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
const int ledPin = 12;

// variables will change:
int buttonState = 0;         // variable for reading the pushbutton status
bool blinking = false;
float valor = 0;


LiquidCrystal lcd(8, 9, 4, 5, 6, 7); //PORTAS DO ARDUINO QUE SÃO UTILIZADAS PELO SHIELD KEYPAD DISPLAY LCD

/**
   Função que lê uma string da Serial
   e retorna-a
*/
String leStringSerial(float valorDisplay) {
  String conteudo = "";
  char caractere;

  // Enquanto receber algo pela serial
  while (Serial.available() > 0) {
    // Lê byte da serial
    caractere = Serial.read();
    // Ignora caractere de quebra de linha
    if (caractere != '\n') {
      // Concatena valores
      conteudo.concat(caractere);
    }
    // Aguarda buffer serial ler próximo caractere
    delay(10);
  }

  //Serial.print("Recebi: ");
  //if (conteudo == "5") {
  //  Serial.print(valorDisplay, 2);
  //  Serial.println(" ");
  //}
  //if (conteudo == "6") {
  //  Serial.println(11.11, 2);
  //  Serial.println(" ");
  //}

  return conteudo;
}

void blink( int cont ) {

  int count = 0;
  while (count < cont) {
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    count++;
  }
}

void imprimirValor( float resultado) {

  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("VALOR A ENVIAR:"); //ESCREVE A FRASE "VALOR A ENVIAR:" NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print(resultado/100);
  //Serial.print(valorDisplay, 2);
  //Serial.println(" ");
}

void setup() {

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledPin, OUTPUT);

  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial:
  Serial.begin(9600);
  while (!Serial) {

  }
  randomSeed(analogRead(0));
  valor = random(1000, 10000);
  valor = valor/100;

  lcd.begin(16, 2); //SETA A QUANTIDADE DE COLUNAS(16) E O NÚMERO DE LINHAS(2) DO DISPLAY. EM SUMA: UMA MATRIZ DE 16 COLUNAS E 2 LINHAS
  imprimirValor(valor);
}

void loop() {

  // Se receber algo pela serial
  if (Serial.available() > 0) {
    // Lê toda string recebida
    String recebido = leStringSerial(valor / 100);

    if (recebido == "5") {
      //Serial.println(valor/100);
      Serial.print(valor/100, 2);
      Serial.println(" ");
    } else if (recebido == "3") {
      valor = 0;
      imprimirValor(valor);
    }
  }

  //lcd.setCursor(0,1); //SETA A POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)
  if ((analogRead(0)) < 80) { //SE A LEITURA DO PINO FOR MENOR QUE 80, FAZ
    //lcd.print ("    DIREITA    "); //ESCREVE NO LCD O TEXTO
    //enviar para Serial
    Serial.print(valor/100, 2);
    Serial.println(" ");
    delay(500);
  }
  else if ((analogRead(0)) < 200) { //SE A LEITURA DO PINO FOR MENOR QUE 200, FAZ
    //lcd.print ("      CIMA     ");  //ESCREVE NO LCD O TEXTO
  }
  else if ((analogRead(0)) < 400) { //SE A LEITURA DO PINO FOR MENOR QUE 400, FAZ
    //lcd.print ("     BAIXO     "); //ESCREVE NO LCD O TEXTO
  }
  else if ((analogRead(0)) < 600) { //SE A LEITURA DO PINO FOR MENOR QUE 600, FAZ
    //lcd.print ("    ESQUERDA   "); //ESCREVE NO LCD O TEXTO
    //zerar valor
    valor = 0;
    imprimirValor(valor);
  }
  else if ((analogRead(0)) < 800) { //SE A LEITURA DO PINO FOR MENOR QUE 800, FAZ
    //lcd.print ("     SELECT    "); //ESCREVE NO LCD O TEXTO
    valor = random(1000, 10000);
    imprimirValor(valor);
  }
}
