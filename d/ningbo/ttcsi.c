// Room: /u/beyond/ningbo/ttcsi.c ��ͯ����
// Beyond make 1997.6.8
#include <room.h>
#include <ansi.h>
inherit ROOM;
void create()
{
	set("short", "��ͯ����");
	set("long", @LONG
��ͯ�����С����Ϸ����֮�ơ��������ذ�ɽ����ģ������ƷǷ���
����Ⱥɽ��������ľ���죬��ɫ�������ˡ������������������ʯ��ᾣ���
ľ���ף�ɽ�����ۣ���ˮ���ȣ�����ʮ�����š�
LONG
	);
	set("exits", ([
	"north" : __DIR__"tianfengta",
        "east" : __DIR__"ningbocheng",
        "southwest" : "/d/fuzhou/road1",
        ]));
	set("coor/x",130);
  set("coor/y",-400);
   set("coor/z",0);
   setup();
}
