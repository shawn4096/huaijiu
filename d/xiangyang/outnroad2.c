// /d/xiangyang/outnroad2.c

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
��������������������Ͼ��ڡ��ϱ�ͨ�������ǡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"north" : __DIR__"outnroad3",
		"south" : __DIR__"outnroad1",
        "northeast" : __DIR__"junying",
	]));

   set("coor/x",20);
  set("coor/y",20);
   set("coor/z",0);
   setup();
}

