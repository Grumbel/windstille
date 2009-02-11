/*
**  Windstille - A Sci-Fi Action-Adventure Game
**  Copyright (C) 2005 Matthias Braun <matze@braunis.de>
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

#ifndef HEADER_WINDSTILLE_REF_HPP
#define HEADER_WINDSTILLE_REF_HPP

/** This class behaves like a pointer to a refcounted object, but increments the
 * reference count when new objects are assigned and decrements the refcounter
 * when it's lifetime has experied. (similar to std::auto_ptr)
 */
template<typename T>
class Ref
{
public:
  Ref(T* object = 0)
    : object(object)
  {
    if(object)
      object->ref();
  }
  Ref(const Ref<T>& other)
    : object(other.object)
  {
    if(object)
      object->ref();
  }
  ~Ref()
  {
    if(object)
      object->unref();
  }

  void operator= (const Ref<T>& other)
  {
    *this = other.get();
  }

  void operator= (T* object)
  {
    if(object)
      object->ref();
    if(this->object)
      this->object->unref();
    this->object = object;
  }

  T* operator ->() const
  {
    return object;
  }

  T& operator* () const
  {
    return *object;
  }

  operator const T* () const
  {
    return object;
  }

  T* get() const
  {
    return object;
  }

private:
  T* object;
};

#endif

/* EOF */
