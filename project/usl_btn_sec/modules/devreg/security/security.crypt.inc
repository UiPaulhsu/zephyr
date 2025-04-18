#define FS_STORE64H(__x, __y)                                                                  \
   { (__y)[0] = (unsigned char)(((__x)>>56)&255); (__y)[1] = (unsigned char)(((__x)>>48)&255);     \
     (__y)[2] = (unsigned char)(((__x)>>40)&255); (__y)[3] = (unsigned char)(((__x)>>32)&255);     \
     (__y)[4] = (unsigned char)(((__x)>>24)&255); (__y)[5] = (unsigned char)(((__x)>>16)&255);     \
     (__y)[6] = (unsigned char)(((__x)>>8)&255); (__y)[7] = (unsigned char)((__x)&255); }

#define FS_STORE32H(__x, __y)                                                                  \
     { (__y)[0] = (unsigned char)(((__x)>>24)&255); (__y)[1] = (unsigned char)(((__x)>>16)&255);   \
       (__y)[2] = (unsigned char)(((__x)>>8)&255); (__y)[3] = (unsigned char)((__x)&255); }

#define FS_LOAD32H(__x, __y)                         \
     { __x = ((unsigned long)((__y)[0] & 255)<<24) | \
           ((unsigned long)((__y)[1] & 255)<<16) | \
           ((unsigned long)((__y)[2] & 255)<<8)  | \
           ((unsigned long)((__y)[3] & 255)); }

#define FS_LOAD64H(__x, __y)                                                       \
     { __x = (((u_int64_t)((__y)[0] & 255))<<56)|(((u_int64_t)((__y)[1] & 255))<<48)| \
           (((u_int64_t)((__y)[2] & 255))<<40)|(((u_int64_t)((__y)[3] & 255))<<32)| \
           (((u_int64_t)((__y)[4] & 255))<<24)|(((u_int64_t)((__y)[5] & 255))<<16)| \
           (((u_int64_t)((__y)[6] & 255))<<8)| (((u_int64_t)((__y)[7] & 255))); }
