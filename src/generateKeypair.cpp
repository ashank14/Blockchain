#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/err.h>
#include <iostream>

void generateRSAKeyPair(int bits) {
    // Create a new RSA key context
    EVP_PKEY *pkey = EVP_PKEY_new();
    if (!pkey) {
        std::cerr << "Error creating EVP_PKEY structure." << std::endl;
        return;
    }

    // Create a context for key generation
    EVP_PKEY_CTX *ctx = EVP_PKEY_CTX_new(pkey, nullptr);
    if (!ctx) {
 std::cerr << "OpenSSL Error: " << ERR_error_string(errno, nullptr) << std::endl;
        std::cerr << "Error creating context." << std::endl;
        EVP_PKEY_free(pkey);
        return;
    }

    // Initialize the key generation
    if (EVP_PKEY_keygen_init(ctx) <= 0) {
        std::cerr << "Error initializing RSA key generation." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return;
    }

    // Set the RSA key size
    if (EVP_PKEY_CTX_set_rsa_keygen_bits(ctx, bits) <= 0) {
        std::cerr << "Error setting RSA key size." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return;
    }

    // Generate the key
    if (EVP_PKEY_keygen(ctx, &pkey) <= 0) {
        std::cerr << "Error generating RSA key." << std::endl;
        EVP_PKEY_CTX_free(ctx);
        EVP_PKEY_free(pkey);
        return;
    }

    EVP_PKEY_CTX_free(ctx); // Free the context

    // Create BIO objects for private and public keys
    BIO *privateBIO = BIO_new(BIO_s_mem());
    BIO *publicBIO = BIO_new(BIO_s_mem());

    // Write private key
    if (PEM_write_bio_PrivateKey(privateBIO, pkey, nullptr, nullptr, 0, nullptr, nullptr) != 1) {
        std::cerr << "Error writing private key." << std::endl;
        ERR_print_errors_fp(stderr);
    }

    // Write public key
    if (PEM_write_bio_PUBKEY(publicBIO, pkey) != 1) {
        std::cerr << "Error writing public key." << std::endl;
        ERR_print_errors_fp(stderr);
    }

    // Print private key
    char *privateKeyData;
    long privateKeyLen = BIO_get_mem_data(privateBIO, &privateKeyData);
    std::cout << "Private Key:\n" << std::string(privateKeyData, privateKeyLen) << std::endl;

    // Print public key
    char *publicKeyData;
    long publicKeyLen = BIO_get_mem_data(publicBIO, &publicKeyData);
    std::cout << "Public Key:\n" << std::string(publicKeyData, publicKeyLen) << std::endl;

    // Clean up
    BIO_free_all(privateBIO);
    BIO_free_all(publicBIO);
    EVP_PKEY_free(pkey);
}