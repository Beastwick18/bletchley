#ifndef __CRYPTO__H_
#define __CRYPTO__H_

char *_encrypt( const char *data, const char *key, const char *iv, int *length ) ;
char *_decrypt( const char *data, int data_length, const char *key, const char *iv, int *length ) ;
int encryptFile( char * input_filename, char * output_filename  ) ;
int decryptFile( char * input_filename, char * output_filename  ) ;

#endif
