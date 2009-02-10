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

#ifndef HEADER_SEGMENT_HPP
#define HEADER_SEGMENT_HPP

#include "math/line.hpp"
#include "math/vector.hpp"
#include "properties.hpp"

class Node;

/** */
class Segment
{
private:
  Node* node1;
  Node* node2;
  
  Properties properties;

public:
  Segment(Node* node1_, Node* node2_, Properties props_ = 0);
  ~Segment();

  /** Calculate the angle between two segments */
  float angle(Segment* seg);
  
  Node* get_node1() const { return node1; } 
  Node* get_node2() const { return node2; } 

  Properties get_properties()  const { return properties; }

  Line   get_line() const;
  Vector get_vector() const;
  
private:
  Segment (const Segment&);
  Segment& operator= (const Segment&);
};

#endif

/* EOF */
