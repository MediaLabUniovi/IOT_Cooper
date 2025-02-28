/* ***********************************************************************************************************************************************************
Este archivo ha sido modificado de manera considerable para implementar el sensor ultrasónico de distancia JSN-SR04T en vez del original BME280.
El enlace para consultar el proyecto original del usuario de GitHub "rwanrooy" es el siguiente:
https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.git
*********************************************************************************************************************************************************** */
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para construir el array circular
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void carga_valores(int nivel){
  int valor_nuevo = nivel;                               // Cargo los nuevos valores leídos por el sensor

  for (int i = TARGET_ARRAY_LENGTH - 1; i > 0; i--){         // El índice del bucle va desde la última posición del array a la primera
    bufferCircular[i] = bufferCircular[i - 1];               // El índice del array es igual al índice anterior, "chocan" los valores desde la izquierda y se "barren" a la derecha
  }
  bufferCircular[0] = valor_nuevo;                           // Cada vez que quiero meter un valor nuevo, lo cargo en la primera posición del array
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para obtener la media de los valores de la lista
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
float obten_media(){                                         // Al tratarse de un array, se pone como puntero
  float suma = 0L;                                           // 0L significa que la constante es de tipo long
  
  for(uint8_t i = 0; i < 5; i++){
    suma = suma + bufferCircular[i];                         // Sumas acumuladas
  }
  return ((float)suma) / 5;                                  // Divido la suma total entre el número de valores de la lista
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para obtener la desviación típica de los valores de la lista
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
float obten_desviacion_estandar(){
  float media = obten_media();
  long int total = 0;
  float varianza, dvstd;
  
  for(uint8_t i = 0; i < TARGET_ARRAY_LENGTH; i++){
    total = total + sq((bufferCircular[i] - media));         // En cada iteración del bucle, calculo la suma total de los cuadrados de la resta de cada uno de los valores de la lista menos la media
  }
  varianza = total / TARGET_ARRAY_LENGTH;                    // La varianza resulta ser el total entre el número de valores de la lista
  dvstd = sqrt(varianza);                                    // La desviación típica resulta ser la raíz cuadrada de la varianza
  return dvstd;
}

void print_desviacion_estandar(){
  Serial.print("La desviación típica de la lista es: ");
  Serial.println(obten_desviacion_estandar());
}
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para imprimir el array
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void printArray() {
  Serial.print("Buffer circular: ");
  for (int i = 0; i < TARGET_ARRAY_LENGTH; i++) {
    Serial.print(bufferCircular[i]);
    Serial.print(" ");
  }
  Serial.println();
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para decidir qué duty cycle usar en función de la desviación típica
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
int dynamic_duty_cycle(){
  int SEND_INTERVAL;
  float desviacion_estandar_lista_medidas_medias = obten_desviacion_estandar();

  if(desviacion_estandar_lista_medidas_medias <= 1){
    SEND_INTERVAL = SEND_INTERVAL_RELAXED;
  }
  else{
    SEND_INTERVAL = SEND_INTERVAL_INTENSIVE;
  }
  return SEND_INTERVAL;
}

void print_dynamic_duty_cycle(){
  Serial.print("El duty cycle es: ");
  Serial.println(dynamic_duty_cycle());
}