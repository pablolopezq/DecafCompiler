// Java program for implementation of Selection Sort
import java.util.*;
class ArrayTest
{
    static int[] arr = new int[10];
    static int n = 10;
 
    public static void main(String[] args) 
    {
        int i;
        
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
        for (i = 0; i<n; i = i + 1) {
            System.out.print(arr[i]);
            System.out.print(" ");
        }
        System.out.println("");
    }
}
