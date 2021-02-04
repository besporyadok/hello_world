#ifndef __XRAYSTL_H__
#define __XRAYSTL_H__

#include <set>
#include <vector>

#define xr_list std::list
#define xr_deque std::deque
#define xr_stack std::stack
#define xr_set std::set
#define xr_multiset std::multiset
#define xr_map std::map
#define xr_multimap std::multimap
#define xr_string std::string

template <class T>
class xr_vector	: public std::vector<T> {
public: 
	typedef	size_t		size_type;
	typedef T&			reference;
	typedef const T&	const_reference;
public: 
			xr_vector			()								: std::vector<T>	()				{}
			xr_vector			(size_t _count, const T& _value): std::vector<T>	(_count,_value)	{}
	explicit xr_vector			(size_t _count)					: std::vector<T> 	(_count)		{}
	void	clear				()								{ erase(begin(),end());				} 
	void	clear_and_free		()								{ std::vector<T>::clear();			}
	void	clear_not_free		()								{ erase(begin(),end());	}
	ICF		const_reference	operator[]	(size_type _Pos) const	{ {VERIFY(_Pos<size());} return (*(begin() + _Pos)); }
	ICF		reference		operator[]	(size_type _Pos)		{ {VERIFY(_Pos<size());} return (*(begin() + _Pos)); }
};

template	<>												
class	xr_vector<bool>	: public std::vector<bool>{ 
	typedef	bool		T;
public: 
			xr_vector<T>		()								: std::vector<T>	()				{}
			xr_vector<T>		(size_t _count, const T& _value): std::vector<T>	(_count,_value)	{}
	explicit xr_vector<T>		(size_t _count)					: std::vector<T>	(_count)		{}
	u32		size() const										{ return (u32)std::vector<T>::size();	} 
	void	clear()												{ erase(begin(),end());				} 
};

#endif