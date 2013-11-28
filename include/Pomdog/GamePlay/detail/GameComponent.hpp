//
//  Copyright (C) 2013 mogemimi.
//
//  Distributed under the MIT License.
//  See accompanying file LICENSE.md or copy at
//  http://enginetrouble.net/pomdog/LICENSE.md for details.
//

#ifndef POMDOG_DETAIL_GAMECOMPONENT_HPP
#define POMDOG_DETAIL_GAMECOMPONENT_HPP

#if (_MSC_VER > 1000)
#	pragma once
#endif

#include "../../Config/FundamentalTypes.hpp"
#include <typeinfo>

namespace Pomdog {
namespace Details {

// in C++03:
//template <class T>
//struct ComponentTypeID
//{
//	static std::size_t const value;
//private:
//	static std::uint8_t const storage = 0;
//};
//
//template <class T>
//std::size_t const ComponentTypeID<T>::value = reinterpret_cast<std::size_t>(&ComponentTypeID<T>::storage);

template <class T>
struct ComponentTypeID
{
	static std::size_t const value;
};

template <class T>
std::size_t const ComponentTypeID<T>::value = typeid(T).hash_code();

class GameComponent
{
public:
	GameComponent() = default;
	GameComponent(GameComponent const&) = default;
	GameComponent(GameComponent &&) = default;

	virtual ~GameComponent() = default;

	GameComponent& operator=(GameComponent const&) = default;
	GameComponent& operator=(GameComponent &&) = default;

	virtual std::size_t GetHashCode() const = 0;
};

template <class T>
class IntrusiveComponent final: public GameComponent
{
public:
	static_assert(std::is_class<T>::value || std::is_enum<T>::value, "T is class or enum");
	
	IntrusiveComponent() = default;
	~IntrusiveComponent() = default;
	
	explicit IntrusiveComponent(T const& source)
		: data(source)
	{}

	std::size_t GetHashCode() const
	{
		return ComponentTypeID<T>::value;
	}
	
	T const* Get() const
	{
		return &data;
	}
	
	T* Get()
	{
		return &data;
	}

private:
	T data;
};

}// namespace Details
}// namespace Pomdog

#endif // !defined(POMDOG_DETAIL_GAMECOMPONENT_HPP)