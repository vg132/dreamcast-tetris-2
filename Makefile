# KallistiOS 1.2.0
#
# dctetris/Makefile
# (c)2002-2003 Viktor Gars
#

include $(KOS_BASE)/Makefile.rules

COMMON_OBJS = ../dccommon/src/id3.o ../dccommon/src/linkedlist.o ../dccommon/src/vmu.o \
							../dccommon/src/dccontrol.o ../dccommon/src/dreamcast.o ../dccommon/src/gldraw.o

TETRIS_OBJS = src/sound/music.o src/sound/cdda.o src/sound/filemusic.o src/xml/xmlparser.o \
							src/theme/background.o \
							src/theme/themeinfo.o src/theme/themehandler.o src/sound/sound.o src/tetris.o \
							src/field.o src/player.o src/draw.o src/game.o src/control.o src/highscore.o \
							src/main.o

#RELEASE_TYPE=_TETRIS_DEBUG_
RELEASE_TYPE=_TETRIS_RELEASE_

DATAOBJS = bin/romdisk.o

#TARGET = /share/temp/dreamcast/tetris.elf
TARGET=bin/tetris.elf

KOS_LOCAL_CFLAGS = -D$(RELEASE_TYPE) -I$(KOS_BASE)/addons/zlib

all: romdisk tetris main dist

clean:
	-rm -f $(TETRIS_OBJS)
	-rm -f bin/tetris.elf
	-rm -f bin/romdisk.*
	-rm -f $(TARGET)

romdisk.img:
	$(KOS_GENROMFS) -f bin/romdisk.img -d romdisk -v

romdisk: romdisk.img
	$(KOS_BASE)/utils/bin2o/bin2o bin/romdisk.img romdisk bin/romdisk.o

main: $(MAIN_OBJS) romdisk
	$(KOS_CCPLUS) $(KOS_CFLAGS) $(KOS_CPPFLAGS) $(KOS_LDFLAGS) -o $(TARGET) \
	$(KOS_START) $(MAIN_OBJS) $(TETRIS_OBJS) $(COMMON_OBJS) $(DATAOBJS) $(OBJEXTRA) $(KOS_LIBS)\
	-lk++ -lgl -lmp3 -lpng -lbz2 -lz -ldcplib -lm -lkallisti -lgcc -lpcx -lexpat $(KOS_LIBS)

tetris: $(TETRIS_OBJS)

run:
	$(KOS_LOADER) $(TARGET)

dist:
	$(KOS_STRIP) $(TARGET)
