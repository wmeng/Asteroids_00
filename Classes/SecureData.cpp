//
//  SecureData.cpp
//  Asteroids
//
//  Created by Wilson Meng on 12/29/14.
//
//

#include "SecureData.h"

unsigned int CSecureData::Encrypt(unsigned int ui)
{
    unsigned int tmpValue, lowerShort, upperShort, retValue;
    
    retValue = ui;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        tmpValue = retValue ^ MAGIC_KEY;
        lowerShort = tmpValue & 0x0000FFFF;
        upperShort = (tmpValue & 0xFFFF0000) >> 16;
        retValue = (lowerShort << 16) + upperShort;
    }
    
    return retValue;
}

unsigned int CSecureData::Decrypt(unsigned int ui)
{
    unsigned int tmpValue, lowerShort, upperShort, retValue;
    
    retValue = ui;
    for (int i = 0; i < NUM_ITERATIONS; i++) {
        lowerShort = retValue & 0x0000FFFF;
        upperShort = (retValue & 0xFFFF0000) >> 16;
        tmpValue = (lowerShort << 16) + upperShort;
        retValue = tmpValue ^ MAGIC_KEY;
    }
    
    return retValue;
}
