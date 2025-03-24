#include "Arduino.h"

#define LED_PIN 2  // LED integrado en ESP32

volatile int sensorData[10]; // Array para almacenar 10 lecturas
volatile int readIndex = 0;  // Índice para las lecturas

// Tarea para leer el "sensor" cada 100 ms
void TaskReadSensor(void *pvParameters) {
    while (1) {
        sensorData[readIndex] = random(0, 1024); // Simula lectura de sensor
        readIndex = (readIndex + 1) % 10; // Mantiene el índice entre 0 y 9
        //Serial.println(readIndex);
        vTaskDelay(pdMS_TO_TICKS(100)); // Espera 100 ms
    }
}

// Tarea para enviar los datos cada 1s y activar el LED 200 ms
void TaskSendData(void *pvParameters) {
    pinMode(LED_PIN, OUTPUT);
    
    while (1) {
        Serial.println("Encendiendo LED...");
        digitalWrite(LED_PIN, HIGH);
        unsigned long startTime = millis(); // Guarda el tiempo inicial
        
        vTaskDelay(pdMS_TO_TICKS(200)); // Mantiene el LED encendido por 200 ms
        
        unsigned long elapsedTime = millis() - startTime; // Calcula el tiempo real
        Serial.print("Tiempo encendido: ");
        Serial.print(elapsedTime);
        Serial.println(" ms");
        
        digitalWrite(LED_PIN, LOW);
        Serial.println("Apagando LED...");
        Serial.print("Valores del sensor en 1s: ");
        
        // Mostrar las 10 lecturas almacenadas
        for (int i = 0; i < 10; i++) {
            Serial.print(sensorData[i]);
            Serial.print(" ");
        }
        
        Serial.println(); // Nueva línea en la salida serial

        vTaskDelay(pdMS_TO_TICKS(800)); // Espera el resto del tiempo hasta completar 1s
    }
}



void setup() {
    Serial.begin(115200);
    
    // Crear tarea de lectura del sensor
    xTaskCreate(TaskReadSensor, "ReadSensor", 2048, NULL, 1, NULL);
    
    // Crear tarea de envío de datos
    xTaskCreate(TaskSendData, "SendData", 2048, NULL, 1, NULL);
}

void loop() {
    // FreeRTOS maneja las tareas
}
