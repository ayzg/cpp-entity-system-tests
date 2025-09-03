#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <cstddef>

class Component
{
public:
	virtual void init() {}
	virtual void update(float m_ft) {}
	virtual void draw() {}
	virtual void recieve(int message) = 0;

	virtual ~Component() = default;
};


//Generates a unique identifier for component objects
inline std::size_t getUniqueComponentID() noexcept
{
	static std::size_t last_id{ 0u };
	return last_id++;
}


//Gets a component ID
template <typename T>
inline std::size_t getComponentTypeID() noexcept
{

	static_assert(std::is_base_of<Component, T>::value,
		"T must inherit from Component");

	static std::size_t typeID{ getUniqueComponentID() };

	return typeID;
}

#endif // COMPONENT_HPP
