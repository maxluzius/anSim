Author: Detlev Droege, Gerrit Lochmann, Kati Hebborn (2015)
Betriebssystem: Mac OS X (10.7 oder neuer)

OpenGLProject enthält alles, was Sie zur Erstellung von Programmen mit OpenGL 3.3 oder höher unter Windows benötigen.


Voraussetzungen:
------------------------------------------
- XCode installieren (incl. Command Line Interface (CLI)) [kostenlos von Apple]
- Als IDEs muss installiert sein:
    Eclipse und das zusätzliche CDT-Modul für C++ [http://eclipse.org] 
    sowie das Plugin Subversive (oder SubClipse) (für Subversion / SVN)
    (experimentell: man kann auch ohne Eclipse direkt mit XCode arbeiten,
    in der Online-Klausur wird aber auf jeden Fall Eclipse (unter Linux) verwendet.)
- CMake muss installiert werden
    Das geht am einfachsten mit MacPorts oder HomeBrew (s.u.)

Anleitung zur Projektgenerierung:
------------------------------------------
- Wechseln Sie in einem Terminal-Fenster in das Verzeichnis, in dem 
  diese Datei steht und rufen sie
    sh setupmac.sh
  auf.
- Folgen Sie den Anweisungen des Scripts.

#=================================================================#
#  Die vom Setup-Script für cmake erzeugten BUILD_*-Verzeichnisse
#  AUF KEINEN FALL in das SVN Repository einchecken.
#  Nur der Quellcode soll in die Versionsverwaltung,
#  NIEMALS die daraus erzeugten Binaries und andere Derivate.
#  Bei Zuwiderhandlung droht Punktabzug !
#=================================================================#


Anleitung für eigene Executables:
------------------------------------------
- Erstellen sie ein neues Unterverzeichnisse in 'framework/%TEAM%/src/executables/'
  nach dem Muster von 01_Start (CG) bzw. blatt00 (BV).
- Stellen Sie insbesondere sicher, dass in dem neuen Verzeichnis die Datei 
  framework/%TEAM%/src/executables/%NAME%/CMakeLists.txt wie in der Vorlage existiert.
- Führen Sie erneut setupmac.sh aus.


Anleitung für eigene Libraries:
------------------------------------------
- Alle eigenen Libraries werden automatisch gegen alle Executables und gegenseitig
  verlinkt. Dadurch können Funktionen programmübergreifend verwendet werden.
- Kopieren Sie eines der Unterverzeichnisse aus 'framework/libraries/'.
- Stellen Sie insbesondere sicher, dass die Datei framework/libraries/%NAME%/CMakeLists.txt existiert mit dem gleichen Inhalt wie in den vorhandenen Verzeichnissen.
- Führen Sie erneut setupmac.sh aus.



Anleitung für neue *.cpp und *.h Files:
------------------------------------------
- Erstellen Sie die Dateien in den verlinkten Verzeichnissen in 'framework/%TEAM%/src/libraries/' und 'framework/%TEAM%/src/executables/'. Achtung: Nicht in einem Unterverzeichnis von 'BUILD_%IDE%'!
- Führen Sie gegebenenfalls 'cmake rebuild_cache' oder 'setupmac.sh' erneut aus.



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
- Das Verzeichnis 'dependencies' kann nicht an einen beliebigen Pfad verschoben werden!