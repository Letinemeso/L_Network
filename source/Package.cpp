#include <Package.h>

using namespace LNet;


void Package::append_data(const Data_Vector& _data)
{
    m_data.append(_data);
}

void Package::clear()
{
    m_data.clear();
}


const char* Package::raw_data() const
{
    return m_data.raw_data();
}

const char* Package::raw_data_with_offset(unsigned int _offset) const
{
    return m_data.raw_data() + _offset;
}

unsigned int Package::raw_data_size() const
{
    return m_data.size();
}
