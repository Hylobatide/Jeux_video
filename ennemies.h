#ifndef ENNEMIES_H
#define ENNEMIES_H

#include <vector>

#include <irrlicht.h>
using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;

class Ennemy 
{
  int id;
 
float lastX;
float lastZ;


core::vector3df positions_ennemies[9]={core::vector3df(-661,-59.99,-103),
  core::vector3df(-588.819,-43.99,106.052),
core::vector3df(77.8154,-59.99,-426.878),
core::vector3df(101.821,-123.99,437.066),
core::vector3df(825.323,-43.99,232.804),
core::vector3df(775.412,20.01,40.8938),
core::vector3df(648.218,212.01,130.452),
core::vector3df(910.532,372.01,288.241),
core::vector3df(319.288,340.01,-353.739)
};

public:

Ennemy();

  bool exist=true;
  float speed=0.0001;
  is::IAnimatedMeshSceneNode *node;
  void popEnnemies(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh,is::IMeshSceneNode *scene, int nbennemy);
  void deleteEnnemy();
  int collision(is::IAnimatedMeshSceneNode *perso, is::IAnimatedMeshSceneNode *node);
  void deplacementEnnemies();

};

#endif   