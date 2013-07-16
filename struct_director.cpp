#include "struct_builder.hh"

template <class Tp>
class StructDirector : public StructDirectorBase {
    private:
    protected:
    public:
        StructDirector(size_t phys_size, size_t logic_size);
        ~StructDirector();
};

