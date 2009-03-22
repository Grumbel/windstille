/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2009 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**  
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**  
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "display/scene_context.hpp"
#include "windstille_widget.hpp"
#include "zoom_tool.hpp"

ZoomTool::ZoomTool()
  : rect_valid(false)
{
}

bool
ZoomTool::mouse_down (GdkEventButton* event, WindstilleWidget* wst)
{
  click_pos = wst->get_state().screen_to_world(Vector2f(event->x, event->y));
  rect_valid = false;
  return true;
}

bool
ZoomTool::mouse_move(GdkEventMotion* event, WindstilleWidget* wst)
{
  Vector2f pos = wst->get_state().screen_to_world(Vector2f(event->x, event->y));

  rect.left   = click_pos.x;
  rect.top    = click_pos.y;
  rect.right  = pos.x;
  rect.bottom = pos.y;
  
  rect_valid = true;
  return true;
}

bool
ZoomTool::mouse_up(GdkEventButton* event, WindstilleWidget* wst)
{
  // Zoom objects
  rect_valid = false;
  return true;
}

void
ZoomTool::draw(SceneContext& sc)
{
  std::cout << "draw: " << rect_valid << std::endl;
  if (rect_valid)
    {
      sc.control().fill_rect(rect, Color(1.0f, 1.0f, 0.0f, 0.25));
      sc.control().draw_rect(rect, Color(1.0f, 1.0f, 0.0f)); 
    }
}

/* EOF */
