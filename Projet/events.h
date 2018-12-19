// events.h

#ifndef EVENTS_H
#define EVENTS_H

#include <vector>

#include <irrlicht.h>
namespace is = irr::scene;
namespace ig = irr::gui;

class EventReceiver : public irr::IEventReceiver
{

  irr::gui::IGUIEnvironment *gui;
  irr::scene::IAnimatedMeshSceneNode *node;
  bool button_pressed;
  int  old_x, old_y;
  std::vector<irr::video::ITexture*> textures;
  int current_texture;
  

  

  bool keyboard_handler(const irr::SEvent &event);
  bool mouse_handler(const irr::SEvent &event);
  bool gui_handler(const irr::SEvent &event);
public:
  
  EventReceiver();
  bool game_on;
  enum difficulty {easy, normal, hard, end};
  bool diff[end];
  bool OnEvent(const irr::SEvent &event);
  void set_gui(irr::gui::IGUIEnvironment *gui);
  void set_node(irr::scene::IAnimatedMeshSceneNode *node);
  void set_textures(const std::vector<irr::video::ITexture *> &tex){textures=tex;}
  bool getMouvement();
  bool getDifficulty();
  enum type {running,forward,stand,backward,right,left,end_of_array};
  bool states[end_of_array];
  void gestion_deplacement(bool states[], is::IAnimatedMeshSceneNode *node);

};

#endif   
