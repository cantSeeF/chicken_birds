#include"egg.h"

bool Egg::init() {
	if (!Sprite::init()){
		return false;
	}
	this->initWithFile("image/egg.png");

	PhysicsBody *eggBody = PhysicsBody::create(1);
	eggBody->addShape(PhysicsShapeBox::create(Size(8, 12)));
	//eggBody->setCategoryBitmask(1);
	eggBody->setCollisionBitmask(1);
	eggBody->setContactTestBitmask(1);
	eggBody->setDynamic(true);
	eggBody->setLinearDamping(0.0f);
	//设置弹性
	eggBody->getShape(0)->setRestitution(0.0f);
	eggBody->getShape(0)->setFriction(5);
	//不能旋转
	eggBody->setRotationEnable(false);
	this->setPhysicsBody(eggBody);
	return true;
}