// wdroad8.c ����·

inherit ROOM;

void create()
{
        set("short", "ɽ����");
	set("long", @LONG
�������䵱ɽ���£���������ɭɭ�����֡�������һ����ɽ, ���Ϸ���һ
��ͤ��
LONG
	);
        set("outdoors", "wudang");

	set("exits", ([
		"east" : __DIR__"wdroad7",
                "southeast" : "/d/wudang/chating",
                "west" : __DIR__"xuanyuemen",
	]));
	set("objects", ([
		__DIR__"npc/yetu" : 2 ]));

	set("coor/x",30);
  set("coor/y",30);
   set("coor/z",0);
   setup();
}

