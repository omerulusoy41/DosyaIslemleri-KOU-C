#include <stdio.h>
#include <stdlib.h>
struct kayit{
   int ogrNo;
   int dersKodu;
   int puan;
};
typedef struct kayit kayit;
int main()
{
    FILE *index,*veri;
    printf("Programa Hosgeldiniz...\n");
    while(1){
        printf("1-)Kayit Ekle\n2-)Kayit Bul\n3-)Kayit Sil\n4-)Kayit Guncelle\n5-)Veri Dosyasini Goster\n6-)Indeks Dosyasini Goster\n7-)Index Dosyasini Sil\n8-)Index Dosyasi Olustur\n9-)cikis\n");
        printf("Bir secim yapiniz=");
        int secim;
        scanf("%d",&secim);
        fflush(stdin);
        switch(secim){
    case 1:
        kayitEkle(veri);
        break;
    case 2:
        if((index=fopen("index.txt","r"))==NULL){
         printf("Index Dosyasi Bulunamadi.\n");
         printf("Bu fonksiyonu Kullanmak Icin Index Dosyasi Olusturulmasi Gerekiyor.\nOlusturmak Icin 8'e Basiniz(fonksiyondan cikmak icin 0 a basiniz).\n");
         int kontrol=0;
         scanf("%d",&kontrol);
         if(kontrol==8){
            indexDosyasiniGuncelle(index,veri);
            printf("Dosya Olusturuldu.\n");
         }else{
            break;
         }
       }else{
           fclose(index);
           indexDosyasiniGuncelle(index,veri);
       }
        kayitBul(index);
        break;
    case 3:
        kayitSil();
        break;
    case 4:
        kayitGuncelle(veri);
        break;
    case 5:
        veriDosyasiniGoster(veri);
        break;
    case 6:
        if((index=fopen("index.txt","r"))==NULL){
         printf("Index Dosyasi Bulunamadi.\n");
         printf("Bu fonksiyonu Kullanmak Icin Index Dosyasi Olusturulmasi Gerekiyor.\nOlusturmak Icin 8'e Basiniz(fonksiyondan cikmak icin 0 a basiniz).\n");
         int kontrol=0;
         scanf("%d",&kontrol);
         if(kontrol==8){
            indexDosyasiniGuncelle(index,veri);
            printf("Dosya Olusturuldu.\n");
         }else{
            break;
         }
       }else{
           fclose(index);
           indexDosyasiniGuncelle(index,veri);
       }
        indexDosyasiniGoster(index);
        break;
    case 7:
        indexDosyasiniSil();
        break;
    case 8:
        indexDosyasiniGuncelle(index,veri);
        printf("Index Dosyasi Olusturuldu...\n");
        break;
    case 9:
        printf("Programdan Cikiliyor...");
        exit(1);
        break;
    default :
        printf("Hatali Giris!!!\n");
        break;

        }
        printf("\n\n");
    }
    return 0;
}
void indexDosyasiniGuncelle(FILE *index,FILE *veri){
      if((veri=fopen("veri.bin","rb"))==NULL){
         printf("Veri Dosyasi Bulunamadi.\n");
      }else{
          int boyut=0;
          int *adres=malloc(sizeof(int)*100);
          int *ogrNo=malloc(sizeof(int)*100);
          kayit *kayitlar=malloc(sizeof(kayit)*100);
          while(fread(&kayitlar[boyut],sizeof(kayit),1,veri)){
              adres[boyut]=&kayitlar[boyut];
              ogrNo[boyut]=kayitlar[boyut].ogrNo;
              boyut++;
          }
          fclose(veri);
          if((index=fopen("index.txt","w"))==NULL){
              printf("dosya Acilamadi.");
          }else{
              for(int i=0;i<boyut;i++){
                  for(int j=0;j<boyut-1;j++){
                      if(ogrNo[j]>ogrNo[j+1]){
                          int tmp=ogrNo[j];
                          ogrNo[j]=ogrNo[j+1];
                          ogrNo[j+1]=tmp;

                          tmp=adres[j];
                          adres[j]=adres[j+1];
                          adres[j+1]=tmp;
                      }
                  }
              }
              for(int i=0;i<boyut;i++){
                 fprintf(index,"%4d   %d\n",ogrNo[i],adres[i]);
              }
             fclose(index);
          }
      }
}
void kayitEkle(FILE *veri){
   veri=fopen("veri.bin","ab");
   if(veri==NULL){
      printf("Dosya Acilamadi..");
   }else{
       int boyut;
       printf("Kac Kayit Girilecek ?...");
       scanf("%d",&boyut);
       kayit *kayitlar=malloc(sizeof(kayit)*boyut);
       for(int i=0;i<boyut;i++){
         printf("Ogrencinin;\n");
         printf("numarasini giriniz=");
         scanf("%d",&kayitlar[i].ogrNo);
         fflush(stdin);
         printf("ders kodunu giriniz=");
         scanf("%d",&kayitlar[i].dersKodu);
         fflush(stdin);
         printf("notunu giriniz=");
         scanf("%d",&kayitlar[i].puan);
         fflush(stdin);
         fwrite(&kayitlar[i],sizeof(kayit),1,veri);
         printf("\n");
        }
        fclose(veri);
   }
}

void kayitBul(FILE *index){
       if((index=fopen("index.txt","r"))==NULL){
        printf("Dosya Acilamadi.");
       }else{
       int ogrNo;
       printf("Ogrenci no Giriniz=");
       scanf("%d",&ogrNo);
       int  kontrol=0;
       int *ogrNolari=malloc(sizeof(int)*100);
       int *adresleri=malloc(sizeof(int)*100);
       int boyut=0;
       while(!(feof(index))){
           fscanf(index,"%d",&ogrNolari[boyut]);
           fscanf(index,"%d",&adresleri[boyut]);
           if(ogrNo==ogrNolari[boyut]){
            kontrol++;
           }
           boyut++;
       }
       if(kontrol!=0){
       printf("\nBu numaraya ait tum sonuclar\n");
       printf("ogrNo dersKodu puan\n");
       for(int i=0;i<boyut;i++){
          if(ogrNolari[i]==ogrNo){
            kayit *p=adresleri[i];
            printf("%4d  %4d  %4d\n",p->ogrNo,p->dersKodu,p->puan);
          }
      }
       int basindis=0,sonindis=boyut-1;
       while(sonindis>=basindis){
          int orta=(basindis+sonindis)/2;
          if(ogrNolari[orta]==ogrNo){
            printf("\nBinary Search ile bulunan ogrenci\n");
            printf("ogrNo dersKodu puan\n");
            kayit *p=adresleri[orta];
            printf("%4d  %4d  %4d\n",p->ogrNo,p->dersKodu,p->puan);
            break;
          }else if(ogrNo>ogrNolari[orta]){
              basindis=orta+1;
          }else{
              sonindis=orta-1;
          }
       }

      }
      else{
        printf("\nBu Numaraya Ait Ogrenci Kaydi Bulunmamaktadir.\n");
      }

     fclose(index);
    }

}
void kayitSil(FILE *veri){

      veri=fopen("veri.bin","rb");
      if(veri==NULL){
        printf("Dosya Bulunamadi.(Kayit Yok)\n");
      }else{
        printf("\nKaydini Silmek Istediginiz Ogrenci No Giriniz");
        int ogrNo;
        scanf("%d",&ogrNo);
        fflush(stdin);
        kayit *kayitlar=malloc(100*sizeof(kayit));
        int i=0;
        int kontrol=0;
        while(fread(&kayitlar[i],sizeof(kayit),1,veri)){
            if(kayitlar[i].ogrNo==ogrNo){
                printf("%d %d %d\n",kayitlar[i].ogrNo,kayitlar[i].dersKodu,kayitlar[i].puan);
                printf("silmek icin 1 e basiniz yoksa 0 a basiniz=");
                int secim=0;
                scanf("%d",&secim);
                if(secim==1){
                    i--;
                }
                kontrol++;
            }
            i++;
        }
        if(kontrol==0){
             printf("\nBu Numaraya Ait Ogrenci Kaydi Bulunmamaktadir.\n");
        }
        fclose(veri);
        veri=fopen("veri.bin","wb");
        for(int a=0;a<i;a++){
            fwrite(&kayitlar[a],sizeof(kayit),1,veri);
        }

        fclose(veri);
      }
}
void kayitGuncelle(FILE *veri){
    veri=fopen("veri.bin","rb");
    if(veri==NULL){
        printf("Dosya Bulunamadi.(Kayit Yok)\n");
    }else{
        int ogrNo;
        printf("\nNotunun Guncellenmesini Istediginiz Ogrencinin Numarasini Giriniz=");
        scanf("%d",&ogrNo);
        fflush(stdin);
        kayit *kayitlar=malloc(100*sizeof(kayit));
        int i=0;
        int kontrol=0;
        while(fread(&kayitlar[i],sizeof(kayit),1,veri)){
            if(kayitlar[i].ogrNo==ogrNo){
                printf("%d %d %d\n",kayitlar[i].ogrNo,kayitlar[i].dersKodu,kayitlar[i].puan);
                printf("Yeni not degerini giriniz=");
                scanf("%d",&kayitlar[i].puan);
                kontrol++;
            }
            i++;
        }
        if(kontrol==0){
             printf("\nBu Numaraya Ait Ogrenci Kaydi Bulunmamaktadir.\n");
        }
        fclose(veri);
        veri=fopen("veri.bin","wb");
        for(int a=0;a<i;a++){
            fwrite(&kayitlar[a],sizeof(kayit),1,veri);
        }

        fclose(veri);
    }
}
void veriDosyasiniGoster(FILE *veri){
      if((veri=fopen("veri.bin","rb"))==NULL){
        printf("Veri Dosyasi Bulunamadi.(Kayit Yok)\n");
      }else{
       printf("\nVeri Dosyasi Goruntuleniyor...\n----------------------------\n");
       kayit *kayitlar=malloc(sizeof(kayit)*100);
       printf("ogrNo dersKodu puan\n");
       int a=0;
       while(fread(&kayitlar[a],sizeof(kayit),1,veri)){
         printf("%4d | %4d   |%4d\n",kayitlar[a].ogrNo,kayitlar[a].dersKodu,kayitlar[a].puan);
         a++;
       }

        fclose(veri);
      }
}
void indexDosyasiniGoster(FILE *index){
    index=fopen("index.txt","r");
    if(index==NULL){
        printf("Index Dosyasi Bulunamadi.\n");
    }else{
     printf("\nIndex Dosyasi Goruntuleniyor....\n----------------------");
     printf("\n<OgrNO><Adres>\n");
     char c=fgetc(index);
     while(c!=EOF){
        printf("%c",c);
        c=fgetc(index);
     }
    }
     fclose(index);
}
void indexDosyasiniSil(){
    if(remove("index.txt")==0){
      printf("dosya silindi\n");
    }else{
       printf("dosya silinemedi\n");
    }
}
