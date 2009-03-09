/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
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

#include "app/globals.hpp"
#include "math/random.hpp"
#include "math/matrix.hpp"
#include "display/vertex_array_drawing_request.hpp"
#include "display/display.hpp"
#include "display/texture_manager.hpp"
#include "nightvision.hpp"

Nightvision::Nightvision(FileReader& props)
  : nightvision("images/nightvision.sprite")
{
  name = "nightvision";
  noise = Texture("images/noise.png");
  noise.set_wrap(GL_REPEAT);
  noise.set_filter(GL_LINEAR);
}

Nightvision::~Nightvision()
{
}

void
Nightvision::draw(SceneContext& sc)
{
  // reset the modelview, so we can draw in screen coordinates
  sc.light().push_modelview();
  sc.light().set_modelview(Matrix::identity());

  // try to stay above everything else with large z value
  if (1)
    {
      nightvision.set_alpha(1.0f);
      nightvision.set_blend_func(GL_ONE, GL_ZERO);
      sc.light().draw(nightvision, Vector2f(0, 0), 10000);
    }

  if (1)
    {
      VertexArrayDrawingRequest* array = new VertexArrayDrawingRequest(Vector2f(0, 0), 10000,
                                                                       sc.light().get_modelview());
      array->set_mode(GL_QUADS);
      array->set_texture(noise);
      array->set_blend_func(GL_DST_COLOR, GL_ZERO);

      float u = rnd.drand()/0.5f;
      float v = rnd.drand()/0.5f;
      float w = 4.0f/6.0f;
      float h = 3.0f/6.0f;

      array->texcoord(u, v);
      array->vertex(0, 0);

      array->texcoord(u + w, v);
      array->vertex(Display::get_width(), 0);

      array->texcoord(u + w, v + h);
      array->vertex(Display::get_width(), Display::get_height());

      array->texcoord(u, v + h);
      array->vertex(0, Display::get_height());
      
      if (0) // second noise level
        {
          u = rnd.drand();
          v = rnd.drand();
          float size = 4.0f;

          array->texcoord(u, v);
          array->vertex(0, 0, 1.0f);

          array->texcoord(u + size, v);
          array->vertex(Display::get_width(), 0, 1.0f);

          array->texcoord(u + size, v + size);
          array->vertex(Display::get_width(), Display::get_height(), 1.0f);

          array->texcoord(u, v + size);
          array->vertex(0, Display::get_height(), 1.0f);
        }

      sc.light().draw(array);
    }
  sc.light().pop_modelview();

  if (1)
    {
      // FIXME: might be better to copy the highlight over to the
      // color layer, however that would require some changes to the
      // DrawingContext structure
      sc.highlight().clear();

      sc.highlight().push_modelview();
      sc.highlight().set_modelview(Matrix::identity());

      nightvision.set_alpha(0.5f);
      nightvision.set_blend_func(GL_SRC_ALPHA, GL_ONE);
      nightvision.set_scale(std::max(float(Display::get_width())  / nightvision.get_width(),
                                     float(Display::get_height()) / nightvision.get_height()));

      sc.highlight().draw(nightvision, 
                          Vector2f(Display::get_width() /2  - (nightvision.get_width()  * nightvision.get_scale()/2),
                                   Display::get_height()/2  - (nightvision.get_height() * nightvision.get_scale()/2)),
                          10000);
      sc.highlight().pop_modelview();
    }
}

void
Nightvision::update(float )
{
}

/* EOF */
