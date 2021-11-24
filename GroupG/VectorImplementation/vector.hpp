#pragma once

#include "../common/mem_inspect.hpp"
#include "../common/type_traits.hpp"

// if you comment out the next line, the tests will run on std::vector instead
// Make sure all tests pass on std::vector before trying to test your implementation
#define USER_VECTOR

/// Place your implementation below
/// The tests are testing not only interface but implementation details. For this to work allocation and deallocation happen in a specific way:
/// You must replace all new/delete with the following
/// T *ptr = new T[count]; -> NEW(T, count);
/// delete[] ptr; -> DELETE(ptr);

/// Example:

// inline void test_allocation() {
// 	int *arr = NEW(int, 12);
// 	for (int c = 0; c < 12; c++) {
// 		arr[c] = c;
// 	}
// 	DELETE(arr);
// }

template <typename T>
struct vector 
{
private:
	T* data = nullptr;
	int m_size = 0;
	int m_capacity = 0;

	void doResize(int newCapacity)
	{
		T* newData = NEW(T, newCapacity);
			for (int i = 0; i < this->m_size; ++i)
			{
				newData[i] = this->data[i];
			}

			DELETE(this->data);
			this->data = newData;
			this->m_capacity = newCapacity;
	}

public:
	vector<T>() = default;

	vector<T>(int count, T value = T())
	{
		this->m_capacity = count;
		this->m_size = count;
		this->data = NEW(T, this->m_capacity);

		for (int i = 0; i < count; ++i)
		{
			this->data[i] = value;
		}
	}

	vector<T>(const vector<T>& other)
	{
		if (other.m_capacity > 0)
		{
			this->m_capacity = other.m_capacity;
			this->m_size = other.m_size;
			this->data = NEW(T, this->m_capacity);

			for (int i = 0; i < this->m_size; ++i)
			{
				this->data[i] = other.data[i];
			}
		}
	}

	vector<T>& operator = (const vector<T>& other)
	{
		if (this != &other)
		{
			DELETE(this->data);
			this->m_capacity = std::max(this->m_capacity, other.m_capacity);
			this->m_size = other.m_size;

			if (this->m_capacity > 0)
			{
				this->data = NEW(T, this->m_capacity);

				for (int i = 0; i < this->m_size; ++i)
				{
					this->data[i] = other.data[i];
				}
			}
			else
			{
				this->data = nullptr;
			}
		}

		return *this;
	}

	~vector<T>()
	{
		DELETE(this->data);
	}

	void clear()
	{
		this->m_size = 0;
	}

	T& front()
	{
		assert(this->m_size > 0);
		return this->data[0];
	}

	const T& front() const
	{
		assert(this->m_size > 0);
		return this->data[0];
	}

	T& back()
	{
		assert(this->m_size > 0);
		return this->data[this->m_size-1];
	}

	const T& back() const
	{
		assert(this->m_size > 0);
		return this->data[this->m_size-1];
	}

	int size() const
	{
		return this->m_size;
	}

	int capacity() const
	{
		return this->m_capacity;
	}

	void resize(int count, T value = T())
	{
		int newCapacity = std::max(m_capacity, count);
		T* newData = NEW(T, newCapacity);

		if (count < this->m_size)
		{
			for (int i = 0; i < count; ++i)
			{
				newData[i] = this->data[i];
			}
		}
		else
		{
			for (int i = 0; i < this->m_size; ++i)
			{
				newData[i] = this->data[i];
			}
			for (int i = this->m_size; i < count; ++i)
			{
				newData[i] = value;
			}
		}

		DELETE(this->data);
		this->data = newData;
		this->m_size = count;
		this->m_capacity = newCapacity;
	}

	void reserve(int newCapacity)
	{
		if (newCapacity > this->m_capacity)
		{
			doResize(newCapacity);
		}
	}

	void shrink_to_fit()
	{
		if (this->m_size < this->m_capacity)
		{
			doResize(this->m_size);
		}
	}

	void push_back(const T& value)
	{
		if (this->m_size == this->m_capacity)
		{
			int newCapacity = (this->m_capacity == 0) ? 2 : this->m_capacity*2;
			this->reserve(newCapacity);
		}

		this->data[this->m_size++] = value;
	}

	void pop_back()
	{
		assert(this->m_size > 0);
		--this->m_size;
	}

	T& operator [] (int index)
	{
		assert(index >= 0 && index < this->m_size);
		return this->data[index];
	}

	const T& operator [] (int index) const
	{
		assert(index >= 0 && index < this->m_size);
		return this->data[index];
	}

	T& at(int index)
	{
		if (index < 0 || index >= this->m_size)
		{
			throw std::out_of_range("Invalid index");
		}
		return this->data[index];
	}

	const T& at(int index) const
	{
		if (index < 0 || index >= this->m_size)
		{
			throw std::out_of_range("Invalid index");
		}
		return this->data[index];
	}

	struct iterator
	{
	private:
		friend struct vector;
		T* pointer;
		iterator(T* pointer)
		{
			this->pointer = pointer;
		}

	public:
		T& operator * ()
		{
			return *pointer;
		}

		const T& operator * () const
		{
			return *pointer;
		}

		T* operator -> ()
		{
			return pointer;
		}

		const T* operator -> () const
		{
			return pointer;
		}

		iterator& operator ++ ()
		{
			++pointer;
			return *this;
		}

		iterator operator ++ (int)
		{
			iterator copy(*this);
			++(*this);
			return copy;
		}

		iterator& operator -- ()
		{
			--pointer;
			return *this;
		}

		iterator operator -- (int)
		{
			iterator copy(*this);
			--(*this);
			return copy;
		}

		bool operator == (const iterator& other) const
		{
			return pointer == other.pointer;
		}

		bool operator != (const iterator& other) const
		{
			return !(*this == other);
		}

		bool operator < (const iterator& other) const
		{
			return pointer < other.pointer;
		}

		bool operator > (const iterator& other) const
		{
			return pointer > other.pointer;
		}

		bool operator <= (const iterator& other) const
		{
			return pointer <= other.pointer;
		}

		bool operator >= (const iterator& other) const
		{
			return pointer >= other.pointer;
		}

		iterator& operator += (int offset)
		{
			pointer += offset;
			return *this;
		}

		iterator& operator -= (int offset)
		{
			pointer -= offset;
			return *this;
		}

		iterator operator + (int offset)
		{
			iterator copy(*this);
			copy += offset;
			return copy;
		}

		iterator operator - (int offset)
		{
			iterator copy(*this);
			copy -= offset;
			return copy;
		}

		T& operator [] (int offset) 
		{
			return *(pointer + offset);
		}

		const T& operator [] (int offset) const
		{
			return *(pointer + offset);
		}
	};

	iterator begin()
	{
		return iterator(this->data);
	}

	iterator end()
	{
		return iterator(this->data + this->m_size);
	}

	bool empty()
	{
		return this->begin() == this->end();
	}

	void insert(iterator pos, const T& value)
	{
		if (pos == this->end() && this->m_size == this->m_capacity)
		{
			int newCapacity = (this->m_capacity == 0) ? 2 : this->m_capacity * 2;
			this->reserve(newCapacity);
		}

		for (iterator it = this->end(); it != pos; --it)
		{
			*it = *(it - 1);
		}
		*pos = value;
		++this->m_size;
	}

	void erase(iterator pos)
	{
		this->erase(pos, pos + 1);
	}

	void erase(iterator first, iterator last)
	{
		int difference = last.pointer - first.pointer;

		for (iterator it = first; it != this->end(); ++it)
		{
			*it = *(it + difference);
		}

		this->m_size -= difference;
	}
};
