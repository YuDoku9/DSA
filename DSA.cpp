#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>
using namespace std;
using namespace std::chrono;

void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == target)
            return mid;
        if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int exponentialSearch(int arr[], int n, int target) {
    if (arr[0] == target)
        return 0;
    int i = 1;
    while (i < n && arr[i] <= target)
        i *= 2;
    int index = binarySearch(arr, min(i, n - 1) + 1, target);
    return index;
}

void quickSort(int arr[], int low, int high) {
    if (low >= high)
        return;
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++)
        if (arr[j] <= pivot)
            swap(arr[++i], arr[j]);
    swap(arr[i + 1], arr[high]);
    quickSort(arr, low, i);
    quickSort(arr, i + 2, high);
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    int L[10000], R[10000];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int i = 0; i < n2; i++) R[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2)
        arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int main() {
    int n, target;

    cout << "Enter number of elements: ";
    cin >> n;

    int arr[n], arrQuick[n], arrMerge[n];

    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    random_device rd;
    mt19937 gen(rd());
    shuffle(arr, arr + n, gen);

    for (int i = 0; i < n; i++) {
        arrQuick[i] = arr[i];
        arrMerge[i] = arr[i];
    }

    cout << "\nGenerated Numbers:\n";
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    cout << "\nEnter number to search: ";
    cin >> target;

    auto startBubble = high_resolution_clock::now();
    bubbleSort(arr, n);
    auto stopBubble = high_resolution_clock::now();

    cout << "\nSorted Array (Bubble Sort): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
    cout << "\nBubble Sort Time: " << duration_cast<duration<double>>(stopBubble - startBubble).count() << " seconds\n";

    auto start1 = high_resolution_clock::now();
    int binRes = binarySearch(arr, n, target);
    auto stop1 = high_resolution_clock::now();
    cout << "\nBinary Search: " << (binRes != -1 ? "Found at index " + to_string(binRes) : "Not Found") << endl;
    cout << "Time: " << duration_cast<microseconds>(stop1 - start1).count() << " microseconds\n";

    auto start2 = high_resolution_clock::now();
    int expRes = exponentialSearch(arr, n, target);
    auto stop2 = high_resolution_clock::now();
    cout << "\nExponential Search: " << (expRes != -1 ? "Found at index " + to_string(expRes) : "Not Found") << endl;
    cout << "Time: " << duration_cast<microseconds>(stop2 - start2).count() << " microseconds\n";

    auto start3 = high_resolution_clock::now();
    quickSort(arrQuick, 0, n - 1);
    auto stop3 = high_resolution_clock::now();
    cout << "\nQuick Sort Time: " << duration_cast<microseconds>(stop3 - start3).count() << " microseconds\n";

    auto start4 = high_resolution_clock::now();
    mergeSort(arrMerge, 0, n - 1);
    auto stop4 = high_resolution_clock::now();
    cout << "\nMerge Sort Time: " << duration_cast<microseconds>(stop4 - start4).count() << " microseconds\n";

    return 0;
}
