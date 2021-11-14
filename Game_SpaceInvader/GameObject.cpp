#include"GameObject.h"
GameObject::GameObject(string image, COORD loc)
{
	this->image = image;
	this->loc = loc;
}
string GameObject::getImage()
{
	return image;
}
COORD GameObject::getLoc()
{
	return loc;
}
void GameObject::setLoc(COORD loc)
{
	this->loc = loc;
}