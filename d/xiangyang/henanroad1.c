// /d/xiangyang/henanroad1.c

inherit ROOM;

void create()
{
	set("short", "��·");
	set("long", @LONG
������ԥ���������·�ϣ�ż��������������ҴҶ����������Ѿ��Ǻ���
�ؽ磬�����Ͻ���������ڡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"northeast" : __DIR__"henanroad2",
		"southwest" : __DIR__"outnroad3",
	]));

	set("coor/x",30);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}

