// Room: /d/jiaxing/nanhu.c

inherit ROOM;

void create()
{
	set("short", "�����Ϻ�");
	set("long", @LONG
�����Ǽ����Ϻ����ڽ������Ҷ���У����ⱥʵ��һ�������
��ת�ĸ�����Ʈ����ˮ���ɵĺ����ϡ�
LONG
	);

	set("exits", ([
                "west" : __DIR__"jiaxing",
		"south" : __DIR__"tieqiang",
                "southeast" : __DIR__ "nanhu1",
	]));

	set("outdoors", "����");
        set("objects", ([
            ]));

	set("coor/x",150);
  set("coor/y",-300);
   set("coor/z",0);
   setup();
}

