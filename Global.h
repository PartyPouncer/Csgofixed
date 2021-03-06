#pragma once

#include "Entity.h"
#include "Cheat.h"
#include "Enhancements.h"
// map standard header
#pragma once
#ifndef _MAP_
#define _MAP_
#ifndef RC_INVOKED

#include <tuple>

#include <xtree>

#pragma pack(push,_CRT_PACKING)
#pragma warning(push,3)
#pragma push_macro("new")
#undef new
_STD_BEGIN
// TEMPLATE CLASS _Tmap_traits
template<class _Kty,	// key type
	class _Ty,	// mapped type
	class _Pr,	// comparator predicate type
	class _Alloc,	// actual allocator type (should be value allocator)
	bool _Mfl>	// true if multiple equivalent keys are permitted
	class _Tmap_traits
{	// traits required to make _Tree behave like a map
public:
	typedef _Kty key_type;
	typedef pair<const _Kty, _Ty> value_type;
	typedef _Pr key_compare;
	typedef _Alloc allocator_type;

	enum
	{	// make multi parameter visible as an enum constant
		_Multi = _Mfl
	};

	class value_compare
	{	// functor for comparing two element values
		friend class _Tmap_traits<_Kty, _Ty, _Pr, _Alloc, _Mfl>;

	public:
		typedef value_type first_argument_type;
		typedef value_type second_argument_type;
		typedef bool result_type;

		bool operator()(const value_type& _Left,
			const value_type& _Right) const
		{	// test if _Left precedes _Right by comparing just keys
			return (comp(_Left.first, _Right.first));
		}

		value_compare(key_compare _Pred)
			: comp(_Pred)
		{	// construct with specified predicate
		}

	protected:
		key_compare comp;	// the comparator predicate for keys
	};

	template<class _Ty1,
		class _Ty2>
		static const _Kty& _Kfn(const pair<_Ty1, _Ty2>& _Val)
	{	// extract key from element value
		return (_Val.first);
	}
};

// TEMPLATE CLASS map
template<class _Kty,
	class _Ty,
	class _Pr = less<_Kty>,
	class _Alloc = allocator<pair<const _Kty, _Ty> > >
	class map
	: public _Tree<_Tmap_traits<_Kty, _Ty, _Pr, _Alloc, false> >
{	// ordered red-black tree of {key, mapped} values, unique keys
public:
	typedef map<_Kty, _Ty, _Pr, _Alloc> _Myt;
	typedef _Tree<_Tmap_traits<_Kty, _Ty, _Pr, _Alloc, false> > _Mybase;
	typedef _Kty key_type;
	typedef _Ty mapped_type;
	typedef _Pr key_compare;
	typedef typename _Mybase::value_compare value_compare;
	typedef typename _Mybase::allocator_type allocator_type;
	typedef typename _Mybase::size_type size_type;
	typedef typename _Mybase::difference_type difference_type;
	typedef typename _Mybase::pointer pointer;
	typedef typename _Mybase::const_pointer const_pointer;
	typedef typename _Mybase::reference reference;
	typedef typename _Mybase::const_reference const_reference;
	typedef typename _Mybase::iterator iterator;
	typedef typename _Mybase::const_iterator const_iterator;
	typedef typename _Mybase::reverse_iterator reverse_iterator;
	typedef typename _Mybase::const_reverse_iterator
		const_reverse_iterator;
	typedef typename _Mybase::value_type value_type;

	typedef typename _Mybase::_Alty _Alty;
	typedef typename _Mybase::_Pairib _Pairib;

	map()
		: _Mybase(key_compare())
	{	// construct empty map from defaults
	}

	explicit map(const allocator_type& _Al)
		: _Mybase(key_compare(), _Al)
	{	// construct empty map from defaults, allocator
	}

	map(const _Myt& _Right)
		: _Mybase(_Right,
			_Right._Getal().select_on_container_copy_construction())
	{	// construct map by copying _Right
	}

	map(const _Myt& _Right, const allocator_type& _Al)
		: _Mybase(_Right, _Al)
	{	// construct map by copying _Right, allocator
	}

	explicit map(const key_compare& _Pred)
		: _Mybase(_Pred)
	{	// construct empty map from comparator
	}

	map(const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct empty map from comparator and allocator
	}

	template<class _Iter>
	map(_Iter _First, _Iter _Last)
		: _Mybase(key_compare())
	{	// construct map from [_First, _Last), defaults
		insert(_First, _Last);
	}

	template<class _Iter>
	map(_Iter _First, _Iter _Last,
		const key_compare& _Pred)
		: _Mybase(_Pred)
	{	// construct map from [_First, _Last), comparator
		insert(_First, _Last);
	}

	template<class _Iter>
	map(_Iter _First, _Iter _Last,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct map from [_First, _Last), comparator, and allocator
		insert(_First, _Last);
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		_Mybase::operator=(_Right);
		return (*this);
	}

	map(_Myt&& _Right)
		: _Mybase(_STD move(_Right))
	{	// construct map by moving _Right
	}

	map(_Myt&& _Right, const allocator_type& _Al)
		: _Mybase(_STD move(_Right), _Al)
	{	// construct map by moving _Right, allocator
	}

	_Myt& operator=(_Myt&& _Right)
		_NOEXCEPT_OP(_Alty::is_always_equal::value
			&& is_nothrow_move_assignable<_Pr>::value)
	{	// assign by moving _Right
		_Mybase::operator=(_STD move(_Right));
		return (*this);
	}

	mapped_type& operator[](key_type&& _Keyval)
	{	// find element matching _Keyval or insert with default mapped
		return (try_emplace(_STD move(_Keyval)).first->second);
	}

	void swap(_Myt& _Right)
		_NOEXCEPT_OP(_Alty::is_always_equal::value
			&& _Is_nothrow_swappable<_Pr>::value)
	{	// exchange contents with non-movable _Right
		_Mybase::swap(_Right);
	}

	using _Mybase::insert;

	template<class _Valty,
		class = enable_if_t<is_constructible<value_type, _Valty>::value> >
		_Pairib insert(_Valty&& _Val)
	{	// insert _Val
		return (this->emplace(_STD forward<_Valty>(_Val)));
	}

	template<class _Valty,
		class = enable_if_t<is_constructible<value_type, _Valty>::value> >
		iterator insert(const_iterator _Where, _Valty&& _Val)
	{	// insert _Val with hint
		return (this->emplace_hint(_Where, _STD forward<_Valty>(_Val)));
	}

	template<class _Keyty,
		class... _Mappedty>
		_Pairib _Try_emplace(_Keyty&& _Keyval,
			_Mappedty&&... _Mapval)
	{	// fail if _Keyval present, else emplace
		iterator _Where = _Mybase::lower_bound(_Keyval);
		if (_Where == _Mybase::end()
			|| _DEBUG_LT_PRED(_Mybase::_Getcomp(),
				_Keyval, _Mybase::_Key(_Where._Mynode())))
			return (_Pairib(
				_Mybase::emplace_hint(_Where,
					piecewise_construct,
					_STD forward_as_tuple(
						_STD forward<_Keyty>(_Keyval)),
					_STD forward_as_tuple(
						_STD forward<_Mappedty>(_Mapval)...)),
				true));
		else
			return (_Pairib(_Where, false));
	}

	template<class... _Mappedty>
	_Pairib try_emplace(const key_type& _Keyval,
		_Mappedty&&... _Mapval)
	{	// fail if _Keyval present, else emplace
		return (_Try_emplace(_Keyval, _STD forward<_Mappedty>(_Mapval)...));
	}

	template<class... _Mappedty>
	iterator try_emplace(const_iterator, const key_type& _Keyval,
		_Mappedty&&... _Mapval)
	{	// fail if _Keyval present, else emplace, ignore hint
		return (_Try_emplace(_Keyval,
			_STD forward<_Mappedty>(_Mapval)...).first);
	}

	template<class... _Mappedty>
	_Pairib try_emplace(key_type&& _Keyval,
		_Mappedty&&... _Mapval)
	{	// fail if _Keyval present, else emplace
		return (_Try_emplace(_STD move(_Keyval),
			_STD forward<_Mappedty>(_Mapval)...));
	}

	template<class... _Mappedty>
	iterator try_emplace(const_iterator, key_type&& _Keyval,
		_Mappedty&&... _Mapval)
	{	// fail if _Keyval present, else emplace, ignore hint
		return (_Try_emplace(_STD move(_Keyval),
			_STD forward<_Mappedty>(_Mapval)...).first);
	}

	template<class _Keyty,
		class _Mappedty>
		_Pairib _Insert_or_assign(_Keyty&& _Keyval,
			_Mappedty&& _Mapval)
	{	// assign if _Keyval present, else insert
		iterator _Where = _Mybase::lower_bound(_Keyval);
		if (_Where == _Mybase::end()
			|| _DEBUG_LT_PRED(_Mybase::_Getcomp(),
				_Keyval, _Mybase::_Key(_Where._Mynode())))
			return (_Pairib(
				_Mybase::emplace_hint(_Where,
					_STD forward<_Keyty>(_Keyval),
					_STD forward<_Mappedty>(_Mapval)),
				true));
		else
		{	// _Keyval present, assign new value
			_Where->second = _STD forward<_Mappedty>(_Mapval);
			return (_Pairib(_Where, false));
		}
	}

	template<class _Mappedty>
	_Pairib insert_or_assign(const key_type& _Keyval,
		_Mappedty&& _Mapval)
	{	// assign if _Keyval present, else insert
		return (_Insert_or_assign(_Keyval,
			_STD forward<_Mappedty>(_Mapval)));
	}

	template<class _Mappedty>
	iterator insert_or_assign(const_iterator, const key_type& _Keyval,
		_Mappedty&& _Mapval)
	{	// assign if _Keyval present, else insert, ignore hint
		return (_Insert_or_assign(_Keyval,
			_STD forward<_Mappedty>(_Mapval)).first);
	}

	template<class _Mappedty>
	_Pairib insert_or_assign(key_type&& _Keyval,
		_Mappedty&& _Mapval)
	{	// assign if _Keyval present, else insert
		return (_Insert_or_assign(_STD move(_Keyval),
			_STD forward<_Mappedty>(_Mapval)));
	}

	template<class _Mappedty>
	iterator insert_or_assign(const_iterator, key_type&& _Keyval,
		_Mappedty&& _Mapval)
	{	// assign if _Keyval present, else insert, ignore hint
		return (_Insert_or_assign(_STD move(_Keyval),
			_STD forward<_Mappedty>(_Mapval)).first);
	}

	map(_XSTD initializer_list<value_type> _Ilist)
		: _Mybase(key_compare())
	{	// construct from initializer_list, defaults
		insert(_Ilist);
	}

	map(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred)
		: _Mybase(_Pred)
	{	// construct from initializer_list, comparator
		insert(_Ilist);
	}

	map(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct from initializer_list, comparator, and allocator
		insert(_Ilist);
	}

	_Myt& operator=(_XSTD initializer_list<value_type> _Ilist)
	{	// assign initializer_list
		_Mybase::clear();
		insert(_Ilist);
		return (*this);
	}

	mapped_type& operator[](const key_type& _Keyval)
	{	// find element matching _Keyval or insert with default mapped
		return (try_emplace(_Keyval).first->second);
	}

	mapped_type& at(const key_type& _Keyval)
	{	// find element matching _Keyval
		iterator _Where = _Mybase::lower_bound(_Keyval);
		if (_Where == _Mybase::end()
			|| _Mybase::_Getcomp()(_Keyval, _Mybase::_Key(_Where._Mynode())))
			_Xout_of_range("invalid map<K, T> key");
		return (_Where->second);
	}

	const mapped_type& at(const key_type& _Keyval) const
	{	// find element matching _Keyval
		const_iterator _Where = _Mybase::lower_bound(_Keyval);
		if (_Where == _Mybase::end()
			|| _Mybase::_Getcomp()(_Keyval, _Mybase::_Key(_Where._Mynode())))
			_Xout_of_range("invalid map<K, T> key");
		return (_Where->second);
	}
};

template<class _Kty,
	class _Ty,
	class _Pr,
	class _Alloc> inline
	void swap(map<_Kty, _Ty, _Pr, _Alloc>& _Left,
		map<_Kty, _Ty, _Pr, _Alloc>& _Right)
	_NOEXCEPT_OP(_NOEXCEPT_OP(_Left.swap(_Right)))
{	// swap _Left and _Right maps
	_Left.swap(_Right);
}

// TEMPLATE CLASS multimap
template<class _Kty,
	class _Ty,
	class _Pr = less<_Kty>,
	class _Alloc = allocator<pair<const _Kty, _Ty> > >
	class multimap
	: public _Tree<_Tmap_traits<_Kty, _Ty, _Pr, _Alloc, true> >
{	// ordered red-black tree of {key, mapped} values, non-unique keys
public:
	typedef multimap<_Kty, _Ty, _Pr, _Alloc> _Myt;
	typedef _Tree<_Tmap_traits<_Kty, _Ty, _Pr, _Alloc, true> > _Mybase;
	typedef _Kty key_type;
	typedef _Ty mapped_type;
	typedef _Pr key_compare;
	typedef typename _Mybase::value_compare value_compare;
	typedef typename _Mybase::allocator_type allocator_type;
	typedef typename _Mybase::size_type size_type;
	typedef typename _Mybase::difference_type difference_type;
	typedef typename _Mybase::pointer pointer;
	typedef typename _Mybase::const_pointer const_pointer;
	typedef typename _Mybase::reference reference;
	typedef typename _Mybase::const_reference const_reference;
	typedef typename _Mybase::iterator iterator;
	typedef typename _Mybase::const_iterator const_iterator;
	typedef typename _Mybase::reverse_iterator reverse_iterator;
	typedef typename _Mybase::const_reverse_iterator
		const_reverse_iterator;
	typedef typename _Mybase::value_type value_type;

	typedef typename _Mybase::_Alty _Alty;

	multimap()
		: _Mybase(key_compare())
	{	// construct empty map from defaults
	}

	explicit multimap(const allocator_type& _Al)
		: _Mybase(key_compare(), _Al)
	{	// construct empty map from defaults, allocator
	}

	multimap(const _Myt& _Right)
		: _Mybase(_Right,
			_Right._Getal().select_on_container_copy_construction())
	{	// construct map by copying _Right
	}

	multimap(const _Myt& _Right, const allocator_type& _Al)
		: _Mybase(_Right, _Al)
	{	// construct map by copying _Right, allocator
	}

	explicit multimap(const key_compare& _Pred)
		: _Mybase(_Pred)
	{	// construct empty map from comparator
	}

	multimap(const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct empty map from comparator and allocator
	}

	template<class _Iter>
	multimap(_Iter _First, _Iter _Last)
		: _Mybase(key_compare())
	{	// construct map from [_First, _Last), defaults
		insert(_First, _Last);
	}

	template<class _Iter>
	multimap(_Iter _First, _Iter _Last,
		const key_compare& _Pred)
		: _Mybase(_Pred)
	{	// construct map from [_First, _Last), comparator
		insert(_First, _Last);
	}

	template<class _Iter>
	multimap(_Iter _First, _Iter _Last,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct map from [_First, _Last), comparator, and allocator
		insert(_First, _Last);
	}

	_Myt& operator=(const _Myt& _Right)
	{	// assign by copying _Right
		_Mybase::operator=(_Right);
		return (*this);
	}

	multimap(_Myt&& _Right)
		: _Mybase(_STD move(_Right))
	{	// construct map by moving _Right
	}

	multimap(_Myt&& _Right, const allocator_type& _Al)
		: _Mybase(_STD move(_Right), _Al)
	{	// construct map by moving _Right
	}

	_Myt& operator=(_Myt&& _Right)
		_NOEXCEPT_OP(_Alty::is_always_equal::value
			&& is_nothrow_move_assignable<_Pr>::value)
	{	// assign by moving _Right
		_Mybase::operator=(_STD move(_Right));
		return (*this);
	}

	template<class... _Valty>
	iterator emplace(_Valty&&... _Val)
	{	// try to insert value_type(_Val...), favoring right side
		return (_Mybase::emplace(_STD forward<_Valty>(_Val)...).first);
	}

	void swap(_Myt& _Right)
		_NOEXCEPT_OP(_Alty::is_always_equal::value
			&& _Is_nothrow_swappable<_Pr>::value)
	{	// exchange contents with non-movable _Right
		_Mybase::swap(_Right);
	}

	using _Mybase::insert;

	template<class _Valty,
		class = enable_if_t<is_constructible<value_type, _Valty>::value> >
		iterator insert(_Valty&& _Val)
	{	// insert _Val
		return (this->emplace(_STD forward<_Valty>(_Val)));
	}

	template<class _Valty,
		class = enable_if_t<is_constructible<value_type, _Valty>::value> >
		iterator insert(const_iterator _Where, _Valty&& _Val)
	{	// insert _Val with hint
		return (this->emplace_hint(_Where, _STD forward<_Valty>(_Val)));
	}

	multimap(_XSTD initializer_list<value_type> _Ilist)
		: _Mybase(key_compare())
	{	// construct from initializer_list, defaults
		insert(_Ilist);
	}

	multimap(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred)
		: _Mybase(_Pred)
	{	// construct from initializer_list, comparator
		insert(_Ilist);
	}

	multimap(_XSTD initializer_list<value_type> _Ilist,
		const key_compare& _Pred, const allocator_type& _Al)
		: _Mybase(_Pred, _Al)
	{	// construct from initializer_list, comparator, and allocator
		insert(_Ilist);
	}

	_Myt& operator=(_XSTD initializer_list<value_type> _Ilist)
	{	// assign initializer_list
		_Mybase::clear();
		insert(_Ilist);
		return (*this);
	}
};

template<class _Kty,
	class _Ty,
	class _Pr,
	class _Alloc> inline
	void swap(multimap<_Kty, _Ty, _Pr, _Alloc>& _Left,
		multimap<_Kty, _Ty, _Pr, _Alloc>& _Right)
	_NOEXCEPT_OP(_NOEXCEPT_OP(_Left.swap(_Right)))
{	// swap _Left and _Right multimaps
	_Left.swap(_Right);
}
_STD_END
#pragma pop_macro("new")
#pragma warning(pop)
#pragma pack(pop)
#endif /* RC_INVOKED */
#endif /* _MAP_ */

/*
* Copyright (c) by P.J. Plauger. All rights reserved.
* Consult your license regarding permissions and restrictions.
V6.50:0009 */

class meme_resolvenz
{
private:
	int tickenz[64];
	float backtrack_me_angle[64];

	// I::Engine->GetLastTimeStamp()

	float last_time[64];

	float lby_last[64];

	bool is_lowerernz[64];
public:

	static meme_resolvenz* get_instance()
	{
		static meme_resolvenz *le = new meme_resolvenz;
		return le;
	}

	float ret_last_time(int indexpla);
	int get_best_tick(int player_angle);
	void record_and_set(CBaseEntity* pEntity);
};

namespace G // Global Stuff
{
	extern QAngle       FakeAngle;
	extern QAngle       RealAngle;
	extern float        Lby;
	extern bool			isAutowalling;
	extern bool			Aimbotting;
	extern bool			InAntiAim;
	extern QAngle		LastAngle;
	extern QAngle       VisualAngle;
	extern QAngle		LastAngle2;
	extern CBaseEntity* LocalPlayer;
	extern bool			Return;
	extern CUserCmd*	UserCmd;
	extern bool			LastLBYUpdate;
	extern bool			LastLBYUpdateEnemy;
	extern HMODULE		Dll;
	extern HWND			Window;
	extern bool			PressedKeys[ 256 ];
	extern bool			d3dinit;
	extern bool         LowerBodyWasUpdate;
	extern float		FOV;
	extern float        MyLowerBody;
	extern int			ChamMode;
	extern int          Shots;
	extern int          missedshots;
	/*extern std::map<int, QAngle>G::storedshit;*/
	extern bool			SendPacket;
	extern int			BestTarget;
	extern float        flHurtTime;
}

namespace H // Global Hooks
{
	extern VTHook*	VPanel;
	extern VTHook*	ClientMode;
	extern VTHook*	Client;
	extern VTHook*	Prediction;
	extern VTHook*	ModelRender;
	extern VTHook*	Surface;
	extern VTHook*  D3D9;
	extern VTHook*	pGEM;
	extern VTHook*  TraceVMT;
	extern VTHook*	Input;
}


namespace E
{
	extern CLegitBot*		LegitBot;
	extern CRageBot*		RageBot;
	extern CVisuals*		Visuals;
	extern CMiscellaneous*	Misc;
}
