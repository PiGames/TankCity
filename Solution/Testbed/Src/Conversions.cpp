/*
	Conrad 'Condzi' Kubacki 2017
	https://github.com/condzi
*/

#include <iostream>

#include "Conversions.hpp"
#include "Types.hpp"

using namespace con;

int main()
{
	int8 int8Val = 1;
	uint8 uint8Val = 2;
	int16 int16Val = 3;
	uint16 uint16Val = 4;
	int32 int32Val = 5;
	uint32 uint32Val = 6;
	int64 int64Val = 7;
	uint64 uint64Val = 8;
	float32 float32Val = 9.5f;
	float64 float64Val = 10.55;
	bool boolVal = true;

	std::string int8str = "1";
	std::string uint8str = "2";
	std::string int16str = "3";
	std::string uint16str = "4";
	std::string int32str = "5";
	std::string uint32str = "6";
	std::string int64str = "7";
	std::string uint64str = "8";
	std::string floatstr = "9.5";
	std::string doublestr = "10.55";
	std::string boolstr = "false";

	std::cout << "Val to string: \n";
	std::cout << To<std::string>( int8Val ) << '\n';
	std::cout << To<std::string>( uint8Val ) << '\n';
	std::cout << To<std::string>( int16Val ) << '\n';
	std::cout << To<std::string>( uint16Val ) << '\n';
	std::cout << To<std::string>( int32Val ) << '\n';
	std::cout << To<std::string>( uint32Val ) << '\n';
	std::cout << To<std::string>( int64Val ) << '\n';
	std::cout << To<std::string>( uint64Val ) << '\n';
	std::cout << To<std::string>( float32Val ) << '\n';
	std::cout << To<std::string>( float64Val ) << '\n';
	std::cout << To<std::string>( boolVal ) << '\n';

	std::cout << "---\n";
	std::cout << "Val from string: \n";
	std::cout << +To<int8>( int8str ) << '\n';
	std::cout << +To<uint8>( uint8str ) << '\n';
	std::cout << To<int16>( int16str ) << '\n';
	std::cout << To<uint16>( uint16str ) << '\n';
	std::cout << To<int32>( int32str ) << '\n';
	std::cout << To<uint32>( uint32str ) << '\n';
	std::cout << To<int64>( int64str ) << '\n';
	std::cout << To<uint64>( uint64str ) << '\n';
	std::cout << To<float32>( floatstr ) << '\n';
	std::cout << To<float64> ( doublestr ) << '\n';
	std::cout << std::boolalpha << con::To<bool>( boolstr ) << '\n';

	std::cout << "---\n";
	std::cout << "Multiple vals to string: \n";
	std::cout << con::To<std::string>( "int8   = ", int8Val, "!" ) << '\n';
	std::cout << con::To<std::string>( "uint8  = ", uint8Val, "!" ) << '\n';
	std::cout << con::To<std::string>( "int16  = ", int16Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "uint16 = ", uint16Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "int32  = ", int32Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "uint32 = ", uint32Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "int64  = ", int64Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "uint64 = ", uint64Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "float32  = ", float32Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "float64  = ", float64Val, "!"  ) << '\n';
	std::cout << con::To<std::string>( "bool	 = ", boolVal, "!"  ) << '\n';

	std::cin.get();
}