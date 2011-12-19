#########################################################################################################################
#																														#
#													  Julien Rosset														#
#																														#
#########################################################################################################################
#																														#
#								 Projet : FractalCooker - Plugin 3D - Eponge de Menger									#
#																														#
#########################################################################################################################

############################################## Informations sur le projet ###############################################
PROJECT		=	EpongeMenger
VER_MAJ		=	2
VER_MIN		=	0
VER_PAT		=	0

################################################# Réglages utilisateur ##################################################
win32 {
	CONFIG	+=	debug

	CONFIG(debug,debug|release):CONFIG += console
}
else {
	CONFIG	+=	debug
}

################################################## Suffixe automatique ##################################################
PROJECT_SUFFIX	=
CONFIG(debug, debug|release) {
	PROJECT_SUFFIX	=	d
}

################################################## Paramètres globaux ###################################################
TARGET		=	$${PROJECT}$${PROJECT_SUFFIX}
#TARGET_EXT	=	.fcp									# FractalCooker Plugin
TEMPLATE	=	lib
VERSION		=	$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

message(Projet $$PROJECT $$VERSION)

####################################### Mode de compilation (statique/dynamique) ########################################
CONFIG			+=	warn_on silent plugin dll

####################################################### Nettoyage #######################################################
win32:QMAKE_DISTCLEAN	+=	*_resource.rc \
							object_script.*

###################################################### Répertoires ######################################################
RACINE		=	../../..

DESTDIR		=	$${RACINE}/Final/Plugins

OBJECTS_DIR	=	Temp/objs$${PROJECT_SUFFIX}
MOC_DIR		=	Temp/mocs$${PROJECT_SUFFIX}

##################################################### Configuration #####################################################
INCLUDEPATH	+=	Data/Headers \
				$${RACINE}/Interfaces
DEPENDPATH	+=	Data/Sources

QT			+=	opengl

CODECFORTR	=	UTF-8
CODECFORSRC	=	UTF-8

####################################################### Fichiers ########################################################
HEADERS		+=	Data/Headers/*.h \
				$${RACINE}/Interfaces/Fractale3D.h
SOURCES		+=	Data/Sources/*.cpp
