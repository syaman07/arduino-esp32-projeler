#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>
#include <XPT2046_Touchscreen.h>
#include <SPI.h>

// ESP32-S3 Pin Tanımlamaları
#define TFT_CS   10
#define TFT_DC    8
#define TFT_RST   9
#define TOUCH_CS  7

// Ekran ve Dokunmatik Sürücüleri
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS);

// Renk Kodları (16-bit RGB565)
#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

// Çizim Ayarları
int currentColor = RED;
int brushSize = 3; // Fırça kalınlığı

// Dokunmatik Kalibrasyon Değerleri (Ekranınıza göre ince ayar gerekebilir)
#define TS_MINX 200
#define TS_MAXX 3800
#define TS_MINY 200
#define TS_MAXY 3800

void setup() {
  Serial.begin(115200);
  
  // Ekranı Başlat
  tft.begin();
  tft.setRotation(1); // Yatay mod (320x240)
  
  // Dokunmatiği Başlat
  ts.begin();
  ts.setRotation(1); // Ekran rotasyonu ile eşitle
  
  // Tuvali temizle ve arayüzü çiz
  tft.fillScreen(WHITE);
  drawUI();
}

void drawUI() {
  // Renk Paleti Kutuları (Genişlik: 40px, Yükseklik: 40px)
  tft.fillRect(0, 0, 40, 40, RED);
  tft.fillRect(40, 0, 40, 40, GREEN);
  tft.fillRect(80, 0, 40, 40, BLUE);
  tft.fillRect(120, 0, 40, 40, YELLOW);
  tft.fillRect(160, 0, 40, 40, BLACK);
  
  // Silgi Kutusu (Beyaz renk, siyah çerçeve)
  tft.fillRect(200, 0, 40, 40, WHITE);
  tft.drawRect(200, 0, 40, 40, BLACK);
  tft.setTextColor(BLACK);
  tft.setCursor(205, 15);
  tft.setTextSize(1);
  tft.print("SILGI");

  // Temizle Butonu
  tft.fillRect(250, 0, 70, 40, BLACK);
  tft.setTextColor(WHITE);
  tft.setCursor(260, 15);
  tft.setTextSize(1);
  tft.print("TEMIZLE");
  
  // Çizim alanı sınırı
  tft.drawLine(0, 41, 320, 41, BLACK);
}

void loop() {
  // Ekrana dokunuluyor mu kontrol et
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    // Dokunmatik ham verilerini ekran piksel koordinatlarına (320x240) eşitle
    int x = map(p.x, TS_MINX, TS_MAXX, 320, 0);
    // --- KAYMA DÜZELTME EKLEMESİ ---
    x = x + 11; // Eğer çok sağdaysa düşürerek sola çekiyoruz. (8 değerini kayma miktarına göre 5, 10, 12 gibi değiştirebilirsin)
    x = constrain(x, 0, 320); // Ekran dışına taşmayı önler
    // ---------------------------------
    int y = map(p.y, TS_MINY, TS_MAXY, 0, 240);
        // --- KAYMA DÜZELTME EKLEMESİ ---
    y = y - 3; // Eğer çok aşağıdaysa düşürerek yukarı çekiyoruz. (8 değerini kayma miktarına göre 5, 10, 12 gibi değiştirebilirsin)
    y = constrain(y, 0, 320); // Ekran dışına taşmayı önler
    // ---------------------------------

    // Eğer dokunma menü alanındaysa (Üstteki ilk 40 piksel)
    if (y < 40) {
      if (x < 40) {
        currentColor = RED;
      } else if (x < 80) {
        currentColor = GREEN;
      } else if (x < 120) {
        currentColor = BLUE;
      } else if (x < 160) {
        currentColor = YELLOW;
      } else if (x < 200) {
        currentColor = BLACK;
      } else if (x < 240) {
        currentColor = WHITE; // Silgi modu (Arka plan renginde çizer)
      } else if (x > 250) {
        // Ekranı temizle ve menüyü yeniden yükle
        tft.fillRect(0, 42, 320, 198, WHITE);
        delay(300); // Yanlışlıkla tekrar çizmemek için kısa bir bekleme
      }
    } 
    // Eğer dokunma çizim alanındaysa (Aşağısı)
    else {
      // Menü sınırına taşmayı önlemek için y koordinatını fırça payı kadar koruyoruz
      if (y > (42 + brushSize)) {
        tft.fillCircle(x, y, brushSize, currentColor);
      }
    }
  }
}
