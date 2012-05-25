#########################################################################################################################
#																														#
#													 Julien Rosset														#
#																														#
#########################################################################################################################
#																														#
#										 Projet : FractalCooker / FractalCooker											#
#																														#
#########################################################################################################################

############################################## Informations sur le projet ###############################################
PROJECT		=	FractalCooker
VER_MAJ		=	1
VER_MIN		=	0
VER_PAT		=	0

################################################## Suffixe automatique ##################################################
PROJECT_SUFFIX	=
CONFIG(debug, debug|release) {
	PROJECT_SUFFIX	=	d

	win32 {
		CONFIG += console
	}
}

################################################## Paramètres globaux ###################################################
TARGET		=	$${PROJECT}$${PROJECT_SUFFIX}
TEMPLATE	=	app
VERSION		=	$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

message(Projet $$PROJECT $$VERSION)

#################################################### Configuration ######################################################
CONFIG	+=	warn_on link_prl silent dll

QT		+=	opengl

####################################################### Nettoyage #######################################################
win32:QMAKE_DISTCLEAN	+=	*_resource.rc \
							object_script.*

QMAKE_DISTCLEAN			+=	*.log

################################################ Paramètres compilateur #################################################
QMAKE_CXXFLAGS				+=	-Wall -Wold-style-cast -Wredundant-decls -Winit-self -Wundef -Winline
QMAKE_CXXFLAGS_RELEASE		+=	-O2 -fexpensive-optimisations -fomit-frame-pointer -s

###################################################### Répertoires ######################################################
RACINE		=	..

DESTDIR		=	$${RACINE}/Final

OBJECTS_DIR	=	$${RACINE}/Temp/$${PROJECT}/objs$${PROJECT_SUFFIX}
MOC_DIR		=	$${RACINE}/Temp/$${PROJECT}/mocs$${PROJECT_SUFFIX}
UI_DIR		=	$${RACINE}/Temp/$${PROJECT}/uics$${PROJECT_SUFFIX}
RCC_DIR		=	$${RACINE}/Temp/$${PROJECT}/rccs$${PROJECT_SUFFIX}

###################################################### Librairies #######################################################
LIBS		+=	-L$${DESTDIR} -lInterfaces$${PROJECT_SUFFIX}

##################################################### Configuration #####################################################
CODECFORTR	=	UTF-8
CODECFORSRC	=	UTF-8

INCLUDEPATH	=	$$RACINE

#Fichiers#
HEADERS		+=	*.h
SOURCES		+=	*.cpp
FORMS		+=	*.ui
RESOURCES	+=	*.qrc
