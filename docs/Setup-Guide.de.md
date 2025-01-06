# ESP32 Drahtloses Feuerwerkszündsystem

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)
![GitHub last commit](https://img.shields.io/github/last-commit/enput/Firework_Ignition_System)

## Einführung

Dieses Handbuch bietet eine Schritt-für-Schritt-Anleitung zum Aufbau eines drahtlosen Feuerwerkssteuerungssystems mit einem ESP32, einem Relaismodul, Nichtelementdraht und anderen notwendigen Komponenten. **WiFiFyr** ist Open Source und darauf ausgelegt, benutzerfreundlich zu sein, auch für diejenigen mit begrenzten Kenntnissen in Elektronik. Befolgen Sie die Anweisungen sorgfältig, um eine sichere und funktionierende Einrichtung zu gewährleisten.

## Inhaltsverzeichnis

1. [Materialien](#materialien)
2. [Vorbereitung](#vorbereitung)
3. [Hardware-Setup](#hardware-setup)
    - [Anschluss des Relaismoduls](#anschluss-des-relaismoduls)
    - [Einrichtung des Nichtelementdrahts](#einrichtung-des-nichtelementdrahts)
    - [Anschluss der LED (Optional)](#anschluss-der-led-optional)
4. [Software-Konfiguration](#software-konfiguration)
    - [Installation der Arduino IDE und ESP32 Board](#installation-der-arduino-ide-und-esp32-board)
    - [Hochladen des Codes](#hochladen-des-codes)
5. [Wi-Fi Einrichtung](#wifi-einrichtung)
6. [Testen und Validierung](#testen-und-validierung)
    - [Testmodus](#testmodus)
    - [Feuerung der Kanäle](#feuerung-der-kanäle)
    - [Überwachung der Signalstärke und Verzögerung](#überwachung-der-signalstärke-und-verzögerung)
7. [Sicherheitstipps](#sicherheitstipps)
8. [Fehlerbehebung](#fehlerbehebung)
    - [Verbindungsprobleme](#verbindungsprobleme)
    - [Code-Upload-Fehler](#code-upload-fehler)
    - [Relais werden nicht aktiviert](#relais-werden-nicht-aktiviert)
    - [LED blinkt nicht](#led-blinkt-nicht)
9. [Materiallinks](#materiallinks)
10. [Beitragen und Lizenz](#beitragen-und-lizenz)

---

## Materialien

### Hauptkomponenten

| Komponente                 | Beschreibung                                     | Link                  |
|---------------------------|-------------------------------------------------|-----------------------|
| **ESP32 Entwicklungsboard** | Wi-Fi und Bluetooth fähiger Mikrocontroller    | [Hier kaufen](https://www.aliexpress.com/item/1005006456519790.html)           |
| **Relaismodul**             | 4-Kanal-Relaismodul empfohlen                  | [Hier kaufen](https://www.aliexpress.com/item/1005002867727977.html)           |
| **Nichtelementdraht**          | 0,1 mm für E-Matches                              | [Hier kaufen](https://www.aliexpress.com/item/1005005947832471.html)           |
| **E-Match Leitungen**     | Verbindung zu E-Matches                        | [Hier kaufen](https://www.aliexpress.com/item/1005001552897167.html)           |
| **12V Batterie**           | Mindestens 6A Kapazität zur Stromversorgung des Systems       | [Hier kaufen](#)           |
| **LED mit Widerstand**      | Anzeige-LED (falls erforderlich)                    | [Hier kaufen](#)           |
| **Jumper Kabel**           | Male-to-Male und Male-to-Female Jumper Kabel    | [Hier kaufen](https://www.aliexpress.com/item/1005005501503609.html)           |
| **Breadboard**            | Für Prototyping und Verbindungen                  | [Hier kaufen](https://www.aliexpress.com/item/32865122971.html)           |
| **DC-DC Stepdown Modul**  | Zur Sicherstellung der korrekten Spannung für die Komponenten         | [Hier kaufen](https://www.aliexpress.com/item/1005006149348817.html)           |

---

## Vorbereitung

Bevor Sie beginnen, stellen Sie sicher, dass Sie alle Materialien bereit haben und einen Arbeitsbereich, der gut belüftet und frei von brennbaren Materialien ist.

---

## Hardware-Setup

### Anschluss des Relaismoduls

1. **Verbinden Sie das Relaismodul mit dem ESP32:**
    - **IN1** → GPIO 4
    - **IN2** → GPIO 5
    - **IN3** → GPIO 18
    - **IN4** → GPIO 19

2. **Verbinden Sie das Relaismodul mit der 12V Batterie:**
    - **VCC** → **+12V** Anschluss der Batterie
    - **GND** → **Gemeinsamer GND** Anschluss

3. **Verbinden Sie den ESP32 mit dem gemeinsamen GND:**
    - **ESP32 GND** → Gemeinsamer GND Anschluss

    **Hinweis:** Es ist wichtig, dass der GND des ESP32 mit dem gleichen gemeinsamen GND Anschluss verbunden ist, den auch die Batterie und das Relaismodul verwenden, um sicherzustellen, dass die Steuersignale vom ESP32 korrekt vom Relaismodul interpretiert werden.

### Einrichtung des Nichtelementdrahts

1. Schneiden Sie geeignete Längen des Nichtelementdrahts (3-5 cm pro E-Match empfohlen).
2. Verbinden Sie den Nichtelementdraht mit den E-Match Leitungen.
3. Befestigen Sie die E-Match Leitungen an den Ausgangsklemmen des Relaismoduls.
4. **Sicherheit:** Stellen Sie sicher, dass der Stromkreis des Relaismoduls von Ihrer 12V Batterie gespeist wird, die mindestens 6A liefern kann.

### Anschluss der LED (Optional)

1. Wenn Ihr ESP32 keine integrierte LED hat, können Sie eine externe LED anschließen:
    - **GPIO 2** → LED mit geeignetem Widerstand.

    Dies bietet eine visuelle Anzeige des Systemstatus, z.B. Testmodus.

---

## Software-Konfiguration

### Installation der Arduino IDE und ESP32 Board

1. **Laden Sie die Arduino IDE herunter und installieren Sie sie:** [Arduino IDE Download](https://www.arduino.cc/en/software)
2. **Fügen Sie das ESP32 Board zur Arduino IDE hinzu:**
    - Öffnen Sie die Arduino IDE.
    - Gehen Sie zu **Datei > Voreinstellungen**.
    - Fügen Sie die folgende URL zu **Zusätzliche Boardverwalter-URLs** hinzu:
      ```
      https://dl.espressif.com/dl/package_esp32_index.json
      ```
    - Gehen Sie zu **Werkzeuge > Board > Boardverwalter**.
    - Suchen Sie nach **ESP32** und installieren Sie das Paket.

### Hochladen des Codes

1. **Kopieren Sie den Code:**
    - Kopieren Sie den Code aus diesem Handbuch in ein neues Arduino-Sketch in der Arduino IDE.
2. **Wählen Sie das richtige Board und den Port aus:**
    - Gehen Sie zu **Werkzeuge > Board** und wählen Sie Ihr ESP32 Board.
    - Gehen Sie zu **Werkzeuge > Port** und wählen Sie den richtigen COM-Port.
3. **Laden Sie den Code hoch:**
    - Klicken Sie auf die **Hochladen**-Schaltfläche und warten Sie, bis der Code auf den ESP32 geflasht wurde.
4. **Öffnen Sie den Serial Monitor:**
    - Gehen Sie zu **Werkzeuge > Serial Monitor**.
    - Wählen Sie die Baudrate **115200**.
    - Sie sollten folgende Meldungen sehen:
      ```
      Wi-Fi gestartet
      Access Point IP: 192.168.4.1
      HTTP-Server gestartet
      ```

---

## Wi-Fi Einrichtung

1. **Verbinden Sie sich mit dem Wi-Fi des ESP32:**
    - Auf Ihrem Telefon oder Computer suchen Sie das Wi-Fi-Netzwerk **WiFiFyr**.
    - Geben Sie das Passwort **password123** ein.

2. **Passen Sie den Netzwerknamen und das Passwort an:**
    - Öffnen Sie Ihr Arduino-Sketch und suchen Sie die folgenden Zeilen:
      ```cpp
      const char* ssid = "WiFiFyr";
      const char* password = "password123";
      ```
    - Ändern Sie **"WiFiFyr"** in den gewünschten Netzwerknamen.
    - Ändern Sie **"password123"** in ein sicheres Passwort, um unbefugten Zugriff auf Ihr Wi-Fi zu verhindern.

3. **Öffnen Sie die Web-Oberfläche:**
    - Öffnen Sie einen Browser und navigieren Sie zu: [http://192.168.4.1](http://192.168.4.1)

---

## Testen und Validierung

### Testmodus

1. **Aktivieren Sie den Testmodus:**
    - In der Web-Oberfläche markieren Sie die Checkbox **"Enable Test Mode"**.
2. **Testen Sie die LED:**
    - Klicken Sie auf die Feuerungsknöpfe für die Kanäle **1, 2, 3, 4**, um die LED blinken zu lassen.

### Feuerung der Kanäle

1. **Deaktivieren Sie den Testmodus:**
    - Entfernen Sie die Markierung der Checkbox **"Enable Test Mode"**.
2. **Feuern Sie die E-Matches:**
    - Klicken Sie auf die gewünschten Feuerungsknöpfe, um die Relais zu aktivieren und die E-Matches zu entzünden.

### Überwachung der Signalstärke und Verzögerung

- Die Web-Oberfläche zeigt **RSSI** (Signalstärke) und **Verzögerung** (ms) in Echtzeit an, was hilft, die Leistung des Systems zu optimieren.

---

## Sicherheitstipps

1. **Verwenden Sie eine geeignete Stromversorgung:**
    - Eine **12V Batterie** mit mindestens **6A** Stromstärke wird für einen stabilen Betrieb des Relaismoduls und des Nichtelementdrahts empfohlen.
2. **Handhaben Sie den Nichtelementdraht vorsichtig:**
    - Der Nichtelementdraht wird während des Betriebs sehr heiß. Stellen Sie sicher, dass er nicht mit brennbaren Materialien in Kontakt kommt.
3. **Testen Sie das System vor der Verwendung von Feuerwerk:**
    - Verwenden Sie den Testmodus, um sicherzustellen, dass alles korrekt funktioniert, bevor Sie Feuerwerk anschließen und zünden.
4. **Sichere Einrichtung von Feuerwerk:**
    - Platzieren Sie E-Matches und Feuerwerk sicher fern von Personen und brennbaren Oberflächen.
5. **Überwachen Sie das System während der Feuerung:**
    - Seien Sie anwesend und überwachen Sie die Funktion des Systems während der Feuerung, um schnell auf Probleme reagieren zu können.

---

## Fehlerbehebung

### Verbindungsprobleme

- **WiFiFyr verbindet sich nicht mit Wi-Fi:**
  - Überprüfen Sie, ob WiFiFyr korrekt mit Strom und dem Relaismodul verbunden ist.
  - Stellen Sie sicher, dass SSID und Passwort im Code korrekt eingestellt sind.

### Code-Upload-Fehler

- **Fehler beim Hochladen:**
  - Stellen Sie sicher, dass das richtige Board und der richtige Port in der Arduino IDE ausgewählt sind.
  - Starten Sie WiFiFyr neu und versuchen Sie es erneut.

### Relais werden nicht aktiviert

- **Relais werden nicht aktiviert:**
  - Überprüfen Sie alle Verbindungen zwischen WiFiFyr und dem Relaismodul.
  - Stellen Sie sicher, dass die Batterie ausreichend Strom liefert.

### LED blinkt nicht

- **LED blinkt im Testmodus nicht:**
  - Überprüfen Sie die Verbindung zwischen WiFiFyrs GPIO 2 und der LED.
  - Stellen Sie sicher, dass der Widerstand korrekt angeschlossen ist.

---

## Materiallinks

- **ESP32 Entwicklungsboard (Wi-Fi):** [Hier kaufen](https://www.aliexpress.com/item/1005006456519790.html)
- **Relaismodul (4 Kanäle oder mehr):** [Hier kaufen](https://www.aliexpress.com/item/1005002867727977.html)
- **Nichtelementdraht (0,1 mm):** [Hier kaufen](https://www.aliexpress.com/item/1005005947832471.html)
- **E-Match Leitungen (mindestens 20AWG):** [Hier kaufen](https://www.aliexpress.com/item/1005001552897167.html)
- **DC-DC Stepdown Modul (3-12V):** [Hier kaufen](https://www.aliexpress.com/item/1005006149348817.html)
- **Breadboard:** [Hier kaufen](https://www.aliexpress.com/item/32865122971.html)
- **Male-to-Male Jumper Kabel (10 Stück):** [Hier kaufen](https://www.aliexpress.com/item/1005005501503609.html)
- **Male-to-Female Jumper Kabel (10 Stück):** [Hier kaufen](https://www.aliexpress.com/item/1005005501503609.html)

---

## Beitragen und Lizenz

Dieses Projekt ist Open Source und begrüßt Beiträge aus der Gemeinschaft. Wenn Sie beitragen möchten, befolgen Sie diese Schritte:

1. Forken Sie das Projekt auf GitHub.
2. Nehmen Sie Ihre Änderungen in einem neuen Branch vor.
3. Öffnen Sie eine Pull-Anfrage mit einer Beschreibung Ihrer Änderungen.

Das Projekt ist unter der **MIT License** lizenziert, was bedeutet, dass Sie es frei verwenden, ändern und verteilen können.

---

**Hinweis:** Arbeiten Sie immer sicher und verantwortungsbewusst, wenn Sie mit Elektronik und Feuerwerk umgehen. Befolgen Sie lokale Gesetze und Vorschriften zur Verwendung von Feuerwerk.
