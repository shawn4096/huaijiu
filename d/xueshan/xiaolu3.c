// Room: xiaolu3.c

inherit ROOM;

void create()
{
	set("short", "����С·");
	set("long", @LONG
������ߵ�һ��С·����ǰ��������ͷ����֪��ͨ�����·��Ұ���ҷ���
�������裬�������Լ��ĽŲ�����������ֻ����һ����һ���͵�������
LONG
	);

	set("exits", ([
		"north" : __DIR__"hubian",
		"west" : __DIR__"xiaolu2",
		"east" : __DIR__"fozhaomen",
	]));
        set("outdoors", "ѩɽ");
	set("coor/x",-240);
  set("coor/y",120);
   set("coor/z",0);
   setup();
}
