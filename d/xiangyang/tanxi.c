// /d/xiangyang/tanxi.c

inherit ROOM;

void create()
{
	set("short", "̴Ϫ");
	set("long", @LONG
��������һ��С�ӱߣ���ˮ���������峺���ס������ҴҾ����������
���㣬������ǵ�������������׷��ʱԽ����̴Ϫ�����ϱ�����С·������
��ͨ���Ĵ��ġ�
LONG
	);
        set("outdoors", "����");

	set("exits", ([
		"east" : __DIR__"outwroad1",
		"southwest" : __DIR__"xiaolu1",
	]));

	set("coor/x",-30);
  set("coor/y",10);
   set("coor/z",0);
   setup();
}

