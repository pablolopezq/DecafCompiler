import java.util.*;
class Factorial
{
	public static void main(String[] args)
	{
		int x;

		x = factorial(6);

		System.out.print("Factorial de \"5\" = ");
		x = factorial(5);
		System.out.println(x);
		System.out.print("Factorial de \"6\" = ");
		x = factorial(6);
		System.out.println(x);
		System.out.print("Factorial de \"7\" = ");
		x = factorial(7);
		System.out.println(x);
	}

	// Funcion que calcula el factorial
	static int factorial(int n)
	{
		if (n == 0) {
			return (1);
		} else {
			return n * factorial(n-1);
		}
	}
}
