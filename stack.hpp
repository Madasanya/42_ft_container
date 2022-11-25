#pragma once

#include "vector.hpp"

namespace ft
{
	template<typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		typedef typename Container::value_type				value_type;
		typedef typename Container::reference				reference;
		typedef typename Container::const_reference			const_reference;
		typedef typename Container::size_type				size_type;
		typedef	Container									container_type;

	protected:
		Container c;

	public:
		explicit stack(const Container& c = Container())
		: c(c) { }

		~stack() {};

		stack& operator=( const stack& other )
		{
			if (*this == other)
				return *this;
			c = other.c;
			return(*this);
		}

		reference top()
		{
			return (c.back());
		}

		const_reference top() const
		{
			return (c.back());
		}


		bool empty() const
		{
			return c.empty();
		}
		
		size_type size() const
		{
			return c.size();
		}

		void push( const value_type& value )
		{
			c.push_back(value);
		}

		void pop()
		{
			c.pop_back();
		}

	protected:
		friend bool operator==( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return (lhs.c == rhs.c);
		};
		
		friend bool operator!=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return !(lhs.c == rhs.c);
		};

		friend bool operator<( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return (lhs.c < rhs.c);
		};

		friend bool operator<=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return !(rhs.c <lhs.c);
		};

		friend bool operator>( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return (rhs.c < lhs.c);
		};

		friend bool operator>=( const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs )
		{
			return !(lhs.c < rhs.c);
		};

	};
}