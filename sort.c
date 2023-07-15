#include <time.h>
#include <stdlib.h>
#include <stdio.h>
//#include <memory.h>
#include <string.h>

int extraMemoryAllocated;

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int* arr, int n, int i) {
    int largest = i; // largest is the root
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    /*
     * finds largest (root)
     */
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]); //Swaps
        heapify(arr, n, largest); // Repeats
    }
}

// extraMemoryAllocated counts bytes of extra memory allocated
// Implemented heap sort
void heapSort(int arr[], int n) {
// Build a max heap
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

// Extract elements from the heap one by one
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
      // extraMemoryAllocated += sizeof(int);

    }
}



// implement merge sort
// extraMemoryAllocated counts bytes of extra memory allocated


void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

// parses input file to an integer array
int parseData(char *inputFileName, int **ppData)
{
	FILE* inFile = fopen(inputFileName,"r");
	int dataSz = 0;
	int i, n, *data;
	*ppData = NULL;
	
	if (inFile)
	{
		fscanf(inFile,"%d\n",&dataSz);
		*ppData = (int *)malloc(sizeof(int) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i=0;i<dataSz;++i)
		{
			fscanf(inFile, "%d ",&n);
			data = *ppData + i;
			*data = n;
		}

		fclose(inFile);
	}
	
	return dataSz;
}

// prints first and last 100 items in the data array
void printArray(int pData[], int dataSz)
{

	int i, sz = dataSz - 100;
	printf("\tData:\n\t");
	for (i=0;i<100;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\t");

	for (i=sz;i<dataSz;++i)
	{
		printf("%d ",pData[i]);
	}
	printf("\n\n");
}

void testHeap(){
    printf("Testing\n");
    int array[] = {4, 2, 6, 3, 63, 232, 42, 63};
    int size = 8;
    for (int i =  0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
    heapSort(array, size);
    printf("Sorted Heap: ");
    for (int i =  0; i < size; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}
int main(void) {
    //testHeap();
    clock_t start, end;
    int i;
    double cpu_time_used;
//    char *fileNames[] = {"C:\\Users\\matt1\\CLionProjects\\lab_assignment_8\\input1.txt", "C:\\Users\\matt1\\CLionProjects\\lab_assignment_8\\input2.txt", "C:\\Users\\matt1\\CLionProjects\\lab_assignment_8\\input3.txt", "C:\\Users\\matt1\\CLionProjects\\lab_assignment_8\\input5.txt"};
    char *fileNames[] = {"input1.txt", "input2.txt", "input3.txt", "input4.txt"};
//	char* fileNames[] = { "input1.txt", "input2.txt", "input3.txt"};
    for (i = 0; i < 4; ++i) {
        int *pDataSrc, *pDataCopy;
        int dataSz = parseData(fileNames[i], &pDataSrc);

        if (dataSz <= 0)
            continue;

        pDataCopy = (int *) malloc(sizeof(int) * dataSz);

        printf("---------------------------\n");
        printf("Dataset Size : %d\n", dataSz);
        printf("---------------------------\n");

        printf("Heap Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        heapSort(pDataCopy, dataSz);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);


        printf("Merge Sort:\n");
        memcpy(pDataCopy, pDataSrc, dataSz * sizeof(int));
        extraMemoryAllocated = 0;
        start = clock();
        mergeSort(pDataCopy, 0, dataSz - 1);
        end = clock();
        cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
        printf("\truntime\t\t\t: %.1lf\n", cpu_time_used);
        printf("\textra memory allocated\t: %d\n", extraMemoryAllocated);
        printArray(pDataCopy, dataSz);

        free(pDataCopy);
        free(pDataSrc);
    }

}