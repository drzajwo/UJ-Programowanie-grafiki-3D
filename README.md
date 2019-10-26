
OGL Sample na zajęcia z programowania grafiki 3D.

Do skompilwoania i uruchomienia sampli wymagane są:
- system Linuks, Windows, lub MacOS (tylko dla pierwszych sampli, sample od 4 nie będą działać pod MacOS!)
- karta graficzna wspierająca OGL 3.3 (4.2 dla sampli >=4) + odpowiednie sterowniki
- cmake w wersji 2.8, lub nowszej
- kompilator wspierający standard C++17 - gcc (8.2, lub nowszy) dla Linuksa/Mac-a, VS (2017, lub nowszy) dla Windowsa
- biblioteka GLFW (min. ver. 3 (wymagana dla Linuksa i Mac-a) - dla Windowsa dostarczona w wersji 3.3)
- biblioteka glbinding (min. ver. 3 (wymagana dla Mac-a) - dla Linuksa i Windowsa dostarczona w wersji 3.1)

Biblioteki GLM (0.9.9.6) i GLI (ver. 0.8.3) są dostarczone z samplami

Plan zajęć:
- Z1 - zasady zaliczenia + ankieta/kolokwium (20 min) + omówienie kolokwium + teoria (CPU vs GPU, zrównoleglanie kodu, wektoryzacja kodu, dostęp do pamięci, wyrównywanie pamięci) + konfiguracja kont
- Z2 - teoria (architektura GPU, OGL vs DX vs Vulkan, pipeline, NDC) + omówienie bibliotek (GLFW, glbinding, OGL) + zapoznanie z framework-iem ("OGLSample0_EmptyScreen") + pierwszy program w OGL + shader-y + VAO, VBO ("OGLSample1_Triangle")
- Z3 - atrybuty wierzchołków, IB ("OGLSample2_IB_VBO") + interpolacja danych wejściowych do FS ("OGLSample3_VS_FS_Interpolation")
- Z4 - FS i UBO (przysyłanie jednej/kilku zmiennych (typu prostego) - "OGLSample4_UBO_Intensity") + sposoby nadpisywania danych w buforach (glBufferData vs glBufferSubData vs glMapBuffer) + tekstury proceduralne (wstęp)
- Z5 - teoria (macierze, przestrzenie, współrzędne jednorodne) + omówienie biblioteki GLM
- Z6 - UBO + wyrównywanie pamięci + pierwsza scena w 3D ("Sample5_3D") + rendering kilku obiektów
- Z7 - rozdział macierzy na 3 (model, view, projection) + tekstury proceduralne
- Z8 - teoria (parametry dzisiejszych GPU (SP, ROPs, TMUs, PFR, TFR, FLOPS, MB, ...)) + teksturowanie + samplery + omówienie biblioteki GLI
- Z9 - teoria (oświetlenie, transformacje normalnych) + model Phonga
- Z10 - kolokwium
- Z11 - omówienie kolokwium + oświetlenie i tekstury + rendering kilku różnych obiektów
- Z12 - model Blinna-Phonga
- Z13 - model Blinna-Phonga (optymalizacje)
- Z14 - mapowanie normalnych/instancing
- Z15 - oddanie projektów
