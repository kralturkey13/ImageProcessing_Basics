#include <iostream>
#include <cmath>
using namespace std;
int i, j;
int IMG[5][6]={{5,5,7,0,0,0},
		       {10,9,7,7,0,1},
			   {14,6,4,7,7,12},
			   {13,6,4,7,7,3},
			   {12,6,8,7,7,3}};
			   
int IMG_mean[4][5]={{5,5,7,0,0},
		       	 	{10,9,7,7,0},
			   		{14,6,4,7,7},
			   		{13,6,4,7,7}};
			
int IMG_median[4][5]={{5,5,7,0,0},
		       		  {10,9,7,7,0},
			   		  {14,6,4,7,7},
			   		  {13,6,4,7,7}};
			   		  
int IMG_gaussian[4][5]={{5,5,7,0,0},
		       		  	{10,9,7,7,0},
			   		  	{14,6,4,7,7},
			   		  	{13,6,4,7,7}};

void Histo(int IMG[5][6], int w, int h,int *hist_array){
	for(i=0;i<16;i++)
		hist_array[i]=0;
	for (i=0;i<w;i++){
		for(j=0;j<h;j++)
			hist_array[IMG[i][j]]++;
	}
	cout<<"histogram"<<endl;
	for(i=0;i<16;i++){
		cout<<hist_array[i]<<" ";
	}
}

int mean_filter_weight[3][3]={{1,2,1},
							  {2,5,2},
							  {1,2,1}};

void mean_filter(int IMG[4][5],int w,int h){
	int IMG_new[4][5];
	int pnew=0,avg=0;
	for(i=0;i<w;i++){
		for(j=0;j<h;j++){
			IMG_new[i][j]=IMG[i][j];
		}
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			avg=avg+mean_filter_weight[i][j];
		}
	}
	for(i=1;i<w-1;i++){
		for(j=1;j<h-1;j++){
			pnew=((IMG[i-1][j-1]*mean_filter_weight[0][0])
			+(IMG[i-1][j]*mean_filter_weight[0][1])
			+(IMG[i-1][j+1]*mean_filter_weight[0][2])
			+(IMG[i][j-1]*mean_filter_weight[1][0])
			+(IMG[i][j]*mean_filter_weight[1][1])
			+(IMG[i][j+1]*mean_filter_weight[1][2])
			+(IMG[i+1][j-1]*mean_filter_weight[2][0])
			+(IMG[i+1][j]*mean_filter_weight[2][1])
			+(IMG[i+1][j+1]*mean_filter_weight[2][2]))/float(avg);
			IMG_new[i][j]=trunc(pnew);
		}
	}
	cout<<"mean filter"<<endl;
	for(i=0;i<w;i++){
		for(j=0;j<h;j++){
			cout<<IMG_new[i][j]<<" ";
		}
		cout<<endl;
	}
}

void median_filter(int IMG[4][5], int w,int h){
	int IMG_new[4][5];
	int temp,mid_element,median_array[9];
	for(i=0;i<w;i++){
		for(j=0;j<h;j++){
			IMG_new[i][j]=IMG[i][j];
		}
	}
	for(i=1;i<w-1;i++){
		for(j=1;j<h-1;j++){
			median_array[0]=IMG_new[i-1][j-1];
			median_array[1]=IMG_new[i-1][j];
			median_array[2]=IMG_new[i-1][j+1];
			median_array[3]=IMG_new[i][j-1];
			median_array[4]=IMG_new[i][j];
			median_array[5]=IMG_new[i][j+1];
			median_array[6]=IMG_new[i+1][j-1];
			median_array[7]=IMG_new[i+1][j];
			median_array[8]=IMG_new[i+1][j+1];
				
			for(int x = 0; x<9; x++){
   				for(int y = y+1; y<9; y++){
      				if(median_array[y] < median_array[x]) {
        				temp = median_array[x];
         				median_array[x] = median_array[y];
         				median_array[y] = temp;
      				}
   				}
   			}
			mid_element=median_array[4];
			IMG[i][j]=mid_element;
		}
	}
	cout<<"median filter"<<endl;
	for(i=0;i<4;i++){
		for(j=0;j<5;j++){
			cout<<IMG[i][j]<<" ";
		}
		cout<<endl;
	}
}

double gaussian_kernel[3][3]={{0.0275,0.1102,0.0275},
							  {0.1102,0.4421,0.1102},
							  {0.0275,0.1102,0.0275}};

void gaussian_filter(int IMG[4][5],int w,int h){
	int IMG_new[4][5];
	int pnew=0;
	for(i=0;i<w;i++){
		for(j=0;j<h;j++){
			IMG_new[i][j]=IMG[i][j];
		}
	}
	for(i=1;i<w-1;i++){
		for(j=1;j<h-1;j++){
			pnew=(gaussian_kernel[0][0]*IMG[i-1][j-1])+
				 (gaussian_kernel[0][1]*IMG[i-1][j])+
				 (gaussian_kernel[0][2]*IMG[i-1][j+1])+
				 (gaussian_kernel[1][0]*IMG[i][j-1])+
				 (gaussian_kernel[1][1]*IMG[i][j])+
				 (gaussian_kernel[1][2]*IMG[i][j+1])+
				 (gaussian_kernel[2][0]*IMG[i+1][j-1])+
				 (gaussian_kernel[2][1]*IMG[i+1][j])+
				 (gaussian_kernel[2][2]*IMG[i+1][j+1]);
			IMG_new[i][j]=pnew;
		}
	}
	cout<<"gaussian filter"<<endl;
	for(i=0;i<w;i++){
		for(j=0;j<h;j++){
			cout<<IMG_new[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(int argc, char** argv) {
	int histo_array[16];
	Histo(IMG,5,6,histo_array);
	cout<<endl<<endl;
	
	cout<<"original image"<<endl;
	for(i=0;i<5;i++){
		for(j=0;j<6;j++){
			cout<<IMG[i][j]<<" ";
		}
		cout<<endl;
	}
	cout<<endl;
	
	mean_filter(IMG_mean,4,5);
	cout<<endl;
	
	median_filter(IMG_median,4,5);
	cout<<endl;
	
	gaussian_filter(IMG_gaussian,4,5);
	
	system("pause");
	return 0;
}
