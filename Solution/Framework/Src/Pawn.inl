/*
	Untitled_Guys 2017
*/

namespace con
{
template <typename TPawnController>
inline TPawnController* Pawn::ResetController()
{
	static_assert( std::is_base_of_v<PawnController, TPawnController> );

	this->controller = std::make_unique<TPawnController>();
	this->controller->posses( this );
	return dynamic_cast<TPawnController*>( this->controller.get() );
}
}