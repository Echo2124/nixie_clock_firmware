void settingsTick() {
  if (curMode == 1) {
    if (blinkTimer.isReady()) {
      sendTime(changeHrs, changeMins);
      lampState = !lampState;
      if (lampState) {
        anodeStates[0] = 1;
        anodeStates[1] = 1;
        anodeStates[2] = 1;
        anodeStates[3] = 1;
      } else {
        if (!currentDigit) {
          anodeStates[0] = 0;
          anodeStates[1] = 0;
        } else {
          anodeStates[2] = 0;
          anodeStates[3] = 0;
        }
      }
    }
  }
}

void buttonsTick() {
  btnSet.tick();
  btnL.tick();
  btnR.tick();

  if (curMode == 1) {
    if (btnR.isClick()) {
      if (!currentDigit) {
        changeHrs++;
        if (changeHrs > 23) changeHrs = 0;
      } else {
        changeMins++;
        if (changeMins > 59) {
          changeMins = 0;
          changeHrs++;
          if (changeHrs > 23) changeHrs = 0;
        }
      }
      sendTime(changeHrs, changeMins);
    }
    if (btnL.isClick()) {
      if (!currentDigit) {
        changeHrs--;
        if (changeHrs < 0) changeHrs = 23;
      } else {
        changeMins--;
        if (changeMins < 0) {
          changeMins = 59;
          changeHrs--;
          if (changeHrs < 0) changeHrs = 23;
        }
      }
      sendTime(changeHrs, changeMins);
    }
  } else if (curMode == 0) {
    // переключение эффектов цифр
    if (btnR.isClick()) {
      if (++FLIP_EFFECT >= FLIP_EFFECT_NUM) FLIP_EFFECT = 0;
      EEPROM.put(0, FLIP_EFFECT);
      flipTimer.setInterval(FLIP_SPEED[FLIP_EFFECT]);
      for (byte i = 0; i < 4; i++) {
        indiDimm[i] = indiMaxBright;
        anodeStates[i] = 1;
      }
      // показать эффект
      newTimeFlag = true;
      for (byte i = 0; i < 4; i++) indiDigits[i] = FLIP_EFFECT;
    }

    // переключение эффектов подсветки
    if (btnL.isClick()) {
      if (++BACKL_MODE >= 3) BACKL_MODE = 0;
      EEPROM.put(1, BACKL_MODE);
      if (BACKL_MODE == 1) {
        setPWM(BACKL, backlMaxBright);
      } else if (BACKL_MODE == 2) {
        digitalWrite(BACKL, 0);
      }
    }

    // переключение глюков
    if (btnL.isHolded()) {
      GLITCH_ALLOWED = !GLITCH_ALLOWED;
      EEPROM.put(2, GLITCH_ALLOWED);
    }
  }

  if (btnSet.isHolded()) {
    anodeStates[0] = 1;
    anodeStates[1] = 1;
    anodeStates[2] = 1;
    anodeStates[3] = 1;
    currentDigit = false;
    if (++curMode >= 2) curMode = 0;
    switch (curMode) {
      case 0:
        hrs = changeHrs;
        mins = changeMins;
        secs = 0;
        rtc.adjust(DateTime(2019, 12, 05, hrs, mins, 0));
        changeBright();
        break;
      case 1:
        changeHrs = hrs;
        changeMins = mins;
        break;
    }
  }
  if (btnSet.isClick()) {
    if (curMode == 1) currentDigit = !currentDigit; // настройка времени
  }
  if (btnR.isHolded()) {
    form_time = !form_time;
    DateTime now = rtc.now();   
    hrs = now.hour();
    mins = now.minute();
    if (form_time) {
      digitalWrite(13, HIGH);
    } else {
      digitalWrite(13, LOW);
    }
    sendTime(hrs, mins);
    delay(500);
    //EEPROM.put(20, form_time);
  }
}
