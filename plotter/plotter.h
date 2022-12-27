//
// Created by maxshavarsky on 25.12.2022.
//

#ifndef ALGORITHMS_PLOTTER_H
#define ALGORITHMS_PLOTTER_H

#include "pbPlots.h"
#include "supportLib.h"
#include "../utils/vector3d.h"

class Plotter {
    typedef std::vector<double> Vec;

    struct SeriesData {
        Vec X;
        Vec Y;
        RGBA *Color;
    };
public:
    Plotter(const Vector3d &leftBottom,
            const Vector3d &rightTop,
            double width = 1080.0,
            double height = 920.0);
    ~Plotter();
public:
    void Plot();
    void AddSeries(Vec x, Vec y, RGBA *color = nullptr);
    void ConvertToPng(const std::string &pathToSave);

private:
    [[nodiscard]] RGBA *NextColor();

    [[nodiscard]] RGBA *HSVtoRGB(float H, float S,float V);

private:
    const Vector3d leftBottom_, rightTop_;
    double width_, height_;
    RGBABitmapImageReference *imgRef_{};
    std::vector<SeriesData> seriesToPlot_;

    int saturation_ = 255;
    int hue_ = 0;
    int value_ = 255;


    int valueStep_ = 80;
    int hueStep_ = 255 / 7;
    int colorIdx_ = 0;
};


#endif //ALGORITHMS_PLOTTER_H
