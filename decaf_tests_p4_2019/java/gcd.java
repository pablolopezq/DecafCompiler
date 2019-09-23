import java.util.*;
class GreatestCommonDivisor
{
	static int a = 10;
	static int b = 20;

	public static void main(String[] args)
	{
		int x, y, z;
		x = a;
		y = b;
		z = gcd(x, y);

		System.out.println(z);
	}

	// Funcion que calcula el maximo comun divisor
	static int gcd(int a, int b)
	{
		if (b == 0) {
			return (a);
		} else {
			return (gcd(b, a % b));
		}
	}
}
