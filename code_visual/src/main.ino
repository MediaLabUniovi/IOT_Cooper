/* ***********************************************************************************************************************************************************
SENSOR COOPER V3.2 - MEDIALAB LPWAN UNIVERSIDAD DE OVIEDO

Este archivo ha sido modificado de manera considerable para implementar el sensor ultrasónico de distancia JSN-SR04T en vez del original BME280.
El enlace para consultar el proyecto original del usuario de GitHub "rwanrooy" es el siguiente:
https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN.git
*********************************************************************************************************************************************************** */
#include "configuration.h"
#include "rom/rtc.h"

RTC_DATA_ATTR uint32_t count = 0;                           // Message counter, stored in RTC memory, survives deep sleep

RTC_DATA_ATTR int bufferCircular[TARGET_ARRAY_LENGTH];  // Lista donde guardo los últimos 5 valores enviados a TTN. LA ALOJO EN LA MEMORIA RTC PARA QUE SOBREVIVA AL DEEP SLEEP

static uint8_t txBuffer[3];                                 // Enter the length of the payload in bytes (this has to be more than 3 if you want to receive downlinks)

static uint8_t rxBuffer[1];                                 // Downlink payload

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para enviar el paquete de datos LoRa
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void send(){
  buildPacket(txBuffer);
  Serial.println("Estoy en send");
  //
  // Gestión del Buffer Circular (AQUÍ PARA EVITAR ENÉSIMAS ITERACIONES) -------------------------------------------------------------------------------------
  //
  int valor_nuevo = (txBuffer[1] << 8) | txBuffer[0];
  carga_valores(valor_nuevo);
  printArray();
  print_desviacion_estandar();
  print_dynamic_duty_cycle();

#if LORAWAN_CONFIRMED_EVERY > 0
  bool confirmed = (count % LORAWAN_CONFIRMED_EVERY == 0);
#else
  bool confirmed = false;
#endif

  ttn_cnt(count);
  
  ttn_send(txBuffer, sizeof(txBuffer), LORAWAN_PORT, confirmed);
  
  count++;                                                  // send count plus one
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para dormir el ESP32 durante el tiempo de duty cycle
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void sleep(){
#if SLEEP_BETWEEN_MESSAGES == 1
  Serial.println("Iniciando deep sleep...");                // Mostrar mensaje de que se ha iniciado el deep sleep
  Serial.println();

  uint32_t sleep_for = (millis() < dynamic_duty_cycle()) ? dynamic_duty_cycle() - millis() : dynamic_duty_cycle(); // We sleep for the interval between messages minus the current millis, this way we distribute the messages evenly every SEND_INTERVAL millis
  sleep_millis(sleep_for);
  //sleep_millis(30000);
#endif
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para mostrar mensajes por monitor serial segun se interactue con TTN
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void callback(uint8_t message){
  if(EV_JOINING == message)Serial.println("Joining TTN...");
  if(EV_JOINED == message)Serial.println("TTN joined!");
  if(EV_JOIN_FAILED == message)Serial.println("TTN join failed");
  if(EV_REJOIN_FAILED == message)Serial.println("TTN rejoin failed");
  if(EV_RESET == message)Serial.println("Reset TTN connection");
  if(EV_LINK_DEAD == message)Serial.println("TTN link dead");
  if(EV_ACK == message)Serial.println("ACK received");
  if(EV_PENDING == message)Serial.println("Message discarded");
  if(EV_QUEUED == message)Serial.println("Message queued");

  if(EV_TXCOMPLETE == message){
    Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
    if(LMIC.txrxFlags & TXRX_ACK){
      Serial.println(F("Received ack"));
    }
    if(LMIC.dataLen){
      Serial.print(F("Received "));
      Serial.print(LMIC.dataLen);
      Serial.println(F(" bytes of payload"));
      for (int i = 0; i < LMIC.dataLen; i++){
        if (LMIC.frame[LMIC.dataBeg + i] < 0x10){
          Serial.print(F("0"));
        }
        Serial.print(F("Received payload: "));
        Serial.print(LMIC.frame[LMIC.dataBeg + i], HEX);
      }
      Serial.println();
    }
    sleep(); //No se si después de esto se ejecuta el manejador de EV_RESPONSE
  }

  if(EV_RESPONSE == message){
    Serial.print(F("[TTN] Response: "));

    size_t len = ttn_response_len();
    uint8_t data[len];
    ttn_response(data, len);

    char buffer[6];
    for(uint8_t i = 0; i < len; i++){
      Serial.print(F(buffer)); //Posible error
    }
    Serial.println();
  }
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion contador del deep sleep mode para saber que, tras volver de d.s., tiene valores en la memoria RTC
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
uint32_t get_count(){
  return count;
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion de temporizacion en milisegundos personalizable. Como 'delay()', pero sin detener la ejecución del programa
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void mi_timer(int intervalo){                                // Supongo un intervalo de 2000
  unsigned long inicioTiempo = millis();                     // Obten el tiempo actual en ms, supongo 14000
  while(millis() - inicioTiempo < intervalo){}               // Mientras 14000... 15000... 16000... - 14000 = 0... 1000... 2000... 3000 (hasta 3000 se cumple) < 2000, me meto en el bucle
}

// -----------------------------------------------------------------------------------------------------------------------------------------------------------
// Funcion para activar o desactivar desde "configuration.h" el monitor serial para debugging
// -----------------------------------------------------------------------------------------------------------------------------------------------------------
void debug_code(){
#if ENABLE_DEBUG == 1
  DEBUG_PORT.begin(SERIAL_BAUD);
#endif
}

// ===========================================================================================================================================================
// Setup main
// ===========================================================================================================================================================
void setup(){
  //
  Serial.begin(115200);
  // Debug ---------------------------------------------------------------------------------------------------------------------------------------------------
  //
  debug_code();

  //
  // Init pines de perifericos que envian por LoRa -----------------------------------------------------------------------------------------------------------
  //
  pinMode(VBATPIN, INPUT);                                  // VBATPIN como input. Es el "sensor" de voltaje de la batería
  pinMode(trigPin, OUTPUT);                                 // trigPin (Rx) como output. Inicia los pulsos ultrasonicos cuando se pone en 'HIGH' 
  pinMode(echoPin, INPUT);                                  // echoPin (Tx) 
  pinMode(VOUT_PIN, OUTPUT);                                // Pin para alimentar al sensor, siempre a 'HIGH' y que se desconecte al entrar el deep sleep
  pinMode(VSLEEP_PIN, OUTPUT);                              // Configurar el pin 14 como salida
  
  digitalWrite(VSLEEP_PIN, HIGH);                           // Ponerlo en alto para cortar la alimentación del transistor
  digitalWrite(VOUT_PIN, HIGH);                             // Poner a 'HIGH' siempre el pin del sensor para que haga de "Vcc"

  //
  // TTN setup -----------------------------------------------------------------------------------------------------------------------------------------------
  //
  if(!ttn_setup()){
    Serial.println("[ERR] Radio module not found!");
    sleep_forever();
  }

  //
  // TTN register --------------------------------------------------------------------------------------------------------------------------------------------
  //
  ttn_register(callback); //Registro mi callback en la lista de funciones que se llaman cuando ocurre un evento
  ttn_join(); 
  ttn_sf(LORAWAN_SF);
  ttn_adr(LORAWAN_ADR);
  Serial.println("Setup finalizado");
}

// ===========================================================================================================================================================
// Loop main
// ===========================================================================================================================================================
void loop(){
  ttn_loop(); //gestiona tareas en segundo plano, mantiene el Stack de Lora en funcionamiento
  //
  // Send every SEND_INTERVAL millis -------------------------------------------------------------------------------------------------------------------------
  //
  static uint32_t last = 0; //estática para que guarden su valor en cada interacción del loop
  static bool first = true;
  if(0 == last || millis() - last > dynamic_duty_cycle()){ //Entra la primera vez y cada vez que se cumpla el duty cycle
    Serial.println("Llegue");
    last = millis();
    first = false;
    Serial.println("TRANSMITTING");
    send();
  }
}