#ifndef COMMON_MD5_H
#define COMMON_MD5_H

#include <string>
#include <stdint.h>

namespace MD5 {

struct MD5Context {
	uint32_t buf[4];
	uint32_t bits[2];
	uint8_t  in[64];
};

typedef struct MD5Context md5_t;

void MD5Init(struct MD5Context *);
void MD5Update(struct MD5Context *, unsigned char const *, unsigned);
void MD5Final(unsigned char digest[16], struct MD5Context *ctx);
void MD5Digest( const unsigned char *msg, int len, unsigned char *digest);
void MD5HMAC(const unsigned char *password,  unsigned pass_len,
		const unsigned char *challenge, unsigned chal_len,
		unsigned char response[16]);
void MD5HMAC2(const unsigned char *password,  unsigned pass_len,
		const unsigned char *challenge, unsigned chal_len,
		const unsigned char *challenge2, unsigned chal_len2,
		unsigned char response[16]);


// 获取md5的值，外部接口使用
extern void GETMD5(const char* data, unsigned len, unsigned char md5[16]);


} // namespace MD5

#endif // COMMON_MD5_H

