#ifndef AES_HS_H
#define AES_HS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_MSC_VER) && (defined(_M_IX86) || defined(_M_AMD64) || defined(_M_X64))
# define SWAP(x) (_lrotl(x, 8) & 0x00ff00ff | _lrotr(x, 8) & 0xff00ff00)
# define GETU32(p) SWAP(*((u32*)(p)))
# define PUTU32(ct, st) { *((u32*)(ct)) = SWAP((st)); }
#else   /* NO lrotr, lrotl -> no SWAP() */
# define GETU32(pt)     (((u32)(pt)[0] << 24) ^ ((u32)(pt)[1] << 16) ^ ((u32)(pt)[2] << 8) ^ ((u32)(pt)[3]))
# define PUTU32(ct, st) { (ct)[0] = (u8)((st) >> 24); \
                          (ct)[1] = (u8)((st) >> 16); \
                          (ct)[2] = (u8)((st) >>  8); \
                          (ct)[3] = (u8)((st)      ); \
                        }
#endif /* END defined(_MSC_VER)...  */

typedef unsigned int   u32
typedef unsigned short u16
typedef unsigned char   u8

# define MAXKS (256/32) /*  aes-256 */
# define MAXKB (256/8)  /*  aes-256 */
# define MAXNR 14       /*  aes-256 */

#endif /* END AES_HS_H  */
