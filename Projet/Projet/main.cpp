#include <irrlicht.h>
#include "events.h"
#include "gui_ids.h"
#include <iostream>
#include "adds.h"

using namespace irr;
using namespace std;
namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;


int main()
{

  EventReceiver receiver;
  std::vector<iv::ITexture*> textures;

  // Création de la fenêtre et du système de rendu.
  IrrlichtDevice *device = createDevice(iv::EDT_OPENGL,
    ic::dimension2d<u32>(1280, 960),
    16, false, false, false, &receiver);

  iv::IVideoDriver  *driver = device->getVideoDriver();
  is::ISceneManager *smgr = device->getSceneManager();
  ig::IGUIEnvironment *gui = device->getGUIEnvironment();
// Ajout de l’archive qui contient entre autres un niveau complet
  device->getFileSystem()->addFileArchive("data/ikzdm1.pk3");
//Onchargeunbsp(unniveau)enparticulier:
  is::IAnimatedMesh *scenemesh=smgr->getMesh("ikzdm1.bsp");
  is::IMeshSceneNode *scene;
  scene=smgr->addOctreeSceneNode(scenemesh->getMesh(0),nullptr,-1,1024);
// Translation pour que nos personnages soient dans le dé cor
  scene->setPosition ( core :: vector3df ( 0 , -50 , 0));




   // Chargement de notre personnage
  is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");
  is::IAnimatedMesh *mesh2 = smgr->getMesh("data/GoldTrunk/GoldTrunk.obj");

 // Attachement de notre personnage dans la scène
  is::IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setMD2Animation(irr::scene::EMAT_STAND);
  textures.push_back(driver->getTexture("data/base.pcx"));
  textures.push_back(driver->getTexture("data/red_texture.pcx"));
  textures.push_back(driver->getTexture("data/blue_texture.pcx"));
  node->setMaterialTexture(0, textures[0]);
  

//2e perso
 /* is::IAnimatedMeshSceneNode *perso2 = smgr->addAnimatedMeshSceneNode(mesh2, nullptr,0,core::vector3df(0,0,0),core::vector3df(0,0,0),core::vector3df(1.0f, 1.0f, 1.0f) );
  perso2->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  perso2->setMD2Animation(irr::scene::EMAT_STAND);*/

  Adds add;
  add.popAdds(driver,smgr,mesh2);


  receiver.set_gui(gui);
  receiver.set_node(node);
  receiver.set_textures(textures);

  scene::ICameraSceneNode *camera = smgr->addCameraSceneNode(node, core::vector3df(-50.0,40.0,0.0),core::vector3df(0.0,0.0,0.0));

  // Création du triangle selector
  scene::ITriangleSelector *selector;
  selector = smgr->createOctreeTriangleSelector(scene->getMesh(), scene);
  scene->setTriangleSelector(selector);
  scene::ISceneNodeAnimator *anim;
  anim = smgr->createCollisionResponseAnimator(selector, 
                                               node,  // Le noeud que l'on veut gérer
                                               ic::vector3df(10, 20, 10), // "rayons" de la caméra
                                               ic::vector3df(0, -10, 0),  // gravité
                                               ic::vector3df(0, 30, 0));  // décalage du centre
  
  node->addAnimator(anim);



  while(device->run())
  {


    camera->setTarget(node->getPosition()+core::vector3df(0.0,30.0,0.0));

    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Dessin de la scène :
    smgr->drawAll();


     driver->endScene();
   }
   device->drop();

   return 0;
 }
