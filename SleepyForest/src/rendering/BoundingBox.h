//
// Created by thefra985 on 15/02/23.
//

#ifndef SLEEPYFOREST_BINDINGBOX_H
#define SLEEPYFOREST_BINDINGBOX_H

#include <cstdint>
#include <ostream>

namespace Rendering {
    struct ValuePair {
    public:
        ValuePair(uint32_t v1, uint32_t v2) : _v1(v1), _v2(v2) {}

        [[nodiscard]] uint32_t getValue1() const { return _v1; }

        [[nodiscard]] uint32_t getValue2() const { return _v2; }

        bool operator==(const ValuePair &o) const {
            return _v1 == o._v1 && _v2 == o._v2;
        }

        bool operator<(const ValuePair &o) const {
            return _v1 < o._v1 || (_v1 == o._v1 && _v2 < o._v2);
        }

    protected:
        uint32_t _v1;
        uint32_t _v2;
    };

    struct Size : protected ValuePair {
    public:
        Size(uint32_t width, uint32_t height) : ValuePair(width, height) {}

        [[nodiscard]] uint32_t getWidth() const { return _v1; }

        [[nodiscard]] uint32_t getHeight() const { return _v2; }

        bool operator==(const Size &o) const {
            return _v1 == o._v1 && _v2 == o._v2;
        }

        friend std::ostream &operator<<(std::ostream &o, const Size &location) {
            return o << "{>" << location.getWidth() << " ^" << location.getHeight() << "}";
        }

        bool operator<(const Size &o) const {
            return _v1 < o._v1 || _v2 < o._v2;
        }

        bool operator>(const Size &o) const {
            return _v1 > o._v1 || _v2 > o._v2;
        }
    };

    struct Location : protected ValuePair {
    public:
        Location(uint32_t x, uint32_t y) : ValuePair(x, y) {}

        [[nodiscard]] uint32_t getX() const { return _v1; }

        [[nodiscard]] uint32_t getY() const { return _v2; }

        bool operator==(const Location &o) const {
            return _v1 == o._v1 && _v2 == o._v2;
        }

        friend std::ostream &operator<<(std::ostream &o, const Location &location) {
            return o << "<" << location.getX() << "," << location.getY() << ">";
        }

        bool operator<(const Location &o) const {
            return _v1 < o._v1 || (_v1 == o._v1 && _v2 < o._v2);
        }

        bool operator>(const Size &size) const {
            return _v1 > size.getWidth() || _v2 > size.getHeight();
        }

        Location operator+(const Size &size) const {
            return {_v1 + size.getWidth(), _v2 + size.getHeight()};
        }

        Location operator-(const Size &size) const {
            return {
                    _v1 >= size.getWidth() ? _v1 - size.getWidth() : 0,
                    _v2 >= size.getHeight() ? _v2 - size.getHeight() : 0
            };
        }

        friend Size operator-(const Size &size, const Location &location) {
            return {
                    size.getWidth() >= location.getX() ? size.getWidth() - location.getX() : 0,
                    size.getHeight() >= location.getY() ? size.getHeight() - location.getY() : 0
            };
        }
    };

    struct BoundingBox {
    public:
        BoundingBox(uint32_t x, uint32_t y) : _x(x), _y(y), _width(0), _height(0) {}

        explicit BoundingBox(const Location &location)
                : _x(location.getX()), _y(location.getY()), _width(0), _height(0) {}

        explicit BoundingBox(const Size &size) : _x(0), _y(0), _width(size.getWidth()), _height(size.getHeight()) {}

        BoundingBox(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
                : _x(x), _y(y), _width(width), _height(height) {}

        [[nodiscard]] uint32_t getX() const { return _x; }

        [[nodiscard]] uint32_t getY() const { return _y; }

        [[nodiscard]] uint32_t getWidth() const { return _width; }

        [[nodiscard]] uint32_t getHeight() const { return _height; }

        [[nodiscard]] Location getLocation() const { return Location(_x, _y); }

        [[nodiscard]] Size getSize() const { return Size(_width, _height); }

        /*bool operator<(const Location &location) const {
            return location.getX() < (_x + _width) && location.getY() < (_y + _height);
        }*/

        Size operator-(const Location &location) const {
            return {_x + _width - location.getX(), _y + _height - location.getY()};
        }

        friend bool operator>(const Location &location, const BoundingBox &boundingBox) {
            return location.getX() > (boundingBox._x + boundingBox._width)
                   || location.getY() > (boundingBox._y + boundingBox._height);
        }

    protected:
        uint32_t _x;
        uint32_t _y;
        uint32_t _width;
        uint32_t _height;
    };

    struct TargetBox : public BoundingBox {
        TargetBox(uint32_t x, uint32_t y)
                : _sourceX(x), _sourceY(y), _sourceWidth(0), _sourceHeight(0), BoundingBox(x, y) {}

        TargetBox(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
                : _sourceX(x), _sourceY(y), _sourceWidth(width), _sourceHeight(height),
                  BoundingBox(x, y, width, height) {}

        explicit TargetBox(const BoundingBox &source)
                : TargetBox(source.getX(), source.getY(), source.getWidth(), source.getHeight()) {}

        [[nodiscard]] uint32_t getGlobalWidth() const { return _sourceWidth; }

        [[nodiscard]] uint32_t getGlobalHeight() const { return _sourceHeight; }

        void updateOrigin(uint32_t x, uint32_t y) {
            _x = _sourceX + x;
            _y = _sourceY + y;
            _width = _sourceWidth - x;
            _height = _sourceHeight - y;
        }

        void setSize(const Size &smallerSize) {
//            if (smallerSize > Size(_width, _height))
//                return;
            if (_width > smallerSize.getWidth())
                _width = smallerSize.getWidth();
            if (_height > smallerSize.getHeight())
                _height = smallerSize.getHeight();
        }

        void restoreSize() {
            _width = _sourceWidth;
            _height = _sourceHeight;
        }
//        uint32_t setX(uint32_t x) { _x = x; }
//
//        uint32_t setY(uint32_t y) { _y = y; }
//
//        uint32_t setWidth(uint32_t width) { _width = width; }
//
//        uint32_t setHeight(uint32_t height) { _height = height; }
    protected:
        const uint32_t _sourceX;
        const uint32_t _sourceY;
        const uint32_t _sourceWidth;
        const uint32_t _sourceHeight;
    };
}

#endif //SLEEPYFOREST_BINDINGBOX_H
