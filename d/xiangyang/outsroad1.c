// /d/xiangyang/outsroad1.c

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������ǳ���æ����ʱ����������ҴҶ�����
������Ͻ�����Ͼ��ڡ�����ͨ�������ǡ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"south" : __DIR__"outsroad2",
//        "northeast" : __DIR__"outeroad1",
//        "northwest" : __DIR__"outwroad1",
		"north" : __DIR__"zhuquemen",
	]));

	set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",-10);
   set("coor/z",0);
   setup();
}

