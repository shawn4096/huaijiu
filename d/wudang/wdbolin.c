// /d/wudang/wdbolin.c �䵱����
// by ydh
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",HIG"�䵱����"NOR);
        set("long", @LONG
�㴩����һƬï�ܵİ����У���ɭ���䣬�������⡣�����ʱ
������Ұ�޵ĺ����������������٣���æ�ӿ첽����
LONG
        );
        set("exits", ([
                "southup" : __DIR__"shanlu1",
                "eastdown" :__DIR__"yuzhengong",
        ]));

        set("objects",([
//                __DIR__"npc/mulang" : 1,

        ]));
        
        set("coor/x",10);
  set("coor/y",-10);
   set("coor/z",40);
   setup();

}
