#!/bin/bash

# QT Button Demo - Build Script
# Скрипт сборки проекта

set -e

# Цвета для вывода
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Функции вывода
print_header() {
    echo -e "${BLUE}============================================${NC}"
    echo -e "${BLUE} $1${NC}"
    echo -e "${BLUE}============================================${NC}"
}

print_success() {
    echo -e "${GREEN}✓ $1${NC}"
}

print_error() {
    echo -e "${RED}✗ $1${NC}"
}

print_info() {
    echo -e "${YELLOW}ℹ $1${NC}"
}

# Проверка зависимостей
check_dependencies() {
    print_header "Проверка зависимостей"
    
    # Проверка cmake
    if ! command -v cmake &> /dev/null; then
        print_error "cmake не найден. Установите cmake"
        exit 1
    fi
    print_success "cmake найден: $(cmake --version | head -n1)"
    
    # Проверка Qt6
    if ! pkg-config --exists Qt6Core 2>/dev/null; then
        print_info "Qt6 не найден через pkg-config, пробуем найти другим способом..."
        if ! find /usr -name "Qt6Config.cmake" 2>/dev/null | head -n1; then
            print_error "Qt6 не найден. Установите Qt6"
            print_info "Для Ubuntu/Debian: sudo apt install qt6-base-dev"
            print_info "Для macOS: brew install qt6"
            exit 1
        fi
    fi
    print_success "Qt6 найден"
}

# Очистка предыдущей сборки
clean_build() {
    print_header "Очистка предыдущей сборки"
    
    if [ -d "build" ]; then
        rm -rf build
        print_success "Удалена директория build/"
    fi
    
    mkdir -p build
    print_success "Создана директория build/"
}

# Конфигурация проекта
configure_project() {
    print_header "Конфигурация проекта"
    
    cd build
    
    if cmake .. -DCMAKE_BUILD_TYPE=Release; then
        print_success "Конфигурация завершена успешно"
    else
        print_error "Ошибка конфигурации"
        exit 1
    fi
    
    cd ..
}

# Сборка проекта
build_project() {
    print_header "Сборка проекта"
    
    cd build
    
    if cmake --build . --config Release; then
        print_success "Сборка завершена успешно"
    else
        print_error "Ошибка сборки"
        exit 1
    fi
    
    cd ..
}

# Копирование ресурсов
copy_resources() {
    print_header "Копирование ресурсов"
    
    # Копируем QSS файлы
    cp light_theme.qss build/
    cp dark_theme.qss build/
    
    print_success "QSS файлы скопированы в build/"
}

# Поиск исполняемого файла
find_executable() {
    print_header "Поиск исполняемого файла"
    
    # Различные возможные расположения
    possible_paths=(
        "build/qt-button-demo"
        "build/Debug/qt-button-demo"
        "build/Release/qt-button-demo"
        "build/qt-button-demo.exe"
        "build/Debug/qt-button-demo.exe"
        "build/Release/qt-button-demo.exe"
    )
    
    for path in "${possible_paths[@]}"; do
        if [ -f "$path" ]; then
            print_success "Исполняемый файл найден: $path"
            EXECUTABLE_PATH="$path"
            return 0
        fi
    done
    
    print_error "Исполняемый файл не найден"
    return 1
}

# Запуск приложения
run_application() {
    print_header "Запуск приложения"
    
    if find_executable; then
        print_info "Запускаем: $EXECUTABLE_PATH"
        if [ -x "$EXECUTABLE_PATH" ]; then
            ./"$EXECUTABLE_PATH"
        else
            print_error "Файл не является исполняемым: $EXECUTABLE_PATH"
            exit 1
        fi
    else
        print_error "Не удалось найти исполняемый файл"
        exit 1
    fi
}

# Главная функция
main() {
    print_header "QT Button Demo - Build Script"
    
    # Проверяем, что мы в правильной директории
    if [ ! -f "main.cpp" ] || [ ! -f "CMakeLists.txt" ]; then
        print_error "Запустите скрипт из корневой директории проекта"
        exit 1
    fi
    
    # Парсинг аргументов
    CLEAN=false
    RUN=false
    
    while [[ $# -gt 0 ]]; do
        case $1 in
            --clean|-c)
                CLEAN=true
                shift
                ;;
            --run|-r)
                RUN=true
                shift
                ;;
            --help|-h)
                echo "Использование: $0 [опции]"
                echo "Опции:"
                echo "  --clean, -c    Очистить перед сборкой"
                echo "  --run, -r      Запустить после сборки"
                echo "  --help, -h     Показать эту справку"
                exit 0
                ;;
            *)
                print_error "Неизвестная опция: $1"
                exit 1
                ;;
        esac
    done
    
    # Выполнение этапов сборки
    check_dependencies
    
    if [ "$CLEAN" = true ] || [ ! -d "build" ]; then
        clean_build
    fi
    
    configure_project
    build_project
    copy_resources
    
    print_success "Сборка завершена успешно!"
    
    if [ "$RUN" = true ]; then
        run_application
    else
        print_info "Для запуска приложения используйте: $0 --run"
        print_info "Или запустите: python3 presentation_script.py"
    fi
}

# Запуск main функции с передачей всех аргументов
main "$@"

