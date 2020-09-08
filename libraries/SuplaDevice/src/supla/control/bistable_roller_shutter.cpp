/*
 Copyright (C) AC SOFTWARE SP. Z O.O.

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

#include "bistable_roller_shutter.h"

namespace Supla {
namespace Control {

BistableRollerShutter::BistableRollerShutter(int pinUp, int pinDown, bool highIsOn)
    : RollerShutter(pinUp, pinDown, highIsOn),
      activeBiRelay(false),
      toggleTime(0) {
}

void BistableRollerShutter::stopMovement() {
  if (currentDirection == UP) {
    relayUpOn();
  } else if (currentDirection == DOWN) {
    relayDownOn();
  }
  currentDirection = STOP;
  doNothingTime = millis();
}

void BistableRollerShutter::relayDownOn() {
  activeBiRelay = true;
  toggleTime = millis();
  digitalWrite(pinDown, highIsOn ? HIGH : LOW);
}

void BistableRollerShutter::relayUpOn() {
  activeBiRelay = true;
  toggleTime = millis();
  digitalWrite(pinUp, highIsOn ? HIGH : LOW);
}

void BistableRollerShutter::relayDownOff() {
  activeBiRelay = false;
  digitalWrite(pinDown, highIsOn ? LOW : HIGH);
}

void BistableRollerShutter::relayUpOff() {
  activeBiRelay = false;
  digitalWrite(pinUp, highIsOn ? LOW : HIGH);
}

void BistableRollerShutter::onTimer() {
  if (activeBiRelay && millis() - toggleTime > 200) {
    switchOffRelays();
    doNothingTime = millis();
  }
  if (activeBiRelay) {
    return;
  }

  RollerShutter::onTimer();
}

};  // namespace Control
};  // namespace Supla