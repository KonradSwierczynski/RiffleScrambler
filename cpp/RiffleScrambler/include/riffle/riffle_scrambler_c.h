//
// Created by konrad on 07.01.19.
//

#ifndef CPP_RIFFLE_SCRAMBLER_C_H
#define CPP_RIFFLE_SCRAMBLER_C_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define RIFFLE_MIN_OUTLEN UINT32_C(4)
#define RIFFLE_MAX_OUTLEN UINT32_C(0xFFFFFFFF)


typedef enum RiffleScrambler_ErrorCode {
    RIFFLE_SCRAMBLER_OK = 0,
    RIFFLE_OUTPUT_PTR_NULL = -1,
    RIFFLE_OUTPUT_TOO_SHORT = -2,
    RIFFLE_OUTPUT_TOO_LONG = -3,
    RIFFLE_ERROR = -4
} error_codes;


/**
* Hashowanie hasła za pomocą RiffleScrambler, wynik zwracany jest do zmiennej @hash
* @param pwd Wskaźnik na hasło
* @param pwdlen_bytes Rozmiar hasła w bajtach
* @param salt Wskaźnika na sól
* @param saltlen_bytes Rozmiar soli w bajtach
* @param t_cost Parametr "lambda" oznaczający ilość iteracji
* @param m_cost Parametr "g" oznaczający rozmiar używanej pamięci
* @param hash Bufor do którego będzie zapisany hash hasła
* @param hashlen Rozmiar bufora, oznacza ile bajtów z hasha hasła ma zostać zapisane
* @return RIFFLE_SCRAMBLER_OK jeśli obliczenia zakończyły się pomyślnie,
* kod błędu w przeciwnym przypadku
*/
int riffle_scrambler(void *hash, const size_t hashlen, const void *pwd,
        const size_t pwdlen_bytes, const void *salt, const size_t saltlen_bytes,
        const uint64_t t_cost, const uint64_t m_cost);



#ifdef __cplusplus
}
#endif


#endif //CPP_RIFFLE_SCRAMBLER_C_H
