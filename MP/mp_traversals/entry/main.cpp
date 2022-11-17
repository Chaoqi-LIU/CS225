
#include "cs225/PNG.h"
#include "FloodFilledImage.h"
#include "Animation.h"

#include "imageTraversal/DFS.h"
#include "imageTraversal/BFS.h"

#include "colorPicker/RainbowColorPicker.h"
#include "colorPicker/GradientColorPicker.h"
#include "colorPicker/GridColorPicker.h"
#include "colorPicker/SolidColorPicker.h"
#include "colorPicker/MyColorPicker.h"

using namespace cs225;

int main() {

  // @todo [Part 3]
  // - The code below assumes you have an Animation called `animation`
  // - The code provided below produces the `myFloodFill.png` file you must
  //   submit Part 3 of this assignment -- uncomment it when you're ready.
  
  MyColorPicker mcp;

  PNG image; image.readFromFile("../entry/image.png");

  FloodFilledImage ffi(image);
  DFS dfs1(image, Point{200,150} , 0.3);
  DFS dfs2(image, Point{200,310} , 0.3);
  BFS bfs1(image, Point{150, 70}, 0.3);
  ffi.addFloodFill(dfs1, mcp);
  ffi.addFloodFill(dfs2, mcp);
  ffi.addFloodFill(bfs1, mcp);
  Animation animation = ffi.animate(1500);
  PNG lastFrame = animation.getFrame( animation.frameCount() - 1 );
  lastFrame.writeToFile("myFloodFill.png");
  animation.write("myFloodFill.gif");

  return 0;
}
