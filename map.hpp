#pragma once

#include "bst.hpp"
#include <functional>
#include <exception>
#include <stdexcept>

namespace ft
{

template <class Key, class T, class Compare = std::less<Key> , class Alloc = std::allocator<pair<const Key,T> > >
class map
{
public:

	typedef Key																			key_type;
	typedef T																			mapped_type;
	typedef pair<const key_type, mapped_type>											value_type;
	typedef const pair<const key_type, mapped_type>										const_value_type;
	typedef Compare																		key_compare;
	typedef typename Alloc::template rebind<nodeStruct<value_type> >::other				allocator_type;
	typedef value_type&																	reference;
	typedef const value_type&															const_reference;
	typedef value_type*																	pointer;
	typedef const value_type*															const_pointer;
	typedef ptrdiff_t																	difference_type;
	typedef size_t																		size_type;
	typedef ft::bst<key_type, mapped_type, value_type, key_compare, allocator_type>		binarySearchTree;
	typedef typename binarySearchTree::nodePtr											nodePtr;
	typedef typename binarySearchTree::constNodePtr										constNodePtr;
	typedef typename ft::bstIterator<nodePtr, value_type>								iterator;
	typedef typename ft::bstIterator<constNodePtr, const_value_type>					const_iterator;
	typedef ft::reverse_iterator<iterator>												reverse_iterator;
	typedef ft::reverse_iterator<const_iterator>										const_reverse_iterator;
	
private:
	binarySearchTree																	bst;
	Compare																				compare;
	allocator_type																		allocator;


public:

	class value_compare
		: std::binary_function<value_type, value_type, bool>
	{
		public:
			friend class map;

			bool operator() (const value_type& lhs, const value_type& rhs) const
			{
				return (comp(lhs.first, rhs.first));
			}

		protected:
			value_compare(key_compare c)
				: comp(c) {}

			key_compare comp;
	};

	explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: bst(binarySearchTree()), compare(comp), allocator(alloc) { }

	template<typename InputIterator>
	map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		: bst(binarySearchTree()), compare(comp), allocator(alloc)
	{
		InputIterator temp = first;
		for(;temp != last; ++temp)
			bst.insert(bst.root, *temp, bst.root->parent);
	}

	map (const map& x)
		:bst(binarySearchTree()), compare(x.compare), allocator(x.allocator)
	{
		bst.copyTree(x.bst.root, this->bst.root, x.bst.nil);
	}

	~map() { }

	map&	operator= (const map& rhs) {
		this->clear();
		bst.copyTree(rhs.bst.root, this->bst.root, rhs.bst.nil);
		compare	= rhs.compare;
		allocator	= rhs.allocator;
		return *this;
	}

	bool empty() const
	{
		return bst.size() == 0;
	}

	size_type size() const
	{
		return bst.size();
	}
	size_type max_size() const
	{
		return allocator.max_size();
	}

	mapped_type& operator[] (const key_type& k)
	{
		return (this->insert(ft::make_pair(k,mapped_type()))).first->second;
	}

	mapped_type& at(const key_type& k)
	{
		iterator element = this->find(k);
		if (element == end())
			throw std::out_of_range("map::at out of range");
		return (*element).second;
	}

	ft::pair<iterator, bool> insert (const value_type& val)
	{
		size_t prevTreeSize = bst.getTreeSize();
		iterator it = iterator(bst.insert(bst.root, val, bst.root->parent));
		if (bst.getTreeSize() == prevTreeSize)
			return (ft::make_pair<iterator, bool>(it, false));
		else
			return (ft::make_pair<iterator, bool>(it, true));
	}

	iterator insert (iterator position, const value_type& val)
	{
		(void)position;
		return iterator(bst.insert(bst.root, val, bst.root->parent));
	}

	template <class InputIterator>
	void insert (InputIterator first, InputIterator last)
	{
		(bst.insert(first, last));
	}

	void erase (iterator position)
	{
		if (size() == 0)
			return;
		bst.erase(position.bstNode);
	}

	size_type erase (const key_type& k)
	{
		iterator element = this->find(k);
		if (element != end())
		{
			bst.erase((this->find(k)).bstNode);
			return 1;
		}
		else return 0;
	}
	
	void erase (iterator first, iterator last)
	{
		iterator toDelete;
		while (first != last)
		{
			toDelete = first;
			first++;
			bst.erase(toDelete.bstNode);
		}
	}

	iterator find(const key_type& k)
	{
		return(bst.find(bst.root, k));
	}
	
	const_iterator find (const key_type& k) const
	{
		return(bst.find(bst.root, k));
	}

	size_type count (const key_type& k) const
	{
		return(bst.find(bst.root, k) != bst.end());
	}

	iterator lower_bound(const key_type& k)
	{
		return(bst.lower_bound(bst.root, k));
	}
	
	const_iterator lower_bound (const key_type& k) const
	{
		return(bst.lower_bound(bst.root, k));
	}

	iterator upper_bound(const key_type& k)
	{
		return(bst.upper_bound(bst.root, k));
	}
	
	const_iterator upper_bound (const key_type& k) const
	{
		return(bst.upper_bound(bst.root, k));
	}

	ft::pair<iterator,iterator> equal_range(const key_type& k)
	{
		return(ft::make_pair(bst.lower_bound(bst.root, k),bst.upper_bound(bst.root, k)));
	}
	
	ft::pair<const_iterator,const_iterator> equal_range (const key_type& k) const
	{
		return(ft::make_pair(bst.lower_bound(bst.root, k), bst.upper_bound(bst.root, k)));
	}

	void clear()
	{
		bst.clear(bst.root);
	}

	void swap (map& x)
	{
		bst.swap(x.bst);
	}

	key_compare key_comp() const
	{
		return compare;
	}
	
	value_compare value_comp() const
	{
		return value_compare(compare);
	}

	allocator_type get_allocator() const {return allocator_type(bst.allocator);}

	iterator begin() throw()
	{
		return iterator(bst.begin());
	}

	const_iterator begin() const throw()
	{
		return const_iterator(bst.begin());
	}

	iterator end() throw()
	{
		return iterator(bst.end());
	}

	const_iterator end() const throw()
	{
		return const_iterator(bst.end());
	}

	reverse_iterator rbegin() throw()
	{
		return (bst.rbegin());
	}

	const_reverse_iterator rbegin() const throw()
	{
		return (bst.rbegin());
	}

	reverse_iterator rend() throw()
	{
		return (bst.rend());
	}

	const_reverse_iterator rend() const throw()
	{
		return (bst.rend());
	}

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool operator==(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	friend bool operator<(const map<_K1, _T1, _C1, _A1>&, const map<_K1, _T1, _C1, _A1>&);

};

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	bool operator== (const map<_K1,_T1,_C1,_A1> & lhs, const map<_K1,_T1,_C1,_A1> & rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<typename _K1, typename _T1, typename _C1, typename _A1>
	bool operator< (const map<_K1,_T1,_C1,_A1> & lhs, const map<_K1,_T1,_C1,_A1> & rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator!=(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator>(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return rhs < lhs;
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator<=(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return !(rhs < lhs);
	}

	template<typename _Key, typename _Tp, typename _Compare, typename Allocator>
	inline bool operator>=(const map<_Key, _Tp, _Compare, Allocator>& lhs, const map<_Key, _Tp, _Compare, Allocator>& rhs)
	{
		return !(lhs < rhs);
	}

}

namespace std
{
	// used in main when std::swap(a,b) is called on map
	template<class Key, class T, class Compare, class Alloc >
	inline void swap(ft::map<Key, T, Compare, Alloc>& a, ft::map<Key, T, Compare, Alloc>& b)
	{
		a.swap(b);
	};
}