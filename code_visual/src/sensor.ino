/* ***********************************************************************************************************************************************************
Este archivo ha sido modificado de manera considerable para implementar el sensor ultrasónico de distancia JSN-SR04T en vez del original BME280.
El enlace para consultar el proyecto original del usuario de GitHub "rwanrooy" es el siguiente:
https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.git
*********************************************************************************************************************************************************** */
#include <QuickMedianLib.h>                                 // Librería para obtener la mediana de un array

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// JSN-SR04T config
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
int obten_distancia(){
  long duracion;
  int distancia;
  
  digitalWrite(trigPin, LOW);                               // Clear the trigPin by setting it LOW:
  delayMicroseconds(5);


  digitalWrite(trigPin, HIGH);                              // Trigger the sensor by setting the trigPin high for 10 microseconds
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duracion = pulseIn(echoPin, HIGH);                        // Read the echoPin. pulseIn() returns the duration (length of the pulse) in microseconds
  distancia = duracion * 0.034 / 2;                         // Calculate the distance:
  return distancia;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para calcular la mediana de un numero n de muestras de distancia para hacer el dato del nivel del agua más robusto
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
int lista_medidas[5];

int obten_nivel_mediano(uint8_t muestras){
  int distancia_sonar;
  int distancia_mediana;

  for(uint8_t i = 0; i < muestras; i++){
    distancia_sonar = obten_distancia();

    if(distancia_sonar == 0){                               // Si distancia es 0, implica que superamos el umbral superior. Sin embargo, ésto a veces ocurre sin estar en esta condición, es decir, el sensor tiene fallos físicos
      Serial.print("En el umbral superior: ");
      Serial.println(distancia_sonar);
      uint8_t index = 0;
      while(distancia_sonar == 0 && index < 2){            // "&& i < 'valor'", así puedo evitar pasarme la vida aquí, pero reducir el error
        Serial.print("Umbral superior, corregiendo...       ");
        Serial.println(index);
        distancia_sonar = obten_distancia();
        index++;                                            
        mi_timer(250);                                      // Por ello, en este 'if', itero cada 250ms hasta que de una medida que no sea 0
      }

      if(index == 2){
        Serial.println("UMBRAL SUPERIOR");
        distancia_sonar = MAX_DISTANCE;
      }
      else{
        Serial.print("Umbral superior corregido, ");
      }
    }

    else if(distancia_sonar <= 24 && distancia_sonar >= 1){ // Si estoy entre 1 y 24, el sensor no tiene resolución y siempre da "24"
      Serial.print("En el umbral inferior: ");
      Serial.println(distancia_sonar);
      uint8_t index = 0;
      while((distancia_sonar <= 24 && distancia_sonar >= 1) && index < 2){ // Itero 10 veces, cada intento en franjas de 250ms
        Serial.print("Umbral inferior, corregiendo...       ");
        Serial.println(index);
        distancia_sonar = obten_distancia();
        index++;
        mi_timer(250); 
      }
      
      if(index ==2){                                      // Si 10 veces seguidas da un "24", tendrá razón y lo acepto
        Serial.println("UMBRAL INFERIOR");
        distancia_sonar = MIN_DISTANCE;
      }
      else{
        Serial.print("Umbral inferior corregido, ");        // Si no, es que consiguió una medida "sana" y es con la que me quedo en el array
      }
    }

    else{
      Serial.print("La muestra es: ");
    }

    Serial.println(distancia_sonar);
    lista_medidas[i] = distancia_sonar;
    mi_timer(1000);
  }
  Serial.print("Lista de medidas antes de calcular la mediana: ");
  for (int j = 0; j < muestras; j++) {
    Serial.print(lista_medidas[j]);
    Serial.print(" ");
  }
  Serial.println();
  distancia_mediana = QuickMedian<int>::GetMedian(lista_medidas, muestras);
  Serial.println(distancia_mediana);
  //nivel_mediana = -((100*(distancia_mediana - 24))/376)+100; // Fórmula para calcular de forma lineal el porcentaje de nivel de agua
  return distancia_mediana;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para calcular el nivel de batería 
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
uint8_t obten_nivel_bateria() {
  analogReadResolution(12);
  float VBAT = (float)(analogRead(VBATPIN)) / 4095 * 2 * V_REF; // Conversión del ADC a voltaje
  float sin_offset = VBAT + 0.3; // Ajuste por el offset de medida
  
  uint8_t nivel_bateria = constrain((sin_offset - 3.1) * (100.0 / (4.2 - 3.1)), 0, 100); // Cálculo del porcentaje

  Serial.print("Lectura ADC: ");
  Serial.print(analogRead(VBATPIN));  
  Serial.print(" - Voltaje: ");
  Serial.print(sin_offset, 2);
  Serial.print("V - Porcentaje: ");
  Serial.print(nivel_bateria);
  Serial.println("%");

  return nivel_bateria;//devuelvo el nivel de la batería 
}

// ===========================================================================================================================================================
// FUNCION PRINCIPAL DE "sensor.ino" - Construir el paquete de datos que se enviara por LoRa
// ===========================================================================================================================================================
void buildPacket(uint8_t txBuffer[3]){                      // Uso 'uint8_t' para que todos los datos sean del tamaño de 1byte (8bits)
  //
  // Distancia -----------------------------------------------------------------------------------------------------------------------------------------------
  //
  int nivel_mediano = obten_nivel_mediano(5);
  Serial.print("Distancia al agua: ");
  Serial.print(nivel_mediano);
  Serial.println("cm");

  txBuffer[0] = lowByte(nivel_mediano);                       // Uso únicamente el lowByte ya que estoy hablando de un porcentaje, del 0% al 100%, valores que no superan 255 y caben en un byte
  txBuffer[1] = highByte(nivel_mediano);
  //
  // Batería -------------------------------------------------------------------------------------------------------------------------------------------------
  //
  uint8_t nivel_bateria = obten_nivel_bateria();
  txBuffer[2] = lowByte(nivel_bateria);


}