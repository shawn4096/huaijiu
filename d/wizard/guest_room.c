#include <room.h>
inherit ROOM;

void create()
{
        set("short", "��ʦ�����");
        set("long", @LONG
¥������ʦ��Ϣ�ң�һ����ҵ��������ϲ�ȥ�ˡ��м�����ʦ���ڽ���
���֪���������Ļ����ڸɻ
LONG);

        set("item_desc", ([
                "up": "�������ǰһƬ������ʲôҲ���������\n",
        ]));

        set("exits", ([
//                 "north": "/u/snowman/bqp/bingqipu",
                "up": __DIR__"wizard_room",
		"southeast": "/d/city/chmiao",
	]));
        set("no_fight", 1);
	set("sleep_room", 1);
	set("no_sleep_room", 1);

	set("objects", ([
		"/clone/npc/wizard" : 1,
	]));

        set("coor/x",100);
  set("coor/y",30);
   set("coor/z",0);
   setup();
        call_other("/clone/board/towiz_b", "???");
}

void init()
{
        add_action("action", ({
                "dazuo",
                "du",
                "exercise",
                "lian",
                "practice",
                "respirate",
                "study",
                "tuna"
        }));
}
int action()
{
        write("���޷���������������\n");
        return 1;
}
int valid_leave(object me, string dir)
{
        if( dir=="up" && !wizardp(me) )
                return notify_fail("����ֻ����ʦ���ܽ�ȥ��\n");
        return ::valid_leave(me, dir);
}
