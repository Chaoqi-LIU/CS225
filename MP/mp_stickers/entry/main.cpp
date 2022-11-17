#include "Image.h"
#include "StickerSheet.h"

int main() {
  Image image, s;
  image.readFromFile("../alma.png");
  s.readFromFile("../i.png");
  StickerSheet ss(image, 5);
  ss.addSticker(s, 0, 0);
  ss.addSticker(s, 100, 0);
  ss.addSticker(s, 500, 500);
  ss.render().writeToFile("../myImage.png");  // make the sticker-sheet and write to file
  return 0;
}
