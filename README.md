<div align="right">

[![english](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/gb.png)](./README.md) | [![spanish](https://raw.githubusercontent.com/stevenrskelton/flag-icon/master/png/16/country-4x3/es.png)](./README_ES.md)

</div>

![Static Badge](https://img.shields.io/badge/stability-beta-%23009680)

# <p align="justify"> SENSOR COOPER V3.2 - MEDIALAB_ LPWAN: LORA ULTRASONIC SENSOR TO MEASURE SAN MIGUEL'S CREEK WATER LEVEL </p>

<div align="center">

_Powered by_

[![made-in-ArduinoIDE](https://img.shields.io/badge/Arduino_IDE-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/) [![programmed-for-LilyGOLoRa32](https://img.shields.io/badge/espressif-E7352C?style=for-the-badge&logo=espressif&logoColor=white)](https://www.lilygo.cc/)

## Project based on: [rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN](https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN)

</div>

___

<div align="justify">

## Table of contents
- [Introduction](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#introduction-leftwards_arrow_with_hook)
- [Main features](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-main-features-leftwards_arrow_with_hook-)
- [To-Do list](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main?tab=readme-ov-file#to-do-list-leftwards_arrow_with_hook)
- [Component list](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-component-list-leftwards_arrow_with_hook-)
- [Connection list](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-connection-list-leftwards_arrow_with_hook-)
- [Flowchart (Simplified!)](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-flowchart-simplified-leftwards_arrow_with_hook-)
- [Code files](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#code-files-leftwards_arrow_with_hook)
- [Libraries](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#libraries-leftwards_arrow_with_hook)
- [Deployment experiment](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-deployment-experiment-leftwards_arrow_with_hook-)
- [License](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-license-leftwards_arrow_with_hook-)
- [Contact](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#-contact-leftwards_arrow_with_hook-)

</div>

___

<div align="justify">

## Introduction [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents)

In honour of Martin Cooper, Princesa de Asturias Award 2009, and Arlene Harris and their vision of IoP, The Internet of People, in MediaLab_ LPWAN we wanted to develop an IoT device that could improve the quality of the Polytechnic School of Engineering of Gijón. As a result, the idea of the Cooper Sensor came in as a LoRa device, synchronizable with [The Things Network](https://www.thethingsnetwork.org/), that could be left measuring the water level of San Miguel's creek without any need of mantainance.

</div>

<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/4_Martin%20Cooper%20y%20Arlene%20Harris.jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>

<p align="justify"> With these sensors, the aim is to monitor the possibility of a flood in the main building during the heavy rains season. Specifically, in 2018, a major flood took place turning useless many expensive equipment from the lower floors that were used by the students during the laboratory practices of many subjetcs: </p>

<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(4).jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>
<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(12).jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>
<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/escuela-politecnica-ingenieria%20(6).jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>

<p align="justify"> In this repo, you will find all the files and teaching guides required to fully understand and even take the creative freedom to improve this project. Folders and files have been given a self-explanatory name to make navigation more intuituve. </p>

___

### <p align="justify"> Main features [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

- <p align="justify"> Developed using LilyGO LoRa32 OLED v2.1_1.6 (ESP32 based board with built-in LoRa capabilities that supports solar recharging and battery management) </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/Screenshot%202023-11-13%20194151.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> Uses **AJ-SR04M** ultrasonic waterproof sensor (an improved model compatible with JSN-SR04T) to measure the **distance to the water surface**. **Battery voltage** is also transmitted to The Things Network. </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/61rPJNXbuNL._AC_UF894%2C1000_QL80_.jpg" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> Real-time **alerts are sent via Telegram** when the measured distance crosses a configured threshold. These alerts are managed using a **Node-RED** flow. Example screenshot: </p> <div align="center"> 

<div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/NodeRED.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> Powered by a **18650 Li-ion battery** through a dedicated **18650 Battery Shield module** with integrated **voltage booster** to ensure a stable 5V output over USB. </p>

<div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/18650.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

- <p align="justify"> A **flexible angled USB cable** is used to optimize space and prevent mechanical strain on the connectors. </p>



> [!WARNING]
> This sensor is extremely sensitive to physical disturbances. Be sure to perfectly align it perpendicularly to the surface where the ultrasonic beam bounces and also mind having direct vision to it

<div align="justify">

- Dynamic Data Transmission Rate implementation: send interval dynamically changes its value between 5 and 10 minutes depending on the typical deviation from the latest 5 distances sent to The Things Network (By OTAA; file [`payload_formatter.json`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/payload_formatter.json) is a suggestion on how to decode the sent bytes)

  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-11-30%20182339.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

</div>

- <p align="justify"> Custom PCB </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/pcb.png" width="600"  style="margin: 10px;"/>
  </div>
  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/esquematico.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

> [!TIP]
> Consider soldering female pin connectors so the electronic components can simply be plugged in and unplugged if a repair has to be done

- <p align="justify"> Custom housing to fit all the elements in the most efficient way (Container + Solar panel holder + USB protector) </p>

  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-01%20175741.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>
  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-01%20175633.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>
  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/Screenshot%202023-12-04%20113305.png" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

  > Assembly example:
  <div align="center">
    <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/5_Carcasa%20%2B%20Electr%C3%B3nica%20montada.jpg" width="600"  style="margin: 10px;"/>
  </div>
  <br/>

> [!WARNING]
> Clear colour PETG 3D printing filament is recommended to survive sun radiation and plastic deformations. An O-ring is also a good choice to fix and stabilize the sensor inside of the bell. Four M3 screws are needed to fix the assembly

___

<div align="justify">

### To-do list [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents)

The following list enumarates all the tasks involved in the researching process of this project and if they have been strictly completed:

- [ ] Full understanding of the development board and its pinout
```diff
- Some pins are conflictive due to poor manufacturer documentation, so testing is still being
- carried out
```

- [x] Full understanding of the sensor working mode and alternative modes

- [x] Sensor code implementation

- [x] LoRa code implementation

- [x] Low power code implementation

- [ ] Low power hardware components
```diff
- A transistor is being tried to be implemented so the sensor can be powered-on from the
- board's 5V pin and powered-off when going to deep slee, but it is getting tricky
```

</div>

<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/circuit.png" width="400"  style="margin: 10px;"/>

  <em>Electric schematic with the transistor</em>
</div>
<br/>

<div align="justify">

- [ ] PCB design
```diff
- As low power hardware has not been fully implemented, PCB has to wait
```

- [x] Casing 3D modeling
      
- [x] Data visualization app

</div>

___

### <p align="justify"> Component list [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

<div align="center">

| Component | Model |
| ------------- | ------------- |
| Dev Module  | [LilyGO LoRa32 OLED v2.1_1.6](https://www.tinytronics.nl/shop/en/development-boards/microcontroller-boards/with-lora/lilygo-ttgo-t3-lora32-868mhz-v1.6.1-esp32) |
| Distance sensor  | [AJ-SR04M](https://ssdielect.com/distancia-ultrasonido-obstaculos-y-reflectancia-1/3519-aj-sr04m.html) |
| N-Channel MOSFET  | [IRF540N](https://www.amazon.es/AUKENIEN-Transistor-IRF9540N-Transistores-potencia/dp/B09TJJJXFY/ref=sr_1_7?crid=32LB9EZ8Q81R0&dib=eyJ2IjoiMSJ9.UqJKtI1towT4naZiatE1UAz3Y34XB4iKgzo6DKubwUI4RG1qKF_oX4Un0vPC8oIiA0EFIXieDXkMAloim0p3wd53thboFPEwhQTLzEYASTn-ir9NuyrY-VBMWOrpUmAWkdOI0-NIpeF4CGnXEBoyOUkkiZ55dz6yiT-UVQ5KhHcHhs34AOguiHi3PlFpSBtSQITXz6c9NVWxuNR-AgDC0xPEYvXwdFZ6dJQA9_fEU7LkaFrESMUXJF041slnfQtWcSPyd30nK2G8wFKLq59d9Q-yjADI9jY9gAWg0tpO2wI.uLG5EZvlmd2_UDPlM2LwyNBqoAfxE2lxi6x1rXETEug&dib_tag=se&keywords=irf540n&qid=1711314804&sprefix=IRF%2Caps%2C88&sr=8-7&th=1) |
| Resistor  | [2k2](https://www.amazon.es/BOJACK-valores-resistencias-pel%C3%ADcula-carbono/dp/B08FD1XVL6/ref=sr_1_5?keywords=resistor&qid=1703351987&sr=8-5) |
| Resistor  | [1k](https://www.amazon.es/BOJACK-valores-resistencias-pel%C3%ADcula-carbono/dp/B08FD1XVL6/ref=sr_1_5?keywords=resistor&qid=1703351987&sr=8-5) |
| Battery  | [18650](https://www.tinytronics.nl/shop/en/power/batteries/18650/eve-18650-li-ion-battery-3100mah-10a-inr18650-33v) |
| Solar panel  | [SYP-S0606](https://www.tinytronics.nl/shop/en/power/solar-energy/solar-panels/solar-panel-with-dc-dc-converter-and-usb-5v-1a) |
| PCB  | [Custom (file included)](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main/pcb) |
| Housing  | [Custom (file included)](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main/carc) |

</div>

___

### <p align="justify"> Connection list [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

<div align="center">

| AJ-SR04M | Transistor | Resistor | 18650 Shield | SYP-S0606 | LilyGO |
| ------------- | ------------- | ------------- | ------------- | ------------- | ------------- |
| `trigger` | - | - | - | - | `13` |
| `echo` | - | - | - | - | `12` |
| `5v` | `S` | - | - | - | - |
| `GND` | - | `indifferent` | - | - | `GND` |
| - | `G` | `indifferent` | - | - | `15` |
| - | `D` | - | - | - | `5V` |
| - | - | - | `USB-In` | `USB-Out` | - |
| - | - | - | `USB-Out` | - | `USB-In` |

</div>

> Sketched it looks the following way:

<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/sensor_cooper_v3_3_schematic.png" width="600"  style="margin: 10px;"/>
</div>
<br/>

> [!CAUTION]
> Board model used in the sketch above is a TTGO T3 v1.3, but pin numbers correspond to those on the v2.1_1.6

___

### <p align="justify"> Flowchart (Simplified!) [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

```mermaid
graph TD;
  A[Turn on] -->|1| B(Wake up if in deep sleep)
  B -->|2| C(Get distance and battery measurement)
  C -->|3| D(Send bytes to TTN)
  D -->|4| E(Time data transmission rate)
  E -->|5| F(Go to deep sleep)
  F -->|6| B
```

___

<div align="justify">

### Code files [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents)

In this section, a brief description on how the code is distributed among files in [`medialablpwan/lorawaterlevelmonitoring/main/`](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main/main), where the code is available and ready to flash or edit, is given:

- [`main.ino`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/main.ino)
  ```C
  /*
  Definition of global functions
  Variables to be stored in the RTC memory
  'setup()' and 'loop()' functions
  */
  ```
- [`sensor.ino`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/sensor.ino)
  ```C
  /*
  Functions and variables needed to make a sensor work
  */
  ```
- [`ddc.ino`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/ddc.ino)
  ```C
  /*
  Functions and variables for the implementation of the dynamic data transfer rate
  */
- [`sleep.ino`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/sleep.ino)
  ```C
  /*
  Functions to activate ESP32's deep sleep mode
  */
- [`ttn.ino`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/ttn.ino)
  ```C
  /*
  Functions from LMIC library
  */
- [`configuration.h`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/configuration.h)
  ```C
  /*
  Sensor macros and boolean toggles
  */
- [`credentials.h`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/credentials.h)
  ```C
  /*
  OTAA keys for TTN synchronization
  */
- [`lmic_project_config.h`](https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/main/lmic_project_config.h)
  ```C
  /*
  LoRa frequency band and radio chip selector
  */
A more in depth analysis is given in the code itself as comments explain what each function does.

</div>

> [!TIP]
> The most important files to edit are `sensor.ino`, where any sensor can be implemented, and `configuration.h`, where the peripherals' macros are declared

> [!CAUTION]
> Additional code may be needed if implementing I2C I/O. The functions to make them work are in the original project in [`TTGO-PAXCOUNTER-LoRa32-V2.1-TTN/main/main.ino`](https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN/blob/master/main/main.ino)

___

<div align="justify">

### Libraries [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents)

- LilyGO board library (Paste the link on the `Preferences` tab and choose `TTGO LoRa32 OLED` as `Board` in Arduino IDE): https://github.com/Xinyuan-LilyGO/LilyGo-LoRa-Series/blob/master/boards/t3_s3_v1_x.json

- LMIC (Copy the contents of the project file `main/lmic_project_config.h` to the library file `arduino-lmic/project_config/lmic_project_config.h` and uncomment the proper frequency for your region. The sketch does always look at the library folder for the configured region!): https://github.com/mcci-catena/arduino-lmic

- QuickMedianLib (To obtain more solid distance values): https://github.com/luisllamasbinaburo/Arduino-QuickMedian

- ESP sleep (To reduce battery consumption): https://github.com/pycom/pycom-esp-idf/blob/master/components/esp32/include/esp_sleep.h

</div>

> [!NOTE]
> Other libraries, like SPI library, are easily downloadable from Arduino IDE

___

___

## <p align="justify"> Deployment experiment [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

### <p align="justify"> The first unit has been deployed near the Polytechnic School of Engineering of Gijón: </p>

<div align="center">
  <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/9_Sensor%20Cooper%20en%20Arroyo%20de%20San%20Miguel.jpg" width="600"  style="margin: 10px;"/>
</div>
<br/>
<div align="center">
  <img src="https://github.com/medialablpwan/lorawaterlevelmonitoring/blob/main/pics/map.png" width="600"  style="margin: 10px;"/>
</div>
<br/>

___

### Access the Grafana panel[^1] via this QR code or the link below it:

<div align="center">
  <img src="https://github.com/medialablpwan/waterlevelcontrol/blob/main/pics/qrcode_4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com.png" width="600"  style="margin: 10px;"/>
</div>
<br/>

<p align="center"> http://4f566df1fed52c6e7fd5f661f64ae3eb.balena-devices.com:8080/d/vJhQNCZgz/sensores-jsn-sr04t-arroyo-de-san-miguel?from=now-24h&orgId=1&to=now&refresh=1m </p>

___

___

## <p align="justify"> License [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

This project is licensed under the [GPL-3.0 license](https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN/blob/master/LICENSE). Contains code from [rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN](https://github.com/rwanrooy/TTGO-PAXCOUNTER-LoRa32-V2.1-TTN)

___

### <p align="justify"> Contact [:leftwards_arrow_with_hook:](https://github.com/medialablpwan/lorawaterlevelmonitoring/tree/main#table-of-contents) </p>

> [!IMPORTANT]
> We will kindly answer doubts and read suggestions: [![Gmail Badge](https://img.shields.io/badge/-Gmail-c14438?style=for-the-badge&logo=Gmail&logoColor=white&link=mailto:medialablpwan@gmail.com)](mailto:medialablpwan@gmail.com)
> 
> More info about our activities: [![Linkedin Badge](https://img.shields.io/badge/-LinkedIn-blue?style=for-the-badge&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/groups/9298597/)](https://www.linkedin.com/groups/9298597/)

_<p align="justify"> Authors: Daniel Rodríguez Moya, Óscar Gijón, Bruno Lolo Neira, Ramón Rubio and MediaLab\_ LPWAN Workgroup :shipit: </p>_

[^1]: Instructions on how to deploy Grafana panels are given on the repo [`medialablpwan/documentacion`](https://github.com/medialablpwan/documentacion).
