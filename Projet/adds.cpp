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


  float const scale = 1.0f;

  nb=nbAdd;
 float X= positions_coffres[nbAdd].X;
  float Y=positions_coffres[nbAdd].Y;
  float Z = positions_coffres[nbAdd].Z;

  node = smgr->addAnimatedMeshSceneNode(mesh);
  node->setMaterialFlag(iv::EMF_LIGHTING, false);
  node->setPosition(core::vector3df(X, Y, Z));
  node->setScale(core::vector3df(scale, scale, scale));
  //node->drop();

  scene::ITriangleSelector *selector;
  selector = smgr->createOctreeTriangleSelector(scene->getMesh(), scene);
  scene->setTriangleSelector(selector);

  const core::aabbox3d<f32>& box = node->getBoundingBox();
  core::vector3df radius = box.MaxEdge- box.getCenter();
  radius.Y=radius.Y/2.0;






  is::ISceneNodeAnimatorCollisionResponse *collision = smgr->createCollisionResponseAnimator(selector, node, radius,ic::vector3df(0, -0.5, 0));
  node->addAnimator(collision);

  const core::aabbox3d<f32>& scenebox = scene->getTransformedBoundingBox();
  core::vector3df sceneradius = scenebox.MaxEdge- scenebox.getCenter();

  
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