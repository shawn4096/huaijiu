// Room: /d/fuzhou/haigang.c

inherit ROOM;

void create()
{
	set("short", "����");
	set("long", @LONG
�����ǴӸ��������ıؾ�֮�أ�������һ����ۡ�
LONG
	);

	set("exits", ([
        "east" : "/d/gb/yugang",
                "west" : __DIR__"zhongxin",
                "north" : __DIR__"bank",
	]));

	set("objects", ([
                __DIR__"npc/boy":2,
                __DIR__"npc/girl":1,
	]));

	set("outdoors", "����");
	set("coor/x",110);
  set("coor/y",-470);
   set("coor/z",0);
   setup();
}

