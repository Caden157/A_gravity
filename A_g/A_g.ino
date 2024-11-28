const int triggerPin = 5; 
const int echoPin = 6;    

// Variáveis
long duration;
float distance;
unsigned long startTime = 0;   
unsigned long elapsedTime = 0; 
int detectionCount = 0;       
int cycleCount = 0;            
unsigned long elapsedTimesBuffer[10];
int bufferIndex = 0; 

void showBufferInSerial() {
  Serial.println("Exibindo os últimos 10 tempos:");
  for (int i = 0; i < 10; i++) {
    Serial.print("Tempo ");
    Serial.print(i + 1);
    Serial.print(": ");
    Serial.print(elapsedTimesBuffer[i] / 1000.0);  // Exibe o tempo em segundos
    Serial.println(" segundos");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;

  if (distance >= 1 && distance <= 5) {
    if (detectionCount == 0) {
      startTime = millis();
      Serial.println("Cronômetro iniciado!");
      detectionCount++;
    } else if (detectionCount == 2) {
      elapsedTime = millis() - startTime;
      Serial.print("Cronômetro parado! Tempo decorrido: ");
      Serial.print(elapsedTime / 1000.0);
      Serial.println(" segundos.");

      elapsedTimesBuffer[bufferIndex] = elapsedTime;
      bufferIndex++;

      if (bufferIndex == 10) {
        showBufferInSerial();  
        bufferIndex = 0;       
      }

      detectionCount = 0;
    } else {
      detectionCount++;
    }
    
    delay(500);
  }
  delay(60);
}
