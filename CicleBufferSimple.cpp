#include <iostream>
using namespace std;


template<typename Type, size_t n> 

class CircleBuffer {
	public:
		static const size_t size = n;
		const Type notSetVal;
    private:
    	Type buffer[size];
        size_t order = -1;

    public:
		CircleBuffer(Type notSetValue) : notSetVal(notSetValue) {
			for(int i = 0; i < size; i++)
				buffer[i] = notSetVal;
		}
		
        void Add(Type newVal) {
            order++;
			if (order >= size)
				order = 0;
            buffer[order] = newVal;
        }
        
        Type GetLast() {
			if (order != -1)
				return buffer[order];
			else {
		        cout << "Wasn`t set";
				return notSetVal;
		    }
        }
        
		Type GetAt(int orderToGive) {
		    if ((orderToGive < 0) or (orderToGive+1 > size)) {
		        cout << "Wrong order";
		        return notSetVal;
		    }
			orderToGive = order - orderToGive;
			if (orderToGive < 0)
				orderToGive += size;
			return buffer[orderToGive];
		}
};


int main()
{
	/*CircleBuffer<int, 780> CB(0);
	for (size_t i = 0; i <780; i++) {
		CB.Add(-i);
		cout << CB.GetLast();
	}
	for (size_t i = 0; i < 780; i++)
		cout << CB.GetAt(i);
	cout << "Int end!";*/
	CircleBuffer<double, 4> dbCB(0);
	dbCB.Add(-1.1);
	cout << dbCB.GetLast();
	dbCB.Add(-2);
	cout << dbCB.GetLast();
	dbCB.Add(-3.5);
	cout << dbCB.GetLast();
	dbCB.Add(-4);
	cout << dbCB.GetLast();
	dbCB.Add(-5);
	cout << dbCB.GetLast();
	dbCB.Add(-6.7);
	cout << dbCB.GetLast();
	dbCB.Add(-7);
	cout << dbCB.GetLast();
	dbCB.Add(-8);
	cout << dbCB.GetLast();
	dbCB.Add(-9.12);
	cout << dbCB.GetLast();
	dbCB.Add(-10);
	cout << dbCB.GetLast();
	dbCB.Add(-11);
	cout << dbCB.GetLast();
	for (size_t i = 0; i < 6; i++)
		cout << dbCB.GetAt(i);
	cout << "Int end!";
}