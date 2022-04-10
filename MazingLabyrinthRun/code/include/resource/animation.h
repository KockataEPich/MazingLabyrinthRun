#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

#include <exception>
#include <string>
#include <vector>

#include "textureEnum.h"

class EndAnimationException : public std::exception {
public:
	explicit EndAnimationException(std::string str) noexcept : m_message(std::move(str)) {}
	const char* what() const noexcept override { return m_message.c_str(); }

private:
	std::string m_message;
};

using Repeat = struct { int numberOfTimes; };
using AnimationSpeed = struct { float speed; };


class Animation {
public:
	Animation(){};

	Animation(const std::string& name, std::vector<Textures::ID>& frames, const Repeat& repeat, const AnimationSpeed& speed)
	    : m_name{name}
	    , m_frames{&frames}
	    , m_repeatNumber{repeat.numberOfTimes}
	    , m_speed{speed.speed} {};

	void nextFrame();
	Textures::ID currentFrame() { return m_frames->at(m_frameIndex); }

	void resetAnimation();
	bool animationCycleFinish();

	float speed() { return m_speed; }
	bool operator==(const Animation animation);
	void operator=(const Animation animation);

protected:
	std::string m_name;
	int m_frameIndex = 0;
	int m_timesPlayed = 0;
	int m_repeatNumber;
	float m_speed;
	std::vector<Textures::ID>* m_frames;
};

#endif