#include <iostream>
#include <array>
using namespace std;


template<typename Type> 

class CircleIterator {
	private:
		Type value;
		CircleIterator* previous;
	public:
		CircleIterator(Type Val, CircleIterator* prev) : value(Val), previous(prev) { }
		CircleIterator(Type Val) : CircleIterator(value, this) { }
		
		CircleIterator<Type> operator++ (int) {
			*this = *previous;
			return *this;
		}
		
		Type GetValue() {
			return value;
		}
		void SetValue(Type value) {
			this->value = value;
		}
		CircleIterator* GetPrevious() {
			return previous;
		}
};


template<typename Type>

class CircleBuffer {
	private:
		size_t size = 0;
		CircleIterator<Type> *first = NULL;
		
	public:
		void Add(Type value) {
			size++;
			if (first == NULL) {
				first = new CircleIterator<Type>(value);
				return;
			}
			*first = CircleIterator<Type>(first->GetValue(), new CircleIterator<Type>(value, first->GetPrevious()));
		}
		
		void Pop() {
			if (size <  1)
				return;
			if (size == 1) {
				delete first;
				first = NULL;
			}
			CircleIterator<Type> *temp = first;
			for(size_t i = 0; i < size-1; i++) 
				temp = temp->GetPrevious();
				
			*temp = CircleIterator<Type>(temp->GetValue(), first->GetPrevious());
			delete first;
			first = temp;
			size--;
		}
		
		Type GetValue() {
				return first->GetPrevious()->GetValue();
		}
		
		CircleIterator<Type> end() {
			return *first->GetPrevious();
		}
		CircleIterator<Type> begin() {
			return *first;
		}
};

int main(int argc, char *argv[])
{
	CircleBuffer<int> CB0;
	CB0.Add(4);
	CB0.Add(5);
	CB0.Add(6);
	CB0.Add(7);
	CB0.Pop();
	CB0.Pop();
	CB0.Add(8);
	CB0.Add(9);
	CircleIterator<int> _val = CB0.end();
	for(size_t i = 0; i < 25; i++) {
	cout << _val.GetValue();
	_val++;
	}
}