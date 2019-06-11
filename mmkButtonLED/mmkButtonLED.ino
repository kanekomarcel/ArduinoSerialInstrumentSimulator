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

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(ledPin, OUTPUT);
  
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  // initialize serial:
  Serial.begin(9600);

  randomSeed(analogRead(0));
  valor = random(1000,10000);
}

/**
   Função que lê uma string da Serial
   e retorna-a
*/
String leStringSerial() {
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

  Serial.print("Recebi: ");
  Serial.println(conteudo);

  return conteudo;
}

// the loop function runs over and over again forever
void loop() {

  buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(LED_BUILTIN, HIGH);
    //blinking = not(blinking);
    valor = random(1000,10000);
    delay(500);
    
  } else {
    // turn LED off:
    digitalWrite(LED_BUILTIN, LOW);
  }

  // Se receber algo pela serial
  if (Serial.available() > 0) {
    // Lê toda string recebida
    String recebido = leStringSerial();

    if (recebido == "5") {
      digitalWrite(ledPin, HIGH);
      //
      Serial.println(valor/100);
      delay(1000);
      digitalWrite(ledPin, LOW);
    }
    if (recebido == "3") {
      valor = 0;
      Serial.println(valor);
      digitalWrite(ledPin, LOW);
      //
    }

  }

  if (blinking) {
    //digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    //delay(1000);                       // wait for a second
    //digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    //delay(1000);
  }// wait for a second
}


