// events.cpp

#include <iostream>

#include <irrlicht.h>

#include "events.h"
#include "gui_ids.h"

using namespace irr;

namespace ic = irr::core;
namespace is = irr::scene;
namespace iv = irr::video;
namespace ig = irr::gui;

/**************************************************************************\
 * EventReceiver::EventReceiver                                           *
\**************************************************************************/
EventReceiver::EventReceiver()
: gui(nullptr), node(nullptr), button_pressed(false), current_texture(0), 
game_on(false)
{
}

/*------------------------------------------------------------------------*\
 * EventReceiver::keyboard_handler                                        *
\*------------------------------------------------------------------------*/
bool EventReceiver::keyboard_handler(const SEvent &event)
{
	if (event.KeyInput.PressedDown)
	{
		ic::vector3df position = node->getPosition();
		ic::vector3df rotation = node->getRotation();
		int speed=5;
		switch (event.KeyInput.Key)
		{
			case KEY_ESCAPE:
			exit(0);
      		case KEY_KEY_Z: // Avance
      		position.X += speed * cos(rotation.Y * M_PI / 180.0);
      		position.Z += -speed * sin(rotation.Y * M_PI / 180.0);
      		states[forward]=true;
      		states[stand]=false;
      		break;
     		case KEY_KEY_S: // Recule
     		position.X += -speed * cos(rotation.Y * M_PI / 180.0);
     		position.Z += speed * sin(rotation.Y * M_PI / 180.0);
     		break;
      		case KEY_KEY_D: // Tourne à droite
      		rotation.Y += 10;
      		break;
      		case KEY_KEY_Q: // Tourne à gauche
      		rotation.Y -= 10;
      		break;
      		default:;
      	}
      	node->setPosition(position);
      	node->setRotation(rotation);
      }
      else
      {
      	states[stand]=true;
      	states[forward]=false;
      }


      if(states[forward]==true)
      {
      	if(states[running]==false)
      	{
      		node->setMD2Animation(irr::scene::EMAT_RUN);
      		states[running]=true;
      		states[stand]=false;
      	}

      }
      else
      {
      	if(states[stand]==true)
      	{
      		node->setMD2Animation(irr::scene::EMAT_STAND);
      		states[stand]=true;
      		states[running]=false;
      	}

      }


      return false;
  }

/*------------------------------------------------------------------------*\
 * EventReceiver::mouse_handler                                           *
\*------------------------------------------------------------------------*/
  bool EventReceiver::mouse_handler(const SEvent &event)
  {
  	switch(event.MouseInput.Event)
  	{
  		case EMIE_LMOUSE_PRESSED_DOWN:
  		button_pressed = true;
  		old_x = event.MouseInput.X;
  		old_y = event.MouseInput.Y;
  		break;
  		case EMIE_LMOUSE_LEFT_UP:
  		button_pressed = false;
  		break;
  		case EMIE_MOUSE_MOVED:
  		if (button_pressed)
  		{
  			ic::vector3df rotation = node->getRotation();
  			rotation.Y += (event.MouseInput.X - old_x);        
  			old_x = event.MouseInput.X;
  			old_y = event.MouseInput.Y;
  			node->setRotation(rotation);
  		}
  		break;
  		default:
  		;
  	}

  	return false;
  }

/*------------------------------------------------------------------------*\
 * EventReceiver::gui_handler                                             *
\*------------------------------------------------------------------------*/
  bool EventReceiver::gui_handler(const SEvent &event)
  {
  	if (!node) return false;
  	switch(event.GUIEvent.EventType)
  	{
    // Gestion des menus de la barre de menu
  		case ig::EGET_MENU_ITEM_SELECTED:
  		{
  			ig::IGUIContextMenu *menu = (ig::IGUIContextMenu*)event.GUIEvent.Caller;
  			s32 item = menu->getSelectedItem();
  			s32 id = menu->getItemCommandId(item);
  			u32 debug_info = node->isDebugDataVisible();

  			switch(id)
  			{
  				case MENU_NEW_GAME:
  				game_on=true;
  				break;

  				case MENU_QUIT:
  				exit(0);

  				case MENU_BOUNDING_BOX:
  				menu->setItemChecked(item, !menu->isItemChecked(item));
  				node->setDebugDataVisible(debug_info ^ is::EDS_BBOX);
  				break;

  				case MENU_NORMALS:
  				menu->setItemChecked(item, !menu->isItemChecked(item));
  				node->setDebugDataVisible(debug_info ^ is::EDS_NORMALS);
  				break;

  				case MENU_TRIANGLES:
  				menu->setItemChecked(item, !menu->isItemChecked(item));
  				node->setDebugDataVisible(debug_info ^ is::EDS_MESH_WIRE_OVERLAY);
  				break;

  				case MENU_TRANSPARENCY:
  				menu->setItemChecked(item, !menu->isItemChecked(item));
  				node->setDebugDataVisible(debug_info ^ is::EDS_HALF_TRANSPARENCY);
  				break;

  				case MENU_ABOUT:
  				break;
  			}
  		}
  		break;
      // gestion des boutons
  		case ig::EGET_BUTTON_CLICKED:
  		{
  			s32 id = event.GUIEvent.Caller->getID();
  			if (id == MENU_NEW_GAME)
  			{
  				std::cout << "Button clicked\n";
  				game_on=true;

  			}
  		}
  		break;

  		default:;
  	}
  	return false;
  }

/**************************************************************************\
 * EventReceiver::OnEvent                                                 *
\**************************************************************************/
  bool EventReceiver::OnEvent(const SEvent &event)
  {
  	if (!node) return false;
  	switch (event.EventType)
  	{
  		case EET_KEY_INPUT_EVENT:
  		return keyboard_handler(event);
  		case EET_MOUSE_INPUT_EVENT:
  		return mouse_handler(event);
  		case EET_GUI_EVENT:
  		return gui_handler(event);
  		default:;
  	}

  	return false;
  }

/**************************************************************************\
 * EventReceiver::set_node                                                *
\**************************************************************************/
  void EventReceiver::set_node(irr::scene::IAnimatedMeshSceneNode *n)
  {
  	node = n;
  }

/**************************************************************************\
 * EventReceiver::set_gui                                                 *
\**************************************************************************/
  void EventReceiver::set_gui(irr::gui::IGUIEnvironment *g)
  {
  	gui = g;
  }

  bool EventReceiver::getMouvement()
  {
  	return &states;
  }

