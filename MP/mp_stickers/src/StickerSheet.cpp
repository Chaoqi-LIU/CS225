#include "StickerSheet.h"

using cs225::PNG;
using cs225::HSLAPixel;

StickerSheet::StickerSheet(const Image& picture, unsigned max)
    : max_(max), pos_vector(), image_vector() {
    pos_vector.push_back(std::make_pair(0,0));
    image_vector.push_back(new Image(picture));
}

StickerSheet::~StickerSheet() {
    for (auto& image : image_vector) { delete image; }
}

StickerSheet::StickerSheet(const StickerSheet& other)
    : max_(other.get_max()), pos_vector(other.get_pos_vector()), image_vector() {
    for (auto& image : other.get_image_vector()) {
        image_vector.push_back(new Image(*image));
    }
}

int StickerSheet::addSticker(Image& sticker, unsigned x, unsigned y) {
    if (image_vector.size()-1 == max_) {
        return -1;
    }
    pos_vector.push_back(std::make_pair(x,y));
    image_vector.push_back(new Image(sticker));
    return image_vector.size();
}

void StickerSheet::changeMaxStickers(unsigned max) {
    if (max < image_vector.size()-1) { 
        for (unsigned int i = 0; i < image_vector.size()-max; ++i) {
            delete image_vector.back();
            image_vector.pop_back();
            pos_vector.pop_back();
        }
    }
    max_ = max;
}

Image* StickerSheet::getSticker(unsigned index) {
    return index >= 0 && index < image_vector.size()-1
        ? image_vector.at(index + 1) 
        : nullptr;
}

const StickerSheet& StickerSheet::operator=(const StickerSheet& other) {
    pos_vector = other.get_pos_vector();
    max_ = other.get_max();
    for (auto& image : image_vector) {
        delete image;
    }
    image_vector.clear();
    for (auto& image : other.get_image_vector()) { 
        image_vector.push_back(new Image(*image)); 
    }
    return *this;
}

void StickerSheet::removeSticker(unsigned index) {
    if (index >= 0 && index < image_vector.size()-1) {
        delete image_vector.at(index + 1);
        image_vector.erase(image_vector.begin() + index + 1);
        pos_vector.erase(pos_vector.begin() + index + 1);
    }
}

Image StickerSheet::render() const {
    unsigned int finalW = image_vector.at(0)->width(), finalH = image_vector.at(0)->height();
    for (unsigned int i = 1; i < image_vector.size(); ++i) {
        unsigned int w = pos_vector.at(i).first + image_vector.at(i)->width(),
                     h = pos_vector.at(i).second + image_vector.at(i)->height();
        finalW = w > finalW ? w : finalW;
        finalH = h > finalH ? h : finalH;
    }
    Image image(*image_vector.at(0));
    image.resize(finalW, finalH);
    for (unsigned int i = 1; i < image_vector.size(); ++i) {
        for (unsigned int x = 0; x < image_vector.at(i)->width(); ++x) {
            for (unsigned int y = 0; y < image_vector.at(i)->height(); ++y) {
                HSLAPixel* image_pixel = &image.getPixel(x + pos_vector.at(i).first, 
                                                         y + pos_vector.at(i).second);
                HSLAPixel* sticker_pixel = &image_vector.at(i)->getPixel(x,y);
                if (sticker_pixel->a != 0) {
                    image_pixel->h = sticker_pixel->h;
                    image_pixel->l = sticker_pixel->l;
                    image_pixel->s = sticker_pixel->s;
                    image_pixel->a = sticker_pixel->a;
                }
            }
        }
    }
    return image;
}


bool StickerSheet::translate(unsigned index, unsigned x, unsigned y) {
    if (index >= 0 && index < image_vector.size()-1) {
        pos_vector.at(index + 1) = std::make_pair(x,y);
        return true;
    }
    return false;
}