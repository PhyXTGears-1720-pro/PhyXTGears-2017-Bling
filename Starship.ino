void explodingCircle (int x, int y, int r, uint16_t color, bool fill) {
  matrix.drawCircle(x, y, r, color);
  if (fill) {
    matrix.fillCircle(x, y, r, color);
  }
  updateScreen();
  delay(200);
  for (int i = 0; i < 0.5 * r; i++) {
    matrix.clear();
    for (int i = 0; i < 0.5 * r; i++) {
      matrix.drawPixel(random(x + i, x + i + 2), random(y + i, y + 1 + 2), color);
    }
    updateScreen();
    delay(30);
  }
}

void drawShipTL (int x, int y, float s, uint16_t color, bool Show) {
  // Left side
  matrix.drawLine(x, y, round(x + s), y, color);
  // long
  matrix.drawLine(x, y, x, round(y + (4 * s)), color);
  matrix.drawLine(x, round(y + (4 * s)), round(x + s), round(y + (4 * s)), color);

  // Middle
  int rX = x + (9 * s);
  int rY = round(y + round((4 * s) / 2.0));
  //  int mY = round(y / 2.0);
  matrix.drawLine(x, rY, rX, rY, color);
  matrix.fillCircle((round((rX - x) / 2.0) + x), rY, (s * 2), color);

  // Right side
  // long
  matrix.drawLine(rX, y, rX, round(y + (4 * s)), color);
  matrix.drawLine(rX, y, rX - s, y, color);
  matrix.drawLine(rX, round(y + (4 * s)), rX - s, round(y + (4 * s)), color);

  if (Show) {
    updateScreen();
  }
}

void drawShip (int x, int y, float s, uint16_t color, bool Show) {
  int X = x;
  int Y = y;
  X -= round(4.5 * s);
  Y -= round((round(y + (4 * s)) - y) / 2.0);
  drawShipTL (X, Y, s, color, Show);
}

