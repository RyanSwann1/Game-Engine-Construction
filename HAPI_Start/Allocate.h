#pragma once

#include <atomic>
#include <memory>



template <class T>
class Allocator : public std::allocator<T>
{

private:
	using Base = std::allocator<T>;
	using Pointer = typename std::allocator_traits<Base>::pointer;
	using SizeType = typename std::allocator_traits<Base>::size_type;

public:
	Allocator() = default;

	template <typename U>
	Allocator(const Allocator<U>& other)
		: Base(other)
	{}
	
	Pointer allocate(SizeType n)
	{
		return Base::allocate(n);
	}
	
	void deallocate(Pointer p, SizeType n)
	{
		Base::deallocate(p, n);
	}

};