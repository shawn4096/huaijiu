// Room: /gaibang/xinglin2.c
// by pishou

inherit ROOM;

void create()
{
    set("short", "������");
	set("long", @LONG
����һƬ�����֣�һ�߽�������·���ʧ�˷��������ӻ���
�Ҵ�, ��ͼ���ֳ�·��
LONG
	);

	set("exits", ([
		"east" : __FILE__,
		"west" : __FILE__,
        "south" : __DIR__"tianjing",
        "north" : __DIR__"xinglin3.c",
	]));
	set("coor/x",110);
  set("coor/y",-170);
   set("coor/z",0);
   setup();
}
