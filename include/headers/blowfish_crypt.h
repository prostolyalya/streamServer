#ifndef BLOWFISH_CRYPT_H
#define BLOWFISH_CRYPT_H

#include <cstdint>
#include <cstring>
#include <QByteArray>

namespace  BlowFish
{
    QByteArray encrypt(const QByteArray &message, const QByteArray &key);
    QByteArray decrypt(const QByteArray &message, const QByteArray &key);

    void SetKey(const char *key, size_t byte_length, uint32_t (&pary)[18], uint32_t (&sbox)[4][256]);
    void EncryptBlock(uint32_t *left, uint32_t *right, uint32_t (&pary)[18], uint32_t (&sbox)[4][256]);
    void DecryptBlock(uint32_t *left, uint32_t *right, uint32_t (&pary)[18], uint32_t (&sbox)[4][256]);
    QByteArray Encrypt(const QByteArray &src, const QByteArray &key, uint32_t (&pary)[18],
                              uint32_t (&sbox)[4][256]);
    QByteArray Decrypt(const QByteArray &src, const QByteArray &key, uint32_t (&pary)[18],
                              uint32_t (&sbox)[4][256]);
    uint32_t Feistel(uint32_t value, uint32_t (&sbox)[4][256]);
};

#endif // BLOWFISH_CRYPT_H
