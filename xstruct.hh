#ifndef XSTRUCT_H_
#define XSTRUCT_H_

#include "struct.hh"

template <class Tp, size_t NUM_LINKS, size_t LINK_OFFSET>
class XStruct : Struct<Tp, NUM_LINKS> {
    private:
    protected:
    public:
}

#include "xstruct_builder.hh"
#include "xstruct_director.hh"

#endif XSTRUCT_H_
