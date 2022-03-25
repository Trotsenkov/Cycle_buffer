#include <iostream>
#include <array>
using namespace std;


template<typename Type> 

class CircleIterator {
	private:
		Type* value;
		CircleIterator* previous;
	public:
		CircleIterator(Type Val, CircleIterator* prev) : value(new Type(Val)), previous(prev) { }
		CircleIterator(Type Val) : CircleIterator(Val, this) { }
		
		CircleIterator<Type> operator++ (int) {
			*this = *previous;
			return *this;
		}
		
		Type GetValue() {
			return *value;
		}
		void SetValue(Type Val) {
			*value = Val;
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
		
		CircleBuffer<Type> operator+ (CircleBuffer<Type> &obj) {
			CircleBuffer<Type> result;
			result = *this;
			CircleBuffer<Type> temp;
			temp.Add(obj.begin().GetValue());
			for(CircleIterator<Type> i = obj.end(); i.GetPrevious() != obj.begin().GetPrevious(); i++)
				temp.Add(i.GetValue());
			result.Add(temp.begin().GetValue());
			for(CircleIterator<Type> i = temp.end(); i.GetPrevious() != temp.begin().GetPrevious(); i++)
				result.Add(i.GetValue());
			return result;
		}
		
		CircleBuffer<Type> operator+= (CircleBuffer<Type> &obj) {
			CircleBuffer<Type> temp;
			temp.Add(obj.begin().GetValue());
			for(CircleIterator<Type> i = obj.end(); i.GetPrevious() != obj.begin().GetPrevious(); i++)
				temp.Add(i.GetValue());
			this->Add(temp.begin().GetValue());
			for(CircleIterator<Type> i = temp.end(); i.GetPrevious() != temp.begin().GetPrevious(); i++)
				this->Add(i.GetValue());
			return *this;
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
	CB0.Add(3);
	CB0.Add(4);
	CB0.Add(5);
	CircleBuffer<int> CB1;
	CB1.Add(6);
	CB1.Add(7);
	CB1.Add(8);
	CB1.Add(9);
	CircleBuffer<int> CB2;
	CB2.Add(1);
	CB2.Add(2);
	CircleIterator<int> _val = CB0.end();
	//_val.SetValue(1);
	for(size_t i = 0; i < 15; i++) {
		cout << _val.GetValue();
		_val++;
	}
	
	cout << endl;
	
	_val = CB1.end();
	for(size_t i = 0; i < 15; i++) {
		cout << _val.GetValue();
		_val++;
	}
	
	cout << endl;
	
	CircleBuffer<int> CBz = CB0 + CB1;
	_val = CBz.end();
	for(size_t i = 0; i < 15; i++) {
		cout << _val.GetValue();
		_val++;
	}
	cout << endl;
	CBz += CB2;
	_val = CBz.end();
	for(size_t i = 0; i < 15; i++) {
		cout << _val.GetValue();
		_val++;
	}
}