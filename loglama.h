#ifndef LOGLAMA_H
#define LOGLAMA_H

// Zaman damgası oluşturur (ör: "2025-07-25 22:53:15")
char *timestamp_olustur(void);

// Log mesajını log.txt'ye yazar (ör: "[2025-07-25 22:53:15] Kullanıcı eklendi")
void loglama(const char *msg);

void loglama(const char *msj);
#endif