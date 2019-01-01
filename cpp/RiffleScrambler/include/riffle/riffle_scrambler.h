//
// Created by konrad on 19.11.18.
//

#ifndef CPP_RIFFLE_SCRAMBLER_H
#define CPP_RIFFLE_SCRAMBLER_H


#include <string>
#include <vector>

/**
 * Hashowanie hasła za pomocą RiffleScrambler, wynik zwracany jest do zmiennej @hash
 * @param pwd Wskaźnik na hasło
 * @param pwdlen_bytes Rozmiar hasła w bajtach
 * @param salt Wskaźnika na sól
 * @param saltlen_bytes Rozmiar soli w bajtach
 * @param t_cost Parametr "lambda" oznaczający ilość iteracji
 * @param m_cost Parametr "g" oznaczający koszt rozmiar używanej pamięci
 * @param hash Bufor do którego będzie zapisany hash hasła
 * @param hashlen Rozmiar bufora, oznacza ile bajtów z hasha hasła ma zostać zapisane
 * @return RIFFLE_SCRAMBLER_OK jeśli obliczenia zakończyły się pomyślnie, kod błędu w przeciwnym przypadku
 */
int riffle_scrambler(void *hash, const size_t hashlen, const void *pwd, const size_t pwdlen_bytes,
        const void *salt, const size_t saltlen_bytes, const uint64_t t_cost, const uint64_t m_cost);

/**
 * Hashowanie hasła za pomocą RiffleScrambler
 * @param password Hasło
 * @param salt Sól
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający koszt czasowy
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia wewnątrz
 * @return Hash hasła jako ciąg znaków w systemie szesnastkowym
 */
std::string riffle_scrambler(const std::string password, const std::string salt,
                             const uint64_t garlic, const uint64_t depth,
                             const std::string hash_func = "sha256");

/**
 * Hashowanie hasła za pomocą RiffleScrambler
 * @param password Wskaźnik na hasło
 * @param pwdlen_bytes Długość hasła w bajtach
 * @param salt Wskaźnik na sól
 * @param saltlen_bytes Długość soli w bajtach
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający koszt czasowy
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia wewnątrz
 * @return Hash hasła jako ciąg znaków w systemie szesnastkowym
 */
std::string riffle_scrambler(const void *const password, const size_t pwdlen_bytes,
                            const void *const salt, const size_t saltlen_bytes,
                            const uint64_t garlic, const uint64_t depth,
                            const std::string hash_func="sha256");

/**
 * Hashowanie hasła za pomocą RiffleScrambler
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający koszt czasowy
 * @param password Hasło
 * @param salt Sól
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia wewnątrz
 * @return Hash hasła jako wektor znaków w systemie szesnastkowym
 */
std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic, const uint64_t depth,
        const std::string password, const std::string salt,
        const std::string hash_func="sha256");

/**
 * Hashowanie hasła za pomocą RiffleScrambler
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający koszt czasowy
 * @param pwd Wskaźnik na hasło
 * @param pwdlen_bytes Długość hasła w bajtach
 * @param salt Wskaźnik na sól
 * @param saltlen_bytes Długość soli w bajtach
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia wewnątrz
 * @return Hash hasła jako wektor znaków w systemie szesnastkowym
 */
std::vector<unsigned char> riffle_scrambler_hash_raw(const uint64_t garlic,
         const uint64_t depth, const void *pwd, const size_t pwdlen_bytes,
         const void *salt, const size_t saltlen_bytes, const std::string hash_func="sha256");


/**
 * Hashowanie hasła za pomocą RiffleScrambler i kodowanie wyniku wraz z parametrami w jeden ciąg znaków
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający koszt czasowy
 * @param pwd Wskaźnik na hasło
 * @param pwdlen_bytes Długość hasła w bajtach
 * @param salt Wskaźnik na sól
 * @param saltlen_bytes Długość soli w bajtach
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia wewnątrz
 * @return Zakodowane parametry funkcji wraz z hashem hasła i solą
 */
std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
        const void *pwd, const size_t pwdlen_bytes,
        const void *salt, const size_t saltlen_bytes, const std::string hash_func="sha256");

/**
 * Hashowanie hasła za pomocą RiffleScrambler i kodowanie wyniku wraz z parametrami w jeden ciąg znaków
 * @param garlic Paremetr "g" oznaczający koszt pamięci
 * @param depth Parametr "lambda" oznaczający koszt czasowy
 * @param pwd Hasło
 * @param salt Sól
 * @param hash_func Nazwa kryptograficznej funkcji skrótu do użycia wewnątrz
 * @return Zakodowane parametry funkcji wraz z hashem hasła i solą
 */
std::string riffle_scrambler_encoded(const uint64_t garlic, const uint64_t depth,
        const std::string pwd,
        const std::string salt, const std::string hash_func="sha256");


/**
 * Weryfikacja hasha hasła z hashem zakodowanym hashem dla zakodowanych parametrów i soli
 * @param encoded Zakodowane parametry wraz z hashem i solą
 * @param pwd Hasło
 * @return true jeśli hashe są równe, false w przeciwny przypadku
 */
bool riffle_scrambler_verify(const std::string encoded, const std::string pwd);


/**
 * Weryfikacja hasha hasła z hashem zakodowanym hashem dla zakodowanych parametrów i soli
 * @param encoded Zakodowane parametry wraz z hashem i solą
 * @param pwd Wskaźnik na hasło
 * @param pwd_len Długość hasła w bajtach
 * @return true jeśli hashe są równe, false w przeciwny przypadku
 */
bool riffle_scrambler_verify(const std::string encoded, const void *pwd, const size_t pwd_len);



#endif // CPP_RIFFLE_SCRAMBLER_H
