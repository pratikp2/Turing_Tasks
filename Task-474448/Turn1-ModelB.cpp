#include<iostream>
using namespace std;

void countSort(int arr[], int min, int max, int n)
{
    // Count occurrences of each element
    int *count = (int*)malloc((max - min + 1) * sizeof(int));
    for (int i = 0; i < n; i++)
        count[arr[i] - min]++;

    // Compute the cumulative sum to know the position of each element in the sorted array
    for (int i = 1; i < (max - min + 1); i++)
        count[i] += count[i - 1];

    // Place the elements in the sorted array
    int *output = (int*)malloc(n * sizeof(int));
    for (int i = n - 1; i >= 0; i--)
    {
        output[count[arr[i] - min] - 1] = arr[i];
        count[arr[i] - min]--;
    }

    // Copy the output back to the input array
    for (int i = 0; i < n; i++)
        arr[i] = output[i];

    free(count);
    free(output);
}

 
int main()
{
    int n = 7;
    int arr[] = {8, 3, 2};

    int min = *min_element(arr, arr+n);
    int max = *max_element(arr, arr+n);

    countSort(arr, min, max, n);

    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
