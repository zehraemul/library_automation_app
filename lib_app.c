#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
struct Ogrenci{
	char ogrID[9];
	char ad[30];
	char soyad[30];
	int puan;
	struct Ogrenci *next;
	struct Ogrenci *prev;
};
struct Yazar{
	int yazarID;
	char yazarAd[30];
	char yazarSoyad[30];
	struct Yazar *next;
};
struct KitapOrnek{
	char EtiketNo[20];
	char Durum[8];
	struct KitapOrnek *next;
};
struct Kitap{
	char kitapAdi[30];
	char ISBN[13];
	int adet;
	struct Kitap *next;
	struct KitapOrnek *head;
};
struct KitapYazar{
	char ISBN[13];
	int YazarID;
};
struct Tarih{
	int gun:5;
	int ay:4;
	int yil:12;
};
struct KitapOdunc{
	char EtiketNo[20];
	char ogrID[8];
	int islemTipi:1;
	struct Tarih islemTarihi;
};

void yazar_okuma(struct Yazar **head1){
	
	FILE *fp = fopen("Yazarlar.csv", "r");
	if(fp==NULL){
		printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.");
		exit(1);
	}
	char satir[1024];
	while(fgets(satir, 1024, fp)!=NULL){
		struct Yazar *tmp = malloc(sizeof(struct Yazar));
		if(tmp==NULL){
			printf("Su an yer acamiyorum.. :(\n");
			exit(1);
		}
		sscanf(satir, "%d, %29[^,], %29[^,]",&tmp->yazarID, tmp->yazarAd, tmp->yazarSoyad);
		tmp->next=*head1;
		(*head1)=tmp;
	}
	
	fclose(fp);
}

void print_yazar_list(struct Yazar *head) {
  struct Yazar *current = head;

  while (current != NULL) {
    printf("Yazar ID:%d,Yazar Adi:%s,Yazar Soyadi:%s\n", current->yazarID, current->yazarAd, current->yazarSoyad);
    current = current->next;
  }
}

void insert_yazar(const char *filename, struct Yazar **yazar_list) {
  
    int yazarID;
    char yazarAd[30];
    char yazarSoyad[30];
    printf("Yazarin ID numarasini girin: \n");
    scanf("%d", &yazarID);
    printf("Yazarin adini girin: \n");
    scanf("%29s", yazarAd);
    printf("Yazarin soyadini girin: \n");
    scanf("%29s", yazarSoyad);
    struct Yazar *yazar = malloc(sizeof(struct Yazar));
    if (yazar == NULL) {
        printf("Su an yer acamiyorum.. :(\n");
        exit(1);
    }
    yazar->yazarID = yazarID;
    strcpy(yazar->yazarAd, yazarAd);
    strcpy(yazar->yazarSoyad, yazarSoyad);
    yazar->next = *yazar_list;
    *yazar_list = yazar;
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
        exit(1);
    }

    fprintf(fp, "%d,%s,%s", yazarID, yazarAd, yazarSoyad);
    fclose(fp);
}

void delete_yazar(const char *filename, struct Yazar **yazar_list) {
    int yazarID, var=1;
    printf("Yazarin ID numarasini girin: ");
    scanf("%d", &yazarID);

    struct Yazar *yazar = *yazar_list;
    while (yazar != NULL &&var) {
        if (yazar->yazarID == yazarID) {
            var=var-1;
        }
        else {
        	yazar = yazar->next;
		}
      
    }
    if (yazar == NULL) {
	    printf("Aradiginiz yazari bulamadim.. Lutfen tekrar deneyin <3.\n");
        return;
    }
    if (yazar == *yazar_list) {
        *yazar_list = yazar->next;
    } else {
        struct Yazar *prev = *yazar_list;
        while (prev->next != yazar) {
            prev = prev->next;
        }
        prev->next = yazar->next;
    }

    free(yazar);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
        exit(1);
    }
    yazar = *yazar_list;
    while (yazar != NULL) {
        fprintf(fp, "%d,%s,%s", yazar->yazarID, yazar->yazarAd, yazar->yazarSoyad);
        yazar = yazar->next;
    }
    fclose(fp);
}

void updateYazar(struct Yazar **head) {
    int yazarID;	
	struct Yazar *yazar = *head;
    printf("Yazarin ID numarasini girin: \n");
    scanf("%d",&yazarID);
    struct Yazar *current = *head;
    while (current != NULL && current->yazarID != yazarID)
        current = current->next;
        
    if (current == NULL)
        printf("Aradiginiz yazari bulamadim.. Lutfen tekrar deneyin <3.\n");
    else
    {
        printf("Yazarin yeni adini girin: ");
        fflush(stdin);
        scanf("%s", current->yazarAd);
        printf("Yazarin yeni soyadini girin: ");
        fflush(stdin);
        scanf("%s", current->yazarSoyad);
        yazar = *head;
        FILE *fp=fopen("Yazarlar.csv","w");
        if(fp==NULL){
        	printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
        	exit(1);
		}else{
		
			while(yazar!=NULL){
				fprintf(fp,"%d,%s,%s",yazar->yazarID, yazar->yazarAd, yazar->yazarSoyad);
				printf("\n");
				yazar = yazar->next;
			}
			fclose(fp);
		}
    }
}

void goruntule_yazar(struct Yazar **yazar_list){
	int yazarID, var=1;
    printf("Yazarin ID numarasini girin: \n");
    scanf("%d", &yazarID);
    
    struct Yazar *yazar = *yazar_list;
    while (yazar != NULL && var==1){
	
        if (yazar->yazarID == yazarID) {
            var=var-1;
        }
        else {
        	yazar = yazar->next;
		}
      
    }
    if (yazar == NULL) {
	    printf("Aradiginiz yazari bulamadim.. Lutfen tekrar deneyin <3.\n");
        return;;
    }
   
  printf("%d %s %s\n\n ",yazar->yazarID,yazar->yazarAd,yazar->yazarSoyad);
}

void ogrenci_okuma(struct Ogrenci **head2){
	
	
	FILE *fp = fopen("Ogrenciler.csv", "r");
	if(fp==NULL){
		printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
		exit(1);
	}
	char satir[1024];
	while(fgets(satir,1024,fp)!=NULL){
		struct Ogrenci *tmp = malloc(sizeof(struct Ogrenci));
		if(tmp==NULL){
			printf("Su an yer acamiyorum.. :(\n");
			exit(1);
		}
		sscanf(satir, "%9[^,],%29[^,],%29[^,],%d\n",tmp->ogrID,tmp->ad,tmp->soyad,&tmp->puan);
		tmp->next=*head2;
		tmp->prev=NULL;
		if(*head2!=NULL){
			(*head2)->prev=tmp;
		}
		(*head2)=tmp;
	}
	fclose(fp);
}

void print_ogrenci_list(struct Ogrenci *ogrenci_list) {
    struct Ogrenci *current = ogrenci_list;
    while (current != NULL) {
        printf("Ogrenci ID: %s, Ogrencinin ad,: %s, Ogrencinin Soyadi: %s, Ogrencinin puani: %d\n", current->ogrID, current->ad, current->soyad, current->puan);
        current = current->next;
    }
}

void insert_ogrenci(const char *filename, struct Ogrenci **ogrenci_list) {
    char ogrID[8];
    char ad[30];
    char soyad[30];
    int puan;
    printf("Ogrencinin ID numarasini girin: \n");
    fflush(stdin);
    scanf("%8s", ogrID);
    printf("Ogrencinin adini girin: \n ");
    fflush(stdin);
    scanf("%29s", ad);
    printf("Ogrencinin soyadini girin: \n: ");
    fflush(stdin);
    scanf("%29s", soyad);
    printf("Ogrencinin puanini girin: \n");
    fflush(stdin);
    scanf("%d", &puan);
    
    struct Ogrenci *ogrenci = malloc(sizeof(struct Ogrenci));
    if (ogrenci == NULL) {
        printf("Su an yer acamiyorum.. :(\n");
        exit(1);
    }
    strcpy(ogrenci->ogrID, ogrID);
    strcpy(ogrenci->ad, ad);
    strcpy(ogrenci->soyad, soyad);
    ogrenci->puan = puan;
    ogrenci->next = *ogrenci_list;
    ogrenci->prev = NULL;
    if (*ogrenci_list != NULL) {
        (*ogrenci_list)->prev = ogrenci;
    }
    *ogrenci_list = ogrenci;

    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
        exit(1);
    }
    fprintf(fp, "%s, %s, %s, %d\n", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
    fclose(fp);
}

void delete_ogrenci(const char *filename, struct Ogrenci **ogrenci_list) {
    char *ogrID=(char *)malloc(8*sizeof(char));
    int var=1;
    printf("Ogrencinin ID numarasini girin: \n");
    scanf("%8s", ogrID);

    struct Ogrenci *ogrenci = *ogrenci_list;
    while ((ogrenci != NULL)&&var) {
        if (strcmp(ogrenci->ogrID, ogrID) == 0) {
            var=var-1;
        }else{
        	ogrenci = ogrenci->next;
		}
    }
    if (ogrenci == NULL) {
	    printf("Aradiginiz ogrenciyi bulamadim..Lutfen tekrar deneyin <3.\n");
        return;
    }

    if (ogrenci->prev != NULL) {
        ogrenci->prev->next = ogrenci->next;
    }
    if (ogrenci->next != NULL) {
        ogrenci->next->prev = ogrenci->prev;
    }
    if (ogrenci == *ogrenci_list) {
        *ogrenci_list = ogrenci->next;
    }

    free(ogrenci);

   
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
        exit(1);
    }
    ogrenci = *ogrenci_list;
    while (ogrenci != NULL) {
        fprintf(fp, "%s, %s, %s, %d\n", ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
        ogrenci = ogrenci->next;
    }
    fclose(fp);
}

void update_ogrenci(struct Ogrenci **head){
	
	char ogrenciID[10];
	int a=1;
	struct Ogrenci *ogrenci = *head;
	printf("Ogrenci ID girin: ");
	scanf("%s", ogrenciID);
	a=strcmp(ogrenciID,ogrenci->ogrID);
	while(ogrenci!=NULL && a){
		ogrenci=ogrenci->next;
		a=strcmp(ogrenciID,ogrenci->ogrID);
	}
	printf("Ogrencinin adi: %s\n",ogrenci->ad);
	if(ogrenci==NULL){
		printf("Aradiginiz ogrenciyi bulamadim.. Lutfen tekrar deneyin <3.\n");
	}else{
		printf("ogrencinin yeni adini girin: \n");
		fflush(stdin);
		scanf("%s",ogrenci->ad);
		printf("ogrencinin yeni soyadini girin: \n");
		fflush(stdin);
		scanf("%s",ogrenci->soyad);
		printf("ogrencinin yeni puanini girin: \n");
		fflush(stdin);
		scanf("%d",&ogrenci->puan);
		ogrenci = *head;
		FILE *fp = fopen("Ogrenciler.csv", "w");
		if(fp==NULL){
			printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3. \n");
			exit(1);
		}
		
		while(ogrenci!=NULL){
			fprintf(fp, "%s, %s, %s, %d\n",ogrenci->ogrID, ogrenci->ad, ogrenci->soyad, ogrenci->puan);
			ogrenci=ogrenci->next;
		}
		fclose(fp);
	}
}

void goruntule_ogrenci(struct Ogrenci **ogrenci_list){
	
	char ogrID[8];
    int var=1;
    printf("Ogrencinin ID numarasini girin: \n");
    scanf("%8s", ogrID);

    struct Ogrenci *ogrenci = *ogrenci_list;
    while ((ogrenci != NULL)&&var==1) {
        if (strcmp(ogrenci->ogrID, ogrID) == 0) {
            var=var-1;
        }
        else{
        	ogrenci = ogrenci->next;
		}
        
    }
    if (ogrenci == NULL) {
	    printf("Aradiginiz ogrenciyi bulamadim.. Lutfen tekrar deneyin <3. \n");
        return;;
    }
    printf("%s %s %s %d\n", ogrenci->ogrID,ogrenci->ad,ogrenci->soyad,ogrenci->puan);
}

struct Kitap *readKitaplar(char *filename){
  FILE *file = fopen(filename, "r");
  int i;
  if (file == NULL){
    perror("Dosyayi acamiyorum.. Lutfen tekrar deneyin <3. \n");
    exit(1);
  }
  struct Kitap *head = NULL;
  struct Kitap *current = NULL;
  char line[256];
  while (fgets(line, sizeof(line), file)){
    char *kitapAdi = strtok(line, ",");
    char *ISBN = strtok(NULL, ",");
    char *adetStr = strtok(NULL, ",");
    int adet = atoi(adetStr);
    struct Kitap *newKitap = malloc(sizeof(struct Kitap));
    strcpy(newKitap->kitapAdi, kitapAdi);
    strcpy(newKitap->ISBN, ISBN);
    newKitap->adet = adet;
    newKitap->next = NULL;
    newKitap->head = NULL;
    if (head == NULL){
      head = newKitap;
      current = newKitap;
    } else {
      current->next = newKitap;
      current = newKitap;
    }
    for (i = 0; i < adet; i++){
      char EtiketNo[20];
      sprintf(EtiketNo, "%s_%d", ISBN, i+1);
      struct KitapOrnek *newOrnek = malloc(sizeof(struct KitapOrnek));
      strcpy(newOrnek->EtiketNo, EtiketNo);
      strcpy(newOrnek->Durum, "Rafta");
      newOrnek->next = NULL;
      if (newKitap->head == NULL){
        newKitap->head = newOrnek;
      } else {
        struct KitapOrnek *currentOrnek = newKitap->head;
        while (currentOrnek->next != NULL){
          currentOrnek = currentOrnek->next;
        }
        currentOrnek->next = newOrnek;
      }
    }
  }
  fclose(file);
  return head;
}

void printKitaplar(struct Kitap *head){
  struct Kitap *current = head;
  while (current != NULL){
    struct KitapOrnek *currentOrnek = current->head;
    while (currentOrnek != NULL){
      printf("\tEtiket No: %s\n", currentOrnek->EtiketNo);
      printf("\tDurum: %s\n", currentOrnek->Durum);
      currentOrnek = currentOrnek->next;
    }
    current = current->next;
  }
}

void addKitap(struct Kitap **head){
  struct Kitap *newKitap = malloc(sizeof(struct Kitap));
  
  char kitapAdi[30];
  printf("Lutfen kitap adini girin: ");
  scanf("%s", kitapAdi);
  char ISBN[14];
  printf("Lutfen ISBN numarasini girin: ");
  scanf("%s", ISBN);
  int adet;
  printf("Lutfen adetini girin: ");
  scanf("%d", &adet);
  int i;
  strcpy(newKitap->kitapAdi, kitapAdi);
  strcpy(newKitap->ISBN, ISBN);
  newKitap->adet = adet;
  newKitap->next = NULL;
  newKitap->head = NULL;
  for (i = 0; i < adet; i++){
    char EtiketNo[20];
    sprintf(EtiketNo, "%s_%d", ISBN, i+1);
    struct KitapOrnek *newOrnek = malloc(sizeof(struct KitapOrnek));
    strcpy(newOrnek->EtiketNo, EtiketNo);
    strcpy(newOrnek->Durum, "Rafta");
    newOrnek->next = NULL;
    if (newKitap->head == NULL){
      newKitap->head = newOrnek;
    } else {
      struct KitapOrnek *currentOrnek = newKitap->head;
      while (currentOrnek->next != NULL){
        currentOrnek = currentOrnek->next;
      }
      currentOrnek->next = newOrnek;
    }
  }
  if (*head == NULL){
    *head = newKitap;
  } else {
    struct Kitap *current = *head;
    while (current->next != NULL){
      current = current->next;
    }
    current->next = newKitap;
  }
  
  FILE *file = fopen("Kitaplar.csv", "a");
if (file == NULL){
  perror("Dosyayi acamiyorum.. Lutfen tekrar deneyin <3. \n");
  exit(1);
}
fprintf(file, "%s,%s,%d\n", kitapAdi, ISBN, adet);
fclose(file);
}

int kitapYazarOkuma(struct KitapYazar ***head){
	FILE *fp = fopen("KitapYazar.csv", "r");
	if(fp==NULL){
			printf("Dosyayi acamiyorum.. Lutfen tekrar deneyin <3. \n");
			exit(1);
	}
	char satir[1024];
	int count=0;
	(*head)=(struct KitapYazar**)malloc(sizeof(struct KitapYazar*));
	while(fgets(satir,1024,fp)!=NULL){
		(*head)=realloc((*head),sizeof(struct KitapYazar*)*(count+1));
		(*head)[count]=(struct KitapYazar*)malloc(sizeof(struct KitapYazar));
		sscanf(satir, "12[^,],%d\n",(*head)[count]->ISBN,&(*head)[count]->YazarID);
		count++;
	}
	fclose(fp);
	return count;
}

int kitapOduncOkuma(struct KitapOdunc ***head){
	FILE *fp = fopen("KitapOdunc.csv", "r");
	if(fp==NULL){
		printf("Dosyayi acamiyorum.. Lutfen tekrar deneyin <3. \n");
		exit(1);
	}
	
	char satir[1024];
	int count=0;
	(*head)=(struct KitapOdunc**)malloc(sizeof(struct KitapOdunc*));
	int type;
	char *token;
	char *tarih=(char *)malloc(11*sizeof(char));
	while(fgets(satir,1024,fp)!=NULL){
		(*head)=realloc((*head),sizeof(struct KitapOdunc*)*(count+1));
		(*head)[count]=(struct KitapOdunc*)malloc(sizeof(struct KitapOdunc));
		sscanf(satir,"%19[^,],%8[^,], %d, %11[^\n]",(*head)[count]->EtiketNo,(*head)[count]->ogrID,&type,tarih);
		struct Tarih trh;
		token=strtok(tarih,".");
		trh.gun=atoi(token);
		token =strtok(NULL,".");
		trh.ay=atoi(token);
		token =strtok(NULL,".");
		trh.yil=atoi(token);
		(*head)[count]->islemTarihi=trh;
		count++;
	}
	fclose(fp);
	return count;
}

void cezalilari_yazdir(struct Ogrenci **head){
	
	struct Ogrenci *tmp = *head;
	while(tmp!=NULL){
		if(tmp->puan<0){
			printf("\n Ogrencinin ID numarasi: %s\tOgrencinin Adi: %10s\t\tOgrencinin soyadi: %12s\tOgrencinin puani: %d\n", tmp->ogrID, tmp->ad, tmp->soyad, tmp->puan);
		}
		tmp = tmp->next;
	}
}

void delete_kitap(const char *filename, struct Kitap **kitap_list) {
    char *kitapISBN=(char*)malloc(15*sizeof(char));
    int var=1;
    struct Kitap *prev=NULL;
    printf("Kitabin ISBN numarasini girin: \n");
    scanf("%s", kitapISBN);

    struct Kitap *kitap = *kitap_list;
    while ((kitap != NULL)&&var) {
    	//printf("%s",kitap->kitapAdi);
    	//	printf("%s",kitap->ISBN);
        if (!strcmp(kitap->ISBN,kitapISBN)) {
            var=var-1;
        }else{
        	prev = kitap;
        	kitap = kitap->next;
		}
       
    }
    if (kitap == NULL) {
	    printf("Aradiginiz kitabi bulamadim.. Lutfen tekrar deneyin <3.\n");
        return;
    }
	if(kitap==*kitap_list){
		*kitap_list=kitap->next;
	}else{
		
		prev->next=kitap->next;
	}
    free(kitap);   
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Dosyayi acamadim.. Lutfen tekrar deneyin <3.\n");
        exit(1);
    }
    kitap = *kitap_list;
    while (kitap != NULL) {
        fprintf(fp, "%s,%s,%d\n", kitap->kitapAdi,kitap->ISBN,kitap->adet);
        kitap = kitap->next;
    }
    fclose(fp);
}

void goruntule_kitap(struct Kitap **kitap_list){
	char *gkitap = (char*)malloc(30*sizeof(char));
	printf("kitabin adini girin : \n");
	scanf("%[^\n]",gkitap);
	int var=1;
	struct Kitap *kitap =*kitap_list;
	while(kitap!=NULL){
		if(strcmp(gkitap,kitap->kitapAdi)==0){
			var= var-1;
			
		}else{
			kitap=kitap->next;
		}
	}
	if(kitap!=NULL){
		printf("%s %s %d",kitap->ISBN,kitap->kitapAdi,kitap->adet);
		struct KitapOrnek *kornek=kitap->head;
		while(kornek!=NULL){
			//printf(kornekduurm ve kornej etiketno)
			printf("%s %s",kornek->Durum,kornek->EtiketNo);
			kornek=kornek->next;
		}
	}else{
		printf("kita yok");
		return;
	}
}


/*void update_kitap(struct Kitap **kitap_list){
	int var=1;
	char *ikitap = (char *)malloc(14*sizeof(char));
	printf("isbn no gir :");
	scanf("%s",ikitap);
	struct Kitap *ukitap = *kitap_list;
	while(ukitap!=NULL){
		if(strcmp((ikitap,ukitap->ISBN)==0){
			var =var-1;
		}else{
			ukitap=ukitap->next;
		}
		
	}
	if(ukitap!=NULL){
		printf("kitap adi:\n");
		scanf("%[^\n]",ukitap->kitapAdi);
		//adedei
		int i;
		ukitap->head=NULL;
		char *eno = (char *)malloc(20*sizeof(char));
		for(i=0;i<ukitap->adet;i++){
			sprintf(eno,"%s_%d",ukitap->ISBN,i+1);
			struct KitapOrnek *kkornek = malloc(sizeof(struct KitapOrnek));
			strcpy(kkornek->EtiketNo,eno);
			strcpy(kkornek->Durum,"Rafta");
			kkornek->next=NULL;
			if(ukitap->head==NULL){
				ukitap->head=kkornek;
				
			}else{
				struct KitapOrnek *asd = ukitap->head;
				while(asd->next!=NULL){
					asd=asd->next;
				}
				asd->next=kkornek;
			}
		}
	}
}*/

int main(int argc, char *argv[]){
	int secim, secimYazar, secimOgrenci, secimKitap,flag=0,exit;
	struct Yazar *head1 = NULL;
	struct Ogrenci *head2 = NULL;
	struct Kitap *head3 = NULL;
	struct KitapYazar **head4 = NULL;
	struct KitapOdunc **head5 = NULL;
	ogrenci_okuma(&head2);
	yazar_okuma(&head1);
	int kitap_yazar_count = kitapYazarOkuma(&head4);
	int kitap_odunc_count = kitapOduncOkuma(&head5);
	struct Kitap *head = readKitaplar("Kitaplar.csv");
	
	
	printf("\n\n");
	printf("KUTUPHANE OTOMASYONU");
	printf("\n\n");

	while(flag==0){
		printf("1-yazar islemleri \n");
		printf("2-ogrenci islemleri \n");
		printf("3-kitap islemleri \n");
		printf("4-cikis \n");
		printf("\n");
		scanf("%d",&secim);
		printf("\n\n");
		if(secim==1){
			//YAZAR ?SLEMLER?
				printf("1-yazarlari listeleme \n");
				printf("2-yazar ekleme \n");
				printf("3-yazar silme \n");
				printf("4-yazar guncelleme \n");
				printf("5- yazar bilgisi goruntuleme \n");
				printf("\n");
				scanf("%d",&secimYazar);
				printf("\n\n");
				if(secimYazar==1){
					print_yazar_list(head1);
				}
				else if(secimYazar==2){
					printf("ekleme yapilmadan onceki hali: \n");
					print_yazar_list(head1);
					insert_yazar("Yazarlar.csv",&head1);
					printf("eklemek yapildikten sonraki hali: \n");
					print_yazar_list(head1);
					}
				else if(secimYazar==3){
					printf("silme yapilmadan onceki hali: \n");
					printf("\n\n");
					print_yazar_list(head1);
					delete_yazar("Yazarlar.csv",&head1);
					printf("silme yapildikten sonraki hali: \n");
					printf("\n\n");
					print_yazar_list(head1);
				}
				else if(secimYazar==4){
					updateYazar(&head1);
				}
				else if(secimYazar==5){
					goruntule_yazar(&head1);
				}
		}
		else if(secim==2){
				printf("1-ogrencileri listeleme \n");
				printf("2-ogrenci ekleme \n");
				printf("3-ogrenci silme \n");
				printf("4-ogrenci guncelleme \n");
				printf("5-ogrenci bilgisi goruntule \n");
				printf("6-kitap teslim etmemis ogrencileri goruntule \n");
				printf("7-cezali ogrencileri goruntule \n");
				printf("8-kitap odunc al/teslim et \n");
				printf("\n");
				scanf("%d",&secimOgrenci);
				printf("\n\n");
			if(secimOgrenci==1){
				print_ogrenci_list(head2);
			}
			else if(secimOgrenci==2){
				printf("ekleme yapilmadan onceki hali: \n");
				print_ogrenci_list(head2);
				insert_ogrenci("Ogrenciler.csv",&head2);
				printf("eklemek yapildikten sonraki hali: \n");
				print_ogrenci_list(head2);
			}
			else if(secimOgrenci==3){
				printf("silme yapilmadan onceki hali: \n");
				print_ogrenci_list(head2);
				delete_ogrenci("Ogrenciler.csv",&head2);
				printf("silme islemi yapildiktan sonraki hali: \n");
				print_ogrenci_list(head2);
			}
			else if(secimOgrenci==4){
				update_ogrenci(&head2);
			}
			else if(secimOgrenci==5){
				goruntule_ogrenci(&head2);
			}
			else if(secimOgrenci==6){
				printf("Su an uygulamamizda bu hizmet bulunmamaktadir.. Lutfen baska bir islem secin <3. \n");
			}
			else if(secimOgrenci==7){
				cezalilari_yazdir(&head2);
				printf("yapmayi deniyorum ama olmuyor.......\n");
			}
			else if(secimOgrenci==8){
				printf("Su an uygulamamizda bu hizmet bulunmamaktadir.. Lutfen baska bir islem secin <3. \n");
			}
		}
		else if(secim==3){
			// K?TAP ?SLEMLER?
				printf("1-rafdaki kitaplari listeleme \n");
				printf("2-kitap ekleme \n");
				printf("3-kitap silme \n");
				printf("4-kitap bilgisi guncelleme \n");
				printf("5-kitap bilgisi goruntule \n");
				printf("6-zamaninda teslim edilmemis kitaplar \n");
				printf("7-kitap yazar eslestir \n");
				printf("8-kitabin yazarini guncelle \n");
				printf("\n");
				scanf("%d",&secimKitap);
				printf("\n\n");
				
				if(secimKitap==1){
				printKitaplar(head);
				}
				else if(secimKitap==2){
					addKitap(&head);
				}
				else if(secimKitap==3){
					delete_kitap("Kitaplar.csv",&head);
				}
				else if(secimKitap==4){
				//	update_kitap("Kitaplar.csv",&head);
				printf("dogru olmasi gerekiyor fakat hatayi bulamiyorum.. :( \n");
				}
				else if(secimKitap==5){
				//	goruntule_kitap("Kitaplar.csv",&head);
				printf("dogru olmasi gerekyor fakat hatayi bulamiyorum.. :( \n");
				}
				else if(secim==6){
					printf("Su an uygulamamizda bu hizmet bulunmamaktadir.. Lutfen baska bir islem secin <3. \n");
				}
				else if(secim==7){
					printf("Su an uygulamamizda bu hizmet bulunmamaktadir.. Lutfen baska bir islem secin <3. \n");
				}
				else if(secim==8){
					printf("Su an uygulamamizda bu hizmet bulunmamaktadir.. Lutfen baska bir islem secin <3. \n");
				}
		}
		else if(secim==4){
			flag=1;
			printf("programin kapanmasina \n");
			int i;
			for(i=2;i>0;i--){
				printf("%d saniye kaldi\n",i);
				sleep(1);
			}
			printf("ekrani kapatmak icin enter tusuna basin.. ");
	}
}
return 0;
}
