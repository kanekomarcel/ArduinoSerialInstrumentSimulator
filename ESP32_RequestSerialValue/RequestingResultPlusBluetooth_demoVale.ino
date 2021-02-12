#include <Wire.h> //Biblioteca para I2C
#include <BLEDevice.h>
#include <BLEServer.h>
#include <BLEUtils.h>
#include <BLE2902.h>
#include <HardwareSerial.h>

#define SERVICE_UUID "ab0828b1-198e-4351-b779-901fa0e0371e"
#define CHARACTERISTIC_UUID_RX "4ac8a682-9736-4e5d-932b-e9b31405049c"
#define CHARACTERISTIC_UUID_TX "0972EF8C-7613-4075-AD52-756F33D4DA91"
#define RXD2 16
#define TXD2 17
float i = 0;
//String conteudo = "";
String valorRes = "";

BLECharacteristic *characteristicTX; //Através desse objeto iremos enviar dados para o client
bool deviceConnected = false; //Controle de dispositivo conectado

//Callback para eventos das características. Configurado pra printar o valor no serial quando receber um dado
class CharacteristicCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *characteristic) {
      //Retorna ponteiro para o registrador contendo o valor atual da caracteristica
      std::string rxValue = characteristic->getValue();
      //Verifica se existe dados (tamanho maior que zero)
      if (rxValue.length() > 0) {
        for (int i = 0; i < rxValue.length(); i++) {
          Serial.print(rxValue[i]);
        }
        Serial.println();
      }
    }
};

//Callback para receber os eventos de conexão de dispositivos
class ServerCallbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Dispositivo conectado");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Dispositivo desconectado");
    }
};


void setup() {


  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2);
  delay(100);
  //pinMode(LED1pin, OUTPUT);
  //pinMode(LED2pin, OUTPUT);
  BLEDevice::init("IoT_Sensor"); //Nome do dispositivo
  BLEServer *server = BLEDevice::createServer(); //Cria um BLE Server
  server->setCallbacks(new ServerCallbacks()); //Seta o callback do server
  BLEService *service = server->createService(SERVICE_UUID); //Cria o BLE Service
  characteristicTX = service->createCharacteristic(CHARACTERISTIC_UUID_TX,
                     BLECharacteristic::PROPERTY_NOTIFY); //Cria o BLE Characteristic para envio de dados
  characteristicTX->addDescriptor(new BLE2902());

  BLECharacteristic *characteristic = service->createCharacteristic(CHARACTERISTIC_UUID_RX,
                                      BLECharacteristic::PROPERTY_WRITE); //Cria o BLE Characteristic para recebimento de dados
  characteristic->setCallbacks(new CharacteristicCallbacks());

  service->start(); //Inicia o service
  server->getAdvertising()->start(); //Inicia o advertising (descoberta do ESP)
  Serial.println("Aguardando um dispositivo conectar");
}

void loop() {

  String conteudo = "";
  char caractere;
  Serial.println("Teste");
  //Serial2.write(0x05);
  //Serial2.write(0x05);
  if (Serial2.available() > 0) {
    Serial.println("OK");
    while (Serial2.available()) {
      // Lê byte da serial
      caractere = char(Serial2.read());
      // Ignora caractere de quebra de linha
      if (caractere != '\n' && caractere != '\r') {
        // Concatena valores
        conteudo.concat(caractere);
      }
      // Aguarda buffer serial ler próximo caractere
      delay(10);
    }
    Serial.println(valorRes);
    valorRes = conteudo;
  } else {
    Serial2.write(0x05);
    Serial2.println();
    Serial.println("Enviada Requisicao");
  }

  //Serial2.write(0x05); //request value ENQ
  

  //Se algum dispositivo está conectado
  if (deviceConnected) {
    char txString[8];
    //dtostrf(i, 2, 2, txString);
    valorRes.toCharArray(txString, 8);
    characteristicTX->setValue(txString);
    characteristicTX->notify();
    //i = i + 0.5;
    //if (i > 50){
    //  i = 0;
    //}
  }


  delay(1000);
}
