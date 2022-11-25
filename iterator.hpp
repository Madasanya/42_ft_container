#pragma once

#include <cstddef>
#include "utils.hpp"
#include <iostream>

#define ITERATOR_COMMENTS 0

namespace ft
{
	template<typename Category, typename T, typename Distance = ptrdiff_t, typename Pointer = T*, typename Reference = T&>
	struct iterator
	{
		typedef Category		iterator_category;
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer			pointer;
		typedef Reference		reference;
	};

	template<typename Iterator>
	struct iterator_traits
	{
		typedef typename Iterator::iterator_category		iterator_category;
		typedef typename Iterator::value_type				value_type;
		typedef typename Iterator::difference_type			difference_type;
		typedef typename Iterator::pointer					pointer;
		typedef typename Iterator::reference				reference;
	};

	template<typename T>
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef T*									pointer;
		typedef T&									reference;
	};

	template<typename T>
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag		iterator_category;
		typedef T									value_type;
		typedef ptrdiff_t							difference_type;
		typedef const T*							pointer;
		typedef const T&							reference;
	};

	template<typename Iterator>
	inline typename ft::iterator_traits<Iterator>::iterator_category iterator_category(const Iterator&)
	{
		if (ITERATOR_COMMENTS)
			std::cout << "iterator_category() function called" << std::endl;
		return (typename ft::iterator_traits<Iterator>::iterator_category());
	}

	/********************	 ITERATOR BASE FUNCTIONS	 *********************/

	template<typename ForwardIterator>
	inline typename ft::iterator_traits<ForwardIterator>::difference_type iteratorDistance(ForwardIterator first, ForwardIterator last, std::forward_iterator_tag)
	{
		typename ft::iterator_traits<ForwardIterator>::difference_type n = 0;
		while (first != last)
		{
			++first;
			++n;
		}
		return n;
	}

	template<typename RandomAccessIterator>
	inline typename ft::iterator_traits<RandomAccessIterator>::difference_type iteratorDistance(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag)
	{
		return last - first;
	}

	template<typename Iterator>
	inline typename ft::iterator_traits<Iterator>::difference_type
	distance(Iterator first, Iterator last)
	{
		return iteratorDistance(first, last, ft::iterator_category(first));
	}

	/******************	ITERATOR	********************/

	/****	start of normal iterator	****/

	template<typename Iterator>
	class vectorIterator
	{
	protected:
		Iterator current;

		typedef ft::iterator_traits<Iterator>				traits_type;

	public:
		typedef Iterator									iterator_type;
		typedef typename traits_type::iterator_category		iterator_category;
		typedef typename traits_type::value_type			value_type;
		typedef typename traits_type::difference_type		difference_type;
		typedef typename traits_type::reference				reference;
		typedef typename traits_type::pointer				pointer;

		vectorIterator() throw()
			: current(Iterator()) 
		{
			if (ITERATOR_COMMENTS)
				std::cout << "vectorIterator default constructor called" << std::endl;
		}

		explicit vectorIterator(const Iterator& iter) throw()
			: current(iter)
		{
			if (ITERATOR_COMMENTS)
				std::cout << "vectorIterator parameter constructor called" << std::endl;
		}

		// Allow iterator to const_iterator conversion
		template<typename Iter>
		vectorIterator(const vectorIterator<Iter>& iter) throw()
			: current(iter.base())
		{
			if (ITERATOR_COMMENTS)
				std::cout << "vectorIterator parameter constructor (to const) called" << std::endl;
		}

		const Iterator& base() const throw()
		{
			return current;
		}

		// Forward iterator requirements
		reference operator*() const throw()
		{
			return *current;
		}

		pointer operator->() const throw()
		{
			return current;
		}

		vectorIterator& operator++() throw()
		{
			++current;
			return *this;
		}

		vectorIterator operator++(int) throw()
		{
			return vectorIterator(current++);
		}

		// Bidirectional iterator requirements
		vectorIterator& operator--() throw()
		{
			--current;
			return *this;
		}

		vectorIterator operator--(int) throw()
		{
			return vectorIterator(current--);
		}

		// Random access iterator requirements
		reference operator[](difference_type n) const throw()
		{
			return current[n];
		}

		vectorIterator& operator+=(difference_type n) throw()
		{
			current += n;
			return *this;
		}

		vectorIterator operator+(difference_type n) const throw()
		{
			return vectorIterator(current + n);
		}

		vectorIterator& operator-=(difference_type n) throw()
		{
			current -= n; return *this;
		}

		vectorIterator operator-(difference_type n) const throw()
		{
			return vectorIterator(current - n);
		}
	};

	// Forward iterator requirements
	template<typename IteratorL, typename IteratorR>
	inline bool	operator==(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs) throw()
	{
		return lhs.base() == rhs.base();
	}

	template<typename IteratorL, typename IteratorR>
	inline bool	operator!=(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs) throw()
	{
		return !(lhs.base() == rhs.base());
	}

	// Random access iterator requirements
	template<typename IteratorL, typename IteratorR>
	inline bool	operator<(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs) throw()
	{ 
		return lhs.base() < rhs.base();
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator>(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs) throw()
	{ 
		return rhs.base() < lhs.base();
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator<=(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs) throw()
	{
		return !(rhs.base() < lhs.base()); 
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator>=(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs) throw()
	{ 
		return !(lhs.base() < rhs.base());
	}

	template<typename IteratorL, typename IteratorR>
	inline typename ft::vectorIterator<IteratorL>::difference_type operator-(const vectorIterator<IteratorL>& lhs, const vectorIterator<IteratorR>& rhs)
	{ 
		return lhs.base() - rhs.base();
	}

	template<typename Iterator>
	inline vectorIterator<Iterator> operator+(typename vectorIterator<Iterator>::difference_type n, const vectorIterator<Iterator>& iter) throw()
	{ 
		return vectorIterator<Iterator>(iter.base() + n);
	}


////////////////////////////////////////////////////
//************** REVERSE ITERATOR ***************//
//////////////////////////////////////////////////

	template<typename Iterator>
	class reverse_iterator
		: public ft::iterator<typename ft::iterator_traits<Iterator>::iterator_category,
							typename ft::iterator_traits<Iterator>::value_type,
							typename ft::iterator_traits<Iterator>::difference_type,
							typename ft::iterator_traits<Iterator>::pointer,
							typename ft::iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;

		typedef ft::iterator_traits<Iterator>			traits_type;

	public:
		typedef Iterator								iterator_type;
		typedef typename traits_type::difference_type	difference_type;
		typedef typename traits_type::pointer			pointer;
		typedef typename traits_type::reference			reference;

		reverse_iterator()
			: current() { }

		explicit reverse_iterator(iterator_type iter)
			: current(iter) { }

		reverse_iterator(const reverse_iterator& iter)
			: current(iter.current) { }

		template<typename Iter>
		reverse_iterator(const reverse_iterator<Iter>& iter)
			: current(iter.base()) { }

		iterator_type base() const
		{
			return current;
		}

		reference operator*() const
		{
			Iterator temp = current;
			return *--temp;
		}

		pointer operator->() const
		{
			return &(operator*()); 
		}

		reverse_iterator& operator++()
		{
			--current;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator temp = *this;
			--current;
			return temp;
		}

		reverse_iterator& operator--()
		{
			++current;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator temp = *this;
			++current;
			return temp;
		}

		reverse_iterator operator+(difference_type n) const
		{ 
			return reverse_iterator(current - n); 
		}

		reverse_iterator& operator+=(difference_type n)
		{
			current -= n;
			return *this;
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(current + n); 
		}

		reverse_iterator& operator-=(difference_type n)
		{
			current += n;
			return *this;
		}

		reference operator[](difference_type n) const
		{
			return *(*this + n); 
		}
	};

	template<typename Iterator>
	inline typename ft::reverse_iterator<Iterator>::difference_type operator-(const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
	{ 
		return rhs.base() - lhs.base();
	}

	template<typename Iterator>
	inline reverse_iterator<Iterator> operator+(typename ft::reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& lhs)
	{ 
		return reverse_iterator<Iterator>(lhs.base() - n);
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator==(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return lhs.base() == rhs.base();
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator<(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return rhs.base() < lhs.base(); 
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator!=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return !(lhs == rhs);
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator>(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return rhs < lhs;
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator<=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return !(rhs < lhs);
	}

	template<typename IteratorL, typename IteratorR>
	inline bool operator>=(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return !(lhs < rhs);
	}

	template<typename IteratorL, typename IteratorR>
	inline typename ft::reverse_iterator<IteratorL>::difference_type operator-(const reverse_iterator<IteratorL>& lhs, const reverse_iterator<IteratorR>& rhs)
	{ 
		return rhs.base() - lhs.base();
	}
} // namespace