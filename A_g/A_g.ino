// Definição dos pinos
const int triggerPin = 5;  // Pino Trigger
const int echoPin = 18;    // Pino Echo

// Variáveis
long duration;
float distance;
unsigned long startTime = 0;   // Armazena o tempo inicial do cronômetro
unsigned long elapsedTime = 0; // Armazena o tempo decorrido
int detectionCount = 0;        // Conta as detecções de objetos
int cycleCount = 0;            // Conta o número de ciclos (1 a 5)

// Novo vetor para exibição no monitor serial
unsigned long elapsedTimesBuffer[10];
int bufferIndex = 0;  // Índice para controlar o vetor de exibição

// Função para mostrar o buffer no monitor serial
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
  // Inicializando o monitor serial
  Serial.begin(115200);

  // Configuração dos pinos como saída e entrada
  pinMode(triggerPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Envio de pulso ao pino Trigger
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);

  // Leitura do tempo do pulso no pino Echo
  duration = pulseIn(echoPin, HIGH);

  // Calcula a distância em cm (velocidade do som: 34300 cm/s)
  distance = duration * 0.034 / 2;

  // Verifica se a distância está entre 1 e 5 cm
  if (distance >= 1 && distance <= 5) {
    if (detectionCount == 0) {
      // Primeira detecção: inicia o cronômetro
      startTime = millis();
      Serial.println("Cronômetro iniciado!");
      detectionCount++;
    } else if (detectionCount == 2) {
      // Terceira detecção: para o cronômetro e armazena o tempo
      elapsedTime = millis() - startTime;
      Serial.print("Cronômetro parado! Tempo decorrido: ");
      Serial.print(elapsedTime / 1000.0);  // Converte milissegundos para segundos
      Serial.println(" segundos.");

      // Armazena o tempo no buffer para exibição no monitor serial
      elapsedTimesBuffer[bufferIndex] = elapsedTime;
      bufferIndex++;

      // Se o buffer tiver 5 valores, exibe no monitor serial e reinicia o buffer
      if (bufferIndex == 10) {
        showBufferInSerial();  // Mostra os valores no monitor serial
        bufferIndex = 0;       // Reseta o índice do buffer
      }

      detectionCount = 0;  // Reseta o ciclo de detecção
    } else {
      // Segunda detecção: não faz nada, apenas incrementa o contador
      detectionCount++;
    }
    
    // Adiciona um pequeno delay para evitar múltiplas leituras rápidas
    delay(500);
  }

  // Pequena pausa para permitir o processamento do próximo pulso
  delay(60);
}