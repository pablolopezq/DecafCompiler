/*
 * WhileTest.decaf
 * Sample program for testing while statement
 */

import java.util.*;
class WhileTest {
    public static void main(String[] args) {
        int total;
        int count;
        int number;
        
        total = 0;
        count = 0;

        while (count < 3) {
            number = (count + 1) * 10;
            System.out.print("Number [");
            System.out.print(count);
            System.out.print("] = ");
            System.out.println(number);
            count = count + 1;
            total = total + number;
        }
        System.out.print("The total is ");
        System.out.println(total);
    }
}
