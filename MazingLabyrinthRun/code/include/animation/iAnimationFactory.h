#ifndef I_ANIMATION_FACTORY
#define I_ANIMATION_FACTORY

template<typename T>
class IAnimationFactory {
public:
	virtual Animation createAnimation() const = 0;
};

#endif