// Room: xiaolu1.c

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
		"southeast" : __DIR__"xiaolu2",
		"northeast" : __DIR__"tianhu",
	]));
        set("outdoors", "ѩɽ");
	set("coor/x",-260);
  set("coor/y",130);
   set("coor/z",0);
   setup();
}
