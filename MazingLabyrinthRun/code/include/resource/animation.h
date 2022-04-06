#ifndef ANIMATION_HEADER_H
#define ANIMATION_HEADER_H

#include <exception>
#include <string>
#include <vector>

class EndAnimationException : public std::exception {
public:
	explicit EndAnimationException(std::string str) noexcept : m_message(std::move(str)) {}
	const char* what() const noexcept override { return m_message.c_str(); }

private:
	std::string m_message;
};

using Repeat = struct { int numberOfTimes; };
using AnimationSpeed = struct { float speed; };

template<typename T>
class Animation {
public:
	Animation(){};

	Animation(const std::string& name, std::vector<T>& frames, const Repeat& repeat, const AnimationSpeed& speed)
	    : m_name{name}
	    , m_frames{&frames}
	    , m_repeatNumber{repeat.numberOfTimes}
	    , m_speed{speed.speed} {};

	void nextFrame();
	T currentFrame() { return m_frames->at(m_frameIndex); }

	void resetAnimation();
	bool animationCycleFinish();

	float speed() { return m_speed; }
	bool operator==(const Animation<T> animation);
	void operator=(const Animation<T> animation);

protected:
	std::string m_name;
	int m_frameIndex = 0;
	int m_timesPlayed = 0;
	int m_repeatNumber;
	float m_speed;
	std::vector<T>* m_frames;
};

template<typename T>
void Animation<T>::nextFrame() {
	m_frameIndex++;
	if (m_frameIndex == m_frames->size()) throw EndAnimationException("The end of the animation has been reached");
}

template<typename T>
void Animation<T>::resetAnimation() {
	m_frameIndex = 0;
	m_timesPlayed++;
}

template<typename T>
bool Animation<T>::animationCycleFinish() {
	if (m_repeatNumber == -1) return false;
	if (m_timesPlayed < m_repeatNumber) return false;
	return true;
}

template<typename T>
bool Animation<T>::operator==(const Animation<T> animation) {
	if (m_name == animation.m_name) return true;
	return false;
}

template<typename T>
void Animation<T>::operator=(const Animation<T> animation) {
	m_name = animation.m_name;
	m_frames = animation.m_frames;
	m_repeatNumber = animation.m_repeatNumber;
	m_speed = animation.m_speed;

	m_timesPlayed = 0;
	m_frameIndex = 0;
}
#endif