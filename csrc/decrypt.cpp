#include <cryptopp/eccrypto.h>
#include <cryptopp/validate.h>

#include "de_quisquis_ec_impl_pp_CryptoppNative.h"
#include "curves.h"
#include "helpers.h"

extern "C" {

JNIEXPORT jbyteArray JNICALL Java_de_quisquis_ec_impl_pp_CryptoppNative_decrypt
  (JNIEnv *env, jclass nativeClass, jbyteArray ciphertext, jbyteArray modulus,
   jbyteArray a, jbyteArray b, jbyteArray gX, jbyteArray gY, jbyteArray n,
   jbyteArray x) {

    CryptoPP::ECIES<CryptoPP::ECP>::Decryptor decrypter;
    initPrivateKey(env, decrypter.AccessKey(), modulus, a, b, gX, gY, n, x);

    jbyte *cipherBytes = env->GetByteArrayElements(ciphertext, NULL);
    if (cipherBytes == NULL) {
        return NULL; // FIXME: check/throw exception
    }
    jsize cipherLen = env->GetArrayLength(ciphertext);
    size_t plainLen = decrypter.MaxPlaintextLength(cipherLen);
    byte plainBuf[plainLen];
    CryptoPP::DecodingResult result = decrypter.Decrypt(GlobalRNG(),cipherBytes,
                                                        cipherLen, plainBuf);
    jbyteArray plaintext;
    if (!result.isValidCoding) {
        plaintext = NULL;
        // FIXME: throw exception
    } else {
        jbyteArray plaintext = env->NewByteArray(cipherLen);
        if (plaintext == NULL) {
            return NULL; // FIXME: check/throw exception
        }
        jbyte *bytes = env->GetByteArrayElements(plaintext, NULL);
        if (bytes == NULL) {
            return NULL; // FIXME: check/throw exception
        }
        memcpy(bytes, plainBuf, result.messageLength);
        env->ReleaseByteArrayElements(plaintext, bytes, 0);
    }
    return plaintext;
}

} /* extern "C" */