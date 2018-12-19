#include <irrlicht.h>
#include "events.h"
#include "gui_ids.h"
#include <iostream>
#include "adds.h"
#include <vector>
#include  "ennemies.h"
#include "vector2d.h"
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
  gui->addStaticText(L"Difficulty:", ic::rect<s32>(40,100, 140,118), false, false, window);
  ig::IGUIComboBox *cbox = gui->addComboBox(ic::rect<s32>(40,120, 140,138), window, MENU_DIFFICULTY);
  cbox->addItem(L"Choix de la difficulté");
  cbox->addItem(L"Easy",DIFFICULTY_EASY);
  cbox->addItem(L"Normal",DIFFICULTY_NORMAL);
  cbox->addItem(L"Difficult",DIFFICULTY_HARD);
}

int main()
{
  int score=0;
  int timer;
  int nbAdds=52;
  int nbennemy=9;
  float speed = 2;
  
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

  auto texture_game_over = driver->getTexture("data/game_over.tga");



   // Chargement de notre personnage
  is::IAnimatedMesh *mesh = smgr->getMesh("data/tris.md2");
  is::IAnimatedMesh *mesh2 = smgr->getMesh("data/GoldTrunk/GoldTrunk.obj");
  is::IAnimatedMesh *ennemy = smgr->getMesh("data/ennemies/Kopaka.obj");
 // Attachement de notre personnage dans la scène
  is::IAnimatedMeshSceneNode *node = smgr->addAnimatedMeshSceneNode(mesh);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setMD2Animation(irr::scene::EMAT_STAND);
  textures.push_back(driver->getTexture("data/base.pcx"));
  textures.push_back(driver->getTexture("data/red_texture.pcx"));
  textures.push_back(driver->getTexture("data/blue_texture.pcx"));
  node->setMaterialTexture(0, textures[0]);
  node->setPosition(core::vector3df(-731,0,-103));


 // add.popAdds(driver,smgr,mesh2,scene,0);



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
                                               ic::vector3df(25, 20, 25), // "rayons" de la caméra
                                               ic::vector3df(0, -5, 0),  // gravité
                                               ic::vector3df(0, 30, 0));  // décalage du centre
  
  node->addAnimator(anim);

  



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

  // Création des places pour les chiffres
  ig::IGUIImage *timer_10000 = gui->addImage(ic::rect<s32>(15+1050,15,  55+1050,55)); timer_10000->setScaleImage(true);
  ig::IGUIImage *timer_1000  = gui->addImage(ic::rect<s32>(55+1050,15,  95+1050,55)); timer_1000->setScaleImage(true);
  ig::IGUIImage *timer_100   = gui->addImage(ic::rect<s32>(95+1050,15,  135+1050,55)); timer_100->setScaleImage(true);
  ig::IGUIImage *timer_10    = gui->addImage(ic::rect<s32>(135+1050,15, 175+1050,55)); timer_10->setScaleImage(true);
  ig::IGUIImage *timer_1     = gui->addImage(ic::rect<s32>(175+1050,15, 215+1050,55)); timer_1->setScaleImage(true);

receiver.states[1]=false;//bouge pas
receiver.states[3]=false;//bouge pas
receiver.states[0]=false;
receiver.diff[0]=true; //Difficulté mis à facile




std::vector<Adds> v;

Adds add;

for (int i = 0; i < nbAdds; ++i)
{

  add.popAdds(driver,smgr,mesh2,scene,i);
  v.push_back(add);
}

std::vector<Ennemy> w;
Ennemy ennemies;
for (int i = 0; i < nbennemy; i++)
{

  ennemies.popEnnemies(driver,smgr,ennemy,scene,i);
  w.push_back(ennemies);
}



while(device->run())
{

  ic::vector3df position = node->getPosition();
  ic::vector3df rotation = node->getRotation();
  camera->setTarget(node->getPosition()+core::vector3df(0.0,30.0,0.0));

  driver->beginScene(true, true, iv::SColor(100,150,200,255));
  gui->drawAll();
// Gestion de la difficulté
  if(receiver.diff[0] == true && receiver.game_on == false)
  {
    timer=1000;
  }
  else if (receiver.diff[1] == true && receiver.game_on == false)
  {
    timer = 2500;
    speed=4;
  }
  else if (receiver.diff[2] == true && receiver.game_on == false)
  {
    timer = 2000;
    speed=6;
  }

  if(receiver.game_on){
    // Dessin de la scène :
    
    
    
    
    smgr->drawAll();
    gui->drawAll();

    timer--;
    
    
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

    for (int j = 0; j < nbennemy; j++)
    {
      w[j].deplacementEnnemies(speed);
      if(w[j].collision(node, w[j].node)==1)
      {
        position.X += -5 * cos(rotation.Y * M_PI / 180.0);
        position.Z += 5 * sin(rotation.Y * M_PI / 180.0);
        node->setPosition(position);
        node->setRotation(rotation);
        if(w[j].touche==false)
        {
          if(score>0)
          {
            score--;
          }
          w[j].touche=true;
        }

        

      }
      w[j].touche=false;
    }
    if (score == 50000) score = -1;
      // Mise à jour du score :
    score_10000->setImage(digits[(score / 10000) % 10]);
    score_1000->setImage(digits[(score / 1000) % 10]);
    score_100->setImage(digits[(score / 100) % 10]);
    score_10->setImage(digits[(score / 10) % 10]);
    score_1->setImage(digits[(score / 1) % 10]);

    if(timer==0) 
    {
      std::cout<<"Game Over"<<std::endl;
      std::cout<<"Score : " << score <<std::endl;
      receiver.game_on=false;
      gui->addImage(texture_game_over,irr::core::position2d< s32 >(-300,-100));
      gui->addStaticText(L"SCORE = :"+score, ic::rect<s32>(40,100, 140,118));
      gui->drawAll();
      
    }
    timer_10000->setImage(digits[(timer / 10000) % 10]);
    timer_1000->setImage(digits[(timer / 1000) % 10]);
    timer_100->setImage(digits[(timer / 100) % 10]);
    timer_10->setImage(digits[(timer / 10) % 10]);
    timer_1->setImage(digits[(timer / 1) % 10]);

    receiver.gestion_deplacement(receiver.states, node);
    
  }




  driver->endScene();
}

device->drop();

return 0;
}
