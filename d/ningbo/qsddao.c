// /u/beyond/ningbo/qsddao1.c 
#include <ansi.h>
inherit ROOM;
void create()
{
        set("short", "��ʯ�ٵ�");
        set("long",@long
������һ����ʯ����ϣ����������ǳ���æ����ʱ������������ҴҶ�����
���������һЩС��̯���ƺ���һ�����С�����������Ǻ��ݳ��ˡ�
long);
set("outdoors", "ningbo");
set("exits",([
"southeast" : __DIR__"shilu",
"northwest" : __DIR__"qsddao1",
]));
set("coor/x",120);
  set("coor/y",-370);
   set("coor/z",0);
   setup();
}
