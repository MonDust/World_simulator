# World_simulator
## General description
The project for Object Oriented Programming course - game of survival.

## Project 1 - CPP
Visualization of the virtual world performed in console. 
 
Every organism is presented as a different ASCII symbol:

## ASCII Representation

### Animals:
- **Wolf:** `W`
- **Sheep:** `S`
- **Fox:** `F`
- **Turtle:** `T`
- **Antelope:** `A`
- **Human:** `&`

### Plants:
- **Grass:** `,`
- **Sowthistle:** `-`
- **Guarana:** `/`
- **Belladonna:** `]`
- **Hogweed:** `{`


## Game Controls

### Movement:
Arrows
- **Up:** `KEY_UP` (`0x48`)
- **Down:** `KEY_DOWN` (`0x50`)
- **Left:** `KEY_LEFT` (`0x4b`)
- **Right:** `KEY_RIGHT` (`0x4d`)

### Actions:
- **Confirm Action:** `KEY_ENTER` (Enter: `0x0d`)
- **Cancel Action:** `KEY_CANCEL` (Escape: `27`)
- **Use human's Special Ability:** `KEY_SPECIALABILITY` (`'h'`)

### Game Management:
- **Quit Game:** `KEY_Q` (`'q'`)
- **Save Game:** `KEY_SAVE` (`'k'`)
- **Load Game:** `KEY_LOAD` (`'l'`)

### Additional Controls:
- **Move Forward:** `KEY_W` (`'w'`)
- **Move Left:** `KEY_A` (`'a'`)
- **Move Backward:** `KEY_S` (`'s'`)

The results are reported at the side.

## Project 2 - Java
UI made using swing library. Images used are in the Images folder.

By clicking on an empty (free) map cell it is possible to add new organism of any kind.

## Project 3 - Python
Implemented using Python Imaging Library.
Addition of the Cyber-sheep.

## Information about the projects - all details.
Available in the Instructions folder.

Remark: No implementation of hexagonal grid (both Java and Python).

## Initialization of the project - Windows

### CPP
```
g++ main.cpp -o game.exe
game.exe

```

To use the example save file put them in the same folder as game.exe.

### Python
Requirements:

Pillow: [(Python Imagining Library)](https://pypi.org/project/pillow/)
```
pip install Pillow
```


## Author
O. Paszkiewicz 2023



# Screenshots
## CPP
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/CPP_screenshot1.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/CPP_screenshot2.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/CPP_screenshot3-loadfile.jpg" width="300"/>

## Java
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Java_screenshot1.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Java_screenshot2.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Java_screenshot3.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Java_screenshot4.jpg" width="300"/>

## Python
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Python_screenshot1.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Python_screenshot2.jpg" width="300"/>
<img src="https://github.com/MonDust/World_simulator/blob/main/Images/Python_screenshot3.jpg" width="300"/>
