/*
	Untitled_Guys 2017
*/

namespace con
{
template <typename TPawnController>
inline TPawnController* ResetController()
{
	this->controller = std::make_unique<TPawnController>();
	this->controller->posses( this );
	return this->controller.get();
}
}