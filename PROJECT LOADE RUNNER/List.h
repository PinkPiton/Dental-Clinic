#pragma once
#include<iostream>
#include<time.h>
#include<fstream>
#include <string> 
using namespace std;
template <class T>
class List {
public: // описание структруры элемента списка

	template <class T>
	struct Element {
		T data; // пользовательские, полезные данные
		Element<T> *pNext, *pPrev;
		Element() : data(), pNext(), pPrev() {}
		Element(const T& val) : data(val), pNext(), pPrev() {}
		Element<T> * GetNext() { return pNext; }
		Element<T> * GetPrev() { return pPrev; }
		void SetNext(Element<T> * next) { pNext = next; }
		void SetPrev(Element<T> * prev) { pPrev = prev; }
		T& GetData() { return data; }
	};
private: // переменные класса - закрытые элементы класса
	Element<T> * pHead; // головной элемент списка
	Element<T> * pTail; // хвостовой элемент списка
	int cnt; // кол-во элементов
public:
	List() : pHead(), pTail(), cnt() {}
	List(const List& lst) : List() {
		Element<T> * temp = lst.pHead;
		while (temp) {
			this->Add(temp->data);
			temp = temp->pNext;
		}

	}
	List(List&& lst) {
		pHead = lst.pHead;
		pTail = lst.pTail;
		cnt = lst.cnt;
		lst.pHead = lst.pTail = nullptr;
		lst.cnt = 0;
	}
	// float mas[10]={1,2,3,4,5,6,7,8,9,10};
	// List<float> lst(mas, 10);
	// lst.setData(mas, 10);
	List(const T * mas, int size) : List() {
		setData(mas, size);
	}
	void setData(const T * mas, int size) {
		Clear();

		for (int i = 0; i < size; i++) {
			Add(mas[i]);
		}
	}
	// lst.Add(99);lst.Add(100);
	// int size;
	// float * mas2 = lst.getData(size);
	// qsort(mas2, size, sizeof(*mas2), CmpFunc);
	// lst.setData(mas2, size);
	// delete[]mas2;
	T * getData(int& size) {
		if (pHead) {
			Element<T> * temp = pHead;
			size = cnt;
			T * mas = new T[size];
			for (int i = 0; i < size; i++) {
				mas[i] = temp->data;
				temp = temp->pNext;
			}
			return mas;
		}
		else { size = 0; return nullptr; }
	}

	int getCnt() const { return cnt; }
	int getCnt_Head() const {
		Element<T> *temp = pHead;
		int cnt2 = 0;
		// обход списка в прямом направлении
		while (temp != nullptr) {
			temp = temp->pNext;
			cnt2++;
		}
		return cnt2;
	}
	int getCnt_Tail() const {
		Element<T> *temp = pTail;
		int cnt2 = 0;
		// обход списка в обратном направлении
		while (temp != nullptr) {
			temp = temp->pPrev;
			cnt2++;
		}
		return cnt2;
	}

	void Add( T& val) {
		Element<T> *temp = new Element<T>(val);
		if (pHead == nullptr) {
			pHead = pTail = temp;
		}
		else {
			temp->SetPrev(pTail);
			pTail->SetNext(temp);
			pTail = temp;
		}
		cnt++;
	}
	void Add_Head( T& val) {
		Element<T> *temp = new Element<T>(val);
		if (pHead == nullptr) {
			pHead = pTail = temp;
		}
		else {
			pHead->SetPrev(temp);
			temp->SetNext(pHead);
			pHead = temp;
		}
		cnt++;
	}
	Element<T> * Find(int index) {
		if (pHead == nullptr) return nullptr;
		Element<T> *temp = pHead;
		for (int i = 0; i < index; i++) {
			if (temp == nullptr)  return nullptr;
			temp = temp->GetNext();
		}
		return temp;
	}
	void Insert(int index,  T& val) {
		if (index <= 0) {
			Add_Head(val);
		}
		else if (index >= cnt) {
			Add(val);
		}
		else {
			//1 - variant
			Element<T> * temp = Find(index);
			Element<T>*tNext = temp;
			Element<T>*tPrev = temp->pPrev;
			Element<T> * t_new = new Element<T>(val);
			tPrev->SetNext(t_new);
			tNext->SetPrev(t_new);
			t_new->SetNext(tNext);
			t_new->SetPrev(tPrev);
			//2 - variant
		   /* t_new->pNext = temp;
			t_new->pPrev = temp->pPrev;
			temp->pPrev->pNext = t_new;
			temp->pPrev = t_new;*/
			cnt++;
		}
	}
	void Delete(int index) {
		if (!pHead)
			return;
		if (index <= 0) {
			Element<T>*temp = pHead;
			pHead = pHead->pNext;
			if (pHead)
				pHead->pPrev = nullptr;
			else
				pTail = nullptr;
			cnt--;
			delete temp;
		}
		else if (index >= cnt - 1) {
			Element<T>*temp = pTail;
			pTail = pTail->pPrev;
			if (pTail)
				pTail->pNext = nullptr;
			else
				pHead = nullptr;
			cnt--;
			delete temp;
		}
		else {
			Element<T>*temp = Find(index);
			temp->pPrev->pNext = temp->pNext;
			temp->pNext->pPrev = temp->pPrev;
			cnt--;
			delete temp;
		}
	}
	void Clear() {// Delete_All();
		while (pHead) {
			Delete(0);
		}
	}
	~List() {
		Clear();
	}

	Element<T> * getHead() { return pHead; }
	Element<T> * getTail() { return pTail; }
	Element<T> * getNext(Element<T> * el) { return el->pNext; }
	Element<T> * getPrev(Element<T> * el) { return el->pPrev; }
	Element<T> * getAt(int index) { return Find(index); }
	T& operator[](int index) {
		Element<T> * temp = getAt(index);
		if (temp != nullptr) { return temp->data; }
		cout << "Nothing here" << endl;
		throw "Nothing here";
	}
	friend ostream& operator<<(ostream& os, List<T>& lst) {
		Element<T> * temp = lst.getHead();
		if (&os == &cout) {
			while (temp) {
				os << temp->GetData() << "  |  ";
				temp = lst.getNext(temp);
			}
		}
		else {
			while (temp) {
				os << temp->data;
				temp = lst.getNext(temp);
			}
		}
		return os;
	}
	template<class T>
	friend class Queue_Prior;
};
