#include <irrlicht.h>
#include "events.h"
#include "gui_ids.h"
#include <iostream>
#include "adds.h"
#include <vector>

using namespace irr;
using namespace std;
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
  // menu->addItem(L"Help", -1 , true, true);

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
  // submenu = menu->getSubMenu(2);
  // submenu->addItem(L"About...", MENU_ABOUT);
}

static void create_window(ig::IGUIEnvironment *gui)
{
  // La fenêtre
  ig::IGUIWindow *window = gui->addWindow(ic::rect<s32>(420,25, 620,460), false, L"First Menu");
  gui->addButton(ic::rect<s32>(40,74, 140,92), window, MENU_NEW_GAME, L"Start!");
}

int main()
{
  int score=0;
  int nbAdds=100;

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
  

  std::vector<Adds> v;

  Adds add;

  for (int i = 0; i < nbAdds; ++i)
  {

    add.popAdds(driver,smgr,mesh2,scene,i);
    v.push_back(add);
  }


 //add.popAdds(driver,smgr,mesh2,scene,0);



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

  receiver.states[1]=false;//bouge pas

  // Création du Gui

//Choix de la police de caractères
  ig::IGUISkin* skin = gui->getSkin();
  ig::IGUIFont* font = gui->getFont("data/fontlucida.png");
  skin->setFont(font);



// La barre de menu
  create_menu(gui);
// LA première fenetre
  create_window(gui);


  iv::ITexture *digits[10];
  digits[0] = driver->getTexture("data/Chiffres/0.png");
  digits[1] = driver->getTexture("data/Chiffres/1.png");
  digits[2] = driver->getTexture("data/Chiffres/2.png");
  digits[3] = driver->getTexture("data/Chiffres/3.png");
  digits[4] = driver->getTexture("data/Chiffres/4.png");
  digits[5] = driver->getTexture("data/Chiffres/5.png");
  digits[6] = driver->getTexture("data/Chiffres/6.png");
  digits[7] = driver->getTexture("data/Chiffres/7.png");
  digits[8] = driver->getTexture("data/Chiffres/8.png");
  digits[9] = driver->getTexture("data/Chiffres/9.png");

    // Création des places pour les chiffres
  ig::IGUIImage *score_10000 = gui->addImage(ic::rect<s32>(15,15,  55,55)); score_10000->setScaleImage(true);
  ig::IGUIImage *score_1000  = gui->addImage(ic::rect<s32>(55,15,  95,55)); score_1000->setScaleImage(true);
  ig::IGUIImage *score_100   = gui->addImage(ic::rect<s32>(95,15,  135,55)); score_100->setScaleImage(true);
  ig::IGUIImage *score_10    = gui->addImage(ic::rect<s32>(135,15, 175,55)); score_10->setScaleImage(true);
  ig::IGUIImage *score_1     = gui->addImage(ic::rect<s32>(175,15, 215,55)); score_1->setScaleImage(true);


  while(device->run())
  {


    camera->setTarget(node->getPosition()+core::vector3df(0.0,30.0,0.0));

    driver->beginScene(true, true, iv::SColor(100,150,200,255));
    gui->drawAll();
   //std::cout<<"collision = "<<collision<<std::endl;

    if(receiver.game_on){
    // Dessin de la scène :
      smgr->drawAll();

      for (int i = 0; i < int(v.size()); ++i)
      {
        if(v[i].exist)
        {

          if(v[i].collision(node,v[i].node)==1)
          {
            v[i].deleteAdds();
            score++;
          }

        }
      }
      if (score == 50000) score = -1;
      // Mise à jour du score :
      score_10000->setImage(digits[(score / 10000) % 10]);
      score_1000->setImage(digits[(score / 1000) % 10]);
      score_100->setImage(digits[(score / 100) % 10]);
      score_10->setImage(digits[(score / 10) % 10]);
      score_1->setImage(digits[(score / 1) % 10]);
      gui->drawAll();
    }

    receiver.gestion_deplacement(receiver.states, node);
//std::cout<<"SCORE = "<<score<<std::endl;

    driver->endScene();

  }
  device->drop();

  return 0;
}
