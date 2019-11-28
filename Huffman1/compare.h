#ifndef COMPARE_H
#define COMPARE_H

#include "node.h"

class compare{
    public:
        bool operator()(const node *n1, const node *n2) const;
};


#endif // COMPARE_H