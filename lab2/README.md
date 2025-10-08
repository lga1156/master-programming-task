# C++ Custom I/O Manipulators

Простая библиотека на C++ для форматирования вывода с помощью кастомных манипуляторов.

- **`http`**: добавляет префикс `http://`.
- **`squares`**: заключает вывод в `[]`.
- **`add`**: складывает два следующих значения.

## Использование

Подключите `iomanip.hpp` и используйте манипуляторы в потоке вывода.

```cpp
#include <iostream>
#include <string>
#include "iomanip.hpp"

int main() {
    // http
    std::cout << "Сайт: " << http << "yandex.ru" << std::endl;
    //> Сайт: http://yandex.ru

    // squares
    std::cout << "Статус: " << squares << "OK" << ", ID: " << squares << 42 << std::endl;
    //> Статус: [OK], ID: [42]

    // add
    std::cout << "Сумма: " << add << 10 << 5 << std::endl;
    //> Сумма: 15

    std::cout << add << "Hello, " << "World!" << std::endl;
    //> Hello, World!
    
    return 0;
}
```