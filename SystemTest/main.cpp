#include "Entity.hpp"
#include "CPosition.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
	Entity e;

	e.addComponent<CPosition>(69);

	std::cout << "Component exists: " << e.hasComponent<CPosition>() << std::endl;

	std::cout << "Component position:" << e.getComponent<CPosition>().pos() << std::endl;


}
