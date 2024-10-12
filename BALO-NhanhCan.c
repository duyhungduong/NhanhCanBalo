//Bai toan cai ba lo 3
// Moi do vat co so luong cho truoc
//Du lieu cho trong file Caitui3.txt

//Giai bang phuong phap NHANH CAN
#include <stdio.h>
#include <malloc.h>
#include <string.h>
typedef struct{
	char TenDV[20];
	float TL, GT , DG; // Trong luong , Gia tri , Don gia 
	int SL , So_DV_Duoc_Chon; // So luong 
}DoVat;
DoVat* ReadFromFile( float* w , int* n){
	FILE *f;
	DoVat *dsdv;
	f = fopen("CaiTui3.txt", "r");
	if(f==NULL){
		printf("LOIIIII!!!!!!!!!!!!!!");
		return;
	}
	fscanf(f, "%f", w); //Xac dinh trong luong cua balo
	dsdv = (DoVat*)malloc(sizeof(DoVat));
	int i=0;
	while (!feof(f)){
		fscanf(f, "%f%f%d%[^\n]", &dsdv[i].TL,&dsdv[i].GT,&dsdv[i].SL,&dsdv[i].TenDV );
		dsdv[i].DG = dsdv[i].GT/dsdv[i].TL;
		dsdv[i].So_DV_Duoc_Chon = 0;
		i++;
		dsdv = realloc(dsdv, sizeof(DoVat)*(i+1));
	}
	*n = i;
	fclose(f);
	return dsdv;
}
void swap(DoVat* x, DoVat* y){
	DoVat temp;
	temp = *x;
	*x = *y;
	*y = temp;
}
void BubbleSort(DoVat* dsdv , int n ){
	int i, j;
	for (i=0 ; i<=n-2 ; i++ )
		for (j=n-1 ; j>= i+1 ; j--)
			if (dsdv[j].DG > dsdv[j-1].DG)
				swap(&dsdv[j], &dsdv[j-1]);
}
void InDSDV(DoVat* dsdv , int n , float w){
	int i ;
	float TongTL = 0.0 , TongGT = 0.0 ;
	printf("\n Phuong an thu duoc tu Ky thuat NHANH CAN nhu sau: \n");
	printf("|---|--------------------|---------|---------|--------|---------|---------------|\n");
	printf("|STT|---  Ten Do Vat  ---|-T.Luong-|-Gia Tri-|So luong| Don Gia |So DV duoc chon|\n");
	printf("|---|--------------------|---------|---------|--------|---------|---------------|\n");
	for (i=0 ; i<n ;i++){
			printf("|%-3d|%-20s|%9.2f|%9.2f|%5d   |%9.2f|%8d	    |\n", i+1, dsdv[i].TenDV, dsdv[i].TL, dsdv[i].GT, dsdv[i].SL, dsdv[i].DG, dsdv[i].So_DV_Duoc_Chon);
			TongGT = TongGT + dsdv[i].So_DV_Duoc_Chon*dsdv[i].GT;
			TongTL = TongTL + dsdv[i].So_DV_Duoc_Chon*dsdv[i].TL;
	}
	printf("|---|--------------------|---------|---------|--------|---------|---------------|\n");
	printf("\nTrong luong cua balo = %9.2f\n", w);
	printf("\nTrong luong cac vat duoc chon = %9.2f\n", TongTL);
	printf("\nGia tri cua balo = %9.2f\n", TongGT);
}
// Tinh cac dai lung tai nut goc

void Tao_Nut_Goc(float w , float* TLConLai, float *CT , float* GiaLNTT, float* TGT , float Don_Gia_Lon_Nhat){
	*TGT = 0.0;
	*TLConLai = w;
	*CT = *TLConLai*Don_Gia_Lon_Nhat; // Can tren cua nut goc
	*GiaLNTT= 0.0;
}
//Ghi nhan phuong an tot nhat tam thoi
void Cap_Nhat_PA_TNTT(float TGT , float* GiaLNTT, int x[], DoVat* dsdv , int n ){
	int i ;
	if (*GiaLNTT < TGT ){
		*GiaLNTT = TGT ;
		for (i=0 ; i<n ; i++)
			dsdv[i].So_DV_Duoc_Chon = x[i];
	}
}

int min(int a, int b){
	return a<b ? a : b;
}

void Nhanh_Can (int i, float *TGT , float *CT, float *TLConLai, float* GiaLNTT, int x[], DoVat* dsdv , int n ){
	int j; // j la so do vat duoc chon
	int So_Do_Vat_Lon_Nhat_Co_The_Chon = min(dsdv[i].SL, *TLConLai/dsdv[i].TL);
	
	for(j=So_Do_Vat_Lon_Nhat_Co_The_Chon; j>=0 ;j--){
		//Xet tat ca cac khe nang co the phan nhanh theo do vat i
		//Ung voi mot gia tri cua j, ta co mot nut tren cay
		// Tinh 3 thong so cua nut
		*TGT = *TGT + j*dsdv[i].GT;
		*TLConLai = *TLConLai - j*dsdv[i].TL;
		 // dsdv[i+1].DG la Don Gia cua vat ke tiep
		*CT = *TGT + *TLConLai*dsdv[i+1].DG;
		if (*CT > *GiaLNTT){//Neu CT <= GiaLNTT thi cat tia
			x[i] = j;
			// Xet het tat ca do vat hoac da day balo
			if ((i==n-1) || (*TLConLai ==0.0)) 
				Cap_Nhat_PA_TNTT(*TGT, GiaLNTT, x, dsdv , n);
			else //Xet nut con cua nut i
				Nhanh_Can(i+1, TGT , CT , TLConLai, GiaLNTT , x, dsdv , n);
		}
		///Quay lui de xet nut khac (ung voi gia tri khac cua j)
		x[i] = 0;
		*TGT = *TGT - j*dsdv[i].GT;		//Tra lai Tong gia tri TGT cua nut cha
		*TLConLai = *TLConLai + j*dsdv[i].TL;	//Tra lai Trong luong con lai cua nut cha
		
	} 
}
int main(){
	DoVat* dsdv ; //Danh sach cac do vat {mang dong cua cac do vat)
	int n ; 		//Luu so luong do vat
	float w;  		//Luu trong luong cua balo
	
	float CT;	// Luu can. tren
	float TGT ; 	//Luu tong gia ri cua cac vat da duoc chon tai mot nut
	float TLConLai; 	//Luu trong luong con lai tai moi nut 
	float GiaLNTT;	//Luu gia tri lon nhat tam thoi
	
	dsdv = ReadFromFile(&w, &n);
	int x[n]; // Luu phuong an tot nhat tam thoi
	// Sap xep lai danh sach do vat
	BubbleSort(dsdv, n );
	
	Tao_Nut_Goc(w, &TLConLai, &CT, &GiaLNTT, &TGT, dsdv[0].DG);
	
	Nhanh_Can(0, &TGT , &CT, &TLConLai , &GiaLNTT, x, dsdv , n);
	
	InDSDV(dsdv, n ,w) ;
	
	free(dsdv) ; 
	return 0;
	
}


