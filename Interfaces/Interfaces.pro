#########################################################################################################################
#																														#
#													 Julien Rosset														#
#																														#
#########################################################################################################################
#																														#
#										  Projet : FractalCooker / Interfaces											#
#																														#
#########################################################################################################################

############################################## Informations sur le projet ###############################################
PROJECT		=	Interfaces
VER_MAJ		=	1
VER_MIN		=	0
VER_PAT		=	0

################################################## Suffixe automatique ##################################################
PROJECT_SUFFIX	=
CONFIG(debug, debug|release) {
	PROJECT_SUFFIX	=	d
}

################################################## Paramètres globaux ###################################################
TARGET		=	$${PROJECT}$${PROJECT_SUFFIX}
TEMPLATE	=	lib
VERSION		=	$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

message(Projet $$PROJECT $$VERSION)

#################################################### Configuration ######################################################
CONFIG	+=	warn_on create_prl silent dll

QT		+=	opengl

####################################################### Nettoyage #######################################################
win32:QMAKE_DISTCLEAN	+=	*_resource.rc \
							object_script.*

QMAKE_DISTCLEAN			+=	*.log

################################################ Paramètres compilateur #################################################
QMAKE_CXXFLAGS				+=	-Wall -Wold-style-cast -Wredundant-decls -Winit-self -Wundef -Winline
QMAKE_CXXFLAGS_REALEASE		+=	-O2 -fexpensive-optimisations -fomit-frame-pointer -s

###################################################### Répertoires ######################################################
RACINE		=	..

DESTDIR		=	$${RACINE}/Final

OBJECTS_DIR	=	$${RACINE}/Temp/$${PROJECT}/objs$${PROJECT_SUFFIX}
MOC_DIR		=	$${RACINE}/Temp/$${PROJECT}/mocs$${PROJECT_SUFFIX}

##################################################### Configuration #####################################################
DEPENDPATH	+=	Data/Sources

CODECFORTR	=	UTF-8
CODECFORSRC	=	UTF-8

#Fichiers#
HEADERS		+=	*.h
SOURCES		+=	*.cpp \
    Fractale2D.cpp \
    Fractale3D.cpp \
    Fractale3D.doc.cpp
