Формат уровней
======

Каждый уровень с номером S представлен директорией S и четырьмя находящимися в ней файлами:

 * S/bg.png - текстура задника,
 * S/towers.txt - описание доступных башен,
 * S/enemies.txt - описание волн врагов,
 * S/map.txt - описание карты уровня.

## bg.png
Должен иметь размер 600x600 и условно делиться на квадраты размером 60x60.

## base.txt
Содержимое имеет вид:

    base_path
    health
    x y

где `base_path` - путь к папке базы,
`health` - здоровье базы,
`x, y` - верхний левый тайл базы.

## towers.txt
Содержимое имеет вид:

    default_balance
    n
    F1
    ...
    Fn

где `n` - количество доступных типов башен,
`default_balance` - количество валюты, доступное в начале уровня,
`Fi` - идентификатор i-й доступной башни.

## enemies.txt

Содержимое имеет вид...

    amount_of_waves
    enemies_per_wave
    cooldown
    delta
    n
    TYPE1
    .....
    TYPEn

где `amount_of_waves` - количество волн на данный уровень,
`enemies_per_wave` - количество врагов в одной волне
`cooldown` - количество волн между приращениями
`delta` - приращение
`n` - количество доступных типов врагов,
`TYPEi` - идентификатор i-го типа врага на данном уровне.
***TODO***

## map.txt

Содержимое имеет вид:

    A1,1 A1,2 ... A1,10
    ...
    A10,1 A10,2 ... A10,10

Число `Ai,j` описывает квадрат в i-й строке и j-м столбце поля. Юниты будут случайным образом
выбирать один из 4-х соседних квадратов, число на котором строго меньше числа на текущем
квадрате, и перемещаться на него.
