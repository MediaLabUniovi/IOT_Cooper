#include "sensor_proximity.h"
#include <QuickMedianLib.h>

#ifdef ENABLE_SENSOR_PROXIMITY

// Estado del sensor
static bool _sensor_available = false;
static bool _force_available = false;

// Variables constantes para el sensor de proximidad
#define MAX_DISTANCE 400
#define MIN_DISTANCE 23

// Función auxiliar: delay no bloqueante
static void mi_timer(uint32_t intervalo) {
  uint32_t inicioTiempo = millis();
  while (millis() - inicioTiempo < intervalo) {
    yield();
  }
}

// Función auxiliar: obtener una lectura individual de distancia
static int obten_distancia() {
  long duracion;
  int distancia;

  digitalWrite(SENSOR_TRIG_PIN, LOW);
  delayMicroseconds(5);

  digitalWrite(SENSOR_TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(SENSOR_TRIG_PIN, LOW);

  duracion = pulseIn(SENSOR_ECHO_PIN, HIGH, 30000); // 30ms timeout ~ 5m
  if (duracion == 0)
    return 0; // Timeout
  distancia = duracion * 0.034 / 2;
  return distancia;
}

// Función auxiliar: obtener mediana de múltiples lecturas
static int obten_nivel_mediano(uint8_t muestras) {
  int distancia_sonar;
  int distancia_mediana;
  int lista_medidas[10];
  if (muestras > 10)
    muestras = 10;

  for (uint8_t i = 0; i < muestras; i++) {
    distancia_sonar = obten_distancia();

    if (distancia_sonar == 0) {
      Serial.print("En el umbral superior: ");
      Serial.println(distancia_sonar);
      uint8_t index = 0;
      while (distancia_sonar == 0 && index < 2) {
        Serial.print("Umbral superior, corregiendo...       ");
        Serial.println(index);
        distancia_sonar = obten_distancia();
        index++;
        mi_timer(250);
      }
      if (index == 2) {
        Serial.println("UMBRAL SUPERIOR");
        distancia_sonar = MAX_DISTANCE;
      } else {
        Serial.print("Umbral superior corregido, ");
      }
    } else if (distancia_sonar <= 24 && distancia_sonar >= 1) {
      Serial.print("En el umbral inferior: ");
      Serial.println(distancia_sonar);
      uint8_t index = 0;
      while ((distancia_sonar <= 24 && distancia_sonar >= 1) && index < 2) {
        Serial.print("Umbral inferior, corregiendo...       ");
        Serial.println(index);
        distancia_sonar = obten_distancia();
        index++;
        mi_timer(250);
      }
      if (index == 2) {
        Serial.println("UMBRAL INFERIOR");
        distancia_sonar = MIN_DISTANCE;
      } else {
        Serial.print("Umbral inferior corregido, ");
      }
    } else {
      Serial.print("La muestra es: ");
    }

    Serial.println(distancia_sonar);
    lista_medidas[i] = distancia_sonar;
    mi_timer(1000); // delay de 1s entre muestras para evitar ecos
  }

  Serial.print("Lista de medidas antes de calcular la mediana: ");
  for (int j = 0; j < muestras; j++) {
    Serial.print(lista_medidas[j]);
    Serial.print(" ");
  }
  Serial.println();

  distancia_mediana = QuickMedian<int>::GetMedian(lista_medidas, muestras);
  Serial.println(distancia_mediana);

  return distancia_mediana;
}

bool sensor_proximity_init(void) {
  Serial.println(
      "[SENSOR] Inicializando sensor de proximidad ultrasónico (JSN-SR04T)...");

  pinMode(SENSOR_TRIG_PIN, OUTPUT);
  pinMode(SENSOR_ECHO_PIN, INPUT);
  pinMode(SENSOR_VSLEEP_PIN, OUTPUT);

  // Apagar por defecto el NPN (LOW = NPN en corte = corta GND al sensor)
  digitalWrite(SENSOR_VSLEEP_PIN, LOW);

  _sensor_available = true;
  Serial.println("[SENSOR] Proximidad inicializado correctamente.");
  return true;
}

bool sensor_proximity_is_available(void) {
  if (_force_available)
    return true;
  return _sensor_available;
}

bool sensor_proximity_retry_init(void) { return sensor_proximity_init(); }

bool sensor_proximity_read_all(sensor_data_t *data) {
  if (!data)
    return false;

  if (!sensor_proximity_is_available()) {
    data->distance = SENSOR_ERROR_DISTANCE;
    data->valid = false;
    return false;
  }

  // Encender sensor energizando el transistor NPN
  Serial.println("[SENSOR] Alimentando sensor de proximidad (NPN activado)...");
  digitalWrite(SENSOR_VSLEEP_PIN, HIGH); // HIGH en base del NPN lo satura y conecta GND al sensor
  mi_timer(1500);    // 1.5s para que se estabilice al arrancar

  // Leer distancia con mediana de 5 muestras como en cooperjosee
  int distancia = obten_nivel_mediano(5);

  // Apagar sensor
  Serial.println("[SENSOR] Apagando sensor de proximidad (NPN desactivado)...");
  digitalWrite(SENSOR_VSLEEP_PIN, LOW); // LOW apaga NPN y corta circuito

  data->distance = distancia;
  data->valid = true;

  Serial.printf("[SENSOR] Distancia al agua final: %d cm\n", distancia);

  return true;
}

void sensor_proximity_set_available_for_testing(bool available) {
  _force_available = available;
  _sensor_available = available;
  Serial.printf("[SENSOR] Proximidad forzado a %s para testing.\n",
                available ? "DISPONIBLE" : "NO DISPONIBLE");
}

#endif // ENABLE_SENSOR_PROXIMITY
