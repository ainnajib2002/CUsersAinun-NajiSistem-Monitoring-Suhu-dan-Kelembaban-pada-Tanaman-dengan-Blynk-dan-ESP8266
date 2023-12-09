#define BLYNK_TEMPLATE_ID "TMPL6gAvzTTCo"
#define BLYNK_TEMPLATE_NAME "Sistem Monitoring Suhu dan Kelembaban Tanaman"
#define BLYNK_AUTH_TOKEN "adj0qvn2YAOfdUv_kfmzEJzVAoC4LmpL"

#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h> // Tambahkan header ini

#include <DHT.h>

char auth[] = "adj0qvn2YAOfdUv_kfmzEJzVAoC4LmpL";

char ssid[] = "Nusa kos";  // type your wifi name
char pass[] = "hadehlalicuk";  // type your wifi password

#define Mois A0
#define DHTPIN D1 
#define DHTTYPE DHT11 
BlynkTimer timer; 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println(F("DHTxx test!"));

  Blynk.begin(auth, ssid, pass); // Inisialisasi Blynk

  dht.begin();
}

void loop() {
  Blynk.run(); // Tambahkan ini di loop

  // Wait a few seconds between measurements.
  delay(5000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, analogRead(Mois));

  // Calculate moisture percentage
  float moisturePercentage = map(analogRead(Mois), 0, 1023, 0, 100);
  // Send moisture percentage to Blynk
  Blynk.virtualWrite(V3, moisturePercentage);

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, h);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.print(F("Nilai Kelembaban Udara: "));
  Serial.print(h);
  Serial.println("%");
  Serial.print(F("Nilai Suhu: "));
  Serial.println(t);
  Serial.print(F("°C"));
  Serial.println(F("Heat index: "));
  Serial.print(hic);
  Serial.println(F("°C"));
  Serial.print("Nilai Analog Moisture: ");
  Serial.println(analogRead(Mois));
  Serial.print(F("Nilai Kelembaban Tanah: "));
  Serial.print(moisturePercentage);
  Serial.println("%");
}
