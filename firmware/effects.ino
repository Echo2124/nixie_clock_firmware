void flipTick() {
  if (FLIP_EFFECT == 0) {
    sendTime(hrs, mins);
    newTimeFlag = false;
  }
  else if (FLIP_EFFECT == 1) {
    sendTime(hrs, mins);
    newTimeFlag = false;
  }
  else if (FLIP_EFFECT == 2) {
     sendTime(hrs, mins);
    newTimeFlag = false;
    //byte cathodeMask[] = {1, 0, 2, 9, 3, 8, 4, 7, 5, 6};  // порядок катодов in14
  }
  else if (FLIP_EFFECT == 3) {
    sendTime(hrs, mins);
    newTimeFlag = false;
  }
// --- train --- //
  else if (FLIP_EFFECT == 4) {
    sendTime(hrs, mins);
    newTimeFlag = false;
  }

// --- elastic band --- //
  else if (FLIP_EFFECT == 5) {
    sendTime(hrs, mins);
    newTimeFlag = false;
}
}
