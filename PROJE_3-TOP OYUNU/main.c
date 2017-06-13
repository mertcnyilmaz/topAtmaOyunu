/* Volkan Uður ARSLAN 130202012 - Mertcan Yýlmaz 130202056   Top Atma Oyunu */
#include <allegro.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>

void Baslat() {
int depth, res;
allegro_init();
depth = desktop_color_depth();
if (depth == 0) depth = 32;
set_color_depth(depth);
res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, 800, 500, 0, 0);
if (res != 0) {
allegro_message(allegro_error);
exit(-1);
}
install_timer();
install_keyboard();
install_mouse();
install_sound(DIGI_AUTODETECT,MIDI_AUTODETECT,"A");

}
void Bitir() 
{
clear_keybuf();
}

volatile int timer;
void incrementa_timer() { timer++; }
END_OF_FUNCTION(incrementa_timer)

int main() 
{
	Baslat();
	
	int x=0,y=0;
	int x1=5,y1=400; 
	int random1 = 0,random2 = 0,random3 = 0, sayi1 = 0,sayi2 = 0;
	int daire=0,kat=0,bina=0,kontrol_kat=0;
	int adet =1,adres = 0,adres1 = 0,ayni = -1,ayni2 = -1;
	int ruzgarSid = 0;
	int gucy1 = 78, gucy2 = 78, yonx1 = 93 ,yonx2 = 713;
	int	tek = 1 ;
	int hak = 1;
	int sinirx = 0, siniry= 0, sinirx1 = 0, siniry1 = 0;	
	int binsay = 0,binsay2 = 0;	
	float deltat = 0.1;
	float cekim = 9.8;
	int kural = 0;
	int Siralama[3];
	int sifirlama;
	int Yuksekpuan = 0;
	int Vurulma1 = 0, Vurulma2 = 0;
	int sira=0,kati=0,sirasi=0;
	
	for (sifirlama = 0; sifirlama<3 ;sifirlama++)	
	{
		Siralama[sifirlama] = 0;
	}
	
	struct Oyuncu
	{
		int xkon,ykon;
		int puani;
		int rengi;
		float yonu ;
		float gucu;
		float gucvx,gucvy;
	} Oyuncular [2];
	Oyuncular[0].puani = 0;
	Oyuncular[1].puani = 0;
	Oyuncular[0].gucu = 1;
	Oyuncular[0].yonu = 1;
	Oyuncular[1].gucu = 1;
	Oyuncular[1].yonu = 1;
	
	
	
	struct Binacik
	{
		int xkon;
		int ykon;
		int katcik;
	} Binalar[15];
	
	install_timer();
	
	LOCK_FUNCTION(incrementa_timer);
	LOCK_VARIABLE(timer);
	install_int_ex(incrementa_timer,SECS_TO_TIMER(1));
	
	srand (time(NULL));
	
	SAMPLE *kirilmases = load_sample("kirilmases.wav");					/*Sesleri Yükleme*/
	SAMPLE *vurmases = load_sample("vurmasesi.wav");
	SAMPLE *atmases = load_sample("atmasesi.wav");
	SAMPLE *arkases = load_sample("arkases.wav");
	BITMAP *oyunresim = create_bitmap(800,500);
	BITMAP *araresim = create_bitmap(800,500);							/*Resimleri Yükleme */
	BITMAP *Menuresim = load_bitmap("Menures.bmp",NULL);
	BITMAP *Sirares = load_bitmap("Siralamares.bmp",NULL);
	BITMAP *Lakapres = load_bitmap("Oyuncuad.bmp",NULL);
	BITMAP *Oyunresim = load_bitmap("Oyunres.bmp",NULL);
	BITMAP *t1 = load_bitmap("Oyna.bmp",NULL);
	BITMAP *t2 = load_bitmap("Siralama.bmp",NULL);
	BITMAP *t3 = load_bitmap("Cikis.bmp",NULL);
	BITMAP *t4 = load_bitmap("Oyna2.bmp",NULL);
	BITMAP *t5 = load_bitmap("Siralama2.bmp",NULL);
	BITMAP *t6 = load_bitmap("Cikis2.bmp",NULL);
	BITMAP *t7 = load_bitmap("Geri.bmp",NULL);
	BITMAP *t8 = load_bitmap("Geri2.bmp",NULL);
	BITMAP *t9 = load_bitmap("Geri3.bmp",NULL);
	BITMAP *t10 = load_bitmap("Geri4.bmp",NULL);
	BITMAP *t11 = load_bitmap("ileri.bmp",NULL);
	BITMAP *t12 = load_bitmap("ileri2.bmp",NULL);
	BITMAP *t13 = load_bitmap("Menu1.bmp",NULL);
	BITMAP *t14 = load_bitmap("Menu2.bmp",NULL);
	BITMAP *k1 = load_bitmap("Karakter1.2.bmp",NULL);
	BITMAP *k2 = load_bitmap("Karakter2.2.bmp",NULL);
	BITMAP *k3 = load_bitmap("Karakter3.2.bmp",NULL);
	BITMAP *k4 = load_bitmap("Karakter4.2.bmp",NULL);
	BITMAP *k5 = load_bitmap("Karakter5.2.bmp",NULL);
	BITMAP *k6 = load_bitmap("Karakter1.bmp",NULL);
	BITMAP *k7 = load_bitmap("Karakter2.bmp",NULL);
	BITMAP *k8 = load_bitmap("Karakter3.bmp",NULL);
	BITMAP *k9 = load_bitmap("Karakter4.bmp",NULL);
	BITMAP *k10 = load_bitmap("Karakter5.bmp",NULL);
	BITMAP *b1 = load_bitmap("Duvar.bmp",NULL);
	BITMAP *b2 = load_bitmap("Kapi.bmp",NULL);
	BITMAP *b3 = load_bitmap("Pencere.bmp",NULL);
	BITMAP *b4 = load_bitmap("kat.bmp",NULL);
	BITMAP *b5 = load_bitmap("Pencere2.bmp",NULL);
	BITMAP *g1 = load_bitmap("Gamer1.bmp",NULL);
	BITMAP *g2 = load_bitmap("Gamer2.bmp",NULL);
	BITMAP *g3 = load_bitmap("Gamer3.bmp",NULL);
	BITMAP *g4 = load_bitmap("Gamer4.bmp",NULL);
	BITMAP *g5 = load_bitmap("Gamer5.bmp",NULL);
	BITMAP *d1 = load_bitmap("kan.bmp",NULL);

	show_mouse(screen);
	while (!key[KEY_ESC]) 
	{
		Menu :
		blit (Menuresim,araresim,0,0,0,0,800,500);																	//Ara resim yükleniyor ki ekran yenileme sorunu oluþmasýn.
		
		blit (t1,araresim,0,0,50,100,100,50);
		blit (t2,araresim,0,0,300,100,200,50);																		//Tuslar Eklendi.
		blit (t3,araresim,0,0,650,100,100,50);
		textout_ex(araresim,font,"alpha.wallhaven.cc",0,490,makecol(255,255,255),-1);								//Arka resmin nereden alýndýðý.
		textout_ex(araresim,font,"Version Alpha 1.0",655,490,makecol(255,255,255),-1);
		textout_ex(araresim,font,"Deorro - Five Hours",330,490,makecol(255,255,255),-1);								
		play_sample(arkases,1,128,1000,0);
		{
		
			if(mouse_x>50 && mouse_x<150 && mouse_y>100 && mouse_y<150)													//Oyna tusu.
			{	
				blit (t4,araresim,0,0,50,100,100,50);
				if (mouse_b & 1)
				{
					while (!key[KEY_BACKSPACE] && !key[KEY_ESC])												//Oyna2 Menüsü.
					{
						clear_to_color(araresim,makecol(0,0,0));
						blit (Lakapres,araresim,0,0,0,0,800,500);
						blit (t11,araresim,0,0,600,375,150,75);
				
						textout_ex(araresim,font,"alpha.wallhaven.cc",0,490,makecol(255,255,255),-1);
						textout_ex(araresim,font,"Version Alpha 1.0",655,490,makecol(255,255,255),-1);
						textout_ex(araresim,font,"1. Oyuncu Karakterini Secsin :",25,25,makecol(255,255,255),-1);
			
						textout_ex(araresim,font,"2. Oyuncu Karakterini Secsin :",25,200,makecol(255,255,255),-1);
				
						blit (k1,araresim,0,0,50,50,100,100);																//Karakter Resimleri Yüklendi.
						blit (k2,araresim,0,0,160,50,100,100);
						blit (k3,araresim,0,0,270,50,100,100);
						blit (k4,araresim,0,0,380,50,100,100);
						blit (k5,araresim,0,0,490,50,100,100);
				
						blit (k1,araresim,0,0,50,225,100,100);
						blit (k2,araresim,0,0,160,225,100,100);
						blit (k3,araresim,0,0,270,225,100,100);
						blit (k4,araresim,0,0,380,225,100,100);
						blit (k5,araresim,0,0,490,225,100,100);
						if (mouse_x>50 && mouse_x<150 && mouse_y>50 && mouse_y<150)										//Üstüne Gelince Canlandý.
						{
							blit (k6,araresim,0,0,50,50,100,100); //1
							if (mouse_b & 1) 
							{
								Oyuncular[0].rengi = 1;
							}
						}
						if (mouse_x>160 && mouse_x<260 && mouse_y>50 && mouse_y<150)
						{
							blit (k7,araresim,0,0,160,50,100,100); 	//2
							if (mouse_b & 1) 
							{
								Oyuncular[0].rengi = 2;
							}
						}
						if (mouse_x>270 && mouse_x<370 && mouse_y>50 && mouse_y<150)
						{
							blit (k8,araresim,0,0,270,50,100,100);	//3
							if (mouse_b & 1) 
							{
								Oyuncular[0].rengi = 3;
							}
						}
						if (mouse_x>380 && mouse_x<480 && mouse_y>50 && mouse_y<150)
						{
							blit (k9,araresim,0,0,380,50,100,100);	//4
							if (mouse_b & 1) 
							{
								Oyuncular[0].rengi = 4;
							}
						}
						if (mouse_x>490 && mouse_x<590 && mouse_y>50 && mouse_y<150)
						{
							blit (k10,araresim,0,0,490,50,100,100);	//5
							if (mouse_b & 1) 
							{
								Oyuncular[0].rengi = 5;
							}
						}
						if (mouse_x>50 && mouse_x<150 && mouse_y>225 && mouse_y<325)
						{
							blit (k6,araresim,0,0,50,225,100,100); //1
							if (mouse_b & 1) 
							{
								Oyuncular[1].rengi = 1;
							}
						}
						if (mouse_x>160 && mouse_x<260 && mouse_y>225 && mouse_y<325)
						{
							blit (k7,araresim,0,0,160,225,100,100); 	//2
							if (mouse_b & 1) 
							{
								Oyuncular[1].rengi = 2;
							}
						}
						if (mouse_x>270 && mouse_x<370 && mouse_y>225 && mouse_y<325)
						{
							blit (k8,araresim,0,0,270,225,100,100);	//3
							if (mouse_b & 1) 
							{
								Oyuncular[1].rengi = 3;
							}
						}
						if (mouse_x>380 && mouse_x<480 && mouse_y>225 && mouse_y<325)
						{
							blit (k9,araresim,0,0,380,225,100,100);	//4
							if (mouse_b & 1) 
							{
								Oyuncular[1].rengi = 4;
							}
						}
						if (mouse_x>490 && mouse_x<590 && mouse_y>225 && mouse_y<325)
						{
							blit (k10,araresim,0,0,490,225,100,100);	//5
							if (mouse_b & 1) 
							{
								Oyuncular[1].rengi = 5;
							}
						}
				
						if (mouse_x>600 && mouse_x<750 && mouse_y>375 && mouse_y<450)
						{
							blit (t12,araresim,0,0,600,375,150,75);	//ileri
							if (mouse_b & 2) 
							{
								while (!key[KEY_BACKSPACE] && !key[KEY_ESC])												//Kurallar Menü
								{
									clear_to_color(araresim,makecol(0,0,0));
									blit (Lakapres,araresim,0,0,0,0,800,500);
									blit (t11,araresim,0,0,600,375,150,75);
									textout_ex(araresim,font,"alpha.wallhaven.cc",0,490,makecol(255,255,255),-1);
									textout_ex(araresim,font,"KURALLAR",300,40,makecol(255,0,0),-1);
									textout_ex(araresim,font,"1. Oyuncu Topun Yonunu W - S , Siddetini ise A - D Ile Ayarlar.",50,70,makecol(255,255,255),-1);
									textout_ex(araresim,font,"2. Oyuncu Topun Yonunu Yukari - Asagi Oklarla , Siddetini Ise Saga - Sola Oklarla Ile Ayarlar.",50,90,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Topun Atisini Yapmadan Once Yukarida Gosterilen Ruzgar Yonunu Ve Siddetine Bakabilirsiniz.",50,110,makecol(255,255,255),-1);
									textout_ex(araresim,font,"1. Oyuncu Topu G , 2. Oyuncu L Ile Atabilir.",50,130,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Her Oyuncunun Topu Atmak Icin 20 Saniyesi Vardir.",50,150,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Her Oyuncunun Toplamda 3 Top Atma Hakki vardir.",50,170,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Rakibine Topu Isabet Ettiren Oyuncu Puan Kazanir.",50,190,makecol(255,255,255),-1);
									textout_ex(araresim,font,"En Sondaki Skor Hesaplamasi Atis Yapilan Sureye ve Isabete Gore Belirlenir.",50,210,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Oyunu Durdurmak Icin P ye, Devam Etmek Icin O ya Basabilirsiniz.",50,230,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Bosluk Tusuna Basarak Haritayi Yenileyebilirsiniz.",50,250,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Iyi Oyunlar!",50,270,makecol(255,255,255),-1);
									textout_ex(araresim,font,"Version Alpha 1.0",655,490,makecol(255,255,255),-1);
									
									if (mouse_x>600 && mouse_x<750 && mouse_y>375 && mouse_y<450)										//Oyun Menü1 den Menü ye Dönüs saðlar.
									{
										blit (t12,araresim,0,0,600,375,150,75);
										if (mouse_b & 1) 
										{	
										while (!key[KEY_BACKSPACE] && !key[KEY_ESC])
											{
												clear_to_color(araresim,makecol(0,0,0));
												clear_to_color(screen,makecol(0,0,0));
												blit (Oyunresim,araresim,0,0,0,0,800,500);
												textout_ex(araresim,font,"alpha.wallhaven.cc",0,490,makecol(0,0,0),-1);					
												textout_ex(araresim,font,"Version Alpha 1.0",655,490,makecol(0,0,0),-1);
												
												ruzgarSid = rand()%21-10;
													
												rect(araresim,35,20,65,80,makecol(0,0,0));
												rect(araresim,36,21,66,81,makecol(0,0,0));
												rect(araresim,90,50,150,80,makecol(0,0,0));
												rect(araresim,91,51,151,81,makecol(0,0,0));
								
												rect(araresim,655,20,685,80,makecol(0,0,0));
												rect(araresim,656,21,686,81,makecol(0,0,0));
												rect(araresim,710,50,770,80,makecol(0,0,0));
												rect(araresim,711,51,771,81,makecol(0,0,0));
															
												textout_ex(araresim,font,"GUC      YON       SURE",40,90,makecol(0,0,0),-1);
												textout_ex(araresim,font,"GUC      YON",660,90,makecol(0,0,0),-1);
												textout_ex(araresim,font,"SURE",590,90,makecol(0,0,0),-1);
												timer = 0;	
									
												line(araresim,325,50,475,50,makecol(0,0,0));
												line(araresim,325,51,475,51,makecol(0,0,0));
															
												if(ruzgarSid<0)
											    triangle(araresim,325,40,325,60,315,50,makecol(0,0,0));
												else if(ruzgarSid>0)
									 	        triangle(araresim,475,40,475,60,485,50,makecol(0,0,0));
															
												textprintf_ex(araresim,font,397,35,makecol(255,255,255),-1,"%d",ruzgarSid);			//Rüzgar
												textout_ex(araresim,font," RUZGAR VE SiDDETi",325,70,makecol(0,0,0),-1);	
								                            
												x1 = 0;
												bina = 0;
												for (bina; bina<15; bina++)
												{
										            kat = 0;
													Binalar[bina].katcik = rand() % 5 + 1;
													y1 = 450 ;
																
													for (kat; kat<=Binalar[bina].katcik; kat++)
													{
																													//Bina Oluþturma Döngüleri.	
														if (x1 > 750)
														{
														 	break;
                                                        }
														if (y1==450)
														{
															blit (b1,araresim,0,0,x1,y1,50,50);
															y1 = y1 - 50;
														}
														else 
														{
															blit (b3,araresim,0,0,x1,y1,50,50);
															Binalar[bina].xkon = x1 ;
															Binalar[bina].ykon = y1;
															y1 = y1 - 50;
														}
													}
													x1=x1+50;
													blit (araresim,screen,0,0,0,0,800,500);
												}
															
												adres = rand() % 8;
												switch (Oyuncular[0].rengi)
												{
													case 1 : blit (g1,araresim,0,0,Binalar[adres].xkon,Binalar[adres].ykon-50,25,50); break;
													case 2 : blit (g2,araresim,0,0,Binalar[adres].xkon,Binalar[adres].ykon-50,25,50); break;
													case 3 : blit (g3,araresim,0,0,Binalar[adres].xkon,Binalar[adres].ykon-50,25,50); break;			//1. Adamý Oluþturma
													case 4 : blit (g4,araresim,0,0,Binalar[adres].xkon,Binalar[adres].ykon-50,25,50); break;
													case 5 : blit (g5,araresim,0,0,Binalar[adres].xkon,Binalar[adres].ykon-50,25,50); break;
													default : blit (g1,araresim,0,0,Binalar[adres].xkon,Binalar[adres].ykon-50,25,50); break;
												}
												Oyuncular[0].xkon = Binalar[adres].xkon;
												Oyuncular[0].ykon = Binalar[adres].ykon-50;
															
												adres1 = rand()	% 7	+ 8;
												switch (Oyuncular[1].rengi)
												{
													case 1 : blit (g1,araresim,0,0,Binalar[adres1].xkon+20,Binalar[adres1].ykon-50,25,50); break;
													case 2 : blit (g2,araresim,0,0,Binalar[adres1].xkon+20,Binalar[adres1].ykon-50,25,50); break;
													case 3 : blit (g3,araresim,0,0,Binalar[adres1].xkon+20,Binalar[adres1].ykon-50,25,50); break;			//2. Adamý Oluþturma
													case 4 : blit (g4,araresim,0,0,Binalar[adres1].xkon+20,Binalar[adres1].ykon-50,25,50); break;
													case 5 : blit (g5,araresim,0,0,Binalar[adres1].xkon+20,Binalar[adres1].ykon-50,25,50); break;
													default : blit (g1,araresim,0,0,Binalar[adres1].xkon+20,Binalar[adres1].ykon-50,25,50); break;
												}
																				    
												Oyuncular[1].xkon = Binalar[adres1].xkon+20;
												Oyuncular[1].ykon = Binalar[adres1].ykon-50;
															
																
												blit(araresim,screen,0,0,0,0,800,500);									
												blit(araresim,oyunresim,0,0,0,0,800,500);
												hak = 1;
												kural =0;
												Oyuncular[0].puani = 0;
												Oyuncular[1].puani = 0;
												while (!key[KEY_SPACE] )
												{
													if (kural < 6)
													{
														
														Oyuncular[0].gucvx=0;
														Oyuncular[0].gucvy=0;
														Oyuncular[1].gucvx=0;
														Oyuncular[1].gucvy=0;
														textout_ex(oyunresim,font,"alpha.wallhaven.cc",0,490,makecol(0,0,0),-1);					
														textout_ex(oyunresim,font,"Version Alpha 1.0",655,490,makecol(0,0,0),-1);
														
														rectfill(oyunresim,37,gucy1,64,79,makecol(255,255,255));
														rectfill(oyunresim,92,52,yonx1,79,makecol(255,255,255));
														rectfill(oyunresim,657,gucy2,684,79,makecol(255,255,255));
														rectfill(oyunresim,712,52,yonx2,79,makecol(255,255,255));	
														if (key[KEY_UP])								///Guc Ve Yon Ayarlama
														{
															if(Oyuncular[1].gucu>0 && Oyuncular[1].gucu<171)
															{
																gucy2 = gucy2-3;
																Oyuncular[1].gucu = Oyuncular[1].gucu+9;
															}
																	
														}
														else if(key[KEY_DOWN])
														{
															if(Oyuncular[1].gucu>0 && Oyuncular[1].gucu<171)
															{
																gucy2 = gucy2+3;
																Oyuncular[1].gucu = Oyuncular[1].gucu-9;	
															}
																		
														}	
														if (key[KEY_RIGHT])
														{
															if(Oyuncular[1].yonu>0 && Oyuncular[1].yonu<57)
															{
																yonx2++;
																Oyuncular[1].yonu++;	
															}
														}
														else if(key[KEY_LEFT])
														{
															if(Oyuncular[1].yonu>0 && Oyuncular[1].yonu<57)
															{
																yonx2--;
																Oyuncular[1].yonu--;
															}
														}
														if (key[KEY_W])
														{
															if(Oyuncular[0].gucu>0 && Oyuncular[0].gucu<171)
															{
																 gucy1= gucy1-3;
																 Oyuncular[0].gucu = Oyuncular[0].gucu+9;
															}
														}
														else if(key[KEY_S])
														{
															if(Oyuncular[0].gucu>0 && Oyuncular[0].gucu<171)
															{
																gucy1 = gucy1+3;
																Oyuncular[0].gucu = Oyuncular[0].gucu-9;
															}
															
														}
														if (key[KEY_D])
														{
															if(Oyuncular[0].yonu>0 && Oyuncular[0].yonu<57)
															{
															yonx1++;
															Oyuncular[0].yonu++;
															}
																
														}
														else if(key[KEY_A])
														{
															if(Oyuncular[0].yonu>0 && Oyuncular[0].yonu<57)
															{
																yonx1--;
																Oyuncular[0].yonu--;
															}
																	
														}
																
														sinirx = Oyuncular[0].xkon+26;
														siniry = Oyuncular[0].ykon+46;
														
														sinirx1 = Oyuncular[1].xkon-4;
														siniry1 = Oyuncular[1].ykon+46;
																	
														if (key[KEY_P])
														{
															while ( !key[KEY_O] )
															{
															}
														}
																														
														blit(oyunresim,screen,0,0,0,0,800,500);
															
														if  (hak == 1) 
														{
															circlefill(araresim,sinirx,siniry,2,makecol(255,255,255));
															blit (araresim,oyunresim,0,0,0,0,800,500);
															textprintf_ex(oyunresim,font,200,70,makecol(0,0,0),-1,"%d",timer);		//Sure
															if (timer > 19)
															{
																hak = 2;
																timer = 0;
																kural++;
															} 
																		
															if (key[KEY_G])
															{
																Oyuncular[0].gucvx = Oyuncular[0].gucu*cos((-Oyuncular[0].yonu)/60) + ruzgarSid;
																Oyuncular[0].gucvy = Oyuncular[0].gucu*sin((-Oyuncular[0].yonu)/60);
																blit(araresim,oyunresim,0,0,0,0,800,500);
																play_sample(atmases,255,128,1000,0);
																while (((sinirx> 0) && (sinirx < 800)) && ((siniry < 500) && (siniry > 0)))
																{
																	blit(oyunresim,screen,0,0,0,0,800,500);
																	circlefill(oyunresim,sinirx+10,siniry-10,2,makecol(255,255,255));
																	Oyuncular[0].gucvy = Oyuncular[0].gucvy + cekim*deltat;
																	sinirx = sinirx + (Oyuncular[0].gucvx*deltat);
																	siniry = siniry + (Oyuncular[0].gucvy*deltat) + 0.5 * cekim *(deltat*deltat);
																	rest (30);
																	if ( ((sinirx+10 > Oyuncular[1].xkon) && (sinirx+10 < Oyuncular[1].xkon+25)) && (siniry-10 > Oyuncular[1].ykon) && (siniry-10 > Oyuncular[1].ykon-50) )
																	{
																		Vurulma1++;
																		Oyuncular[0].puani += 10 ;
																		play_sample(vurmases,255,128,1000,0);
																		switch (timer)
																		{
																			case 1 : Oyuncular[0].puani += 200 ; break;
																			case 2 : Oyuncular[0].puani += 190 ; break;
																			case 3 : Oyuncular[0].puani += 180 ; break;
																			case 4 : Oyuncular[0].puani += 170 ; break;			//Vurulma + Puan
																			case 5 : Oyuncular[0].puani += 160 ; break;
																			case 6 : Oyuncular[0].puani += 150 ; break;
																			case 7 : Oyuncular[0].puani += 140 ; break;
																			case 8 : Oyuncular[0].puani += 130 ; break;
																			case 9 : Oyuncular[0].puani += 120 ; break;
																			case 10 : Oyuncular[0].puani += 110 ; break;
																			case 11 : Oyuncular[0].puani += 100 ; break;
																			case 12 : Oyuncular[0].puani += 90 ; break;
																			case 13 : Oyuncular[0].puani += 80 ; break;
																			case 14 : Oyuncular[0].puani += 70 ; break;
																			case 15 : Oyuncular[0].puani += 60 ; break;
																			case 16 : Oyuncular[0].puani += 50 ; break;
																			case 17 : Oyuncular[0].puani += 40 ; break;
																			case 18 : Oyuncular[0].puani += 30 ; break;
																			case 19 : Oyuncular[0].puani += 20 ; break;
																			case 20 : Oyuncular[0].puani += 10 ; break;
																			default : Oyuncular[0].puani += 5 ; break;
																		}
																		switch (Vurulma1)
																		{
																			case 1 : textout_ex(araresim,font,"+",Oyuncular[1].xkon+5,Oyuncular[1].ykon-10,makecol(255,0,0),-1); break;
																			case 2 : textout_ex(araresim,font,"++",Oyuncular[1].xkon+5,Oyuncular[1].ykon-10,makecol(255,0,0),-1); break;
																			case 3 : textout_ex(araresim,font,"+++",Oyuncular[1].xkon+5,Oyuncular[1].ykon-10,makecol(255,0,0),-1); break;
																			default : textout_ex(araresim,font,"",Oyuncular[1].xkon+10,Oyuncular[1].ykon-10,makecol(255,0,0),-1); break;
																		}
																		
																		goto BURAYAGEL;
																	}
																	else 
																	{
																		for (binsay = 0; binsay<15 ; binsay++)
																		{
																			if ( (sinirx >= Binalar[binsay].xkon && sinirx <= Binalar[binsay].xkon + 50) && (siniry >= Binalar[binsay].ykon && siniry <= 500)) 
																			{
																				for(kontrol_kat = Binalar[binsay].katcik ; kontrol_kat>=0 ; --kontrol_kat )
																				{
																					if((siniry>=Binalar[binsay].ykon && siniry<=Binalar[binsay].ykon+50)) 		//Binaya çarptý mý kontrol
																			        {
																			        	blit (b5,araresim,0,0,Binalar[binsay].xkon,Binalar[binsay].ykon,50,50);
																						Binalar[binsay].ykon = Binalar[binsay].ykon + 50;
																						play_sample(kirilmases,255,128,1000,0);
																			        }	
																				}
																				goto BURAYAGEL;
																			}
																		}
																	}
																}
																BURAYAGEL :	
																Oyuncular[0].gucu = 1;
																Oyuncular[0].yonu = 1;
																gucy1 = 78;
																yonx1 = 93;
																hak = 2;
																kural++;
																blit (araresim,oyunresim,0,0,0,0,800,500);
																timer = 0;	
																	
															}
														}
																														
														else if (hak == 2)
														{
															circlefill(araresim,sinirx1+5,siniry1,2,makecol(255,255,255));
															blit (araresim,oyunresim,0,0,0,0,800,500);
															textprintf_ex(oyunresim,font,600,70,makecol(0,0,0),-1,"%d",timer);			//sure
															if (timer > 19)
															{
																hak = 1;
																timer = 0;
																kural++;
															} 
																
															if (key[KEY_L] )
															{
																Oyuncular[1].gucvx = Oyuncular[1].gucu*cos((-Oyuncular[1].yonu)/60) + ruzgarSid;
																Oyuncular[1].gucvy = Oyuncular[1].gucu*sin((-Oyuncular[1].yonu)/60);
																blit(araresim,oyunresim,0,0,0,0,800,500);
																play_sample(atmases,255,128,1000,0);
																while (((sinirx1> 0) && (sinirx1 < 800)) && ((siniry1 < 500) && (siniry1 > 0)))
																{
																	blit(oyunresim,screen,0,0,0,0,800,500);
																	circlefill(oyunresim,sinirx1,siniry1,2,makecol(255,255,255));
																	Oyuncular[1].gucvy = Oyuncular[1].gucvy + cekim*deltat;
																	sinirx1 = sinirx1 - (Oyuncular[1].gucvx*deltat);
																	siniry1 = siniry1 + (Oyuncular[1].gucvy*deltat) + 0.5 * cekim *(deltat*deltat);
																	rest (30);
																	if ( ((sinirx1 > Oyuncular[0].xkon) && (sinirx1 < Oyuncular[0].xkon+25)) && (siniry1 > Oyuncular[0].ykon) && (siniry1 > Oyuncular[0].ykon-50) )
											 						{
											 							Vurulma2++;
																		Oyuncular[1].puani += 10;
																		play_sample(vurmases,255,128,1000,0);
																		switch (timer)
																		{
																			case 1 : Oyuncular[1].puani += 200 ; break;
																			case 2 : Oyuncular[1].puani += 190 ; break;			//vurulma ve puan hesabý
																			case 3 : Oyuncular[1].puani += 180 ; break;
																			case 4 : Oyuncular[1].puani += 170 ; break;
																			case 5 : Oyuncular[1].puani += 160 ; break;
																			case 6 : Oyuncular[1].puani += 150 ; break;
																			case 7 : Oyuncular[1].puani += 140 ; break;
																			case 8 : Oyuncular[1].puani += 130 ; break;
																			case 9 : Oyuncular[1].puani += 120 ; break;
																			case 10 : Oyuncular[1].puani += 110 ; break;
																			case 11 : Oyuncular[1].puani += 100 ; break;
																			case 12 : Oyuncular[1].puani += 90 ; break;
																			case 13 : Oyuncular[1].puani += 80 ; break;
																			case 14 : Oyuncular[1].puani += 70 ; break;
																			case 15 : Oyuncular[1].puani += 60 ; break;
																			case 16 : Oyuncular[1].puani += 50 ; break;
																			case 17 : Oyuncular[1].puani += 40 ; break;
																			case 18 : Oyuncular[1].puani += 30 ; break;
																			case 19 : Oyuncular[1].puani += 20 ; break;
																			case 20 : Oyuncular[1].puani += 10 ; break;
																			default : Oyuncular[0].puani += 5 ; break;
																		}
																		switch (Vurulma2)
																		{
																			case 1 : textout_ex(araresim,font,"+",Oyuncular[0].xkon+5,Oyuncular[0].ykon-10,makecol(255,0,0),-1); break;
																			case 2 : textout_ex(araresim,font,"++",Oyuncular[0].xkon+5,Oyuncular[0].ykon-10,makecol(255,0,0),-1); break;
																			case 3 : textout_ex(araresim,font,"+++",Oyuncular[0].xkon+5,Oyuncular[0].ykon-10,makecol(255,0,0),-1); break;
																		default : textout_ex(araresim,font,"",Oyuncular[0].xkon+5,Oyuncular[0].ykon-10,makecol(255,0,0),-1); break;
																		}
																				
																		goto BURAYAGELIKI;
																	}
																	else 
																	{
																		for (binsay = 0; binsay<15 ; binsay++)
																		{
																		if ( (sinirx1 >= Binalar[binsay].xkon && sinirx1 <= Binalar[binsay].xkon + 50) && (siniry1 >= Binalar[binsay].ykon && siniry1 <= 500)) 
																			{
																				for(kontrol_kat = Binalar[binsay].katcik ; kontrol_kat>=0 ; --kontrol_kat )			//Binaya çarptý mý kontrol
																				{
																					if((siniry1>=Binalar[binsay].ykon && siniry1<=Binalar[binsay].ykon+50)) 
																			       {
																			       		blit (b5,araresim,0,0,Binalar[binsay].xkon,Binalar[binsay].ykon,50,50);
																				   		Binalar[binsay].ykon = Binalar[binsay].ykon + 50;
																				   		play_sample(kirilmases,255,128,1000,0);
																			       }
																				}
																				goto BURAYAGELIKI;
																			}
																		}
																	}
																				
																}
															BURAYAGELIKI :
															Oyuncular[1].gucu = 1;
															Oyuncular[1].yonu = 1;
															gucy2 = 78;
															yonx2 = 713;
															hak = 1;
															kural++;
															timer = 0;
															blit (araresim,oyunresim,0,0,0,0,800,500);
															}
																		
														}
														if (Oyuncular[0].puani>Oyuncular[1].puani)
															Yuksekpuan = Oyuncular[0].puani;
														else 
															Yuksekpuan = Oyuncular[1].puani;
														rest (100);
														blit(araresim,screen,0,0,0,0,800,500); 	
													}
													else //Puan karþýlaþtýrma
													{
														if (Yuksekpuan > Siralama[2])
														{
															Siralama[2] = Yuksekpuan;
															Yuksekpuan = -1;
														}
														else if(Yuksekpuan > Siralama[1])	
														{
															Siralama[1] = Yuksekpuan;
															Yuksekpuan = -1;
														}
														else if (Yuksekpuan > Siralama[0])
														{
															Siralama[0] = Yuksekpuan;
															Yuksekpuan = -1;
														}
																																	
														blit(araresim,screen,0,0,0,0,800,500);
														blit(Lakapres,araresim,0,0,0,0,800,500);	
														textout_ex(araresim,font,"alpha.wallhaven.cc",0,490,makecol(0,0,0),-1);					//Kazanan Menü
														textout_ex(araresim,font,"Version Alpha 1.0",655,490,makecol(0,0,0),-1);
														textout_ex(araresim,font,"KAZANAN",350,40,makecol(255,0,0),-1);
														if (Oyuncular[0].puani>Oyuncular[1].puani)
														{
															textout_ex(araresim,font,"Kazanan : 1. Oyuncu",50,90,makecol(255,255,255),-1);
															textprintf_ex(araresim,font,80,130,makecol(255,255,255),-1,"Puani : %d",Oyuncular[0].puani );
														}
														
														else if (Oyuncular[0].puani<Oyuncular[1].puani)
														{
															textout_ex(araresim,font,"Kazanan : 2. Oyuncu",50,90,makecol(255,255,255),-1);
															textprintf_ex(araresim,font,80,130,makecol(255,255,255),-1,"Puani : %d",Oyuncular[1].puani );
														}
															
														else 
														{
															textout_ex(araresim,font,"Puanlar Esit.",50,90,makecol(255,255,255),-1);
															textprintf_ex(araresim,font,80,130,makecol(255,255,255),-1,"Puani : %d",Oyuncular[0].puani );
														}
															
														blit (t13,araresim,0,0,650,375,100,50);
														if (mouse_x>650 && mouse_x<750 && mouse_y>375 && mouse_y<425)
														{
															blit (t14,araresim,0,0,650,375,100,50);
															if (mouse_b & 1)
															{
																goto Menu;
															}
														}
														blit(araresim,screen,0,0,0,0,800,500); 
													}
													blit(araresim,screen,0,0,0,0,800,500);
												}
											}
										}
									}
									blit(araresim,screen,0,0,0,0,800,500);
								}
							}
						}
						blit(araresim,screen,0,0,0,0,800,500);
							
					}
						
				}
			}
			if(mouse_x>300 && mouse_x<500 && mouse_y>100 && mouse_y<150)												//En Yüksek 3 Sýralama.
			{
				blit (t5,araresim,0,0,300,100,200,50);
				if (mouse_b & 1)
				{
					while (!key[KEY_BACKSPACE] && !key[KEY_ESC])						
					{
						clear_to_color(araresim,makecol(0,0,0));
						blit (Sirares,araresim,0,0,0,0,800,500);
						blit (t7,araresim,0,0,25,400,100,75);
						textout_ex(araresim,font,"alpha.wallhaven.cc",0,490,makecol(255,255,255),-1);
						textout_ex(araresim,font,"Version Alpha 1.0",655,490,makecol(255,255,255),-1);
						textout_ex(araresim,font,"En Yuksek 3 Skor",75,100,makecol(255,128,0),-1);
						textprintf_ex(araresim,font,100,120,makecol(255,128,0),-1,"%d",Siralama[2] );
						textprintf_ex(araresim,font,100,140,makecol(255,128,0),-1,"%d",Siralama[1] );
						textprintf_ex(araresim,font,100,160,makecol(255,128,0),-1,"%d",Siralama[0] );
						if (mouse_x>25 && mouse_x<125 && mouse_y>400 && mouse_y<475)
						{
							blit (t8,araresim,0,0,25,400,100,75);
							if (mouse_b & 1)	goto Menu;
						}
					blit(araresim,screen,0,0,0,0,800,500);
					}
				}
			}	
		if(mouse_x>650 && mouse_x<750 && mouse_y>100 && mouse_y<150)												//Çýkýþ Tuþu.
		{
			blit (t6,araresim,0,0,650,100,100,50);
			if (mouse_b & 1)
			exit(0);
		}
		blit(araresim,screen,0,0,0,0,800,500);
		
		
		}
   }
	 
	Bitir();
	return 0;
}
END_OF_MAIN()


