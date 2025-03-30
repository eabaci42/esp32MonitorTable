# <div align="center">🖥️ ESP32 Monitör Masa Kontrol Sistemi</div>

<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0891b2&height=200&section=header&text=ESP32%20Monitör%20Masa&fontSize=50&fontColor=ffffff&animation=fadeIn&fontAlignY=38" alt="ESP32 Monitör Masa" />
</div>

<p align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=22&duration=2000&pause=500&color=0891B2&center=true&vCenter=true&width=450&lines=Durum+Makinesi+Kontrol+Sistemi;Motor+Kontrol+%C3%9Cnitesi;Buton+%C4%B0%C5%9Fleme+Mant%C4%B1%C4%9F%C4%B1;Kapak+Y%C3%B6netim+Mod%C3%BCl%C3%BC;Hata+Yakalama+Sistemi" alt="Typing SVG" />
</p>

<div align="center">
  <a href="https://github.com/eabaci42/esp32MonitorTable">
    <img src="https://img.shields.io/badge/GitHub-esp32MonitorTable-181717?style=for-the-badge&logo=github&logoColor=white" />
  </a>
  <a href="https://www.arduino.cc/reference/en/">
    <img src="https://img.shields.io/badge/Platform-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  </a>
  <a href="https://www.espressif.com/en/products/socs/esp32">
    <img src="https://img.shields.io/badge/Microcontroller-ESP32-D4222A?style=for-the-badge&logo=espressif&logoColor=white" />
  </a>
</div>

## <div align="center">📋 Proje Açıklaması</div>

<div align="center">
  <img src="https://media.giphy.com/media/7c8QeB0VMddFOuu4iR/giphy.gif" width="400" />
</div>

<div align="center">
  <table style="background-color: #101728; width: 85%; margin: 25px auto; border-collapse: collapse; border-radius: 8px; overflow: hidden; border-left: 5px solid #0891b2;">
    <tr>
      <td style="padding: 20px; text-align: left;">
        <p><i><b>"Sonlu Durum Makinesi mantığıyla tasarlanmış tam otomatik monitör masa kontrol sistemi"</b></i></p>
        <p>Bu proje, ESP32 mikrodenetleyicisi kullanılarak bir monitör masasının kapak ve motor hareketlerini kontrol eden modüler bir sistemdir. Sonlu Durum Makinesi (FSM) kullanarak farklı durumlar arasında geçiş yapar ve kullanıcı girişlerine göre masanın hareketlerini koordine eder.</p>
        <p>Sistem, kullanıcı tarafından basılan butonlara veya limit switchlerin durumuna bağlı olarak, ana motor, ikincil motor ve kapak motoru olmak üzere üç farklı motoru kontrol eder. Motorların doğru sırayla ve güvenli bir şekilde çalışmasını sağlamak için kapsamlı bir durum makinesi uygulanmıştır.</p>
        <p><i><b>"Modüler tasarım sayesinde bakım ve geliştirme süreci kolaylaştırılmıştır."</b></i></p>
      </td>
    </tr>
  </table>
</div>

## <div align="center">🔌 Donanım Bağlantıları</div>

<div align="center">
  <table>
    <tr>
      <th>Bileşen</th>
      <th>Pin Numarası</th>
      <th>Açıklama</th>
    </tr>
    <tr>
      <td>Yukarı Butonu</td>
      <td>25</td>
      <td>Yukarı yönlü hareketi başlatır</td>
    </tr>
    <tr>
      <td>Aşağı Butonu</td>
      <td>26</td>
      <td>Aşağı yönlü hareketi başlatır</td>
    </tr>
    <tr>
      <td>Durdurma Butonu</td>
      <td>27</td>
      <td>Hareketi durdurur</td>
    </tr>
    <tr>
      <td>Yatay Butonu</td>
      <td>14</td>
      <td>Yatay eksende hareketi başlatır</td>
    </tr>
    <tr>
      <td>Dikey Butonu</td>
      <td>13</td>
      <td>Dikey eksende hareketi başlatır</td>
    </tr>
    <tr>
      <td>Başlatma Anahtarı</td>
      <td>36</td>
      <td>Sistemin temel konumunu algılar</td>
    </tr>
    <tr>
      <td>Kapak Açık Anahtarı</td>
      <td>39</td>
      <td>Kapağın açık olduğunu algılar</td>
    </tr>
    <tr>
      <td>Kapak Kapalı Anahtarı</td>
      <td>34</td>
      <td>Kapağın kapalı olduğunu algılar</td>
    </tr>
    <tr>
      <td>Y-Maksimum Anahtarı</td>
      <td>35</td>
      <td>Y ekseninde maksimum konumu algılar</td>
    </tr>
    <tr>
      <td>Dikey Konum Anahtarı</td>
      <td>32</td>
      <td>Dikey konumu algılar</td>
    </tr>
    <tr>
      <td>Son Konum Anahtarı</td>
      <td>33</td>
      <td>Sistemin son konumunu algılar</td>
    </tr>
    <tr>
      <td>Ana Motor İleri</td>
      <td>23</td>
      <td>Ana motorun ileri yönde hareketi</td>
    </tr>
    <tr>
      <td>Ana Motor Geri</td>
      <td>22</td>
      <td>Ana motorun geri yönde hareketi</td>
    </tr>
    <tr>
      <td>İkincil Motor İleri</td>
      <td>3</td>
      <td>İkincil motorun ileri yönde hareketi</td>
    </tr>
    <tr>
      <td>İkincil Motor Geri</td>
      <td>21</td>
      <td>İkincil motorun geri yönde hareketi</td>
    </tr>
    <tr>
      <td>Kapak Motor İleri</td>
      <td>19</td>
      <td>Kapak motorunun ileri yönde hareketi</td>
    </tr>
    <tr>
      <td>Kapak Motor Geri</td>
      <td>18</td>
      <td>Kapak motorunun geri yönde hareketi</td>
    </tr>
  </table>
</div>

## <div align="center">🧩 Proje Yapısı</div>

<div align="center">
  <img src="https://media.giphy.com/media/QNFhOolVeCzPQ2Mx85/giphy.gif" width="400" />
</div>

Proje, modüler bir yapıda organize edilmiştir:

```
esp32MonitorTable/
├── include/             # Header dosyaları
│   ├── buttons/         # Butonlarla ilgili tanımlamalar
│   ├── cap/             # Kapak kontrolü ile ilgili tanımlamalar
│   ├── config/          # Konfigürasyon ve pin tanımlamaları 
│   ├── motors/          # Motor kontrolü ile ilgili tanımlamalar
│   ├── states/          # Durum makinesi ve durum tanımlamaları
│   └── utils/           # Yardımcı fonksiyonlar ve bayraklar
├── src/                 # Kaynak dosyaları
│   ├── buttons/         # Buton işlevleri implementasyonu
│   ├── cap/             # Kapak kontrol işlevleri implementasyonu
│   ├── config/          # (Boş, yalnızca header içeriyor)
│   ├── motors/          # Motor kontrol işlevleri implementasyonu
│   ├── states/          # Durum makinesi ve durum işlevleri implementasyonu
│   └── utils/           # Yardımcı fonksiyonlar implementasyonu
├── srclib/              # Harici kütüphaneler
│   ├── ezButton/        # Buton debounce kütüphanesi
│   └── FiniteStateMachine/ # FSM kütüphanesi
├── main.ino             # Ana program dosyası
├── LICENSE              # Lisans bilgileri
└── README.md            # Proje açıklaması (bu dosya)
```

## <div align="center">🔄 Sonlu Durum Makinesi</div>

<div align="center">
  <table>
    <tr>
      <td>
        <h3>Durum Geçişleri</h3>
        <img src="https://media.giphy.com/media/3oKIPsx2VAYAgEHC12/giphy.gif" width="300" />
        <p>Sistem aşağıdaki durum geçişlerini kullanır:</p>
        <ul>
          <li>START → OPENCAP → Y_RISING → YZ_VERTICAL → Z_RISING → PRESENTATION</li>
          <li>PRESENTATION → Z_FALLING → YZ_VERTICAL → Y_FALLING → CLOSECAP → START</li>
          <li>Her durum için orta konumlar (Y_MIDDLE, Z_MIDDLE)</li>
          <li>Hata durumları için ERROR durumu</li>
        </ul>
      </td>
      <td>
        <h3>Durum İşlevleri</h3>
        <img src="https://media.giphy.com/media/3o7qDPfGhunRMZikI8/giphy.gif" width="300" />
        <p>Her durum için tanımlanmış işlevler:</p>
        <ul>
          <li><b>startState()</b> - Başlangıç durumu</li>
          <li><b>openCapState()</b> - Kapak açma durumu</li>
          <li><b>closeCapState()</b> - Kapak kapatma durumu</li>
          <li><b>yrisingState()</b> - Y ekseninde yükselme</li>
          <li><b>yfallingState()</b> - Y ekseninde inme</li>
          <li><b>zrisingState()</b> - Z ekseninde yükselme</li>
          <li><b>zfallingState()</b> - Z ekseninde inme</li>
          <li><b>yzverticalState()</b> - Y-Z eksenlerinde dikey pozisyon</li>
          <li><b>presentationState()</b> - Sunum modu</li>
        </ul>
      </td>
    </tr>
  </table>
</div>

## <div align="center">⚙️ Kurulum</div>

<div align="center">
  <img src="https://media.giphy.com/media/RJzm826vu7WbJvBtxX/giphy.gif" width="400" />
</div>

1. Bu projeyi klonlayın:
   ```sh
   git clone https://github.com/eabaci42/esp32MonitorTable.git
   ```

2. Arduino IDE'yi açın ve gerekli kütüphaneleri yükleyin:
   - ezButton
   - FiniteStateMachine

3. `Tools -> Board` menüsünden ESP32 geliştirme kartınızı seçin.

4. Donanım bağlantılarını pin tablosuna göre yapın.

5. Projeyi derleyin ve ESP32'ye yükleyin.

## <div align="center">🚀 Kullanım</div>

<div align="center">
  <img src="https://media.giphy.com/media/YnexM3nEIKtPxpNKJi/giphy.gif" width="400" />
</div>

1. Sistemi çalıştırdıktan sonra, monitör masası başlangıç konumunda olacaktır.

2. Yukarı butonu ile hareketi başlatın:
   - Önce kapak açılacak
   - Sonra Y ekseninde yükselme başlayacak
   - Y-Max konumuna ulaşıldığında Z ekseni hareketi başlayacak
   - Son konuma ulaşıldığında sunum moduna geçilecek

3. Aşağı butonu ile geri dönüş hareketini başlatın:
   - Z ekseni aşağı inecek
   - Y ekseni aşağı inecek
   - Başlangıç konumuna geldiğinde kapak kapanacak

4. Durdurma butonu ile hareketi istediğiniz zaman durdurabilirsiniz.

5. Yatay ve dikey butonları ile manuel kontrol yapabilirsiniz.

## <div align="center">🛠️ Modüller</div>

<div align="center">
  <table>
    <tr>
      <td width="33%" align="center">
        <h3>🔘 Buton Modülü</h3>
        <img src="https://media.giphy.com/media/xT0GqimU9dTwmE5lra/giphy.gif" width="200" />
        <p>Butonların durumlarını okur ve debounce uygular.</p>
      </td>
      <td width="33%" align="center">
        <h3>⚙️ Motor Modülü</h3>
        <img src="https://media.giphy.com/media/3ornjXbo3cjqh2BIyY/giphy.gif" width="200" />
        <p>Motorların ileri, geri ve durma işlemlerini kontrol eder.</p>
      </td>
      <td width="33%" align="center">
        <h3>🚪 Kapak Modülü</h3>
        <img src="https://media.giphy.com/media/l0HlQXlQ3nHyLMvte/giphy.gif" width="200" />
        <p>Kapağın açılıp kapanmasını yönetir.</p>
      </td>
    </tr>
    <tr>
      <td width="33%" align="center">
        <h3>🔄 Durum Modülü</h3>
        <img src="https://media.giphy.com/media/qgQUggAC3Pfv687qPC/giphy.gif" width="200" />
        <p>Durum makinesi ve durum geçişlerini yönetir.</p>
      </td>
      <td width="33%" align="center">
        <h3>🚩 Bayraklar Modülü</h3>
        <img src="https://media.giphy.com/media/QWvra259h4LCvdJnxP/giphy.gif" width="200" />
        <p>Sistem durumunu izleyen bayrakları yönetir.</p>
      </td>
      <td width="33%" align="center">
        <h3>⚠️ Hata Yönetimi</h3>
        <img src="https://media.giphy.com/media/3osxY9kuM2NGUfvThe/giphy.gif" width="200" />
        <p>Hata durumlarını tespit eder ve raporlar.</p>
      </td>
    </tr>
  </table>
</div>

## <div align="center">⚡ Teknik Özellikler</div>

<div align="center">
  <img src="https://img.shields.io/badge/Mikrodenetleyici-ESP32-D4222A?style=for-the-badge&logo=espressif&logoColor=white" />
  <img src="https://img.shields.io/badge/Programlama_Dili-C++-00599C?style=for-the-badge&logo=cplusplus&logoColor=white" />
  <img src="https://img.shields.io/badge/Framework-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/Durum_Makinesi-FSM-2B822E?style=for-the-badge&logo=arduino&logoColor=white" />
  <img src="https://img.shields.io/badge/Motor_Kontrolü-PWM-FF9E0F?style=for-the-badge&logo=arduino&logoColor=white" />
</div>

<table align="center">
  <tr>
    <td width="50%">
      <h3>💾 Bellek Kullanımı</h3>
      <ul>
        <li>Program Hafızası: ~30KB</li>
        <li>Dinamik Bellek: ~5KB</li>
        <li>Durum Makinesi: 14 Durum</li>
      </ul>
    </td>
    <td width="50%">
      <h3>⏱️ Performans</h3>
      <ul>
        <li>Buton Debounce Süresi: 50ms</li>
        <li>Durum Geçiş Süresi: <5ms</li>
        <li>Seri Haberleşme Hızı: 115200 baud</li>
      </ul>
    </td>
  </tr>
</table>

## <div align="center">📝 Hata Kodları</div>

<div align="center">
  <img src="https://media.giphy.com/media/xT9IgzoKnwFNmISR8I/giphy.gif" width="400" />
</div>

<div align="center">
  <table>
    <tr>
      <th>Hata Kodu</th>
      <th>Açıklama</th>
    </tr>
    <tr>
      <td>E02X001</td>
      <td>openCapState fonksiyonuna yetkisiz erişim</td>
    </tr>
    <tr>
      <td>E02X002</td>
      <td>openCapFlag beklenmeyen değere sahip</td>
    </tr>
    <tr>
      <td>E02X003</td>
      <td>Kapak açma işlemi sırasında hata oluştu</td>
    </tr>
    <tr>
      <td>E03X001</td>
      <td>closeCapState fonksiyonuna yetkisiz erişim</td>
    </tr>
    <tr>
      <td>E03X002</td>
      <td>closeCapFlag beklenmeyen değere sahip</td>
    </tr>
    <tr>
      <td>E03X003</td>
      <td>Kapak kapatma işlemi sırasında hata oluştu</td>
    </tr>
  </table>
</div>

## <div align="center">👨‍💻 Geliştirici</div>

<div align="center">
  <a href="https://github.com/eabaci42">
    <img src="https://img.shields.io/badge/GitHub-eabaci42-181717?style=for-the-badge&logo=github&logoColor=white" />
  </a>
  <a href="mailto:ertugrul@atikrost.com">
    <img src="https://img.shields.io/badge/Email-ertugrul@atikrost.com-D14836?style=for-the-badge&logo=gmail&logoColor=white" />
  </a>
  <a href="https://www.linkedin.com/in/eabaci42">
    <img src="https://img.shields.io/badge/LinkedIn-eabaci42-0077B5?style=for-the-badge&logo=linkedin&logoColor=white" />
  </a>
</div>

<div align="center">
  <a href="https://github.com/eabaci42">
    <img src="https://github-readme-stats-git-masterrstaa-rickstaa.vercel.app/api?username=eabaci42&show_icons=true&theme=tokyonight&hide_title=true&count_private=true&hide_border=true" alt="GitHub İstatistikleri" />
  </a>
</div>

## <div align="center">📜 Lisans</div>

<div align="center">
  <img src="https://media.giphy.com/media/VgGthkhUvGgOit7Y9i/giphy.gif" width="300" />
</div>

<div align="center">
  <a href="https://github.com/eabaci42/esp32MonitorTable/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/eabaci42/esp32MonitorTable?style=for-the-badge&color=0891b2" alt="License" />
  </a>
</div>

<div align="center">
  <p>Bu proje MIT Lisansı altında lisanslanmıştır. Daha fazla bilgi için <a href="LICENSE">LICENSE</a> dosyasına bakın.</p>
</div>

<div align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=0891b2&height=150&section=footer&fontSize=30"/>
</div>

<div align="center">
  <img src="https://readme-typing-svg.demolab.com?font=Fira+Code&size=18&duration=2000&pause=500&color=0891b2&center=true&vCenter=true&width=500&lines=Modüler+kod+daha+iyi+kodtur...;Basit+çözümler+karmaşık+sorunları+yener...;İyi+tasarlanmış+sistem+uzun+ömürlüdür...;İyi+dokümantasyon+projeyi+ölümsüzleştirir..." alt="Slogan" />
</div>
