void spot (unsigned long Stop, int wide, int Delay, bool first) {
  float past = 0.3;
  unsigned long Start = millis();
  Stop += Start;
  //
  uint16_t color = matrix.Color(255, 255, 0);
  // speed vars
  int speedMaxRand = 1501;
  int speedAdd = 350;
  float speedD = 1000.0;
  int speedMinDiff = 600;
  //
  float sp = random(speedMaxRand);
  sp += speedAdd;
  float Speed = sp / speedD;
  Serial.println("Speed: " + String(Speed));
  float loc1 = random(matrix.width() - wide);
  loc1 += wide;
  float a1 = Speed;
  int width = wide;
  //
  float sp2 = random(speedMaxRand);
  if (abs(sp - sp2) < speedMinDiff) {
    while (abs(sp - sp2) < speedMinDiff) {
      Serial.println("Speed reselection");
      sp2 = random(speedMaxRand);
    }
  }
  sp2 += speedAdd;
  float Speed2 = sp2 / speedD;
  Serial.println("Speed: " + String(Speed2));
  float loc2 = random(matrix.width() - wide);
  loc2 += wide;
  float a2 = Speed;
  int width2 = wide;
  //
  int r = 0;
  //
  int rS = 0; // 3      7
  int cS = 0; // 3 even 6
  int tS = 0; // 4 even 7
  int c = 1;
  //
  int cAm = 255;
  int lBi = 255;
  bool Run = true;
  while (Start < Stop) {
    color = matrix.Color(lBi, lBi, 0);
    if (first) {
      int sPosX = (ceil(matrix.width() / 4) * 3) + 1;
      int sPosY = floor(matrix.height() / 2) - 1;
      int tPosX = floor(matrix.width() / 4) - 2;
      int tPosY = floor(matrix.height() / 2) - 0;
      int cPosX = round(matrix.width() / 2) - 0;
      int cPosY = floor(matrix.height() / 2) - 1;
      //
      c++;
      //
      if (rS < 3 && (c % 9) == 0 && cS > 2) {
        rS++;
      }
      if (cS < 3 && (c % 9) == 0 && tS > 3) {
        cS++;
      }
      if (tS < 4 && (c % 9) == 0) {
        tS++;
      }
      //
      if (tS != 0) {
        drawTriangleCenter(tPosX, tPosY, tS, matrix.Color(cAm, 0, 0));
      }
      if (cS != 0) {
        matrix.drawCircle(cPosX, cPosY, cS, matrix.Color(cAm, cAm, cAm));
      }
      if (rS != 0) {
        rectFromCenter(sPosX, sPosY, rS, matrix.Color(0, 0, cAm));
      }
      if ((Stop - Start) < 2500) {
        if ((c % 5) == 0) {
          rS++;
          cS++;
          tS++;
        }
        cAm -= 10;
        if (cAm <= 0) {
          first = false;
        }
      }
    }
    if (Run) {
      matrix.fillTriangle(5, (matrix.height() - 1), (round(loc1) - width), 0, round(loc1), 0, color);
      matrix.fillTriangle((matrix.width() - 6), (matrix.height() - 1), (round(loc2) - width), 0, round(loc2), 0, color);
      updateScreen();
    }
    matrix.clear();
    //
    loc1 += a1;
    //    Serial.print("1: ");
    //    Serial.println(loc1);
    if (loc1 > (matrix.width() * (past + 1))) {
      loc1 -= 2;
      a1 = Speed;
      a1 = a1 * -1;
    }
    if ((loc1 - width) < ((past * 40.0) * -1)) {
      loc1 += 2;
      a1 = Speed;
    }
    if (loc1 > 20) {
      width = wide + 1;
    }
    if (loc1 > 40) {
      width = wide + 2;
    }
    if (loc1 > 40) {
      width = wide + 1;
    }
    if (loc1 > 20) {
      width = wide;
    }
    //
    loc2 += a2;
    //    Serial.println(loc2);
    if (loc2 > (matrix.width() * (past + 1))) {
      loc2 -= 2;
      a2 = Speed2;
      a2 = a2 * -1;
    }
    if ((loc2 - width2) < ((past * 40.0) * -1)) {
      loc2 += 2;
      a2 = Speed2;
    }
    if (loc2 > 20) {
      width2 = wide + 1;
    }
    if (loc2 > 40) {
      width2 = wide + 2;
    }
    if (loc2 > 40) {
      width2 = wide + 1;
    }
    if (loc2 > 20) {
      width2 = wide;
    }
    //
    if ((Stop - Start) < 1000) {
      if (lBi <= 15) {
        Run = false;
      }
      lBi -= 13;
    }
    //
    delay(Delay);
    Start = millis();
  }
}

void rectFromCenter (int centerX, int centerY, int radius, uint16_t color) {
  int a = radius * 2;
  a++;
  matrix.drawRect((centerX - radius), (centerY - radius), a, a, color);
  //  Serial.println("X: " + String(centerX) + " Y: " + String(centerY) + " R: " + String(radius));
}

float getSpeedVal (float s, float mi, float ma) { // mi = 0.5;   ma = 2;      mi = 0.3;   ma = 3;
  // half of values <1 other half >1
  // put 1 in with <1
  int miI = round(mi * 100.0);    // 50       30
  int maI = round(ma * 100.0);    // 200      300
  float s1 = random(maI - miI);   // 0-150    0-270
  if (s <= miI) {
    s += 50;                      // 50-100   30-80
  } else if (s > miI) {
    s *= 2;
  }
}
