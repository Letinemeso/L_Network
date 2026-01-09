#include <Package.h>

using namespace LNet;


Package::Package()
{

}

Package::Package(const Package& _other)
{
    m_data = _other.m_data;
}

Package::Package(Package&& _from)
{
    m_data = (Data_Vector&&)_from.m_data;
}

Package::~Package()
{

}



void Package::append_data(const Data_Vector& _data)
{
    m_data.append(_data);
}

void Package::append_data(const char* _data, unsigned int _size)
{
    unsigned int old_data_size = m_data.size();

    m_data.resize(old_data_size + _size);
    char* new_raw_data_ptr = m_data.raw_data() + old_data_size;

    memcpy(new_raw_data_ptr, _data, _size);

    m_data.mark_full();
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
