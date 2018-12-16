#ifndef ADDS_H
#define ADDS_H
#include <vector>


namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;


class Adds 
{
	int nb;

public:
  Adds();

  
  bool exist=true;

  is::IAnimatedMeshSceneNode *node;
  void popAdds(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh,is::IMeshSceneNode *scene, int nbAdd);
  void deleteAdds();
	int collision(is::IAnimatedMeshSceneNode *perso, is::IAnimatedMeshSceneNode *node);
};



#endif   