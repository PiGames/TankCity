/*
	Untitled_Guys 2017
*/

namespace con
{
template <typename TPawnController>
inline void Pawn::ResetController()
{
	static_assert( std::is_base_of_v<PawnController, TPawnController> );

	this->controller = std::make_unique<TPawnController>();
	this->controller->owner = this;
}
}