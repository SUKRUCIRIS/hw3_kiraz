# ŞÜKRÜ ÇİRİŞ 18401785

## Explain why the cleanup code doesn’t work very well:
Cleanup kodunda Stmt::reset_root(); fonksiyonu çağrılıyordu. Bu fonksiyon shared_pointer olan root'un referans sayısını 1 azaltır. Eğer referans sayısı 1'den fazla ise pointer silinmez. Bir while döngüsünde referans sayısı 0 olana kadar reset fonksiyonu çağrılması lazım, tamamen silinmesi için.
## Implement a test fixture and move the common code from the init and cleanup stages there:
test_clear fonksiyonunu yazdım, tüm testlerdeki cleanup aşamasında kullanmak için. Yukarda anlattığım şeyi de yaptım. init için fazladan fonksiyon yazmadım çünkü zaten tek satır ve teste göre değişiyor. Bence mantıksız olur :). test_hw3.cc dosyasına değişiklik yaptım.