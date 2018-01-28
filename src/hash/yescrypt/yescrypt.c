/*-
 * Copyright 2014 Alexander Peslyak
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */
#include "yescrypt.h"
#include "sha256_c.h"
#include "yescrypt-best_c.h"

#define YESCRYPT_N 65536 //2^15=32768. 2^16=65536.  Yenten was 4096.  Bitzeny was 2048.  The higher the more GPU resistant.
#define YESCRYPT_R 8 //yenten changed this to 16 but as far as I can tell better to increase N than R.  N*R is memory allocation.
#define YESCRYPT_P 1 // 1 is best for GPU resistance.  Higher is more favorable to GPU's
#define YESCRYPT_T 2 // 2 is 89% efficiency and will give 45% increase in ASIC resistance.  1 is 96% efficient +25% resistance.  Bitzeny and Yenten had set to 0 (which is 100% efficient, 0% boost in resistance)
#define YESCRYPT_FLAGS (YESCRYPT_RW | YESCRYPT_PWXFORM)

#ifdef __clang__

static int yescrypt_yenten(const uint8_t *passwd, size_t passwdlen,
                            const uint8_t *salt, size_t saltlen,
                            uint8_t *buf, size_t buflen)
{
    yescrypt_shared_t shared;
    yescrypt_local_t local;
    int retval;
    
    if (yescrypt_init_shared(&shared, NULL, 0,
                             0, 0, 0, YESCRYPT_SHARED_DEFAULTS, 0, NULL, 0))
        return -1;
    if (yescrypt_init_local(&local)) {
        yescrypt_free_shared(&shared);
        return -1;
    }
    retval = yescrypt_kdf(&shared, &local, passwd, passwdlen, salt, saltlen,
                          YESCRYPT_N, YESCRYPT_R, YESCRYPT_P, YESCRYPT_T,
                          YESCRYPT_FLAGS, buf, buflen);
    if (yescrypt_free_local(&local)) {
        yescrypt_free_shared(&shared);
        return -1;
    }
    if (yescrypt_free_shared(&shared))
        return -1;
    
    return retval;
}

#else

static int yescrypt_yenten(const uint8_t *passwd, size_t passwdlen,
                            const uint8_t *salt, size_t saltlen,
                            uint8_t *buf, size_t buflen)
{
    static __thread int initialized = 0;
    static __thread yescrypt_shared_t shared;
    static __thread yescrypt_local_t local;
    int retval;
    if (!initialized) {
        /* "shared" could in fact be shared, but it's simpler to keep it private
         * along with "local".  It's dummy and tiny anyway. */
        if (yescrypt_init_shared(&shared, NULL, 0,
                                 0, 0, 0, YESCRYPT_SHARED_DEFAULTS, 0, NULL, 0))
            return -1;
        if (yescrypt_init_local(&local)) {
            yescrypt_free_shared(&shared);
            return -1;
        }
        initialized = 1;
    }
    retval = yescrypt_kdf(&shared, &local, passwd, passwdlen, salt, saltlen,
                          YESCRYPT_N, YESCRYPT_R, YESCRYPT_P, YESCRYPT_T,
                          YESCRYPT_FLAGS, buf, buflen);
#if 0
    if (yescrypt_free_local(&local)) {
        yescrypt_free_shared(&shared);
        return -1;
    }
    if (yescrypt_free_shared(&shared))
        return -1;
    initialized = 0;
#endif
    if (retval < 0) {
        yescrypt_free_local(&local);
        yescrypt_free_shared(&shared);
    }
    return retval;
}

#endif

void yescrypt_hash(const char *input, char *output)
{
    yescrypt_yenten((const uint8_t *) input, 80,
                     (const uint8_t *) input, 80,
                     (uint8_t *) output, 32);
}
