/*
	Untitled_Guys 2017
*/

#pragma once

#include "Vec2.hpp"
#include "Drawable.hpp"
#include "Guideline.hpp"

namespace con
{
class Scene;

/* Basic class of objects chiearchy. You can rotate it, move and draw it.
	It has unique id so you can use it to distinguish different Actors.
*/
class Actor
{
public:
	Actor( const Actor& ) = default;
	Actor( Actor&& ) = default;
	Actor& operator=( const Actor& ) = default;
	Actor& operator=( Actor&& ) = default;
	Actor() = default;

	virtual ~Actor() = default;

	point GetPosition() const;
	degrees GetRotation() const;
	int32 GetUniqueID() const;
	Drawable& DrawableRef();
	NotNull<Scene*> GetScene();

	void SetPosition( const point& position_ );
	void SetRotation( degrees rotation_ );
	void _SetUniqueID( int32 uniqueID_ );
	void _SetScene( Scene& scene_ );

	void Kill();
	void Rotate( degrees angle );
	void Move( const Vec2f& force );

	virtual void Update();
	void Draw( sf::RenderTarget& target );

private:
	point position = point::ZERO;
	degrees rotation = 0;
	int32 uniqueID = -1;
	Drawable toDraw;
	Scene* scene = nullptr;

	/* 361 to 1, 400 to 40 (x - 360 unltil x <= 360
		Converts to abs value if negative.
	*/
	degrees convertToCorrectDegrees( degrees in );
};
}