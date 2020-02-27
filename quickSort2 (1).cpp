#include <stdio.h>
int *arr;
int n;
void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}
void swap(int *a, int *b) {
    int t;
    t = *a;
    *a = *b;
    *b = t;
}
int partition(int arr[], int lowIndex, int highIndex) {
    int i = lowIndex-1;
    for (int j=lowIndex; j<=highIndex-1; j++) {
        if (arr[j] < arr[highIndex]) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1],&arr[highIndex]);
    return i+1;

}
void quickSort(int arr[], int lowIndex, int highIndex) {
    if (lowIndex < highIndex) {
    	printf("VTTT: %d, low=%d, high=%d\n", highIndex, lowIndex, highIndex-1);
        print(arr,n);
        int pi = partition(arr,lowIndex,highIndex);
        quickSort(arr,lowIndex,pi-1);
        quickSort(arr,pi+1,highIndex);
        
    }
}
int main()
{
	printf("Nhap so phan tu: ");
	scanf("%d", &n);
	arr = new int[n];
	for (int i=0; i<n; i++) {
		printf("Phan tu thu %d ",i);
		scanf("%d", &arr[i]);
	}
	print(arr, n);
    quickSort(arr, 0, n - 1);
    print(arr, n);
}
