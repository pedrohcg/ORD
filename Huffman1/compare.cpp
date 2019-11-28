#include "compare.h"

bool compare::operator()(const node *n1, const node *n2) const{
    return n1->freq > n2->freq;
}
