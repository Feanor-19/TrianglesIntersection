# Пересечение треугольников в 3D

## Краткое описание

### TrianglesLib

В данном учебном проекте реализованы следующие геометрические примитивы:

- Point3D
- Vector3D
- LineSeg3D
- Plane
- Triangle3D
- BoundingBox (axis-aligned bounding box)

Реализованы методы для определения пересечений между различными геометрическими объектами, используется переопределение операторов. Алгоритмы определения пересечения взяты из `Eberly, Schneider – Geometric Tools for Computer Graphics, 2002`.

Для ускорения определения пересечений используются axis-aligned bounding boxes.

### Driver

Получает на вход набор из 9 чисел, описывающих координаты трёх точек фигуры. Далее фигуры классифицируются (точка, отрезок или треугольник), определяются индексы всех фигур, которые пересекаются с какой-либо другой, используя методы из TrianglesLib. 

## Установка

### Виртуальное окружение

Все последующие шаги, включая установку conan, можно делать в [виртуальном окружении](https://docs.python.org/3/library/venv.html):

```
python3 -m venv .venv
source .venv/bin/activate
pip3 install conan
```

### Необходимые сторонние инструменты

- cmake >=3.11
- conan >= 2.7.1

Если `conan` используется первый раз, требуется также исполнить: 
```
conan profile detect
```

### Клонирование репозитория

```
git clone https://github.com/Feanor-19/TrianglesIntersection
cd TrianglesIntersection
```

### Подготовка зависимостей

Release configure preset:
```
conan install . --output-folder=build/Release --build=missing --settings=build_type=Release
```

Debug configure preset:
```
conan install . --output-folder=build/Debug --build=missing --settings=build_type=Debug
```

### Сборка с cmake

Release:
```
cd build/Release
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release
cmake --build .
```

Debug:
```
cd build/Debug
cmake ../.. -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug
cmake --build .
```