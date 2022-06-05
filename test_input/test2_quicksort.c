int printf(char* format,...);

int number[8];

void quick_sort(int first,int last){
    int i, j, pivot, temp;
    if(first<last){
        pivot=first;
        i=first;
        j=last;
        while(i<j){
            while(number[i]<=number[pivot]&&i<last){
                i=i+1;
            }
            while(number[j]>number[pivot]){
                j=j-1;
            }
            if(i<j){
                temp=number[i];
                number[i]=number[j];
                number[j]=temp;
            }
        }
        temp=number[pivot];
        number[pivot]=number[j];
        number[j]=temp;
        quick_sort(first,j-1);
        quick_sort(j+1,last);
    }
}

void print_array(int n){
    int k;
    k=0;
    while(k<n){
        printf("%d ",number[k]);
        k=k+1;
    }
    printf("\n");
}

int main(){
    int n;
    n=8;
    number[0]=20;
    number[1]=32;
    number[2]=77;
    number[3]=48;
    number[4]=2323;
    number[5]=67;
    number[6]=10332;
    number[7]=1;
    print_array(n);
    quick_sort(0,n-1);
    print_array(n);
}

