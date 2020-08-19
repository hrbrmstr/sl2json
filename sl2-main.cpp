#include <iostream>
#include <fstream>
#include <bitset>

// REF: https://raw.githubusercontent.com/kmpm/node-sl2format/master/doc/sl2fileformat.md

// 1MB buffer
#define MAX_BUFFER_SIZE (1024 * 1000)

int main(int argc, const char *argv[]) {

  char buffer[MAX_BUFFER_SIZE];

  if (argc < 2) {
    ::std::cerr << "Usage: " << argv[0] << "<filename>\n";
    return(1);
  }

  ::std::ifstream in;
  in.rdbuf()->pubsetbuf(buffer, sizeof(buffer));
  in.open(argv[1], ::std::ifstream::in |::std::ios::binary);

  uint16_t format;
  in.seekg(0, ::std::ios_base::beg);
  in.read((char *)&format, sizeof(format));

  if (!((format >=1) && (format <= 3))) {
    ::std::cerr << "Unexpected format indicator in header; Likely not an SL2/SL3/SLG file" << ::std::endl;
    return(1);
  }

  uint16_t blockSize;
  in.seekg(4, ::std::ios_base::beg);
  in.read((char *)&blockSize, sizeof(blockSize));
  
  if (!((blockSize != 1970) || (blockSize != 3200))) {
    ::std::cerr << "Unexpected block size in header; Likely not an SL2/SL3/SLG file" << ::std::endl;
    return(1);
  }

  in.seekg(8, ::std::ios_base::beg); // start of records

  while (!(in.tellg() == -1)) {

    ::std::streampos recStart = in.tellg(); 

    uint16_t channel;
    in.seekg(recStart); in.seekg(32, ::std::ios_base::cur);
    in.read((char *)&channel, sizeof(channel));

    ::std::cout << "{\"channel\":" << channel << ",";

    uint16_t packetSize;
    in.seekg(recStart); in.seekg(34, ::std::ios_base::cur);
    in.read((char *)&packetSize, sizeof(packetSize));

    float upperLimit, lowerLimit;
    in.seekg(recStart); in.seekg(40, ::std::ios_base::cur);
    in.read((char *)&upperLimit, sizeof(upperLimit));
    in.read((char *)&lowerLimit, sizeof(lowerLimit));

    ::std::cout << "\"upperLimit\":" << upperLimit << ",";
    ::std::cout << "\"lowerLimit\":" << lowerLimit << ",";

    float waterDepth, keelDepth;
    in.seekg(recStart); in.seekg(64, ::std::ios_base::cur);
    in.read((char *)&waterDepth, sizeof(waterDepth));
    in.read((char *)&keelDepth, sizeof(keelDepth));

    ::std::cout << "\"waterDepth\":" << waterDepth << ",";
    ::std::cout << "\"keelDepth\":" << keelDepth << ",";

    float speedGps, temperature, speedWater, track, altitude, heading;
    uint32_t lngEnc, latEnc;
    ::std::bitset<16> flags;
    in.seekg(recStart); in.seekg(100, ::std::ios_base::cur);
    in.read((char *)&speedGps, sizeof(speedGps));
    in.read((char *)&temperature, sizeof(temperature));
    in.read((char *)&lngEnc, sizeof(lngEnc));
    in.read((char *)&latEnc, sizeof(latEnc));
    in.read((char *)&speedWater, sizeof(speedWater));
    in.read((char *)&track, sizeof(track));
    in.read((char *)&altitude, sizeof(altitude));
    in.read((char *)&heading, sizeof(heading));
    in.read((char *)&flags, sizeof(flags));

    ::std::cout << "\"speedGps\":" << speedGps << ",";
    ::std::cout << "\"temperature\":" << temperature << ",";
    ::std::cout << "\"longitude\":" << lngEnc << ",";
    ::std::cout << "\"latitude\":" << latEnc << ",";
    ::std::cout << "\"speedWater\":" << speedWater << ",";
    ::std::cout << "\"track\":" << track << ",";
    ::std::cout << "\"altitude\":" << altitude << ",";
    ::std::cout << "\"heading\":" << heading << ",";

    ::std::cout << "\"headingValid\":" << (flags.test(0) ? "true" : "false") << "," ;
    ::std::cout << "\"altitudeValid\":" << (flags.test(1) ? "true" : "false") << "," ;
    ::std::cout << "\"gpsSpeedValid\":" << (flags.test(9) ? "true" : "false") << "," ;
    ::std::cout << "\"waterTempValid\":" << (flags.test(10) ? "true" : "false") << "," ;
    ::std::cout << "\"positionValid\":" << (flags.test(12) ? "true" : "false") << "," ;
    ::std::cout << "\"waterSpeedValid\":" << (flags.test(14) ? "true" : "false") << "," ;
    ::std::cout << "\"trackValid\":" << (flags.test(15) ? "true" : "false") << "," ;

    uint32_t timeOffset;
    in.seekg(recStart); in.seekg(140, ::std::ios_base::cur);
    in.read((char *)&timeOffset, sizeof(timeOffset));

    ::std::cout << "\"timeOffset\":" << timeOffset << "}" << ::std::endl;

    in.seekg(recStart); in.seekg(144, ::std::ios_base::cur);
    in.seekg(packetSize, ::std::ios_base::cur); // move past the sounding/bounce data

  }

  in.close();

  return(0);

}
