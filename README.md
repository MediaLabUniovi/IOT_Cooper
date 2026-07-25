<img width="935" height="659" alt="imagen" src="https://github.com/user-attachments/assets/221a95be-81c0-4e78-9349-08ce7716aa0f" />

<img width="688" height="610" alt="imagen" src="https://github.com/user-attachments/assets/fe3c36bc-6043-4863-aa5c-2857bcdb9427" />



# Sensor Cooper

**Sensor Cooper** es un sistema de monitorización IoT de bajo consumo basado en LoRaWAN, diseñado específicamente para medir el nivel y la altura del agua en ríos y arroyos en tiempo real. 

Utilizando conectividad inalámbrica de largo alcance (LoRa) y sensores de precisión, este proyecto facilita la medición remota y la prevención de desbordamientos en entornos naturales de difícil acceso.

---

##  Características Principales

*   **Medición Ultrasónica de Precisión:** Utiliza el sensor ultrasónico industrial impermeable **JSN-SR04T** para calcular con alta fiabilidad la distancia entre el nodo sensor y la superficie del agua.
*   **Ultrabajo Consumo de Energía:** Optimizado para funcionar con baterías y paneles solares mediante el modo *Deep Sleep* del ESP32.
*   **Gestión Inteligente de Alimentación:** El sensor ultrasónico no está encendido continuamente. Se corta y habilita su alimentación (GND) a través de un transistor NPN de forma programática, garantizando la recolección de los datos precisos usando la menor energía posible.
*   **Conectividad LoRaWAN:** Transmisión de largo alcance de la distancia al agua y voltaje de la batería, perfectamente compatible para integración en **The Things Network (TTN)** u otras plataformas de servidor privado (ChirpStack).
*   **Generador Integrado de Decodificador TTN:** Permite visualizar de manera autónoma el código Javascript necesario para TTN (The Things Network) adaptado al *payload* dinámico de la distancia.
*   **Diseño Robusto (Filtro de Mediana):** Ejecuta la medición usando algoritmos de cálculo de la mediana para evitar interferencias, ecos falsos causados por obstáculos menores y suavizar variaciones erráticas en la superficie del agua.

##  Hardware Requerido

1.  **Placa Controlador LoRa:** Basada en ESP32 con chip LoRa SX1276 (por ejemplo: LilyGo T3, T-Beam u otras placas de desarrollo T-Series compatibles).
2.  **Sensor de Proximidad Unshielded/Waterproof:** Sensor Ultrasónico **JSN-SR04T**.
    *   **Pines predeterminados:**
        *   `TRIG` (Trigger): Pin **13**
        *   `ECHO`: Pin **12**
3.  **Transistor NPN:** (Por ejemplo 2N2222, BC547) para actuar como interruptor (*low-side switch*) puenteando el GND del sensor y ahorrando batería durante los intervalos de *Sleep*. Controlado a través del Pin **15** (`VSLEEP`). (Se incluye también un pin **0** para `VOUT` constante).
4.  **Batería LiPo o 18650** y, opcionalmente, un setup de panel solar si la placa soporta carga (Ej: gestión mediante AXP192 / PMU integrado).

## ⚙️ Funcionamiento

El comportamiento cíclico del **Sensor Cooper** se resume en los siguientes pasos:

1.  El microcontrolador ESP32 despierta de su estado de sueño profundo (*Deep Sleep*).
2.  Alimenta al sensor **JSN-SR04T** activando la base del transistor NPN (nivel alto/`HIGH`).
3.  Tras un breve tiempo de estabilización (~500ms), emite los pulsos ultrasónicos y recolecta una muestra secuencial de 5 medidas distintas, filtrando los extremos extraños y calculando la mediana matemática de los resultados.
4.  Corta la alimentación al sensor para detener el consumo eléctrico del JSN-SR04T y del propio conversor de la placa sensora (poniendo a `LOW` el pin de control).
5.  Recopila el nivel actual de batería.
6.  Integra la distancia en centímetros y el voltaje de la batería en un pequeño *payload* (paquete de datos).
7.  Transmite los datos a través del módulo radiofrecuencia (LoRaWAN).
8.  Al recibir la confirmación (si está configurado) o completar la ventana de escucha de la red, vuelve al estado *Deep Sleep* durante el tiempo programado, reiniciando su ciclo.

## 💻 Desarrollo y Compilación

Este proyecto usa **PlatformIO** para el desarrollo. Asegúrate de tenerlo instalado (ej: como extensión en VS Code).

```bash
# Para compilar el proyecto (reemplaza T3_V1_6_SX1276 con el chip LoRa de tu placa)
pio run -e T3_V1_6_SX1276

# Para subir el código e inicializar el monitor serie
pio run -e T3_V1_6_SX1276 -t upload && pio device monitor
```

> **Configuración LMIC:** Todos los pines del sensor y las claves de conexión OTAA/ABP de The Things Network deben definirse y comprobarse en `config/lorawan_config.h` y `config/hardware_config.h` según aplique a tu hardware de despliegue final.
