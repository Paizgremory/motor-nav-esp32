// Sketch minimal untuk tes SD saja, terpisah dari firmware utama.
// Upload ini dulu ke board yang sama, lihat hasil di Serial Monitor (115200 baud).
#include <SPI.h>
#include <SD.h>

#define SD_SCK   21
#define SD_MISO  17
#define SD_MOSI  22
#define SD_CS    16

SPIClass sdSpi(HSPI);

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Mulai tes SD...");
  sdSpi.begin(SD_SCK, SD_MISO, SD_MOSI, SD_CS);

  if (!SD.begin(SD_CS, sdSpi, 1000000)) {   // paling pelan: 1 MHz
    Serial.println("GAGAL: SD.begin() return false");
    return;
  }
  uint8_t type = SD.cardType();
  Serial.printf("Tipe kartu: %u\n", type);
  if (type == CARD_NONE) {
    Serial.println("Tidak ada kartu terdeteksi sama sekali");
  } else {
    Serial.printf("Ukuran kartu: %llu MB\n", SD.cardSize() / (1024ULL * 1024ULL));
    File root = SD.open("/");
    File f = root.openNextFile();
    while (f) {
      Serial.printf("File: %s (%u bytes)\n", f.name(), (unsigned)f.size());
      f = root.openNextFile();
    }
    Serial.println("SD BERHASIL DIBACA!");
  }
}

void loop() {}
