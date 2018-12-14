#include <irrlicht.h>
#include "ennemies.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

Ennemy::Ennemy()
{

}


void Ennemy::popEnnemies(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh,is::IMeshSceneNode *scene,int nbennemy)

{

	//srand(time(0));

	float const scale = 20.0f;

  // float  X = rand()%1000;
  // float  Z = rand()%1000;

	float X= positions_ennemies[nbennemy].X;
	float Y=positions_ennemies[nbennemy].Y;
	float Z = positions_ennemies[nbennemy].Z;
	id=nbennemy;


	node = smgr->addAnimatedMeshSceneNode(mesh);
	node->setMaterialFlag(iv::EMF_LIGHTING, false);
	node->setPosition(core::vector3df(X, Y, Z));
	node->setScale(core::vector3df(scale, scale, scale));



	scene::ITriangleSelector *selector;
	selector = smgr->createOctreeTriangleSelector(scene->getMesh(), scene);
	scene->setTriangleSelector(selector);

	const core::aabbox3d<f32>& box = node->getBoundingBox();
	core::vector3df radius = box.MaxEdge- box.getCenter();
	radius.Y=radius.Y/2.0;




	is::ISceneNodeAnimatorCollisionResponse *collision = smgr->createCollisionResponseAnimator(selector, node, radius,ic::vector3df(0, -10, 0));
	node->addAnimator(collision);




}

int Ennemy::collision(is::IAnimatedMeshSceneNode *perso, is::IAnimatedMeshSceneNode *node)
{

	return perso->getTransformedBoundingBox().intersectsWithBox(node->getTransformedBoundingBox());
}
void Ennemy::deleteEnnemy()
{
	node->remove();
	exist=false;
}


void Ennemy::deplacementEnnemies()
{
	    ic::vector3df position = node->getPosition();
    	ic::vector3df rotation = node->getRotation();
    	int i =0;
    	
    while(i<10000)
    {
    	lastX=position.X;
    	lastZ=position.Z;
    	position.X += speed * cos(rotation.Y * M_PI / 180.0);
      	position.Z += -speed * sin(rotation.Y * M_PI / 180.0);

      	// if(int(lastX)==int(position.X) && int(lastZ)==int(position.Z))
      	// {
      	// 	rotation.Y+=180;
      	// }
      		if(i>5000)
      	{
      		rotation.Y=180;
      	}
      	node->setPosition(position);
    	node->setRotation(rotation);
      	i++;
    }
    	

    	



}
