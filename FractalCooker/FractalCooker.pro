#########################################################################################################################
#																														#
#													  Julien Rosset														#
#																														#
#########################################################################################################################
#																														#
# 										  Projet : FractalCooker - Programme											#
#																														#
#########################################################################################################################

############################################## Informations sur le projet ###############################################
PROJECT		=	FractalCooker
VER_MAJ		=	1
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
TEMPLATE	=	app
VERSION		=	$${VER_MAJ}.$${VER_MIN}.$${VER_PAT}

message(Projet $$PROJECT $$VERSION)

####################################### Mode de compilation (statique/dynamique) ########################################
CONFIG		+=	warn_on link_prl silent

####################################################### Nettoyage #######################################################
win32:QMAKE_DISTCLEAN	+=	*_resource.rc \
							object_script.*

###################################################### Répertoires ######################################################
DESTDIR		=	../Final

OBJECTS_DIR	=	Temp/objs$${PROJECT_SUFFIX}
MOC_DIR		=	Temp/mocs$${PROJECT_SUFFIX}
UI_DIR		=	Temp/uics$${PROJECT_SUFFIX}
RCC_DIR		=	Temp/rccs$${PROJECT_SUFFIX}

##################################################### Configuration #####################################################
INCLUDEPATH	+=	Data/Headers \
				../Interfaces \
				$$UI_DIR
DEPENDPATH	+=	Data/Sources \
				$$RCC_DIR

QT			+=	opengl

CODECFORTR	=	UTF-8
CODECFORSRC	=	UTF-8

####################################################### Fichiers ########################################################
HEADERS		+=	Data/Headers/*.h \
				../Interfaces/*.h
SOURCES		+=	Data/Sources/*.cpp
FORMS		+=	Data/Forms/*.ui
RESOURCES	+=	Data/*.qrc
