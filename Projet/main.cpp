#include <irrlicht.h>
#include "events.h"
#include "gui_ids.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

static void create_menu(ig::IGUIEnvironment *gui)
{
  ig::IGUIContextMenu *submenu;

  // Les trois menus principaux
  ig::IGUIContextMenu *menu = gui ->addMenu();
  menu->addItem(L"File", -1 , true, true);
  menu->addItem(L"Debug", -1 , true, true);
  menu->addItem(L"Help", -1 , true, true);

  // Le contenu de menu File
  submenu = menu->getSubMenu(0);
  submenu->addItem(L"New game...", MENU_NEW_GAME);
  submenu->addSeparator();
  submenu->addItem(L"Quit", MENU_QUIT);

  // Le contenu du menu Debug :
  submenu = menu->getSubMenu(1);
  submenu->addItem(L"Bounding Box",   MENU_BOUNDING_BOX);
  submenu->addItem(L"Show Normals",   MENU_NORMALS);
  submenu->addItem(L"Show Triangles", MENU_TRIANGLES);
  submenu->addItem(L"Transparency",   MENU_TRANSPARENCY);

  // Le contenu du menu Help :
  submenu = menu->getSubMenu(2);
  submenu->addItem(L"About...", MENU_ABOUT);
}

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
  scene->setPosition ( core :: vector3df ( 0 , -40 , 0));




   // Chargement de notre personnage
  is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");
 // Attachement de notre personnage dans la scène
  is::IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setMD2Animation(irr::scene::EMAT_STAND);
  textures.push_back(driver->getTexture("data/base.pcx"));
  textures.push_back(driver->getTexture("data/red_texture.pcx"));
  textures.push_back(driver->getTexture("data/blue_texture.pcx"));
  node->setMaterialTexture(0, textures[0]);
  receiver.set_gui(gui);
  receiver.set_node(node);
  receiver.set_textures(textures);

  scene::ICameraSceneNode *camera = smgr->addCameraSceneNodeFPS ();

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
  //camera->addAnimator(anim);
  node->addAnimator(anim);
  node->addAnimator(anim);

// Création du Gui

//Choix de la police de caractères
  ig::IGUISkin* skin = gui->getSkin();
  ig::IGUIFont* font = gui->getFont("data/fontlucida.png");
  skin->setFont(font);

// La barre de menu

  create_menu(gui);



  while(device->run())
  {
    driver->beginScene(true, true, iv::SColor(100,150,200,255));

    // Dessin de la scène :

    smgr->drawAll();

    // Dessin de l'interface
    
    gui->drawAll();
    driver->endScene();
  }
  device->drop();

  return 0;
}
