#ifndef XDATA_H_
#define XDATA_H_

template <class Tp>
struct XData {
    size_t num_links_
    XData<Tp>** links_;
    Tp* value_;
    XData() : num_links_(0), links_(NULL), value_(NULL) {}
    XData(size_t num_links, XData<Tp>** links, Tp* value) : num_links_(num_links), links_(links), value_(value) {}
};

#endif // XDATA_H_
