#include "Image.h"

#include <algorithm>

using cs225::HSLAPixel;
using cs225::PNG;

void Image::darken() { darken(0.1); }
void Image::darken(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            HSLAPixel* pixel = &getPixel(x,y);
            if (pixel->l >= amount) { pixel->l -= amount; } 
            else { pixel->l = 0.0; }
        }
    }
}

void Image::desaturate() { desaturate(0.1); }
void Image::desaturate(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            HSLAPixel* pixel = &getPixel(x,y);
            if (pixel->s >= amount) { pixel->s -= amount; } 
            else { pixel->s = 0.0; }
        }
    }
}

void Image::grayscale() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) { 
            getPixel(x,y).s = 0.0;
        }
    }
}

void Image::illinify() {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            HSLAPixel* pixel = &getPixel(x,y);
            pixel->h = std::abs(pixel->h - 11.0) >= std::abs(pixel->h - 216.0)
                ? 11.0
                : 216.0;
        }
    }
}

void Image::lighten() { lighten(0.1); }
void Image::lighten(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            HSLAPixel* pixel = &getPixel(x,y);
            if (pixel->l <= 1.0-amount) { pixel->l += amount; } 
            else { pixel->l = 1.0; }
        }
    }
}

void Image::rotateColor(double degrees) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            HSLAPixel* pixel = &getPixel(x,y);
            if (pixel->h + degrees > 360.0) {
                pixel->h += degrees - 360.0;
            } else if (pixel->h + degrees < 0.0) {
                pixel->h += degrees + 360.0;
            } else {
                pixel->h += degrees;
            }
        }
    }
}

void Image::saturate() { saturate(0.1); }
void Image::saturate(double amount) {
    for (unsigned int x = 0; x < width(); ++x) {
        for (unsigned int y = 0; y < height(); ++y) {
            HSLAPixel* pixel = &getPixel(x,y);
            if (pixel->s <= 1.0-amount) { pixel->s += amount; } 
            else { pixel->s = 1.0; }
        }
    }
}

void Image::scale(double factor) {
    unsigned int oldWidth = width(), oldHeight = height();
    unsigned int newWidth = oldWidth * factor, newHeight = oldHeight * factor;
    HSLAPixel* oldImageData_ = new HSLAPixel[oldWidth * oldHeight];
    for (unsigned int x = 0; x < oldWidth; ++x) {
        for (unsigned int y = 0; y < oldHeight; ++y) {
            unsigned int idx = y * oldWidth + x;
            HSLAPixel *pixel = &getPixel(x,y);
            oldImageData_[idx].h = pixel->h;
            oldImageData_[idx].s = pixel->s;
            oldImageData_[idx].l = pixel->l;
            oldImageData_[idx].a = pixel->a;
        }
    }
    resize(newWidth, newHeight);
    for (unsigned int x = 0; x < newWidth; ++x) {
        for (unsigned int y = 0; y < newHeight; ++y) {
            unsigned int oldIdx = static_cast<int>(y / factor) * oldWidth 
                                + static_cast<int>(x / factor);
            HSLAPixel* pixel = &getPixel(x,y);
            pixel->h = oldImageData_[oldIdx].h;
            pixel->s = oldImageData_[oldIdx].s;
            pixel->l = oldImageData_[oldIdx].l;
            pixel->a = oldImageData_[oldIdx].a;
        }
    }
    delete[] oldImageData_;
}

void Image::scale(unsigned w, unsigned h) {
    double factor = std::min( 
        static_cast<double>(w) / static_cast<double>(width()), 
        static_cast<double>(h) / static_cast<double>(height())
    );
    scale(factor);
}

// void Image::scale(double factor) {
//     unsigned int oldW = width(), oldH = height();
//     unsigned int newW = oldW*factor, newH = oldH*factor;
//     HSLAPixel* newImageData = new HSLAPixel[newW * newH];
//     for (unsigned int x = 0; x < newW; ++x) {
//         for (unsigned int y = 0; y < newH; ++y) {
//             HSLAPixel* oldPixel = &getPixel(x / factor, y / factor);
//             newImageData[y * newW + x].h = oldPixel->h;
//             newImageData[y * newW + x].l = oldPixel->l;
//             newImageData[y * newW + x].s = oldPixel->s;
//             newImageData[y * newW + x].a = oldPixel->a;
//         }
//     }
//     resize(newW, newH);
//     for (unsigned int x = 0; x < newW; ++x) {
//         for (unsigned int y = 0; y < newH; ++y) {
//             HSLAPixel* newPixel = &getPixel(x, y);
//             newPixel->h = newImageData[y * newW + x].h;
//             newPixel->l = newImageData[y * newW + x].l;
//             newPixel->s = newImageData[y * newW + x].s;
//             newPixel->a = newImageData[y * newW + x].a;
//         }
//     }
//     delete[] newImageData;
// }