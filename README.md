>> # Freshman Programming Project — SDL2 Battle Game
>>
>> This is a simple **two-player battle game** built with **C++** and **SDL2** for my freshman programming course project.
>> Through this project, I learned key concepts of **object-oriented programming (OOP), including:
>>
>> - Classes and Objects
>> - Encapsulation (`public`, `private`, `protected`)
>> - `const` and `static` members
>> - Inheritance
>> - Friend functions
>> - Modular programming with headers and source files
>>
>> This experience helped me understand how to organize and design larger systems,
>> and I hope to apply these skills to more complex projects in the future.
>>
>> ---
>>
>> ## Project Structure
'''
project-root/
├─ src/ # Source code (C++ headers and implementation files)
├─ assets/ # Game assets (images, sounds)
├─ vendor/SDL/ # SDL libraries used for compilation
├─ docs/ # Project report (PDF)
├─ media/ # Presentation videos
└─ dist/ # Executable and runtime DLLs (not included in Git)
'''
>>
>> ---
>>
>> ## Technologies Used
>> - **Language:** C++
>> - **Libraries:** SDL2, SDL2_image, SDL2_mixer, SDL2_ttf, SDL_bgi
>> - **IDE / Tools:** Dev-C++ or Visual Studio Code
>>
>> ---
>>
>> ## How to Run
>> 1. Go to the `dist/` folder.
>> 2. Make sure it contains:
>>    - `SDL.exe`
>>    - All `.dll` files (SDL2, image, mixer, ttf, bgi)
>>    - `img/` and `voi/` folders (for images and sounds)
>> 3. Run `SDL.exe` to start the game.
>>
>> ---
>>
>> ## How to Build (Optional)
>> If you want to recompile the game from source:
>>
>> ```bash
>> g++ src/main.cpp -Ivendor/SDL/SDL2-2.28.5/include -Lvendor/SDL/SDL2-2.28.5/lib ^
>>   -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -o dist/SDL.exe
>>
>> ## Release Build
>> To create a playable zip for release:
>> Compress-Archive -Path ".\dist" -DestinationPath ".\dist-release.zip" -Force
>>
>> Name: (Po Hung Cheng)
>>
>> Project Period: Fall 2023
>>
>> Goal: To master C++ and apply it to more challenging projects in the future.