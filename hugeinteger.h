
#include <iostream>
#include <string>
#include<cstring>
#include<stdio.h> 
#include<string.h>

using namespace std;

class hugeinteger
{
private:
	char* data;
	int size;
public:
	//given functions
	hugeinteger() {	
		data = 0;
		size = 0;
	}

	hugeinteger(const hugeinteger& obj) {		//COPY CONSTRUCTOR	
		this->data = new char[obj.size];
		this->data = obj.data;
		this->size = obj.size;
	}

	hugeinteger(int size) {
		this->size = size;
		this->data = new char[size];
	}

	~hugeinteger() {
		delete[]data;
	}

	//AWEIN FUNCTION 
	friend int equal(const hugeinteger& obj1, const hugeinteger& obj2) {
		bool equal = true; int i = 0;
		if (obj1.size == obj2.size) {  //checks the same digits
			for (i = 0; i < obj1.size && equal == true;i++ ) {
				if (obj1.data[i] != obj2.data[i]) {
					equal = false;
				}			
			}
		}
		if (obj1.size > obj2.size) {		//give the index where objects has different digits
			i=0;
		} else if(obj1.size < obj2.size) {
			i=1;
		}
		return i;
	}
	friend void integerConverter(int a[225], const hugeinteger& obj1) {
		for (int i = 0; i < obj1.size; i++) {	//stores int array after coverting 
			a[i] = obj1.data[i] - '0';
		}
	}

	friend void reverseRestore(int a[225], const hugeinteger& obj3, int k) {
		int i = 0;
		for (; i < obj3.size; i++, k--) {
			obj3.data[i] = a[k] + '0';
		}
		obj3.data[i] = '\0';
	}

	friend istream& operator>> (istream& in, hugeinteger& obj) {
		cout << endl << "Enter size of huge integer = ";
		in >> obj.size;
		obj.data = new char[obj.size];
		cout << "\nEnter HugeInteger = ";
		in >> obj.data; cout << endl;
		int b = strlen(obj.data);
		bool zero = true; int count = 0; int i = 0, j = 0;
		for (int i = 0; i <b && zero == true; i++) {
			if ((obj.data[i] == '0' ) && zero == true) {	//count of zeroes at the left side of the number
				count++;
			}
			if (obj.data[i+1]!='0' && i<b-1 ) {
				zero = false;
			}
		}
		for (i = 0, j = count; j < b && count!=0; i++, j++) {	//removing zeros at left side
			obj.data[i] = obj.data[j];
		}
		b = strlen(obj.data)-count;
		obj.data[i] = obj.data[j];
		obj.size = b;
		cout << endl << "New Size Of HugeInteger = " << b << endl;

		return in;
	};

	friend ostream& operator<< (ostream& out, hugeinteger& obj) {
		for (int i = 0; i < strlen(obj.data); i++) {	
			out << obj.data[i] << " ";
		} out << endl;
		return out;
	}
	friend bool operator== (const hugeinteger& obj1, const hugeinteger& obj2) {	
		if (obj1.size == obj2.size) {
			for (int i = 0; i < obj1.size; i++) {
				if (obj1.data[i] != obj2.data[i]) {	return false; }
			}
		}
		if (obj1.size != obj2.size) {	
			return false; 
		}
		return true;		
	}

	friend bool operator!= (const hugeinteger& obj1, const hugeinteger& obj2) {

		if (obj1.size == obj2.size) {
			for (int i = 0; i < obj1.size; i++) {
				if (obj1.data[i] != obj2.data[i]) {		//checks the first an equal digit
					return true;
				}
			}
		}
		if (obj1.size != obj2.size) {	return true; }
		return false;
	}

	friend bool operator < (const hugeinteger& obj1, const hugeinteger& obj2) {	
		int i = equal(obj1, obj2);
		if (obj1.data[i - 1] < obj2.data[i - 1] || obj1.size < obj2.size) {
			return true;
		}
		return false;
	}

	friend bool operator > (const hugeinteger& obj1, const hugeinteger& obj2) {
		int i = equal(obj1, obj2);
		if (obj1.data[i - 1] > obj2.data[i - 1] || obj1.size > obj2.size) {	//checks the first unequal digit is less or not 
			return true;
		}
		
		return false;
	}

	friend bool operator <=(const hugeinteger& obj1, const hugeinteger& obj2) {
		if (obj1 < obj2 || obj1 == obj2) {
			return true;
		}
		else {
			return false;
		}
		//int i = equal(obj1, obj2);
		//if (((obj1.data[i - 1] < obj2.data[i - 1]) && obj1.size<obj2.size)|| obj1.size < obj2.size || i>1) {	//checks the first unequal digit is less or not 
		//	return true;
		//}else {
		//	return false;
		//}

	}

	friend bool operator >=(const hugeinteger& obj1, const hugeinteger& obj2) {
		if (obj1 > obj2 || obj1 == obj2) {
			return true;
		}
		else {
			return false;
		}
		//int i = equal(obj1, obj2);	//returns i=0 if length of obj1 is greater straight
		//if ((obj1.data[i - 1] > obj2.data[i - 1] && obj1.size==obj2.size) || obj1.size > obj2.size || i>1) {	//checks the first unequal digit is less or not 
		//	return true;
		//}else {
		//	return false;
		//}
	}
	
	friend hugeinteger operator + (const hugeinteger& obj1, const hugeinteger& obj2) {
		int i1[255], i2[255], add[255], carry = 0 ;
		integerConverter(i1, obj1);
		integerConverter(i2, obj2);
	
		int  i = obj1.size-1, j = obj2.size-1, k = 0;
		for (; i >= 0 && j >= 0; i--, j--, k++) {		//adding the numbers
			add[k] = (i1[i] + i2[j] + carry) % 10;
			carry = (i1[i] + i2[j] + carry) / 10;
		}
		if (i > j) {	//decides whose size is greter
			for (;  i >= 0; i--, k++) {	//adding the carry to remaining digits
				add[k] = (i1[i] + carry) % 10;
				carry = (i1[i] + carry) / 10;
			}
		}
		else if (j > i) {
			for (;  j >= 0; j--, k++) {	//adding the carry to remaining digits
				add[k] = (i2[j] + carry) % 10;
				carry = (i2[j] + carry) / 10;
			}
		}else {
			if (carry > 0) {
				add[k++] = carry;
			}
		}
		hugeinteger obj3(k);	k--;
		reverseRestore(add, obj3, k);

		return obj3;
	}
	friend hugeinteger operator - (const hugeinteger& obj1, const hugeinteger& obj2) {
		int i1[255], i2[255], sub[255], carry = 0, borrow = 10;
		integerConverter(i1,obj1);
		integerConverter(i2, obj2);

		int  i = obj1.size - 1, j = obj2.size - 1, k = 0;
		for (; i >= 0 && j >= 0; i--, j--, k++) {		//subtracting the numbers
			if (i != 0) {
				i1[i - 1]--;
			}
			else { borrow = 0; }
			sub[k] = ((borrow + i1[i]  + carry) - i2[j] )% 10;
			carry = ((borrow + i1[i] + carry) - i2[j]) / 10;
		}
		if (carry != 0) {
			sub[k++] = carry;
		}

		hugeinteger obj3(k); k--;
		reverseRestore(sub, obj3, k);	//stores the result in obj3	
		if (obj1 <= obj2) {
			obj3.size = 1;
		}
		return obj3;
	}
	friend hugeinteger operator * (const hugeinteger& obj1, const hugeinteger& obj2) {
		int i1[255], i2[255], mul[50][50], carry = 0;
		integerConverter(i1, obj2);//
		integerConverter(i2, obj1);
	
		int  i = obj2.size - 1, j = obj1.size - 1, k = 0, h = 0;
		for (i = obj2.size - 1; i >= 0; i--) {//multiply with on digit and put rowize in mul array
			for (j = obj1.size - 1; j >= 0; j--) {			
				if (j > 0) {
					mul[i][j] = ((i1[i] * i2[j]) + carry) % 10;
					h = ((i1[i] * i2[j]) + carry) / 10;
					carry = h;
				}else if (j == 0) {
					mul[i][j] = ((i1[i] * i2[j])+carry);	carry = 0;
				}			
			}
		}
		 
		 int mul2[255] = {}; carry = 0; int p = 0, x = 1;
		 i = obj2.size - 1, j = obj1.size - 1;	//i index for first number and j for the second
			for (i= obj2.size - 1-1; i >= 0 ; i--,x++) {	//puts zero where it should be cross X
				for ( p = j+x; p >j ; p--) {	//x increases with the number of rows
					mul[i][p] = 0;
				}
			}
			p = obj2.size - 1;
			for (j = obj1.size - 1 + p; j >= 0;j--) {
				//add the multiplied rows
				for (int m=0,l=j; m <= obj2.size-1 && l >=0 ; m++, l--) {
					h = (mul2[k] + mul[m][l]);
					mul2[k] = h;	
				}

				mul2[k] = (h) % 10;
				carry = (h) / 10;
				k++;
				mul2[k] = mul2[k] + carry;
			}	

			hugeinteger obj3(k--);
			reverseRestore(mul2, obj3,k);
		return obj3;
	}

	hugeinteger operator%(hugeinteger& obj2) {
		if (size == 0) {
			return obj2;
		}
		if (obj2.size == 0) {
			return *this;
		}
		hugeinteger temp = (*this - obj2);
		
		return temp;
	}

	friend hugeinteger divisionByonedigit(hugeinteger& obj1 ,int a) {
		// As result can be very large store it in string 
		//string ans;
		hugeinteger obj3(10);
	
		// Find prefix of number that is larger 
		// than divisor. 
		int i = 0;
		int temp = obj1.data[i] - '0';
		while (temp < a) {
			temp = temp * 10 + (obj1.data[++i] - '0');
		}
			

		// Repeatedly divide divisor with temp. After  
		// every division, update temp to include one  
		// more digit. 
		while (obj1.size > i)
		{
			// Store result in answer i.e. temp / divisor 
			obj3.data[i] += ((temp / a) + '0');
			
			// Take next digit of number 
			temp = (temp % a) * 10 + obj1.data[++i] - '0';
		}

		// If divisor is greater than number 
		//if (ans.length() == 0)
			

		// else return ans 
		
		return obj3;
	}
	friend hugeinteger operator/(hugeinteger &obj1,hugeinteger& obj2) {
		cout << endl;
		hugeinteger result(1);
		result.data[0] = '1';
		result.data[1] = '\0';
		
		hugeinteger one(1);
		one.data[0] = '1';
		one.data[1] = '\0';
		
		hugeinteger real = obj1;
		
		while (real > obj2 && real >= (one - one)) {
			real = real % obj2;
			result = (result+ one);	//increases 	
		}
		return result;
	}

	friend hugeinteger squareRoot(hugeinteger& obj1)
	{
		hugeinteger zero(1);
		zero.data[0] = '1';
		zero.data[1] = '\0';

		hugeinteger two(1);
		two.data[0] = '2';
		two.data[1] = '\0';

		hugeinteger one(1);
		one.data[0] = '1';
		one.data[1] = '\0';

		hugeinteger old =zero;
		hugeinteger neww= obj1;

		while ((neww - old) >= one)
		{
			old = neww;
			hugeinteger div = (obj1 / old);
			//neww = (old + div) / two;
		}
		return neww;
	}
	
};

