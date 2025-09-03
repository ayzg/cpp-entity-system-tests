#ifndef CPOSITION_HPP
#define CPOSITION_HPP
#include "Component.hpp"



class CPosition : public Component
{
public:
	int position;
	void init() override {}
	void update(float m_ft) override {}
	void draw() override {}
	void recieve(int message) override {};
	CPosition() = default;
	CPosition(const int& m_position) : position(m_position) {}

	float pos() const noexcept { return position; }
};

#endif // CPOSITION_HPP
