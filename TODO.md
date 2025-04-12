# TODO

- [x] libdengid.a şeklinde her şeyi değil de sadece oyunu compile etmek için gerekli olan dosyaları lib olarak kaydet.
- [x] oyun için spesifik olan kodları (app_main.cpp falan gibi) engine_build dizininin içinde ki src ve include içinde tanımla
- [x] engine_build içinde oyunu build edecek bir Makefile oluştur.

- [x] makefile yazmayı öğren. wildcard lar ya da recursive dizin okumalar falan nasıl yapılıyor öğren
- [x] game_main ile main dosyalarını src den ayır ve ayrı ayrı çalışacak makefile'lar yaz
- [x] oyunu önce manual olarak build et
- [x] sonra engine ve game için kullanılan ortak kaynak kodları .a gibi library olarak kaydet ve bu şekilde manual compile et
- [x] sonra build işlemini engine içinde yapan fonksiyonu (veya sistemi) kur
- [x] oyunu engine içinden build edebilmeyi sağla
- [x] build edilen oyun executable'ının içinde sahne ve obje verilerinin çalışmasını sağla

- [x] projeyi build etmeden önce otomatik kaydetsin
- [ ] build sürecini engine içinde ui da göster
- [x] build sürecinde custom scriptleri .o olarak kaydet ve sadece değişen dosyalar compile edilsin
- [x] yeni proje açıldığında engine_build dizinindeki makefile ile clean çalıştırsın ki oyuna özgü obj dosyaları falan temizlensin

- [X] engine içinde projeyi çalıştırma seçeneği ekle
- [x] custom scriptleri çalıştırmayı ekle
- [x] input handling mekanizmasını kur
- [x] script içinde inputları test edebileceğimiz fonksiyonlar tanımla
- [x] input handle edebileceğimiz başka fonksiyonlar da tanımla
- [x] mouse inputları için fonksiyonlar da tanımla
- [ ] bir component tipinden birden fazla olabilsin. özellikle script componenti için
- [ ] bir script içinden başka componentlerin içeriklerine kolayca erişilebilsin
- [x] engine içinde kısayol tuşlarını ekle

- [ ] collision detection için bir yapı ayarla, script içinden diğer objelere nasıl erişecek
- [ ] objelere tag ekleyebileceğimiz bir yapı ayarla
- [ ] belli taga sahip objeleri filtreleyebileceğimiz fonksiyonlar oluştur

- [ ] undo redo sistemi kur

- [ ] camera ekle
- [ ] engine içinde objeleri mouse ile seçip düzenleyebilmeyi ekle
- [ ] objelerin sırasını değiştirebilmeyi ekle
- [ ] objeleri silebilmeyi ekle
- [ ] objeleri kopyalamayı ekle
- [ ] componentleri silebilmeyi ekle
- [ ] obje şablonu oluşturmayı ekle
- [ ] şablon objeleri ekleyebilmeyi ekle

- [ ] son açılan proje en üste olacak şekilde sırala
- [ ] proje açarken belirli dizindeki projeler seçilebilsin
- [ ] yeni proje oluştururken klasör oluşacağını belirten bir yazı ekle
- [ ] projeyi kapatıp tekrar initial view'e dönmeyi ekle
- [ ] proje ayarlarını game exe sine yansıt. pencere boyutları gibi

- [ ] objelere depth ekle
- [ ] ysort componenti ekle

- [x] editore terminal windowu ekle
- [x] terminal windowuna yazdırmaya yarayan print fonksiyonu ekle
- [ ] terminal windowundaki mouse ile yazılar seçilip kopyalanabilsin
- [x] build edilen game çalışırken print edilen şeyler normal terminale (stdout) yazdırılıyor. game, engine içinde çalıştırıldığında buraya yazılan şeyleri engine terminalinde yazdır
- [x] debug mesajlarını falan bu windowa ekle
- [x] birden fazla oyun aynı anda çalıştırılamasın engine içinde. run fonksiyonu çalışınca baksın zaten çalışıyor mu diye, çalışmıyorsa çalıştırsın. çalışırken build de edilemesin
- [x] build edilmemişken çalıştırmaya çalışılırsa hata vermesin uyarı yazsın
- [x] engine içinden oyunu durdurabileceğimiz bir stop seçeneği ekle

- [x] scriptteki macroları düzenle. app global olsun. print olmasın
- [ ] scriptteki get component macrolarını düzenle
