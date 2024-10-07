#include <Adafruit_GFX.h>      
#include <Adafruit_ST7735.h>   
#include <PulseSensorPlayground.h>

// pinos de controle
#define TFT_CS     10   // Chip Select
#define TFT_RST    9    // Reset (ou -1 se não for usado)
#define TFT_DC     8    // Data/Command

//Variáveis Sensor de Pulso
const int PulseWire = 0;
const int LED = LED_BUILTIN;
int Threshold = 550; 


PulseSensorPlayground pulseSensor; //Cria instância do sensor de pulso
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST); //Cria instância da Tela

void setup() {

  Serial.begin(9600); 
    pulseSensor.analogInput(PulseWire);   
    pulseSensor.blinkOnPulse(LED);       
    pulseSensor.setThreshold(Threshold);

    if (pulseSensor.begin()) {
    Serial.println("We created a pulseSensor Object !");  //This prints one time at Arduino power-up,  or on Arduino reset.  
    }
  

  // Inicializa a comunicação com a tela
  tft.initR(INITR_GREENTAB); 
  tft.invertDisplay(true);
  
  // Prepara a tela
  tft.fillScreen(ST7735_BLACK);  // Preenche a tela com cor preta
  tft.setTextColor(ST7735_WHITE); // Define a cor do texto como branca
  tft.setTextSize(2); 
  
  tft.setCursor(28, 20);  // Define a posição inicial do texto (x, y)
  tft.println("IFTECH"); // Define o texto
  
  tft.setTextSize(1);
  tft.setCursor(38, 40);  
  tft.println("Sensor de");
  tft.setCursor(50, 50);
  tft.println("Pulso");

  tft.fillCircle(55, 80, 10, ST7735_RED);   // Primeira metade do coração (circulo esquerdo)
  tft.fillCircle(75, 80, 10, ST7735_RED);   // Segunda metade do coração (circulo direito)
  tft.fillTriangle(65, 105, 45, 80, 85, 80, ST7735_RED); //Ponta do Coração
}

void loop() {
  if (pulseSensor.sawStartOfBeat()) {            // Checa se o sensor captou algum sinal
    int myBPM = pulseSensor.getBeatsPerMinute();  // Chama a função que retorna o BPM e guarda na variável.

    //Testes do Sensor, não sendo necessário no produto final.
    Serial.println("♥  A HeartBeat Happened ! "); // If test is "true", print a message "a heartbeat happened".
    Serial.print("BPM: ");                        // Print phrase "BPM: " 
    Serial.println(myBPM);                        // Print the value inside of myBPM.

    //Reseta o bpm
    tft.fillRect(0, 120, 100, 30, ST7735_BLACK);

    //Imprime o bpm
    tft.setTextSize(2);
    tft.setCursor(50, 120);
    tft.println(myBPM);
  }

    delay(1000);                    // delay de 1 segundo para o usuário conseguir entender.
}
