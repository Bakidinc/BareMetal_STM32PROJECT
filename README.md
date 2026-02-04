🚀 STM32 Bare-Metal Programlama Serisi

Bu proje, STM32F410RB (Nucleo-64) mikrodenetleyicisi üzerinde kütüphanesiz (Bare-Metal) programlama öğrenme sürecimi dökümante etmek amacıyla oluşturulmuştur. Bir gömülü yazılım mühendisi olarak, gömülü sistemler dünyasına attığım bu adımda, donanımın en derin seviyelerine inerek sistemleri en verimli, güvenilir ve optimize şekilde çalıştırmayı hedefliyorum.

🛠️ Geliştirme Ortamı ve Araçlar

Proje iki aşamalı bir yapıya sahiptir:

BaremetalF410rbgit
Projenin başlangıç ve temel yapılandırma aşamaları STM32CubeIDE ortamında gerçekleştirilmiştir.

Bare_Metal_Series
Diğer tüm uygulama kodları, sürücüler ve register seviyesindeki geliştirmeler VS Code ortamında; OpenOCD, ARM GNU Toolchain ve Cortex-Debug kullanılarak yazılmıştır.

📚 Yararlanılan Kaynaklar

Bu projeyi geliştirirken aşağıdaki teknik dökümanlardan ve değerli içerik üreticilerinden faydalanılmıştır:

📄 Teknik Dökümanlar

STM32F410x8 / STM32F410xB Datasheet
Donanım özellikleri ve pin yapılandırmaları için.

RM0401 Reference Manual
STM32F410 advanced Arm®-based 32-bit MCUs
(Register detayları ve çevre birimleri yönetimi için).

🎥 Eğitim Kanalları

Low Byte Productions (lowbyteproductions) – Bare Metal Programming Series

AsabreTech (ebenezerasabre) – Bare Metal Programming STM32

📁 Proje Yapısı

Eğitim serisi kapsamında her konu başlığı ayrı bir klasör altında toplanmıştır.

🚀 Başlarken

Projeyi kendi bilgisayarınızda incelemek veya derlemek isterseniz:

git clone --recursive https://github.com/Bakidinc/BareMetal_STM32PROJECT.git


VS Code ile açın ve ilgili proje klasöründeki Makefile üzerinden derleyin.

Debug için launch.json dosyasındaki SVD yollarının STM32F410.svd dosyasını gösterdiğinden emin olun.
