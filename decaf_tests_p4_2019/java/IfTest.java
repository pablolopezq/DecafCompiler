/*******************************************
 * File: IfTest.decaf
 * A test program for if statement
 *******************************************/

import java.util.*;
class IfTest {
    public static void main(String[] args) {
        int x, y;
        
        //srand(time(0));
        
        x = 5;
        y = 7;

        System.out.print("X = ");
        System.out.print(x);
        System.out.print(" Y = ");
        System.out.println(y);

        if (x == y) {
            System.out.print ("X is equal to Y\n");
        }
        else {
            System.out.print("X is not equal to Y\n");
        }
        
        x = 456;
        y = 456;

        System.out.print("X = ");
        System.out.print(x);
        System.out.print(" Y = ");
        System.out.println(y);

        if (x == y) {
            System.out.print ("X is equal to Y\n");
        }
        else {
            System.out.print("X is not equal to Y\n");
        }
    }
}
