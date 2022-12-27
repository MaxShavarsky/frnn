//
// Created by maxshavarsky on 25.12.2022.
//

#include "plotter.h"
#include <random>
#include <utility>

Plotter::Plotter(const Vector3d &leftBottom,
        const Vector3d &rightTop,
        double width,
        double height)
    : leftBottom_(leftBottom), rightTop_(rightTop), width_(width), height_(height) {
    imgRef_ = CreateRGBABitmapImageReference();
}

Plotter::~Plotter() {
    DeleteImage(imgRef_->image);
}

void Plotter::Plot() {
    auto reference = new StringReference();

    auto settings = GetDefaultScatterPlotSettings();
    settings->width = width_;
    settings->height = height_;
    settings->autoBoundaries = false;
    settings->xMin = leftBottom_.X();
    settings->xMax = rightTop_.X();
    settings->yMin = leftBottom_.Y();
    settings->yMax = rightTop_.Y();

    std::vector<ScatterPlotSeries*> series;
    for (auto &data : seriesToPlot_) {
        series.emplace_back(GetDefaultScatterPlotSeriesSettings());
        if (data.Color)
            series.back()->color = data.Color;
        else
            series.back()->color = NextColor();
        series.back()->xs = &data.X;
        series.back()->ys = &data.Y;

        settings->scatterPlotSeries->emplace_back(series.back());
    }

    DrawScatterPlotFromSettings(imgRef_, settings, reference);
}

void Plotter::AddSeries(Vec x, Vec y, RGBA *color) {
    SeriesData data;
    data.X = std::move(x);
    data.Y = std::move(y);
    data.Color = color;

    seriesToPlot_.emplace_back(data);
}

void Plotter::ConvertToPng(const std::string &pathToSave) {
    std::vector<double> *pngData = ConvertToPNG(imgRef_->image);
    WriteToFile(pngData, pathToSave);
}

RGBA *Plotter::NextColor() {
    std::vector<int> hueShuffle = {0,4,1,5,2,6,3};
    hue_ = hueShuffle[colorIdx_ % 8] * hueStep_;
    value_ = 255 - valueStep_ * ((colorIdx_ % 21) / 7);
    colorIdx_++;
    return HSVtoRGB((float)hue_,(float)saturation_/255.0f,(float)value_/255.0f);
}

//RGBA *Plotter::HSVtoRGB(float H, float S, float V) {
//    if(H > 360 || H < 0 || S > 255 || S < 0 || V > 255 || V < 0){
//        std::cout << "The given HSV values are not in valid range" << std::endl;
//        return nullptr;
//    }
//    float s = S/255;
//    float v = V/255;
//    float C = s*v;
//    float X = C*(1-abs(fmod(H/60.0, 2)-1));
//    float m = v-C;
//    float r,g,b;
//    if(H >= 0 && H < 60) {
//        r = C,g = X,b = 0;
//    }
//    else if(H >= 60 && H < 120) {
//        r = X,g = C,b = 0;
//    }
//    else if(H >= 120 && H < 180) {
//        r = 0,g = C,b = X;
//    }
//    else if(H >= 180 && H < 240) {
//        r = 0,g = X,b = C;
//    }
//    else if(H >= 240 && H < 300) {
//        r = X,g = 0,b = C;
//    }
//    else{
//        r = C,g = 0,b = X;
//    }
//    double R = (r+m);
//    double G = (g+m);
//    double B = (b+m);
//    std::cout << "R : " << R << std::endl;
//    std::cout << "G : " << G << std::endl;
//    std::cout << "B : " << B << std::endl;
//    return CreateRGBColor(R, G, B);
//}

RGBA *Plotter::HSVtoRGB(float H, float S, float V) {
    double r = 0, g = 0, b = 0;

    if (S == 0) {
        r = V;
        g = V;
        b = V;
    } else {
        int i;
        double f, p, q, t;

        if (H == 360)
            H = 0;
        else
            H = H / 60;

        i = (int) trunc(H);
        f = H - i;

        p = V * (1.0 - S);
        q = V * (1.0 - (S * f));
        t = V * (1.0 - (S * (1.0 - f)));

        switch (i) {
            case 0:
                r = V;
                g = t;
                b = p;
                break;

            case 1:
                r = q;
                g = V;
                b = p;
                break;

            case 2:
                r = p;
                g = V;
                b = t;
                break;

            case 3:
                r = p;
                g = q;
                b = V;
                break;

            case 4:
                r = t;
                g = p;
                b = V;
                break;

            default:
                r = V;
                g = p;
                b = q;
                break;
        }

    }

    return CreateRGBColor(r,g,b);
}