#include <iostream>
#include <cmath>
#include <math.h>
#include <vector>
using namespace std;

// declaration of functions before use
double myexp(double, double);

// Creating function myexp(x, tol) that calculates the approximation of the 
// exponential function using the ampunt of terms from the Maclaurin series
// that lets the approximation satisfy the required accuracy.
double myexp(double x, double tol)
{
    double S = 1; //define first term from series
    double t = x; //define first error term
    
    for (int i = 1; true; i++){
        
        S += t; //adding new terms from Maclaurin series
        t *= x/(i+1); //computing updated error term
        
        if (abs(t) < tol) { 
            
            cout << "The number of terms required: " << i << endl;
            break; //checking required accuracy
        }
    }
    return S;
}

int main()
{
	//declaration of variable before use, here choose input
	//variable for the approximations
	double x = 10;
	double tol = 1e-10;
	//printing out the exact and approximate values and corresponding errors
        cout << "The input value x is: " << x << endl;
        double F = myexp(x, tol);
	cout << "The approximated exponential from our routine: " << F << endl;
        double e = exp(x);
        cout << "The exact exponential: " << e << endl;
	return 1;
        
}
