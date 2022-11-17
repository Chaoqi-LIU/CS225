/**
 * @file maptiles.cpp
 * Code for the maptiles function.
 */

#include <iostream>
#include <map>

#include "maptiles.h"

using namespace std;


Point<3> convertToXYZ(LUVAPixel pixel) {
    return Point<3>( pixel.l, pixel.u, pixel.v );
}

MosaicCanvas* mapTiles(SourceImage const& theSource,
                       vector<TileImage>& theTiles)
{
    /**
     * @todo Implement this function!
     */
    
    // pre-processing 
    vector<Point<3>> pixel_points;
    map<Point<3>, TileImage*> LUVAPixel_to_TileImage_map;
    for (auto & tile : theTiles) {
        Point<3> pixel_pt =  convertToXYZ(tile.getAverageColor());
        LUVAPixel_to_TileImage_map.insert({pixel_pt, new TileImage(tile)});
        pixel_points.push_back(pixel_pt);
    }
    
    // build kd_tree
    KDTree<3> kd_tree(pixel_points);

    int num_rows = theSource.getRows(), num_cols = theSource.getColumns();

    MosaicCanvas * mosaic_canvas = new MosaicCanvas(num_rows, num_cols);

    for (int row = 0; row < num_rows; ++row) {
        for (int col = 0; col < num_cols; ++col) {
            Point<3> pt = kd_tree.findNearestNeighbor(
                convertToXYZ(theSource.getRegionColor(row, col))
            );
            TileImage * tile_image_in_map = LUVAPixel_to_TileImage_map[pt];
            mosaic_canvas->setTile(row, col, tile_image_in_map);
        }
    }

    return mosaic_canvas;
}

