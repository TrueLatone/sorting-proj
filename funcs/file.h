#ifndef __FILE_H_INCLUDED__ // If file.h hasn't been included yet...
#define __FILE_H_INCLUDED__ //  #define this so the compiler knows it has been included

#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>
#include <cmath>
#include <chrono>

using namespace std;
using namespace chrono;

template <class T>
void HoanVi(T &a, T &b);

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n);

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n);

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n);

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n);

void GenerateData(int a[], int n, int dataType);

// For SORTING ALGORITHM
void swap(int &a, int &b);

void SelectionSort(int* a, int n);
void InsertionSort(int* a, int n);
void BubbleSort(int* a, int n);
void FlashSort(int* a, int n);
void Heapify(int* a, int n, int i);
void HeapSort(int* a, int n);
void ShakerSort(int* a, int n);
void ShellSort(int* a, int n);
int BinarySearch(int* a, int k, int low, int high);
void BinaryInsertionSort(int* a, int n);
void Merge(int* a, int low, int mid, int high);
void MergeSort(int* a, int low, int high);
int Partition(int* a , int low , int high);
void QuickSort_recursion(int* a , int low, int high);
void QuickSort(int* a , int n);
void CountingSort(int* a, int n);
void CountSort(int arr[], int n, int exp);
void RadixSort(int* a, int n);

void SelectionSortc(int* a, int n, long long &comparisons);
void InsertionSortc(int* a, int n, long long &comparisons);
void BubbleSortc(int* a, int n, long long &comparisons);
void FlashSortc(int* a, int n, long long &comparisons);
void Heapifyc(int* a, int n, int i, long long &comparisons);
void HeapSortc(int* a, int n, long long &comparisons);
void ShakerSortc(int* a, int n, long long &comparisons);
void ShellSortc(int* a, int n, long long &comparisons);
int BinarySearchc(int* a, int k, int low, int high, long long &comparisons);
void BinaryInsertionSortc(int* a, int n, long long &comparisons);
void Mergec(int* a, int low, int mid, int high, long long &comparisons);
void MergeSortc(int* a, int low, int high, long long &comparisons);
int Partitionc(int* a , int low , int high, long long &comparisons);
void QuickSort_recursionc(int* a , int low, int high, long long &comparisons);
void QuickSortc(int* a , int n, long long &comparisons);
void CountingSortc(int* a, int n, long long &comparisons);
void CountSortc(int arr[], int n, int exp, long long &comparisons);
void RadixSortc(int* a, int n, long long &comparisons);


// FOR GENERATING ARGUMENTS

int* ParseData(string filename, int& size);
void RunAlgorithm(const string& algorithm, int* a, int &n, bool measureTime, bool measureComp);
void CompareAlgorithm(const string& algo1, const string& algo2, int* a, int& n);
// void print(bool measureTime, bool measureComp, long long comparisons, microseconds time);

#endif
