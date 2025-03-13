#include "sort.cpp"

template <class T>
void HoanVi(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand()%n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int) time(NULL));
	for (int i = 0; i < 10; i ++)
	{
		int r1 = rand()%n;
		int r2 = rand()%n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateSortedData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateReverseData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}


// FOR EXECUTING ARGUMENTS:

int* ParseData(string filename, int &size) {
    fstream fi(filename);
    if (!fi.is_open()) {
        size = 0;
        return NULL;
    }
    fi >> size;
    fi.ignore();
    int num, index = 0;
    int* a = new int[size];
    while (fi >> num) a[index++] = num;
    fi.close();
    return a;
}

// const string algorithms[12] = {"selection-sort", "insertion-sort", "shell-sort", "bubble-sort", "heap-sort", "merge-sort", "quick-sort", "radix-sort", "counting-sort", "binary-insertion-sort", "shaker-sort", "flash-sort"};

void sortonly(const string& algorithm, int* a, int &n) {
    if (algorithm == "selection-sort") SelectionSort(a, n);
    else if (algorithm == "insertion-sort") InsertionSort(a, n);
    else if (algorithm == "bubble-sort") BubbleSort(a, n);
    else if (algorithm == "flash-sort") FlashSort(a, n);
    else if (algorithm == "heap-sort") HeapSort(a, n);
    else if (algorithm == "shaker-sort") ShakerSort(a, n);
    else if (algorithm == "shell-sort") ShellSort(a, n);
    else if (algorithm == "binary-insertion-sort") BinaryInsertionSort(a, n);
    else if (algorithm == "merge-sort") MergeSort(a, 0, n - 1);
    else if (algorithm == "quick-sort") QuickSort(a, n);
    else if (algorithm == "counting-sort") CountingSort(a, n);
    else if (algorithm == "radix-sort") RadixSort(a, n);
}

void sortwithcomp(const string& algorithm, int* a, int &n, long long &comparisons) {
    if (algorithm == "selection-sort") SelectionSortc(a, n, comparisons);
    else if (algorithm == "insertion-sort") InsertionSortc(a, n, comparisons);
    else if (algorithm == "bubble-sort") BubbleSortc(a, n, comparisons);
    else if (algorithm == "flash-sort") FlashSortc(a, n, comparisons);
    else if (algorithm == "heap-sort") HeapSortc(a, n, comparisons);
    else if (algorithm == "shaker-sort") ShakerSortc(a, n, comparisons);
    else if (algorithm == "shell-sort") ShellSortc(a, n, comparisons);
    else if (algorithm == "binary-insertion-sort") BinaryInsertionSortc(a, n, comparisons);
    else if (algorithm == "merge-sort") MergeSortc(a, 0, n - 1, comparisons);
    else if (algorithm == "quick-sort") QuickSortc(a, n, comparisons);
    else if (algorithm == "counting-sort") CountingSortc(a, n, comparisons);
    else if (algorithm == "radix-sort") RadixSortc(a, n, comparisons);
}

void RunAlgorithm(const string& algorithm, int* a, int &n, bool measureTime, bool measureComp) {
    long long comparisons = 0;
    milliseconds time;
	bool measureTime = false, measureComp = false;

    if (measureTime && !measureComp) {
        auto start = high_resolution_clock::now();
        sortonly(algorithm, a, n);
        auto end = high_resolution_clock::now();
        time = duration_cast<milliseconds>(end - start);
    }
    if (measureComp && !measureTime) {
        sortwithcomp(algorithm, a, n, comparisons);
    }
    if (measureTime && measureComp) {
	int* b = new int[n];
	for (int i = 0; i < n; i++) b[i] = a[i];

	sortwithcomp(algorithm, b, n, comparisons);
	auto start = high_resolution_clock::now();
	sortonly(algorithm, a, n);
	auto end = high_resolution_clock::now();
	time = duration_cast<milliseconds>(end - start);
	delete[] b;
    }
    
    if (measureTime) cout << "Running time: " << time.count() << " ms" << endl;
    if (measureComp) cout << "Comparisons: " << comparisons << " times" << endl;
    else if (!measureTime && !measureComp) cout << "Parameters might be incorrect. Please check README.txt!" << endl;
}

void CompareAlgorithm(const string& algo1, const string& algo2, int* a, int& n) {
    long long comp1 = 0, comp2 = 0;
    int* copy1 = new int[n], *copy2 = new int[n], *temp = new int[n];
    for (int i = 0; i < n; i++) copy1[i] = a[i];
    for (int i = 0; i < n; i++) copy2[i] = a[i];
    for (int i = 0; i < n; i++) temp[i] = a[i];

    sortwithcomp(algo1, copy1, n, comp1);
    auto start1 = high_resolution_clock::now();
    sortonly(algo1, a, n);
    auto end1 = high_resolution_clock::now();
    milliseconds time1 = duration_cast<milliseconds> (end1 - start1);
    delete[] copy1;

    sortwithcomp(algo2, copy2, n, comp2);
    auto start2 = high_resolution_clock::now();
    sortonly(algo2, temp, n);
    auto end2 = high_resolution_clock::now();
    milliseconds time2 = duration_cast<milliseconds> (end2 - start2);
    delete[] copy2;
    delete[] temp;

    cout << "Running time: " << time1.count() << " | " << time2.count() << endl;
    cout << "Comparisons: " << comp1 << " | " << comp2 << endl;
}

