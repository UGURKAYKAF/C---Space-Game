#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

int saha[100][30]={0};
int k,l;
int can;


void gotoxy(short x, short y) { //istediðimiz konuma istediðimizi yazdýrmaya yarýyor
	HANDLE hConsoleOutput;
	COORD Cursor_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_Pos);
}

void cerceve(int x1, int y1, int x2, int y2,int tur){//Çerceve sýnýrý belirliyor
    int i;
    for(i=x1; i<=x2;i++){ //yataydaki sýnýrlarý belirler
        saha[i][y1] = tur;//sol 
        saha[i][y2] = tur;//sað
    }
    for(i=y1; i<=y2;i++){ //dikeydeki sýnýrlarý belirler
        saha[x1][i] = tur; //sol
        saha[x2][i] = tur; //sað
    }
}

void ekrani_bas(){//cerceveyi yazdýrýyor
    int x,y;
    for(x=0;x<100;x++){
        for(y=0;y<30;y++){
        gotoxy(x+1,y+1);
			if(saha[x][y]==2){
               printf("%c",219);
            }
        }
    }
}

void randomAta(int *k,int *l){ //random atamayapýyor
    srand(time(NULL)); 
    *k=3+((rand()%95)*(rand()%95))%95;
    *l=3+rand()%2; 
}

struct players {//oyuncu tutuyor
	char nick[50];
	int puan;
}player[100];


int main(){
	int q;
	system("color 2");//bütün çýktýlarý yesile donduruyor
    int sx=2, sy=20;//platformun baþlangýc konumlarýnýn belirlendiði yer
    int dx=0, dy=0;//deðiþken deðistirme
    unsigned char tus; //tuslarýn tutulduðu yer
    int devam=0;//oyunun sonsuz dongosu
	can=3;//oyuncu caný
    int kisi;//oynayacak kisi yasýyý
    int konum=15;//çýktýnýn yerini belirlemek icin
    int b;//döngü 81.satýr
    int c;//struct 

    
    
    
    printf("\n \n     Hos geldin! \n \n \n \n");
    Sleep(2000);
    printf("              Iyi sanslar.");
    Sleep(1000);
    printf("\n \n \n \n Oyunu baslatmak icin  bir tusa basiniz.");
    getch();
    system("cls");
	
	
    gotoxy(30,13); printf("Kac kisi oynayacaksiniz:");
    scanf("%d",&kisi);
    for(b=0;b<kisi;b++){
    	konum++;
    	//printf("%d",konum);
    	gotoxy(30,konum); printf("%d.Kullanici adini giriniz: ",b+1);
    	scanf("%s",player[b].nick);//44444
	}
	
    system("cls");//ekrandaki tüm çýktýlarý temizliyor
    cerceve(0,0,99,29,2);//cerceve sýnýrlarýný caðýr
	ekrani_bas();//cerceve cýktýsýný caðýr
	randomAta(&k,&l); //meteorun random atamasýný caðýr
	
	c:
    do{//oyunun genel sonsuz döngüsü   
		
    	a:
    	if(kbhit()){    //kbhit tuþa basýlma durumunu alýyor 
            tus=getch();
            if(tus==224){
                tus=getch();
                switch(tus){
                    case 77: dx=1; dy=0; //sol tus
                        break;
                    case 75: dx=-1; dy=0; // sað
                    	break;
                }
            }
    	}
		
    	sx=sx+dx;//platformun deðiþken deðiþtirme yondetim ile hareketinin saðlandýðý yer
    	sy=sy+dy;
		
		if(sx>95){//sýnýrlarýn  aþýlmasý durumunda karþý tarafdan oyun alanýna girilmesini saðlýyor
			sx=2;
		}
		if(sx<2){
			sx=95;
		}
		if(sy>28){
			sy=2;
		}
		if(sy=2){
			sy=28;
		}	
		
		if((k-3==sx || k-2==sx || k-1==sx || k-4==sx || k-5==sx )&& sy==l){//platformla meteor ayný anda carpýsýrsa puan 1 artýyor
        	player[c].puan++;
        	gotoxy(105,3); printf("Puan: %d",player[c].puan);
    	}
    	
    /*
		gotoxy(105,7); printf("k: %d",k);
    	gotoxy(105,8); printf("l: %d",l);
    	gotoxy(105,9); printf("sx: %d",sx);
		gotoxy(105,10); printf("sy: %d",sy);
	*/
			
		if(k-3!=sx && k-2!=sx && k-1!=sx && k-4!=sx && k-5!=sx){//platformla meteor ayný anda carpýsmazsa can 1 eksiliyor
			if(sy==l){
				gotoxy(105,4); printf("Caniniz : %d",can);
				gotoxy(105,4); printf("                ");
				can--;
				gotoxy(105,4); printf("Caniniz : %d",can);	
				
				if(can==0){//eðer can 0 a esit olursa diðer kullanýcýya geçe durumu
				
					for(q=0;q<=kisi;q++){

						can=3;
						system("cls");
						//printf("q = %d",q);
						//printf("kisi : %d",kisi);
						gotoxy(40,13);printf("%s Adli oyuncunun oyunu bitti.",player[b].nick);
						gotoxy(40,14);printf("Puani : %d",player[c].puan);
						gotoxy(40,15);printf("Siradaki oyuncuya gecmek icin bir tusa basiniz. %d",q);
						getch();						
						
						system("cls");
						cerceve(0,0,99,29,2);
						ekrani_bas();
						goto c;//1.oyuncudan sonra oyunu diger kullancýya geçitmek için oyunun baþýna götürür
					}

					system("cls");
					gotoxy(50,13); printf("TEBRIKLER OYUN BITTI !!!");
					for(b=0;b<kisi;b++){
						konum++;
						gotoxy(50,konum); printf("%s Puani : %d",player[b].nick,player[c].puan);
					}
					getch();//klavye den bir tus bekliyor
				}
			}	
		}

		b:
		gotoxy(sx,sy); printf("*****");	//platformun yazdýrýlýyor
		Sleep(50);//platform hýzý
		gotoxy(sx,sy); printf("     ");//platformun sil ekle mantýgý

	for(l;l<=29;l++){//meteorun yukardan aþagý hareketi
	
		gotoxy(k,l); printf("%c",248);//meteor yadýrýyor
		Sleep(150);	//meteor hýzý
		gotoxy(k,l); printf(" ");//meteor sil ekle
		
		if(l==29){	//meteor en asagý geldiginde random atamasýný yapýyor
			k=4+rand() % 95;		
			randomAta(&k,&l);
			goto b;	//192.satýra götürü oyunu
		}
		
		if(l++){
			goto a;	//100,satýra götürüyor	
		}			
	}
	
	}while(devam==0);
    	   
    getch();
    return 0 ;
}
