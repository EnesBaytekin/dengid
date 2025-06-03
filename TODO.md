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

- [x] objelere hitbox componenti ekle
- [x] objeler için EditorUtility diye bir class oluştur
- [x] objelerin editördeki seçimlerini falan yönetebilmemiz için EditorUtility'ye size'larını alabilecek fonksiyon tanımla

- [ ] collision detection için bir yapı ayarla, script içinden diğer objelere nasıl erişecek
- [ ] objelere tag ekleyebileceğimiz bir yapı ayarla
- [ ] belli taga sahip objeleri filtreleyebileceğimiz fonksiyonlar oluştur

- [ ] undo redo sistemi kur

- [x] camera ekle
- [x] cameraya zoom özelliği ekle
- [x] kameranın en son konum ve zoomu da proje dizininde kaydedilsin, projeyi tekrar açınca ordan devam etsin
- [ ] oyun içinde hareket ettirilebilecek kamera ekle
- [x] oyunu build edince objeler görünmüyor

- [x] engine içinde objeleri mouse ile seçip düzenleyebilmeyi ekle
- [x] objelerin sırasını değiştirebilmeyi ekle
- [x] objeleri silebilmeyi ekle
- [x] objeleri kopyalamayı ekle
- [x] componentleri silebilmeyi ekle
- [x] obje şablonu oluşturmayı ekle
- [x] şablon objeleri ekleyebilmeyi ekle
- [ ] şablonlar eklenince doğrudan sahneye kopyalanmasın. şablon olduğu belirtilen bir şey olsun. şablon dosyasını build ederken dinamik çeksin. böylece bir şablon düzenlendiğinde daha önceden o çablon ile oluşturulmuş objede de aynı değişiklik yapılmış olsun.
- [ ] templateleri unique yapabilmeyi ekle
- [ ] projedeki templateler bir pencerede listelensin. kolayca seçip eklenebilsin

- [ ] son açılan proje en üste olacak şekilde sırala
- [x] proje açarken belirli dizindeki projeler seçilebilsin
- [ ] yeni proje oluştururken klasör oluşacağını belirten bir yazı ekle
- [x] projeyi kapatıp tekrar initial view'e dönmeyi ekle
- [ ] proje ayarlarını game exe sine yansıt. pencere boyutları gibi

- [x] objelere depth ekle
- [x] ysort componenti ekle
- [x] ysort inspectorde düzgün görünmüyor
- [ ] image componentine offset ekle

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

- [ ] custom scriptlerin sonuna register_script otomatik eklensin
- [ ] create new script seçeneği ekle
- [ ] scriptler proje rootunda olmadığı sürece çalışmıyor, onu düzelt

- [x] ui'daki bir şeylere tıklayınca arkadaki sahneye de tıklanmış oluyor ve başka objeler falan seçiliyor. tıklama ui'da ise sahneye etki etmesin

- [x] engine kapandığında o anki çalışmakta olan oyun açık kalıyor
