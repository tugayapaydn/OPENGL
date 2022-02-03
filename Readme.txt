Proje Visual Studio 2019 ile build edilmiştir (Eski versiyonları ile de çalışabilmektedir).

GLUT dosyaları konumlandırılması:

glut.h :        C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\{Versiyonunuz}\include\GL.
glut.lib :      C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\{Versiyonunuz}\lib\x64.
glut32.lib :    C:\Program Files (x86)\Microsoft Visual Studio\2017\Community\VC\Tools\MSVC\{Versiyonunuz}\lib\x86.
glut.dll :      C:\Windows\SysWOW64 
glut32.dll :    C:\Windows\SysWOW64 and C:\Windows\System32

GLUT dosyalarını doğru konumlandırdıktan sonra, 
Project > Properties > All Configuration > Configuration Properties > C/C++ > Precompiled Headers

Precompiled Headers değeri Not Using Precompiled Headers olarak değiştirilmelidir.

Ardından,
Configuration Properties > Linker > Input,
Additional Dependencies seçeneğine sağ tıklayarak Edit seçeneğine basın.
Ardından aşağıdakileri kopyalayarak kaydedin.

opengl32.lib
glu32.lib
glut32.lib

 Artık projeyi build edebilirsiniz.