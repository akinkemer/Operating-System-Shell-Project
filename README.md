# OperatingSystemsProject
SAÜ Bilgisayar Mühendisliği İşletim Sistemleri Grup Proje Ödevi

## String Methodları
```C
#include <string.h>
```
String metotlarını kullanabilmek için bu kütüphaneyi dahil etmemiz gerekiyor


### puts()
- String'i direkt olarak ekrana yazdırır ve alt satıra geçer.

```C
int puts(const char *string)
```

```C
 char str[]="This is a test string";
 puts(str);
 puts(str);
```
Çıktı:

*This is a test string*

*This is a test string*


### sscanf()
- Stringi başka tiplere çevirmek için kullanılır. 1 döndürürse işlem başarılıdır.

```C
int sscanf(const char *str, const char *format, ...)
```

```C
char str[]="12";
int i;
if(sscanf(str, "%d", &i) ==1 ){
  printf("İşlem başarılı i=%d",i);
}
```
Çıktı:

*İşlem başarılı i=12*

### strlen()
- String uzunluğunu bulma fonksiyonu

```C
size_t strlen(const char *str);
```

```C
char a[20]="Program";
printf("Length of string a = %s \n",strlen(a));
```
Çıktı:

*Length of string a = 7*


### strcpy()
- String s2'yi s1'e kopyalar

```C
char *strcpy(char *s1, char *s2);
```

```C
char give[5];
strcpy(give, "Give");
printf("%s\n", give);
```
Çıktı:

*Give*

### strcat()
- String s2'yi s1'e ekler

```C
char *strcat(char *destination, const char *source)
```

```C
char str1[100] = "Operating ", str2[] = "Systems";
strcat(str1, str2);
puts(str1);
```
Çıktı:

*Operating Systems*



### strcmp() ve strncmp()
- İki stringi karşılaştırır eşitse 0 döner. strncmp istenilen indexe kadar karşılaştırma yapar

```C
int strcmp(char *s1, char *s2);
int strncmp(char *s1, char *s2, int n);
```

```C
char str1[]="abc";
char str2[]="bac";
if(strcmp(str1,str2)==0){
  puts("Eşit");
}
else{
  puts("Eşit değil");
}
```
Çıktı:

*Eşit değil*


### strchr()
- Stringin içinden karakter bulmak için kullanılır.

```C
char *strchr(char *s, int c);
```

```C
 const char cdizi[] = "Bilgisayar";
 char *ret;
 let = strchr(cdizi, 's');
 printf("Bulunan karakterden itibaren dizi içeriği: %s", ret);
```
Çıktı:

*Bulunan karakterden itibaren dizi içeriği: sayar*


### strtok()
- stringi parçalara ayırmak için kullanılır

```C
char *strtok(char *str, const char *delim)
```

```C
 char str[80] = "saü bilgisayar mühendisliği";
 const char s[2] = " ";
 char *token;

  token = strtok(str, s);
   
  while( token != NULL ) {
      printf( " %s\n", token );
    
      token = strtok(NULL, s);
   }
```
Çıktı:

*saü*

*bilgisayar*

*mühendisliği*
