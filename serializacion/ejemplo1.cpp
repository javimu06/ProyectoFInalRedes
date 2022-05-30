#include "Serializable.h"
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
class Jugador : public Serializable
{
public:
    Jugador(const char* _n, int16_t _x, int16_t _y) :x(_x), y(_y)
    {
        strncpy(name, _n, 80);
    };
    virtual ~Jugador() {};
    void to_bin()
    {
        alloc_data(sizeof(char) * MAX_NAME + sizeof(int16_t) * 2);  //Reservamos espacio
        char* tmp = _data + sizeof(int32_t);                        //Escribe en su espacio reservado (tmp) la informacion relevante
        memcpy(tmp, (void*)name, sizeof(char) * MAX_NAME);
        tmp += sizeof(char) * MAX_NAME;
        memcpy(tmp, &x, sizeof(int16_t));
        tmp += sizeof(int16_t);
        memcpy(tmp, &y, sizeof(int16_t));
    }
    int from_bin(char* data)
    {
        char* tmp = data + sizeof(int32_t);
        memcpy(name, tmp, MAX_NAME);
        tmp += MAX_NAME;
        memcpy(&x, tmp, sizeof(int16_t));
        tmp += sizeof(int16_t);
        memcpy(&y, tmp, sizeof(int16_t));
        return 0;
    }
public:
    static const size_t MAX_NAME = 80;
    char name[MAX_NAME];
    int16_t x;
    int16_t y;
};
int main(int argc, char** argv)
{
    Jugador one_r("", 0, 0);
    Jugador one_w("Player_ONE", 123, 987);
    // 1. Serializar el objeto one_w
    int file = open("one_w.bin", O_RDWR | O_TRUNC | O_CREAT);
    if (file < 0) return -1;
    one_w.to_bin();     //Traduce los datos del jugador al bin
    // 2. Escribir la serialización en un fichero
    write(file, one_w.data(), one_w.size());
    // 3. Leer el fichero
    read(file, one_w.data(), one_w.size());
    close(file);
    // 4. "Deserializar" en one_r
    one_r.from_bin(one_w.data());
    // 5. Mostrar el contenido de one_r
    std::cout << "Jugador: " << one_r.name << " x: " << one_r.x << " y: " << one_r.y << std::endl;
    return 0;
}