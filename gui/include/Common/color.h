#ifndef COLOR_H
#define COLOR_H

#define DEFAULT_GL_BACKGROUND_COLOR() Color{0.5, 0.55, 0.5, 0.0}
#define BLACK() Color{0.0, 0.0, 0.0, 1.0}

struct Color {
    double red;
    double green;
    double blue;
    double alpha;
    Color &operator=(const Color &c) = default;
    virtual ~Color() = default;
    Color(const Color &) = default;
    Color(Color &&) = default;
    Color &operator=(Color &&) = default;
    Color(double r = 0.0, double g = 0.0, double b = 0.0, double a = 1.0): red(r), green(g), blue(b), alpha(a) {}
    Color(int r, int g, int b, double a = 1.0): red(r/255.0), green(g/255.0), blue(b/255.0), alpha(a) {}
    //Color() = default;
};

#endif // COLOR_H
