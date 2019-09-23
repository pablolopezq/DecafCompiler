/*
 * ForTest.decaf
 * Sample program for testing 'For' statement
 */

import java.util.*;
class ForTest {
    public static void main(String[] args) {
        int i;
        
        for (i = 0; i <= 10; i = i + 1) {
            System.out.print("i = ");
            System.out.println(i);
        }
        System.out.println("End of loop");
    }
}
