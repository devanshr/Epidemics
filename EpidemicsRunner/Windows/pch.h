// pch.h: Dies ist eine vorkompilierte Headerdatei.
// Die unten aufgeführten Dateien werden nur einmal kompiliert, um die Buildleistung für zukünftige Builds zu verbessern.
// Dies wirkt sich auch auf die IntelliSense-Leistung aus, Codevervollständigung und viele Features zum Durchsuchen von Code eingeschlossen.
// Die hier aufgeführten Dateien werden jedoch ALLE neu kompiliert, wenn mindestens eine davon zwischen den Builds aktualisiert wird.
// Fügen Sie hier keine Dateien hinzu, die häufig aktualisiert werden sollen, da sich so der Leistungsvorteil ins Gegenteil verkehrt.

#ifndef PCH_H
#define PCH_H
#define NOMINMAX //somehow Windows.h is included here. If this is not included, numeric_limist<double>::min will not work due to conflicting macro definition, see  https://stackoverflow.com/questions/4913922/possible-problems-with-nominmax-on-visual-c
// Fügen Sie hier Header hinzu, die vorkompiliert werden sollen.

#endif //PCH_H
