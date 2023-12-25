# Используем Debian 12 в качестве базового образа
FROM debian:12

# Обновляем пакеты
RUN apt-get update && apt-get -y install \
    build-essential \
    clang \
    cmake \
    gdb \
    wget \
    echo "start"

# Устанавливаем необходимые пакеты
RUN apt-get install -y g++

# Устанавливаем и настраиваем приложение (если необходимо)

# Определяем команду по умолчанию для запуска контейнера
CMD ["/bin/bash"]

