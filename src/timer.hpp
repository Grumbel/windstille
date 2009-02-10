//
// 
//  SuperTux
//  Copyright (C) 2005 Matthias Braun <matze@braunis.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
//  02111-1307, USA.
#ifndef __SUPERTUX_TIMER_HPP__
#define __SUPERTUX_TIMER_HPP__

/**
 * This is the global game time in seconds. Should be the same as normal time,
 * except that it stops when the game pauses
 */
extern float game_time;

/**
 * new simpler timer designed to be used in the update functions of objects
 */
class Timer
{
public:
  Timer();
  ~Timer();

  /** start the timer with the given period (in seconds).
   * If cyclic=true then the timer willl be reset after each period.
   * Set period to zero if you want to disable the timer.
   */
  void start(float period, bool cyclic = false);
  /** returns true if a period (or more) passed since start call or last
   * successfull check
   */
  bool check();
  /** stop the timer */
  void stop()
  { start(0); }

  /** returns the period of the timer or 0 if it isn't started */
  float get_period() const
  { return period; }
  float get_timeleft() const
  { return period - (game_time - cycle_start); }
  float get_timegone() const
  { return game_time - cycle_start; }
  bool started() const
  { return period != 0 && get_timeleft() > 0; }

private:
  float period;
  float cycle_start;
  bool cyclic;
};

#endif

