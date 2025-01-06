# ESP32 Trådløst Fyrværkeri Affyrings System

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/enput/Firework_Ignition_System)

## Introduktion

Denne manual guider dig trin-for-trin i at bygge et trådløst fyrværkerikontrolsystem ved hjælp af ESP32, et relæmodul, nichrometråd og andre nødvendige komponenter. Systemet er open source og designet til at være brugervenligt, selv for dem med begrænset viden om elektronik. Følg vejledningen nøje for at sikre en sikker og velfungerende opsætning.

## Indholdsfortegnelse

1. [Materialer](#materialer)
2. [Forberedelse](#forberedelse)
3. [Hardware Opsætning](#hardware-opsætning)
    - [Forbindelse af Relæmodul](#forbindelse-af-relæmodul)
    - [Opsætning af Nichrometråd](#opsætning-af-nichrometråd)
    - [Tilslutning af LED (valgfrit)](#tilslutning-af-led-valgfrit)
4. [Software Konfiguration](#software-konfiguration)
    - [Installation af Arduino IDE og ESP32 Board](#installation-af-arduino-ide-og-esp32-board)
    - [Upload af Kode](#upload-af-kode)
5. [Wi-Fi Opsætning](#wi-fi-opsætning)
6. [Test og Validering](#test-og-validering)
    - [Testmode](#testmode)
    - [Affyring af Kanaler](#affyring-af-kanaler)
    - [Overvågning af Signalstyrke og Forsinkelse](#overvågning-af-signalstyrke-og-forsinkelse)
7. [Sikkerhedstips](#sikkerhedstips)
8. [Fejlfinding](#fejlfinding)
    - [Problemer med Forbindelse](#problemer-med-forbindelse)
    - [Kode Upload Fejl](#kode-upload-fejl)
    - [Relæer Ikke Aktiveret](#relæer-ikke-aktiveret)
    - [LED Blinker Ikke](#led-blinker-ikke)
9. [Materialelinks](#materialelinks)
10. [Bidrag og Licens](#bidrag-og-licens)

---

## Materialer

### Hovedkomponenter

| Komponent                 | Beskrivelse                                    | Link                  |
|---------------------------|------------------------------------------------|-----------------------|
| **ESP32 Udviklingsboard** | Wi-Fi og Bluetooth kapabel mikrokontroller    | [Køb her](#https://www.aliexpress.com/item/1005006456519790.html)           |
| **Relæmodul**             | 4-kanals relæmodul anbefales                   | [Køb her](#https://www.aliexpress.com/item/1005002867727977.html)           |
| **Nichrometråd**          | 0.1mm til E-matches                             | [Køb her](#https://www.aliexpress.com/item/1005005947832471.html)           |
| **E-match Ledninger**     | Forbindelse til E-matches                       | [Køb her](#https://www.aliexpress.com/item/1005001552897167.html)           |
| **12V Batteri**           | Mindst 6A kapacitet til drift af systemet       | [Køb her](#)           |
| **LED med Modstand**      | Indikator LED (hvis nødvendigt)                 | [Køb her](#)           |
| **Jumpertråde**           | Han-til-han og han-til-hun jumpertråde          | [Køb her](#https://www.aliexpress.com/item/1005005501503609.html)           |
| **Breadboard**            | Til prototyping og forbindelser                  | [Køb her](#https://www.aliexpress.com/item/32865122971.html)           |
| **DC-DC Stepdown-Modul**  | For at sikre korrekt spænding til komponenter     | [Køb her](#https://www.aliexpress.com/item/1005006149348817.html)           |

---

## Forberedelse

Før du begynder, sørg for at have alle materialerne klar og et arbejdsområde, der er godt ventileret og fri for brandbare materialer.

---

## Hardware Opsætning

### Forbindelse af Relæmodul

1. **Forbind Relæmodul til ESP32:**
    - **IN1** → GPIO 4
    - **IN2** → GPIO 5
    - **IN3** → GPIO 18
    - **IN4** → GPIO 19

2. **Forbind Relæmodul til 12V Batteriet:**
    - **VCC** → **+12V** terminal på batteriet
    - **GND** → **Fælles GND** terminal

3. **Forbind ESP32 til Fælles GND:**
    - **ESP32 GND** → Fælles GND terminal

    **Bemærk:** Det er vigtigt, at ESP32’s GND er forbundet til den samme fælles GND terminal som batteriet og relæmodulet for korrekt signaltolkning.

### Opsætning af Nichrometråd

1. Klip passende længder af nichrometråd (3-5 cm anbefales pr. E-match).
2. Forbind nichrometråden til E-match ledningerne.
3. Fastgør E-match ledningerne til relæets outputterminaler.
4. **Sikkerhed:** Sørg for, at relæets kredsløb drives af dit 12V batteri, som kan levere mindst 6A.

### Tilslutning af LED (Valgfrit)

1. Hvis din ESP32 ikke har en indbygget LED, kan du tilslutte en ekstern LED:
    - **GPIO 2** → LED med passende modstand.

    Dette giver en visuel indikation af systemets tilstand, f.eks. testmode.

---

## Software Konfiguration

### Installation af Arduino IDE og ESP32 Board

1. **Download og installer Arduino IDE:** [Arduino IDE Download](https://www.arduino.cc/en/software)
2. **Tilføj ESP32 Board til Arduino IDE:**
    - Åbn Arduino IDE.
    - Gå til **Filer > Indstillinger**.
    - Tilføj følgende URL til **Ekstra Board Manager URLs**:
      ```
      https://dl.espressif.com/dl/package_esp32_index.json
      ```
    - Gå til **Værktøjer > Board > Board Manager**.
    - Søg efter **ESP32** og installer pakken.

### Upload af Kode

1. **Kopier Koden:**
    - Kopiér koden fra denne manual til en ny Arduino sketch i Arduino IDE.
2. **Vælg Det Rigtige Board og Port:**
    - Gå til **Værktøjer > Board** og vælg dit ESP32 board.
    - Gå til **Værktøjer > Port** og vælg den korrekte COM-port.
3. **Upload Koden:**
    - Klik på **Upload**-knappen og vent, indtil koden er flashet til ESP32.
4. **Åbn Serial Monitor:**
    - Gå til **Værktøjer > Serial Monitor**.
    - Vælg baudrate **115200**.
    - Du bør se følgende beskeder:
      ```
      Wi-Fi started
      Access Point IP: 192.168.4.1
      HTTP server started
      ```

---

## Wi-Fi Opsætning

1. **Forbind til ESP32's Wi-Fi:**
    - På din telefon eller computer, find Wi-Fi-netværket **FireworkSystem**.
    - Indtast adgangskoden **password123**.

2. **Tilpas Netværksnavn og Adgangskode:**
    - Åbn din Arduino sketch og find følgende linjer:
      ```cpp
      const char* ssid = "FireworkSystem";
      const char* password = "password123";
      ```
    - Ændr **"FireworkSystem"** til det ønskede netværksnavn.
    - Ændr **"password123"** til et sikkert password for at forhindre uautoriseret adgang.

3. **Åbn Webinterface:**
    - Åbn en browser og navigér til: [http://192.168.4.1](http://192.168.4.1)

---

## Test og Validering

### Testmode

1. **Aktivér Testmode:**
    - I webinterfacet, marker **"Enable Test Mode"** checkboxen.
2. **Test LED:**
    - Klik på fyringsknapperne for kanaler **1, 2, 3, 4** for at få LED’en til at blinke.

### Affyring af Kanaler

1. **Deaktiver Testmode:**
    - Fjern markeringen af **"Enable Test Mode"**.
2. **Affyr E-matches:**
    - Klik på de ønskede fyringsknapper for at aktivere relæerne og tænde E-matches.

### Overvågning af Signalstyrke og Forsinkelse

- Webinterfacet viser **RSSI** (signalstyrke) og **forsinkelse** (ms) i realtid, hvilket hjælper med at optimere systemets ydeevne.

---

## Sikkerhedstips

1. **Brug en Korrekt Strømforsyning:**
    - Et **12V batteri** med mindst **6A** strømstyrke anbefales for stabil drift af relæmodul og nichrometråd.
2. **Håndtér Nichrometråd Forsigtigt:**
    - Nichrometråden bliver meget varm under brug. Sørg for, at den ikke kommer i kontakt med brandbare materialer.
3. **Test Systemet Før Fyrværkeri:**
    - Brug testmode til at sikre, at alt fungerer korrekt, før du tilslutter og affyrer fyrværkeri.
4. **Sikker Opsætning af Fyrværkeri:**
    - Placer E-matches og fyrværkeri sikkert væk fra personer og brandbare overflader.
5. **Overvåg Systemet Under Affyring:**
    - Vær til stede og overvåg systemets funktion under affyring for at reagere hurtigt i tilfælde af problemer.

---

## Fejlfinding

### Problemer med Forbindelse

- **ESP32 Forbinder Ikke til Wi-Fi:**
  - Tjek, at ESP32 er korrekt forbundet til strøm og relæmodul.
  - Sørg for, at SSID og password er korrekt indstillet i koden.

### Kode Upload Fejl

- **Fejl Under Upload:**
  - Sørg for, at det rigtige board og port er valgt i Arduino IDE.
  - Genstart ESP32 og prøv igen.

### Relæer Ikke Aktiveret

- **Relæerne Aktiveres Ikke:**
  - Tjek alle forbindelser mellem ESP32 og relæmodulet.
  - Sikr, at batteriet leverer tilstrækkelig strøm.

### LED Blinker Ikke

- **LED Blinker Ikke i Testmode:**
  - Tjek forbindelsen mellem ESP32’s GPIO 2 og LED’en.
  - Sørg for, at modstanden er korrekt tilsluttet.

---

## Materialelinks

- **ESP32 Udviklingsboard (Wi-Fi):** [Køb her](#https://www.aliexpress.com/item/1005006456519790.html)
- **Relæmodul (4 kanaler eller mere):** [Køb her](#https://www.aliexpress.com/item/1005002867727977.html)
- **Nichrometråd (0.1mm):** [Køb her](#https://www.aliexpress.com/item/1005005947832471.html)
- **E-match Ledninger (minimum 20AWG):** [Køb her](#https://www.aliexpress.com/item/1005001552897167.html)
- **DC-DC Stepdown-Modul (3-12V):** [Køb her](#https://www.aliexpress.com/item/1005006149348817.html)
- **Breadboard:** [Køb her](#https://www.aliexpress.com/item/32865122971.html)
- **Han-til-han Jumpertråde (10 stk):** [Køb her](#https://www.aliexpress.com/item/1005005501503609.html)
- **Han-til-hun Jumpertråde (10 stk):** [Køb her](#https://www.aliexpress.com/item/1005005501503609.html)

---

## Bidrag og Licens

Dette projekt er open source og velkommen til bidrag fra fællesskabet. Hvis du ønsker at bidrage, skal du følge disse trin:

1. Fork projektet på GitHub.
2. Lav dine ændringer i en ny branch.
3. Åbn en pull request med en beskrivelse af dine ændringer.

Projektet er licenseret under **MIT License**, hvilket betyder, at du frit kan bruge, ændre og distribuere det.

---

**Bemærk:** Arbejd altid sikkert og ansvarligt, når du håndterer elektronik og fyrværkeri. Følg lokale love og regler for brug af fyrværkeri.
