// /u/beyond/hangzhou/hubian.c ������
#include <ansi.h>
#include <room.h>
inherit ROOM;
void create()
{
        set("short",GRN"��������"NOR);
        set("long", @LONG
    ��������ɽ��ˮ�㣬�̲�����������ɽɫ����ӳ��Ȥ�����ۺ�������
�����У������������续���Ρ�����֮�����������Թ����������ǳ����ޡ�
�����ġ��㡢�ᡢ������������
LONG
        );
set("objects",([
__DIR__"npc/you" : 2,

]));
        set("exits", ([
"west" : __DIR__"lxs",
"south" : __DIR__"dhq",
]));
	set("outdoors", "����");
        set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",90);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}
