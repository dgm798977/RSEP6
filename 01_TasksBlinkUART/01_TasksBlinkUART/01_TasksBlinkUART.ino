#include "Arduino.h"

#define LED_PIN 2  // Pin del LED (puedes cambiarlo según tu placa)

// Tarea para parpadear el LED
void TaskBlink(void *pvParameters) {
    pinMode(LED_PIN, OUTPUT);
    while (1) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // Cambia el estado del LED
        vTaskDelay(pdMS_TO_TICKS(200)); // Espera 200ms
    }
}

// Tarea para enviar "Hola mundo" por UART
void TaskSerialPrint(void *pvParameters) {
    while (1) {
        Serial.println("Hola mundo");
        vTaskDelay(pdMS_TO_TICKS(1000)); // Espera 1s
    }
}

void setup() {
    Serial.begin(115200); // Inicia la comunicación serial

    // Crear la tarea para el LED
    xTaskCreate(
        TaskBlink,  // Función de la tarea
        "BlinkTask",// Nombre de la tarea
        1024,       // Tamaño del stack (en bytes)
        NULL,       // Parámetros de la tarea
        1,          // Prioridad
        NULL        // Manejador de la tarea (opcional)
    );

    // Crear la tarea para el UART
    xTaskCreate(
        TaskSerialPrint, // Función de la tarea
        "SerialTask",    // Nombre de la tarea
        2048,            // Tamaño del stack (más grande para UART)
        NULL,            // Parámetros de la tarea
        1,               // Prioridad
        NULL             // Manejador de la tarea (opcional)
    );
}

void loop() {
    // El loop queda vacío porque las tareas corren en FreeRTOS
}
