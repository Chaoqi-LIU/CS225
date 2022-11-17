/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */

#pragma once

#include <vector>
#include "Image.h"
class StickerSheet {
    public:
        StickerSheet(const Image& picture, unsigned max);  // deep copy
        ~StickerSheet();  // destructor
        StickerSheet(const StickerSheet& other);  // copy constructor
        const StickerSheet& operator=(const StickerSheet& other);  // assignment op
        void changeMaxStickers(unsigned max);
        int addSticker(Image& sticker, unsigned x, unsigned y);
        bool translate(unsigned index, unsigned x, unsigned y);
        void removeSticker(unsigned index);
        Image* getSticker(unsigned index);
        Image render() const;
        unsigned int get_max() const { return max_; }
        std::vector<Image*> get_image_vector() const { return image_vector; }
        std::vector<std::pair<unsigned int, unsigned int>> get_pos_vector() const { return pos_vector; }

    private:
        unsigned int max_;
        std::vector<std::pair<unsigned int, unsigned int>> pos_vector;
        std::vector<Image*> image_vector;
};