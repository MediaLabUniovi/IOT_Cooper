# Sensor Cooper

Nodo IoT de bajo consumo para medir la distancia hasta la superficie del agua y transmitirla mediante **LoRaWAN**.

El sistema utiliza una **LilyGO T3 v1.6.1 con radio SX1276** y un sensor ultrasónico impermeable **JSN-SR04T**.

<p align="center">
  <img width="688" alt="Esquemático de la PCB Sensor Cooper" src="https://github.com/user-attachments/assets/221a95be-81c0-4e78-9349-08ce7716aa0f">
</p>

<p align="center">
  <em>Esquemático de la PCB para LilyGO T3 v1.6.1.</em>
</p>

<p align="center">
  <img width="688" alt="PCB Sensor Cooper" src="https://github.com/user-attachments/assets/fe3c36bc-6043-4863-aa5c-2857bcdb9427">
</p>

<p align="center">
  <em>PCB del nodo Sensor Cooper.</em>
</p>

## Características

* Medición de distancia con sensor **JSN-SR04T**.
* Comunicación **LoRaWAN OTAA** en la región **EU868**.
* Filtrado mediante la mediana de cinco muestras.
* Lectura del nivel de batería.
* Alimentación con batería y soporte para carga solar.
* Desconexión del sensor entre mediciones.
* Modo de bajo consumo entre transmisiones.
* Watchdog para recuperación ante bloqueos.
* Generación del decodificador de payload para The Things Network.

## Hardware

* LilyGO T3 v1.6.1.
* Radio LoRa SX1276.
* Sensor ultrasónico impermeable JSN-SR04T.
* PCB Sensor Cooper.
* Batería Li-Ion o LiPo.
* Panel solar opcional.

## Alimentación

La PCB incorpora dos convertidores elevadores independientes:

* Un convertidor para la LilyGO y la electrónica de control.
* Un convertidor de **5 V** dedicado al JSN-SR04T.

> Antes de conectar la LilyGO o el sensor, ajusta y comprueba la salida de ambos convertidores con un multímetro. El convertidor del sensor debe entregar **5 V estables**.

La alimentación del JSN-SR04T se controla mediante un transistor NPN conectado al GPIO 15. El sensor permanece apagado cuando no se están realizando mediciones.

## Conexiones del sensor

| Señal                            | GPIO |
| -------------------------------- | ---: |
| `TRIG`                           |   13 |
| `ECHO`                           |   12 |
| Control de alimentación `VSLEEP` |   15 |
| Salida auxiliar `VOUT`           |    0 |

> Los GPIO 13 y 15 también están asociados a la interfaz de la tarjeta SD de la LilyGO T3 v1.6. No debe utilizarse la tarjeta SD con esta asignación de pines.

## Ciclo de funcionamiento

1. El ESP32 inicia o sale del modo de bajo consumo.
2. Activa la alimentación del JSN-SR04T.
3. Espera 1,5 segundos para estabilizar el sensor.
4. Realiza cinco mediciones ultrasónicas.
5. Corrige lecturas fuera del rango configurado.
6. Calcula la mediana de las muestras.
7. Desactiva la alimentación del sensor.
8. Lee el estado de la batería.
9. Envía el payload mediante LoRaWAN.
10. Vuelve al modo de bajo consumo hasta el siguiente envío.

## Formato del payload

La configuración predeterminada genera un payload de **3 bytes**:

| Bytes | Campo     | Formato                                 |
| ----- | --------- | --------------------------------------- |
| `0–1` | Distancia | Entero de 16 bits, little-endian, en cm |
| `2`   | Batería   | Porcentaje de 0 a 100                   |

Ejemplo de decodificador para The Things Network:

```javascript
function decodeUplink(input) {
  const bytes = input.bytes;

  if (bytes.length < 3) {
    return {
      errors: ["Payload incompleto"]
    };
  }

  return {
    data: {
      distancia_agua: bytes[0] | (bytes[1] << 8),
      nivel_bateria: bytes[2]
    }
  };
}
```

El firmware también imprime este decodificador en el monitor serie cuando `SHOW_TTN_DECODER` está habilitado.

## Configuración

### 1. Crear el archivo de credenciales

Copia la plantilla:

```bash
cp config/lorawan_config_template.h config/lorawan_config.h
```

Edita `config/lorawan_config.h` e introduce las credenciales OTAA del dispositivo:

* `APPEUI`
* `DEVEUI`
* `APPKEY`

El archivo `lorawan_config.h` no debe subirse al repositorio.

### 2. Configurar el dispositivo

Los principales parámetros se encuentran en `config/config.h`:

```cpp
#define T3_V1_6_SX1276
#define SEND_INTERVAL_SECONDS 300
#define WATCHDOG_TIMEOUT_MINUTES 5
#define TX_POWER_DBM 17
#define ENABLE_DISPLAY false
```

Configuración LoRaWAN predeterminada:

```cpp
#define LORAWAN_REGION LMIC_region_t::LMIC_REGION_eu868
```

### 3. Configurar los pines

Las asignaciones de la placa y del sensor se encuentran en:

```text
config/hardware_config.h
```

## Compilación

El proyecto utiliza **PlatformIO** con el framework Arduino para ESP32.

Compilar:

```bash
pio run -e T3_V1_6_SX1276
```

Subir el firmware:

```bash
pio run -e T3_V1_6_SX1276 -t upload
```

Abrir el monitor serie:

```bash
pio device monitor
```

Subir y abrir el monitor:

```bash
pio run -e T3_V1_6_SX1276 -t upload && pio device monitor
```

La velocidad del monitor serie es de **115200 baudios**.

## Estructura del proyecto

```text
IOT_Cooper/
├── config/
│   ├── config.h
│   ├── hardware_config.h
│   └── lorawan_config_template.h
├── include/
├── lib/
├── src/
│   ├── sensor/
│   │   └── sensor_proximity.cpp
│   ├── main.ino
│   ├── sensor.cpp
│   ├── solar.cpp
│   ├── screen.cpp
│   └── ttn_decoder_generator.cpp
└── platformio.ini
```

## Parámetros actuales

| Parámetro                 | Valor          |
| ------------------------- | -------------- |
| Placa                     | LilyGO T3 v1.6 |
| Radio                     | SX1276         |
| Región                    | EU868          |
| Activación                | OTAA           |
| Intervalo de envío        | 300 segundos   |
| Potencia LoRa             | 17 dBm         |
| Watchdog                  | 5 minutos      |
| Pantalla                  | Desactivada    |
| Muestras por medición     | 5              |
| Distancia mínima aplicada | 23 cm          |
| Distancia máxima aplicada | 400 cm         |
| Batería en payload        | Porcentaje     |
