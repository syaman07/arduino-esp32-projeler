# ESP32-S3 & ILI9341 Dokunmatik Paint Projesi

Bu proje, **ESP32-S3** mikrodenetleyicisi ve **2.4 inç ILI9341 TFT Dokunmatik Ekran** kullanılarak geliştirilmiş, donanım tabanlı bir dijital çizim (Paint) uygulamasıdır. Kullanıcılar ekran üzerindeki dokunmatik paneli kullanarak çizim yapabilir, renk değiştirebilir ve tuvali temizleyebilir.

---

## 🛠️ Donanım Gereksinimleri & Bağlantı Şeması

### Gerekli Donanımlar
1. ESP32-S3 Geliştirme Kartı
2. ILI9341 2.4" veya 2.8" TFT Dokunmatik Ekran (XPT2046 Dokunmatik Entegreli)
3. Jumper Kablolar

### Pin Bağlantı Tablosu

| Ekran / Dokunmatik Pini | ESP32-S3 GPIO Pini | Açıklama |
| :--- | :--- | :--- |
| **TFT_CS** | 10 | TFT Chip Select |
| **TFT_DC** | 8 | TFT Data/Command |
| **TFT_RST** | 9 | TFT Reset |
| **TOUCH_CS** | 7 | Touch Screen Chip Select |
| **MOSI** | `[SPI MOSI PİNİNİ YAZ]` | SPI Master Out Slave In |
| **MISO** | `[SPI MISO PİNİNİ YAZ]` | SPI Master In Slave Out |
| **SCK** | `[SPI SCK PİNİNİ YAZ]` | SPI Clock |

---

## 📚 Gerekli Kütüphaneler

Projenin Arduino IDE üzerinde sorunsuz derlenebilmesi için aşağıdaki kütüphanelerin kurulması gerekmektedir:

* `Adafruit_GFX.h` (Ekran grafik çizimleri için)
* `Adafruit_ILI9341.h` (Ekran sürücüsü için)
* `XPT2046_Touchscreen.h` (Dokunmatik panel sürücüsü için)

---

## ⚙️ Kurulum ve Çalıştırma

1. Bu repository'yi bilgisayarınıza indirin veya klonlayın.
2. `paintprojesi/paintprojesi.ino` dosyasını Arduino IDE ile açın.
3. **Araçlar > Kart** menüsünden kendi ESP32-S3 modelinizi seçin.
4. Gerekli kütüphanelerin yüklü olduğundan emin olun.
5. Yukarıdaki pin şemasına göre bağlantılarınızı yapın ve kodu kartınıza yükleyin.

> ⚠️ **Kalibrasyon Notu:** Ekran panellerindeki üretim farklılıklarından dolayı dokunmatikte kaymalar yaşanabilir. Kod içerisindeki `TS_MINX`, `TS_MAXX`, `TS_MINY`, `TS_MAXY` değerleri ile `x = x + 11` / `y = y - 3` olarak belirlenen kayma düzeltme değerlerini kendi ekranınıza göre ince ayar yaparak optimize edebilirsiniz.
