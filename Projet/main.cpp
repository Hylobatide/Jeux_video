#include <irrlicht.h>

using namespace irr;
namespace iv = irr::video;
namespace is = irr::scene;

int main()
{
  // Création de la fenêtre et du système de rendu.
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();

  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Dessin de la scène :
    smgr->drawAll();
    // 
    driver->endScene();
  }
  device->drop();

  return 0;
}
