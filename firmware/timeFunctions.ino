// отправить на индикаторы
void sendTime(byte hours, byte minutes) {
  if (form_time) {
    indiDigits[0] = (byte)hours / 10;
    indiDigits[1] = (byte)hours % 10;

    indiDigits[2] = (byte)minutes / 10;
    indiDigits[3] = (byte)minutes % 10;
  } else {
    if (hours>12) hours-=12;
    indiDigits[0] = (byte)hours / 10;
    indiDigits[1] = (byte)hours % 10;

    indiDigits[2] = (byte)minutes / 10;
    indiDigits[3] = (byte)minutes % 10;
  }
}

// для эффектов
void setNewTime() {
  if (form_time) {
    newTime[0] = (byte)hrs / 10;
    newTime[1] = (byte)hrs % 10;

    newTime[2] = (byte)mins / 10;
    newTime[3] = (byte)mins % 10;
  } else {
    if (hrs>12) hrs-=12;
    newTime[0] = (byte)hrs / 10;
    newTime[1] = (byte)hrs % 10;

    newTime[2] = (byte)mins / 10;
    newTime[3] = (byte)mins % 10;
  }
}
