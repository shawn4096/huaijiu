// /d/jiaxing/tianjing.c �쾮
// by shang 97/6

inherit ROOM;

void create()
{
        set("short", "�쾮");
	set("long", @LONG
����½��ׯׯ���쾮����һ�����ڴ�ɨ�š�
LONG
	);

	set("exits", ([
                "enter" : __DIR__"dating",
                "out" : __DIR__"luzhuang",
	]));

        set("objects", ([
                __DIR__"npc/puren" : 1,
        ]));
        set("outdoors", "����");
	set("coor/x",150);
  set("coor/y",-340);
   set("coor/z",10);
   setup();
}

