#ifndef IBOUNDABLE_H
#define IBOUNDABLE_H
#include <QRectF>


class IBoundable {
public:
    virtual ~IBoundable() = default;
    virtual void setBounds(const QRectF& bounds) = 0;
};



#endif //IBOUNDABLE_H
