#pragma once

#include "iterator.hpp"

namespace ft
{

	template<bool Cond, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	template <typename T, T v>
	struct integral_constant
	{
		static const T value = v;
	};

	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	//default template with false value
	template <typename T>
	struct is_integral
		: public false_type { };


	//specializations with true value
	template <>
	struct is_integral<bool>
		: public true_type {};

	template <>
	struct is_integral<char>
		: public true_type {};

	template <>
	struct is_integral<wchar_t>
		: public true_type {};

	template <>
	struct is_integral<signed char>
		:public true_type {};

	template <>
	struct is_integral<short int>
		:public true_type {};

	template <>
	struct is_integral<int>
		:public true_type {};

	template <>
	struct is_integral<long int>
		:public true_type {};

	template <>
	struct is_integral<long long int>
		:public true_type {};

	template <>
	struct is_integral<unsigned char>
		:public true_type {};

	template <>
	struct is_integral<unsigned short int>
	:public true_type {};

	template <>
	struct is_integral<unsigned int>
	:public true_type {};

	template <>
	struct is_integral<unsigned long int>
	:public true_type {};

	template <>
	struct is_integral<unsigned long long int>
	:public true_type {};

	//for enable_if testing
	template <class T>
	typename enable_if<is_integral<T>::value,bool>::type is_odd (T i)
	{
		return bool(i%2);
	};

	template < class T>
	bool is_even(T i)
	{
		typedef typename enable_if<is_integral<T>::value,bool>::type integral;
		integral h;
		h = 0;
		if (!h)
			return (!bool(i%2));
		return (0) ;
	};

	template <class T1, class T2>
	struct pair
	{
	public:
		typedef T1 first_type;
		typedef T2 second_type;

		first_type first;
		second_type second;

		pair() 
			: first(), second() { };

		template <class U, class V>
		pair(const pair<U, V>& pr)
			: first(pr.first), second(pr.second) { };

		pair(const first_type& a, const second_type& b)
			: first(a), second(b) { };


		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;

			return *this;
		};
	};

	template <class T1, class T2>
	bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T1, class T2>
	bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second);
	}

	template < class T1, class T2 >
	bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T1, class T2>
	bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return rhs < lhs;
	}

	template <class T1, class T2>
	bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs)
	{
		return !(lhs < rhs);
	}

	template <class T1, class T2>
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template<class InputIt1, class InputIt2>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		while (first1!=last1)
		{
			if (first2 == last2 || *first2 < *first1) 
				return false;
			else if (*first1 < *first2) 
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template<class InputIt1, class InputIt2, class Compare>
	bool lexicographical_compare(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2, Compare comp)
	{
		for (; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2) 
		{
			if (comp(*first1, *first2)) 
				return true;
			if (comp(*first2, *first1)) 
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	//default template with false value
	template <typename T, typename U>
	struct are_same : public false_type { };

	//specializations with true value
	template <typename T>
	struct are_same<T, T>
		: public true_type {};

	template<class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}

	template<class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}
}