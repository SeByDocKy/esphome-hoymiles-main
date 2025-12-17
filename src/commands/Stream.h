// Stream.h - Compatibility layer
#ifndef STREAM_H
#define STREAM_H

#include <stdint.h>
#include <stddef.h>

class Stream {
public:
    virtual ~Stream() {}
    
    // Méthodes de lecture
    virtual int available() = 0;
    virtual int read() = 0;
    virtual int peek() = 0;
    
    // Méthodes d'écriture
    virtual size_t write(uint8_t) = 0;
    virtual size_t write(const uint8_t *buffer, size_t size) {
        size_t n = 0;
        while (size--) {
            n += write(*buffer++);
        }
        return n;
    }
    
    // Méthodes utilitaires
    virtual void flush() {}
    
    size_t print(const char* str) {
        return write((const uint8_t*)str, strlen(str));
    }
    
    size_t println(const char* str) {
        size_t n = print(str);
        n += write('\r');
        n += write('\n');
        return n;
    }
};

#endif // STREAM_H