#include <room.h>

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "����");
	set("long", @LONG
���Ǳ����ţ���Ϊ����ʧ�𣬵����ڳ�ǽ���Ǻں����ģ���˰�ֽ����
�Ĺٸ���ʾ(gaoshi)���Ե��ر����ۡ�������һƬ��ɽ���룬һ������С��
��ɽ�����Ѷ��ϡ�
LONG
	);

	set("item_desc", ([
		"gaoshi" : (:look_gaoshi:),
	]));

	set("exits",([
                  "north" : __DIR__"qsgdao6",
                  "west" : __DIR__"bingying.c",
                  "south" : __DIR__"beidajie2",
	]));
        set("objects", ([
                __DIR__"npc/wujiang" : 1,
                __DIR__"npc/bing" : 2,
        ]));
	set("outdoors", "suzhou");
	set("coor/x",110);
  set("coor/y",-190);
   set("coor/z",0);
   setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n����֪��\n��֪��\n";
}

