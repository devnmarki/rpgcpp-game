#ifndef DIRECTIONCOMPONENT_HPP
#define DIRECTIONCOMPONENT_HPP

#include <unordered_map>

enum class Directions {
	None,
	Up,
	Down,
	Left,
	Right
};

inline const std::unordered_map<Directions, std::string> DIRECTION_TO_STRING = {
	{ Directions::None, "none" },
	{ Directions::Up, "up" },
	{ Directions::Down, "down" },
	{ Directions::Left, "left" },
	{ Directions::Right, "right" }
};

struct DirectionComponent {
	Directions direction = Directions::None;
};

#endif