#include "file.h"

inline void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

inline void SelectionSort(int* a, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            if (a[j] < a[min]) min = j;
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

inline void InsertionSort(int* a, int n) {
	for (int i = 1; i < n; i++) {
		int key = a[i];
		int j = i - 1;

		while ((j >= 0) && (a[j] > key)) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

inline void BubbleSort(int* a, int n) {
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1 - i; j++) {
			if (a[j] > a[j+1])
				swap(a[j], a[j+1]);
		}
	}
}

inline void FlashSort(int* a, int n) {
	int minVal = a[0], max = 0;
	int m = 0.45 * n;
	int* l = new int[m];
	
	for (int i = 0; i < m; i++)
		l[i] = 0;
		
	for (int i = 1; i < n; i++) {
		if (a[i] < minVal)
			minVal = a[i];
		if (a[i] > a[max])
			max = i;
	}
	
	if (a[max] == minVal)
		return;
		
	double c1 = (double)(m - 1) / (a[max] - minVal);
	
	for (int i = 0; i < n; i++) {
		int k = c1 * (a[i] - minVal);
		l[k]++;
	}
	
	for (int i = 1; i < m; i++)
		l[i] += l[i - 1];
		
	swap(a[max], a[0]);
	
	int move = 0;
	int j = 0;
	int k = m - 1;
	int flash;
	
	while (move < n - 1) {
		while (j > l[k] - 1) {
			j++;
			k = int(c1*(a[j] - minVal));
		}
		
		flash = a[j];
		if (k < 0) break;
		
		while (j != l[k]) {
			k = int(c1*(flash - minVal));
			l[k]--;
			swap(flash, a[l[k]]);
			move++;
		}
	}
	delete[] l;
	InsertionSort(a, n);
}

inline void heapify(int* a, int n, int i) {
	int largest = i;
	int left = 2 * i + 1, right = left + 1;
	
	if (left < n && a[left] > a[largest])
		largest = left;
	if (right < n && a[right] > a[largest])
		largest = right;
		
	if (largest != i) {
		swap(a[largest], a[i]);
		heapify(a, n, largest);
	}	
}

inline void HeapSort(int* a, int n) {
	for (int i = n / 2 - 1; i >= 0; i--) {
		heapify(a, n, i);
	}
	
	for (int i = n - 1; i > 0; i--) {
		swap(a[0], a[i]);
		heapify(a, i, 0);
	}
}

inline void ShakerSort(int* a, int n) {
	int start = 0, end = n - 1;
	bool swapped = true;
	while (swapped) {
		swapped = false;
		
		for (int i = start; i < end; i++) {
			if (a[i] > a[i+1]) {
				swap(a[i], a[i+1]);
				swapped = true;
			}
		}
		
		if (!swapped)
			break;
		end--;
		
		for (int i = end - 1; i >= start; i--) {
			if (a[i] > a[i+1]) {
				swap(a[i], a[i+1]);
				swapped = true;
			}
		}
		
		if (!swapped)
			break;
		start++;
	}
}

inline void ShellSort(int* a, int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int key = a[i];
            int j;
            for (j = i; (j >= gap) && (a[j - gap] > key); j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = key;
        }
    }
}

inline int binarySearch(int* a, int k, int low, int high) {
    if (high <= low) {
        return (k > a[low]) ? (low + 1) : low;
    }

    int mid = low + (high - low) / 2; 

    if (k == a[mid]) {
        return mid + 1; 
    }

    if (k > a[mid]) {
        return binarySearch(a, k, mid + 1, high); 
    }
    return binarySearch(a, k, low, mid - 1); 
}

inline void BinaryInsertionSort(int* a, int n) {
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;
        int loc = binarySearch(a, key, 0, j);
        while (j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

inline void Merge(int* a, int low, int mid, int high) {
    int i = low; 
    int j = mid + 1; 
    int k = 0; 
    int *temp = new int[high - low + 1];

    while (i <= mid && j <= high) {  
        if (a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (i <= mid) {
        temp[k++] = a[i++];
    }
    while (j <= high) {
        temp[k++] = a[j++];
    }
    for (int i = low; i <= high; i++) {
        a[i] = temp[i - low];
    }
    delete[] temp;
}

inline void MergeSort(int* a, int low, int high) {
    if (low < high) {
        int mid = (low + high) / 2;
        MergeSort(a, low, mid);
        MergeSort(a, mid + 1, high);
        Merge(a, low, mid, high);  
    }
}

inline int Partition (int* a , int low , int high) {
    int pivot_value = a[high];
    int i = low - 1;
    int temp;
    for (int j = low ; j < high ; j++){
        if (a[j] < pivot_value){
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    i++;
    temp = a[i];
    a[i] = a[high];
    a[high] = temp;
    return i;
}

inline void QuickSort_recursion (int* a , int low, int high) {
    if (low < high){
    int pivot_index = Partition(a , low , high);
    QuickSort_recursion(a, low, pivot_index - 1);
    QuickSort_recursion(a, pivot_index + 1, high);
    }
}

inline void QuickSort (int* a , int n) {
      QuickSort_recursion(a , 0 , n - 1);
}

inline void CountingSort (int* a, int n) {
    int max = a[0];
    for (int i = 0; i < n; i++){ //This loop will be skipped if user typed in max value (which is the default input for counting sort and there would be no comparisons)         
        if (a[i] > max)        
        max = a[i];
    }
    int* b = new int [max + 1];
    int* s = new int[n];
    for (int i = 0 ; i <= max ; i++) {
        b[i] = 0;
    }
    for (int i = 0 ; i < n ; i++) {
        b[a[i]]++;
    }
    for (int i = 1 ; i <= max; i++) {
        b[i] += b[i - 1];
    }
    for (int i = n - 1 ; i >= 0 ; i--) {
        s[b[a[i]] - 1] = a[i];
        b[a[i]]--; 
    }
    for (int i = 0 ; i < n ; i++)
        a[i] = s[i];

    delete[] b;
    delete[] s;
}

inline void countSort(int arr[], int n, int exp) {
    int output[n];
    int i, count[10] = {0};
    for (i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; i < n; i++) arr[i] = output[i];
}

inline void RadixSort(int* a, int n) {
    int max = a[0];
    for (int i = 1 ; i < n ; i++) { //sane comment from counting sort also applies here
        if (a[i] > max)
            max = a[i];
    }
    int m = 0;
    while (max > 0){
        m++;
        max /= 10;
    }

    for (int exp = 1; m / exp > 0; exp *= 10) countSort(a, n, exp);
}

// FOR COUNTING COMPARISONS

inline void SelectionSortc(int* a, int n, long long &comparisons) {
    for (int i = 0; ++comparisons && i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; ++comparisons && j < n; j++) {
            if (++comparisons && a[j] < a[min]) min = j;
        }
        int temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

inline void InsertionSortc(int* a, int n, long long &comparisons) {
	for (int i = 1; ++comparisons && i < n; i++) {
		int key = a[i];
		int j = i - 1;

		while ((++comparisons && j >= 0) && (++comparisons && a[j] > key)) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = key;
	}
}

inline void BubbleSortc(int* a, int n, long long &comparisons) {
	for (int i = 0; ++comparisons && i < n - 1; i++) {
		for (int j = 0; ++comparisons && j < n - 1 - i; j++) {
			if (++comparisons && a[j] > a[j+1])
				swap(a[j], a[j+1]);
		}
	}
}

inline void FlashSortc(int* a, int n, long long &comparisons) {
	int minVal = a[0], max = 0;
	int m = 0.45 * n;
	int* l = new int[m];
	
	for (int i = 0; ++comparisons && i < m; i++)
		l[i] = 0;
		
	for (int i = 1; ++comparisons && i < n; i++) {
		if (++comparisons && a[i] < minVal)
			minVal = a[i];
		if (++comparisons && a[i] > a[max])
			max = i;
	}
	
	if (++comparisons && a[max] == minVal)
		return;
		
	double c1 = (double)(m - 1) / (a[max] - minVal);
	
	for (int i = 0; ++comparisons && i < n; i++) {
		int k = c1 * (a[i] - minVal);
		l[k]++;
	}
	
	for (int i = 1; ++comparisons && i < m; i++)
		l[i] += l[i - 1];
		
	swap(a[max], a[0]);
	
	int move = 0;
	int j = 0;
	int k = m - 1;
	int flash;
	
	while (++comparisons && move < n - 1) {
		while (++comparisons && j > l[k] - 1) {
			j++;
			k = int(c1*(a[j] - minVal));
		}
		
		flash = a[j];
		if (++comparisons && k < 0) break;
		
		while (++comparisons && j != l[k]) {
			k = int(c1*(flash - minVal));
			l[k]--;
			swap(flash, a[l[k]]);
			move++;
		}
	}
	delete[] l;
	InsertionSortc(a, n, comparisons);
}

inline void heapifyc(int* a, int n, int i, long long &comparisons) {
	int largest = i;
	int left = 2 * i + 1, right = left + 1;
	
	if (++comparisons && left < n && ++comparisons && a[left] > a[largest])
		largest = left;
	if (++comparisons && right < n && ++comparisons && a[right] > a[largest])
		largest = right;
		
	if (++comparisons && largest != i) {
		swap(a[largest], a[i]);
		heapifyc(a, n, largest, comparisons);
	}	
}

inline void HeapSortc(int* a, int n, long long &comparisons) {
	for (int i = n / 2 - 1; ++comparisons && i >= 0; i--) {
		heapifyc(a, n, i, comparisons);
	}
	
	for (int i = n - 1; ++comparisons && i > 0; i--) {
		swap(a[0], a[i]);
		heapifyc(a, i, 0, comparisons);
	}
}

inline void ShakerSortc(int* a, int n, long long &comparisons) {
	int start = 0, end = n - 1;
	bool swapped = true;
	while (++comparisons && swapped) {
		swapped = false;
		
		for (int i = start; ++comparisons && i < end; i++) {
			if (++comparisons && a[i] > a[i+1]) {
				swap(a[i], a[i+1]);
				swapped = true;
			}
		}
		
		if (++comparisons && !swapped)
			break;
		end--;
		
		for (int i = end - 1; ++comparisons && i >= start; i--) {
			if (++comparisons && a[i] > a[i+1]) {
				swap(a[i], a[i+1]);
				swapped = true;
			}
		}
		
		if (++comparisons && !swapped)
			break;
		start++;
	}
}

inline void ShellSortc(int* a, int n, long long &comparisons) {
    for (int gap = n / 2; ++comparisons && gap > 0; gap /= 2) {
        for (int i = gap; ++comparisons && i < n; i++) {
            int key = a[i];
            int j;
            for (j = i; (++comparisons && j >= gap) && (++comparisons && a[j - gap] > key); j -= gap) {
                a[j] = a[j - gap];
            }
            a[j] = key;
        }
    }
}

inline int binarySearchc(int* a, int k, int low, int high, long long &comparisons) {
    if (++comparisons && high <= low) {
        return (++comparisons && k > a[low]) ? (low + 1) : low;
    }

    int mid = low + (high - low) / 2; 

    if (++ comparisons && k == a[mid]) {
        return mid + 1; 
    }

    if (++comparisons && k > a[mid]) {
        return binarySearchc(a, k, mid + 1, high, comparisons); 
    }
    return binarySearchc(a, k, low, mid - 1, comparisons); 
}

inline void BinaryInsertionSortc(int* a, int n, long long &comparisons) {
    for (int i = 1; ++comparisons && i < n; i++) {
        int key = a[i];
        int j = i - 1;
        int loc = binarySearchc(a, key, 0, j, comparisons);
        while (++comparisons && j >= loc) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = key;
    }
}

inline void Mergec(int* a, int low, int mid, int high, long long &comparisons) {
    int i = low; 
    int j = mid + 1; 
    int k = 0; 
    int *temp = new int[high - low + 1];

    while (++comparisons && i <= mid && ++comparisons && j <= high) {  
        if (++comparisons && a[i] <= a[j]) {
            temp[k++] = a[i++];
        } else {
            temp[k++] = a[j++];
        }
    }
    while (++comparisons && i <= mid) {
        temp[k++] = a[i++];
    }
    while (++comparisons && j <= high) {
        temp[k++] = a[j++];
    }
    for (int i = low; ++comparisons && i <= high; i++) {
        a[i] = temp[i - low];
    }
    delete[] temp;
}

inline void MergeSortc(int* a, int low, int high, long long &comparisons) {
    if (++comparisons && low < high) {
        int mid = (low + high) / 2;
        MergeSortc(a, low, mid, comparisons);
        MergeSortc(a, mid + 1, high, comparisons);
        Mergec(a, low, mid, high, comparisons);  
    }
}

inline int Partitionc(int* a , int low , int high, long long &comparisons) {
    int pivot_value = a[high];
    int i = low - 1;
    int temp;
    for (int j = low ; ++comparisons && j < high ; j++){
        if (++comparisons && a[j] < pivot_value){
            i++;
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
        }
    }
    i++;
    temp = a[i];
    a[i] = a[high];
    a[high] = temp;
    return i;
}

inline void QuickSort_recursionc (int* a , int low, int high, long long &comparisons) {
    if (++comparisons && low < high){
    int pivot_index = Partitionc(a , low , high, comparisons);
    QuickSort_recursionc(a, low, pivot_index - 1, comparisons);
    QuickSort_recursionc(a, pivot_index + 1, high, comparisons);
    }
}

inline void QuickSortc(int* a , int n, long long &comparisons) {
      QuickSort_recursionc(a , 0 , n - 1, comparisons);
}

inline void CountingSortc(int* a, int n, long long &comparisons) {
    int max = a[0];
    for (int i = 0; ++comparisons && i < n; i++){ //This loop will be skipped if user typed in max value (which is the default input for counting sort and there would be no comparisons)         
        if (++comparisons && a[i] > max)        
        max = a[i];
    }
    int* b = new int [max + 1];
    int* s = new int[n];
    for (int i = 0 ; ++comparisons && i <= max ; i++) {
        b[i] = 0;
    }
    for (int i = 0 ; ++comparisons && i < n ; i++) {
        b[a[i]]++;
    }
    for (int i = 1 ; ++comparisons && i <= max; i++) {
        b[i] += b[i - 1];
    }
    for (int i = n - 1 ; ++comparisons && i >= 0 ; i--) {
        s[b[a[i]] - 1] = a[i];
        b[a[i]]--; 
    }
    for (int i = 0 ; ++comparisons && i < n ; i++)
        a[i] = s[i];

    delete[] b;
    delete[] s;
}

inline void countSortc(int arr[], int n, int exp, long long &comparisons) {
    int output[n];
    int i, count[10] = {0};
    for (i = 0; ++comparisons && i < n; i++)
        count[(arr[i] / exp) % 10]++;
    for (i = 1; ++comparisons && i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; ++comparisons && i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    for (i = 0; ++comparisons && i < n; i++) arr[i] = output[i];
}

inline void RadixSortc(int* a, int n, long long &comparisons) {
    int max = a[0];
    for (int i = 1 ; ++comparisons && i < n ; i++) { //sane comment from counting sort also applies here
        if (++comparisons && a[i] > max)
            max = a[i];
    }
    int m = 0;
    while (++comparisons && max > 0){
        m++;
        max /= 10;
    }

    for (int exp = 1; ++comparisons && m / exp > 0; exp *= 10) countSortc(a, n, exp, comparisons);
}