#pragma once
#include <array>
#include <vector>
#include <bitset>
#include <cassert>
#include "Component.hpp"


class Entity
{
private:
	static const int MAX_COMPONENTS = 32;
	std::vector<std::unique_ptr<Component>> components_;
	std::bitset<MAX_COMPONENTS> component_bitset_;
	std::array<Component*, MAX_COMPONENTS> component_array_;
	bool exists_{ true };
	//id& entity_id_{Radio::generate_u_id(1)};

public:

	bool exists() const { return exists_; }

	//@method: update
	//calls update on all components belonging to entity
	void update(float mFT)
	{
		for (auto& c : component_array_)
		{
			if (c != nullptr)
				c->update(mFT);

		}
	}

	//@method: update
	//calls draw on all components belonging to entity
	void draw()
	{
		for (auto& c : component_array_)
		{
			if (c != nullptr)
				c->draw();
		}
	}

	//@method: hasComponent
	//checks if this entity has a certain component by Type
	template <typename T>
	bool hasComponent() const
	{
		return component_bitset_[getComponentTypeID<T>()];
	}

	//bool hasGroup(Group mGroup) const noexcept
	//{
	//}

	//void addGroup(Group mGroup) noexcept;
	//void delGroup(Group mGroup) noexcept { groupBitset[mGroup] = false; }

	//@method: addComponent
	//adds a component to this entity by forwarding TArgs to the component's constructor
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{
		// assert component does not already belong to entity
		assert(!hasComponent<T>());

		auto* new_comp(new T(std::forward<TArgs>(mArgs)...));

		//std::unique_ptr<Component> uPtr_comp{ new_comp };

		//components_.emplace_back(std::move(uPtr_comp));

		component_array_[getComponentTypeID<T>()] = new_comp;
		component_bitset_[getComponentTypeID<T>()] = true;

		//uPtr_comp->test();

		return *new_comp;
	}






	//@method: addComponent
	//returns a component by reference by type
	template <typename T>
	T& getComponent() const
	{
		assert(hasComponent<T>());

		auto ptr(component_array_[getComponentTypeID<T>()]);

		return *reinterpret_cast<T*>(ptr);
	}


	//@method: broadcast
	//broadcast a message to all components belonging to this entity
	void broadcast(int message)
	{
		for (int i = 0; i < MAX_COMPONENTS; i++)
		{
			if (component_array_[i] != nullptr)
			{
				component_array_[i]->recieve(message);
			}
		}
	}

	//@method: send
	//send a message to a component by Type belinging to this entity
	template<typename T>
	void send(int message)
	{
		if (hasComponent<T>())
			component_array_[getComponentTypeID<T>()]->recieve(message);
		else
			std::cout << typeid(T).name() << " does not exist in this entity. Message sent: " << message << std::endl;
	}


};
