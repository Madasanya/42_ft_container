#pragma once

#include <memory>
#include "iterator.hpp"
#include <exception>
#include <limits>
#include "utils.hpp"
#include <iostream>
#include <stdexcept>

#define VECTOR_COMMENTS 0

namespace ft
{
	template<typename T, typename Allocator = std::allocator<T> >
	struct vectorBase
	{
		typedef typename Allocator::pointer pointer;
		
		struct vectorBaseData : public Allocator
		{
			pointer start;
			pointer finish;
			pointer endOfStorage;

			vectorBaseData()
				: start(), finish(), endOfStorage() { }

			vectorBaseData(Allocator const& a) throw()
				: Allocator(a) , start(), finish(), endOfStorage() { }
		};
	protected:
		pointer dataAllocation(size_t n)
		{
			return (n != 0 ? getAllocator().allocate(n) : pointer());
		}

		void dataDeallocation(pointer ptr, size_t n)
		{
			if (ptr)
				getAllocator().deallocate(ptr, n);
		}

	private:
		void createStorage(size_t n)
		{
			this->vectorBaseVar.start = this->dataAllocation(n);
			this->vectorBaseVar.finish = this->vectorBaseVar.start;
			this->vectorBaseVar.endOfStorage = vectorBaseVar.start + n;
		}

	public:
		void swapData(vectorBaseData& x)
		{
			if (VECTOR_COMMENTS)
				std::cout << "vectorBase swapData() called" << std::endl;
			std::swap(this->vectorBaseVar.start, x.start);
			std::swap(this->vectorBaseVar.finish, x.finish);
			std::swap(this->vectorBaseVar.endOfStorage, x.endOfStorage);
		}

	public:
		vectorBase()
			: vectorBaseVar()
		{
			if (VECTOR_COMMENTS)
				std::cout << "vectorBase default constructor called on " << std::endl;
		}

		vectorBase(const Allocator& a) throw()
			: vectorBaseVar(a) { }

		vectorBase(size_t n)
			: vectorBaseVar()
		{
			createStorage(n);
		}

		vectorBase(const Allocator& a, typename Allocator::size_type n)
			: vectorBaseVar(a)
		{
			createStorage(n);
		}
		
		~vectorBase() throw()
		{
			if (VECTOR_COMMENTS)
				std::cout << "vectorBase destructor called on " << this << " with " << this->vectorBaseVar.start << " to " << this->vectorBaseVar.finish << std::endl;
			dataDeallocation(vectorBaseVar.start, vectorBaseVar.finish - vectorBaseVar.start);
		}

		Allocator getAllocator() const throw()
		{
			return Allocator(allocReturn()) ; 
		}

	protected:
		Allocator& allocReturn() throw()
		{
			return this->vectorBaseVar;
		}

		const Allocator& allocReturn() const 
		{
			return this->vectorBaseVar;
		}

	public:
		vectorBaseData vectorBaseVar;

	};

	template<typename T, typename Allocator = std::allocator<T> >
	class vector: private vectorBase<T, Allocator>
	{
	protected:
		using typename vectorBase<T, Allocator>::vectorBaseData;
		using vectorBase<T, Allocator>::getAllocator;

	public:
		typedef typename Allocator::value_type						value_type; // T would also be possible
		typedef typename Allocator::reference						reference;
		typedef typename Allocator::const_reference					const_reference;
		typedef typename Allocator::pointer							pointer;
		typedef typename Allocator::const_pointer					const_pointer;
		typedef typename ft::vectorIterator<pointer>				iterator;
		typedef typename ft::vectorIterator<const_pointer>			const_iterator;
		typedef ft::reverse_iterator<iterator>						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>				const_reverse_iterator;
		typedef typename Allocator::difference_type					difference_type;
		typedef typename Allocator::size_type						size_type;
		typedef Allocator											allocator_type;
	private:
		typedef vector&												vec_reference;
		

// COPLIEN //

	public:
		explicit vector (const Allocator& alloc = Allocator()) throw();//reference pages
		explicit vector (size_type n, const value_type& val = value_type(), const Allocator& alloc = Allocator());
		template <typename InputIterator>
		vector(InputIterator first, InputIterator last, const Allocator& alloc = Allocator(), typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);
		vector (const vector& x);
		~vector() throw();
		vec_reference operator=(const vector& rhs);

	private:
		void destroyElements();

// CAPACITY //

	public:
		size_type size() const throw();
		size_type max_size() const throw();
		bool empty() const throw();
		void resize (size_type n, value_type val = value_type());
		size_type capacity() const throw();
		void reserve(size_type n);

// ITERATORS //

		iterator begin() throw();
		const_iterator begin() const throw();
		reverse_iterator rbegin() throw();
		const_reverse_iterator rbegin() const throw();
		iterator end() throw();
		const_iterator end() const throw();
		reverse_iterator rend() throw();
		const_reverse_iterator rend() const throw();

// ELEMENT ACCESS //

		reference front() throw();
		const_reference front() const throw();
		reference back() throw();
		const_reference back() const throw();
		reference operator[] (size_type idx) throw();
		const_reference operator[] (size_type idx) const throw();
		reference at(size_type n);
		const_reference at(size_type n) const;


// MODIFIERS //

		template<typename InputIterator>
		void assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);
		void assign (size_type n, const value_type& val);
		iterator insert (iterator position, const value_type& val);
		void insert (iterator position, size_type n, const value_type& val);
		template<typename InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type* = 0);
		iterator erase (iterator position);
		iterator erase (iterator first, iterator last);
		void push_back(const T& x);
		void pop_back() throw();
		void clear() throw();
		void swap(vector& x) throw();

	private:
		size_t capacityCalc (difference_type distance);
		void erase_handler(difference_type distance, iterator position);


// OBSERVERS //

	public:
		allocator_type get_allocator() const;
	};

////////////////////////////////////////////////////
//**************** COPLIEN FORM *****************//
//////////////////////////////////////////////////

	//1)
	template<typename T, typename Allocator>
	ft::vector< T, Allocator>::vector (const Allocator& alloc) throw()//reference pages 
		: vectorBase<T, Allocator>(alloc, 0)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector default constructor called" << std::endl;
	};

	//2)
	template<typename T, typename Allocator>
	ft::vector< T, Allocator>::vector (size_type n, const value_type& val, const Allocator& alloc)
		:vectorBase<T, Allocator>(alloc, n)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector fill constructor called" << std::endl;
		std::uninitialized_fill(this->vectorBaseVar.start, this->vectorBaseVar.start + n, val);
		this->vectorBaseVar.finish = this->vectorBaseVar.start + n;
	};

	//range constructor
	template<typename T, typename Allocator>
	template <typename InputIterator>
	ft::vector< T, Allocator>::vector(InputIterator first, InputIterator last, const Allocator& alloc, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
		: vectorBase<T, Allocator>(alloc, ft::distance(first, last))
	{
		if(VECTOR_COMMENTS == 1)
			std::cout << "Vector range constructor called" << std::endl;
		std::uninitialized_copy(first, last, this->vectorBaseVar.start);
		this->vectorBaseVar.finish += ft::distance(first, last); 
	}

	//4)
	template<typename T, typename Allocator>
	ft::vector< T, Allocator>::vector (const vector& x)
		:vectorBase<T, Allocator>(x.getAllocator(), x.capacity())
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector copy constructor called from " << &x << " on " << this << std::endl;
		std::uninitialized_copy(x.vectorBaseVar.start, x.vectorBaseVar.finish, this->vectorBaseVar.start);
		this->vectorBaseVar.finish = this->vectorBaseVar.start + x.size();
	};

	template<typename T, typename Allocator>
	ft::vector< T, Allocator>::~vector() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector destructor called on " << this << std::endl;
		destroyElements();
	};

	template<typename T, typename Allocator>
	typename ft::vector< T, Allocator>::vec_reference ft::vector< T, Allocator>::operator=(const vector& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector copy assignement operator called from " << &rhs << " on " << this << std::endl;
		// create temporary copy, but not with copy constructor, as this would differ in the capacity of vector compared to original container
		if (this == &rhs)
			return *this;
		vectorBase<T, Allocator> temp(this->capacity() < rhs.size() ? rhs.size() : this->capacity());
		temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
		std::uninitialized_copy(rhs.vectorBaseVar.start, rhs.vectorBaseVar.finish, temp.vectorBaseVar.start); // copy the elements of rhs into a temporary 
		temp.vectorBaseVar.finish = temp.vectorBaseVar.start + rhs.size();
		this->destroyElements();
		temp.swapData(this->vectorBaseVar);
		return(*this);
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::destroyElements()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector destroyElements() called" << std::endl;
		for (T* elem = this->vectorBaseVar.start; elem != this->vectorBaseVar.finish; ++elem)
		{
			if (VECTOR_COMMENTS)
				std::cout << elem << std::endl;
			this->getAllocator().destroy(elem);
		}
	}

////////////////////////////////////////////////////
//****************** ITERATORS ******************//
//////////////////////////////////////////////////

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::iterator ft::vector< T, Allocator>::begin() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector begin() called" << std::endl;
		return (iterator(this->vectorBaseVar.start));
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_iterator ft::vector< T, Allocator>::begin() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const begin() called" << std::endl;
		return (const_iterator(this->vectorBaseVar.start));
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::reverse_iterator ft::vector< T, Allocator>::rbegin() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector rbegin() called" << std::endl;
		return reverse_iterator(end());
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_reverse_iterator ft::vector< T, Allocator>::rbegin() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const rbegin() called" << std::endl;
		return const_reverse_iterator(end());
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::iterator ft::vector< T, Allocator>::end() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector end() called" << std::endl;
		return (iterator(this->vectorBaseVar.finish));
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_iterator ft::vector< T, Allocator>::end() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const end() called" << std::endl;
		return (const_iterator(this->vectorBaseVar.finish));
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::reverse_iterator ft::vector< T, Allocator>::rend() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector rend() called" << std::endl;
		return reverse_iterator(begin());
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_reverse_iterator ft::vector< T, Allocator>::rend() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const rend() called" << std::endl;
		return const_reverse_iterator(begin());
	}

////////////////////////////////////////////////////
//****************** CAPACITY *******************//
//////////////////////////////////////////////////

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::size_type ft::vector< T, Allocator>::size() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector size() called" << std::endl;
		return (this->vectorBaseVar.finish - this->vectorBaseVar.start);
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::size_type ft::vector< T, Allocator>::max_size() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector max_size() called" << std::endl;
		return (getAllocator().max_size());
	}

	template<typename T, typename Allocator>
	inline bool ft::vector< T, Allocator>::empty() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector empty() called" << std::endl;
		return (this->vectorBaseVar.start == this->vectorBaseVar.finish);
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::resize (size_type n, value_type val)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector resize() called" << std::endl;
		if (n < size())
		{
			for (; n < size(); )
				this->pop_back();

		}
		else if (n > size() && n <= capacity())
			this->insert(end(), n - size(), val);
		else
		{
			vectorBase<T, Allocator> temp(capacity()*2);
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
			std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.finish, temp.vectorBaseVar.start);
			temp.vectorBaseVar.finish += this->end() - this->begin();
			std::uninitialized_fill_n(temp.vectorBaseVar.finish, n - size(), val);
			temp.vectorBaseVar.finish += n - size();
			this->destroyElements();
			temp.swapData(this->vectorBaseVar);
		}
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::size_type ft::vector< T, Allocator>::capacity() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector capacity() called" << std::endl;
		return (this->vectorBaseVar.endOfStorage - this->vectorBaseVar.start);
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::reserve(size_type n)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector reserve() called" << std::endl;
		if (n > max_size())
			throw std::runtime_error("vector::reserve");
		if (capacity() < n)
		{
			vectorBase<T, Allocator> temp(n);
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
			std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.finish, temp.vectorBaseVar.start); // copy the elements of rhs into a temporary 
			temp.vectorBaseVar.finish += this->size();
			this->destroyElements();
			temp.swapData(this->vectorBaseVar);
		}
	}

////////////////////////////////////////////////////
//*************** ELEMENT ACCESS ****************//
//////////////////////////////////////////////////

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::reference ft::vector< T, Allocator>::front() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector front() called" << std::endl;
		return *begin();
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_reference ft::vector< T, Allocator>::front() const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const front() called" << std::endl;
		return *begin();
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::reference ft::vector< T, Allocator>::back() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector back() called" << std::endl;
		return *(end() - 1);
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_reference ft::vector< T, Allocator>::back() const throw() 
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const back() called" << std::endl;
		return *(end() - 1);
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::reference ft::vector< T, Allocator>::operator[] (size_type idx) throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator[] overload called" << std::endl;
		return *(this->vectorBaseVar.start + idx);
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_reference ft::vector< T, Allocator>::operator[] (size_type idx) const throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const operator[] overload called" << std::endl;
		return *(this->vectorBaseVar.start + idx);
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::reference ft::vector< T, Allocator>::at(size_type n)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector at() called" << std::endl;
		if(n < 0 || n >= this->size())
			throw std::out_of_range("vector::at out of range");
		return (*this)[n];
	}

	template<typename T, typename Allocator>
	inline typename ft::vector< T, Allocator>::const_reference ft::vector< T, Allocator>::at(size_type n) const
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector const at() called" << std::endl;
		if(n < 0 || n >= this->size())
			throw std::out_of_range("vector::const_reference at out of range");
		return (*this)[n];
	}

////////////////////////////////////////////////////
//******************* MODIFIERS *****************//
//////////////////////////////////////////////////

	//range (1)
	template<typename T, typename Allocator>
	template<typename InputIterator>
	void ft::vector< T, Allocator>::assign (InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector assign() range called" << std::endl;
		difference_type distance = ft::distance(first, last);
		if(distance > (difference_type)capacity())
		{
			vectorBase<T, Allocator> temp(distance);
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
			std::uninitialized_copy(first, last, temp.vectorBaseVar.start);
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start + distance;
			this->destroyElements();
			temp.swapData(this->vectorBaseVar);
		}
		else
		{
			clear();
			this->vectorBaseVar.finish = this->vectorBaseVar.start;
			std::copy(first, last, this->vectorBaseVar.start);
			this->vectorBaseVar.finish = this->vectorBaseVar.start + distance;
		}
	}

	//fill (2)
	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::assign (size_type n, const value_type& val)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector assign() fill called" << std::endl;
		if(n > capacity())
		{
			vectorBase<T, Allocator> temp(n);
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
			std::uninitialized_fill_n(temp.vectorBaseVar.start, n, val); // copy the elements of rhs into a temporary 
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start + n;
			this->destroyElements();
			temp.swapData(this->vectorBaseVar);
		}
		else
		{
			clear();
			this->vectorBaseVar.finish = this->vectorBaseVar.start;
			std::fill_n(this->vectorBaseVar.start, n, val);
			this->vectorBaseVar.finish = this->vectorBaseVar.start + n;
		}
	}

	//single element (1)
	template<typename T, typename Allocator>
	typename ft::vector< T, Allocator>::iterator ft::vector< T, Allocator>::insert (iterator position, const value_type& val)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector single element insert function called" << std::endl;

		if (position == end())
		{
			difference_type posDiff = position - this->begin();
			push_back(val);
			position = this->begin() + posDiff;
		}
		else
		{
			if (size() + 1 <= capacity())
			{
				std::uninitialized_copy(this->vectorBaseVar.finish - 1, this->vectorBaseVar.finish, (this->vectorBaseVar.finish) );
				++(this->vectorBaseVar.finish);
				std::copy_backward(&(*position), this->vectorBaseVar.finish - 2, this->vectorBaseVar.finish - 1);
				std::fill_n(position, 1, val);
			}
			else
			{
				vectorBase<T, Allocator> temp(capacity()*2);
				temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
				std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.start + (position - this->begin()), temp.vectorBaseVar.start);
				temp.vectorBaseVar.finish += position - this->begin();
				std::uninitialized_fill_n(temp.vectorBaseVar.finish, 1, val);
				++temp.vectorBaseVar.finish;
				std::uninitialized_copy(this->vectorBaseVar.start + (position - this->begin()), this->vectorBaseVar.finish, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += this->end() - position;
				this->destroyElements();
				temp.swapData(this->vectorBaseVar);
				position = this->begin() + (&(*position) - temp.vectorBaseVar.start);
			}
		}
		return iterator(position);
	}

	//fill (2)
	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::insert (iterator position, size_type n, const value_type& val)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector fill insert function called" << std::endl;

		if (position == end())
		{
			if (size() + n <= capacity())
			{
				std::uninitialized_fill_n(this->vectorBaseVar.start + (position - this->begin()), n, val);
				this->vectorBaseVar.finish += n;
			}
			else
			{
				size_t newCapacity = capacityCalc(n);
				vectorBase<T, Allocator> temp(newCapacity);
				temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
				std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.start + (position - this->begin()), temp.vectorBaseVar.start);
				temp.vectorBaseVar.finish += position - this->begin();
				std::uninitialized_fill_n(temp.vectorBaseVar.finish, n, val);
				temp.vectorBaseVar.finish += n;
				std::uninitialized_copy(this->vectorBaseVar.start + (position - this->begin()), this->vectorBaseVar.finish, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += this->end() - position;
				this->destroyElements();
				temp.swapData(this->vectorBaseVar);
			}
			
		}
		else
		{
			if (size() + n <= capacity())
			{
				std::uninitialized_copy(this->vectorBaseVar.finish - n, this->vectorBaseVar.finish, (this->vectorBaseVar.finish) );
				this->vectorBaseVar.finish += n;
				std::copy_backward(&(*position), this->vectorBaseVar.finish - 2 * n, this->vectorBaseVar.finish - n);
				std::fill_n(position, n, val);
			}
			else
			{
				size_t newCapacity = capacityCalc(n);
				vectorBase<T, Allocator> temp(newCapacity);
				temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
				std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.start + (position - this->begin()), temp.vectorBaseVar.start);
				temp.vectorBaseVar.finish += position - this->begin();
				std::uninitialized_fill_n(temp.vectorBaseVar.finish, n, val);
				temp.vectorBaseVar.finish += n;
				std::uninitialized_copy(this->vectorBaseVar.start + (position - this->begin()), this->vectorBaseVar.finish, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += this->end() - position;
				this->destroyElements();
				temp.swapData(this->vectorBaseVar);
			}
		}
	}

	//range (3)
	template<typename T, typename Allocator>
	template<typename InputIterator>
	void ft::vector< T, Allocator>::insert (iterator position, InputIterator first, InputIterator last, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type*)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector fill insert function called" << std::endl;

		difference_type distance = ft::distance(first, last);
		if (position == end())
		{
			if (size() + distance <= capacity())
			{
				std::uninitialized_copy(first, last, this->vectorBaseVar.start + (position - this->begin()));
				this->vectorBaseVar.finish += distance;
			}
			else
			{
				size_t newCapacity = capacityCalc(distance);
				vectorBase<T, Allocator> temp(newCapacity);
				temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
				std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.start + (position - this->begin()), temp.vectorBaseVar.start);
				temp.vectorBaseVar.finish += position - this->begin();
				std::uninitialized_copy(first, last, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += distance;
				std::uninitialized_copy(this->vectorBaseVar.start + (position - this->begin()), this->vectorBaseVar.finish, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += this->end() - position;
				this->destroyElements();
				temp.swapData(this->vectorBaseVar);
			}
			
		}
		else
		{
			if (size() + distance <= capacity())
			{
				std::uninitialized_copy(this->vectorBaseVar.finish, this->vectorBaseVar.finish + distance, this->vectorBaseVar.finish - distance);
				this->vectorBaseVar.finish += distance;
				std::copy_backward(&(*position), this->vectorBaseVar.finish - 2 * distance, this->vectorBaseVar.finish - distance);
				std::copy(first, last, position);
			}
			else
			{
				size_t newCapacity = capacityCalc(distance);
				vectorBase<T, Allocator> temp(newCapacity);
				temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
				std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.start + (position - this->begin()), temp.vectorBaseVar.start);
				temp.vectorBaseVar.finish += position - this->begin();
				std::uninitialized_copy(first, last, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += distance;
				std::uninitialized_copy(this->vectorBaseVar.start + (position - this->begin()), this->vectorBaseVar.finish, temp.vectorBaseVar.finish);
				temp.vectorBaseVar.finish += this->end() - position;
				this->destroyElements();
				temp.swapData(this->vectorBaseVar);
			}
		}
	}

	template<typename T, typename Allocator>
	size_t ft::vector< T, Allocator>::capacityCalc (difference_type distance)
	{
		if (size() + distance < capacity() * 2)
		{
			if (size() + distance > size() * 2)
				return(size() +  distance);
			else
				return (size() *2);
		}
		else
		{
			if (size() + distance > capacity() * 2)
				return (size() +  distance);
			else
				return(capacity() * 2);
		}
	}

	template<typename T, typename Allocator>
	typename ft::vector< T, Allocator>::iterator ft::vector< T, Allocator>::erase (iterator position)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector erase() single element called" << std::endl;
		erase_handler(1, position);
		return position;
	}

	template<typename T, typename Allocator>
	typename ft::vector< T, Allocator>::iterator ft::vector< T, Allocator>::erase (iterator first, iterator last)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector erase() range called" << std::endl;
		difference_type distance = ft::distance(first, last);
		erase_handler(distance, first);
		return (iterator(first));
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::erase_handler(difference_type distance, iterator position)
	{
		if(position + distance != end())
			std::copy(&(*position) + distance, this->vectorBaseVar.finish, &(*position));
		for (difference_type i = 0; i < distance; i++)
			this->pop_back();
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::push_back(const T& x)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector push_back() called" << std::endl;
		if (VECTOR_COMMENTS == 1)
			std::cout << "Vector push_back() called" << std::endl;
		if (this->vectorBaseVar.finish == this->vectorBaseVar.endOfStorage)
		{
			vectorBase<T, Allocator> temp(this->size() ? 2 * this->size() : 1);
			temp.vectorBaseVar.finish = temp.vectorBaseVar.start;
			std::uninitialized_copy(this->vectorBaseVar.start, this->vectorBaseVar.finish, temp.vectorBaseVar.start);
			temp.vectorBaseVar.finish += this->size();
			this->getAllocator().construct(temp.vectorBaseVar.finish, x);
			++temp.vectorBaseVar.finish;
			this->destroyElements();
			temp.swapData(this->vectorBaseVar);
			return;
		}
		this->getAllocator().construct(this->vectorBaseVar.finish, x);
		++(this->vectorBaseVar.finish);
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::pop_back() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector pop_back() called" << std::endl;
		this->getAllocator().destroy(this->vectorBaseVar.finish);
		--this->vectorBaseVar.finish;
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::clear() throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector clear() called" << std::endl;
		// vector<T>().swap(*this);
		erase(begin(), end());
	}

	template<typename T, typename Allocator>
	void ft::vector< T, Allocator>::swap(vector& x) throw()
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector swap() member function called" << std::endl;
		this->swapData(x.vectorBaseVar);
	}

////////////////////////////////////////////////////
//****************** OBSERVERS ******************//
//////////////////////////////////////////////////

	template<typename T, typename Allocator>
	typename ft::vector< T, Allocator>::allocator_type ft::vector< T, Allocator>::get_allocator() const
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector get_allocator() member function called" << std::endl;
		return this->getAllocator();
	}

////////////////////////////////////////////////////
//****************** OVERLOADS ******************//
//////////////////////////////////////////////////

	template<typename T, typename Allocator>
	inline bool operator==(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator== overload called" << std::endl;
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<typename T, typename Allocator>
	inline bool operator<(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator< overload called" << std::endl;
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); 		
	}

	template<typename T, typename Allocator>
	inline bool operator!=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator!= overload called" << std::endl;
		return !(lhs == rhs);
	}

	template<typename T, typename Allocator>
	inline bool operator>(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator> overload called" << std::endl;
		return rhs < lhs;
	}

	template<typename T, typename Allocator>
	inline bool operator<=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator<= overload called" << std::endl;
		return !(rhs < lhs);
	}

	template<typename T, typename Allocator>
	inline bool operator>=(const vector<T, Allocator>& lhs, const vector<T, Allocator>& rhs)
	{
		if (VECTOR_COMMENTS)
			std::cout << "Vector operator>= overload called" << std::endl;
		return !(lhs < rhs);
	}
}


namespace std
{
	// used when std::swap(a,b) is called on vectors
	template<class T, class Alloc>
	inline void swap(ft::vector<T,Alloc>& a, ft::vector<T,Alloc>& b)
	{
		if (VECTOR_COMMENTS)
			std::cout << "vector std::swap() specialization called on " << &a << " and " << &b << std::endl;
		a.swap(b);
	};
}