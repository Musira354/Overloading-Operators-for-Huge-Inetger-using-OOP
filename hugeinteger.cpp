#include "hugeinteger.h"
#include <iostream>

using namespace std;

int main() {
	
	

	/*while (a - k * b >= b)
		++k;

	return a - k * b;*/

	/*while (a > b)
	{
		r = a % b;
		count ++;
	}
	cout << a;*/
	hugeinteger h1,h2;
	cin >> h1;
	cout << endl<<h1;
	
	cin >> h2;
	cout << endl<<h2;
	cout<< endl<<" (h1==h2) = "<<(h1 == h2) << "\n";
	cout <<endl<<" (h1!=h2) = "<< (h1 != h2) << "\n";
	cout <<endl<<" (h1<h2 = )"<< (h1 < h2) << "\n";
	cout << endl<<" (h1>h2 = )"<<(h1 > h2) << "\n";
	cout <<endl<<" (h1<=h2) = "<< (h1 <= h2) << "\n";
	cout << endl << " (h1>=h2) = " << (h1 >= h2) << "\n";

	cout << "Sum of two huge integers is : ";
	hugeinteger h = (h1 + h2);
	cout << h;
	cout << "Difference of two huge integers is : ";
	h = (h1-h2);
	cout << h;
	cout << "Product of two huge integers is : ";
	h = (h1 * h2);
	cout << h;
	
	cout << "Division of two huge integers is : ";
	hugeinteger h3 = (h1 / h2);
	cout << h3;
	
	h=squareRoot(h);
	cout <<"square = "<< h;

	return 0;
}
