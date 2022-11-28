#pragma once

template<typename T> struct NewType
{
    typedef unsigned char Raw;
    NewType<unsigned char>::Raw value;

	void NewType();
    void NewType(const NewType<unsigned char>::Raw &);
	void NewType(const NewType<unsigned char> &);
   
    const NewType<unsigned char>::Raw &operator const unsigned char &() const;
	
	NewType<unsigned char> &operator=(const NewType<unsigned char> &);
    bool operator==(const NewType<unsigned char> &) const;
    bool operator<(const NewType<unsigned char> &) const;
};