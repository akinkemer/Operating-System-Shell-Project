#İŞLETİM SİSTEMLERİ  - KABUK PROJESİ

G181210386      Samet Ertaş (2A)

G181210101       Akın Kemer (2A)

G181210062     Emrullah Enes Can (2A)

B191210302      Elif Kuş (1A)

G191210383      Emre Koç (1A)


TASARIMA GENEL BAKIŞ

  Kodumuzda genel olarak bir kabuktaki gibi komutların girilip çalışmasını sağladık, bunu iki yöntemle biri komut sisteminden direk komutları çalıştırarak diğeri ise bir dosyadan aldığımız komutları okuyarak gerçekleştirdik. Ayrıca kabuğumuzda ";" işareti ile birden fazla komutun aynı anda girişini sağladık. Bunu yaparken komutları ayırdık ve boşluk kontrollerini de sağladık. Kabuğun sorunsuz çalışması için ise belli yerlerde hata kontrollerine yer verdik. Komutların icra edilmesinde execvp ve wait fonksiyonlarından yararlandık.
  
ÖZEL DURUMLAR
  
  Birden fazla komut girişi için olan ";" işareti için pointer yardımıyla ";" gördüğümüz yerde komutları bir diziye aktararak komutların beraber çalışma özel durumu sağlamaya çalıştık. Ve aslında komutları boşluk ve virgüllere göre bölmüş olduk.
  Komut yok komut yürütülemez, dosya açılamıyor kontrollerini sağladık, kabuk entere basılma, fazladan boşluk, ctrl-d gibi işlevler ile çalışıyor.
  Komutun birden fazla kelimeli argümanlarını dizi ve fonksiyonlarla gerçekleştirdik.
