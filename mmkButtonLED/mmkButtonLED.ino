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
  while (!Serial) {
    
  }
  randomSeed(analogRead(0));
  valor = random(1000,10000);
}

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
  if (conteudo == "5") {
    Serial.print(valorDisplay, 2);
    Serial.println(" ");
  }
  if (conteudo == "6") {
    Serial.println(11.11, 2);
    Serial.println(" ");
  }

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
    String recebido = leStringSerial(valor/100);

    if (recebido == "5") {
      //Serial.println(valor/100);
      blink(1);
    } else {
      blink(2);
    }
    if (recebido == "3") {
      valor = 0;
    }

  }
}


