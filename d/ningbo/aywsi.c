// Room: /u/beyond/ningbo/tianfengta.c ��������
// Beyond make 1997.6.8
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "��������");
	set("long", @LONG
�������µ�����Ի�ɫ�����ߣ������������߼����������ǽ��ʯ��
��â���䡣�ഫ�����ܴ������п��������ӣ�ʯ����������Ĳ�������ڻ�
��ʮ���ľ����Ǽ��õ�����֮����
LONG
	);
	set("exits", ([
	"northwest" : __DIR__"tianyige",
        "west" : __DIR__"tianfengta",
        "southeast" : __DIR__"ningbocheng",
        "east" : "/d/mingjiao/xikou",
	]));
	set("coor/x",140);
  set("coor/y",-390);
   set("coor/z",0);
   setup();
}
