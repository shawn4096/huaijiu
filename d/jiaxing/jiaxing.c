// Room: /d/jiaxing/jiaxing.c

inherit ROOM;

void create()
{
	set("short", "���˳�");
	set("long", @LONG
�����ǽ������Ǽ��ˡ��Ƕ��Ƿ羰�续���Ϻ���
LONG
	);

	set("exits", ([
                "northwest" : __DIR__"road1",
                "east" : __DIR__"nanhu",
		"south" : __DIR__"jxnanmen",
	]));

        set("outdoors", "����");
	set("coor/x",140);
  set("coor/y",-300);
   set("coor/z",0);
   setup();
}

