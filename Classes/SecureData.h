//
//  SecureData.h
//  Asteroids
//
//  Created by Wilson Meng on 12/29/14.
//
//

#ifndef __Asteroids__SecureData__
#define __Asteroids__SecureData__

class CSecureData
{
protected:
    static const unsigned int MAGIC_KEY = 0xB62CA5E4;
    static const int NUM_ITERATIONS = 2;
    
    unsigned int m_SecuredData;
    
public:
    CSecureData(unsigned int raw = 0) : m_SecuredData(Encrypt(raw)) {}
    
    const CSecureData& operator+=(unsigned int raw) {
        m_SecuredData = Encrypt(Decrypt(m_SecuredData) + raw);
        return *this;
    }

    const CSecureData operator+(unsigned int raw) {
        return CSecureData(*this) += raw;
    }
    
    unsigned int GetDecryptedData() { return Decrypt(m_SecuredData); }
    
    static unsigned int Encrypt(unsigned int);
    static unsigned int Decrypt(unsigned int);
    const CSecureData& operator=(const CSecureData& rSecureData) {
        m_SecuredData = rSecureData.m_SecuredData;
        return *this;
    }
};

#endif /* defined(__Asteroids__SecureData__) */
