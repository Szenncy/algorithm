#include "stdio.h"
#include "sys/malloc.h"
#include "stdlib.h"
#include "string.h"

/*
 
	显示二维数组
 
 */

void display(int **a,int n)
{
    int bits,bit=0;
    bits = n * n;
    while(bits)
    {
        bits/=10;
        bit++;
    }
    
    for(int i = 0; i < n ; i++)
    {
        for(int j = 0;j < n ;j++)
        {
            printf("%d ",a[i][j]);
            
        }
        printf("\n");
    }
}

/*
 
	动态申请二维数组
 
 */

int ** create_array2D(int row, int col)
{
    
    int **arr;
    
    arr = (int **)malloc(row * sizeof(int *));
    
    for (int i = 0; i < col ; i++) {
        arr[i] = (int*)malloc(col * sizeof(int));
    }
    
    return arr;
}

//列对称互换
void changeR(int **arr,int n){
    int high,low,temp;
    low=0;high=n-1;
    for(int i =0 ;i<n;i++){
        for(int j = 0;j<n/2;j++){
            if(low<high){
                temp = arr[i][low];
                arr[i][low]=arr[i][high];
                arr[i][high]=temp;
                low++;
                high--;
            }
        }
        low=0;high=n-1;
    }
}

//行对称互换
void changeL(int **arr,int n){
    int high,low,temp;
    low=0;high=n-1;
    for(int i =0 ;i<n;i++){
        for(int j = 0;j<n/2;j++){
            if(low<high){
                temp = arr[low][i];
                arr[low][i]=arr[high][i];
                arr[high][i]=temp;
                low++;
                high--;
            }
        }
        low=0;high=n-1;
    }
}

/*
	
    初始化二维数组，让array[i][j] = i + j + fn
 
    fn:起始数值
 
 */

int ** initArray(int n,int fn)
{
    int **arr;
    
    arr = create_array2D(n,n);
    
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
        {
            arr[i][j]=i+j+fn;
        }
    
    return arr;
}

/*
 
	对二维数组插入数据
 
    参数：
        n：数组的阶层
        fn：开始的数值
 
 */

int **inserNumber(int n,int fn){
    int i,j;
    int **array = create_array2D(n,n);
    if(n==2)
    {
        array = initArray(n,fn);
        
        array[1][0]=fn+3;
        
    } else {
        
        array = initArray(n,fn);
        
        int ** temp = create_array2D(n,n);
        
        temp = inserNumber(n-1,fn+n*2-1);
        
        changeR(temp,n-1);
        
        changeL(temp,n-1);
        
        /*
         例如：
         array: 1 2 3    temp: 8 9
		        2 3 4          7 6
		        3 4 5
         
         替换:  
                1 2 3
                8 9 4
                7 6 5
         */
        for(i = 0 ; i < n-1 ; i++)
            for(j = 0 ; j < n-1 ; j++)
            {
                array[i+1][j]=temp[i][j];
            }
        
        
    }
    
    return array;
}



int main(){
    
    int **number,n;
    printf("Input the len of your array:");
    scanf("%d",&n);
    
    if(n>1){
        number = create_array2D(n,n);
        number = inserNumber(n,1);
        display(number,n);
    }else if(n >= 0)
        printf("%d\n",n);
    else
        printf("Printf Error\n");
    
    return 0;
}