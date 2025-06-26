/* ***********************************************************************************************************************************************************
Credentials file
*********************************************************************************************************************************************************** */

#pragma once

// Only one of these settings must be defined
//#define USE_ABP
#define USE_OTAA

#ifdef USE_ABP

// UPDATE WITH YOUR TTN KEYS AND ADDR.
//static const PROGMEM u1_t NWKSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//static const u1_t PROGMEM APPSKEY[16] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };
//static const u4_t DEVADDR = 0x26010000 ; // <-- Change this address for every node!

#endif

#ifdef USE_OTAA

    // This EUI must be in little-endian format, so least-significant-byte
    // first. When copying an EUI from ttnctl output, this means to reverse
    // the bytes. For TTN issued EUIs the last bytes should be 0x00, 0x00,
    // 0x00.
    //static const u1_t PROGMEM APPEUI[8]  = {0x07, 0x06, 0x05, 0x04, 0x03, 0x02, 0x01, 0x00};  // INTRODUCIR EN LSB cooper1
    static const u1_t PROGMEM APPEUI[8]  = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  // INTRODUCIR EN LSB cooper2
    // This should also be in little endian format, see above. (least-significant-byte
    // first)
    //static const u1_t PROGMEM DEVEUI[8]  = {0x17, 0xC3, 0x06, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};  // INTRODUCIR EN LSB cooper1
    static const u1_t PROGMEM DEVEUI[8]  = {0xE8, 0x11, 0x07, 0xD0, 0x7E, 0xD5, 0xB3, 0x70};  // INTRODUCIR EN LSB cooper2
    // This key should be in big endian format (or, since it is not really a
    // number but a block of memory, endianness does not really apply). In
    // practice, a key taken from ttnctl can be copied as-is.
    // The key shown here is the semtech default key.
    //static const u1_t PROGMEM APPKEY[16] = { 0xE6, 0x30, 0x0D, 0xFC, 0xBC, 0x26, 0x02, 0xC7, 0x2B, 0x2B, 0xDA, 0x84, 0x01, 0xBC, 0x1D, 0x05 };  // INTRODUCIR EN MSB cooper1
    static const u1_t PROGMEM APPKEY[16] = { 0x6D, 0x68, 0x85, 0xE1, 0xDB, 0xEE, 0x18, 0x46, 0xC4, 0x39, 0xEF, 0x64, 0x92, 0x24, 0x19, 0xD1 };  // INTRODUCIR EN MSB cooper2
#endif