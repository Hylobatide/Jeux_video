#include <irrlicht.h>
#include "adds.h"
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

Adds::Adds()
{

}

void Adds::popAdds(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh,is::IMeshSceneNode *scene,int nbAdd)

{

	//srand(time(0));

  float const scale = 1.0f;

  float  X = rand()%1000;

  float  Z = rand()%1000;
  nb=nbAdd;


  node = smgr->addAnimatedMeshSceneNode(mesh);
  node->setMaterialFlag(iv::EMF_LIGHTING, false);
  node->setPosition(core::vector3df(X, 0.0, Z));
  node->setScale(core::vector3df(scale, scale, scale));
  //node->drop();

  scene::ITriangleSelector *selector;
  selector = smgr->createOctreeTriangleSelector(scene->getMesh(), scene);
  scene->setTriangleSelector(selector);

  const core::aabbox3d<f32>& box = node->getBoundingBox();
  core::vector3df radius = box.MaxEdge- box.getCenter();
  radius.Y=radius.Y/2.0;
        //radius.X=radius.X+10.0;
        //radius.Y=radius.Y+10.0;



  is::ISceneNodeAnimatorCollisionResponse *collision = smgr->createCollisionResponseAnimator(selector, node, radius,ic::vector3df(0, -0.5, 0));
  node->addAnimator(collision);

  const core::aabbox3d<f32>& scenebox = scene->getTransformedBoundingBox();
  core::vector3df sceneradius = scenebox.MaxEdge- scenebox.getCenter();
    //fixer la collision avec les murs 
  // if((sceneradius.Y>radius.Y)||(sceneradius.Z>radius.Z))
  // {
  //   node->remove();
  //   exist=false;
  // }

  
}

int Adds::collision(is::IAnimatedMeshSceneNode *perso, is::IAnimatedMeshSceneNode *node)
{

  return perso->getTransformedBoundingBox().intersectsWithBox(node->getTransformedBoundingBox());
}
void Adds::deleteAdds()
{
  node->remove();
  exist=false;
}

