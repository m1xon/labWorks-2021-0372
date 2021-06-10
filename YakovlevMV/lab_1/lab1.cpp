#include <iostream>

using namespace std;
using T = double;

template<typename T>
class List
{
public:
	List();
	~List();

	List(unsigned size);
	List(unsigned size, const T& value);
	void resize(unsigned re_size);
	int find(const T& value);
	bool contains(const T& value);
	void clear();
	void pop_front();
	void push_back(T value);
	int GetSize() {
		return Size;
	};

	T& operator[](unsigned index);
	void push_front(T value);
	bool insert(T value, unsigned pos);
	void removeAt(int index);
	void pop_back();
	void remove_range(int pos, int count);

private:

	template<typename T>
	class Node
	{
	public:
		Node* pNext;
		T value;
		Node(T value = T(), Node* pNext = nullptr)
		{
			this->value = value;
			this->pNext = pNext;
		}
	};

	int Size;
	Node<T>* head;
};

template<typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}

template<typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();
	}
}

template<typename T>
List<T>::List(unsigned size)
{
	Size = size;
	if (Size > 0)
	{
		head = new Node<T>{ 0, nullptr };
		Node<T>* temp = head;
		for (int i = 0; i < Size - 1; i++)
		{
			temp->pNext = new Node<T>{ 0, nullptr };
			temp = temp->pNext;
		}
	}
}

template<typename T>
List<T>::List(unsigned size, const T& value)
{
	Size = size;
	if (Size > 0)
	{
		head = new Node<T>{ value, nullptr };
		Node<T>* temp = head;
		for (int i = 0; i < Size - 1; i++)
		{
			temp->pNext = new Node<T>{ value, nullptr };
			temp = temp->pNext;
		}
	}
}

template<typename T>
void List<T>::resize(unsigned size)
{
	if (size > Size)
	{
		for (unsigned i = Size; i < size; i++) {
			push_back(0);
		}
	}
	else
		if (size < Size)
			for (unsigned i = Size; i > size; i--) {
				removeAt(Size - 1);
			}
}

template<typename T>
int List<T>::find(const T& value)
{
	Node<T>* temp = head;
	for (int i = 0; i < Size; i++)
	{
		if (temp->value == value)
			return i;
		temp = temp->pNext;
	}
	return -1;
}

template<typename T>
bool List<T>::contains(const T& value)
{
	if (this->find(value) == -1) {
		return false;
	}
	return true;
}

template<typename T>
void List<T>::pop_front()
{
	Node<T>* temp = head;
	head = head->pNext;

	delete temp;
	Size--;
}

template<typename T>
void List<T>::push_back(T value)
{
	if (head == nullptr)
	{
		head = new Node<T>(value);
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(value);
	}

	Size++;
}

template<typename T>
T& List<T>::operator[](unsigned index)
{
	int counter = 0;
	Node<T>* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->value;
		}
		current = current->pNext;
		counter++;
	}
}

template<typename T>
void List<T>::push_front(T value)
{
	head = new Node<T>(value, head);
	Size++;
}

template<typename T>
bool List<T>::insert(T value, unsigned pos)
{
	if (pos == 0)
	{
		push_front(value);
	}
	else if (pos <= GetSize())
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < pos - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(value, previous->pNext);

		previous->pNext = newNode;

		Size++;

		return true;
	}
	else
	{
		return false;
	}
}

template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		delete toDelete;
		Size--;
	}
}

template<typename T>
void List<T>::pop_back()
{
	removeAt(Size - 1);
}

template<typename T>
void List<T>::remove_range(int pos, int count)
{
	int temp_size = Size;
	if ((pos + count) <= temp_size) {
		for (int i = 0; i < count; i++) {
			removeAt(pos);
		}
	}
	else
	{
		for (int i = 0; i < temp_size; i++) {
			removeAt(pos);
		}
	}
}

void print(List<int>& List)
{
	for (int i = 0; i < List.GetSize(); i++)
	{
		cout << List[i] << " ";
	}
	cout << endl;
}

int main() {
	List<int> lst{ 5 };
	cout << "List size 5 with default value" << endl;
	print(lst);
	lst.clear();

	List<int> lst_1{ 10, 5 };
	cout << "List size 10 with value == 5" << endl;
	print(lst_1);

	cout << "Resize" << endl;
	lst_1.resize(6);
	print(lst_1);

	cout << "Size of List" << endl;
	cout << lst_1.GetSize() << endl;

	cout << "Insert" << endl;
	lst_1.insert(0, 2);
	print(lst_1);

	cout << "Push_back" << endl;
	lst_1.push_back(1);
	print(lst_1);

	cout << "Contains" << endl;
	cout << lst_1.contains(0) << endl;

	cout << "Operator" << endl;
	cout << lst_1.operator[](2) << endl;

	cout << "Find" << endl;
	cout << lst_1.find(6) << endl;

	cout << "Remove_range" << endl;
	lst_1.remove_range(3, 3);
	print(lst_1);

	return 0;
}
