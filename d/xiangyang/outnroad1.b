// /d/xiangyang/outnroad1.c

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
		"north" : __DIR__"outnroad2",
		"south" : __DIR__"xuanwumen",
        "southeast" : __DIR__"outeroad1",
        "southwest" : __DIR__"outwroad1",
	]));

   set("coor/x",20);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",10);
   set("coor/z",0);
   set("coor/x",20);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

