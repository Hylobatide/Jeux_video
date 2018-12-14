#ifndef ADDS_H
#define ADDS_H
#include <vector>

using namespace irr;
namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;


class Adds 
{
	int nb;
	
	  core::vector3df positions_coffres[52]={core::vector3df(-661,-59.99,-103),
core::vector3df(-561,-59.99,-103),
core::vector3df(-461,-59.99,-103),
core::vector3df(-341,-59.99,-103),
core::vector3df(-231,-59.99,-103),
core::vector3df(-151,-59.99,-103),
core::vector3df(-41,-59.99,-103),
core::vector3df(99,-59.99,-103),
core::vector3df(99,-59.99,27),
core::vector3df(99,-67.0903,157.024),
core::vector3df(99,-114.679,347.378),
core::vector3df(99,-123.99,517.521),
core::vector3df(264.626,-123.99,688.017),
core::vector3df(642.699,-91.6231,592.462),
core::vector3df(620.862,-43.99,301.79),
core::vector3df(923.154,-43.99,281.611),
core::vector3df(1249.48,-11.99,106.062),
core::vector3df(1168.02,-11.99,-104.844),
core::vector3df(851.578,-11.99,-114.175),
core::vector3df(713.822,20.01,93.7218),
core::vector3df(318.32,84.01,139.227),
core::vector3df(330.35,212.01,409.628),
core::vector3df(653.19,212.01,300.93),
core::vector3df(728.607,212.01,-137.941),
core::vector3df(882.408,212.01,-182.043),
core::vector3df(956.137,372.01,246.349),
core::vector3df(702.645,372.01,333.624),
core::vector3df(413.149,372.01,169.883),
core::vector3df(321.464,372.01,301.622),
core::vector3df(306.496,372.01,474.389),
core::vector3df(-134.633,276.01,609.23),
core::vector3df(-179.392,276.01,175.246),
core::vector3df(-321.737,276.01,-122.038),
core::vector3df(-146.995,276.01,-348.734),
core::vector3df(-434.835,276.01,-365.369),
core::vector3df(-684.869,276.01,-530.235),
core::vector3df(811.99,-11.99,-434.464),
core::vector3df(758.173,-11.99,-668.345),
core::vector3df(473.199,-11.99,-624.63),
core::vector3df(264.513,-11.99,-484.04),
core::vector3df(413.159,-43.99,-266.929),
core::vector3df(373.22,-43.99,-40.4228),
core::vector3df(-576.408,-43.99,70.2355),
core::vector3df(-577.277,-83.99,369.756),
core::vector3df(-559.482,-75.99,703.121),
core::vector3df(-344.663,-43.99,705.39),
core::vector3df(-338.741,84.01,324.499),
core::vector3df(-152.881,116.01,341.717),
core::vector3df(-294.76,116.01,160.508),
core::vector3df(-329.541,244.01,312.519),
core::vector3df(-133.244,276.01,314.26),
core::vector3df(-383.838,116.01,695.349)};
public:
  Adds();
  
  
  bool exist=true;

  is::IAnimatedMeshSceneNode *node;
  void popAdds(iv::IVideoDriver *driver, is::ISceneManager *smgr, is::IAnimatedMesh *mesh,is::IMeshSceneNode *scene, int nbAdd);
  void deleteAdds();
	int collision(is::IAnimatedMeshSceneNode *perso, is::IAnimatedMeshSceneNode *node);
};



#endif   