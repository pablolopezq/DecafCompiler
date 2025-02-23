// Java program for implementation of Selection Sort
import java.util.*;
class SelectionSort
{
    static int[] arr = new int[10];
    static int n = 10;
    
    static void sort() {
        int i, min_idx, j, temp;

        for (i = 0; i < n-1; i = i + 1) {
            min_idx = i;
            for (j = i+1; j < n; j = j + 1) 
            {
                if (arr[j] < arr[min_idx])
                {
                    min_idx = j;
                }
            }

            temp = arr[min_idx];
            arr[min_idx] = arr[i];
            arr[i] = temp;
        }
    }
 
    // Prints the array
    static void printArray() {
        int i;

        for (i = 0; i<n; i = i + 1) {
            System.out.print(arr[i]);
            System.out.print(" ");
        }
        System.out.println("");
    }
 
    public static void main(String[] args) 
    {
        arr[0] = 24;
        arr[1] = 71;
        arr[2] = 94;
        arr[3] = 3;
        arr[4] = 46;
        arr[5] = 54;
        arr[6] = 96;
        arr[7] = 14;
        arr[8] = 7;
        arr[9] = 42;
        sort();
        System.out.println("Sorted array");
        printArray();
    }
}
