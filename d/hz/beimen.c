// /u/beyond/hz/beimen.c ����
#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_gaoshi();
void create()
{
	set("short",HIY"����"NOR);
	set("long", @LONG
������Ǻ��ݳǵı����ˣ��׻�˵���������ã������պ���Ľ��������
�ο����ﲻ������վ�ڳ��ſڰ��صĹٱ���Ҳϸϸ�̲�������οͣ�������
�߹�������æ��ǰ�̲顣���ſ�����һ�Ÿ�ʾ(gaoshi)��
LONG
	);
	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));
	set("exits",([
                  "north" : __DIR__"qsddao7",
                  "south" : __DIR__"qsddao6",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
	set("outdoors", "hz");
	set("coor/x",100);
  set("coor/y",-310);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n����\n";
}

