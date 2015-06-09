Author: Gerrit Lochmann (2014)
Betriebssystem: Windows

OpenGLProject enthält alles, was Sie zur Erstellung von Programmen mit OpenGL 3.3 oder höher unter Windows benötigen.



Voraussetzungen:
------------------------------------------
- CMake muss installiert sein und das Verzeichnis von cmake.exe im PATH eingetragen sein.
- Eine der folgenden IDEs muss installiert sein:
    Visual Studio 2010
    Visual Studio 2012
    Visual Studio 2013
    Eclipse CDT mit MinGW Compiler (Wird in der Vorlesung verwendet)

#=================================================================#
#  Die vom Setup-Script für cmake erzeugten BUILD_*-Verzeichnisse
#  AUF KEINEN FALL in das SVN Repository einchecken.
#  Nur der Quellcode soll in die Versionsverwaltung,
#  NIEMALS die daraus erzeugten Binaries und andere Derivate.
#  Bei Zuwiderhandlung droht Punktabzug !
#=================================================================#


Anleitung zur Projektgenerierung:
------------------------------------------
- Führen Sie setup.bat aus und wählen Sie die von Ihnen verwendete IDE.
- Folgen Sie den Anweisungen des Scripts.
- Anschließend sollten die Umgebungsvariablen der folgenden Dependencies gesetzt sein:
	OpenGL_ROOT
	GLM_ROOT
	GLFW3_ROOT



Anleitung für eigene Executables:
------------------------------------------
- Kopieren Sie eines der Unterverzeichnisse aus 'framework/%TEAM%/src/executables/'.
- Stellen Sie insbesondere sicher, dass die Datei framework/%TEAM%/src/executables/%NAME%/CMakeLists.txt existiert.
- Führen Sie erneut setup.bat aus.



Anleitung für eigene Libraries:
------------------------------------------
- Alle eigenen Libraries werden automatisch gegen alle Executables und gegenseitig verlinkt. Dadurch können Funktionen programmübergreifend verwendet werden.
- Kopieren Sie eines der Unterverzeichnisse aus 'framework/%TEAM%/src/libraries/'.
- Stellen Sie insbesondere sicher, dass die Datei framework/%TEAM%/src/libraries/%NAME%/CMakeLists.txt existiert.
- Führen Sie erneut setup.bat aus.



Anleitung für neue *.cpp und *.h Files:
------------------------------------------
- Erstellen Sie die Dateien in den verlinkten Verzeichnissen in 'framework/%TEAM%/src/libraries/' und 'framework/%TEAM%/src/executables/'. Achtung: Nicht in einem Unterverzeichnis von 'BUILD_%IDE%'!
- Führen Sie gegebenenfalls 'cmake rebuild_cache' oder 'setup.bat' erneut aus.



Anleitung für neue Shader:
------------------------------------------
- Erstellen Sie die Dateien im verlinkten Verzeichnis 'framework/%TEAM%/src/shaders/'.
- In C++ ist das Präprozessor Makro SHADERS_PATH definiert. Es enthält den absoluten Verzeichnisstring zu 'framework/%TEAM%/src/shaders/'. Aus diesem werden zur Laufzeit die Shader geladen.
- Folgende Endungen werden berücksichtigt: *.glsl *.vert *.vertex *.vs *.tcs *.cont *.t_cont *.tes *.eval *.t_eval *.geom *.geo *.geometry *.gs *.frag *.fragment *.fs *.ps *.comp *.compute *.cs.



Anleitung für neue Ressourcen (Texturen, Modelle, usw.):
------------------------------------------
- Legen Sie die entsprechenden Dateien in '/resources/' ab.
- In C++ ist das Präprozessor Makro RESOURCES_PATH definiert. Es enthält den absoluten Verzeichnisstring zu 'framework/%TEAM%/src/shaders/'. Aus diesem werden zur Laufzeit die Shader geladen



Sonstige Informationen allgemein:
------------------------------------------
- Generierte Projektdateien werden in 'BUILD_%IDE%' generiert.
- Ausführbare Dateien werden in 'BUILD_%IDE%/bin/' erzeugt.
- Alle Quellcode Dateien bleiben in 'src' gespeichert. In der IDE sind diese Verzeichnisse verlinkt. Dadurch bleiben alle Dateien in 'src' versionierbar. Versionieren Sie daher lediglich das Verzeichnis 'src'.
- In C++ sind folgende Präprozessor Makros definiert:
    SHADERS_PATH - Enthält den absoluten Verzeichnisstring zu 'framework/%TEAM%/src/shaders'. Aus diesem werden zur Laufzeit die Shader geladen.
    RESOURCES_PATH - Enthält den absoluten Verzeichnisstring zu 'resources'. Aus diesem werden zur Laufzeit Texturen, Modelle usw. geladen.
- Das Verzeichnis 'dependencies' kann an einen beliebigen Pfad verschoben werden (z.B. um Redundanzen zu vermeiden), sofern die Umgebungsvariablen GLFW3_ROOT, GLM_ROOT und OpenGL_ROOT korrekt gesetzt werden. Das Script 'dependencies/SetEnvironment.bat' führt dies für Sie aus.