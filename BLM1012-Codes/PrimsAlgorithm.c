#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <sys/time.h>

double prim(int [][20],int);
int valueMST(int [],bool [],int);
void printM(int [][20],int);
void readM(int [][20],int);


int main(){
	int i,j,secim=1,count=0,size,dizi[20][20],yildiz[20],yildiz1[20];
	double zamanlar[20];
	printf(" Prim Algoritmasi");
	while(secim==1){
		printf("\n\n\t%d. Agac\n", count+1);
		printf("\n\t\tAgacta bulunan nokta sayisi = ");
		scanf("%d",&size);yildiz1[count]=size*size;// O(n*2) hesapl�yor
		readM(dizi,size);system("cls");
		printf("\n %d.Agacin matris hali...\n\n",count+1);
		printM(dizi, size);
		zamanlar[count] = prim(dizi,size);// d�nd�r�len ger�ek zaman� dizide tutuyor
		printf("\n %d. Islem boyunca gecen zaman = %lf saniye\n", count+1, zamanlar[count]);// zaman� yazd�r�yor
		yildiz[count] = (int)(zamanlar[count] * 100000);// zaman� y�ld�za �eviriyor
		printf("\n 1- Yeni Agac Girisi...\n\n 2- Cikis...\n ");scanf(" %d", &secim);system("cls");
		count++;
	}
	for(i=0;i<count;i++){
		printf("\n\t\t%d. Agac", i+1);		
		printf("\n\n  O(n^2), Islem Sayisina Bagli Zamanin Yildiz Diyagrami...\n   ");
		for(j=0;j<yildiz1[i];j++){
			printf("*");
		}printf("\n  Yildiz Sayisi = %d",yildiz1[i]);
		printf("\n");
		printf("\n  Gercek Zaman = %lf saniye",zamanlar[i]);	
		printf("\n  Gercek Zamana Bagli Yildiz Diyagrami...\n   ");		
		for(j=0;j<yildiz[i];j++){
			printf("*");
		}printf("\n  Yildiz Sayisi = %d",yildiz[i]);
	}

	return 0;
}

double prim(int dizi[20][20], int size){
	int i,j,edge,path;
	int deger[20];// d���mler aras�ndaki k�sa mesafeyi tutacak
	int former[20];// �nceki d���mleri tutacak
	bool visited[20];
	struct timeval start,stop;
	do{
		gettimeofday(&start,NULL);// ger�ek zaman sayac�n� ba�lat�yor
		for(i=0;i<size;i++){
			visited[i] = false;// d���mlerin hi�biri ziyaret edilmedi
			deger[i] = INT_MAX;// t�m d���mlerin b�y�kl���
		}
		deger[0] = 0;// ba�lad���m�z d���m
		former[0] = -1;// baslad���m�z d�g�m�n atas� yok
		for(path=0;path<size-1;path++){
			edge = valueMST(deger,visited,size);// en k�sa kenar� d�nd�r�yor
			visited[edge] = true;// art�k ziyaret edilmi� oldu	
			for(j=0; j<size; j++){		
				if(dizi[edge][j]!=0 && visited[j] == false && dizi[edge][j] < deger[j]){// d���m�n varl���n�, ziyaret edilmemi� olmas�n�, yolun daha k�sa olmas�n� kontrol ediyor
					deger[j] = dizi[edge][j];// de�eri tutuyor
					former[j] = edge;// eski d���m� kaydediyor
				}
			}
		}
		gettimeofday(&stop,NULL);// ger�ek zaman sayac�n� durduruyor
	}while(((double)(stop.tv_usec-start.tv_usec)/1000000 + (double)(stop.tv_sec-start.tv_sec))==0.0);// ger�ek zaman 0 ��kmas�n diye
	int sum=0;
	printf("\n\n\n Ilk Dugum\tSon Dugum\tUzaklik");
	for(i=1;i<size;i++){
		printf("\n\n     %d\t\t    %d\t\t   %d\n",former[i],i,deger[i]);// ilk ve gidilen d���m�, uzakl��� yazd�r�yor
	}
	for(i=1;i<size;i++){
		sum += deger[i];// toplam uzakl��� hesapl�yor
	}
	printf("\n Tum dugumlere ulasilabilecek en az uzaklik = %d\n",sum);// toplam uzakl��� yazd�r�yor
	return (double)(stop.tv_usec-start.tv_usec) / 1000000 + (double)(stop.tv_sec-start.tv_sec);// zaman� d�nd�r�yor
}

int valueMST(int deger[],bool visited[],int size){
	int i,minIndex;
	int min = INT_MAX;
	for(i=0; i<size; i++){
		if(visited[i] == false && deger[i] < min){//d���m ziyaret edilmemi� ve min de�erden k���k olacak
			min = deger[i];
			minIndex = i;
		}
	}

	return minIndex;//en k�sa kenar�n indexi d�nd�r�yor
}

void printM(int dizi[20][20],int n){
	int i,j;printf(" \\");
	for(j=0;j<n;j++){
		printf("\t %d",j+1);
	}
	for(i=0;i<n;i++){
		printf("\n\n\n %d",i+1);
		for(j=0;j<n;j++){
			printf("\t %d",dizi[i][j]);
		}
	}

}

void readM(int dizi[20][20],int n){
	int i,j;
	printf("\n\t Matrisin elemanlari...\n");
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			if(i==j){
				dizi[i][j] = 0;
				printf("\t\tM[%d][%d] = %d\n",i,j,dizi[i][j]);
			}else{
				printf("\t\tM[%d][%d] = ",i,j);
				scanf("%d",&dizi[i][j]);
			}
		}
		printf("\n");
	}

}
