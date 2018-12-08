#ifndef ADDS_H
#define ADDS_H



namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;


class Adds 
{


public:
  Adds();
  is::IAnimatedMeshSceneNode *node;
  void popAdds(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh);

};



#endif   