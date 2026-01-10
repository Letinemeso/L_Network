#pragma once

#include <Data_Structures/Vector.h>


namespace LNet
{

    class Package
    {
    public:
        using Data_Vector = LDS::Vector<char>;

    private:
        Data_Vector m_data;

    public:
        Package();
        Package(const Package& _other);
        Package(Package&& _from);
        ~Package();

    public:
        inline bool empty() const { return m_data.size() == 0; }

    public:
        void append_data(const Data_Vector& _data);
        void append_data(const char* _data, unsigned int _size);
        void clear();

        const char* raw_data() const;
        const char* raw_data_with_offset(unsigned int _offset) const;
        unsigned int raw_data_size() const;

        template<typename _Header>
        Data_Vector construct_header_data(const _Header& _header) const;
        template<typename _Header>
        void append_header(const _Header& _header);
        template<typename _Header>
        _Header parse_header() const;

        template<typename _Header_Type>
        const char* raw_data_without_header() const;
        template<typename _Header_Type>
        unsigned int raw_data_size_without_header() const;

    };



    template<typename _Header>
    Package::Data_Vector Package::construct_header_data(const _Header& _header) const
    {
        unsigned int header_size = sizeof(_header);
        char* header_as_char = (char*)&_header;

        Data_Vector data(header_size);
        for(unsigned int i = 0; i < header_size; ++i)
            data[i] = header_as_char[i];
        data.mark_full();

        return data;
    }

    template<typename _Header>
    void Package::append_header(const _Header& _header)
    {
        append_data( construct_header_data(_header) );
    }

    template<typename _Header>
    _Header Package::parse_header() const
    {
        _Header result;
        unsigned int header_size = sizeof(result);

        L_ASSERT(m_data.size() >= header_size);

        char* header_as_char = (char*)&result;
        for(unsigned int i = 0; i < header_size; ++i)
            header_as_char[i] = m_data[i];

        return result;
    }


    template<typename _Header_Type>
    const char* Package::raw_data_without_header() const
    {
        return raw_data_with_offset( sizeof(_Header_Type) );
    }

    template<typename _Header_Type>
    unsigned int Package::raw_data_size_without_header() const
    {
        constexpr unsigned int header_size = sizeof(_Header_Type);
        L_ASSERT(header_size < m_data.size());

        return raw_data_size() - header_size;
    }

}
