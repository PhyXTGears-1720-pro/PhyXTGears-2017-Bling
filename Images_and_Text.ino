void printText (String Phrase, int color[], int run_time, bool scroll, bool upperCase, int Skip, int pixOffset) {
  String phrase = Phrase;
  phrase.replace(" ", "  ");
  int h = matrix.height() - 1;
  h -= pixOffset;
  char p[phrase.length()];
  if (upperCase) {
    phrase.toUpperCase();
  }
  phrase.toCharArray(p, phrase.length());
  clearScreen();
  matrix.setTextColor(matrix.Color(color[0], color[1], color[2]));
  int x;
  if (scroll) {
    x = matrix.width();
    run_time += (phrase.length() * 11) + matrix.width();
  } else {
    x = 0;
  }
  for (int j = 0; j < run_time; j += Skip + 1) {
    clearScreen();
    matrix.setCursor(x, h);
    matrix.print(phrase);
    if ( scroll) {
      x -= Skip + 1;
    }
    delay(0);
    updateScreen();
  }
}

void rectangleZoom (int x, int y, int width, int height, int color, int Delay, bool noFill) {
  int iterations = min(width / 2, height / 2);
  //  int c = 0;
  for (int i = 0; i < iterations; i++) {
    matrix.drawRect(x, y, width, height, color);
    delay(Delay);
    updateScreen();
    if (noFill) {
      matrix.clear();
    }
    x += 1;
    y += 1;
    width -= 2;
    height -= 2;
    //    if (Length < c) {
    //      c += 1;
    //    }
  }
}

void creditsPrint (String message, uint16_t color, int Delay, bool twoText, String message2, uint16_t color2, bool threeText, String message3, uint16_t color3, bool allCaps, int endDelay) {
  matrix.setFont();
  if (allCaps) {
    message.toUpperCase();
    message2.toUpperCase();
    message3.toUpperCase();
  }
  int h = matrix.height();
  for (int i = 0; i >= -8; i--) {
    if (twoText) {
      matrix.setTextColor(color2);
      matrix.setCursor(0, i + 8);
      matrix.print(message2);
    }
    if (threeText) {
      matrix.setTextColor(color3);
      matrix.setCursor(0, i + 16);
      matrix.print(message3);
    }
    matrix.setTextColor(color);
    matrix.setCursor(0, i);
    matrix.print(message);
    updateScreen();
    matrix.clear();
    delay(Delay);
  }
  //  delay(endDelay);
  matrix.setFont(&FONT);
}


void credits (String messages[], uint16_t colors[], int LoopSize, int Delay, int scrollDelay, bool randColor) {
//  String messages[LoopSize] = Messages;
//  for (int i < LoopSize) {
//    if () {
//      //
//    }
//  }
  //  uint16_t colors[LoopSize];
  //  if (randCol) {
  //    for (int i = 0; i < LoopSize; i++) {
  //      colors[i] = matrix.Color(random(256), random(256), random(256));
  //    }
  //  } else {
  //    colors = Colors;
  //  }
  float Size = sizeof(messages);
  float SizeString = sizeof(messages[0]);
  Serial.println("Size: " + String(Size));
  //  int L = Size / SizeString;
  int L = LoopSize;
  Serial.println("L: " + String(L));
  if (randColor) {
    creditsPrint ("", BLACK, scrollDelay, true, "", BLACK, true, messages[0], randCol());
  } else {
    creditsPrint ("", BLACK, scrollDelay, true, "", BLACK, true, messages[0], colors[0]);
  }
  //  delay(Delay);
  Serial.println("A");
  if (randColor) {
    creditsPrint ("", BLACK, scrollDelay, true, messages[0], randCol(), true, messages[1], randCol());
  } else {
    creditsPrint ("", BLACK, scrollDelay, true, messages[0], colors[0], true, messages[1], colors[1]);
  }
  delay(Delay);
  //
  for (int i = 0; i < (L - 2); i++) {
    if (randColor) {
      creditsPrint (messages[i], randCol(), scrollDelay, true, messages[i + 1], randCol(), true, messages[i + 2], randCol());
    } else {
      creditsPrint (messages[i], colors[i], scrollDelay, true, messages[i + 1], colors[i + 1], true, messages[i + 2], colors[i + 2]);
    }
    Serial.println("I: " + String(i));
  }
  //
  if (randColor) {
    creditsPrint (messages[L - 2], randCol(), scrollDelay, true, messages[L - 1], randCol(), true, "", BLACK);
  } else {
    creditsPrint (messages[L - 2], colors[L - 2], scrollDelay, true, messages[L - 1], colors[L - 1], true, "", BLACK);
  }
  delay(Delay);
  Serial.println("B");
  if (randColor) {
    creditsPrint (messages[L - 1], randCol(), scrollDelay, true, "", BLACK, true, "", BLACK);
  } else {
    creditsPrint (messages[L - 1], colors[L - 1], scrollDelay, true, "", BLACK, true, "", BLACK);
  }
  delay(Delay);
}

const int randThreshold = 50;

uint16_t randCol () {
  return matrix.Color(random(randThreshold, 256), random(randThreshold, 256), random(randThreshold, 256));
}

