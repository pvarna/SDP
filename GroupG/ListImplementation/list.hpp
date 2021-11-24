#pragma once

#include <cassert>
#include "../common/mem_inspect.hpp"

// Uncomment to test this list
#define USER_LIST

// use NEW(Type, count) for allocation
// use DELETE(ptr) for deallocation

// Uncomment if you allocate dynamic dummy node, example: this->dummy = NEW(Node, 1)
// #define LIST_EXTRA_ELEMENT

template <typename T>
struct list 
{
	struct Node 
	{
		Node *next = nullptr;
		Node *prev = nullptr;
		T data;
	};

private:
	Node dummy;
	int count;

	void remove(Node* toRemove)
	{
		toRemove->prev->next = toRemove->next;
		toRemove->next->prev = toRemove->prev;

		DELETE(toRemove);

		--this->count;
	}

	void insertBefore(Node* next, const T& toInsert)
	{
		Node* toAdd = NEW(Node, 1);
		toAdd->data = toInsert;

		toAdd->next = next;
		toAdd->prev = next->prev;

		toAdd->next->prev = toAdd;
		toAdd->prev->next = toAdd;

		++this->count;
	}

	void insertAfter(Node* prev, const T& toInsert)
	{
		Node* toAdd = NEW(Node, 1);
		toAdd->data = toInsert;

		toAdd->prev = prev;
		toAdd->next = prev->next;

		toAdd->next->prev = toAdd;
		toAdd->prev->next = toAdd;

		++this->count;
	}

	void copy(const list<T>& other)
	{
		Node* current = other.dummy.next;

		while (current != &other.dummy)
		{
			insertBefore(&this->dummy, current->data);
			current = current->next;
		}
	}

	Node* getPosToInsert(Node* toInsert)
	{
		Node* result = &this->dummy;
		while (result->next != &this->dummy && result->next->data < toInsert->data)
		{
			result = result->next;
		}

		return result;
	}

	Node* detachFirst()
	{
		Node* result = this->dummy.next;

		this->dummy.next = result->next;
		result->next->prev = &this->dummy;

		--this->count;

		return result;
	}

public:
	list()
	{
		this->dummy.next = &dummy;
		this->dummy.prev = &dummy;

		this->count = 0;
	}

	list(const int& count, const T& value = T()) : list()
	{
		while (this->count < count)
		{
			this->insertBefore(&this->dummy, value);
		}
	}

	list(const list<T>& other) : list()
	{
		this->copy(other);
	}

	list& operator = (const list<T>& other)
	{
		if (this != &other)
		{
			this->clear();
			this->copy(other);
		}

		return *this;
	}

	~list()
	{
		this->clear();
	}

	void clear()
	{
		while (this->count)
		{
			this->remove(dummy.next);
		}
	}

	int size()
	{
		return this->count;
	}

	T& front()
	{
		assert(this->count > 0);
		return this->dummy.next->data;
	}

	const T& front() const
	{
		assert(this->count > 0);
		return this->dummy.next->data;
	}

	T& back()
	{
		assert(this->count > 0);
		return this->dummy.prev->data;
	}

	const T& back() const
	{
		assert(this->count > 0);
		return this->dummy.prev->data;
	}

	void push_back(const T& value)
	{
		this->insertBefore(&this->dummy, value);
	}

	void push_front(const T& value)
	{
		this->insertAfter(&this->dummy, value);
	}

	void pop_back()
	{
		assert(this->count > 0);
		this->remove(this->dummy.prev);
	}

	void pop_front()
	{
		assert(this->count > 0);
		this->remove(this->dummy.next);
	}

	bool empty()
	{
		return this->count == 0;
	}

	struct iterator
	{
		friend struct list;

		private:
		Node* pointer;

		public:
		iterator(Node* pointer) : pointer(pointer) {}

		T& operator * ()
		{
			return this->pointer->data;
		}

		const T& operator * () const
		{
			return this->pointer->data;
		}

		T* operator -> ()
		{
			return &this->pointer->data;
		}

		const T* operator -> () const
		{
			return &this->pointer->data;
		}

		iterator& operator ++ ()
		{
			pointer = pointer->next;

			return *this;
		}

		iterator operator ++ (int)
		{
			iterator copy(*this);
			this->pointer = this->pointer->next;
			
			return copy;
		}

		iterator& operator -- ()
		{
			pointer = pointer->prev;

			return *this;
		}

		iterator operator -- (int)
		{
			iterator copy(*this);
			this->pointer = this->pointer->prev;
			
			return copy;
		}

		bool operator == (const iterator& other) const
		{
			return this->pointer == other.pointer;
		}

		bool operator != (const iterator& other) const
		{
			return !(*this == other);
		}
	};

	iterator begin()
	{
		assert(this->count > 0);
		return iterator(this->dummy.next);
	}

	iterator end()
	{
		assert(this->count > 0);
		return iterator(&this->dummy);
	}

	void insert(iterator pos, const T& value)
	{
		this->insertBefore(pos.pointer, value);
	}

	void erase(iterator start, iterator end)
	{
		list<T>::iterator current = start;
		while (current != end)
		{
			list<T>::iterator next = iterator(current.pointer->next);
			this->remove(current.pointer);
			current = next;
		}
	}

	void erase(iterator start)
	{
		this->remove(start.pointer);
	}

	void splice(iterator pos, list<T>& other)
	{
		Node* next = pos.pointer;
		Node* prev = next->prev;

		Node* firstToAdd = other.dummy.next;
		Node* lastToAdd = other.dummy.prev;

		firstToAdd->prev = prev;
		lastToAdd->next = next;

		prev->next = firstToAdd;
		next->prev = lastToAdd;

		other.dummy.next = &other.dummy;
		other.dummy.prev = &other.dummy;

		this->count += other.count;

		other.count = 0;
	}

	void merge(list<T>& other)
	{
		while (!other.empty())
		{
			Node* current = other.detachFirst();
			Node* prev = this->getPosToInsert(current);
			Node* next = prev->next;

			current->prev = prev;
			current->next = next;

			prev->next = current;
			next->prev = current;

			++this->count;
		}
	}

	void unique()
	{
		Node* current = this->dummy.next;

		while (current->next != &this->dummy)
		{
			if (current->data == current->next->data)
			{
				this->remove(current->next);
				current = current->prev;
			}

			current = current->next;
		}
	}
};