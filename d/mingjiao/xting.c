// wxiang.c ���᷿
// Modify By River@SJ 99.06
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{ 
       set("short", HIY"С��"NOR);
       set("long", @LONG
���Ǿ�����ǰ��һ��С���������Ժ���Ǿ��������ϱ������䳡��������
�߷ֱ�ͨ���������Ϣ�ҡ�        
LONG);    
        set("exits", ([
                "east" : __DIR__"sleeproom",                          
                "north" : __DIR__"jyt",
                "west" : __DIR__"eatroom",
                "south" : __DIR__"wu1",
        ]));             
        set("objects",([
                __DIR__"npc/f-dizi" : 1,
                __DIR__"npc/m-dizi" : 1,
                CLASS_D("mingjiao") + "/zhou" : 1,
        ]));
        set("coor/x",-290);
  set("coor/y",210);
   set("coor/z",120);
   set("coor/x",-290);
 set("coor/y",210);
   set("coor/z",120);
   setup();
}
