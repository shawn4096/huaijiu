// Room: /d/village/hsroad3.c
// ��ɽ��������Ľӿ�

inherit ROOM;

void create()
{
	set("short", "����·");
	set("long", @LONG
	һ���ӿ����ݵ���·�����������Ĳ�֪��ͨ��η���
LONG
	);
        set("outdoors", "��ɽ");

	set("exits", ([
                "south" : "/d/xiangyang/shanxiroad2",
                "north" : __DIR__"sexit",
	]));

	set("coor/x",0);
  set("coor/y",60);
   set("coor/z",0);
   setup();
}

