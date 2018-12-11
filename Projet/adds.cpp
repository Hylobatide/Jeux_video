#include <irrlicht.h>
#include "adds.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

Adds::Adds()
{

}

void Adds::popAdds(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh)

{

	float const scale = 0.8f;
  float const X = rand() % 200;
  float const Z = rand() % 200;
  node = smgr->addAnimatedMeshSceneNode(mesh);
  node->setMaterialFlag(iv::EMF_LIGHTING, false);
  node->setPosition(core::vector3df(X, -10.0f, Z));
  node->setScale(core::vector3df(scale, scale, scale));
}