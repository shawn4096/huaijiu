// hsroad1.c

inherit ROOM;

void create()
{
	set("short", "��ʯ���");
	set("long", @LONG
������һ����ʯ����ϣ����������طǳ���æ����ʱ������������ҴҶ�
�����ϱ�ͨ�����ݳǡ���������һ������С������ͨ��һ��Сɽ�ԡ�
LONG
	);
        set("outdoors", "wudang");

	set("exits", ([
                "north" : "/d/huanghe/caodi1",
                "south" : __DIR__"beimen",
                "northwest" : "/d/gb/shangang",
	]));

	set("coor/x",120);
  set("coor/y",40);
   set("coor/z",0);
   set("coor/x",120);
  set("coor/y",40);
   set("coor/z",0);
   setup();
}

